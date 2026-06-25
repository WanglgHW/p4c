/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * RallocModelPass implementation (Doc 06 §2, Doc 07 §1 "P2-first" integration).
 *
 * Built into libralloc_bridge (RALLOC_WITH_BFP4C=1). Runs the MILP MAU/VLIW
 * placement over the legacy PHV allocation, stamps the result onto the IR, and
 * falls back to the legacy table-placement pass on any failure.
 */
#include "ralloc/ralloc_model_pass.h"

#include "backends/tofino/bf-p4c/bf-p4c-options.h"
#include "backends/tofino/bf-p4c/mau/attached_info.h"   // SplitAttachedInfo
#include "backends/tofino/bf-p4c/mau/table_dependency_graph.h"  // DependencyGraph (red_info)
#include "backends/tofino/bf-p4c/mau/table_layout.h"    // LayoutChoices
#include "ralloc/compiler_bridge.h"
#include "ralloc/model_json.h"
#include "ralloc/resource_model.h"
#include "lib/exceptions.h"  // Util::CompilerBug
#include "lib/log.h"

#include <exception>
#include <map>
#include <string>

namespace BFN {

RallocModelPass::RallocModelPass(const BFN_Options &options, PhvInfo &phv, DependencyGraph &deps,
                                 FieldDefUse &defuse, ClotInfo &clot, TablesMutuallyExclusive &mutex,
                                 P4::Visitor *fallback)
    : options_(options),
      phv_(phv),
      deps_(deps),
      defuse_(defuse),
      clot_(clot),
      mutex_(mutex),
      fallback_(fallback) {
    setName("RallocModelPass");
}

ralloc::SolveOptions RallocModelPass::makeSolveOptions() const {
    ralloc::SolveOptions o;
    o.objective = ralloc::Objective::MinStages;
    o.time_limit_s = 120.0;
    o.mip_gap = 0.05;
    o.warm_start = true;
    o.deterministic = true;
    return o;
}

const IR::Node *RallocModelPass::runFallback(IR::BFN::Pipe *pipe) {
    LOG1("ralloc: falling back to legacy table placement");
    return fallback_ ? pipe->apply(*fallback_) : pipe;
}

const IR::Node *RallocModelPass::runResume(IR::BFN::Pipe *pipe, const ralloc::ModelInputs &inputs,
                                           ralloc::CompilerBridge &bridge) {
    const std::string &dir = options_.ralloc_resume_dir;

    ralloc::ResumeBundle bundle;
    ralloc::ModelResults results;
    try {
        bundle = ralloc::readResumeBundleFile(dir + "/ir_middle.json");
        results = ralloc::readModelResultsFile(dir + "/model_out.json");
    } catch (const std::exception &e) {
        LOG2("ralloc: cannot read resume inputs from " << dir << " (" << e.what()
             << "); fallback");
        return runFallback(pipe);
    }

    // Consistency check: the resume run must be the SAME program the solver saw.
    // ingest() is deterministic, so the live bundle (built from this compile's IR)
    // must match the on-disk one id-for-id. A mismatch means the .p4 / flags drifted
    // between emit and resume; bail to legacy rather than apply a stale placement.
    ralloc::ResumeBundle live = bridge.buildResumeBundle(inputs);
    std::map<ralloc::Id, std::string> live_name;
    for (const auto &t : live.tables) live_name[t.id] = t.name;
    bool consistent = live.tables.size() == bundle.tables.size();
    for (const auto &t : bundle.tables) {
        auto it = live_name.find(t.id);
        if (it == live_name.end() || it->second != t.name) {
            consistent = false;
            LOG2("ralloc: resume bundle mismatch at table id " << t.id << " ('" << t.name
                 << "' vs live '" << (it == live_name.end() ? "<none>" : it->second) << "')");
            break;
        }
    }
    if (!consistent) {
        LOG2("ralloc: ir_middle.json does not match the current program; fallback");
        return runFallback(pipe);
    }

    // Advisory: report the solver's placement (joined to names) and validate it is
    // self-consistent, then let the legacy allocator emit the binary (the commit
    // path that realizes memuse is the separate RALLOC_COMMIT work).
    std::map<ralloc::Id, std::string> name_by_id;
    for (const auto &t : bundle.tables) name_by_id[t.id] = t.name;
    LOG1("ralloc: resume — applying model_out.json from " << dir << " ("
         << results.mau.stages_used << " stage(s), " << results.mau.tables.size()
         << " table(s))");
    for (const auto &ta : results.mau.tables) {
        auto it = name_by_id.find(ta.table_id);
        LOG2("ralloc:   table " << (it == name_by_id.end() ? "?" : it->second) << " -> stage "
             << ta.first_stage << (ta.last_stage > ta.first_stage
                                       ? "-" + std::to_string(ta.last_stage) : "")
             << " (option " << ta.option_id << ")");
    }

#ifdef RALLOC_COMMIT
    if (!bridge.writeBack(results)) {
        LOG2("ralloc: resume writeBack/selfCheck failed; fallback");
        return runFallback(pipe);
    }
    return pipe->apply(*bridge.placementWriter());
#else
    return runFallback(pipe);
#endif
}

// Forward backtracking to the wrapped legacy table-placement visitor. TableSummary
// throws RerunTablePlacementTrigger / FinalRerunTablePlacementTrigger to re-run
// table placement (e.g. without container conflicts); only TablePlacement::backtrack
// handles those. Delegating lets the backend PassManager rewind into table placement
// through this wrapper. Returns false for triggers TablePlacement does not own (e.g.
// PHVTrigger::failure), so the manager keeps walking back to their real handler.
bool RallocModelPass::backtrack(P4::Backtrack::trigger &trig) {
    if (auto *bt = dynamic_cast<P4::Backtrack *>(fallback_)) return bt->backtrack(trig);
    return false;
}

// Report this pass as backtrack-capable iff the wrapped pass is, so the PassManager
// saves a checkpoint before running us (it only checkpoints passes for which
// never_backtracks() is false).
bool RallocModelPass::never_backtracks() {
    if (auto *bt = dynamic_cast<P4::Backtrack *>(fallback_)) return bt->never_backtracks();
    return true;
}

const IR::Node *RallocModelPass::preorder(IR::BFN::Pipe *pipe) {
    // We process the whole pipe here; do not recurse into children.
    prune();

    // Backtracking (RerunTablePlacementTrigger / PHVTrigger from TableSummary)
    // re-enters this pass for each additional table-placement round. The MILP is
    // advisory and SCIP is unsafe to re-run under the GC, so solve only once and
    // delegate to the legacy allocator on every subsequent (backtrack) round.
    if (attempted_) return runFallback(pipe);
    attempted_ = true;

    // The entire model attempt is wrapped: any exception (e.g. a BUG_CHECK in the
    // ingest machinery) degrades to the legacy allocator rather than aborting the
    // compile, since --use-ralloc is experimental. (Note: if writeBack's
    // PHV::ValidateAllocation self-check finds a genuinely invalid allocation it
    // emits hard error()s before we fall back; a fully silent probe would require
    // wrapping this in an AutoCompileContext — see Doc 06 §5.)
    try {
        // ---- build real layout-option demand inputs (mirrors TablePlacement) --
        // SplitAttachedInfo is an analysis over the pipe; LayoutChoices computes
        // the per-table layout options lazily from it.
        SplitAttachedInfo split(phv_);
        pipe->apply(split);
        LayoutChoices layout(phv_, deps_.red_info, split);

        // TablesMutuallyExclusive is an analysis that must be applied before its
        // operator() is valid (it BUG_CHECKs on unknown tables otherwise); table
        // placement normally runs it internally, so populate it here.
        pipe->apply(mutex_);

        // ---- ingest IR -> model inputs ------------------------------------
        ralloc::CompilerContext ctx;
        ctx.pipe = pipe;
        ctx.phv = &phv_;
        ctx.deps = &deps_;
        ctx.defuse = &defuse_;
        ctx.clots = &clot_;
        ctx.layout = &layout;
        ctx.mutex = &mutex_;
        ctx.options = &options_;
        ralloc::CompilerBridge bridge(ctx);

        ralloc::ModelInputs inputs = bridge.ingest();
        ralloc::ValidationReport report = bridge.validate(inputs);
        if (!report.ok) {
            for (const auto &e : report.errors) LOG2("ralloc: invalid input: " << e);
            return runFallback(pipe);
        }

        // ---- decoupled (out-of-process) flow -------------------------------
        // --ralloc-emit: write the solver input + the resume bundle and stop the
        // compile here (no SCIP in this process). The standalone `ralloc-solve`
        // then turns model_input.json into model_out.json.
        if (!options_.ralloc_emit_dir.empty()) {
            const std::string &dir = options_.ralloc_emit_dir;
            ralloc::CompilerBridge::writeInputsJson(inputs, dir + "/model_input.json");
            ralloc::writeResumeBundleFile(bridge.buildResumeBundle(inputs),
                                          dir + "/ir_middle.json");
            LOG1("ralloc: emitted model_input.json + ir_middle.json to " << dir
                 << "; stopping compile (run ralloc-solve next)");
            throw RallocEmitDone{dir};
        }

        // --ralloc-resume: consume the solver's model_out.json (joined to the
        // resume bundle by stable name) instead of running SCIP in-process.
        if (!options_.ralloc_resume_dir.empty()) {
            return runResume(pipe, inputs, bridge);
        }

        // ---- solve M2 (MAU/memory) consuming the legacy PHV, then M3 (VLIW) -
        ralloc::ResourceModel model(makeSolveOptions());
        ralloc::SolveResult mau = model.solveMau(inputs, /*phv=*/ {});
        if (!mau.usable()) {
            LOG2("ralloc: MAU placement not usable (" << mau.message << "); fallback");
            return runFallback(pipe);
        }
        ralloc::SolveResult vliw = model.solveVliw(inputs, mau.results.mau);
        if (vliw.usable()) mau.results.vliw = vliw.results.vliw;

        LOG1("ralloc: MILP solved — "
             << mau.results.mau.stages_used << " stage(s), "
             << mau.results.mau.tables.size() << " table(s), optimal");

        // ADVISORY (shadow) MODE — the default until memory realization lands.
        //
        // The MILP fixes the hard decisions (stage / logical-id / layout option),
        // but a complete TableResourceAlloc also needs detailed memuse / ixbar /
        // action-data, which the legacy Memories/IXBar passes fill *inside*
        // table_alloc. Committing only the coarse placement leaves memuse empty
        // and a downstream pass fails. To honor the no-regression contract we
        // therefore log the optimal solution and let the legacy allocator produce
        // the actual binary. Flip RALLOC_COMMIT to exercise the real write-back
        // once a constrained Memories realization pass is wired in (Doc 06 §4).
#ifdef RALLOC_COMMIT
        if (!bridge.writeBack(mau.results)) {
            LOG2("ralloc: writeBack/selfCheck failed; fallback");
            return runFallback(pipe);
        }
        return pipe->apply(*bridge.placementWriter());
#else
        return runFallback(pipe);
#endif
    } catch (const Util::CompilerBug &e) {
        LOG2("ralloc: internal error (" << e.what() << "); fallback to legacy");
        return runFallback(pipe);
    } catch (const std::exception &e) {
        LOG2("ralloc: exception (" << e.what() << "); fallback to legacy");
        return runFallback(pipe);
    }
}

}  // namespace BFN
