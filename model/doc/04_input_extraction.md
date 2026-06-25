# Doc 04 — Extracting Model Inputs from the bf-p4c Midend IR

The MILP is only as correct as its parameters. This document maps every model
parameter (Doc 03) to the concrete backend data structure it is read from. All
reads happen **after** the backend has run instruction selection, dependency
analysis, and layout-choice generation, but **before** PHV allocation and table
placement — i.e. the model *replaces* those two passes.

## 1. Where in the pass pipeline

`bf-p4c/backend.cpp` builds the backend `PassManager` (the `addPasses({...})`
list, `backend.cpp:215`). The relevant prefix that we keep, in order:

```
CollectPhvInfo            → PhvInfo (fields, slices, widths)            backend.cpp:246
InstructionSelection      → IR::MAU::Action with primitives            backend.cpp:261
FindDependencyGraph       → DependencyGraph deps                       backend.cpp:263
... (alias, mutex, defuse) ...
PHV_AnalysisPass          ← REPLACED by M1                             backend.cpp:192
TableePlacement/MauAlloc  ← REPLACED by M2/M3
```

The new model is inserted as a pass `RallocModelPass` that runs where
`PHV_AnalysisPass` + `TablePlacement` currently run. It has read access to the
same context objects those passes receive:
`PhvInfo&, DependencyGraph&, FieldDefUse&, ClotInfo&, LayoutChoices&,
TablesMutuallyExclusive&, BFN_Options&` (see `Backend` members in `backend.h`).

## 2. M1 (PHV) parameters

| Param | Source object | Access |
|---|---|---|
| slice set `S`, width `w(s)` | `PhvInfo` / `PHV::Field::fieldSlices()` | iterate `phv.get_all_fields()` → `field->foreach_alloc`/`slices()` |
| `kindOK(s,c)`, type/size | `PHV::Type`, `Device::phvSpec()` | container inventory from `PhvSpec::physicalContainers()` |
| live range `lr(s)` | `FieldDefUse`, `fieldslice_live_range.cpp` | `PHV::LiveRange` per slice |
| `MUTEX(s,s')` | `PHV::FieldMutex` / `phv.field_mutex()` | symmetric bitmatrix |
| `CONF(s,s')` (pack conflict) | `ActionPhvConstraints` (`action_phv_constraints.h`) | `has_pack_conflict(fs1,fs2)` (`allocate_phv.h:126`) |
| `align(s)`, `byteAlign(s)` | pragmas + `PHV::Field` flags | `@pa_container_size`, `@pa_byte_pack`, deparser/checksum flags |
| kind restrictions (T-PHV/mocha/dark) | `phv_parde_mau_use.cpp` (`PhvUse`) | `uses.is_used_mau/parde(f)` |
| `srcReach(s,c)` (P11) | `ActionPhvConstraints` action-source graph | derived from `action_source_tracker.cpp` |
| `Ext(e)` extractor budgets (P12) | `PardeSpec` + `parser_extract_balance_score.h` | per parser state extraction sets |

Practical note: `PHV::Field::is_solitary()`, `no_pack()`, `is_tphv_candidate()`,
and `exact_containers()` are already-computed boolean attributes on
`PHV::Field` — they map 1-1 to the `kindOK`/`CONF`/`align` parameters.

## 3. M2 (MAU/memory) parameters — the layout-option columns

The single most important input is the per-table set of **layout options** with
their resource demand vectors. The backend **already computes these** today:

- `LayoutChoices` (`bf-p4c/mau/table_layout.{h,cpp}`) enumerates the legal
  `LayoutOption`s for each table (ways, width, packing, ternary vs. exact, action
  data placement).
- `StageUseEstimate` (`bf-p4c/mau/resource_estimate.{h,cpp}`) converts a
  `LayoutOption` + entry count into the demand vector:
  `logical_ids, srams, tcams, local_tinds, maprams, exact_ixbar_bytes,
  ternary_ixbar_groups, meter_alus, stats_alus, hash_bits_masked`
  (`resource_estimate.h:44-54`). **This is exactly `d[t,o]`.**

So M0 constructs `O(t)` by:
```cpp
for (table t : pipe) {
  attached_entries_t att = collect_attached(t);
  for (LayoutOption& lo : layoutChoices.get_layout_options(t)) {
    StageUseEstimate est(t, entries, att, &layoutChoices, /*prev_placed*/false,
                         gateway_attached, /*disable_split*/false, phv);
    O(t).push_back( demand_vector_from(est, lo) );   // → d[t,o]
  }
}
```
`stages_required()` (`resource_estimate.h:192`) gives `parts(t,o)` for split
tables. `MAX_WAYS=8`, `MAX_METER_ALUS=4`, etc. are the RHS constants (Doc 03 §1).

| Param | Source |
|---|---|
| `O(t)` options + `d[t,o]` | `LayoutChoices` + `StageUseEstimate` |
| `parts(t,o)`, `split(t)` | `StageUseEstimate::stages_required()` |
| `DEP`, gaps `g(b,a)` | `DependencyGraph` (`table_dependency_graph.h`); dep kind ∈ {MATCH, ACTION, CONTROL, ANTI} |
| control-flow order | `IR::MAU::TableSeq` next-table structure |
| `mutexTbl(t,t')` | `TablesMutuallyExclusive` (`backend.h`) |
| `gress(t)` | `t->gress` |
| `keyBytes(t,o)` (C1) | `IXBar` key analysis (`ixbar_expr.cpp`) + M1 container map |
| `pow(t,o)` | `mau_power.cpp` / `determine_power_usage.cpp` |
| budgets `NSRAM…` | `Device::*Spec()` / `StageUse` constants |

### 3.1 Dependency-gap derivation

From `DependencyGraph` edge types (`table_dependency_graph.h`):
- **MATCH dependency** (a reads what b writes into the match key): `g=1`
  (different stages, a after b).
- **ACTION dependency** (a's action input depends on b's action output via same
  ALU): handled by imem/`g≥1` if not resolvable; the graph already classifies
  reduced/avoidable action deps.
- **CONTROL / next-table**: `g=0` but ordering preserved.
- **ANTI / REVERSE**: `g=0`, no stage constraint, only same-stage exclusion if
  needed.

## 4. M3 (VLIW/action) parameters

| Param | Source |
|---|---|
| `A_kr` active actions per (stage,gress) | from M2 solution: actions of tables placed in (k, r) |
| `Wr(a)` written ALU/container set | `IR::MAU::Action` primitives → destination `PHV::Field` → container (from M1) |
| `share(a,a')` identical-opcode | `ActionAnalysis` (`action_analysis.cpp`); `NoAction` etc. |
| action-data fields, `slot(f)` | `ActionData::Format` (`action_format.cpp`), `ActionDataPerWord` |
| bus class / format offsets | `ActionDataBus::Use` (`action_data_bus.h`) |
| `StatefulAluSpec` caps | `Device::statefulAluSpec()` |

## 5. Ingestion implementation

The class `ralloc::CompilerBridge` (`model/include/ralloc/compiler_bridge.h`)
wraps all of the above behind a narrow interface so the model core has **no
dependency on bf-p4c headers** except through the bridge:

```cpp
ModelInputs in = bridge.ingest(pipe, phv, deps, defuse, clots,
                               layoutChoices, mutex, options);
```
`ModelInputs` is a plain-old-data struct (Doc 06) holding the sets and parameter
tables defined here. This keeps the solver core unit-testable from JSON fixtures
without linking the whole compiler (Doc 07 §4).

## 6. Validation of extracted parameters

Before solving, `CompilerBridge::validate(in)` checks invariants that catch
extraction bugs early:
- every referenced slice has ≥ 1 legal container (`Σ_c kindOK > 0`);
- every table has ≥ 1 layout option;
- demand vectors are componentwise ≤ `StageUseEstimate::max()`;
- dependency graph is a DAG (after anti-dep removal);
- total minimal demand per resource ≤ NSTAGE × budget (necessary feasibility).

A failed invariant is reported as a normal compiler error with the offending IR
node, and the backend falls back to the legacy allocator (Doc 06 §5).
