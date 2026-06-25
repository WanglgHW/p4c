/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/compiler_bridge.h  --  IR <-> model translation (Doc 04, Doc 06).
 *
 * The ONLY component that includes bf-p4c IR headers. It (a) ingests the midend
 * IR + analysis results into a ModelInputs, (b) validates them, and (c) writes a
 * ModelResults back into PhvInfo / TableResourceAlloc / InstructionMemory::Use.
 *
 * Forward-declared compiler types keep this header light; the .cpp pulls the
 * real bf-p4c headers. Everything below the fold is guarded so the model core
 * can be built/tested without the compiler.
 */
#ifndef RALLOC_COMPILER_BRIDGE_H_
#define RALLOC_COMPILER_BRIDGE_H_

#include <string>
#include <vector>

#include "ralloc/model_types.h"

// ---- forward declarations of bf-p4c types (defined in their own headers) ----
namespace P4 {
class Transform;  // ir/visitor.h
namespace IR {
namespace BFN {
class Pipe;
}  // namespace BFN
}  // namespace IR
}  // namespace P4
class PhvInfo;
class FieldDefUse;
class ClotInfo;
class LayoutChoices;
class TablesMutuallyExclusive;
struct DependencyGraph;
class BFN_Options;

namespace ralloc {

/// Result of validating extracted inputs (Doc 04 §6).
struct ValidationReport {
    bool ok = true;
    std::vector<std::string> errors;   ///< empty iff ok
};

/// Bundles the compiler context objects the bridge needs (mirrors Backend
/// members in backends/tofino/bf-p4c/backend.h).
struct CompilerContext {
    const P4::IR::BFN::Pipe *pipe = nullptr;
    PhvInfo *phv = nullptr;
    const DependencyGraph *deps = nullptr;
    const FieldDefUse *defuse = nullptr;
    const ClotInfo *clots = nullptr;
    LayoutChoices *layout = nullptr;
    const TablesMutuallyExclusive *mutex = nullptr;
    const BFN_Options *options = nullptr;
};

/**
 * Translates between bf-p4c IR and the model PODs. Holds the id<->IR-node maps
 * needed by writeBack, so a single CompilerBridge instance must be used for both
 * ingest and writeBack of one compile.
 */
class CompilerBridge {
 public:
    explicit CompilerBridge(CompilerContext ctx);
    ~CompilerBridge();

    /// IR + analyses -> ModelInputs (Doc 04 §2-4). Fills DeviceSpec from
    /// Device::get(). Populates internal id<->node maps.
    ModelInputs ingest();

    /// Necessary-feasibility / sanity checks (Doc 04 §6).
    ValidationReport validate(const ModelInputs &) const;

    /// ModelResults -> compiler structures (Doc 06 §4). Two halves:
    ///   PHV  : mutated DIRECTLY here — a PHV::AllocSlice per assignment is
    ///          attached to its PHV::Field in PhvInfo (no IR rewrite needed).
    ///   MAU  : recorded into an internal placement plan (stage / logical-id /
    ///          stage-split / chosen layout option / imem row+color); APPLIED to
    ///          the IR by the Transform returned from placementWriter(), which
    ///          the host pass runs on the Pipe. The constrained legacy detailed
    ///          allocators (Memories/IXBar/ActionDataBus) then fill memuse.
    /// Returns false if the written allocation fails the legacy self-check
    /// (validate_allocation.cpp), in which case the caller must fall back.
    bool writeBack(const ModelResults &);

    /// IR Transform that stamps the recorded MAU/VLIW plan onto IR::MAU::Table
    /// nodes (stage_, logical_id, stage_split, resources). Run AFTER writeBack:
    ///   pipe = pipe->apply(*bridge.placementWriter());
    /// Returns nullptr in the standalone (no-compiler) build.
    P4::Transform *placementWriter();

    /// Re-run the legacy bf-p4c constraint checkers against current IR state
    /// (Doc 06 §5). True == allocation is legal.
    bool selfCheck() const;

    // Optional JSON I/O for fixtures / offline solving (Doc 07 §4).
    static void writeInputsJson(const ModelInputs &, const std::string &path);
    static ModelInputs readInputsJson(const std::string &path);

    /// Build the ir_middle resume bundle (solver id <-> stable IR name) from the
    /// id<->node maps that ingest() populated, so the decoupled resume phase can
    /// map model_out.json ids back onto live IR entities by name. Must be called
    /// on the same CompilerBridge that produced `in` via ingest(). Returns an
    /// empty bundle in the standalone (no-compiler) build.
    ResumeBundle buildResumeBundle(const ModelInputs &in) const;

 private:
    CompilerContext ctx_;
    struct Maps;
    Maps *maps_;   ///< id <-> IR node bookkeeping (opaque)
};

}  // namespace ralloc

#endif  // RALLOC_COMPILER_BRIDGE_H_
