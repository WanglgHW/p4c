# Repository Guidelines

## Project Structure & Module Organization
Two-level map of the repository (major folders only):
```text
.
|-- .github/               # CI config (workflows/).
|-- backends/              # Backends.
|   |-- {bmv2,dpdk,ebpf,graphs,p4fmt,p4test,p4tools,tc,tofino,ubpf}/ # Targets.
|-- bazel/                 # Bazel build.
|-- build/                 # Local build output (generated).
|-- cmake/                 # CMake helpers.
|-- control-plane/         # Control-plane APIs.
|-- debian/                # Debian packaging.
|-- docs/                  # Docs.
|-- extensions/            # Extensions.
|-- frontends/             # Frontend stages.
|   |-- {common,p4,p4-14,parsers}/ # Frontend layers.
|-- ir/                    # IR definitions (.def files + hand-written nodes).
|   |-- static-ir/         # Pre-generated static IR (used when ENABLE_TOFINO=OFF).
|-- json_outputs/          # JSON output helpers.
|-- lib/                   # Shared libraries.
|-- midend/                # Midend passes.
|-- model/                 # MILP/OR-Tools resource allocator (ralloc, --use-ralloc) — see dedicated section.
|-- p4include/             # P4 headers.
|-- test/                  # Unit tests.
|-- testdata/              # Test inputs/outputs.
|   |-- {p4_14_*,p4_16_*,p4tc_*}/ # Test suites.
|-- tests/                 # Integration tests.
|-- tools/                 # Dev scripts.
```

## Build, Test, and Development Commands
- `mkdir -p build `
- `cmake -B build -DCMAKE_BUILD_TYPE=Release`: configure.
- `cmake --build build`: compile.
- `cmake --build build --target check`: run tests.


Optional tools:
- `cmake --build build --target clang-format cpplint black isort`: format/lint checks (`*-fix-errors` to fix).

## IR Generation Strategy (two modes, picked by `ENABLE_TOFINO`)
The `ir-generated` translation unit (the `IR::*` node classes) is produced one of
two ways, selected automatically in the top-level `CMakeLists.txt`:

- **`ENABLE_TOFINO=ON` → build-time generation.** The `tools/ir-generator`
  `irgenerator` tool parses every collected `.def` file (core IR **plus** the
  Tofino `.def` extensions under `backends/tofino/bf-p4c/ir/`) and emits
  `ir-generated.{h,cpp}` + `gen-tree-macro.h` into `${P4C_BINARY_DIR}/ir/` via the
  `genIR` target. This is **required** for Tofino — its `IR::BFN::*` / `IR::MAU::*`
  node classes exist only in those `.def` files and cannot be pre-generated.
- **`ENABLE_TOFINO=OFF` (bmv2 and the other open-source backends) → static IR.**
  The pre-generated, hand-split files in **`ir/static-ir/`** (core/frontend nodes
  only) are staged into `${P4C_BINARY_DIR}/ir/` at configure time and compiled
  directly. No `irgenerator` is built — these backends do not need the flex/bison
  IR-generator step, and their IR is identical to what they always built against.

Either way the sources land under `${P4C_BINARY_DIR}/ir/`, so `#include
"ir/ir-generated.h"` resolves identically regardless of mode. If you change an IR
`.def` file, the static copies in `ir/static-ir/` must be regenerated to match
(build once with `ENABLE_TOFINO=ON` and copy `build/ir/ir-generated*` across, or
keep `.def` edits Tofino-only).

## MILP/OR-Tools Resource Allocator — `model/` (`--use-ralloc`)
The fork's headline feature. It replaces (augments) the Tofino backend's classic
*greedy + backtracking + heuristic* physical-resource allocators with a single
**Mixed-Integer Linear Program** solved to (near-)optimality by **Google OR-Tools
(CP-SAT)**, then
writes the result back so the rest of the pipeline (`bf-asm`) is unchanged. The
legacy allocators are locally optimal at best, backtrack heavily, can fail on
feasible programs, and optimize no global objective; the model captures the
device constraints exactly and minimizes a real objective (stages, power, PHV
pressure). Full design lives in `model/doc/00..08` + `model/doc/MANUAL.md`;
`model/README.md` is the entry point.

### The math model (Doc 03 — `model/doc/03_model_formulation.md`)
Allocation is too large for one monolithic MILP, so it uses **staged
decomposition** mirroring the hardware dependency order. Each `Mi` is a
self-contained MILP linked by a few coupling parameters; the assignment cores are
**Binary ILP** (assignment/packing/coloring are inherently 0/1, capacities and
dependencies are linear ⇒ MILP, strictly stronger than pure CP for these
knapsack/assignment structures):
- **M0** — parameter ingestion (sets, costs) from the IR; not an optimization.
- **M1 PHV** (Binary ILP) — field slice → PHV container. Vars `x[s,c]`, bit-offset
  `p[s,c,o]`, container-used `u[c]`; constraints for assignment, kind/size
  legality, overlay/no-overlap, pack conflict, alignment, crossbar-group locality;
  objective minimizes containers used (+ tie-breaks). ~10⁴–10⁵ binaries.
- **M2 MAU + memory** (MILP, the most important sub-model) — table → stage,
  logical-id, layout option, SRAM/TCAM/mapRAM, input-crossbar bytes, hash, stats/
  meter ALUs, gateways. Var `s[t,o,k]` (table `t`, layout option `o`, stage `k`)
  with per-stage capacity rows (one per resource) and dependency/min-stage-gap
  rows; objective `W_stage·Σ useStage + W_pow·power + W_bal·spread` (lexicographic
  via `W_stage ≫ W_pow ≫ W_bal`). Demand vectors come from `StageUseEstimate`.
- **M3 VLIW / action** (Binary ILP, solved **per (stage, gress)** ⇒ tiny) — action
  → imem row+color, action-data-bus byte slots. Enforces the imem coloring rule
  (ALU-overlapping actions can't share a row).
- **M4** — write-back to bf-p4c data structures.

Device-spec constants (NSTAGE=12, NSRAM=80, NTCAM=24, NLID=16, …) live in
`include/ralloc/device_spec.h`, referenced symbolically so the model is
device-portable. An optional **global fused** M1∪M2∪M3 model exists as a
research/ground-truth mode (Doc 03 §9), not the default (size).

### The solver strategy (Doc 05 — `model/doc/05_ortools_integration.md`)
- **Solver-agnostic seam.** Builders emit an abstract `LinearModel` (vars, linear
  rows, indicator rows, objective); `OrToolsBackend` translates it into an
  OR-Tools **CP-SAT** model when every var is discrete and every row scales to
  integer coefficients (true for M1/M2/M3), else into **MPSolver** (SCIP/CBC/HiGHS
  MIP, big-M indicators). OR-Tools is **optional** (`find_package(ortools CONFIG)`):
  without it the backend degrades to an `.lp`/MPS exporter and the in-compiler path
  always falls back to legacy. `LinearModel`'s `.lp`/MPS export also enables
  cross-validation against HiGHS/Gurobi/CPLEX and solver-less unit tests.
- **Indicator rows are native** on the CP-SAT path (`Constraint::OnlyEnforceIf`),
  so Doc 03 §8 needs no big-M tuning.
- **Solve order:** M1 → M2 (coarse) → M3 per (k,r); exact RAM-cell placement is
  delegated to the legacy `Memories::allocate_all` unless `--ralloc-fine-memory`.
- **Anytime / time-boxed:** per-sub-model `max_time_in_seconds` +
  `relative_gap_limit`; CP-SAT returns the best incumbent in budget. No
  integer-feasible found ⇒ fall back.
- **Warm-start** each sub-model with the legacy allocator's solution
  (`CpModelBuilder::AddHint`) for a guaranteed incumbent and ~10× speedup.
- **Logic-based Benders coupling cuts:** an M3 (k,r) infeasibility becomes a
  no-good cut on M2 (those tables can't all share stage k); re-solve, capped at
  `K=8` iterations, else fall back. Guarantees termination + correctness.
- **Determinism:** `num_workers = 1` + fixed `random_seed` for byte-identical
  output (the search log's `solution_fingerprint` makes drift visible);
  `--ralloc-threads N` opts into parallel search at the cost of determinism.

### Safety contract — it can never break a compilable program
The model is a **strictly optional optimizer**. On any infeasibility, timeout,
solver absence, self-check failure, or exception it falls back to the legacy
allocator. `RallocModelPass` wraps the legacy `&table_alloc` and today runs in
**advisory mode** (solves + logs the optimal placement, legacy emits the binary ⇒
a proven no-op on output). Committing the MILP placement needs a detailed
memory-realization step gated behind the `RALLOC_COMMIT` compile define
(`model/src/bridge/ralloc_model_pass.cpp`). Verified end-to-end on
`testdata/dpvs-l4LB/dpvs_l4lb.p4` (6 stages / 24 tables; resumed `.bfa`
byte-identical to baseline modulo `run_id`).

### Code layout & build
- `model/include/ralloc/` — `resource_model.h` (facade), `device_spec.h`,
  `linear_model.h`, `phv_model.h`/`mau_model.h`/`vliw_model.h` (M1/M2/M3 builders),
  `ortools_solver.h` (`SolverBackend`/`OrToolsBackend`), `compiler_bridge.h`
  (IR ingest + write-back + self-check), `ralloc_model_pass.h`, `model_json.h`.
- `model/src/{model,solver,bridge,tool}/` — builders+facade / `LinearModel`+OR-Tools /
  compiler glue+`RallocModelPass`+`spec_check` / `ralloc-solve` standalone driver.
- **Standalone build (no compiler):** `cmake -S model -B model/build
  [-DCMAKE_PREFIX_PATH=/opt/homebrew]` then `cmake --build model/build`;
  `cmake --build model/build --target ralloc_tests` + `ctest --test-dir model/build`
  runs `ralloc_unit` + `ralloc_solver_test` + `ralloc_json_test`.
- **In-tree:** `backends/tofino/bf-p4c/CMakeLists.txt` builds a `ralloc_bridge`
  static lib (`BFP4C_HAVE_RALLOC=1`), linked into `tofinobackend`. Needs
  `ENABLE_TOFINO=ON`. OR-Tools is **not** linked into the compiler by default —
  it ships its own abseil/protobuf/re2, which collide with p4c's FetchContent
  copies — so in-process solving is opt-in via
  `-DP4C_USE_PREINSTALLED_ABSEIL=ON -DRALLOC_INPROCESS_SOLVER=ON`; otherwise
  `--use-ralloc` logs the reason and falls back, and real solves go through the
  decoupled flow below. Wiring: `--use-ralloc` flag in `bf-p4c-options.{h,cpp}`;
  the gated `&table_alloc` entry in `backend.cpp:~454` swaps in
  `BFN::RallocModelPass`.

### Decoupled (out-of-process) flow — Doc 08
OR-Tools runs as a separate process from the compiler, handing off via JSON files
(`--ralloc-emit dir` → `model_input.json` + `ir_middle.json` then stop; run
`model/build/ralloc-solve model_input.json -o model_out.json`; `--ralloc-resume
dir` consumes both and finishes). This keeps `ralloc-solve` independently
buildable and sidesteps both the solver-under-p4c-GC re-entrancy hazard and the
abseil/protobuf clash; it is the default route.

## Coding Style & Naming Conventions
- Follow the P4 coding standard philosophy and `.clang-tidy`.
- C++ uses `clang-format` and `cpplint`; Python uses `black` and `isort`.
- Prefer IR node casts via `node->to<Node>()`; use `node->checkedTo<Node>()` when `nullptr` is not acceptable. Avoid `dynamic_cast`.
- Main C++ dependency is Abseil; do not introduce new Boost dependencies.

## P4 Language Notes
- Follow the P4 language spec.
- `p4include/` has `core.p4` plus target models: `v1model.p4` (BMv2), `ebpf_model.p4`, `ubpf_model.p4`, `xdp_model.p4`, `pna.p4`, and `p4include/{bmv2,dpdk,tc}/{pna,psa}.p4`. Tofino uses `backends/tofino/bf-p4c/p4include/tna.p4`.

## Backend Guides
- See `backends/{bmv2,dpdk,ebpf,graphs,p4fmt,p4test,p4tools,tc,tofino,ubpf}/AGENTS.md` for backend-specific guidance.

## Testing Guidelines
- Run the full suite with `cmake --build build --target check` (additional `check-*` targets are defined in CMake files when present).
- Idiomatic filtered runs: `ctest --test-dir build -j<N> --output-on-failure -R <filter>` (use the relevant suite or backend filter).
- Expected outputs live under `testdata/*_outputs/`; refresh them with `P4TEST_REPLACE=1 cmake --build build --target check`.
- Pass compiler flags via `P4C_ARGS`, e.g. `P4C_ARGS="-Xp4c=MY_CUSTOM_FLAG" cmake --build build --target check`.

## Commit & Pull Request Guidelines
- Use DCO sign-off for every commit (`git commit --signoff`).
- Use a ~50-character summary plus a body explaining why/how and linking issues.
- Single-commit PRs inherit the message; multi-commit PRs should include a synopsis and be squashed on merge.
- Code review is required; tests and format/lint must pass.
- Install hooks to enforce formatting checks: `./tools/install_git_hooks.sh`.
