/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * SolverBackend implementations (Doc 05). The SCIP path is compiled only when
 * RALLOC_HAVE_SCIP=1 (CMake find_package(SCIP)). Otherwise ScipBackend reports
 * unavailable and the facade forces legacy fallback (Doc 06 §5).
 */
#include "ralloc/scip_solver.h"

#include <cmath>
#include <fstream>

#if RALLOC_HAVE_SCIP
#include <scip/scip.h>
#include <scip/scipdefplugins.h>
#endif

namespace ralloc {

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
// ScipBackend
// ---------------------------------------------------------------------------
struct ScipBackend::Impl {
    std::vector<double> warm;
#if RALLOC_HAVE_SCIP
    // Translate a LinearModel into a SCIP problem and solve.
    Solution run(const LinearModel &m, const SolverParams &p) {
        SCIP *scip = nullptr;
        SCIPcreate(&scip);
        SCIPincludeDefaultPlugins(scip);
        SCIPcreateProbBasic(scip, m.name().c_str());
        SCIPsetObjsense(scip, m.objSense() == ObjSense::Minimize ? SCIP_OBJSENSE_MINIMIZE
                                                                 : SCIP_OBJSENSE_MAXIMIZE);
        // variables
        std::vector<SCIP_VAR *> vars(m.vars().size(), nullptr);
        for (std::size_t i = 0; i < m.vars().size(); ++i) {
            const Var &v = m.vars()[i];
            SCIP_VARTYPE vt = v.type == VarType::Binary       ? SCIP_VARTYPE_BINARY
                              : v.type == VarType::Integer     ? SCIP_VARTYPE_INTEGER
                                                               : SCIP_VARTYPE_CONTINUOUS;
            SCIPcreateVarBasic(scip, &vars[i], v.name.c_str(), v.lb, v.ub, v.obj, vt);
            SCIPaddVar(scip, vars[i]);
        }
        // linear rows
        for (const Row &r : m.rows()) {
            double lhs = -SCIPinfinity(scip), rhs = SCIPinfinity(scip);
            if (r.sense == Sense::LE) rhs = r.rhs;
            else if (r.sense == Sense::GE) lhs = r.rhs;
            else lhs = rhs = r.rhs;
            SCIP_CONS *cons = nullptr;
            SCIPcreateConsBasicLinear(scip, &cons, r.name.c_str(), 0, nullptr, nullptr, lhs, rhs);
            for (std::size_t i = 0; i < r.vars.size(); ++i)
                SCIPaddCoefLinear(scip, cons, vars[r.vars[i]], r.coeffs[i]);
            SCIPaddCons(scip, cons);
            SCIPreleaseCons(scip, &cons);
        }
        // indicator rows
        for (const IndicatorRow &ir : m.indicators()) {
            std::vector<SCIP_VAR *> rv;
            std::vector<double> rc;
            for (std::size_t i = 0; i < ir.implied.vars.size(); ++i) {
                rv.push_back(vars[ir.implied.vars[i]]);
                rc.push_back(ir.implied.coeffs[i]);
            }
            SCIP_CONS *cons = nullptr;
            SCIPcreateConsBasicIndicator(scip, &cons, ir.name.c_str(), vars[ir.trigger],
                                         static_cast<int>(rv.size()), rv.data(), rc.data(),
                                         ir.implied.rhs);
            SCIPaddCons(scip, cons);
            SCIPreleaseCons(scip, &cons);
        }
        // parameters
        SCIPsetRealParam(scip, "limits/time", p.time_limit_s);
        SCIPsetRealParam(scip, "limits/gap", p.gap);
        if (p.deterministic) {
            SCIPsetIntParam(scip, "randomization/randomseedshift", static_cast<int>(p.seed));
            SCIPsetIntParam(scip, "parallel/maxnthreads", 1);
        }
        if (p.emphasis_feasibility)
            SCIPsetEmphasis(scip, SCIP_PARAMEMPHASIS_FEASIBILITY, TRUE);
        if (!p.dump_path.empty())
            SCIPwriteOrigProblem(scip, (p.dump_path + ".lp").c_str(), "lp", FALSE);

        // warm start
        if (!warm.empty() && warm.size() == vars.size()) {
            SCIP_SOL *sol = nullptr;
            SCIPcreateSol(scip, &sol, nullptr);
            for (std::size_t i = 0; i < vars.size(); ++i)
                if (!std::isnan(warm[i])) SCIPsetSolVal(scip, sol, vars[i], warm[i]);
            SCIP_Bool stored = FALSE;
            SCIPaddSolFree(scip, &sol, &stored);
        }

        SCIPsolve(scip);

        Solution out;
        out.solve_time_s = SCIPgetSolvingTime(scip);
        out.bound = SCIPgetDualbound(scip);
        SCIP_STATUS st = SCIPgetStatus(scip);
        SCIP_SOL *best = SCIPgetBestSol(scip);
        if (best) {
            out.values.resize(vars.size());
            for (std::size_t i = 0; i < vars.size(); ++i)
                out.values[i] = SCIPgetSolVal(scip, best, vars[i]);
            out.objective = SCIPgetSolOrigObj(scip, best);
            out.gap = SCIPgetGap(scip);
            out.outcome = (st == SCIP_STATUS_OPTIMAL) ? SolveOutcome::Optimal
                                                      : SolveOutcome::Feasible;
        } else if (st == SCIP_STATUS_INFEASIBLE) {
            out.outcome = SolveOutcome::Infeasible;
        } else {
            out.outcome = SolveOutcome::TimeoutNoSolution;
        }
        for (auto *v : vars) SCIPreleaseVar(scip, &v);
        SCIPfree(&scip);
        return out;
    }
#endif
};

ScipBackend::ScipBackend() : impl_(std::make_unique<Impl>()) {}
ScipBackend::~ScipBackend() = default;

bool ScipBackend::available() const {
#if RALLOC_HAVE_SCIP
    return true;
#else
    return false;
#endif
}

void ScipBackend::setWarmStart(const std::vector<double> &seed) { impl_->warm = seed; }

Solution ScipBackend::solve(const LinearModel &m, const SolverParams &p) {
#if RALLOC_HAVE_SCIP
    return impl_->run(m, p);
#else
    (void)m;
    (void)p;
    Solution s;
    s.outcome = SolveOutcome::Error;
    return s;
#endif
}

std::unique_ptr<SolverBackend> makeSolver(bool prefer_scip, std::string dump_dir) {
    if (prefer_scip) {
        auto b = std::make_unique<ScipBackend>();
        if (b->available()) return b;
    }
    return std::make_unique<LpExportBackend>(dump_dir.empty() ? "ralloc_model.lp"
                                                              : dump_dir + "/ralloc_model.lp");
}

}  // namespace ralloc
