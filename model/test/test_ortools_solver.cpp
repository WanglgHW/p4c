/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * Behavioural test for the OR-Tools SolverBackend (Doc 05). Unlike
 * test_mau_model.cpp (structure only) this one actually *solves*:
 *
 *   1. the Doc 03 §6 two-table MAU model  -> CP-SAT, proven optimal placement
 *   2. indicator rows, trigger on and off -> native OnlyEnforceIf semantics
 *   3. a pure LP and a mixed indicator LP -> MPSolver path incl. big-M
 *
 * Without OR-Tools linked (RALLOC_HAVE_ORTOOLS=0) the backend must report
 * unavailable and the factory must hand back the .lp exporter; the test asserts
 * that instead of solving, so it stays meaningful in a solver-less CI.
 */
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

#include "ralloc/mau_model.h"
#include "ralloc/model_types.h"
#include "ralloc/ortools_solver.h"

using namespace ralloc;

namespace {

int failures = 0;

/// assert() is compiled out under NDEBUG, so check explicitly.
void check(bool ok, const std::string &what) {
    if (!ok) {
        std::cerr << "FAIL: " << what << "\n";
        ++failures;
    }
}

bool near(double a, double b, double tol = 1e-6) { return std::abs(a - b) <= tol; }

// --- 1. the Doc 03 §6 worked example --------------------------------------
ModelInputs makeTinyInputs() {
    ModelInputs in;
    in.device = DeviceSpec::tofino1();
    in.device.num_stages = 2;

    TableInput t1;
    t1.id = 1;
    t1.gress = Gress::Ingress;
    LayoutOptionInput o1;
    o1.option_id = 10;
    o1.demand[D_SRAMS] = 3;
    o1.demand[D_EXACT_IXBAR_BYTES] = 6;
    o1.demand[D_LOGICAL_IDS] = 1;
    t1.options.push_back(o1);

    TableInput t2;
    t2.id = 2;
    t2.gress = Gress::Ingress;
    LayoutOptionInput o2;
    o2.option_id = 20;
    o2.demand[D_TCAMS] = 2;
    o2.demand[D_TERNARY_GROUPS] = 1;
    o2.demand[D_LOGICAL_IDS] = 1;
    t2.options.push_back(o2);

    in.tables = {t1, t2};
    in.deps.push_back({/*from*/ 1, /*to*/ 2, /*gap*/ 1, DepKind::Match});
    return in;
}

void testMauSolve(SolverBackend *solver) {
    ModelInputs in = makeTinyInputs();
    MauModelBuilder b(in);
    LinearModel m = b.build();
    check(OrToolsBackend::isCpSatEligible(m), "MAU model is CP-SAT eligible");

    SolverParams p;
    p.time_limit_s = 30.0;
    Solution s = solver->solve(m, p);
    check(s.outcome == SolveOutcome::Optimal, "MAU model solved to optimality");
    if (s.outcome != SolveOutcome::Optimal) return;

    MauResult r = b.readBack(s.values);
    check(r.tables.size() == 2, "both tables read back");
    check(r.stages_used == 2, "the match dependency forces both stages to be used");
    for (const TableAssignment &ta : r.tables) {
        check(ta.stage_tables.size() == 1, "table placed in exactly one stage");
        if (ta.table_id == 1) check(ta.first_stage == 0, "t1 in stage 0");
        if (ta.table_id == 2) check(ta.first_stage == 1, "t2 in stage 1 (dep gap 1)");
    }
    // objective is 1e6 per used stage (O1)
    check(near(s.objective, 2.0e6, 1.0), "objective == 2 used stages");
    printf("  MAU: %s, obj=%.0f, bound=%.0f, %.3fs\n",
           s.outcome == SolveOutcome::Optimal ? "optimal" : "suboptimal", s.objective, s.bound,
           s.solve_time_s);
}

// --- 2. indicator rows ----------------------------------------------------
/// minimize 2b - x - y  s.t.  b == `trigger_fixed`, and
/// b == `trigger_value` -> x + y <= 1.
LinearModel indicatorModel(int trigger_fixed, bool trigger_value = true) {
    LinearModel m("indicator");
    VarRef b = m.addBinary("b", /*obj=*/2.0);
    VarRef x = m.addBinary("x", /*obj=*/-1.0);
    VarRef y = m.addBinary("y", /*obj=*/-1.0);
    m.setObjSense(ObjSense::Minimize);
    m.addLinear("fix_b", {b}, {1.0}, Sense::EQ, static_cast<double>(trigger_fixed));
    IndicatorRow ir;
    ir.name = "b_limits_xy";
    ir.trigger = b;
    ir.trigger_value = trigger_value;
    ir.implied = Row{"xy_le_1", {x, y}, {1.0, 1.0}, Sense::LE, 1.0};
    m.addIndicator(std::move(ir));
    return m;
}

/// `enforced` says whether the implied row must bind; obj is 2b - (x+y), so an
/// enforced row gives 2*b - 1 and a relaxed one 2*b - 2.
void checkIndicator(SolverBackend *solver, int fixed, bool trigger_value, bool enforced,
                    const std::string &what) {
    SolverParams p;
    p.time_limit_s = 30.0;
    Solution s = solver->solve(indicatorModel(fixed, trigger_value), p);
    check(s.outcome == SolveOutcome::Optimal, what + ": optimal");
    if (s.outcome != SolveOutcome::Optimal) return;
    const double xy = enforced ? 1.0 : 2.0;
    check(near(s.objective, 2.0 * fixed - xy), what + ": objective");
    check(near(s.values[1] + s.values[2], xy), what + ": x + y");
}

void testIndicators(SolverBackend *solver) {
    checkIndicator(solver, /*fixed=*/1, /*trigger_value=*/true, /*enforced=*/true,
                   "trigger=1 fires on true");
    checkIndicator(solver, /*fixed=*/0, /*trigger_value=*/true, /*enforced=*/false,
                   "trigger=0 relaxes on true");
    checkIndicator(solver, /*fixed=*/0, /*trigger_value=*/false, /*enforced=*/true,
                   "trigger=0 fires on false");
    checkIndicator(solver, /*fixed=*/1, /*trigger_value=*/false, /*enforced=*/false,
                   "trigger=1 relaxes on false");
    printf("  indicators: all four trigger/polarity combinations OK\n");
}

// --- 3. continuous models (MPSolver path) ---------------------------------
/// maximize 3x + 2y  s.t.  x + y <= 4,  x + 3y <= 6,  0 <= x,y <= 10.
LinearModel lpModel() {
    LinearModel m("lp");
    VarRef x = m.addVar("x", VarType::Continuous, 0.0, 10.0, /*obj=*/3.0);
    VarRef y = m.addVar("y", VarType::Continuous, 0.0, 10.0, /*obj=*/2.0);
    m.setObjSense(ObjSense::Maximize);
    m.addLinear("c1", {x, y}, {1.0, 1.0}, Sense::LE, 4.0);
    m.addLinear("c2", {x, y}, {1.0, 3.0}, Sense::LE, 6.0);
    return m;
}

/// The same LP plus a binary trigger fixed to `trigger_fixed` that caps x at 1
/// when it equals `trigger_value` — exercises the big-M relaxation.
LinearModel mixedIndicatorModel(int trigger_fixed, bool trigger_value) {
    LinearModel m = lpModel();
    const VarRef x = 0;  // lpModel() creates x first
    VarRef b = m.addBinary("b");
    m.addLinear("fix_b", {b}, {1.0}, Sense::EQ, static_cast<double>(trigger_fixed));
    IndicatorRow ir;
    ir.name = "b_caps_x";
    ir.trigger = b;
    ir.trigger_value = trigger_value;
    ir.implied = Row{"x_le_1", {x}, {1.0}, Sense::LE, 1.0};
    m.addIndicator(std::move(ir));
    return m;
}

void testContinuous(SolverBackend *solver) {
    SolverParams p;
    p.time_limit_s = 30.0;

    LinearModel lp = lpModel();
    check(!OrToolsBackend::isCpSatEligible(lp), "continuous model is not CP-SAT eligible");
    Solution s = solver->solve(lp, p);
    if (s.outcome == SolveOutcome::Error) {
        // No LP/MIP engine in this OR-Tools build; CP-SAT-only builds are legal.
        printf("  continuous: no MPSolver engine in this OR-Tools build (skipped)\n");
        return;
    }
    check(s.outcome == SolveOutcome::Optimal, "LP solved to optimality");
    check(near(s.objective, 12.0, 1e-4), "LP optimum is 12 (x=4, y=0)");

    // With x <= 1 enforced, y <= min(3, 5/3) => obj = 3 + 10/3; relaxed => 12.
    const double kCapped = 3.0 + 10.0 / 3.0;
    struct Case {
        int fixed;
        bool trigger_value;
        double expect;
        const char *what;
    };
    for (const Case &c : {Case{1, true, kCapped, "big-M fires on true"},
                          Case{0, true, 12.0, "big-M relaxes on true"},
                          Case{0, false, kCapped, "big-M fires on false"},
                          Case{1, false, 12.0, "big-M relaxes on false"}}) {
        Solution mi = solver->solve(mixedIndicatorModel(c.fixed, c.trigger_value), p);
        check(mi.outcome == SolveOutcome::Optimal, std::string(c.what) + ": optimal");
        if (mi.outcome == SolveOutcome::Optimal)
            check(near(mi.objective, c.expect, 1e-4), std::string(c.what) + ": objective");
    }
    printf("  continuous: lp=%.4f, big-M indicator OK in all four combinations\n", s.objective);
}

}  // namespace

int main() {
    OrToolsBackend backend;
#if RALLOC_HAVE_ORTOOLS
    check(backend.available(), "OR-Tools backend available when linked");
    std::cout << "solving with OR-Tools:\n";
    testMauSolve(&backend);
    testIndicators(&backend);
    testContinuous(&backend);
#else
    check(!backend.available(), "OR-Tools backend unavailable when not linked");
    // The factory must degrade to the .lp exporter, never to a broken solver.
    auto fallback = makeSolver(/*prefer_ortools=*/true, "/tmp");
    LinearModel m = indicatorModel(1);
    Solution s = fallback->solve(m, SolverParams{});
    check(s.outcome == SolveOutcome::TimeoutNoSolution, "export-only backend never claims a solve");
    std::cout << "OR-Tools not linked: export-only fallback checked\n";
#endif

    if (failures != 0) {
        std::cerr << failures << " check(s) failed\n";
        return 1;
    }
    std::cout << "OK: OR-Tools solver test passed\n";
    return 0;
}
