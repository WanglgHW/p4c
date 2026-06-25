/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * CompilerBridge: bf-p4c IR <-> model PODs (Doc 04, Doc 06). This is the ONLY
 * model TU that includes bf-p4c headers. Built as `libralloc_bridge` and linked
 * into the tofino backend target.
 *
 * The real ingest (RALLOC_WITH_BFP4C=1) reads:
 *   - M1 PHV   : PhvInfo fields/containers, field mutex/no-pack, PhvSpec
 *   - M2 MAU   : IR::MAU::Table walk + StageUseEstimate demand + DependencyGraph
 *   - M3 VLIW  : IR::MAU::Action write-sets
 * The standalone build (RALLOC_WITH_BFP4C=0) keeps only the JSON-fixture path so
 * the model core stays buildable/testable without the compiler.
 */
#include "ralloc/compiler_bridge.h"

#include "ralloc/model_json.h"

#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <unordered_map>

#if RALLOC_WITH_BFP4C
#include "backends/tofino/bf-p4c/phv/phv_fields.h"        // PhvInfo, PHV::Field
#include "backends/tofino/bf-p4c/phv/allocate_phv.h"      // AllocUtils::bind_slices
#include "backends/tofino/bf-p4c/mau/resource.h"          // TableResourceAlloc
#include "backends/tofino/bf-p4c/mau/resource_estimate.h"  // StageUseEstimate
#include "backends/tofino/bf-p4c/mau/table_layout.h"       // LayoutChoices
#include "backends/tofino/bf-p4c/mau/table_mutex.h"        // TablesMutuallyExclusive
#include "backends/tofino/bf-p4c/mau/table_dependency_graph.h"  // DependencyGraph
#include "backends/tofino/bf-p4c/mau/reduction_or.h"        // ReductionOrInfo
#include "backends/tofino/bf-p4c/phv/alloc_setting.h"       // PHV::AllocSetting
#include "backends/tofino/bf-p4c/phv/fieldslice_live_range.h"  // FieldSliceLiveRangeDB
#include "backends/tofino/bf-p4c/phv/pragma/phv_pragmas.h"  // PHV::Pragmas
#include "backends/tofino/bf-p4c/phv/validate_allocation.h"  // PHV::ValidateAllocation
#include "backends/tofino/bf-p4c/specs/device.h"
#include "ir/ir.h"
#include "lib/error.h"  // P4::errorCount()
#endif

namespace ralloc {

#if RALLOC_WITH_BFP4C
/// Per-table placement decision recorded by writeBack(), applied by the
/// PlacementWriterPass Transform. File-scope so the Transform (a free class) can
/// reference it.
struct TablePlan {
    int stage = -1;
    int logical_id = -1;
    int stage_split = -1;
    Id option_id = 0;
};
#endif

// ---------------------------------------------------------------------------
// id <-> IR-node bookkeeping (needed by write-back; opaque in the header).
// ---------------------------------------------------------------------------
struct CompilerBridge::Maps {
#if RALLOC_WITH_BFP4C
    // M1: slice id -> (field id, lo bit, width). container id == PhvSpec id.
    struct SliceRef {
        const PHV::Field *field;
        int lo;
        int width;
    };
    std::vector<SliceRef> slice_by_id;
    std::vector<PHV::Container> container_by_id;       // model container id -> Container
    std::unordered_map<int, Id> phvSpecId_to_model;    // PhvSpec id -> model container id
    // M2/M3
    std::vector<const IR::MAU::Table *> table_by_id;
    std::unordered_map<const IR::MAU::Table *, Id> table_to_id;
    std::vector<const IR::MAU::Action *> action_by_id;
    std::map<std::pair<Id, Id>, Id> option_by_table;   // (table,optIdx) -> option id

    // Placement plan recorded by writeBack(), applied by placementWriter().
    std::map<cstring, TablePlan> plan;                 // keyed by table name
    // per action: (imem row, color), keyed by action node.
    std::map<const IR::MAU::Action *, std::pair<int, int>> imem;
#endif
};

CompilerBridge::CompilerBridge(CompilerContext ctx) : ctx_(ctx), maps_(new Maps) {}
CompilerBridge::~CompilerBridge() { delete maps_; }

#if RALLOC_WITH_BFP4C
namespace {

inline Gress toGress(gress_t g) {
    switch (g) {
        case INGRESS: return Gress::Ingress;
        case EGRESS: return Gress::Egress;
        default: return Gress::Ghost;  // GHOST
    }
}

inline PhvSize toPhvSize(PHV::Size s) {
    switch (s) {
        case PHV::Size::b8: return PhvSize::B8;
        case PHV::Size::b16: return PhvSize::B16;
        default: return PhvSize::B32;
    }
}
inline PhvKind toPhvKind(PHV::Kind k) {
    switch (k) {
        case PHV::Kind::tagalong: return PhvKind::Tagalong;
        case PHV::Kind::mocha: return PhvKind::Mocha;
        case PHV::Kind::dark: return PhvKind::Dark;
        default: return PhvKind::Normal;
    }
}

/// Walk a Pipe collecting all match/action tables in visitation order.
struct CollectTables : public Inspector {
    std::vector<const IR::MAU::Table *> tables;
    bool preorder(const IR::MAU::Table *t) override {
        tables.push_back(t);
        return true;
    }
};

/// Collect the destination field-ids written by an action (proxy for Wr(a),
/// Doc 04 §4; refined to containers post-PHV).
struct CollectWrites : public Inspector {
    const PhvInfo &phv;
    std::vector<int> dests;
    explicit CollectWrites(const PhvInfo &p) : phv(p) {}
    bool preorder(const IR::MAU::Instruction *inst) override {
        if (auto *out = inst->getOutput()) {
            le_bitrange bits;
            if (const PHV::Field *f = phv.field(out, &bits)) dests.push_back(f->id);
        }
        return true;
    }
};

/// Container-kind legality for a field (P2/P7/P10), without PhvUse: a mocha/dark
/// candidate may also use the lower-restriction kinds; everything excludes
/// tagalong (modeled scope = normal/mocha/dark, Doc 01 §2.1).
bool kindLegal(const PHV::Field *f, PHV::Kind ck) {
    if (ck == PHV::Kind::tagalong) return false;
    if (ck == PHV::Kind::normal) return true;
    if (ck == PHV::Kind::mocha) return f->is_mocha_candidate() || f->is_dark_candidate();
    if (ck == PHV::Kind::dark) return f->is_dark_candidate();
    return true;
}

}  // namespace
#endif  // RALLOC_WITH_BFP4C

ModelInputs CompilerBridge::ingest() {
    ModelInputs in;
#if RALLOC_WITH_BFP4C
    BUG_CHECK(ctx_.phv && ctx_.pipe, "CompilerBridge: PhvInfo/Pipe required");
    const PhvInfo &phv = *ctx_.phv;
    const PhvSpec &spec = Device::phvSpec();

    // ----- device -------------------------------------------------------
    in.device = DeviceSpec::fromName(Device::name().c_str());
    in.device.num_stages = Device::numStages();

    // ----- M1: containers ----------------------------------------------
    for (int cid : spec.physicalContainers()) {
        PHV::Container c = spec.idToContainer(cid);
        ContainerInput ci;
        ci.id = static_cast<Id>(in.containers.size());
        ci.size = toPhvSize(c.type().size());
        ci.kind = toPhvKind(c.type().kind());
        ci.mau_group = static_cast<int>(spec.mauGroupId(c));
        ci.ingress_only = spec.ingressOnly().getbit(cid);
        ci.egress_only = spec.egressOnly().getbit(cid);
        maps_->phvSpecId_to_model[cid] = ci.id;
        maps_->container_by_id.push_back(c);
        in.containers.push_back(ci);
    }

    // ----- M1: field slices + legal containers --------------------------
    // One representative slice id per field is recorded for mutex/no-pack pairs.
    std::unordered_map<int, Id> field_first_slice;
    for (const PHV::Field &field : phv) {
        const PHV::Field *f = &field;
        if (!f || f->is_ignore_alloc()) continue;
        int W = f->size;
        if (W <= 0) continue;
        // Chunk wide fields into <=32-bit slices aligned to container sizes
        // (a conservative stand-in for SuperCluster slicing, Doc 04 §2).
        int lo = 0;
        bool first = true;
        while (lo < W) {
            int rem = W - lo;
            int sw = rem >= 32 ? 32 : rem >= 16 ? 16 : rem >= 8 ? 8 : rem;
            SliceInput s;
            s.id = static_cast<Id>(in.slices.size());
            s.width_bits = sw;
            s.live_lo = 0;
            s.live_hi = in.device.num_stages;  // conservative; overlay via mutex
            s.required_offset = -1;
            s.byte_aligned = f->exact_containers() || f->deparsed_bottom_bits();
            s.needs_mau = true;  // tagalong excluded in kindLegal anyway
            s.solitary = f->is_solitary();
            s.no_pack = f->is_solitary();
            s.field_id = f->id;
            if (first) {
                field_first_slice[f->id] = s.id;
                first = false;
            }
            // legal containers for this slice
            std::vector<Id> legal;
            for (const auto &ci : in.containers) {
                if (static_cast<int>(ci.size) < sw) continue;
                if (ci.ingress_only && f->gress != INGRESS) continue;
                if (ci.egress_only && f->gress != EGRESS) continue;
                PHV::Container c = maps_->container_by_id[ci.id];
                if (!kindLegal(f, c.type().kind())) continue;
                legal.push_back(ci.id);
            }
            maps_->slice_by_id.push_back({f, lo, sw});
            in.slices.push_back(s);
            in.legal_containers.push_back(std::move(legal));
            lo += sw;
        }
    }

    // ----- M1: mutex (overlay) + no-pack (conflict) pairs ---------------
    // Representative-slice level (whole-field relations); Doc 04 §2.
    for (const PHV::Field &f1ref : phv) {
        const PHV::Field *f1 = &f1ref;
        if (!field_first_slice.count(f1->id)) continue;
        for (const PHV::Field &f2ref : phv) {
            const PHV::Field *f2 = &f2ref;
            if (f2->id <= f1->id || !field_first_slice.count(f2->id)) continue;
            Id s1 = field_first_slice[f1->id], s2 = field_first_slice[f2->id];
            if (phv.isFieldMutex(f1, f2)) in.slice_pairs.mutex.push_back({s1, s2});
            if (phv.isFieldNoPack(f1, f2)) in.slice_pairs.conflict.push_back({s1, s2});
        }
    }

    // ----- M2: tables + layout-option demand ----------------------------
    CollectTables ct;
    ctx_.pipe->apply(ct);
    for (const IR::MAU::Table *t : ct.tables) {
        TableInput ti;
        ti.id = static_cast<Id>(in.tables.size());
        ti.gress = toGress(t->gress);
        maps_->table_to_id[t] = ti.id;
        maps_->table_by_id.push_back(t);

        // actions
        for (const auto &kv : t->actions) {
            Id aid = static_cast<Id>(in.actions.size());
            ti.action_ids.push_back(aid);
            ActionInput ai;
            ai.id = aid;
            ai.table_id = ti.id;
            ai.gress = ti.gress;
            ai.stateful = !kv.second->stateful_calls.empty();
            CollectWrites cw(phv);
            kv.second->apply(cw);
            for (int fid : cw.dests) ai.written_containers.push_back(fid);
            maps_->action_by_id.push_back(kv.second);
            in.actions.push_back(ai);
        }

        // demand vector from StageUseEstimate (the compiler's own estimator).
        LayoutOptionInput opt;
        opt.option_id = 0;
        opt.parts = 1;
        if (ctx_.layout) {
            int entries = t->layout.entries > 0 ? t->layout.entries
                                                : (t->match_key.empty() ? 1 : 512);
            attached_entries_t att;
            StageUseEstimate est(t, entries, att,
                                 const_cast<LayoutChoices *>(ctx_.layout),
                                 /*prev_placed*/ false, /*gateway_attached*/ false,
                                 /*disable_split*/ true, *ctx_.phv);
            opt.demand[D_LOGICAL_IDS] = est.logical_ids > 0 ? est.logical_ids : 1;
            opt.demand[D_SRAMS] = est.srams;
            opt.demand[D_TCAMS] = est.tcams;
            opt.demand[D_MAPRAMS] = est.maprams;
            opt.demand[D_EXACT_IXBAR_BYTES] = est.exact_ixbar_bytes;
            opt.demand[D_TERNARY_GROUPS] = est.ternary_ixbar_groups;
            opt.demand[D_STATS_ALUS] = est.stats_alus;
            opt.demand[D_METER_ALUS] = est.meter_alus;
            opt.parts = est.stages_required() > 0 ? est.stages_required() : 1;
        } else {
            opt.demand[D_LOGICAL_IDS] = 1;
        }
        ti.splittable = opt.parts > 1;
        maps_->option_by_table[{ti.id, 0}] = opt.option_id;
        ti.options.push_back(opt);
        in.tables.push_back(ti);
    }

    // ----- M2: dependency edges (data deps force a later stage) ----------
    if (ctx_.deps) {
        for (const auto &kv : ctx_.deps->happens_phys_before_map) {
            auto it = maps_->table_to_id.find(kv.first);
            if (it == maps_->table_to_id.end()) continue;
            Id from = it->second;  // producer (earlier)
            for (const IR::MAU::Table *later : kv.second) {
                auto jt = maps_->table_to_id.find(later);
                if (jt == maps_->table_to_id.end()) continue;
                in.deps.push_back({from, jt->second, /*gap*/ 1, DepKind::Match});
            }
        }
    }

    // ----- M2: table mutual exclusion -----------------------------------
    if (ctx_.mutex) {
        const auto &tbls = maps_->table_by_id;
        for (size_t i = 0; i < tbls.size(); ++i)
            for (size_t j = i + 1; j < tbls.size(); ++j)
                if ((*ctx_.mutex)(tbls[i], tbls[j]))
                    in.table_mutex.push_back({static_cast<Id>(i), static_cast<Id>(j)});
    }
#else
    (void)ctx_;
#endif
    return in;
}

ValidationReport CompilerBridge::validate(const ModelInputs &in) const {
    ValidationReport rep;
    auto fail = [&](std::string msg) {
        rep.ok = false;
        rep.errors.push_back(std::move(msg));
    };
    for (std::size_t i = 0; i < in.slices.size(); ++i)
        if (i >= in.legal_containers.size() || in.legal_containers[i].empty())
            fail("slice " + std::to_string(in.slices[i].id) + " has no legal container");
    for (const auto &t : in.tables)
        if (t.options.empty()) fail("table " + std::to_string(t.id) + " has no layout option");
    // Necessary-feasibility: per resource, min total demand <= stages * budget.
    if (!in.tables.empty()) {
        long sram = 0, tcam = 0;
        for (const auto &t : in.tables) {
            sram += t.options.front().demand[D_SRAMS];
            tcam += t.options.front().demand[D_TCAMS];
        }
        long cap = static_cast<long>(in.device.num_stages);
        if (sram > cap * in.device.srams_per_stage) fail("aggregate SRAM demand exceeds pipe");
        if (tcam > cap * in.device.tcams_per_stage) fail("aggregate TCAM demand exceeds pipe");
    }
    return rep;
}

bool CompilerBridge::writeBack(const ModelResults &res) {
#if RALLOC_WITH_BFP4C
    BUG_CHECK(ctx_.phv, "writeBack requires PhvInfo");
    PhvInfo &phv = *ctx_.phv;

    // ===== PHV: attach a PHV::AllocSlice per assignment to its Field ======
    // Clear any prior allocation on touched fields exactly once, then append.
    std::set<int> touched;
    for (const PhvAssignment &a : res.phv.assignments) {
        if (a.slice_id < 0 || a.slice_id >= static_cast<Id>(maps_->slice_by_id.size())) continue;
        const PHV::Field *cf = maps_->slice_by_id[a.slice_id].field;
        if (touched.insert(cf->id).second)
            if (PHV::Field *mf = phv.field(cf->id)) mf->clear_alloc();
    }
    // Conservative whole-pipe liveness; finalize_physical_liverange refines later.
    const PHV::StageAndAccess live_lo{-1, PHV::FieldUse(PHV::FieldUse::WRITE)};
    const PHV::StageAndAccess live_hi{Device::numStages(), PHV::FieldUse(PHV::FieldUse::READ)};
    for (const PhvAssignment &a : res.phv.assignments) {
        if (a.slice_id < 0 || a.slice_id >= static_cast<Id>(maps_->slice_by_id.size())) continue;
        if (a.container_id < 0 || a.container_id >= static_cast<Id>(maps_->container_by_id.size()))
            continue;
        const auto &ref = maps_->slice_by_id[a.slice_id];
        PHV::Field *mf = phv.field(ref.field->id);
        if (!mf) continue;
        PHV::Container c = maps_->container_by_id[a.container_id];
        PHV::AllocSlice slice(mf, c, ref.lo, a.bit_offset, ref.width);
        slice.setLiveness(live_lo, live_hi);
        mf->add_alloc(slice);
    }
    for (int fid : touched)
        if (PHV::Field *mf = phv.field(fid)) mf->sort_alloc();

    // ===== MAU/VLIW: record the plan (applied by placementWriter) =========
    maps_->plan.clear();
    maps_->imem.clear();
    std::map<int, int> next_lid;  // stage -> next free logical id (T2 §8 post-assign)
    for (const TableAssignment &ta : res.mau.tables) {
        if (ta.table_id < 0 || ta.table_id >= static_cast<Id>(maps_->table_by_id.size())) continue;
        const IR::MAU::Table *t = maps_->table_by_id[ta.table_id];
        TablePlan tp;
        tp.stage = ta.first_stage;
        tp.logical_id = next_lid[ta.first_stage]++;
        tp.stage_split = (ta.last_stage > ta.first_stage) ? 0 : -1;
        tp.option_id = ta.option_id;
        maps_->plan[t->name] = tp;
    }
    for (const ActionAssignment &aa : res.vliw.actions) {
        if (aa.action_id < 0 || aa.action_id >= static_cast<Id>(maps_->action_by_id.size()))
            continue;
        maps_->imem[maps_->action_by_id[aa.action_id]] = {aa.imem_row, aa.imem_color};
    }
    return selfCheck();
#else
    (void)res;
    return false;
#endif
}

#if RALLOC_WITH_BFP4C
namespace {
/// Stamps the recorded placement plan onto IR::MAU::Table nodes, mirroring
/// TransformTables in mau/table_placement.cpp (sets stage_/logical_id/
/// stage_split/resources). The chosen LayoutOption is attached so the
/// constrained legacy Memories/IXBar passes can fill memuse afterward.
class PlacementWriterPass : public Transform {
    const std::map<cstring, TablePlan> &plan;
    LayoutChoices *layout;

 public:
    PlacementWriterPass(const std::map<cstring, TablePlan> &p, LayoutChoices *lc)
        : plan(p), layout(lc) {}

    IR::Node *preorder(IR::MAU::Table *tbl) override {
        auto it = plan.find(tbl->name);
        if (it == plan.end()) return tbl;
        const auto &tp = it->second;
        tbl->stage_ = tp.stage;
        tbl->set_global_id(tp.stage * StageUse::MAX_LOGICAL_IDS + tp.logical_id);
        tbl->stage_split = tp.stage_split;
        if (layout) {
            const auto &opts = layout->get_layout_options(tbl);
            if (!opts.empty()) {
                size_t idx = std::min<size_t>(tp.option_id, opts.size() - 1);
                auto *r = new TableResourceAlloc();
                r->layout_option = opts[idx];  // copy chosen option
                tbl->resources = r;            // memuse filled by constrained Memories pass
            }
        }
        return tbl;
    }
};
}  // namespace
#endif  // RALLOC_WITH_BFP4C

P4::Transform *CompilerBridge::placementWriter() {
#if RALLOC_WITH_BFP4C
    return new PlacementWriterPass(maps_->plan, ctx_.layout);
#else
    return nullptr;
#endif
}

bool CompilerBridge::selfCheck() const {
#if RALLOC_WITH_BFP4C
    // Re-run the legacy PHV::ValidateAllocation Inspector over the mutated IR.
    // It reports any illegal allocation (thread split, double-allocated bits,
    // overlapping non-mutex fields, un-deparsable layout, ...) via error(), so a
    // non-zero increase in the global error count means the model's allocation
    // is invalid and the caller must fall back to the legacy allocator (Doc 06
    // §5). Requires PhvInfo + Pipe + ClotInfo; if any is missing we cannot check
    // and conservatively report success (the host's normal validation still runs
    // downstream).
    if (!ctx_.phv || !ctx_.pipe || !ctx_.clots) return true;

    PhvInfo &phv = *ctx_.phv;
    const ClotInfo &clot = *ctx_.clots;

    // Build a FieldSliceLiveRangeDB to satisfy the validator's signature. With
    // physical-liverange overlay disabled (the default AllocSetting), the
    // validator never dereferences this DB, so we construct it cheaply (its
    // sub-passes are not applied) from the context we have. A null backtracker
    // is acceptable; red_info/pragmas are empty placeholders.
    ReductionOrInfo red_info;
    PHV::Pragmas pragmas(phv);  // constructed, not applied
    PHV::FieldSliceLiveRangeDB liverange(/*backtracker*/ nullptr, ctx_.defuse, phv, red_info, clot,
                                         pragmas);
    PHV::AllocSetting setting;  // defaults: physical_liverange_overlay = false

    PHV::ValidateAllocation validator(phv, clot, liverange, setting);

    unsigned errors_before = P4::errorCount();
    ctx_.pipe->apply(validator);
    return P4::errorCount() == errors_before;
#else
    return true;
#endif
}

void CompilerBridge::writeInputsJson(const ModelInputs &in, const std::string &path) {
    writeModelInputsFile(in, path);
}

ModelInputs CompilerBridge::readInputsJson(const std::string &path) {
    return readModelInputsFile(path);
}

ResumeBundle CompilerBridge::buildResumeBundle(const ModelInputs &in) const {
    ResumeBundle b;
#if RALLOC_WITH_BFP4C
    for (const TableInput &t : in.tables) {
        ResumeTableRef r;
        r.id = t.id;
        if (t.id >= 0 && t.id < static_cast<Id>(maps_->table_by_id.size()))
            r.name = std::string(maps_->table_by_id[t.id]->name.c_str());
        for (const auto &op : t.options) r.option_ids.push_back(op.option_id);
        b.tables.push_back(std::move(r));
    }
    for (const ActionInput &a : in.actions) {
        ResumeActionRef r;
        r.id = a.id;
        r.table_id = a.table_id;
        if (a.table_id >= 0 && a.table_id < static_cast<Id>(maps_->table_by_id.size()))
            r.table_name = std::string(maps_->table_by_id[a.table_id]->name.c_str());
        if (a.id >= 0 && a.id < static_cast<Id>(maps_->action_by_id.size()))
            r.action_name = std::string(maps_->action_by_id[a.id]->name.name.c_str());
        b.actions.push_back(std::move(r));
    }
#else
    (void)in;
#endif
    return b;
}

}  // namespace ralloc
