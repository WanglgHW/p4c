/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/device_spec.h
 *
 * Tofino device resource constants used as right-hand-sides of the MILP
 * (Doc 03 §1). These mirror the bf-p4c specs exactly:
 *   - StageUse / MauSpec  : backends/tofino/bf-p4c/specs/mau_spec.h
 *   - Memories            : backends/tofino/bf-p4c/mau/memories.h
 *   - StageUseEstimate    : backends/tofino/bf-p4c/mau/resource_estimate.h
 *   - PhvSpec / device    : backends/tofino/bf-p4c/specs/{phv_spec.cpp,device.h}
 *   - TofinoIMemSpec      : backends/tofino/bf-p4c/specs/mau_spec.cpp
 *
 * A compile-time bridge (model/src/bridge/spec_check.cpp) static_asserts each
 * constant against the live bf-p4c symbol so spec drift breaks the build.
 *
 * The model NEVER hard-codes these at call sites; it reads a DeviceSpec value
 * so that Tofino-1 / Tofino-2 variants and --phv-scale-factor are honored.
 */
#ifndef RALLOC_DEVICE_SPEC_H_
#define RALLOC_DEVICE_SPEC_H_

#include <array>
#include <cstdint>
#include <string>

namespace ralloc {

enum class DeviceKind { Tofino1, Tofino2U, Tofino2M, Tofino2H };

/// PHV container size classes (bits). Matches PHV::Size {b8,b16,b32}.
enum class PhvSize : uint8_t { B8 = 8, B16 = 16, B32 = 32 };

/// PHV container kind. Matches PHV::Kind.
enum class PhvKind : uint8_t { Normal, Tagalong, Mocha, Dark };

/// One PHV container-class population (e.g. 4 MAU groups x 16 of 8-bit normal).
struct PhvClassSpec {
    PhvSize size;
    PhvKind kind;
    unsigned num_groups;        ///< MAU groups of this class
    unsigned per_group;         ///< containers per group
    unsigned containers() const { return num_groups * per_group; }
    unsigned bits() const { return containers() * static_cast<unsigned>(size); }
};

/**
 * Full per-device resource budget. Values below are Tofino-1 defaults
 * (DeviceSpec::tofino1()); Tofino-2 variants override via the named factories.
 */
struct DeviceSpec {
    DeviceKind kind = DeviceKind::Tofino1;

    // ---- MAU pipeline geometry (Doc 01 §3) -------------------------------
    int num_stages          = 12;   ///< Device::getNumStages()  (T2-U: 20)
    int logical_ids_per_stage = 16; ///< StageUse::MAX_LOGICAL_IDS

    // ---- Per-stage memory/compute budgets (StageUse / resource_estimate) --
    int srams_per_stage     = 80;   ///< MAX_SRAMS  (SRAM_ROWS 8 x SRAM_COLUMNS 10)
    int tcams_per_stage     = 24;   ///< MAX_TCAMS  (12 rows x 2 cols)
    int maprams_per_stage   = 48;   ///< MAX_MAPRAMS (8 rows x 6 cols)
    int stats_alus_per_stage  = 4;  ///< MAX_STATS_ALUS
    int meter_alus_per_stage  = 4;  ///< MAX_METER_ALUS
    int local_tinds_per_stage = 16; ///< MAX_LOCAL_TINDS
    int gateways_per_stage  = 16;   ///< GATEWAYS_PER_ROW(2) x SRAM_ROWS(8)

    // ---- Memory geometry (memories.h) ------------------------------------
    int sram_rows = 8, sram_columns = 10;
    int left_side_columns = 4, right_side_columns = 6;
    int mapram_columns = 6;
    int sram_depth = 1024;          ///< lines per RAM
    int tcam_rows = 12, tcam_columns = 2;
    int tcam_depth = 512;           ///< lines per TCAM
    int tcam_width = 44;            ///< bits per TCAM line (MauSpec::tcam_width)
    int max_data_swbox_rows = 5;    ///< MAX_DATA_SWBOX_ROWS
    int max_ways = 8;               ///< StageUseEstimate::MAX_WAYS

    // ---- Input crossbar (TofinoIXBarSpec) (Doc 01 §4) --------------------
    int exact_ixbar_groups    = 8;
    int exact_bytes_per_group = 16;
    int exact_ixbar_bytes     = 128; ///< MAX_IXBAR_BYTES = groups x bytes
    int ternary_ixbar_groups  = 12;  ///< MAX_TERNARY_GROUPS
    int ternary_bytes_per_group = 5;
    int ternary_bytes_per_big_group = 11;
    int gateway_search_bytes  = 4;

    // ---- Hash (Doc 01 §4.1) ----------------------------------------------
    int hash_tables       = 16;
    int hash_groups       = 8;
    int hash_index_groups = 4;   ///< 10-bit index groups
    int hash_single_bits  = 12;  ///< top individually-addressable bits
    int max_hash_bits     = 52;
    int hash_dist_units   = 2;
    int hash_dist_bits    = 16;

    // ---- VLIW / instruction memory (TofinoIMemSpec) (Doc 01 §5) ----------
    int imem_rows_per_gress = 32;  ///< rows()
    int imem_colors         = 2;   ///< colors()
    int imem_address_bits   = 6;
    int imem_map_table_entries = 8;

    // ---- PHV inventory (Doc 01 §2) ---------------------------------------
    // Tofino-1 normal: B 4x16, H 6x16, W 4x16; T-PHV: 8 collections.
    std::array<PhvClassSpec, 3> normal_phv = {{
        {PhvSize::B8,  PhvKind::Normal, 4, 16},
        {PhvSize::B16, PhvKind::Normal, 6, 16},
        {PhvSize::B32, PhvKind::Normal, 4, 16},
    }};
    int num_pov_bits = 256;
    int num_tagalong_collections = 8;

    // ---- factories -------------------------------------------------------
    static DeviceSpec tofino1();
    static DeviceSpec tofino2u();
    static DeviceSpec tofino2m();
    /// Build from a bf-p4c device name string ("Tofino", "Tofino2", ...).
    static DeviceSpec fromName(const std::string &name, float phv_scale_factor = 1.0f);

    int total_normal_containers() const {
        int n = 0;
        for (auto &c : normal_phv) n += c.containers();
        return n;
    }
};

}  // namespace ralloc

#endif  // RALLOC_DEVICE_SPEC_H_
