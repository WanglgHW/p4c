# Doc 08 — Decoupled (out-of-process) solver flow

This document describes the **file-based, multi-phase** integration that runs the
MILP/OR-Tools allocator as a **separate process** from `bf-p4c`, handing off through
three JSON files. It complements the in-process integration of Doc 06 (which is
retained for `--use-ralloc`).

## 1. Why decouple

The original integration links the solver into `p4c-barefoot` and solves
**in-process** inside `BFN::RallocModelPass`. Three problems motivated splitting
the solver out:

- **A linked MILP solver is unsafe under p4c's GC-overridden `operator new`.** A
  second in-process solve crashed inside the solver's internal allocation (with
  SCIP: papilo/rapidlearning via `GC_malloc`), which forced the in-process pass to
  solve only once and guard with `attempted_`. Running the solver in its **own
  process** (its own allocator, its own address space) removes the hazard entirely.
- **OR-Tools brings its own abseil/protobuf/re2.** p4c builds abseil and protobuf
  itself, so linking OR-Tools into `p4c-barefoot` does not even configure without
  switching p4c to the system libraries; in a separate binary the question does
  not arise (Doc 05 §1.2).
- **The model is meant to be an independent, separately buildable optimizer**
  (`model/include/ralloc/*` links no bf-p4c headers). A standalone solver binary
  makes that real and enables offline solving, caching, and parallel/remote solves.

## 2. The three phases and three files

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
| `model_input.json` | emit | `ralloc-solve` | `ralloc::ModelInputs` — the full M1/M2/M3 problem (device, slices, containers, tables+layout-option demand, deps, mutexes, actions). |
| `ir_middle.json`   | emit | resume | `ralloc::ResumeBundle` — the id ↔ stable-name map (`table_id`→table name, `action_id`→table/action name, option ids). The compiler-side data, beyond `model_input.json`, needed to map solver ids back onto live IR. |
| `model_out.json`   | `ralloc-solve` | resume | `ralloc::ModelResults` — the placement (PHV assignments, per-table stage/option, imem rows, action-data bus bytes). |

All three are serialized by the dependency-free JSON layer
`model/{include,src}/.../model_json.{h,cpp}` (a small self-contained DOM; no
external JSON library, no bf-p4c headers), so the same code reads/writes them in
both `ralloc-solve` and `ralloc_bridge`.

## 3. Commands

```sh
P=build/backends/tofino/bf-p4c/p4c-barefoot
SOLVE=model/build/ralloc-solve            # standalone, the only binary linking OR-Tools
IO=/tmp/ralloc_io

# Phase 1 — emit the solver input + resume bundle, then STOP the compile.
$P --target tofino --arch tna -I build/p4include --ralloc-emit $IO prog.p4

# Phase 2 — solve out-of-process (OR-Tools runs here, never in p4c-barefoot).
$SOLVE $IO/model_input.json -o $IO/model_out.json --time-limit 120

# Phase 3 — consume the result + bundle and finish the compile.
$P --target tofino --arch tna -I build/p4include --ralloc-resume $IO prog.p4 -o $IO/out
```

`ralloc-solve` options: `-o <out>`, `--time-limit <s>`, `--gap <frac>`,
`--seed <n>`, `--objective stage|power|phv|feasible|lex`, `--dump-dir <dir>`.

## 4. How each phase works

**Emit** (`--ralloc-emit <dir>`, `RallocModelPass::preorder`): builds the same
`LayoutChoices` / `TablesMutuallyExclusive` analyses as the in-process pass,
`ingest()`s the IR into `ModelInputs`, writes `model_input.json` and
`ir_middle.json` (from `CompilerBridge::buildResumeBundle`), then throws
`BFN::RallocEmitDone` — a control-flow signal (not a `std::exception`, so it is not
swallowed by the pass's own fallback `catch` nor the PassManager's backtrack
handling) that `execute_backend()` in `p4c-barefoot.cpp` catches and treats as a
successful early exit. No solver runs in this process.

**Solve** (`ralloc-solve`): reads `model_input.json`, runs `ResourceModel::solveMau`
then `solveVliw` (M2 over the legacy PHV, then M3), writes `model_out.json`. Exits
non-zero if the solve is unusable so a driver can fall back. This is the **only**
process that runs OR-Tools.

**Resume** (`--ralloc-resume <dir>`): re-runs the backend deterministically to the
table-placement seam, then `runResume()` reads `model_out.json` + `ir_middle.json`,
**joins them by stable name**, and verifies the live program matches the bundle
id-for-id (a drift guard — if the `.p4`/flags changed between emit and resume it
falls back rather than apply a stale placement). It then logs the advisory
placement and delegates to the legacy allocator to emit the binary.

## 5. Result use: advisory (unchanged from Doc 06 §4.1)

Resume consumes `model_out.json` in **advisory mode**: it validates and logs the
solver's placement, but the legacy detailed allocators (`Memories`/`IXBar`/…) still
realize the binary. This preserves the no-regression guarantee — committing the
model placement (filling `TableResourceAlloc::memuse`) is the separate
`RALLOC_COMMIT` realization-gap work (Doc 06 §4.1). The `runResume()` path is
already wired for commit behind `#ifdef RALLOC_COMMIT`.

## 6. Build targets

- `ralloc-solve` (`model/CMakeLists.txt`) — standalone executable, links **only**
  the `ralloc` core (which pulls OR-Tools). Built by the standalone model build
  (`cmake -S model -B model/build`).
- `ralloc_bridge` (`backends/tofino/bf-p4c/CMakeLists.txt`) — now also compiles
  `model_json.cpp`; the emit/resume code lives in `ralloc_model_pass.cpp`.
- `p4c-barefoot` — gets `BFP4C_HAVE_RALLOC` + the ralloc include dir so its TU
  compiles the `RallocEmitDone` catch.

## 7. Verified end-to-end (`testdata/dpvs-l4LB/dpvs_l4lb.p4`)

- Phase 1 produced a 175 KB `model_input.json` and a `ir_middle.json` with the real
  table/action names.
- Phase 2: `ralloc-solve` solved to optimality out-of-process — **6 stages,
  24 tables**.
- Phase 3 consumed both files, logged the table→stage placement, and emitted the
  `.bfa`, which is **byte-identical to a baseline (non-ralloc) compile** modulo
  `run_id`.
- `ralloc_json_test` asserts `ModelInputs`/`ModelResults`/`ResumeBundle` JSON
  round-trips.

## 8. Status & next steps

- The compiler is now built **without** OR-Tools by default; the in-process
  `--use-ralloc` path (Doc 06) is retained but needs
  `-DRALLOC_INPROCESS_SOLVER=ON` (Doc 05 §1.2), and logs a pointer to this flow
  when the solver is absent. The decoupled flow is the supported route.
- `ir_middle.json` currently carries the id↔name bundle (sufficient for advisory
  resume, which re-derives the IR by recompiling deterministically). A future,
  recompile-free resume would also serialize the backend `IR::BFN::Pipe`
  (`JSONGenerator`/`JSONLoader`) and the PHV allocation.
- Commit mode (real write-back from `model_out.json`) is gated behind
  `RALLOC_COMMIT`, blocked on the memuse-realization work (Doc 06 §4.1).
