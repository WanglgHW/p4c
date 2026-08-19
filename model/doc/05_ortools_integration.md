# Doc 05 — OR-Tools Solver Integration

This document specifies how the MILP of Doc 03 is built, solved, decomposed, and
warm-started using **Google OR-Tools**. OR-Tools is chosen because it is (a) a
top open-source optimization suite under Apache-2.0 (safe to link into an open
compiler), (b) its **CP-SAT** engine is state of the art on exactly the shape of
problem ralloc produces — pure 0/1 programs with logical structure — and it
supports **indicator constraints natively** (`OnlyEnforceIf`, no big-M) plus
solution hints and reproducible search, and (c) it also ships **MPSolver**, a
generic LP/MIP wrapper (SCIP/CBC/HiGHS/GLOP), so mixed models with continuous
variables remain solvable through the same backend.

## 1. Linking & abstraction

The solver is hidden behind `ralloc::SolverBackend` (`ortools_solver.h`) so
OR-Tools is an optional dependency:

```
SolverBackend (abstract)
   ├── OrToolsBackend      ← CP-SAT (all-discrete) | MPSolver (mixed/continuous)
   ├── LpExportBackend     ← writes .lp, never solves (CI / no OR-Tools)
   └── (future) direct HiGHS / Gurobi backends
```

CMake: `find_package(ortools CONFIG)`. If absent, `RALLOC_HAVE_ORTOOLS=0`,
`OrToolsBackend::available()` is false and `makeSolver()` hands back the `.lp`
exporter, which forces legacy-allocator fallback. The model **builders**
(`phv_model`, `mau_model`, `vliw_model`) are solver-agnostic: they emit an
abstract `LinearModel` (variables, linear rows, indicator rows, objective) which
`OrToolsBackend` translates into a `sat::CpModelBuilder` (or an `MPSolver`
problem).

### 1.1 Which engine, and why it is safe

`OrToolsBackend::isCpSatEligible()` decides per model:

* every variable is `Binary`/`Integer` with integral bounds, **and**
* every row scales to integer coefficients by a power of ten ≤ 10⁶ (each row is
  scaled independently — multiplying a row's coefficients *and* its rhs by the
  same factor preserves its meaning), **and**
* the objective coefficients scale the same way.

All ralloc sub-models (M1/M2/M3) satisfy this — they are pure 0/1 programs with
integral demands — so CP-SAT is the normal path. Anything else (a continuous
variable, a genuinely fractional coefficient) goes to MPSolver, where only a
MIP-capable engine is accepted if the model has integrality (GLOP is offered for
pure LPs only, so an integer model can never be silently relaxed to its LP).

### 1.2 Which *process* links the solver

`ralloc-solve` (the standalone solver binary) always links OR-Tools. The
compiler itself does **not** by default: OR-Tools brings its own abseil,
protobuf and re2, while p4c builds abseil/protobuf itself, and two copies in one
binary neither configure nor link cleanly. In-process solving is therefore
opt-in:

```
cmake -DP4C_USE_PREINSTALLED_ABSEIL=ON -DRALLOC_INPROCESS_SOLVER=ON .
```

Without it, `--use-ralloc` logs that OR-Tools is not linked and falls back to
the legacy allocator; the supported route is the decoupled flow of Doc 08
(`--ralloc-emit` → `ralloc-solve` → `--ralloc-resume`), which also sidesteps the
solver-under-p4c-GC hazard.

## 2. Build → solve → read cycle (per sub-model)

```cpp
LinearModel m = builder.build(inputs);          // Doc 03 formulas
Solution sol = solver->solve(m, params);        // CP-SAT search
if (sol.outcome == Optimal || sol.outcome == Feasible)
    builder.readBack(sol.values, &results);     // var values → allocation
```

`SolverParams` maps onto CP-SAT `SatParameters` as follows:

| SolverParams | CP-SAT parameter | meaning |
|---|---|---|
| `time_limit_s` | `max_time_in_seconds` | per-sub-model wall-clock budget |
| `gap` | `relative_gap_limit` | accept near-optimal (e.g. 5%) |
| `seed` | `random_seed` | reproducible search |
| `deterministic` | `num_workers = 1` | byte-identical results across runs |
| `emphasis_feasibility` | `stop_after_first_solution` | objective O5: any legal allocation, fastest |
| `dump_path` | `log_search_progress` + `log_to_response` | `.lp`, `.pb.txt` model dump and `.log` search log |

On the MPSolver path the equivalents are `SetTimeLimit`, `MPSolverParameters::
RELATIVE_MIP_GAP` and `SetNumThreads(1)`.

## 3. Decomposition & solve order

Default pipeline (matches Doc 00 §3):

1. **M1 PHV** — one model, ~10⁴–10⁵ binaries. Time budget e.g. 60 s, gap 5%.
2. **M2 MAU/memory (coarse)** — one model, ~10⁴ binaries. Budget 60 s.
3. For each (stage, gress): **M3 VLIW** — tiny model, solved to optimality (< 1 s).
4. If any M3 infeasible → add cut to M2, re-solve M2 (bounded ≤ K iterations).
5. Exact RAM cell placement: **delegated to `Memories::allocate_all`** (fast,
   deterministic) rather than M2-fine, unless `--ralloc-fine-memory` is set.

### 3.1 Time-boxing & anytime behavior

Every `solve` returns the best feasible solution found within the budget (CP-SAT
is anytime: `FEASIBLE` carries an incumbent, `best_objective_bound()` the dual
bound). If no integer feasible solution was found (`UNKNOWN`), we **fall back**
to the legacy allocator for that sub-problem and log the gap. This makes the
model strictly a *best-effort improver*: it can never make a previously
compilable program fail.

### 3.2 Symmetry handling

CP-SAT detects and exploits symmetry automatically (`symmetry_level`, on by
default). Add the container lexicographic ordering (Doc 03 §8) only for large
PHV instances where the detector is too slow.

## 4. Multi-objective / lexicographic

Two supported modes:
- **Weighted sum** with separated weights `W_stage ≫ W_pow ≫ W_bal` (simple,
  default).
- **True lexicographic**: solve for O1, fix `Σ useStage` to its optimum as a
  constraint, re-solve for O3, etc. Implemented as a small loop over `solve`
  calls, each seeded with the previous solution as a hint.

## 5. Coupling cuts (logic-based Benders)

For couplings C1 (PHV↔ixbar) and C5 (stage↔imem) the downstream infeasibility is
turned into a **no-good cut** on the upstream model:

- **C5 example:** M3 finds that action set `Q ⊆ A` cannot be colored into 32×2
  rows in stage k. Add to M2:
  `Σ_{t: action(t)∈Q} y[t,k] ≤ |tables(Q)| − 1`
  i.e. "not all these tables may share stage k." Re-solve M2.
- Implemented as an outer loop with re-solve (`ResourceModel::solve`), capped at
  `K=8` iterations; on exhaustion → legacy fallback. (A lazy variant is possible
  with a CP-SAT solution callback, but the outer loop is simpler and the cut
  count is small.)

This guarantees termination and correctness: every added cut removes ≥ 1
infeasible assignment, the feasible region is finite, and fallback covers the cap.

## 6. Warm-starting from the legacy allocator

To make the search fast and to guarantee an incumbent, we **seed** each sub-model
with the solution the legacy heuristic would produce:

- Run a *fast* pass of the existing greedy allocator (or a previous compile's
  result) to get an initial assignment.
- Pass it to `SolverBackend::setWarmStart()`; the CP-SAT path turns it into
  `CpModelBuilder::AddHint()` per variable (partial hints are fine — `NaN`
  entries are skipped and CP-SAT repairs the rest), the MPSolver path into
  `MPSolver::SetHint`.
- This both bounds the objective and gives the search a strong incumbent,
  typically cutting solve time by an order of magnitude.

## 7. Performance plan & expected sizes

| Sub-model | binaries (large prog.) | rows | target time |
|---|---|---|---|
| M1 PHV | 10⁴–10⁵ | 10⁴ | 30–120 s (gap 5%) |
| M2 MAU coarse | 5·10³–2·10⁴ | 10³ | 10–60 s |
| M3 per (k,r) | 10²–10³ | 10² | < 1 s each |

Measured: a 24-table TNA program (`testdata/dpvs-l4LB/dpvs_l4lb.p4`) solves M2 +
all M3 sub-models to proven optimality in ~0.1 s total.

Levers if too slow: tighten gap, reduce `O(t)` to the top-N options by a cheap
score, restrict PHV candidate containers per slice to its MAU-group-compatible
subset (already implied by `kindOK`), and raise `num_workers` (trading
determinism, see §8).

## 8. Determinism & reproducibility

- Fix `random_seed` and run with `num_workers = 1` for byte-identical output
  across runs (compilers must be reproducible). A `--ralloc-threads N` opt-in
  can enable parallel search at the cost of determinism.
- The search log records a `solution_fingerprint`, which makes a determinism
  regression obvious in a diff.
- Dump the model under `--dump-dir` for offline analysis and regression
  fixtures: `<model>.lp` (CPLEX LP, from `LinearModel::toLpString`),
  `<model>.pb.txt` (the CP-SAT proto) and `<model>.log` (the search log).

## 9. Solver-independence & testing

`LinearModel` can be written to standard `.lp` / MPS, so the exact same model is
solvable by HiGHS, Gurobi, or CPLEX for cross-validation, and unit tests can run
without OR-Tools installed (`RALLOC_HAVE_ORTOOLS=0` → the export-only backend).
`model/test/test_ortools_solver.cpp` covers the live path: it solves the Doc 03
§6 example to optimality, checks indicator rows in all four trigger/polarity
combinations (native enforcement on the CP-SAT path, big-M on the MPSolver
path), and solves a small LP. See Doc 07 §4.
