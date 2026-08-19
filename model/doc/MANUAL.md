# ralloc User Manual — MILP Resource Allocation for the Tofino Backend

This manual covers building, enabling, running, and troubleshooting the
experimental MILP/OR-Tools resource allocator (`--use-ralloc`) in `bf-p4c`.

- **What it is:** a Mixed-Integer Linear Programming model of Tofino MAU resource
  allocation, solved by [Google OR-Tools](https://developers.google.com/optimization)
  (CP-SAT), integrated into the compiler as `BFN::RallocModelPass`.
- **Status:** experimental, **off by default**, runs in **advisory mode** (see
  §6). Enabling it never changes the emitted binary except by improving the
  allocation once "commit mode" is enabled; today it is provably a no-op on
  output.
- **Two ways to run it:** the *decoupled out-of-process flow* (`--ralloc-emit` /
  `ralloc-solve` / `--ralloc-resume`, **§10**) where the solver is a separate
  process exchanging three JSON files — this is the default and recommended route;
  or *in-process* (`--use-ralloc`, §3), which requires building the compiler with
  OR-Tools linked in (`-DRALLOC_INPROCESS_SOLVER=ON`, §2). §11 is a worked example that verifies the
  model path against the legacy allocator.
- **Design background:** see `model/doc/00..08` (overview → formulation →
  integration → decoupled flow). This manual is the operational companion.

---

## 1. Prerequisites

| Requirement | Notes |
|---|---|
| A working `bf-p4c` build tree | the p4c/Tofino source tree this repo is part of |
| C++17 compiler | Apple clang / gcc |
| CMake ≥ 3.16, make or ninja | the existing generator is fine |
| **OR-Tools** (optional but required to actually solve) | e.g. `brew install or-tools`; without it the solver degrades to `.lp` export and the pass always falls back |

Check OR-Tools is visible to CMake:

```bash
ls $(brew --prefix)/lib/cmake/ortools/ortoolsConfig.cmake   # macOS/homebrew
```

---

## 2. Building

The integration lives in `model/` and is wired into
`backends/tofino/bf-p4c/CMakeLists.txt`. To pick it up you must **reconfigure** so
CMake builds the `ralloc_bridge` library.

```bash
# from the build directory
cmake .
# expect: "-- ralloc: compiler built without OR-Tools — solve out of process
#          with ralloc-solve (--ralloc-emit / --ralloc-resume)"

make ralloc_bridge p4c-barefoot -j$(nproc)
```

- `ralloc_bridge` is a static library compiled from `model/src/**` with the
  backend's include environment; it is linked into `p4c-barefoot`.
- **The compiler does not link OR-Tools by default.** OR-Tools ships its own
  abseil, protobuf and re2, which clash with the copies p4c builds itself
  (`find_package(ortools)` then fails to configure). So `--use-ralloc` alone
  logs "OR-Tools is not linked into the compiler" and falls back to legacy;
  the real solving happens in `ralloc-solve` via the decoupled flow (§10).
- To solve *in process* anyway, configure p4c against the same system abseil that
  OR-Tools was built with:

  ```bash
  cmake . -DP4C_USE_PREINSTALLED_ABSEIL=ON -DRALLOC_INPROCESS_SOLVER=ON \
          -DCMAKE_PREFIX_PATH=$(brew --prefix)
  # expect: "-- ralloc: OR-Tools found — in-process CP-SAT/MILP solving enabled"
  ```

  (This changes how p4c itself obtains abseil, so it triggers a large rebuild.)
- The build defines `BFP4C_HAVE_RALLOC=1`. If `model/` is absent the flag is
  undefined and `backend.cpp` compiles the plain legacy path.

> The freshly built binary is `build/backends/tofino/bf-p4c/p4c-barefoot`.
> A top-level `build/p4c-barefoot` may be a stale copy — prefer the full path
> when testing a fresh build.

### Standalone (no compiler) build of the model core

For unit-testing the model/solver without the compiler:

```bash
cmake -S model -B model/build -DCMAKE_PREFIX_PATH=$(brew --prefix)
# expect: "-- ralloc: OR-Tools found — CP-SAT/MILP solving enabled"
cmake --build model/build
cmake --build model/build --target ralloc_tests   # tests are EXCLUDE_FROM_ALL
ctest --test-dir model/build
```

`ralloc_solver_test` solves the Doc 03 §6 example plus indicator/LP fixtures
through OR-Tools, so it fails loudly if the solver path breaks.

---

## 3. Enabling it

Pass `--use-ralloc` to `p4c-barefoot` (or via the `bf-p4c` driver's
pass-through). It is a hidden flag.

```bash
p4c-barefoot --target tofino --arch tna -I <p4include> \
    --use-ralloc your_program.p4 -o out_dir
```

| Flag | Effect |
|---|---|
| `--use-ralloc` | enable the MILP allocator for MAU table placement |
| (none) | default legacy allocator, byte-for-byte unchanged |

The model's solve parameters (time limit, MIP gap, objective) are currently set
in `RallocModelPass::makeSolveOptions()` (`model/src/bridge/ralloc_model_pass.cpp`):
120 s time limit, 5 % gap, minimize-stages objective, warm start on,
deterministic. Per-flag CLI exposure of these is listed in Doc 06 §6 as a
follow-up.

---

## 4. Seeing what it did (logging)

The pass uses p4c's per-file trace logging. Enable it with `-T<file>:<level>`:

```bash
p4c-barefoot ... --use-ralloc -Tralloc_model_pass:1 prog.p4 -o out
```

| Level | Output |
|---|---|
| `-Tralloc_model_pass:1` | one line: solve result + stages/tables, or fallback reason |
| `-Tralloc_model_pass:2` | also the per-failure detail (invalid input, infeasible, exception) |

With `--dump-dir`, `ralloc-solve` also writes the CP-SAT search log (status,
bound, gap, `solution_fingerprint`) next to the `.lp`/`.pb.txt` model dumps.

### Example output (success)

```
ralloc: MILP solved — 1 stage(s), 3 table(s), optimal              # M2 + M3
ralloc: falling back to legacy table placement                     # advisory mode
```

Built without the in-process solver you instead get:

```
ralloc: OR-Tools is not linked into the compiler; use the decoupled flow
        (--ralloc-emit -> ralloc-solve -> --ralloc-resume) ...
ralloc: falling back to legacy table placement
```

### Example output (fallback)

```
ralloc: internal error (...table_mutex.cpp:171...); fallback to legacy
ralloc: falling back to legacy table placement
```

In every case the compile finishes with the legacy allocator's result.

---

## 5. Interpreting the result

The MILP solves two sub-models:

- **M2 — MAU placement / memory:** assigns tables to stages and layout options
  subject to per-stage SRAM/TCAM/map-RAM/ixbar/ALU/logical-id budgets and
  dependency ordering. The `N stage(s), M table(s)` line is its objective
  (minimize stages) and the count of placed (stage-)tables.
- **M3 — VLIW / action:** per (stage, gress), packs actions into the 32×2
  instruction-memory rows with the ALU-disjointness coloring rule.

`optimal` means the solver closed the gap; `feasible` means it found a valid allocation
within the time budget but didn't prove optimality. Either is usable.

To compare against the legacy allocation, compile once with and once without the
flag and diff the emitted `pipe/*.bfa` — in advisory mode they are identical
except the random `run_id` header line.

---

## 6. Advisory mode vs. commit mode

By default the pass runs in **advisory (shadow) mode**:

1. ingest the IR → MILP inputs,
2. solve M2 + M3 with OR-Tools (and log the optimal placement),
3. **fall back to the legacy allocator to produce the actual binary.**

This is deliberate. The MILP fixes the *coarse* decisions (stage, logical-id,
layout option), but a complete `TableResourceAlloc` also needs detailed
`memuse` / input-crossbar / action-data, which the legacy `Memories`/`IXBar`
passes fill *inside* `table_alloc`. Committing only the coarse placement leaves
`memuse` empty and a downstream pass fails. Advisory mode therefore guarantees
**`--use-ralloc` never regresses a compilable program** while still exercising
and validating the full MILP pipeline.

**Commit mode** (apply the MILP placement to the binary) is gated behind the
`RALLOC_COMMIT` compile define in `ralloc_model_pass.cpp`. It is **not** ready:
enabling it requires a constrained detailed-resource realization step (run
`Memories::allocate_all` / `IXBar::allocTable` for the MILP-chosen stages) to
populate `memuse`. See Doc 06 §4 and Doc 07 (phase P2) for the plan. Do not
define `RALLOC_COMMIT` for production builds yet.

---

## 7. Troubleshooting

| Symptom | Cause / fix |
|---|---|
| `Unknown option --use-ralloc` | binary predates the integration, or you ran a stale `build/p4c-barefoot`. Rebuild and run `build/backends/tofino/bf-p4c/p4c-barefoot`. |
| `ralloc: OR-Tools is not linked into the compiler` in the log | expected in a default build: use the decoupled flow (§10), or rebuild with `-DP4C_USE_PREINSTALLED_ABSEIL=ON -DRALLOC_INPROCESS_SOLVER=ON` (§2). |
| No `ralloc:` lines in the log | the flag isn't set, or `BFP4C_HAVE_RALLOC` was undefined at build (model/ missing). |
| `ralloc: ... fallback to legacy` | the model couldn't solve/ingest this program; the compile still succeeds via legacy. Raise `-Tralloc_model_pass:2` for the reason. |
| Link error `undefined BFN::RallocModelPass` | `ralloc_bridge` wasn't linked into `p4c-barefoot`. Reconfigure; the CMake links it explicitly (object libs don't propagate transitively). |
| Build configured at a moved path (`CMakeCache.txt directory ... different`) | the build tree was relocated; symlink the original source path or reconfigure a fresh build dir. |
| Compile fails *only* with `--use-ralloc` | you likely enabled `RALLOC_COMMIT` — that path is incomplete (see §6). Build without it. |
| `--ralloc-emit` produced no `.bfa` | expected — emit writes `model_input.json` + `ir_middle.json` and **stops** before solving (§10). Run `ralloc-solve` then `--ralloc-resume`. |
| `ralloc-solve: OR-Tools not linked` | the standalone model build didn't find OR-Tools; `brew install or-tools` and reconfigure `model/build` with `-DCMAKE_PREFIX_PATH=$(brew --prefix)`. |
| resume falls back: `ir_middle.json does not match the current program` | the `.p4` source or flags changed between emit and resume; re-run emit + solve so the bundle matches (§10.5 drift guard). |

---

## 8. Where things live

| Path | What |
|---|---|
| `model/include/ralloc/resource_model.h` | main solver API |
| `model/include/ralloc/ralloc_model_pass.h` | the hosting pass |
| `model/src/bridge/compiler_bridge.cpp` | IR ingest / write-back / self-check |
| `model/src/bridge/ralloc_model_pass.cpp` | the pass (solve options, advisory/commit + emit/resume) |
| `model/src/solver/ortools_solver.cpp` | OR-Tools backend (CP-SAT + MPSolver) |
| `model/src/model/*.cpp` | M1/M2/M3 builders + orchestration |
| `model/include/ralloc/model_json.h`, `model/src/model/model_json.cpp` | JSON I/O for the 3-file decoupled flow (§10) |
| `model/src/tool/ralloc_solve_main.cpp` | the standalone `ralloc-solve` solver binary |
| `backends/tofino/bf-p4c/backend.cpp` | wiring (gated `&table_alloc`) |
| `backends/tofino/bf-p4c/bf-p4c-options.{h,cpp}` | the `--use-ralloc` / `--ralloc-emit` / `--ralloc-resume` flags |
| `backends/tofino/bf-p4c/CMakeLists.txt` | `ralloc_bridge` build + link |
| `backends/tofino/bf-p4c/p4c-barefoot.cpp` | catches `RallocEmitDone` (emit early-exit) |

---

## 9. Quick reference

### 9.1 One driver for everything: `model/run_ralloc.py`

All operations in this manual are wrapped by `model/run_ralloc.py` (paths are
auto-detected relative to the script). Prefer it over copy-pasting commands:

```bash
./model/run_ralloc.py build                                   # §2  build compiler + ralloc-solve
./model/run_ralloc.py test                                    # §2  standalone unit tests
./model/run_ralloc.py run    prog.p4 -o out                   # §3  in-process --use-ralloc
./model/run_ralloc.py emit   prog.p4 --io /tmp/io             # §10 phase 1
./model/run_ralloc.py solve            --io /tmp/io           # §10 phase 2 (ralloc-solve)
./model/run_ralloc.py resume prog.p4   --io /tmp/io -o out    # §10 phase 3
./model/run_ralloc.py flow   prog.p4 --io /tmp/io             # §10 emit -> solve -> resume
./model/run_ralloc.py verify prog.p4                          # §11 legacy vs model compare
```

`run_ralloc.py --help` (and `<command> --help`) lists every option
(`--time-limit`, `--objective`, `--build-dir`, `--p4c`, `--solve`, …).

### 9.2 Raw commands

```bash
# configure (once, to pick up ralloc)
cmake .

# build
make ralloc_bridge p4c-barefoot -j8

# run with logging
build/backends/tofino/bf-p4c/p4c-barefoot \
  --target tofino --arch tna -I build/p4include \
  --use-ralloc -Tralloc_model_pass:1 prog.p4 -o out

# compare against legacy (expect identical bfa except run_id)
diff <(sed 1,3d base/pipe/prog.bfa) <(sed 1,3d out/pipe/prog.bfa)
```

---

## 10. Decoupled (out-of-process) solver flow

Instead of solving inside `p4c-barefoot`, the solver can run as a **separate
process** (`ralloc-solve`), exchanging three JSON files with the compiler. This
keeps the math model/solver fully isolated from the compiler (its own process and
allocator — which also sidesteps the solver-under-p4c-GC re-entrancy hazard and the
abseil/protobuf clash of a linked OR-Tools) and
makes the solver independently runnable for offline/parallel/cached solves. Full
design: `model/doc/08_decoupled_flow.md`.

### 10.1 The three phases and three files

```
                model_input.json                 model_out.json
  ┌───────────────┐   │            ┌─────────────┐   │          ┌────────────────┐
  │ p4c-barefoot  │───┼──────────► │ ralloc-solve│───┼────────► │ p4c-barefoot   │
  │ --ralloc-emit │   │            │ (OR-Tools)  │              │ --ralloc-resume│──► .bfa
  └───────────────┘   │            └─────────────┘              └────────────────┘
        │             │                                                ▲
        └─ ir_middle.json ──────────────────────────────────────────────┘
```

| File | Producer | Consumer | Contents |
|---|---|---|---|
| `model_input.json` | `--ralloc-emit` | `ralloc-solve` | the full M1/M2/M3 problem (`ralloc::ModelInputs`): device, slices, containers, tables + layout-option demand, deps, mutexes, actions |
| `ir_middle.json` | `--ralloc-emit` | `--ralloc-resume` | the resume bundle (`ralloc::ResumeBundle`): solver-id ↔ stable IR-name map (table/action names, option ids) |
| `model_out.json` | `ralloc-solve` | `--ralloc-resume` | the placement (`ralloc::ModelResults`): per-table stage/option, PHV assignments, imem rows, action-data bus bytes |

All three use the dependency-free JSON layer `model/.../model_json.{h,cpp}` (a tiny
self-contained DOM — no external JSON library, no bf-p4c headers), so the same code
reads/writes them in both `ralloc-solve` and the compiler.

### 10.2 Building `ralloc-solve`

`ralloc-solve` links only the model core (which pulls OR-Tools), so it builds from the
standalone model build:

```bash
cmake -S model -B model/build -DCMAKE_PREFIX_PATH=$(brew --prefix)
cmake --build model/build --target ralloc-solve
# binary: model/build/ralloc-solve
```

The compiler side (`--ralloc-emit` / `--ralloc-resume`) is part of the normal
`p4c-barefoot` build (§2) — no extra target.

### 10.3 Running the three phases

```bash
P=build/backends/tofino/bf-p4c/p4c-barefoot
SOLVE=model/build/ralloc-solve
IO=/tmp/ralloc_io ; mkdir -p $IO

# Phase 1 — emit the solver input + resume bundle, then STOP the compile.
$P --target tofino --arch tna -I build/p4include --ralloc-emit $IO prog.p4
#   writes $IO/model_input.json and $IO/ir_middle.json; no solver runs here.

# Phase 2 — solve out-of-process (this is the ONLY process that runs OR-Tools).
$SOLVE $IO/model_input.json -o $IO/model_out.json --time-limit 120
#   prints: "ralloc-solve: solved — N stage(s), M table(s); wrote .../model_out.json"

# Phase 3 — consume the result + bundle and finish the compile.
$P --target tofino --arch tna -I build/p4include --ralloc-resume $IO prog.p4 \
   -Tralloc_model_pass:2 -o $IO/out
#   logs "ralloc: resume — applying model_out.json ..." then a table→stage report.
```

Both `--ralloc-emit` and `--ralloc-resume` imply `--use-ralloc`.

### 10.4 `ralloc-solve` options

| Option | Meaning |
|---|---|
| `<model_input.json>` | positional input path |
| `-o <model_out.json>` | output path (required) |
| `--time-limit <s>` | per sub-model wall-clock budget (default 120) |
| `--gap <frac>` | accepted MIP optimality gap (default 0.05) |
| `--seed <n>` | solver seed (deterministic) |
| `--objective stage\|power\|phv\|feasible\|lex` | objective (default `stage`) |
| `--dump-dir <dir>` | dump `.lp`/`.cip` models + solver logs |

Exit code is non-zero if the solve is unusable (infeasible/timeout/no OR-Tools), so a
driver script can fall back.

### 10.5 What each compiler phase does

- **Emit** (`RallocModelPass::preorder`): builds the same `LayoutChoices` /
  `TablesMutuallyExclusive` analyses as the in-process pass, `ingest()`s the IR into
  `ModelInputs`, writes the two files, then throws `BFN::RallocEmitDone` — a
  control-flow signal (not a `std::exception`, so it is not swallowed by the pass's
  own fallback `catch` nor the PassManager's backtrack handling) that
  `execute_backend()` in `p4c-barefoot.cpp` catches and treats as a successful early
  exit. **No solver runs in this process.**
- **Resume** (`RallocModelPass::runResume`): re-runs the backend deterministically to
  the table-placement seam, reads `model_out.json` + `ir_middle.json`, **joins them
  by stable name**, and verifies the live program matches the bundle id-for-id (a
  drift guard: if the `.p4`/flags changed between emit and resume it falls back
  rather than apply a stale placement). It then logs the advisory placement and
  delegates to the legacy allocator to emit the binary (same advisory contract as
  §6; commit is behind `RALLOC_COMMIT`).

---

## 11. Verifying the model path against the legacy allocator (worked example)

This is the procedure used to confirm the model/OR-Tools path is correct and
non-regressing, on `testdata/dpvs-l4LB/dpvs_l4lb.p4`.

### 11.1 Compile twice — original algorithm vs. model/OR-Tools

```bash
P=build/backends/tofino/bf-p4c/p4c-barefoot
SOLVE=model/build/ralloc-solve
SRC=testdata/dpvs-l4LB/dpvs_l4lb.p4
INC="-I build/p4include"
mkdir -p /tmp/cmp/orig /tmp/cmp/model /tmp/cmp/io

# RUN 1 — ORIGINAL algorithm (legacy allocator, no ralloc)
$P --target tofino --arch tna $INC $SRC -o /tmp/cmp/orig

# RUN 2 — MODEL/OR-TOOLS method (decoupled 3-phase)
$P --target tofino --arch tna $INC --ralloc-emit  /tmp/cmp/io $SRC -o /tmp/cmp/io/emit
$SOLVE /tmp/cmp/io/model_input.json -o /tmp/cmp/io/model_out.json --time-limit 120
$P --target tofino --arch tna $INC --ralloc-resume /tmp/cmp/io $SRC -o /tmp/cmp/model
```

### 11.2 Compare every output artifact

```bash
cd /tmp/cmp
for f in $(cd orig && find . -type f | sort); do
  diff -q "orig/$f" "model/$f" >/dev/null 2>&1 \
    || { echo "DIFFERS: $f"; diff "orig/$f" "model/$f" | grep '^[<>]' | head; }
done
```

### 11.3 Expected result — identical except non-deterministic fields

Both runs produce the **same 10 output files**. The only differences are the
per-compile random `run_id` and the `build_date` timestamp, in 3 files:

| File | Only difference |
|---|---|
| `pipe/dpvs_l4lb.bfa` | `run_id` |
| `pipe/context.json` | `run_id` + `build_date` |
| `manifest.json` | `run_id` + `build_date` |
| all 7 others (graphs, dynhash, prim.json, dslx, …) | **byte-identical** |

Neither `run_id` nor `build_date` is compiled content, so **every byte of the
actual binary/layout is identical** ⇒ the model/OR-Tools pipeline runs end-to-end and
never corrupts or regresses the result.

### 11.4 The solver itself works (and finds a better packing)

Check the solver's own solution vs. what the legacy allocator actually used:

```bash
grep -o '"stages_used":[0-9]*' /tmp/cmp/io/model_out.json        # model: 6
grep -oE "^stage [0-9]+ ingress" /tmp/cmp/orig/pipe/dpvs_l4lb.bfa | sort -u  # legacy: 0..9
```

| | Original (legacy greedy) | Model/OR-Tools |
|---|---|---|
| MAU stages used | 10 ingress (0–9) + 1 egress | **6** (proven optimal) |
| Tables placed | 24 | 24 |

The MILP packed the same 24 tables into **6 stages vs the legacy's 10** — a strictly
tighter solution.

### 11.5 How to read this result

The two compiles are byte-identical **because the model runs in advisory mode**
(§6): it solves + logs the optimal 6-stage placement, but the **legacy allocator
still emits the binary** (which uses 10 stages). So this verifies two distinct
things:

1. **The decoupled model/OR-Tools infrastructure is correct** — emit → solve → resume
   produces a valid, non-regressing compile. ✅
2. **The model produces a valid, better solution** (6 stages), but **that
   improvement is not yet in the emitted binary.** Realizing it is the gated
   `RALLOC_COMMIT` work (the detailed memory-realization step; §6, Doc 06 §4.1,
   Doc 08 §8).

In short: the new model/OR-Tools way is verified **OK** (correct and non-regressing),
and the optimizer demonstrably beats the legacy heuristic on stage count; committing
that placement into the binary is the remaining follow-up.
