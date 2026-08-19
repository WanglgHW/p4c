# ralloc — Tofino Resource Allocation via MILP (OR-Tools)

A research/engineering project that replaces (or augments) the greedy +
backtracking resource allocators in the Tofino backend (`backends/tofino/bf-p4c`)
with a **Mixed-Integer Linear Programming** model solved by **Google OR-Tools**
(CP-SAT), then writes
the optimal allocation back into the compiler so the remaining stages proceed
unchanged.

## What it allocates

| Resource | Where in hardware | Model |
|---|---|---|
| PHV containers | packet header vector register file | M1 (Binary ILP) |
| MAU stages, logical ids, SRAM/TCAM/mapRAM, input crossbar, hash, stats/meter ALUs, gateways | match-action pipeline | M2 (MILP) |
| VLIW instruction memory rows/colors, action-data bus | action engine | M3 (Binary ILP) |

See `doc/` for the full analysis, formulation, and integration plan.

## Documentation (read in order)

| File | Phase |
|---|---|
| `doc/00_overview.md` | Goals, scope, decomposition strategy |
| `doc/01_resource_analysis.md` | Every Tofino resource + exact spec numbers + source locations |
| `doc/02_constraints_relations.md` | Constraint catalogue + inter-resource couplings |
| `doc/03_model_formulation.md` | **The MILP**: sets, parameters, variables, objective, every constraint formula |
| `doc/04_input_extraction.md` | How each parameter is read from the bf-p4c midend IR |
| `doc/05_ortools_integration.md` | OR-Tools/CP-SAT encoding, decomposition, warm-start, coupling cuts |
| `doc/06_compiler_interface.md` | Public API, pass insertion, write-back, fallback contract |
| `doc/07_implementation_plan.md` | Milestones, file-by-file plan, testing, risks |
| `doc/08_decoupled_flow.md` | **Out-of-process flow**: `ralloc-solve` + the 3 JSON files (`--ralloc-emit`/`--ralloc-resume`) |
| `doc/MANUAL.md` | **User manual** — build, enable, run, log, troubleshoot |

## Source layout

```
include/ralloc/
  resource_model.h   MAIN public API (ResourceModel facade)
  device_spec.h      Tofino resource constants (mirror bf-p4c specs)
  model_types.h      ModelInputs / ModelResults POD seam
  linear_model.h     solver-agnostic MILP + .lp export
  phv_model.h        M1 builder
  mau_model.h        M2 builder
  vliw_model.h       M3 builder
  ortools_solver.h   SolverBackend + OrToolsBackend (CP-SAT / MPSolver)
  compiler_bridge.h  IR ingest / write-back
  model_json.h       JSON I/O for the ModelInputs/ModelResults/ResumeBundle seam
  ralloc_model_pass.h  RallocModelPass — the bf-p4c hosting pass
src/
  model/             builders + facade + device spec + model_json
  solver/            LinearModel + OR-Tools backend
  bridge/            compiler glue + spec_check + RallocModelPass
  tool/              ralloc-solve standalone solver (model_input.json -> model_out.json)
test/                structural + solver unit tests (no compiler)
```

## Build (standalone, no compiler)

```bash
cmake -S model -B model/build -DCMAKE_PREFIX_PATH=/opt/homebrew   # where OR-Tools lives
cmake --build model/build
cmake --build model/build --target ralloc_tests
ctest --test-dir model/build             # ralloc_unit, ralloc_solver_test, ralloc_json_test
```

Without OR-Tools the core still builds; the solver becomes an `.lp` exporter and
the in-compiler path falls back to the legacy allocator.

## In-tree build (already wired)

The integration is already committed in `backends/tofino/bf-p4c`:

- `CMakeLists.txt` builds a `ralloc_bridge` static library from the `model/`
  sources (inheriting `tofinobackend`'s include environment + generated IR
  headers), links it into `tofinobackend`, and defines `BFP4C_HAVE_RALLOC=1`.
  OR-Tools is **not** linked into the compiler by default: it ships its own
  abseil/protobuf/re2, which collide with the copies p4c builds itself. Opt in
  with `-DP4C_USE_PREINSTALLED_ABSEIL=ON -DRALLOC_INPROCESS_SOLVER=ON` to solve
  in process; otherwise the pass falls back to legacy and the real solving
  happens out of process in `ralloc-solve` (see below).
- `bf-p4c-options.{h,cpp}` add the `--use-ralloc` flag (default off).
- `backend.cpp` gates the `&table_alloc` entry in the backend pass list: when
  `--use-ralloc` is set it runs `BFN::RallocModelPass`, which wraps the legacy
  `table_alloc` and transparently falls back to it on any failure. When the flag
  is off (or `BFP4C_HAVE_RALLOC` is undefined), the list is byte-for-byte the
  legacy `&table_alloc`.

`RallocModelPass` (Doc 06 §2) runs MILP MAU placement (M2) + VLIW (M3) over the
already-computed legacy PHV allocation (the Doc 07 §1 "P2-first" integration),
writes the placement back, self-checks it, and falls back on any
infeasibility/timeout/exception/missing-solver.

## Decoupled (out-of-process) flow

The solver runs as a **separate process** from the compiler (the default and
recommended route), handing off via three JSON files (see
`doc/08_decoupled_flow.md`):

```bash
P=build/backends/tofino/bf-p4c/p4c-barefoot
$P --target tofino --arch tna -I build/p4include --ralloc-emit  /tmp/io prog.p4   # -> model_input.json + ir_middle.json, then stops
model/build/ralloc-solve /tmp/io/model_input.json -o /tmp/io/model_out.json       # OR-Tools runs HERE only
$P --target tofino --arch tna -I build/p4include --ralloc-resume /tmp/io prog.p4 -o /tmp/out  # consumes both, finishes
```

This makes the solver independently buildable (`ralloc-solve`) and sidesteps both
the solver-under-p4c-GC re-entrancy hazard and the abseil/protobuf clash. Verified end-to-end on
`testdata/dpvs-l4LB/dpvs_l4lb.p4` (6 stages / 24 tables; resumed `.bfa`
byte-identical to baseline modulo `run_id`).

## Safety contract

The model is an **optional optimizer**: on any infeasibility, timeout, solver
absence, or write-back self-check failure it falls back to the legacy allocator
(Doc 06 §5). Enabling it can only improve the objective or be a no-op — it can
never make a previously-compilable program fail.

## Status — built & tested

The full pipeline is implemented, **builds against the real bf-p4c headers +
OR-Tools, and was tested end-to-end** on a TNA program (see `doc/MANUAL.md`):

- `--use-ralloc` is wired into `backend.cpp`; the pass ingests the real IR,
  builds the MILP, and **OR-Tools CP-SAT solves M2 (MAU placement) + M3 (VLIW)
  to proven optimality** (`ralloc-solve: solved — N stage(s), M table(s)`;
  in-process: `ralloc: MILP solved — N stage(s), M table(s)`).
- **No regression verified**: with the flag, the emitted `.bfa` is byte-for-byte
  identical to the baseline except the random `run_id`; without it, zero ralloc
  involvement.
- **Graceful fallback verified**: a `BUG_CHECK` during ingest is caught and the
  compile still succeeds via the legacy allocator.

Implemented and compiling in-tree: `compiler_bridge.cpp` (real IR
**`ingest()`** — M1 PHV from `PhvInfo`/`PhvSpec`/mutex+no-pack; M2 from an
`IR::MAU::Table` walk + `StageUseEstimate` demand + `DependencyGraph`; M3 from
`IR::MAU::Action` write-sets — plus **`writeBack()`** via direct `PhvInfo`
mutation + the `placementWriter()` `IR::Transform`, and **`selfCheck()`**
re-running `PHV::ValidateAllocation`), the `RallocModelPass` host pass, the
model builders, and the OR-Tools backend.

**Mode:** the pass runs in **advisory mode** today — it solves and logs the
optimal placement, then lets the legacy allocator emit the binary (so it is a
proven no-op on output). Committing the MILP placement needs a constrained
detailed-memory realization step and is gated behind `RALLOC_COMMIT`; see
`doc/MANUAL.md` §6 and Doc 06 §4 / Doc 07 P2.
