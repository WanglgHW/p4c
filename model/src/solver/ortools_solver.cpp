/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * SolverBackend implementations (Doc 05). The OR-Tools path is compiled only
 * when RALLOC_HAVE_ORTOOLS=1 (CMake find_package(ortools)). Otherwise
 * OrToolsBackend reports unavailable and the facade forces legacy fallback
 * (Doc 06 §5).
 *
 * Two engines, picked per model by isCpSatEligible():
 *   CP-SAT    all-discrete models (every ralloc sub-model): integral rows,
 *             native `OnlyEnforceIf` indicators, solution hints, proven gap.
 *   MPSolver  models with continuous variables: MIP via OR-Tools' bundled
 *             SCIP/CBC, indicators relaxed to big-M.
 */
#include "ralloc/ortools_solver.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <limits>
#include <utility>

#if RALLOC_HAVE_ORTOOLS
#include "absl/time/time.h"
#include "ortools/linear_solver/linear_solver.h"
#include "ortools/sat/cp_model.h"
#include "ortools/sat/cp_model_solver.h"
#include "ortools/sat/sat_parameters.pb.h"
#include "ortools/util/sorted_interval_list.h"
#endif

namespace ralloc {

namespace {

/// Tolerance for "this double is really an integer".
constexpr double kIntTol = 1e-9;
/// Largest power-of-ten row scaling we are willing to apply before declaring a
/// model non-integral (beyond this the int64 coefficients get risky).
constexpr double kMaxScale = 1e6;

bool isIntegral(double v) { return std::abs(v - std::llround(v)) <= kIntTol; }

bool isFiniteBound(double v) {
    return std::isfinite(v) && std::abs(v) < std::numeric_limits<double>::max() / 4;
}

/// Smallest power-of-ten scale in [1, kMaxScale] that makes every value in
/// `xs` integral. Returns false if none does (model is genuinely fractional).
/// Scaling a whole row (coefficients *and* rhs) is semantics-preserving.
bool integerScale(const std::vector<double> &xs, double *scale) {
    for (double s = 1.0; s <= kMaxScale; s *= 10.0) {
        bool ok = true;
        for (double x : xs) {
            if (!isIntegral(x * s) || std::abs(x * s) > 4.0e18) {
                ok = false;
                break;
            }
        }
        if (ok) {
            *scale = s;
            return true;
        }
    }
    return false;
}

/// Row (or objective) values that must share one scale factor.
std::vector<double> rowValues(const Row &r) {
    std::vector<double> vals = r.coeffs;
    vals.push_back(r.rhs);
    return vals;
}

}  // namespace

// ---------------------------------------------------------------------------
// LpExportBackend: write the .lp and return "no solution" (CI path).
// ---------------------------------------------------------------------------
Solution LpExportBackend::solve(const LinearModel &m, const SolverParams &) {
    std::ofstream(out_path_) << m.toLpString();
    Solution s;
    s.outcome = SolveOutcome::TimeoutNoSolution;  // export-only never solves
    return s;
}

// ---------------------------------------------------------------------------
// Model classification (works with or without OR-Tools linked).
// ---------------------------------------------------------------------------
bool OrToolsBackend::isCpSatEligible(const LinearModel &m) {
    for (const Var &v : m.vars()) {
        if (v.type == VarType::Continuous) return false;
        if (isFiniteBound(v.lb) && !isIntegral(v.lb)) return false;
        if (isFiniteBound(v.ub) && !isIntegral(v.ub)) return false;
    }
    double scale = 1.0;
    for (const Row &r : m.rows())
        if (!integerScale(rowValues(r), &scale)) return false;
    for (const IndicatorRow &ir : m.indicators())
        if (!integerScale(rowValues(ir.implied), &scale)) return false;
    std::vector<double> objs;
    objs.reserve(m.vars().size());
    for (const Var &v : m.vars()) objs.push_back(v.obj);
    return integerScale(objs, &scale);
}

// ---------------------------------------------------------------------------
// OrToolsBackend
// ---------------------------------------------------------------------------
struct OrToolsBackend::Impl {
    std::vector<double> warm;  ///< partial primal hint, NaN = unset
};

#if RALLOC_HAVE_ORTOOLS
namespace {

namespace sat = operations_research::sat;
using operations_research::Domain;
using operations_research::MPConstraint;
using operations_research::MPSolver;
using operations_research::MPSolverParameters;
using operations_research::MPVariable;

/// Finite stand-in for an infinite CP-SAT variable bound. Comfortably inside
/// int64 so that coefficient * bound products cannot overflow.
constexpr double kCpSatInfinity = 1e15;

/// Relative MIP gap from an incumbent objective and a dual bound.
double relGap(double obj, double bound) {
    const double denom = std::max(1e-10, std::abs(obj));
    return std::abs(obj - bound) / denom;
}

// --- CP-SAT ---------------------------------------------------------------

/// Discrete-variable handles: binaries stay BoolVars (so they can drive
/// `OnlyEnforceIf` directly), general integers become IntVars.
struct CpVars {
    std::vector<sat::BoolVar> bools;
    std::vector<sat::IntVar> ints;
    std::vector<bool> is_bool;

    void addTerm(sat::LinearExpr *e, VarRef i, int64_t coeff) const {
        if (is_bool[i]) {
            *e += sat::LinearExpr::Term(bools[i], coeff);
        } else {
            *e += sat::LinearExpr::Term(ints[i], coeff);
        }
    }
};

/// sum(coeff*var) as a CP-SAT expression, all coefficients scaled by `scale`.
sat::LinearExpr scaledExpr(const CpVars &cv, const Row &r, double scale) {
    sat::LinearExpr e;
    for (std::size_t i = 0; i < r.vars.size(); ++i)
        cv.addTerm(&e, r.vars[i], std::llround(r.coeffs[i] * scale));
    return e;
}

/// Domain of admissible values for `sum == expr` given the row sense and rhs.
Domain senseDomain(Sense sense, int64_t rhs) {
    switch (sense) {
        case Sense::LE:
            return Domain(std::numeric_limits<int64_t>::min() / 4, rhs);
        case Sense::GE:
            return Domain(rhs, std::numeric_limits<int64_t>::max() / 4);
        case Sense::EQ:
            break;
    }
    return Domain(rhs, rhs);
}

Solution runCpSat(const LinearModel &m, const SolverParams &p, const std::vector<double> &warm) {
    sat::CpModelBuilder cp;
    cp.SetName(m.name());

    CpVars cv;
    cv.bools.reserve(m.vars().size());
    cv.ints.reserve(m.vars().size());
    cv.is_bool.reserve(m.vars().size());
    for (const Var &v : m.vars()) {
        const bool binary = v.type == VarType::Binary;
        const int64_t lb = std::llround(isFiniteBound(v.lb) ? v.lb : -kCpSatInfinity);
        const int64_t ub = std::llround(isFiniteBound(v.ub) ? v.ub : kCpSatInfinity);
        if (binary) {
            sat::BoolVar b = cp.NewBoolVar().WithName(v.name);
            // Respect fixed binaries (lb==ub) coming from presolve/warm starts.
            if (lb == 1) cp.AddEquality(b, 1);
            if (ub == 0) cp.AddEquality(b, 0);
            cv.bools.push_back(b);
            cv.ints.push_back(sat::IntVar());
        } else {
            cv.bools.push_back(sat::BoolVar());
            cv.ints.push_back(cp.NewIntVar(Domain(lb, ub)).WithName(v.name));
        }
        cv.is_bool.push_back(binary);
    }

    // linear rows (each row scaled independently — semantics preserving)
    for (const Row &r : m.rows()) {
        double scale = 1.0;
        integerScale(rowValues(r), &scale);
        cp.AddLinearConstraint(scaledExpr(cv, r, scale),
                               senseDomain(r.sense, std::llround(r.rhs * scale)))
            .WithName(r.name);
    }

    // indicator rows: native enforcement literal, no big-M (Doc 03 §8)
    for (const IndicatorRow &ir : m.indicators()) {
        double scale = 1.0;
        integerScale(rowValues(ir.implied), &scale);
        sat::BoolVar lit = cv.is_bool[ir.trigger] ? cv.bools[ir.trigger] : sat::BoolVar();
        if (!cv.is_bool[ir.trigger]) {
            // Non-binary trigger: reify `trigger >= 1` into a literal.
            lit = cp.NewBoolVar();
            cp.AddGreaterOrEqual(cv.ints[ir.trigger], 1).OnlyEnforceIf(lit);
            cp.AddLessOrEqual(cv.ints[ir.trigger], 0).OnlyEnforceIf(lit.Not());
        }
        cp.AddLinearConstraint(scaledExpr(cv, ir.implied, scale),
                               senseDomain(ir.implied.sense, std::llround(ir.implied.rhs * scale)))
            .WithName(ir.name)
            .OnlyEnforceIf(ir.trigger_value ? lit : lit.Not());
    }

    // objective
    double obj_scale = 1.0;
    {
        std::vector<double> objs;
        objs.reserve(m.vars().size());
        for (const Var &v : m.vars()) objs.push_back(v.obj);
        integerScale(objs, &obj_scale);
    }
    sat::LinearExpr obj;
    for (std::size_t i = 0; i < m.vars().size(); ++i) {
        const double c = m.vars()[i].obj;
        if (c == 0.0) continue;
        cv.addTerm(&obj, static_cast<VarRef>(i), std::llround(c * obj_scale));
    }
    if (m.objSense() == ObjSense::Minimize) {
        cp.Minimize(obj);
    } else {
        cp.Maximize(obj);
    }

    // warm start (Doc 05 §6): a partial hint; CP-SAT repairs the rest.
    if (warm.size() == m.vars().size()) {
        for (std::size_t i = 0; i < warm.size(); ++i) {
            if (std::isnan(warm[i])) continue;
            if (cv.is_bool[i]) {
                cp.AddHint(cv.bools[i], warm[i] > 0.5);
            } else {
                cp.AddHint(cv.ints[i], std::llround(warm[i]));
            }
        }
    }

    // parameters
    sat::SatParameters params;
    params.set_max_time_in_seconds(p.time_limit_s);
    params.set_relative_gap_limit(p.gap);
    params.set_random_seed(static_cast<int>(p.seed));
    if (p.deterministic) {
        params.set_num_workers(1);
    }
    if (p.emphasis_feasibility) {
        // O5: any legal allocation, as fast as possible.
        params.set_stop_after_first_solution(true);
    }
    if (!p.dump_path.empty()) {
        params.set_log_search_progress(true);
        params.set_log_to_stdout(false);
        params.set_log_to_response(true);
        std::ofstream(p.dump_path + ".lp") << m.toLpString();
        std::ofstream(p.dump_path + ".pb.txt") << cp.Proto().DebugString();
    }

    const sat::CpSolverResponse resp = sat::SolveWithParameters(cp.Build(), params);

    Solution out;
    out.solve_time_s = resp.wall_time();
    out.bound = resp.best_objective_bound() / obj_scale;
    if (!p.dump_path.empty() && !resp.solve_log().empty())
        std::ofstream(p.dump_path + ".log") << resp.solve_log();

    if (resp.status() == sat::CpSolverStatus::OPTIMAL ||
        resp.status() == sat::CpSolverStatus::FEASIBLE) {
        out.values.resize(m.vars().size());
        for (std::size_t i = 0; i < m.vars().size(); ++i)
            out.values[i] = cv.is_bool[i]
                                ? static_cast<double>(sat::SolutionBooleanValue(resp, cv.bools[i]))
                                : static_cast<double>(sat::SolutionIntegerValue(resp, cv.ints[i]));
        out.objective = resp.objective_value() / obj_scale;
        out.gap = relGap(out.objective, out.bound);
        out.outcome = resp.status() == sat::CpSolverStatus::OPTIMAL ? SolveOutcome::Optimal
                                                                    : SolveOutcome::Feasible;
    } else if (resp.status() == sat::CpSolverStatus::INFEASIBLE) {
        out.outcome = SolveOutcome::Infeasible;
    } else if (resp.status() == sat::CpSolverStatus::UNKNOWN) {
        out.outcome = SolveOutcome::TimeoutNoSolution;
    } else {
        out.outcome = SolveOutcome::Error;  // MODEL_INVALID
    }
    return out;
}

// --- MPSolver (mixed/continuous models) -----------------------------------

/// A big-M large enough to switch off `r` over the variables' own bounds.
double bigM(const LinearModel &m, const Row &r) {
    double span = std::abs(r.rhs);
    for (std::size_t i = 0; i < r.vars.size(); ++i) {
        const Var &v = m.vars()[r.vars[i]];
        const double lo = isFiniteBound(v.lb) ? v.lb : -1e9;
        const double hi = isFiniteBound(v.ub) ? v.ub : 1e9;
        span += std::abs(r.coeffs[i]) * std::max(std::abs(lo), std::abs(hi));
    }
    return span + 1.0;
}

Solution runMpSolver(const LinearModel &m, const SolverParams &p, const std::vector<double> &warm) {
    // Only a MIP-capable engine may see a model with integrality: GLOP would
    // silently solve the relaxation, so it is offered for pure LPs only.
    bool has_discrete = false;
    for (const Var &v : m.vars())
        if (v.type != VarType::Continuous) has_discrete = true;
    const std::vector<const char *> mip_ids{"SCIP", "CBC", "HIGHS"};
    const std::vector<const char *> lp_ids{"GLOP", "SCIP", "CBC", "HIGHS"};

    std::unique_ptr<MPSolver> solver;
    for (const char *id : has_discrete ? mip_ids : lp_ids) {
        solver.reset(MPSolver::CreateSolver(id));
        if (solver) break;
    }
    Solution out;
    if (!solver) {
        // No suitable engine in this OR-Tools build -> caller falls back.
        out.outcome = SolveOutcome::Error;
        return out;
    }
    const double kInf = MPSolver::infinity();

    std::vector<MPVariable *> vars(m.vars().size(), nullptr);
    for (std::size_t i = 0; i < m.vars().size(); ++i) {
        const Var &v = m.vars()[i];
        const double lb = isFiniteBound(v.lb) ? v.lb : -kInf;
        const double ub = isFiniteBound(v.ub) ? v.ub : kInf;
        vars[i] = v.type == VarType::Continuous ? solver->MakeNumVar(lb, ub, v.name)
                                                : solver->MakeIntVar(lb, ub, v.name);
        solver->MutableObjective()->SetCoefficient(vars[i], v.obj);
    }
    if (m.objSense() == ObjSense::Minimize) {
        solver->MutableObjective()->SetMinimization();
    } else {
        solver->MutableObjective()->SetMaximization();
    }

    auto addRow = [&](const Row &r, const std::string &name, double lhs_bound,
                      double rhs_bound) -> MPConstraint * {
        MPConstraint *c = solver->MakeRowConstraint(lhs_bound, rhs_bound, name);
        for (std::size_t i = 0; i < r.vars.size(); ++i)
            c->SetCoefficient(vars[r.vars[i]], r.coeffs[i]);
        return c;
    };
    for (const Row &r : m.rows()) {
        const double lo = r.sense == Sense::LE ? -kInf : r.rhs;
        const double hi = r.sense == Sense::GE ? kInf : r.rhs;
        addRow(r, r.name, lo, hi);
    }
    // Indicator rows have no native MPSolver form: relax to big-M. With
    // trigger_value == true the row must hold when trigger == 1:
    //     sum c*x + M*trigger <= rhs + M       (trigger=1: exact; 0: relaxed)
    //     sum c*x - M*trigger >= rhs - M
    // and with trigger_value == false the trigger term flips sign and the rhs
    // shift disappears (trigger=0: exact; 1: relaxed).
    for (const IndicatorRow &ir : m.indicators()) {
        const double M = bigM(m, ir.implied);
        const Row &r = ir.implied;
        const double slack_coeff = ir.trigger_value ? M : -M;
        const double rhs_shift = ir.trigger_value ? M : 0.0;
        if (r.sense != Sense::GE) {  // LE part of LE/EQ
            MPConstraint *c = addRow(r, ir.name + "_le", -kInf, r.rhs + rhs_shift);
            c->SetCoefficient(vars[ir.trigger], c->GetCoefficient(vars[ir.trigger]) + slack_coeff);
        }
        if (r.sense != Sense::LE) {  // GE part of GE/EQ
            MPConstraint *c = addRow(r, ir.name + "_ge", r.rhs - rhs_shift, kInf);
            c->SetCoefficient(vars[ir.trigger], c->GetCoefficient(vars[ir.trigger]) - slack_coeff);
        }
    }

    solver->SetTimeLimit(absl::Seconds(p.time_limit_s));
    if (p.deterministic) (void)solver->SetNumThreads(1);
    if (warm.size() == vars.size()) {
        std::vector<std::pair<const MPVariable *, double>> hint;
        for (std::size_t i = 0; i < warm.size(); ++i)
            if (!std::isnan(warm[i])) hint.emplace_back(vars[i], warm[i]);
        if (!hint.empty()) solver->SetHint(hint);
    }
    if (!p.dump_path.empty()) std::ofstream(p.dump_path + ".lp") << m.toLpString();

    MPSolverParameters mp;
    mp.SetDoubleParam(MPSolverParameters::RELATIVE_MIP_GAP, p.gap);
    const MPSolver::ResultStatus st = solver->Solve(mp);

    out.solve_time_s = static_cast<double>(solver->wall_time()) / 1000.0;
    switch (st) {
        case MPSolver::OPTIMAL:
        case MPSolver::FEASIBLE: {
            out.values.resize(vars.size());
            for (std::size_t i = 0; i < vars.size(); ++i) out.values[i] = vars[i]->solution_value();
            out.objective = solver->Objective().Value();
            out.bound = solver->Objective().BestBound();
            out.gap = relGap(out.objective, out.bound);
            out.outcome = st == MPSolver::OPTIMAL ? SolveOutcome::Optimal : SolveOutcome::Feasible;
            break;
        }
        case MPSolver::INFEASIBLE:
            out.outcome = SolveOutcome::Infeasible;
            break;
        case MPSolver::NOT_SOLVED:
            out.outcome = SolveOutcome::TimeoutNoSolution;
            break;
        default:
            out.outcome = SolveOutcome::Error;
            break;
    }
    return out;
}

}  // namespace
#endif  // RALLOC_HAVE_ORTOOLS

OrToolsBackend::OrToolsBackend() : impl_(std::make_unique<Impl>()) {}
OrToolsBackend::~OrToolsBackend() = default;

bool OrToolsBackend::available() const {
#if RALLOC_HAVE_ORTOOLS
    return true;
#else
    return false;
#endif
}

void OrToolsBackend::setWarmStart(const std::vector<double> &seed) { impl_->warm = seed; }

Solution OrToolsBackend::solve(const LinearModel &m, const SolverParams &p) {
#if RALLOC_HAVE_ORTOOLS
    return isCpSatEligible(m) ? runCpSat(m, p, impl_->warm) : runMpSolver(m, p, impl_->warm);
#else
    (void)m;
    (void)p;
    Solution s;
    s.outcome = SolveOutcome::Error;
    return s;
#endif
}

std::unique_ptr<SolverBackend> makeSolver(bool prefer_ortools, std::string dump_dir) {
    if (prefer_ortools) {
        auto b = std::make_unique<OrToolsBackend>();
        if (b->available()) return b;
    }
    return std::make_unique<LpExportBackend>(dump_dir.empty() ? "ralloc_model.lp"
                                                              : dump_dir + "/ralloc_model.lp");
}

}  // namespace ralloc
