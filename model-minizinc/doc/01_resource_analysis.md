# Doc 01 — Tofino Programmable Resource Analysis

This document enumerates every physical resource the Tofino backend allocates,
the **exact device specification numbers** (with the source file/line they are
read from), and the allocation algorithm `bf-p4c` uses today. All numbers below
are for **Tofino-1**; Tofino-2 (JBay) deltas are noted. They are the constants
the MILP must use as right-hand-sides.

> Spec sources: `bf-p4c/specs/device.h`, `bf-p4c/specs/mau_spec.{h,cpp}`,
> `bf-p4c/specs/phv_spec.cpp`, `bf-p4c/mau/memories.h`,
> `bf-p4c/mau/resource_estimate.h`, `bf-p4c/mau/instruction_memory.{h,cpp}`.

---

## 1. The PISA / Tofino pipeline at a glance

```
 Ingress:  Parser → MAU[0..N-1] → Deparser
 Egress :  Parser → MAU[0..N-1] → Deparser
 N (Tofino) = 12 stages,  N (Tofino2-U) = 20,  N (Tofino2-M) = 12.
```

Both gresses (ingress/egress) **share the same physical pipe** on Tofino
(`getThreadsSharePipe()==true`), so per-stage resources are shared between
ingress and egress tables placed in that stage.

Data carried through the pipe lives in the **PHV** (Packet Header Vector). Each
MAU stage reads PHV via the **input crossbar (IXBar)** into match (exact/ternary)
units and hash units, looks up **SRAM/TCAM** memories, drives **VLIW action
ALUs** (one per PHV container) parameterized by **action-data** fetched over the
**action-data bus**, and writes results back to the PHV.

---

## 2. PHV — Packet Header Vector

The PHV is the register file flowing through the pipeline. Allocation = assign
each **field slice** to a **container** + bit offset, honoring container type and
many packing/alignment rules.

### 2.1 Container inventory (Tofino-1)

From `TofinoPhvSpec` constructor, `bf-p4c/specs/phv_spec.cpp:367`:

| Class | PHV type | Width | #MAU groups × size | Total containers | Total bits |
|---|---|---|---|---|---|
| Normal | `B` | 8 b | 4 × 16 | 64 | 512 |
| Normal | `H` | 16 b | 6 × 16 | 96 | 1536 |
| Normal | `W` | 32 b | 4 × 16 | 64 | 2048 |
| **Normal subtotal** | | | | **224** | **4096** |
| Tagalong (T-PHV) | `TB/TH/TW` | 8/16/32 | 8 collections | 32+48+32 = 112 | 1024 |

- A **MAU group** is the crossbar-addressable unit: `B` has 4 groups of 16,
  `H` has 6 groups of 16, `W` has 4 groups of 16 (`numContainersPerGroup`,
  `phv_spec.cpp:379`). Containers in the same group share input-crossbar wiring,
  which is why MAU group is an allocation axis.
- **POV bits:** `numPovBits = 256` (`phv_spec.cpp:443`).
- **Tagalong collections:** `numTagalongCollections = 8` (`phv_spec.cpp:431`).
  T-PHV containers travel with the packet but **cannot be read/written in the
  MAU** — only parser/deparser. So a field used in the MAU cannot be in T-PHV.
- A `phv_scale_factor` option scales group counts (for studies / smaller virtual
  devices). The MILP reads the *effective* counts from the spec, never literals.

Tofino-2 (`JBayPhvSpec`) adds **mocha** and **dark** container kinds (restricted
read/write) and different group counts; the model treats "kind" as a per-container
attribute (Doc 03 §3.1).

### 2.2 Container "kinds" (Tofino-2 relevant)

`PHV::Kind`: `normal`, `tagalong`, `mocha`, `dark`.
- **mocha**: can be written only by full-container moves / a restricted ALU set;
  good for header fields that are merely passed through.
- **dark**: no ALU, no crossbar read; pure storage, used for live-range splitting.

### 2.3 Deparser groups

`deparserGroupSpec` (`phv_spec.cpp:439`): `B`→(8,8), `H`→(12,8), `W`→(16,4).
Fields emitted together by the deparser must respect these grouping rules.

### 2.4 Today's algorithm

`AllocatePHV` (`bf-p4c/phv/allocate_phv.cpp`) builds **SuperClusters** of field
slices that must be co-allocated (`make_clusters.cpp`), then does a
**greedy best-fit search with backtracking** scored by `AllocScore`
(`allocate_phv.h:259`). Constraints live in `action_phv_constraints.cpp`,
`parde_phv_constraints.cpp`, `table_phv_constraints.cpp`,
`constraints/`. This is the largest single heuristic in the backend.

---

## 3. MAU stage — global per-stage budgets

A logical table is placed into a **stage**; within the stage it consumes a slice
of every resource type. The per-stage budgets (`StageUse`, `bf-p4c/specs/mau_spec.h:33`
and `StageUseEstimate::max()`, `resource_estimate.h:91`):

| Resource | Constant | Value (Tofino) | Source |
|---|---|---|---|
| Logical table IDs / stage | `MAX_LOGICAL_IDS` | **16** | `mau_spec.h:34` |
| SRAM units / stage | `MAX_SRAMS` | **80** (8 rows × 10 cols) | `mau_spec.h:35`, `memories.h:41-49` |
| TCAM units / stage | `MAX_TCAMS` | **24** (12 rows × 2 cols) | `mau_spec.h:36` |
| Map RAMs / stage | `MAX_MAPRAMS` | **48** (8 rows × 6 cols) | `mau_spec.h:37`, `memories.h:50` |
| Input-xbar bytes (exact) | `MAX_IXBAR_BYTES` | **128** (8 grp × 16 B) | `mau_spec.h:38` |
| Ternary ixbar groups | `MAX_TERNARY_GROUPS` | **12** | `mau_spec.h:39` |
| Stats ALUs / stage | `MAX_STATS_ALUS` | **4** | `resource_estimate.h:33`, `memories.h:66` |
| Meter ALUs / stage | `MAX_METER_ALUS` | **4** | `resource_estimate.h:32`, `memories.h:67` |
| Local ternary-indirect / stage | `MAX_LOCAL_TINDS` | **16** | `resource_estimate.h:34` |
| Gateways per row | `GATEWAYS_PER_ROW` | **2** (×8 rows = 16) | `memories.h:63` |
| Stages | `getNumStages()` | **12** (T1) / 20 (T2-U) | `device.h:225,302` |

`StageUseEstimate` (`resource_estimate.h:29`) is precisely the per-table resource
vector the backend already computes; the MILP reuses it as the per-table demand
vector `d[t]` (Doc 04 §3).

### 3.1 SRAM array geometry (`memories.h`)

- `SRAM_ROWS = 8`, `SRAM_COLUMNS = 10` ⇒ 80 RAMs/stage; each `SRAM_DEPTH = 1024`
  lines × 128 b.
- Left/right split: `LEFT_SIDE_COLUMNS = 4`, `RIGHT_SIDE_COLUMNS = 6`
  (`memories.h:45-46`). Some unit types are restricted to one side.
- `MAPRAM_COLUMNS = 6` ⇒ 48 map RAMs (used by counters/meters/selectors/idletime
  and for ternary-indirect color).
- `MAX_DATA_SWBOX_ROWS = 5`: the action/stats/meter data switchbox spans ≤ 5 rows.
- `MATCH_CENTRAL_ROW = 4`: home row for result distribution.

### 3.2 TCAM array geometry

- 12 rows × 2 columns = 24 TCAMs; `TCAM_DEPTH = 512` lines × 44 b
  (`mau_spec.cpp:96,98`, `memories.h:57`). Ternary key wider than 44 b spans
  multiple TCAM columns/rows; range match expands entries (see `RangeEntries`,
  `resource_estimate.h:212`).

### 3.3 Today's algorithm

`TablePlacement` (`bf-p4c/mau/table_placement.cpp`) is a **list-scheduler with
backtracking**: it orders tables by dependency depth (`DependencyGraph`,
`table_dependency_graph.cpp`), then for each table tries the earliest stage where
`StageUseEstimate` fits the remaining budget (`try_alloc_mem`, `try_alloc_all`).
`Memories::allocate_all` (`memories.cpp`) then does the detailed RAM placement.
Failure triggers `RejectReason` + backtrack (`table_placement.h:150`).

---

## 4. Input crossbar (IXBar)

The IXBar selects PHV bytes to feed match/hash/gateway/ALU units. `TofinoIXBarSpec`
(`mau_spec.h:122`, numbers in `mau_spec.cpp`):

| Sub-resource | Value | Source |
|---|---|---|
| Exact-match groups | **8** | `EXACT_GROUPS`, `mau_spec.h:124` |
| Exact bytes per group | **16** ⇒ 128 B total | `EXACT_BYTES_PER_GROUP` |
| Ternary groups | **12** | `ternaryGroups()` |
| Ternary bytes / group | **5** (big group **11**) | `TERNARY_BYTES_PER_GROUP` |
| Hash tables | **16** | `HASH_TABLES` |
| Hash groups | **8** | `HASH_GROUPS` |
| Hash index groups (10-bit) | **4** | `HASH_INDEX_GROUPS` |
| Hash single bits (top) | **12** | `HASH_SINGLE_BITS` |
| Max hash bits | **52** | `MAX_HASH_BITS` |
| Gateway search bytes | **4** | `GATEWAY_SEARCH_BYTES` |
| Hash-distribution units | **2** | `HASH_DIST_UNITS` |
| Hash-dist bits | **16** (expand **7**) | `HASH_DIST_BITS` |

A byte placed on the exact crossbar occupies a fixed (group, byte) ordinate;
the same PHV byte can be shared by tables that need it (read-sharing). The
crossbar is the tightest coupling between **PHV allocation** (which container a
field lands in fixes which crossbar byte it can use) and **table placement**.
Code: `bf-p4c/mau/tofino/input_xbar.cpp`, `ixbar_expr.cpp`.

### 4.1 Hash

Match keys that are not directly indexed are hashed into RAM addresses. Exact
match "ways" (`StageUseEstimate::MAX_WAYS = 8`, `resource_estimate.h:30`) are
hash-indexed RAM banks; the number of ways trades RAMs vs. fit probability. Hash
also feeds selectors, hash-distribution (for stats/meter addressing), and
dynamic hashing.

---

## 5. VLIW action engine

Each PHV container has its own **ALU**; one P4 `action` is compiled to a **VLIW
instruction word** = one instruction per ALU, stored as **one line of the
instruction memory (imem)**.

`TofinoIMemSpec` (`mau_spec.cpp:28-36`):

| Property | Value |
|---|---|
| imem rows / gress | **32** (`rows()`) |
| colors / row | **2** (`colors()`) |
| color bits | 1 |
| address bits | 6 (`IMEM_ADDRESS_BITS`, `memories.h:70`) |
| map-table entries | 8 (`map_table_entries()`; ≤ 8 hit actions get short codes) |

Key facts (`instruction_memory.h:53-83`):
- One **action ⇒ one imem row**. Per stage per gress there are **32 rows**.
- A row has **2 colors**: two actions may share a row **iff their sets of
  written ALUs are disjoint** (`instruction_memory.h:70-73`). This is a
  graph-coloring/packing constraint.
- Actions with identical opcodes can be **shared** across tables (e.g. `NoAction`)
  — same imem line reused (`instruction_memory.h:75`).
- ALU instruction sources are themselves constrained (`action_phv_constraints`):
  the operands of an ALU must come from PHV bytes reachable to that ALU's
  container group, action data, or hash — this couples back to PHV allocation.

### 5.1 Action data bus & action format

Action constants/immediates and table-supplied action data are fetched from
SRAM and driven onto the **action-data bus** as BYTE / HALF / FULL slots, then
aligned to ALU inputs by the **action format** (`action_data_bus.{h,cpp}`,
`action_format.cpp`, `ActionDataPerWord`, `resource_estimate.h:198`). The bus has
a fixed width of byte/half/word slots per stage; the **action format** assigns
each action-data field a byte offset (`Use::byte_offset`, `action_data_bus.h:96`).

---

## 6. Attached tables / stateful resources

Tables may have *attached* units (`IR::MAU::BackendAttached`) consuming dedicated
per-stage ALUs and map RAMs:

| Attached unit | ALU budget | Notes / source |
|---|---|---|
| Counter (stats) | `STATS_ALUS = 4` | `memories.h:66`; `CounterPerWord`, `resource_estimate.h:195` |
| Meter | `METER_ALUS = 4` | `memories.h:67` |
| Register / StatefulAlu | shares meter ALU | `StatefulAluSpec`, `device.h:78` |
| Selector | shares meter ALU + map RAM | `SelectorRAMLinesPerEntry`, `resource_estimate.h:205` |
| Idletime | map RAM | `IdleTimePerWord`, `resource_estimate.h:204` |
| Ternary-indirect (tind) | SRAM | `TernaryIndirectPerWord`, `resource_estimate.h:203` |
| Action data | SRAM | `ActionDataPerWord` |

`StatefulAluSpec` (`device.h:78-94`) bounds per-stage stateful capability
(`MaxSize`, `MaxDualSize`, `MaxInstructions`, `OutputWords`, …). These become
capacity constants for the meter-ALU constraints (Doc 02 §4).

---

## 7. Power / latency (objective inputs)

`MauPowerSpec` (`bf-p4c/specs/power_spec.h`, `bf-p4c/mau/mau_power.cpp`) bounds
total stage power and gives per-RAM-access energy. Table placement already
computes a power graph (`build_power_graph.cpp`, `determine_power_usage.cpp`).
The MILP can use these as (a) a hard constraint (≤ power budget) and/or (b) an
objective term. Latency = number of stages on the critical dependency path.

---

## 8. Summary: the allocation axes

| # | Resource | Decision variable theme | Per-stage budget |
|---|---|---|---|
| R1 | PHV container | field slice → (container, offset) | 224 normal containers |
| R2 | MAU stage / logical id | table → (stage, logical id) | 16 logical ids × N stages |
| R3 | SRAM | table words → RAM units | 80 / stage |
| R4 | TCAM | ternary table → TCAM units | 24 / stage |
| R5 | Map RAM | attached → map RAM | 48 / stage |
| R6 | Exact IXBar | match byte → (group, byte) | 128 B / stage |
| R7 | Ternary IXBar | ternary byte → group | 12 groups / stage |
| R8 | Hash | key → hash bits/ways | 52 bits, 8 groups / stage |
| R9 | Stats ALU | counter → ALU | 4 / stage |
| R10 | Meter ALU | meter/reg/sel → ALU | 4 / stage |
| R11 | VLIW imem | action → (row, color) | 32 rows × 2 / gress / stage |
| R12 | Action-data bus | adata field → byte slot | fixed slots / stage |

Doc 02 turns each axis into precise constraints and exposes the couplings that
force them to be solved jointly (or with explicit coupling parameters).
