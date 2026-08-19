/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * M3 VLIW/action Binary-ILP builder (Doc 03 §5). One tiny model per (stage,gress).
 */
#include "ralloc/vliw_model.h"

#include <algorithm>
#include <string>
#include <unordered_set>

namespace ralloc {

namespace {
const ActionInput *findAction(const ModelInputs &in, Id id) {
    for (const auto &a : in.actions)
        if (a.id == id) return &a;
    return nullptr;
}
bool aluOverlap(const ActionInput &a, const ActionInput &b) {
    std::unordered_set<Id> wa(a.written_containers.begin(), a.written_containers.end());
    for (Id c : b.written_containers)
        if (wa.count(c)) return true;
    return false;
}
bool identical(const ActionInput &a, Id other) {
    return std::find(a.identical_actions.begin(), a.identical_actions.end(), other) !=
           a.identical_actions.end();
}
inline long long key3(Id a, int r, int col) {
    return (static_cast<long long>(a) << 20) ^ (r << 4) ^ col;
}
}  // namespace

std::vector<VliwSubproblem> VliwModelBuilder::partition(const MauResult &mau) const {
    // Group actions by (stage, gress) according to where their tables landed.
    std::unordered_map<long long, VliwSubproblem> by;
    for (const auto &ta : mau.tables) {
        // find table -> actions, gress
        const TableInput *t = nullptr;
        for (const auto &ti : in_.tables)
            if (ti.id == ta.table_id) t = &ti;
        if (!t) continue;
        for (int k : ta.stage_tables) {
            long long key = (static_cast<long long>(k) << 4) ^ static_cast<int>(t->gress);
            auto &sub = by[key];
            sub.stage = k;
            sub.gress = t->gress;
            sub.table_ids.push_back(t->id);
            for (Id a : t->action_ids) sub.action_ids.push_back(a);
        }
    }
    std::vector<VliwSubproblem> out;
    out.reserve(by.size());
    for (auto &kv : by) out.push_back(std::move(kv.second));
    return out;
}

VarRef VliwModelBuilder::rcol(Id a, int r, int col) const { return 0; /* index map in full impl */ }
VarRef VliwModelBuilder::slot(Id f, int b) const { return 0; }

LinearModel VliwModelBuilder::build(const VliwSubproblem &sub) {
    LinearModel m("M3-VLIW_s" + std::to_string(sub.stage));
    m.setObjSense(ObjSense::Minimize);
    addRowColoring(m, sub);
    addActionData(m, sub);
    addStatefulCaps(m, sub);
    return m;
}

// (25) one placement; (26) one action per (row,color); (27) ALU-overlap actions
// cannot share a row.
void VliwModelBuilder::addRowColoring(LinearModel &m, const VliwSubproblem &sub) {
    const int ROWS = in_.device.imem_rows_per_gress;
    const int COLS = in_.device.imem_colors;
    std::unordered_map<long long, VarRef> rc;
    for (Id a : sub.action_ids)
        for (int r = 0; r < ROWS; ++r)
            for (int col = 0; col < COLS; ++col)
                rc[key3(a, r, col)] = m.addBinary("rc_" + std::to_string(a) + "_" +
                                                  std::to_string(r) + "_" + std::to_string(col));
    // (25)
    for (Id a : sub.action_ids) {
        std::vector<VarRef> v;
        for (int r = 0; r < ROWS; ++r)
            for (int col = 0; col < COLS; ++col) v.push_back(rc[key3(a, r, col)]);
        m.addLinear("one_" + std::to_string(a), v, std::vector<double>(v.size(), 1.0), Sense::EQ,
                    1.0);
    }
    // (26)
    for (int r = 0; r < ROWS; ++r)
        for (int col = 0; col < COLS; ++col) {
            std::vector<VarRef> v;
            for (Id a : sub.action_ids) v.push_back(rc[key3(a, r, col)]);
            m.addLinear("cell_" + std::to_string(r) + "_" + std::to_string(col), v,
                        std::vector<double>(v.size(), 1.0), Sense::LE, 1.0);
        }
    // (27) overlapping & non-identical actions cannot share a row (any colors).
    for (std::size_t i = 0; i < sub.action_ids.size(); ++i)
        for (std::size_t j = i + 1; j < sub.action_ids.size(); ++j) {
            const ActionInput *a = findAction(in_, sub.action_ids[i]);
            const ActionInput *b = findAction(in_, sub.action_ids[j]);
            if (!a || !b || !aluOverlap(*a, *b) || identical(*a, b->id)) continue;
            for (int r = 0; r < ROWS; ++r) {
                std::vector<VarRef> v;
                for (int col = 0; col < COLS; ++col) {
                    v.push_back(rc[key3(a->id, r, col)]);
                    v.push_back(rc[key3(b->id, r, col)]);
                }
                m.addLinear("row_" + std::to_string(a->id) + "_" + std::to_string(b->id) + "_" +
                                std::to_string(r),
                            v, std::vector<double>(v.size(), 1.0), Sense::LE, 1.0);
            }
        }
}

// (28)-(30) action-data bus byte packing.
void VliwModelBuilder::addActionData(LinearModel & /*m*/, const VliwSubproblem & /*sub*/) {}

// (V7) per-stage stateful caps.
void VliwModelBuilder::addStatefulCaps(LinearModel & /*m*/, const VliwSubproblem & /*sub*/) {}

void VliwModelBuilder::readBack(const VliwSubproblem &sub, const std::vector<double> &val,
                                VliwResult *out) const {
    const int ROWS = in_.device.imem_rows_per_gress;
    const int COLS = in_.device.imem_colors;
    (void)ROWS;
    (void)COLS;
    (void)val;
    // Decode rcol -> ActionAssignment (omitted: needs the index map kept in build()).
    for (Id a : sub.action_ids) out->actions.push_back({a, /*row*/ 0, /*color*/ 0});
}

std::optional<StageNoGood> VliwModelBuilder::noGood(const VliwSubproblem &sub) const {
    StageNoGood ng;
    ng.stage = sub.stage;
    ng.tables = sub.table_ids;
    return ng;
}

}  // namespace ralloc
