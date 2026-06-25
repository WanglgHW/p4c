/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/ralloc_model_pass.h
 *
 * RallocModelPass — the bf-p4c hosting pass for the MILP allocator (Doc 06 §2).
 *
 * It is a thin IR::Transform that, when --use-ralloc is set, runs the MILP MAU
 * placement (M2) + VLIW (M3) consuming the already-computed legacy PHV
 * allocation (the Doc 07 §1 "P2 first" integration), writes the placement back
 * onto the IR, and self-checks it. On ANY failure (no solver, infeasible,
 * timeout, validation) it transparently delegates to the legacy table-placement
 * visitor passed as `fallback`, so it can never regress a compilable program.
 *
 * Wiring (backends/tofino/bf-p4c/backend.cpp), replacing the `&table_alloc`
 * entry in the addPasses list:
 *
 *     options.use_ralloc
 *         ? static_cast<Visitor *>(new BFN::RallocModelPass(
 *               options, phv, deps, defuse, clot, mutex, &table_alloc))
 *         : static_cast<Visitor *>(&table_alloc),
 *
 * This header is only used inside the p4c tree (it includes bf-p4c IR headers);
 * the matching .cpp is built into libralloc_bridge.
 */
#ifndef RALLOC_RALLOC_MODEL_PASS_H_
#define RALLOC_RALLOC_MODEL_PASS_H_

#include "ir/ir.h"
#include "ir/visitor.h"
#include "ralloc/resource_model.h"

namespace ralloc {
class CompilerBridge;
struct ModelInputs;
}  // namespace ralloc

// Forward declarations of the bf-p4c analysis results the pass consumes.
class PhvInfo;
class FieldDefUse;
class ClotInfo;
class TablesMutuallyExclusive;
struct DependencyGraph;
class BFN_Options;

namespace BFN {

// Control-flow signal thrown by the emit phase (--ralloc-emit) after writing
// model_input.json + ir_middle.json, to stop the compile cleanly before solving.
// Deliberately NOT derived from std::exception / Backtrack::trigger so it is not
// swallowed by RallocModelPass's own fallback catch or the PassManager's
// backtrack handling; execute_backend() in p4c-barefoot.cpp catches it and
// returns success.
struct RallocEmitDone {
    std::string dir;
};

class RallocModelPass : public P4::Transform, public P4::Backtrack {
 public:
    RallocModelPass(const BFN_Options &options, PhvInfo &phv, DependencyGraph &deps,
                    FieldDefUse &defuse, ClotInfo &clot, TablesMutuallyExclusive &mutex,
                    P4::Visitor *fallback);

    const P4::IR::Node *preorder(P4::IR::BFN::Pipe *pipe) override;

    // RallocModelPass wraps the legacy table-placement visitor (`fallback`), which
    // is itself a Backtrack handler: TableSummary drives multi-round allocation by
    // throwing RerunTablePlacementTrigger / FinalRerunTablePlacementTrigger, and
    // only TablePlacement::backtrack() handles those. Because the wrapped pass runs
    // as a nested apply() (not a managed pass of the backend PassManager), the
    // manager would never consult its backtrack(), so those triggers would escape
    // uncaught. We therefore forward backtrack()/never_backtracks() to the wrapped
    // visitor so the manager checkpoints this pass and rewinds table placement
    // exactly as it would for the bare legacy pass. (PHVTrigger::failure is handled
    // by a separate managed pass — MauBacktracker — so delegating returns false for
    // it and the manager continues to that handler, unchanged.)
    bool backtrack(P4::Backtrack::trigger &trig) override;
    bool never_backtracks() override;

 private:
    const P4::IR::Node *runFallback(P4::IR::BFN::Pipe *pipe);
    // --ralloc-resume: load model_out.json + ir_middle.json from the resume dir,
    // join the solver result to the live program by stable name, log the advisory
    // placement, then delegate to the legacy allocator (which produces the binary).
    const P4::IR::Node *runResume(P4::IR::BFN::Pipe *pipe, const ralloc::ModelInputs &inputs,
                                  ralloc::CompilerBridge &bridge);
    ralloc::SolveOptions makeSolveOptions() const;

    const BFN_Options &options_;
    PhvInfo &phv_;
    DependencyGraph &deps_;
    FieldDefUse &defuse_;
    ClotInfo &clot_;
    TablesMutuallyExclusive &mutex_;
    P4::Visitor *fallback_;

    // The MILP solve is advisory (its result is logged, not committed) and SCIP's
    // heavy allocation is unsafe to repeat under p4c's GC-overridden operator new.
    // TableSummary drives several table-placement rounds via backtracking, which
    // re-enters this pass; we therefore solve the model only on the first round and
    // delegate straight to the legacy allocator on every backtrack re-entry.
    bool attempted_ = false;
};

}  // namespace BFN

#endif  // RALLOC_RALLOC_MODEL_PASS_H_
