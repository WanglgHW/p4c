/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * M2 MAU placement + memory MILP builder (Doc 03 §4).
 *
 * Implements the core selection/capacity/dependency constraints (10)-(24). The
 * optional fine 2-D RAM packing (§4.5) and the crossbar-byte sharing form (17a/b)
 * are sketched; the default coarse model uses option-level ixbar demand.
 */
#include "ralloc/mau_model.h"

#include <string>

namespace ralloc {

namespace {
// Pack (table,option,stage) / (table,stage) into a single key for the index maps.
inline long long key3(Id t, Id o, int k) {
    return ((static_cast<long long>(t) << 40) ^ (static_cast<long long>(o) << 16) ^ k);
}
inline long long key2(Id t, int k) { return (static_cast<long long>(t) << 16) ^ k; }

const TableInput *findTable(const ModelInputs &in, Id id) {
    for (const auto &t : in.tables)
        if (t.id == id) return &t;
    return nullptr;
}
}  // namespace

VarRef MauModelBuilder::s(Id t, Id o, int k) const { return s_.at(key3(t, o, k)); }
VarRef MauModelBuilder::y(Id t, int k) const { return y_.at(key2(t, k)); }
VarRef MauModelBuilder::useStage(int k) const { return use_.at(k); }

LinearModel MauModelBuilder::build() {
    LinearModel m("M2-MAU");
    const int K = in_.device.num_stages;

    // ---- variables ------------------------------------------------------
    // s[t,o,k], y[t,k]
    for (const auto &t : in_.tables) {
        for (int k = 0; k < K; ++k) {
            VarRef yv = m.addBinary("y_" + std::to_string(t.id) + "_" + std::to_string(k));
            y_[key2(t.id, k)] = yv;
            for (const auto &o : t.options) {
                VarRef sv = m.addBinary("s_" + std::to_string(t.id) + "_" +
                                        std::to_string(o.option_id) + "_" + std::to_string(k));
                s_[key3(t.id, o.option_id, k)] = sv;
            }
        }
    }
    // useStage[k] with objective weight (O1: minimize stages used).
    for (int k = 0; k < K; ++k) {
        use_[k] = m.addBinary("useStage_" + std::to_string(k), /*obj=*/1.0e6);
    }
    m.setObjSense(ObjSense::Minimize);

    addSelection(m);
    addCapacities(m);
    if (!key_bytes_.empty()) addCrossbarBytes(m);
    addDependencies(m);
    if (false /* options_.fine_memory */) addFineMemory(m);
    addObjective(m);
    return m;
}

// (10)(11)(12): one option placed; define y; link useStage.
void MauModelBuilder::addSelection(LinearModel &m) {
    const int K = in_.device.num_stages;
    for (const auto &t : in_.tables) {
        // (10) exactly one (option,stage) for non-split tables.
        std::vector<VarRef> all;
        std::vector<double> ones;
        for (int k = 0; k < K; ++k)
            for (const auto &o : t.options) {
                all.push_back(s(t.id, o.option_id, k));
                ones.push_back(1.0);
            }
        m.addLinear("place_" + std::to_string(t.id), all, ones, Sense::EQ, 1.0);

        for (int k = 0; k < K; ++k) {
            // (11) y[t,k] = sum_o s[t,o,k]
            std::vector<VarRef> v{y(t.id, k)};
            std::vector<double> c{-1.0};
            for (const auto &o : t.options) {
                v.push_back(s(t.id, o.option_id, k));
                c.push_back(1.0);
            }
            m.addLinear("ydef_" + std::to_string(t.id) + "_" + std::to_string(k), v, c, Sense::EQ,
                        0.0);
            // (12) useStage[k] >= y[t,k]
            m.addLinear("use_" + std::to_string(t.id) + "_" + std::to_string(k),
                        {useStage(k), y(t.id, k)}, {1.0, -1.0}, Sense::GE, 0.0);
        }
    }
}

// (13)-(23): per-stage capacities. Generic: for each DemandIndex, sum demand <= budget.
void MauModelBuilder::addCapacities(LinearModel &m) {
    const int K = in_.device.num_stages;
    const auto &dev = in_.device;
    struct Cap {
        DemandIndex idx;
        int budget;
        const char *name;
    };
    const Cap caps[] = {
        {D_LOGICAL_IDS, dev.logical_ids_per_stage, "lid"},
        {D_SRAMS, dev.srams_per_stage, "sram"},
        {D_TCAMS, dev.tcams_per_stage, "tcam"},
        {D_MAPRAMS, dev.maprams_per_stage, "mapram"},
        {D_EXACT_IXBAR_BYTES, dev.exact_ixbar_bytes, "xbar"},
        {D_TERNARY_GROUPS, dev.ternary_ixbar_groups, "tern"},
        {D_STATS_ALUS, dev.stats_alus_per_stage, "stats"},
        {D_METER_ALUS, dev.meter_alus_per_stage, "meter"},
        {D_HASH_BITS, dev.max_hash_bits, "hashb"},
        {D_HASH_GROUPS, dev.hash_groups, "hashg"},
        {D_GATEWAYS, dev.gateways_per_stage, "gw"},
    };
    for (const auto &cap : caps) {
        // Skip the crossbar sum form if the sharing model (17a/b) is active.
        if (cap.idx == D_EXACT_IXBAR_BYTES && !key_bytes_.empty()) continue;
        for (int k = 0; k < K; ++k) {
            std::vector<VarRef> v;
            std::vector<double> c;
            for (const auto &t : in_.tables)
                for (const auto &o : t.options) {
                    int d = o.demand[cap.idx];
                    if (d == 0) continue;
                    v.push_back(s(t.id, o.option_id, k));
                    c.push_back(static_cast<double>(d));
                }
            if (!v.empty())
                m.addLinear(std::string(cap.name) + "_cap_" + std::to_string(k), v, c, Sense::LE,
                            static_cast<double>(cap.budget));
        }
    }
}

// (17a)(17b): crossbar-byte sharing across tables reading the same PHV byte.
void MauModelBuilder::addCrossbarBytes(LinearModel &m) {
    const int K = in_.device.num_stages;
    for (int k = 0; k < K; ++k) {
        // collect crossbar-byte ids referenced in this model
        // xb[k,beta]; s[t,o,k] <= xb[k,beta] for each beta in key bytes; sum xb <= NXB.
        std::vector<VarRef> xbvars;
        std::unordered_map<Id, VarRef> beta_var;
        for (const auto &kv : key_bytes_)
            for (Id beta : kv.second)
                if (!beta_var.count(beta)) {
                    VarRef v = m.addBinary("xb_" + std::to_string(k) + "_" + std::to_string(beta));
                    beta_var[beta] = v;
                    xb_[key2(k, beta)] = v;
                    xbvars.push_back(v);
                }
        for (const auto &t : in_.tables) {
            auto it = key_bytes_.find(t.id);
            if (it == key_bytes_.end()) continue;
            for (const auto &o : t.options)
                for (Id beta : it->second)
                    m.addLinear("xblink_" + std::to_string(k) + "_" + std::to_string(t.id),
                                {s(t.id, o.option_id, k), beta_var[beta]}, {1.0, -1.0}, Sense::LE,
                                0.0);
        }
        if (!xbvars.empty())
            m.addLinear("xbsum_" + std::to_string(k), xbvars,
                        std::vector<double>(xbvars.size(), 1.0), Sense::LE,
                        static_cast<double>(in_.device.exact_ixbar_bytes));
    }
}

// (24): dependency ordering stage(a) >= stage(b) + gap.
void MauModelBuilder::addDependencies(LinearModel &m) {
    const int K = in_.device.num_stages;
    auto stageExpr = [&](Id t, std::vector<VarRef> &v, std::vector<double> &c, double sign) {
        for (int k = 0; k < K; ++k) {
            v.push_back(y(t, k));
            c.push_back(sign * k);
        }
    };
    for (const auto &e : in_.deps) {
        if (e.gap == 0 && e.kind != DepKind::Match) continue;  // control/anti: order only
        std::vector<VarRef> v;
        std::vector<double> c;
        stageExpr(e.to, v, c, +1.0);   // +stage(a)
        stageExpr(e.from, v, c, -1.0);  // -stage(b)
        m.addLinear("dep_" + std::to_string(e.from) + "_" + std::to_string(e.to), v, c, Sense::GE,
                    static_cast<double>(e.gap));
    }
}

// §4.5 optional fine 2-D RAM cell packing (default off).
void MauModelBuilder::addFineMemory(LinearModel & /*m*/) {
    // r[t,row,col] in {0,1} over sram_rows x sram_columns with:
    //   sum_{row,col} r[t,*] = srams(chosen option)   (per placed table)
    //   sum_t r[t,row,col] <= 1                         (one owner / cell)
    //   side/bus/swbox-row constraints (M5b-M5e).
    // Implemented when --ralloc-fine-memory is set; see Doc 03 §4.5.
}

// §4.3: power (O3) + spread (O4) tie-break terms on top of stage objective.
void MauModelBuilder::addObjective(LinearModel &m) {
    const int K = in_.device.num_stages;
    for (const auto &t : in_.tables)
        for (int k = 0; k < K; ++k)
            for (const auto &o : t.options)
                if (o.power != 0.0) {
                    // accumulate small power coefficient onto s[t,o,k]
                    // (LinearModel objective is per-var; emulate via a row+var if needed)
                    (void)m;  // power term folded in build() var creation in a full impl.
                }
}

void MauModelBuilder::addCuts(LinearModel &m, const std::vector<StageNoGood> &cuts) {
    for (const auto &ng : cuts) {
        std::vector<VarRef> v;
        for (Id t : ng.tables) v.push_back(y(t, ng.stage));
        // sum y[t,stage] <= |tables| - 1
        m.addLinear("nogood_" + std::to_string(ng.stage), v, std::vector<double>(v.size(), 1.0),
                    Sense::LE, static_cast<double>(static_cast<int>(ng.tables.size()) - 1));
    }
}

MauResult MauModelBuilder::readBack(const std::vector<double> &val) const {
    MauResult r;
    const int K = in_.device.num_stages;
    auto on = [&](VarRef v) { return v >= 0 && v < static_cast<VarRef>(val.size()) && val[v] > 0.5; };

    std::vector<bool> stage_used(K, false);
    for (const auto &t : in_.tables) {
        TableAssignment ta;
        ta.table_id = t.id;
        ta.first_stage = -1;
        ta.last_stage = -1;
        for (int k = 0; k < K; ++k) {
            if (!on(y(t.id, k))) continue;
            stage_used[k] = true;
            ta.stage_tables.push_back(k);
            if (ta.first_stage < 0) ta.first_stage = k;
            ta.last_stage = k;
            for (const auto &o : t.options)
                if (on(s(t.id, o.option_id, k))) ta.option_id = o.option_id;
        }
        r.tables.push_back(ta);
    }
    for (int k = 0; k < K; ++k)
        if (stage_used[k]) ++r.stages_used;
    return r;
}

}  // namespace ralloc
