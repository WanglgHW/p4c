# Doc 07 — Implementation Plan, Milestones & Validation

This is the execution plan: file-by-file work breakdown, phase ordering,
dependencies, testing strategy, and acceptance criteria.

## 1. Phase plan

Status legend: ✅ done & tested in-tree · 🟡 partial · ⬜ not started.

| Phase | Goal | Status | Notes |
|---|---|---|---|
| **P0 Scaffolding** | buildable skeleton + APIs | ✅ | `libralloc` + unit test build; no solver dependency, `minizinc` probed at runtime. |
| **P1 Bridge in** | IR → `ModelInputs` | ✅ | `compiler_bridge.cpp::ingest()` compiles & runs on real IR. |
| **P2 M2 MAU** | table→stage IP | 🟡 | M2 builds & **CP-SAT solves to optimality** on test program; the **memory-realization write-back is the open item** (advisory mode, Doc 06 §4.1). |
| **P3 M1 PHV** | field→container MILP | 🟡 | `phv_model.cpp` core constraints implemented; not yet driven in-tree (M2-first consumes legacy PHV). |
| **P4 M3 VLIW** | action→imem MILP | 🟡 | `vliw_model.cpp` row-coloring implemented & solved; action-data bus packing TODO. |
| **P5 Couplings** | C1/C5 Benders loop, warm-start | 🟡 | loop in `resource_model.cpp`; warm-start TODO. |
| **P6 Hardening** | determinism, perf, dumps, CLI | 🟡 | `--use-ralloc` + logging done; per-flag tuning (`--ralloc-*`) TODO. |
| **P7 Eval** | optimality study | ⬜ | needs commit mode + benchmark suite. |

**The single highest-priority open item** is closing the *memory-realization
gap* (P2): after the MILP fixes stages/options, run a constrained
`Memories::allocate_all` / `IXBar::allocTable` to fill `TableResourceAlloc::
memuse`, so the placement can be committed (flip `RALLOC_COMMIT`) instead of
running advisory. Everything else already builds and the MILP solves optimally;
this is what blocks the model from actually driving the emitted binary.

P2 precedes P3 deliberately: table placement is where the legacy compiler most
often fails/backtracks, so M2 delivers value first, while M1 initially consumes
the *legacy* PHV result as a fixed input (the coupling C1 parameter is then read
from legacy PHV). This is the integration that ships today.

### 1.1 Verified results (this build)

- Builds clean against real bf-p4c headers with **no solver library** to link;
  `ralloc_bridge` links into `p4c-barefoot`.
- On a 2-table TNA program: `ralloc: MILP solved — 1 stage(s), 3 table(s)`, with
  MiniZinc/CP-SAT reporting a proven-optimal solution (`==========`) for M2 and M3.
- `--use-ralloc` output `.bfa` byte-identical to baseline except `run_id`
  (no regression); fallback-on-exception verified. See `doc/MANUAL.md`.
  (The optimality numbers were first measured with the SCIP edition; the MiniZinc
  edition solves the identical formulation.)

## 2. File-by-file work breakdown

```
model-minizinc/include/ralloc/
  device_spec.h      P0   constants mirror bf-p4c specs (single source via static_assert bridge)
  model_types.h      P0   ModelInputs / ModelResults POD structs (Doc 04/06)
  linear_model.h     P0   solver-agnostic LinearModel (vars, rows, objective)
  resource_model.h   P0   MAIN public API (ResourceModel, SolveOptions, SolveResult)
  phv_model.h        P3   PhvModelBuilder
  mau_model.h        P2   MauModelBuilder
  vliw_model.h       P4   VliwModelBuilder
  minizinc_solver.h  P0   SolverBackend + MiniZincBackend (OR-Tools CP-SAT)
  compiler_bridge.h  P1   CompilerBridge (ingest/writeBack/validate)

model-minizinc/src/
  model/phv_model.cpp     P3
  model/mau_model.cpp     P2
  model/vliw_model.cpp    P4
  model/resource_model.cpp P5  (orchestration, coupling loop, warm-start)
  solver/minizinc_solver.cpp P2
  solver/linear_model.cpp P0  (LinearModel helpers, .mzn + .lp export)
  bridge/compiler_bridge.cpp P1
  CMakeLists.txt          P0
```

## 3. Build integration

- `model-minizinc/CMakeLists.txt` builds `libralloc` (core, no bf-p4c deps) and
  `libralloc_bridge` (links IR). There is **no solver library** to find or link —
  `MiniZincBackend` shells out to `minizinc` at runtime.
- Hook into the top-level build by adding `add_subdirectory(model-minizinc)` and linking
  `libralloc_bridge` into the tofino backend target
  (`backends/tofino/bf-p4c/CMakeLists.txt`, target `tofinobackend`).
- `device_spec.h` constants are kept in sync with bf-p4c via a compile-time
  bridge file (`bridge/spec_check.cpp`) full of `static_assert(ralloc::NSRAM ==
  StageUse::MAX_SRAMS)` so a spec change in the backend breaks the build loudly.

## 4. Testing strategy

1. **Unit (no compiler, no solver):** feed JSON `ModelInputs` fixtures, build
   `LinearModel`, assert variable/row counts and `.mzn`/`.lp` text against goldens.
   Validates the formulas of Doc 03 directly (`test/test_minizinc_export.cpp`).
2. **Solver unit (MiniZinc/CP-SAT):** small hand-built instances (like Doc 03 §6)
   with known optimum; assert objective + a valid assignment. Self-skips when
   `minizinc` is not on `$PATH`.
3. **Bridge tests:** run `CompilerBridge::ingest` on a curated set of `.p4`
   programs from `testdata/` and snapshot `ModelInputs`.
4. **End-to-end:** compile the Tofino test suite with `--use-ralloc`; require
   (a) every program legacy compiles also compiles, (b) constraint self-check
   passes, (c) stage/power/PHV objective ≤ legacy. Compare emitted assembly via
   the existing `bf-asm` path.
5. **Optimality study:** on small programs, also build the fused model (Doc 03 §9)
   and report the decomposition's optimality gap.
6. **Performance/regression:** track solve time per program in CI; budget guard.

## 5. Risk register

| Risk | Mitigation |
|---|---|
| Model too large/slow on big programs | decomposition + option pruning + time-box + fallback (Doc 05 §4) |
| Spec drift between model and backend | `static_assert` spec bridge (§3) |
| Coupling loop non-termination | iteration cap `K` + monotone no-good cuts + fallback (Doc 05 §6) |
| Hidden constraints not in our catalogue | self-validation reuses legacy checkers; fallback on any violation (Doc 06 §5) |
| MiniZinc availability in CI | runtime-only dependency; the `.mzn` export path + structural tests run with no solver installed |
| Determinism | fixed seed, single-thread default (Doc 05 §8) |

## 6. Acceptance criteria (definition of done)

- `--use-ralloc` compiles 100% of programs the legacy path compiles, with
  byte-stable output across runs.
- On the benchmark set, median **stages used ≤ legacy** and **no program uses more
  stages**; power not worse; PHV containers ≤ legacy.
- All model formulas in Doc 03 are covered by unit tests against goldens.
- No path can emit an allocation failing `validate_allocation.cpp`.

## 7. Sequencing summary

```
P0 ──► P1 ──► P2 ──► P3 ──► P4 ──► P5 ──► P6 ──► P7
       (bridge) (MAU)  (PHV)  (VLIW)(couple)(harden)(eval)
```
M2 (P2) is the critical path to first value; everything else layers on top with
the fallback contract ensuring safety at every step.
