/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * Round-trip test for the model JSON seam (model_json.h). Builds a populated
 * ModelInputs and ModelResults, serializes to a string, reads them back, and
 * asserts structural equality. No bf-p4c / solver needed.
 */
#include <cassert>
#include <iostream>
#include <sstream>

#include "ralloc/model_json.h"
#include "ralloc/model_types.h"

using namespace ralloc;

static ModelInputs makeInputs() {
    ModelInputs in;
    in.device = DeviceSpec::tofino1();
    in.device.num_stages = 9;

    SliceInput s;
    s.id = 0;
    s.width_bits = 16;
    s.live_lo = 0;
    s.live_hi = 9;
    s.required_offset = -1;
    s.byte_aligned = true;
    s.needs_mau = true;
    s.solitary = false;
    s.no_pack = false;
    s.max_kind_size = PhvSize::B16;
    s.field_id = 7;
    in.slices.push_back(s);

    ContainerInput c;
    c.id = 0;
    c.size = PhvSize::B16;
    c.kind = PhvKind::Normal;
    c.mau_group = 2;
    c.ingress_only = true;
    c.egress_only = false;
    in.containers.push_back(c);

    in.slice_pairs.mutex.push_back({0, 1});
    in.slice_pairs.conflict.push_back({2, 3});
    in.legal_containers.push_back({0, 1, 2});

    TableInput t;
    t.id = 1;
    t.gress = Gress::Egress;
    t.splittable = true;
    t.host_table = -1;
    t.action_ids = {0, 1};
    LayoutOptionInput op;
    op.option_id = 5;
    op.demand[D_SRAMS] = 3;
    op.demand[D_TCAMS] = 1;
    op.demand[D_LOGICAL_IDS] = 1;
    op.parts = 2;
    op.power = 1.25;
    op.key_byte_ids = {4, 5};
    t.options.push_back(op);
    in.tables.push_back(t);

    in.deps.push_back({0, 1, 1, DepKind::Match});
    in.table_mutex.push_back({0, 1});

    ActionInput a;
    a.id = 0;
    a.table_id = 1;
    a.gress = Gress::Egress;
    a.stateful = true;
    a.written_containers = {0, 2};
    a.identical_actions = {1};
    in.actions.push_back(a);

    ActionDataField f;
    f.id = 0;
    f.action_id = 0;
    f.slot_bytes = 4;
    f.format_offset = 8;
    in.action_data.push_back(f);

    in.action_data_bus_bytes = 48;
    return in;
}

static ModelResults makeResults() {
    ModelResults r;
    r.phv.containers_used = 3;
    r.phv.assignments.push_back({0, 1, 8});
    r.mau.stages_used = 4;
    r.mau.total_power = 2.5;
    r.mau.peak_utilization[D_SRAMS] = 7;
    r.mau.tables.push_back({1, 5, 2, 3, {2, 3}});
    r.vliw.actions.push_back({0, 6, 1});
    r.vliw.adata.push_back({0, 12});
    return r;
}

int main() {
    // ModelInputs round trip
    ModelInputs in = makeInputs();
    std::ostringstream os;
    writeModelInputs(in, os);
    std::istringstream is(os.str());
    ModelInputs in2 = readModelInputs(is);

    assert(in2.device.kind == in.device.kind);
    assert(in2.device.num_stages == 9);
    assert(in2.slices.size() == 1);
    assert(in2.slices[0].width_bits == 16);
    assert(in2.slices[0].byte_aligned);
    assert(in2.slices[0].max_kind_size == PhvSize::B16);
    assert(in2.slices[0].field_id == 7);
    assert(in2.containers.size() == 1);
    assert(in2.containers[0].ingress_only && !in2.containers[0].egress_only);
    assert(in2.slice_pairs.mutex.size() == 1 && in2.slice_pairs.mutex[0].second == 1);
    assert(in2.slice_pairs.conflict.size() == 1);
    assert(in2.legal_containers.size() == 1 && in2.legal_containers[0].size() == 3);
    assert(in2.tables.size() == 1);
    assert(in2.tables[0].gress == Gress::Egress && in2.tables[0].splittable);
    assert(in2.tables[0].options.size() == 1);
    assert(in2.tables[0].options[0].option_id == 5);
    assert(in2.tables[0].options[0].demand[D_SRAMS] == 3);
    assert(in2.tables[0].options[0].parts == 2);
    assert(in2.tables[0].options[0].key_byte_ids.size() == 2);
    assert(in2.deps.size() == 1 && in2.deps[0].kind == DepKind::Match);
    assert(in2.table_mutex.size() == 1);
    assert(in2.actions.size() == 1 && in2.actions[0].stateful);
    assert(in2.actions[0].written_containers.size() == 2);
    assert(in2.action_data.size() == 1 && in2.action_data[0].slot_bytes == 4);
    assert(in2.action_data_bus_bytes == 48);

    // ModelResults round trip
    ModelResults r = makeResults();
    std::ostringstream ros;
    writeModelResults(r, ros);
    std::istringstream ris(ros.str());
    ModelResults r2 = readModelResults(ris);

    assert(r2.phv.containers_used == 3);
    assert(r2.phv.assignments.size() == 1 && r2.phv.assignments[0].bit_offset == 8);
    assert(r2.mau.stages_used == 4);
    assert(r2.mau.peak_utilization[D_SRAMS] == 7);
    assert(r2.mau.tables.size() == 1 && r2.mau.tables[0].stage_tables.size() == 2);
    assert(r2.vliw.actions.size() == 1 && r2.vliw.actions[0].imem_row == 6);
    assert(r2.vliw.adata.size() == 1 && r2.vliw.adata[0].bus_byte == 12);

    // ResumeBundle (ir_middle.json) round trip
    ResumeBundle b;
    b.tables.push_back({1, "ingress.t_one", {5, 6}});
    b.tables.push_back({2, "egress.t_two", {7}});
    b.actions.push_back({0, 1, "ingress.t_one", "ingress.set_x"});
    std::ostringstream bos;
    writeResumeBundle(b, bos);
    std::istringstream bis(bos.str());
    ResumeBundle b2 = readResumeBundle(bis);
    assert(b2.tables.size() == 2);
    assert(b2.tables[0].id == 1 && b2.tables[0].name == "ingress.t_one");
    assert(b2.tables[0].option_ids.size() == 2 && b2.tables[0].option_ids[1] == 6);
    assert(b2.tables[1].name == "egress.t_two");
    assert(b2.actions.size() == 1 && b2.actions[0].action_name == "ingress.set_x");
    assert(b2.actions[0].table_name == "ingress.t_one" && b2.actions[0].table_id == 1);

    std::cout << "test_model_json: OK\n";
    return 0;
}
