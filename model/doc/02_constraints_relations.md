# Doc 02 — Constraint Catalogue & Inter-Resource Relations

This document is the bridge between the hardware analysis (Doc 01) and the formal
MILP (Doc 03). It (a) catalogues every constraint class as a *plain-language +
set-relation* statement, and (b) makes explicit the **couplings** that decide
which constraints must live in the same sub-model vs. can be passed as parameters.

Notation: see Doc 03 §1 for the formal sets. Here we use informal names.

---

## 1. PHV constraints (sub-model M1)

| ID | Name | Statement | Source |
|---|---|---|---|
| P1 | **Assignment** | every referenced field slice is placed in exactly one container at one offset | `phv/allocate_phv.cpp` |
| P2 | **Type/size fit** | slice of width w must go in a container of width ≥ w of a compatible kind | `phv.cpp`, `PHV::Type` |
| P3 | **No bit overlap** | two slices live at the same time in the same container must not overlap in bits | `phv/utils/` |
| P4 | **Mutual exclusion / overlay** | slices whose live ranges are disjoint (or mutually exclusive headers) **may** share bits (overlay) | `fieldslice_live_range.cpp`, `mutex` |
| P5 | **No-pack conflict** | two slices that conflict (written by the same action with different sources, etc.) cannot share a container | `action_phv_constraints.cpp`, `has_pack_conflict` (`allocate_phv.h:126`) |
| P6 | **Alignment** | slice must start at a required bit offset (e.g. byte-aligned for deparse/checksum, or fixed by a `@pa_container_size`/`@pa_byte_pack` pragma) | `constraints/`, `pragma/` |
| P7 | **Container kind legality** | a field read/written in the MAU cannot be in tagalong; dark/mocha restrictions on write/read | `phv_parde_mau_use.cpp` |
| P8 | **MAU group bytes** | the set of containers feeding one table's match key must fit the crossbar group wiring (couples to R6) | `parde_phv_constraints.cpp` |
| P9 | **Deparser grouping** | fields emitted together respect `deparserGroupSpec` (8/12/16 sizes) | `phv_spec.cpp:439` |
| P10 | **Solitary / exact-container** | some fields require a whole container (`@pa_solitary`) | `pragma/` |
| P11 | **Action ALU reachability** | every operand source of an ALU writing container c must be reachable by c's ALU (couples to R11) | `action_phv_constraints.cpp` |
| P12 | **Parser extractor balance** | extractions per parser state ≤ extractor budget; balances containers across extractor groups | `parser_extract_balance_score.h` |

## 2. MAU placement constraints (sub-model M2)

| ID | Name | Statement | Source |
|---|---|---|---|
| T1 | **Stage assignment** | each table placed in exactly one stage (or split across consecutive stages if too big) | `table_placement.cpp` |
| T2 | **Logical-id capacity** | ≤ 16 logical tables per stage | `MAX_LOGICAL_IDS` |
| T3 | **Dependency order** | if table A's match key depends on B's action (match/action dependency), `stage(A) ≥ stage(B) (+1)` | `table_dependency_graph.cpp` |
| T4 | **Control-flow order** | next-table / sequential apply order respected | `default_next.h`, `jbay_next_table.cpp` |
| T5 | **SRAM capacity** | Σ table RAM demand in a stage ≤ 80 | `MAX_SRAMS` |
| T6 | **TCAM capacity** | Σ ternary demand ≤ 24 | `MAX_TCAMS` |
| T7 | **Map-RAM capacity** | Σ attached map-RAM demand ≤ 48 | `MAX_MAPRAMS` |
| T8 | **Exact ixbar bytes** | Σ exact key bytes ≤ 128 (group-packed) | `MAX_IXBAR_BYTES` |
| T9 | **Ternary ixbar groups** | Σ ternary groups ≤ 12 | `MAX_TERNARY_GROUPS` |
| T10 | **Stats/Meter ALUs** | ≤ 4 stats ALUs, ≤ 4 meter ALUs per stage | `STATS_ALUS`, `METER_ALUS` |
| T11 | **Hash capacity** | Σ hash bits ≤ 52, hash groups ≤ 8 per stage | `mau_spec.cpp` |
| T12 | **Gateway capacity** | ≤ 16 gateways (2/row × 8 rows) | `GATEWAYS_PER_ROW` |
| T13 | **Table splitting** | a table needing > stage budget is split into ≥ ⌈demand/budget⌉ stage-tables | `stages_required()` (`resource_estimate.h:192`) |
| T14 | **Attached co-residence** | an attached unit lives in the same stage as (one stage-table of) its match table, unless explicitly indirect | `attached_info.cpp` |

## 3. Memory placement constraints (sub-model M2, detailed level)

| ID | Name | Statement | Source |
|---|---|---|---|
| M5a | **RAM = rows×cols** | a table's RAMs occupy distinct (row,col) cells; ways are width×depth rectangles | `memories.cpp` |
| M5b | **Left/right side** | tind/some units restricted to a side (4 left / 6 right cols) | `memories.h:45` |
| M5c | **Busses per row** | ≤ 2 search + 2 result busses per row | `BUS_COUNT`, `memories.h:64` |
| M5d | **Switchbox span** | action/stats/meter data spans ≤ 5 rows | `MAX_DATA_SWBOX_ROWS` |
| M5e | **Map-RAM adjacency** | color map RAMs ≤ 4/row; stats RAMs ≤ 3 rows/ALU | `memories.h:69,75` |

> M2 is naturally **two-level**: a coarse capacity MILP (T5–T12, counts only) and
> an optional fine placement MILP (M5*, exact cells). Doc 03 §5 gives both; the
> default solves the coarse model and delegates exact cell packing to the existing
> `Memories::allocate_all` (which is fast once stage assignment is fixed).

## 4. VLIW / action constraints (sub-model M3)

| ID | Name | Statement | Source |
|---|---|---|---|
| V1 | **Action → row** | each action used in a (stage,gress) takes one imem row of 32 | `instruction_memory.h:53` |
| V2 | **Color packing** | two actions share a row only if their written-ALU sets are disjoint | `instruction_memory.h:70` |
| V3 | **Row capacity** | ≤ 32 rows × 2 colors per (stage,gress) | `rows()=32`, `colors()=2` |
| V4 | **Action sharing** | identical-opcode actions may map to the same row (saves rows) | `instruction_memory.h:75` |
| V5 | **Action-data bus** | each action-data field gets a byte/half/full slot; Σ ≤ bus width | `action_data_bus.cpp` |
| V6 | **Action format** | action-data byte offsets feasible for the ALU inputs that consume them | `action_format.cpp` |
| V7 | **Stateful ALU caps** | per-stage stateful instruction/size limits | `StatefulAluSpec` (`device.h:78`) |

## 5. Objective candidates

| Obj | Meaning | Source of cost data |
|---|---|---|
| O1 | **min number of stages used** (latency) | stage indicator vars |
| O2 | **min PHV containers used** (free room for later programs / overlay) | container-used vars |
| O3 | **min total power** | `MauPowerSpec`, `mau_power.cpp` |
| O4 | **min crossbar/hash pressure** (improves fit robustness) | ixbar usage vars |
| O5 | **feasibility only** (find any legal allocation fastest) | constant objective |

Default lexicographic objective: **feasibility ≻ min stages (O1) ≻ min power (O3)
≻ min PHV (O2)**, implemented via weighted sum with widely separated weights or
OR-Tools' lexicographic solve loop (Doc 05 §4).

---

## 6. Inter-resource couplings (why decomposition needs coupling parameters)

The sub-models are *not* independent. The couplings, and how the staged pipeline
handles each, are the crux of the design:

| Coupling | Between | Nature | Handling |
|---|---|---|---|
| C1 | PHV (R1) ↔ exact IXBar (R6) | the container a field lands in fixes which crossbar bytes/groups a table can use for its key | M1 emits, per field slice, the **set of crossbar-reachable bytes**; M2 consumes it as a parameter `xbar_byte(t,slice)`. If M2 is infeasible, **feedback** re-runs M1 with an added constraint (Doc 05 §5). |
| C2 | PHV (R1) ↔ VLIW ALU (R11) | operands of an ALU must be reachable from the writing container's group | M1 enforces P11 using the action-source graph (parameter from M0), so M3 never sees an illegal source. |
| C3 | Table stage (R2) ↔ memory (R3–R5) | stage capacity is exactly the sum of placed tables' RAM demand | Solved **inside** M2 (same model): demand vector `d[t]` per table, budget per stage. |
| C4 | Dependencies (T3) ↔ PHV live ranges (P4) | overlay (bit sharing) is only legal if live ranges proven disjoint, which depends on stage placement | M1 uses **conservative** live ranges from `FieldDefUse`/`fieldslice_live_range.cpp` (control-flow based, stage-independent). Physical-liverange overlay that needs stages is left to the existing `finalize_physical_liverange` pass (kept downstream). |
| C5 | Table stage (R2) ↔ action imem (R11) | actions of tables in a stage compete for 32 rows | M2 exports per-stage the set of (table,action) pairs; M3 solves the per-stage row/color packing. If M3 infeasible for a stage, feedback adds a "this set of actions cannot co-reside" cut to M2. |
| C6 | Attached ALUs (R9/R10) ↔ stage (R2) | counters/meters consume stage ALUs | Inside M2 (demand vector includes `stats_alus`, `meter_alus` from `StageUseEstimate`). |
| C7 | Hash (R8) ↔ exact ways (R3) | #ways changes RAM count and hash-bit usage | M2 chooses among precomputed **layout options** (`LayoutOption`, see Doc 04 §3) per table — each option is a discrete column with its own (srams, ixbar, hash) demand; one option selected per table. |

### 6.1 Coupling strategy summary

- **Intra-model couplings** (C3, C6, C7): handled by putting the resources in the
  same MILP (M2) and using per-table multi-option columns.
- **Forward couplings** (C1, C2, C4): upstream model emits a *parameter* the
  downstream model treats as fixed input — chosen so the upstream can always
  satisfy it (conservative).
- **Backward couplings** (C1 failure, C5): handled by **logic-based Benders /
  lazy cuts** — a downstream infeasibility produces a *no-good cut* added to the
  upstream model, which is re-solved (Doc 05 §5). Bounded iteration count with a
  fallback to the legacy allocator guarantees termination.

---

## 7. Constraint → model-size estimate

| Set | Typical magnitude (large program) |
|---|---|
| field slices `S` | 2k–8k |
| containers `C` | 224 (+112 T-PHV) |
| tables `T` | 100–400 (logical), 200–800 stage-tables |
| stages `G` | 12 or 20 |
| actions `A` | 300–1500 |

Naive monolithic binary vars ≈ |S|·|C| + |T|·|G| + |A|·|G|·rows ≈ 10⁶–10⁷.
Decomposition + symmetry reduction (Doc 03 §8) brings each sub-model to 10⁴–10⁵
binaries, well within CP-SAT's reach with the warm-starts of Doc 05.
