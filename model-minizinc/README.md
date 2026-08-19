# ralloc — Tofino Resource Allocation via MiniZinc + OR-Tools

A research/engineering project that replaces (or augments) the greedy +
backtracking resource allocators in the Tofino backend (`backends/tofino/bf-p4c`)
with a **constraint/integer-programming** model expressed in **MiniZinc** and
solved by **Google OR-Tools CP-SAT**, then writes the optimal allocation back
into the compiler so the remaining stages proceed unchanged.

This is the MiniZinc edition of `model/` (which uses the SCIP C API). The
solver-agnostic model core is unchanged; only the backend differs: the same
`LinearModel` is serialised to a `.mzn` file (`LinearModel::toMiniZincString`)
and handed to the `minizinc` CLI with a CP-SAT FlatZinc backend. Because every
ralloc variable is binary and all coefficients are integral, the problem is a
pure integer program — exactly what CP-SAT solves natively. MiniZinc runs as an
**external process**, so there is no build- or link-time solver dependency;
availability is a runtime probe of the `minizinc` binary.

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
| `doc/05_minizinc_integration.md` | MiniZinc + OR-Tools CP-SAT encoding, decomposition, coupling cuts, determinism |
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
  linear_model.h     solver-agnostic MILP + .lp / .mzn export
  phv_model.h        M1 builder
  mau_model.h        M2 builder
  vliw_model.h       M3 builder
  minizinc_solver.h  SolverBackend + MiniZincBackend (OR-Tools CP-SAT)
  compiler_bridge.h  IR ingest / write-back
  model_json.h       JSON I/O for the ModelInputs/ModelResults/ResumeBundle seam
  ralloc_model_pass.h  RallocModelPass — the bf-p4c hosting pass
src/
  model/             builders + facade + device spec + model_json
  solver/            LinearModel + MiniZinc backend
  bridge/            compiler glue + spec_check + RallocModelPass
  tool/              ralloc-solve standalone solver (model_input.json -> model_out.json)
test/                structural unit tests (no solver, no compiler)
```

## Build (standalone, no compiler)

```bash
cmake -S model-minizinc -B model-minizinc/build
cmake --build model-minizinc/build
ctest --test-dir model-minizinc/build    # runs ralloc_unit (no solver needed)
```

There is no build-time solver dependency. To actually solve, install MiniZinc
with an OR-Tools CP-SAT backend and put `minizinc` on `$PATH`:

```bash
export RALLOC_MINIZINC=minizinc          # binary (default: minizinc)
export RALLOC_MINIZINC_SOLVER=cp-sat     # FlatZinc solver id/tag (default: cp-sat)
```

Without a `minizinc` binary the core still builds; the solver becomes a `.mzn`
exporter and the in-compiler path falls back to the legacy allocator.

## In-tree build (already wired)

The integration is already committed in `backends/tofino/bf-p4c`:

- `CMakeLists.txt` builds a `ralloc_bridge` static library from the
  `model-minizinc/` sources (inheriting `tofinobackend`'s include environment +
  generated IR headers), links it into `tofinobackend`, and defines
  `BFP4C_HAVE_RALLOC=1`. There is no solver library to find or link — the pass
  shells out to `minizinc` at runtime; without it on `$PATH` the solver degrades
  to `.mzn` export and the pass always falls back.
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

The solver can also run as a **separate process** from the compiler, handing off
via three JSON files (see `doc/08_decoupled_flow.md`):

```bash
P=build/backends/tofino/bf-p4c/p4c-barefoot
$P --target tofino --arch tna -I build/p4include --ralloc-emit  /tmp/io prog.p4   # -> model_input.json + ir_middle.json, then stops
model-minizinc/build/ralloc-solve /tmp/io/model_input.json -o /tmp/io/model_out.json  # MiniZinc/CP-SAT runs HERE only
$P --target tofino --arch tna -I build/p4include --ralloc-resume /tmp/io prog.p4 -o /tmp/out  # consumes both, finishes
```

This makes the solver independently buildable (`ralloc-solve`) and sidesteps the
solver-under-p4c-GC re-entrancy hazard. Verified end-to-end on
`testdata/dpvs-l4LB/dpvs_l4lb.p4` (6 stages / 24 tables; resumed `.bfa`
byte-identical to baseline modulo `run_id`).

## Safety contract

The model is an **optional optimizer**: on any infeasibility, timeout, solver
absence, or write-back self-check failure it falls back to the legacy allocator
(Doc 06 §5). Enabling it can only improve the objective or be a no-op — it can
never make a previously-compilable program fail.

## Status — MiniZinc edition

This edition swaps the SCIP C-API backend for a MiniZinc + OR-Tools CP-SAT
backend. The solver-agnostic model core, the bf-p4c bridge, and the decomposition
are inherited unchanged from `model/`; only `src/solver/` and the `SolverBackend`
seam differ.

- The core library and `ralloc-solve` build with **no solver dependency**, and
  the structural unit tests (`ralloc_unit`, `ralloc_json_test`) pass.
- `LinearModel::toMiniZincString()` emits the MAU (M2) and VLIW (M3) integer
  programs as `.mzn`; `MiniZincBackend` runs `minizinc --solver cp-sat`, parses
  the `v<i>=<value>` solution lines back, and maps MiniZinc's
  `==========` / `=====UNSATISFIABLE=====` / `=====UNKNOWN=====` markers onto
  `Optimal` / `Infeasible` / `TimeoutNoSolution`.
- The in-tree wiring (`--use-ralloc`, `RallocModelPass`, ingest/write-back/
  self-check) is the same as the SCIP edition; the pass still runs in **advisory
  mode** and falls back to the legacy allocator on any
  infeasibility/timeout/exception/missing-solver.

The end-to-end TNA results quoted in `model/`'s README were measured with the
SCIP backend; re-run with a `minizinc`/CP-SAT install on `$PATH` to reproduce
them here.

**Mode:** the pass runs in **advisory mode** today — it solves and logs the
optimal placement, then lets the legacy allocator emit the binary (so it is a
proven no-op on output). Committing the MILP placement needs a constrained
detailed-memory realization step and is gated behind `RALLOC_COMMIT`; see
`doc/MANUAL.md` §6 and Doc 06 §4 / Doc 07 P2.
