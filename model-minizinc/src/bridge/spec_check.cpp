/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * Compile-time guard that keeps ralloc::DeviceSpec in sync with the live bf-p4c
 * specs (Doc 07 §3). Built only inside the p4c tree (RALLOC_WITH_BFP4C=1); a
 * spec change in the backend then breaks THIS build loudly instead of silently
 * making the model wrong.
 */
#include "ralloc/device_spec.h"

#if RALLOC_WITH_BFP4C
#include "backends/tofino/bf-p4c/mau/memories.h"
#include "backends/tofino/bf-p4c/specs/mau_spec.h"

namespace ralloc {
namespace {
constexpr DeviceSpec kT1 = [] {
    DeviceSpec d;  // header defaults = Tofino-1
    return d;
}();

static_assert(kT1.logical_ids_per_stage == StageUse::MAX_LOGICAL_IDS, "logical id drift");
static_assert(kT1.srams_per_stage == StageUse::MAX_SRAMS, "sram drift");
static_assert(kT1.tcams_per_stage == StageUse::MAX_TCAMS, "tcam drift");
static_assert(kT1.maprams_per_stage == StageUse::MAX_MAPRAMS, "mapram drift");
static_assert(kT1.exact_ixbar_bytes == StageUse::MAX_IXBAR_BYTES, "ixbar drift");
static_assert(kT1.ternary_ixbar_groups == StageUse::MAX_TERNARY_GROUPS, "ternary drift");
static_assert(kT1.sram_rows == Memories::SRAM_ROWS, "sram rows drift");
static_assert(kT1.sram_columns == Memories::SRAM_COLUMNS, "sram cols drift");
static_assert(kT1.mapram_columns == Memories::MAPRAM_COLUMNS, "mapram cols drift");
static_assert(kT1.stats_alus_per_stage == Memories::STATS_ALUS, "stats alu drift");
static_assert(kT1.meter_alus_per_stage == Memories::METER_ALUS, "meter alu drift");
static_assert(kT1.max_data_swbox_rows == Memories::MAX_DATA_SWBOX_ROWS, "swbox drift");
}  // namespace
}  // namespace ralloc
#endif  // RALLOC_WITH_BFP4C
