# Doc 05 — SCIP Solver Integration

This document specifies how the MILP of Doc 03 is built, solved, decomposed, and
warm-started using **SCIP**. SCIP is chosen because it is (a) a top open-source
MILP/branch-and-cut solver, (b) supports **indicator constraints**, **lazy
constraints / constraint handlers** (needed for the Benders-style coupling cuts,
Doc 02 §6.1), and (c) has a stable C API and a permissive license suitable for
linking into an open compiler.

## 1. Linking & abstraction

The solver is hidden behind `ralloc::SolverBackend` (`scip_solver.h`) so SCIP is
an optional dependency:

```
SolverBackend (abstract)
   ├── ScipBackend         ← libscip (C API)
   └── (future) HiGHS / Gurobi backends
```

CMake: `find_package(SCIP)`. If absent, `RALLOC_HAVE_SCIP=0` and the backend
compiles to a stub that forces legacy-allocator fallback. The model **builders**
(`phv_model`, `mau_model`, `vliw_model`) are solver-agnostic: they emit an
abstract `LinearModel` (variables, linear rows, indicator rows, objective) which
`ScipBackend` translates to SCIP `SCIP_VAR*` / `SCIPcreateConsLinear` /
`SCIPcreateConsIndicator`.

## 2. Build → solve → read cycle (per sub-model)

```cpp
LinearModel m = builder.build(inputs);          // Doc 03 formulas
auto sol = scip.solve(m, params);               // branch-and-cut
if (sol.status == OPTIMAL || sol.status == FEASIBLE)
    builder.readBack(sol, &results);            // var values → allocation
```

`scip.solve` configures:
- `SCIPsetRealParam(scip,"limits/time", T)` — per-stage wall-clock budget.
- `SCIPsetRealParam(scip,"limits/gap", g)` — accept near-optimal (e.g. 2%).
- emphasis `SCIPsetEmphasis(scip, SCIP_PARAMEMPHASIS_FEASIBILITY, …)` when we only
  need a legal allocation (objective O5).
- `limits/solutions 1` for first-feasible fast paths.

## 3. Decomposition & solve order

Default pipeline (matches Doc 00 §3):

1. **M1 PHV** — one MILP, ~10⁴–10⁵ binaries. Time budget e.g. 60 s, gap 5%.
2. **M2 MAU/memory (coarse)** — one MILP, ~10⁴ binaries. Budget 60 s.
3. For each (stage, gress): **M3 VLIW** — tiny MILP, solved to optimality (< 1 s).
4. If any M3 infeasible → add cut to M2, re-solve M2 (bounded ≤ K iterations).
5. Exact RAM cell placement: **delegated to `Memories::allocate_all`** (fast,
   deterministic) rather than M2-fine, unless `--ralloc-fine-memory` is set.

### 3.1 Time-boxing & anytime behavior

Every `solve` returns the best feasible solution found within the budget (SCIP is
anytime). If only the LP bound is known (no integer feasible found), we **fall
back** to the legacy allocator for that sub-problem and log the gap. This makes
the model strictly a *best-effort improver*: it can never make a previously
compilable program fail.

### 3.2 Symmetry handling in SCIP

- Enable SCIP's automatic symmetry detection (`misc/usesymmetry`).
- Add the container lexicographic ordering (Doc 03 §8) only for large PHV
  instances where SCIP's detector is too slow.

## 4. Multi-objective / lexicographic

Two supported modes:
- **Weighted sum** with separated weights `W_stage ≫ W_pow ≫ W_bal` (simple,
  default).
- **True lexicographic**: solve for O1, fix `Σ useStage` to its optimum as a
  constraint, re-solve for O3, etc. Implemented as a small loop over `solve`
  calls reusing the warm-started SCIP instance.

## 5. Coupling cuts (logic-based Benders)

For couplings C1 (PHV↔ixbar) and C5 (stage↔imem) the downstream infeasibility is
turned into a **no-good cut** on the upstream model:

- **C5 example:** M3 finds that action set `Q ⊆ A` cannot be colored into 32×2
  rows in stage k. Add to M2:
  `Σ_{t: action(t)∈Q} y[t,k] ≤ |tables(Q)| − 1`
  i.e. "not all these tables may share stage k." Re-solve M2.
- Implemented as a SCIP **constraint handler** (`CONSHDLR`) so cuts are added
  lazily during a single branch-and-bound when possible, or as an outer loop with
  re-solve (simpler, default). Iterations capped at `K=8`; on exhaustion → legacy
  fallback.

This guarantees termination and correctness: every added cut removes ≥ 1
infeasible assignment, the feasible region is finite, and fallback covers the cap.

## 6. Warm-starting from the legacy allocator

To make SCIP fast and to guarantee an incumbent, we **seed** each sub-model with
the solution the legacy heuristic would produce:

- Run a *fast* pass of the existing greedy allocator (or a previous compile's
  result) to get an initial assignment.
- Convert it to a SCIP primal solution via `SCIPcreateSol` + `SCIPsetSolVal` and
  add with `SCIPaddSolFree` (checked). SCIP then improves on it.
- This both bounds the objective and gives branch-and-cut a strong incumbent,
  typically cutting solve time by an order of magnitude.

## 7. Performance plan & expected sizes

| Sub-model | binaries (large prog.) | rows | target time |
|---|---|---|---|
| M1 PHV | 10⁴–10⁵ | 10⁴ | 30–120 s (gap 5%) |
| M2 MAU coarse | 5·10³–2·10⁴ | 10³ | 10–60 s |
| M3 per (k,r) | 10²–10³ | 10² | < 1 s each |

Levers if too slow: tighten gap, reduce `O(t)` to the top-N options by a cheap
score, restrict PHV candidate containers per slice to its MAU-group-compatible
subset (already implied by `kindOK`), and enable aggressive presolve
(`presolving/maxrounds -1`).

## 8. Determinism & reproducibility

- Fix `randomization/randomseedshift` and run single-threaded for byte-identical
  output across runs (compilers must be reproducible). A `--ralloc-threads N`
  opt-in enables parallel SCIP at the cost of determinism.
- Dump the model (`SCIPwriteOrigProblem` → `.lp`/`.cip`) under `-g`/debug for
  offline analysis and regression fixtures.

## 9. Solver-independence & testing

`LinearModel` can be written to standard `.lp` / MPS, so the exact same model is
solvable by HiGHS, Gurobi, or CPLEX for cross-validation, and unit tests can run
without SCIP installed (compare against a checked-in expected solution). See
Doc 07 §4.
