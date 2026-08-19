/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * Minimal self-checking test for the M2 MAU model (Doc 03 §6 worked example):
 * two tables with a match dependency, NSTAGE=2; asserts the model has the
 * expected variables and a dependency row. No external test framework needed.
 */
#include <cassert>
#include <iostream>

#include "ralloc/mau_model.h"
#include "ralloc/model_types.h"

using namespace ralloc;

static ModelInputs makeTinyInputs() {
    ModelInputs in;
    in.device = DeviceSpec::tofino1();
    in.device.num_stages = 2;  // shrink for the test

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
    // t2 match-depends on t1  => stage(t2) >= stage(t1) + 1
    in.deps.push_back({/*from*/ 1, /*to*/ 2, /*gap*/ 1, DepKind::Match});
    return in;
}

int main() {
    ModelInputs in = makeTinyInputs();
    MauModelBuilder b(in);
    LinearModel m = b.build();

    // s[t,o,k] for 2 tables x 1 option x 2 stages = 4; y[t,k]=4; useStage=2 => 10 binaries.
    std::cout << "vars=" << m.vars().size() << " rows=" << m.rows().size()
              << " binaries=" << m.numBinary() << "\n";
    assert(m.numBinary() == 10);

    // There must be a dependency row named dep_1_2.
    bool found_dep = false;
    for (const auto &r : m.rows())
        if (r.name == "dep_1_2") found_dep = true;
    assert(found_dep);

    // .lp export is non-empty and mentions the objective.
    std::string lp = m.toLpString();
    assert(lp.find("Minimize") != std::string::npos);
    assert(lp.find("useStage_0") != std::string::npos);

    std::cout << "OK: MAU model structural test passed\n";
    return 0;
}
