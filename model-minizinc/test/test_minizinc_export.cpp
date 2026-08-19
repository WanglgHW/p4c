/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * Tests the MiniZinc / OR-Tools CP-SAT backend seam.
 *
 * The structural half always runs (no solver needed): it builds the Doc 03 §6
 * worked-example MAU model and asserts LinearModel::toMiniZincString() emits a
 * well-formed `.mzn` (variable declarations, an objective, constraints, and the
 * parseable `v<i>=` output block). The live half only runs when a `minizinc`
 * binary is on $PATH (MiniZincBackend::available()); it solves a tiny model and
 * checks the outcome + parsed values, so CI without MiniZinc still passes.
 */
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "ralloc/mau_model.h"
#include "ralloc/minizinc_solver.h"
#include "ralloc/model_types.h"

using namespace ralloc;

static ModelInputs makeTinyInputs() {
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

static void testStructural() {
    ModelInputs in = makeTinyInputs();
    MauModelBuilder b(in);
    LinearModel m = b.build();

    std::string mzn = m.toMiniZincString();

    // one `var 0..1: v<i>;` per variable
    std::size_t decls = 0;
    for (std::size_t pos = mzn.find("var 0..1: v"); pos != std::string::npos;
         pos = mzn.find("var 0..1: v", pos + 1))
        ++decls;
    assert(decls == m.numBinary());

    // objective + output block + a real constraint are all present
    assert(mzn.find("solve minimize") != std::string::npos);
    assert(mzn.find("output [") != std::string::npos);
    assert(mzn.find("show(v0)") != std::string::npos);
    assert(mzn.find("constraint") != std::string::npos);
    // the match dependency shows up as a labelled constraint comment
    assert(mzn.find("dep_1_2") != std::string::npos);

    std::cout << "OK: MiniZinc structural export test passed (" << decls << " vars)\n";
}

static void testLiveSolve() {
    MiniZincBackend be;
    if (!be.available()) {
        std::cout << "SKIP: minizinc not found on PATH — live solve skipped\n";
        return;
    }

    // minimize v0 + 100*v1  s.t.  v0 + v1 >= 1  =>  v0=1, v1=0, obj=1.
    LinearModel m("live");
    VarRef a = m.addBinary("a", 1.0);
    VarRef c = m.addBinary("b", 100.0);
    m.addLinear("cover", {a, c}, {1.0, 1.0}, Sense::GE, 1.0);
    m.setObjSense(ObjSense::Minimize);

    SolverParams p;
    p.time_limit_s = 10.0;
    Solution s = be.solve(m, p);

    assert(s.outcome == SolveOutcome::Optimal || s.outcome == SolveOutcome::Feasible);
    assert(s.values.size() == 2);
    assert(std::fabs(s.values[a] - 1.0) < 1e-6);
    assert(std::fabs(s.values[c] - 0.0) < 1e-6);
    assert(std::fabs(s.objective - 1.0) < 1e-6);

    std::cout << "OK: MiniZinc live solve test passed (obj=" << s.objective << ")\n";
}

int main() {
    testStructural();
    testLiveSolve();
    return 0;
}
