# Doc 05 — MiniZinc + OR-Tools Solver Integration

This document specifies how the integer program of Doc 03 is built, solved,
decomposed, and (optionally) warm-started using **MiniZinc** as the modelling
layer and **Google OR-Tools CP-SAT** as the solver.

MiniZinc + CP-SAT is chosen because (a) CP-SAT is a state-of-the-art
constraint/integer solver that is extremely strong on the pure 0/1 problems this
model produces; (b) MiniZinc supports **reified/half-reified implications**
directly (`b -> constraint`), which is exactly the indicator-constraint shape the
coupling cuts need (Doc 02 §6.1), with no big-M; and (c) MiniZinc is driven as a
**command-line process**, so there is no solver library to find, link, or ship
inside the compiler — a much lighter integration than a C-API solver.

> This is the MiniZinc edition of the allocator. The SCIP edition (`model/`)
> follows the identical formulation and decomposition; only this backend seam
> differs. Where this doc says "the solver" it means `minizinc --solver cp-sat`.

## 1. Process model & abstraction

The solver is hidden behind `ralloc::SolverBackend` (`minizinc_solver.h`):

```
SolverBackend (abstract)
   ├── MiniZincBackend     ← spawns `minizinc --solver cp-sat`
   └── MznExportBackend    ← writes .mzn only, never solves (CI / no solver)
```

There is **no build- or link-time solver dependency**. The model **builders**
(`phv_model`, `mau_model`, `vliw_model`) stay solver-agnostic: they emit an
abstract `LinearModel` (variables, linear rows, indicator rows, objective).
`MiniZincBackend` serialises that model with `LinearModel::toMiniZincString()`,
runs MiniZinc as a child process, and parses the result back.

Availability is a **runtime probe**: `MiniZincBackend::available()` runs
`minizinc --version`. If the binary is missing, the facade forces
legacy-allocator fallback (parallel to the old SCIP-less path). Configuration is
by environment:

| Variable | Default | Meaning |
|---|---|---|
| `RALLOC_MINIZINC` | `minizinc` | path to the MiniZinc driver binary |
| `RALLOC_MINIZINC_SOLVER` | `cp-sat` | FlatZinc solver id/tag (`cp-sat` = OR-Tools) |

`RALLOC_MINIZINC_SOLVER` lets the same model be routed to any registered MiniZinc
backend (`cbc`, `gecode`, `chuffed`, `highs`, …) for cross-validation without a
recompile.

## 2. The emitted `.mzn`

`toMiniZincString()` maps the `LinearModel` onto MiniZinc 1:1. Variables are
declared as `v0..vN` indexed by `VarRef`, so arbitrary LP-style names never
collide with MiniZinc identifier rules. Because every ralloc variable is binary
and every coefficient is integral, the emitted model is a **pure integer
program** — the shape CP-SAT solves natively (no LP relaxation, no rounding).

```minizinc
% ralloc model: M2-MAU (MiniZinc / OR-Tools CP-SAT)
var 0..1: v0;   % y_1_0
var 0..1: v1;   % y_1_1
...
constraint v0 + v1 + v2 <= 2;                 % linear row
constraint (v5 = 1) -> (v0 + v3 >= 1);        % indicator row (implication)
solve minimize (1000000*v7 + v0);             % objective
output [ "v0=", show(v0), "\n", "v1=", show(v1), "\n", ... ];
```

The `output` block prints one `v<i>=<value>` line per variable; the backend
parses these back into `Solution::values` (indexed identically to the model).

## 3. Build → solve → read cycle (per sub-model)

```cpp
LinearModel m = builder.build(inputs);          // Doc 03 formulas
Solution sol = minizinc.solve(m, params);       // spawn minizinc, parse output
if (sol.outcome == Optimal || sol.outcome == Feasible)
    builder.readBack(sol.values, &results);     // var values → allocation
```

`MiniZincBackend::solve` builds the command line:

- `--solver cp-sat` — the OR-Tools CP-SAT FlatZinc backend.
- `--time-limit <ms>` — per-sub-model wall-clock budget (`SolverParams::time_limit_s`).
- `-p 1` — single search worker, for reproducibility (see §8).

MiniZinc's terminal markers are mapped onto `SolveOutcome`:

| MiniZinc output | `SolveOutcome` |
|---|---|
| solution printed, then `==========` | `Optimal` (proven) |
| solution printed, no `==========` (e.g. time limit) | `Feasible` |
| `=====UNSATISFIABLE=====` | `Infeasible` |
| `=====UNKNOWN=====` (no solution found) | `TimeoutNoSolution` |
| `=====ERROR=====` / `=====UNBOUNDED=====` / launch failure | `Error` |

The objective is recomputed from the returned values against the model's
objective coefficients; when the solve is proven optimal, `bound == objective`
and `gap == 0`.

## 4. Decomposition & solve order

Default pipeline (matches Doc 00 §3), unchanged from the SCIP edition:

1. **M1 PHV** — one integer program, ~10⁴–10⁵ binaries. Time budget e.g. 60 s.
2. **M2 MAU/memory (coarse)** — one integer program, ~10⁴ binaries. Budget 60 s.
3. For each (stage, gress): **M3 VLIW** — tiny program, solved to optimality (< 1 s).
4. If any M3 infeasible → add a no-good cut to M2, re-solve M2 (bounded ≤ K iters).
5. Exact RAM cell placement: **delegated to `Memories::allocate_all`** (fast,
   deterministic) rather than M2-fine, unless `--ralloc-fine-memory` is set.

### 4.1 Time-boxing & anytime behavior

CP-SAT is an anytime solver: on hitting `--time-limit` it prints the best
solution found so far (→ `Feasible`) or `=====UNKNOWN=====` if none was found
(→ `TimeoutNoSolution`). In the latter case ralloc **falls back** to the legacy
allocator for that sub-problem. This keeps the model a strict *best-effort
improver*: it can never make a previously compilable program fail.

## 5. Multi-objective / lexicographic

Two supported modes:
- **Weighted sum** with separated weights `W_stage ≫ W_pow ≫ W_bal` (simple,
  default). This is exactly what the emitted `solve minimize (…)` encodes — e.g.
  `useStage` carries coefficient `1e6` so stage minimisation dominates.
- **True lexicographic**: solve for O1, add `Σ useStage = optimum` as a
  constraint, re-solve for O3, etc. — a small loop over `solve` calls, each a
  fresh `minizinc` invocation on an augmented model.

## 6. Coupling cuts (logic-based Benders)

For couplings C1 (PHV↔ixbar) and C5 (stage↔imem) the downstream infeasibility is
turned into a **no-good cut** on the upstream model:

- **C5 example:** M3 finds that action set `Q ⊆ A` cannot be colored into 32×2
  rows in stage k. Add to M2:
  `Σ_{t: action(t)∈Q} y[t,k] ≤ |tables(Q)| − 1`
  i.e. "not all these tables may share stage k." Re-solve M2.
- Implemented as an **outer loop** in `ResourceModel::solve`: each iteration
  rebuilds the M2 model with the accumulated cuts and re-invokes MiniZinc.
  Iterations capped at `K = 8`; on exhaustion → legacy fallback.

This guarantees termination and correctness: every added cut removes ≥ 1
infeasible assignment, the feasible region is finite, and fallback covers the cap.
(Because MiniZinc is stateless between invocations, cuts are re-emitted into each
fresh model rather than added lazily inside one search — simpler, and the M2
solves are short enough that re-solving is cheap.)

## 7. Warm-starting

`SolverBackend::setWarmStart` accepts a (possibly partial) primal seed from the
legacy heuristic. The interface is retained for parity with the SCIP edition, but
the MiniZinc CLI has no portable, solver-agnostic warm-start channel, so the
current `MiniZincBackend` stores the seed and does not inject it. CP-SAT's own
presolve + portfolio search finds strong incumbents quickly on these 0/1 models,
so the practical cost is small. (A future refinement can emit CP-SAT search hints
via `--cp-sat-flags` or a solver-specific annotation when `cp-sat` is the target.)

## 8. Determinism & reproducibility

- `-p 1` (single worker) makes CP-SAT deterministic, so the emitted allocation is
  byte-identical across runs — a hard requirement for a compiler. A future
  `--ralloc-threads N` opt-in could trade determinism for speed.
- Under `--dump-dir`, the generated `.mzn` and the raw solver log are written
  (`<model>.mzn`, `<model>.log`) for offline analysis and regression fixtures.

## 9. Solver-independence & testing

`LinearModel` can be written to MiniZinc (`toMiniZincString`) **and** to standard
CPLEX `.lp` (`toLpString`), so the same model can be routed to any MiniZinc
backend or imported by HiGHS/Gurobi/CPLEX for cross-validation. Unit tests
(`test/test_minizinc_export.cpp`) assert the `.mzn` structure with no solver
installed, and additionally run a live CP-SAT solve when `minizinc` is on `$PATH`
(self-skipping otherwise). See Doc 07 §4.
