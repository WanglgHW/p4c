# Doc 06 — Compiler Interface (API, Insertion, Write-Back, Fallback)

This document specifies how the model integrates with `bf-p4c`: the public C++
API (`model-minizinc/include/ralloc/resource_model.h`), the pass that hosts it,
how solver results are written back into the backend's native structures, and the
fallback contract that guarantees the model can never regress compilability.

## 1. Design principle: a narrow, replaceable seam

The model is inserted at exactly one seam — the PHV-allocation + table-placement
boundary — and communicates with the rest of the compiler through **plain POD
structs** (`model-minizinc/include/ralloc/model_types.h`):

```
ModelInputs    (compiler → model)   : sets + parameters of Doc 04
ModelResults   (model → compiler)   : the allocation decisions
ResumeBundle   (compiler → compiler): solver-id ↔ stable-IR-name map, so a result
                                       computed out-of-process can be re-attached
```

Neither the model core nor the MiniZinc backend includes any bf-p4c IR header. Only
`compiler_bridge.{h,cpp}` (which *does* include IR headers) translates between IR
and these PODs. A dependency-free JSON layer, `model_json.{h,cpp}`
(`writeModelInputs`/`readModelInputs`, `writeModelResults`/`readModelResults`,
`writeResumeBundle`/`readResumeBundle`, + `*File` wrappers), serializes the same
PODs so the seam works **in-process** or **across processes** (Doc 08). This keeps
the optimizer independently buildable, testable, and runnable as a standalone tool.

> **Implementation status (as built & tested).** Implemented and verified in-tree —
> see `doc/MANUAL.md`. The pass is an `IR::Transform` **and** `P4::Backtrack`
> (`BFN::RallocModelPass`, `model-minizinc/src/bridge/ralloc_model_pass.cpp`), gated by
> `--use-ralloc`, that replaces the `&table_alloc` entry in `backend.cpp`'s pass
> list. It runs **M2 + M3 over the legacy PHV allocation** (the "P2-first"
> integration, not full `solve()`), in **advisory mode** (§4.1, §5): it solves +
> logs the optimal placement, then delegates to the legacy allocator. The shipped
> constructor is
> `RallocModelPass(const BFN_Options&, PhvInfo&, DependencyGraph&, FieldDefUse&,
> ClotInfo&, TablesMutuallyExclusive&, P4::Visitor* fallback)`. Three run modes are
> selected by `BFN_Options` (§2): in-process solve (`--use-ralloc`), out-of-process
> **emit** (`--ralloc-emit`), and out-of-process **resume** (`--ralloc-resume`).

## 2. The hosting pass and its calling point

```cpp
// model-minizinc/include/ralloc/ralloc_model_pass.h
class RallocModelPass : public P4::Transform, public P4::Backtrack {
 public:
  RallocModelPass(const BFN_Options&, PhvInfo&, DependencyGraph&, FieldDefUse&,
                  ClotInfo&, TablesMutuallyExclusive&, P4::Visitor* fallback);
  const IR::Node* preorder(IR::BFN::Pipe*) override;        // ingest → (emit|resume|solve) → fallback
  bool backtrack(P4::Backtrack::trigger&) override;          // delegate to wrapped table_alloc
  bool never_backtracks() override;
};
```

**Calling point.** `backends/tofino/bf-p4c/backend.cpp` swaps the single
`&table_alloc` entry in the backend pass list for the wrapper when ralloc is on
(`#if defined(BFP4C_HAVE_RALLOC)`):

```cpp
options.use_ralloc
    ? static_cast<Visitor *>(new BFN::RallocModelPass(options, phv, deps, defuse,
                                                       clot, mutex, &table_alloc))
    : static_cast<Visitor *>(&table_alloc),
```

So the pass receives the post-PHV `IR::BFN::Pipe` exactly where table placement
would have run, and `fallback` is the real legacy `table_alloc` it wraps.
`backtrack()`/`never_backtracks()` forward to that wrapped pass so the backend
`PassManager` rewinds table placement through the wrapper (TableSummary's
`RerunTablePlacementTrigger`/`FinalRerunTablePlacementTrigger` are only handled by
`TablePlacement::backtrack`).

**`preorder()` flow (as shipped).** Common prologue, then a 3-way branch on
`BFN_Options`:

1. Build layout demand: `SplitAttachedInfo` + `LayoutChoices`; apply
   `TablesMutuallyExclusive` (so its `operator()` is valid).
2. `CompilerBridge::ingest()` → `ModelInputs`; `validate()`.
3. Branch:
   - **emit** (`options.ralloc_emit_dir` set): write the inputs + resume bundle to
     disk and **stop** the compile (§2.1). No solver runs in this process.
   - **resume** (`options.ralloc_resume_dir` set): `runResume()` consumes the
     out-of-process result (§4.2). No solver runs in this process.
   - **in-process** (plain `--use-ralloc`): `ResourceModel::solveMau(...)` then
     `solveVliw(...)` (M2 over legacy PHV, M3), then commit/advisory (§4).
4. **Advisory mode** (default): log the placement, then `runFallback()` = apply the
   legacy `table_alloc`. **Commit mode** (`#ifdef RALLOC_COMMIT`): `writeBack()` +
   `placementWriter()` instead (§4, §4.1).
5. Any exception (`Util::CompilerBug`/`std::exception`) → `runFallback()`. (The emit
   stop signal `BFN::RallocEmitDone` is intentionally **not** a `std::exception`, so
   it escapes this catch and the `PassManager` backtrack handling; it is caught by
   `execute_backend()` in `p4c-barefoot.cpp` as a clean early exit.)
6. The model is solved only once: a second invocation (backtrack re-entry)
   delegates straight to legacy (`attempted_` guard), avoiding a redundant solver
   invocation each backtrack round. The decoupled flow avoids this entirely by
   solving in a separate process.

### 2.1 `model_input` generation interface (the emit calling point)

The compiler→model handoff is produced inside `preorder()` from the just-built
`ModelInputs`, via `CompilerBridge`:

```cpp
ralloc::CompilerBridge bridge(ctx);            // ctx bundles pipe + phv/deps/defuse/clot/layout/mutex/options
ralloc::ModelInputs in = bridge.ingest();      // IR + analyses → POD problem (Doc 04)
if (!options.ralloc_emit_dir.empty()) {
    ralloc::CompilerBridge::writeInputsJson(in, dir + "/model_input.json");        // ModelInputs  → model_input.json
    ralloc::writeResumeBundleFile(bridge.buildResumeBundle(in),                    // ResumeBundle → ir_middle.json
                                  dir + "/ir_middle.json");
    throw BFN::RallocEmitDone{dir};            // stop the compile before solving
}
```

- `CompilerBridge::ingest()` (`compiler_bridge.cpp`) walks the `Pipe` and analyses
  and fills every `ModelInputs` field (Doc 04); it also populates the internal
  id↔IR-node maps.
- `CompilerBridge::writeInputsJson()` now delegates to `writeModelInputsFile()`
  (real JSON; the old summary stub is gone).
- `CompilerBridge::buildResumeBundle(in)` reads those id↔node maps and emits a
  `ResumeBundle` keyed by **stable IR names** (table name per `table_id`; table +
  action name per `action_id`; per-table option ids). This is the *only* extra
  state, beyond `model_input.json`, that resume needs to re-attach an
  out-of-process result. `ingest()` is deterministic, so a later `--ralloc-resume`
  run rebuilds the identical ids and joins on these names.

The standalone solver (`ralloc-solve`, `model-minizinc/src/tool/ralloc_solve_main.cpp`) then
reads `model_input.json` and writes `model_out.json` — see Doc 08.

## 3. The public API (`resource_model.h`)

The header (delivered in `model-minizinc/include/ralloc/resource_model.h`) declares:

```cpp
namespace ralloc {

enum class Objective { Feasibility, MinStages, MinPower, MinPhv, Lexicographic };
enum class SolverChoice { MiniZinc, MznExportOnly };

struct SolveOptions {
  double       time_limit_s      = 120.0;
  double       mip_gap           = 0.05;
  Objective    objective         = Objective::Lexicographic;
  bool         fine_memory       = false;   // M2-fine 2-D RAM packing
  int          max_coupling_iters = 8;
  bool         warm_start        = true;
  bool         deterministic     = true;    // fixed seed, single thread
  unsigned     seed              = 1;
  SolverChoice solver            = SolverChoice::MiniZinc;
  std::string  dump_dir;                     // if set, dump .mzn + solver logs
};

enum class SolveStatus { Optimal, Feasible, Infeasible, TimeoutNoSolution, Error };

class ResourceModel {
 public:
  explicit ResourceModel(SolveOptions = {});
  // Full staged pipeline M1→M2→M3 with coupling cuts.
  SolveResult solve(const ModelInputs&);
  // Individual stages (used by the shipped pass / ralloc-solve and for testing).
  SolveResult solvePhv(const ModelInputs&);
  SolveResult solveMau(const ModelInputs&, const PhvResult&);
  SolveResult solveVliw(const ModelInputs&, const MauResult&);
};

bool hasMiniZinc();   // false if the `minizinc` binary is unavailable (⇒ fall back / .mzn export only)

} // namespace ralloc
```

`RallocModelPass::makeSolveOptions()` and `ralloc-solve` both set
`objective = MinStages` for the P2-first integration.

`SolveResult` bundles a `SolveStatus`, the `ModelResults`, and diagnostics
(objective values, per-resource utilization, solve time, coupling iterations,
optimality gap).

The full struct definitions (`ModelInputs`, `ModelResults`, the per-resource
sub-results) are in the header; they mirror Doc 04 (inputs) and §4 below
(outputs).

## 4. ModelResults insertion (write-back)

The `model → compiler` direction maps each `ModelResults` field onto a native
bf-p4c structure:

| Result field | Meaning | Written into |
|---|---|---|
| `phv.assignments[s]` | container + bit offset per field slice | `PHV::Field` alloc slice, mutated directly in `PhvInfo` (`CompilerBridge::writeBack`) |
| `mau.tables[t].first/last_stage` | stage (and stage-table parts) per table | IR `Table::stage_` / `logical_id` / `stage_split` (`placementWriter()`) |
| `mau.tables[t].option_id` | chosen `LayoutOption` | `TableResourceAlloc::layout_option` (`resource.h`) |
| `mau` srams/tcams/… | per-stage demand | `TableResourceAlloc` + `Memories::Use` (filled by a constrained `Memories::allocate_all`) |
| `vliw.actions[a]` | imem row+color per action | `InstructionMemory::Use` (`instruction_memory.h`) |
| `vliw.adata[f]` | action-data bus byte | `ActionDataBus::Use` (`action_data_bus.h`) |

Insertion is deliberately *coarse*: the model fixes the **hard combinatorial
decisions** (which container, which stage, which option, which imem row); the
existing detailed allocators (`Memories::allocate_all`, `IXBar::allocTable`) are
then run in a **constrained, deterministic** mode that only has to realize the
already-chosen layout. This reuses thousands of lines of validated emission code.

The insertion API lives on `CompilerBridge`:

```cpp
bool         writeBack(const ModelResults&);   // PHV mutated in place; MAU/VLIW plan recorded; runs selfCheck()
P4::Transform* placementWriter();              // IR pass that stamps the recorded plan onto IR::MAU::Table
bool         selfCheck() const;                // re-run PHV::ValidateAllocation; error-count delta == 0 ⇒ legal
```

### 4.1 In-process insertion (`--use-ralloc`)

After `solveMau`/`solveVliw` return a usable `ModelResults res`:

- **Advisory (default):** log the optimum, `runFallback()` — the legacy allocator
  emits the binary. The constrained detailed-realization step that fills
  `TableResourceAlloc::memuse` is **not yet wired in**, so committing only the
  coarse placement leaves `memuse` empty and a downstream pass fails (`map::at: key
  not found`, observed). Advisory mode keeps the no-regression guarantee absolute
  (§5) — verified: the emitted `.bfa` is byte-identical to baseline except
  `run_id`.
- **Commit (`#ifdef RALLOC_COMMIT`):** `bridge.writeBack(res)` then
  `pipe->apply(*bridge.placementWriter())`. `writeBack` returns `false` (via
  `selfCheck`) ⇒ `runFallback()`. Closing the realization gap is Doc 07 phase P2.

### 4.2 Out-of-process insertion (`--ralloc-resume <dir>`)

When the result was produced by the standalone solver, `RallocModelPass::runResume`
re-attaches it (`ralloc_model_pass.cpp`):

```cpp
ResumeBundle bundle = ralloc::readResumeBundleFile(dir + "/ir_middle.json");   // solver-id ↔ IR-name
ModelResults results = ralloc::readModelResultsFile(dir + "/model_out.json");  // the placement
// drift guard: ingest() is deterministic, so the live bundle must match the
// on-disk one id-for-id (compared by table count + each id's name); a mismatch
// (the .p4 / flags changed between emit and resume) ⇒ runFallback().
if (live_bundle_differs_from(bundle)) return runFallback(pipe);
// advisory: log table→stage joined by name; then runFallback().
//   #ifdef RALLOC_COMMIT: bridge.writeBack(results) + placementWriter() instead.
```

The join is what makes a result computed in another process insertable: the solver
only ever speaks integer ids, and `ir_middle.json` maps those ids back to the
stable IR names that exist in the resumed compile. Result use is **advisory** today
for the same realization-gap reason as §4.1; the commit branch is identical to the
in-process one and shares `writeBack()`/`placementWriter()`.

## 5. Fallback contract (no regression guarantee)

The model is an **optional optimizer**, gated by `--use-ralloc` (default off until
validated). The contract:

1. If the `minizinc` binary is unavailable, or the solve returns `Infeasible/TimeoutNoSolution/
   Error`, or write-back validation fails, **or any exception is thrown during
   ingest/solve** (`Util::CompilerBug`/`std::exception` are caught),
   `RallocModelPass` runs the **legacy** `table_alloc` it wraps (passed in as the
   `fallback` visitor) exactly as today.
2. In commit mode, per-sub-model fallback is allowed: if M2 succeeds but M3 is
   infeasible, the coupling cut / fallback applies (Doc 05 §5).
3. `selfCheck()` re-validates the written-back allocation by re-running
   `PHV::ValidateAllocation` (`validate_allocation.cpp`) and checking the global
   error-count delta; any violation → legacy fallback (never a wrong binary).
4. **Advisory mode** (the current default, §4.1) makes (1)–(3) moot for output:
   the legacy allocator always produces the binary, so enabling `--use-ralloc`
   exercises and validates the MILP while being a guaranteed no-op on the result.

Thus enabling the model can only **improve** fit/objective (once commit mode
lands) or be a no-op; it can never produce an illegal or failing compile that the
legacy path would have compiled. **Verified** end-to-end (`doc/MANUAL.md`).

## 6. CLI / options surface

**Implemented on `BFN_Options` (`bf-p4c-options.{h,cpp}`):**

```
--use-ralloc                 enable the MILP allocator, in-process (default: off)
--ralloc-emit <dir>          decoupled flow: write model_input.json + ir_middle.json, then stop (Doc 08)
--ralloc-resume <dir>        decoupled flow: consume model_out.json + ir_middle.json (Doc 08)
```

`--ralloc-emit` / `--ralloc-resume` both imply `--use-ralloc` and select the
**out-of-process** integration: the solver runs as the standalone `ralloc-solve`
binary instead of in `p4c-barefoot`, handing off through three JSON files. See
**Doc 08 — Decoupled (out-of-process) solver flow**.

**Solver-side options (on `ralloc-solve`, not the compiler):** `--time-limit`,
`--gap`, `--objective stage|power|phv|feasible|lex`, `--seed`, `--dump-dir`. The
in-process pass currently hard-codes its `SolveOptions` in
`RallocModelPass::makeSolveOptions()`; exposing these as `--ralloc-*` compiler
flags (time-limit/gap/objective/fine-memory/dump/fallback) remains a follow-up.

## 7. Logging & explainability

On `--ralloc-dump`, emit per sub-model: the `.mzn` model, the solver log, the
final utilization table (per stage: srams/tcams/ixbar/… used vs. budget), and a
human-readable placement report compatible with the existing `.res.json`/table
summary so existing tooling and visualizers keep working.

## 8. Backtracking interplay (as shipped)

The legacy backend uses `Backtrack::trigger` to re-run table placement
(`TableSummary` throws `RerunTablePlacementTrigger` / `FinalRerunTablePlacement‐
Trigger`; only `TablePlacement::backtrack` handles them). Because
`RallocModelPass` *wraps* `table_alloc` rather than being a managed
`PassManager` pass, it implements `P4::Backtrack` and **forwards**
`backtrack()` / `never_backtracks()` to the wrapped visitor, so the manager
checkpoints the wrapper and rewinds table placement exactly as for the bare
legacy pass. (`PHVTrigger::failure` is owned by the separate `MauBacktracker`, so
delegating returns `false` for it and the manager walks back to that handler.)

On a backtrack re-entry the model is **not** re-solved: it is advisory and
re-invoking the out-of-process solver each round is wasteful, so an `attempted_`
guard delegates straight to legacy after the first round. *Future:* re-invoke the solver with the new
constraint added to `ModelInputs` (forced container / forbidden stage) and a
warm start — trivially safe in the decoupled flow, where each solve is a fresh
`ralloc-solve` process.
