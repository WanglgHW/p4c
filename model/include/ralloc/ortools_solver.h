/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/ortools_solver.h  --  SolverBackend abstraction + OR-Tools backend (Doc 05).
 *
 * Model builders emit a solver-agnostic LinearModel; a SolverBackend solves it.
 * OrToolsBackend uses Google OR-Tools and picks the right engine per model:
 *
 *   - CP-SAT (`operations_research::sat`) whenever every variable is discrete
 *     (Binary/Integer) and every row scales to integer coefficients — which is
 *     the case for all ralloc sub-models (M1/M2/M3 are pure 0/1 programs). This
 *     is the preferred path: it needs no big-M for indicator rows (`OnlyEnforceIf`
 *     is native), gives a proven optimality gap, and is deterministic.
 *   - MPSolver (`operations_research::MPSolver`, CP-SAT/SCIP/CBC MIP backend) for
 *     the general mixed case with continuous variables, where indicator rows are
 *     relaxed to big-M. Kept so the LinearModel contract stays fully honored.
 *
 * If OR-Tools is not linked (RALLOC_HAVE_ORTOOLS=0), OrToolsBackend::available()
 * is false and the facade forces legacy fallback.
 */
#ifndef RALLOC_ORTOOLS_SOLVER_H_
#define RALLOC_ORTOOLS_SOLVER_H_

#include <memory>
#include <string>
#include <vector>

#include "ralloc/linear_model.h"

namespace ralloc {

enum class SolveOutcome { Optimal, Feasible, Infeasible, TimeoutNoSolution, Error };

struct SolverParams {
    double time_limit_s = 120.0;
    double gap = 0.05;
    bool deterministic = true;
    unsigned seed = 1;
    bool emphasis_feasibility = false;  ///< objective O5: stop at the first solution
    std::string dump_path;              ///< if set, write .lp/.pb.txt + solver log
};

/// A primal solution: value per LinearModel variable index (Doc 05 §2).
struct Solution {
    SolveOutcome outcome = SolveOutcome::Error;
    std::vector<double> values;  ///< size == model.vars().size()
    double objective = 0.0;
    double bound = 0.0;
    double gap = 1.0;
    double solve_time_s = 0.0;
};

/// Abstract solver. Doc 05 §1.
class SolverBackend {
 public:
    virtual ~SolverBackend() = default;
    virtual bool available() const = 0;
    virtual Solution solve(const LinearModel &, const SolverParams &) = 0;
    /// Warm-start hint: a (possibly partial) primal solution to seed the search
    /// (Doc 05 §6). `seed[i]` is the value for variable i; NaN = unset.
    virtual void setWarmStart(const std::vector<double> &seed) = 0;
};

/// OR-Tools-backed implementation (model/src/solver/ortools_solver.cpp).
class OrToolsBackend : public SolverBackend {
 public:
    OrToolsBackend();
    ~OrToolsBackend() override;
    bool available() const override;
    Solution solve(const LinearModel &, const SolverParams &) override;
    void setWarmStart(const std::vector<double> &seed) override;

    /// True if `m` can go down the CP-SAT path (all-discrete, integer-scalable).
    /// Exposed for diagnostics/tests; `solve()` applies it automatically.
    static bool isCpSatEligible(const LinearModel &m);

 private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

/// Backend that only exports `.lp`/MPS and never solves (Doc 05 §9, CI w/o OR-Tools).
class LpExportBackend : public SolverBackend {
 public:
    explicit LpExportBackend(std::string out_path) : out_path_(std::move(out_path)) {}
    bool available() const override { return true; }
    Solution solve(const LinearModel &, const SolverParams &) override;
    void setWarmStart(const std::vector<double> &) override {}

 private:
    std::string out_path_;
};

/// Factory honoring SolverChoice + link-time availability.
std::unique_ptr<SolverBackend> makeSolver(bool prefer_ortools, std::string dump_dir = "");

}  // namespace ralloc

#endif  // RALLOC_ORTOOLS_SOLVER_H_
