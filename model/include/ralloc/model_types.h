/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/model_types.h
 *
 * Plain-old-data structs forming the seam between bf-p4c and the optimizer
 * (Doc 04 inputs, Doc 06 outputs). These deliberately contain NO bf-p4c IR
 * types: entities are referred to by stable integer ids, with a side table
 * mapping ids back to IR nodes held only inside compiler_bridge.cpp.
 *
 * This makes the model core unit-testable from JSON fixtures without linking
 * the compiler.
 */
#ifndef RALLOC_MODEL_TYPES_H_
#define RALLOC_MODEL_TYPES_H_

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "ralloc/device_spec.h"

namespace ralloc {

using Id = int32_t;                       ///< opaque entity id
using ResourceVec = std::array<int, 11>;  ///< demand vector, see DemandIndex

/// Index into a per-(table,option) demand vector d[t,o] (Doc 03 §4, mirrors
/// StageUseEstimate fields in resource_estimate.h).
enum DemandIndex {
    D_LOGICAL_IDS = 0,
    D_SRAMS,
    D_TCAMS,
    D_MAPRAMS,
    D_EXACT_IXBAR_BYTES,
    D_TERNARY_GROUPS,
    D_STATS_ALUS,
    D_METER_ALUS,
    D_HASH_BITS,
    D_HASH_GROUPS,
    D_GATEWAYS,
    D_COUNT
};

enum class Gress : uint8_t { Ingress, Egress, Ghost };

// ===========================================================================
// PHV (M1) inputs
// ===========================================================================

/// A field slice to be placed in a PHV container (Doc 03 §3).
struct SliceInput {
    Id id;
    int width_bits;                 ///< w(s)
    int live_lo, live_hi;           ///< control-flow live range [lo,hi]
    int required_offset = -1;       ///< align(s); -1 = free
    bool byte_aligned = false;      ///< byteAlign(s)
    bool needs_mau = false;         ///< read/written in MAU (forbids T-PHV)
    bool solitary = false;          ///< @pa_solitary -> whole container
    bool no_pack = false;           ///< cannot share container
    PhvSize max_kind_size = PhvSize::B32;
    Id field_id = -1;               ///< owning field (for grouping)
};

/// A physical PHV container (Doc 03 §3).
struct ContainerInput {
    Id id;
    PhvSize size;
    PhvKind kind;
    int mau_group;                  ///< grp(c)
    bool ingress_only = false;
    bool egress_only = false;
};

/// Symmetric relations among slices (encoded as id pairs).
struct SlicePairs {
    std::vector<std::pair<Id, Id>> mutex;   ///< MUTEX (may overlay)
    std::vector<std::pair<Id, Id>> conflict;///< CONF  (cannot co-reside)
};

// ===========================================================================
// MAU (M2) inputs
// ===========================================================================

/// One layout option of a table with its resource demand vector (Doc 04 §3).
struct LayoutOptionInput {
    Id option_id;
    ResourceVec demand{};           ///< d[t,o] indexed by DemandIndex
    int parts = 1;                   ///< stage-tables when split (stages_required)
    double power = 0.0;              ///< pow(t,o)
    std::vector<Id> key_byte_ids;    ///< crossbar bytes used (coupling C1)
};

struct TableInput {
    Id id;
    Gress gress;
    bool splittable = false;
    std::vector<LayoutOptionInput> options;   ///< O(t), >= 1
    std::vector<Id> action_ids;               ///< actions of this table
    Id host_table = -1;                        ///< for shared/indirect attached
};

enum class DepKind : uint8_t { Match, Action, Control, Anti };

struct DepEdge {
    Id from;          ///< b (producer)
    Id to;            ///< a (consumer), stage(a) >= stage(b) + gap
    int gap;          ///< g(b,a) in {0,1}
    DepKind kind;
};

// ===========================================================================
// VLIW (M3) inputs
// ===========================================================================

struct ActionInput {
    Id id;
    Id table_id;
    Gress gress;
    std::vector<Id> written_containers;   ///< Wr(a) (ALUs written)
    std::vector<Id> identical_actions;    ///< share(a,a')=1 set (V4)
    bool stateful = false;
};

struct ActionDataField {
    Id id;
    Id action_id;
    int slot_bytes;                       ///< slot(f) in {1,2,4}
    int format_offset = -1;               ///< fixed byte offset, -1 = free (V6)
};

// ===========================================================================
// Aggregate input bundle
// ===========================================================================

struct ModelInputs {
    DeviceSpec device;

    // M1
    std::vector<SliceInput> slices;
    std::vector<ContainerInput> containers;
    SlicePairs slice_pairs;
    // kindOK / srcReach as a sparse legal-container list per slice (Doc 03 (3)).
    // legal_containers[i] is the candidate container ids for slices[i].
    std::vector<std::vector<Id>> legal_containers;

    // M2
    std::vector<TableInput> tables;
    std::vector<DepEdge> deps;
    std::vector<std::pair<Id, Id>> table_mutex;

    // M3
    std::vector<ActionInput> actions;
    std::vector<ActionDataField> action_data;
    int action_data_bus_bytes = 32;       ///< bus width (device-specific)
};

// ===========================================================================
// Results (Doc 06 §4)
// ===========================================================================

struct PhvAssignment {
    Id slice_id;
    Id container_id;
    int bit_offset;
};
struct PhvResult {
    std::vector<PhvAssignment> assignments;
    int containers_used = 0;
};

struct TableAssignment {
    Id table_id;
    Id option_id;
    int first_stage;
    int last_stage;                       ///< == first_stage unless split
    std::vector<int> stage_tables;        ///< stages occupied
};
struct MauResult {
    std::vector<TableAssignment> tables;
    int stages_used = 0;
    double total_power = 0.0;
    ResourceVec peak_utilization{};       ///< max over stages, per resource
};

struct ActionAssignment {
    Id action_id;
    int imem_row;
    int imem_color;
};
struct AdataAssignment {
    Id field_id;
    int bus_byte;
};
struct VliwResult {
    std::vector<ActionAssignment> actions;
    std::vector<AdataAssignment> adata;
};

struct ModelResults {
    PhvResult phv;
    MauResult mau;
    VliwResult vliw;
};

// ===========================================================================
// Resume bundle (ir_middle.json)
// ===========================================================================
//
// The compiler-side data, beyond model_input.json, that the decoupled resume
// phase needs to map the solver's integer ids in model_out.json back onto live
// IR entities. It is pure POD (ids + stable names) — no IR types — so it round
// trips through the same JSON layer. The resume run re-derives the IR itself by
// recompiling deterministically and joins it to model_out.json on these names.

struct ResumeTableRef {
    Id id;                       ///< matches TableAssignment::table_id
    std::string name;            ///< IR::MAU::Table::name
    std::vector<Id> option_ids;  ///< option index -> option id (layout choices)
};
struct ResumeActionRef {
    Id id;                       ///< matches ActionAssignment::action_id
    Id table_id;
    std::string table_name;
    std::string action_name;
};
struct ResumeBundle {
    std::vector<ResumeTableRef> tables;
    std::vector<ResumeActionRef> actions;
};

}  // namespace ralloc

#endif  // RALLOC_MODEL_TYPES_H_
