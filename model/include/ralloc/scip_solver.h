/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/scip_solver.h  --  SolverBackend abstraction + SCIP backend (Doc 05).
 *
 * Model builders emit a solver-agnostic LinearModel; a SolverBackend solves it.
 * ScipBackend uses libscip (C API). If SCIP is not linked (RALLOC_HAVE_SCIP=0),
 * ScipBackend::available() is false and the facade forces legacy fallback.
 */
#ifndef RALLOC_SCIP_SOLVER_H_
#define RALLOC_SCIP_SOLVER_H_

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
    bool emphasis_feasibility = false;  ///< objective O5
    std::string dump_path;              ///< if set, write .lp/.cip + log
};

/// A primal solution: value per LinearModel variable index (Doc 05 §2).
struct Solution {
    SolveOutcome outcome = SolveOutcome::Error;
    std::vector<double> values;   ///< size == model.vars().size()
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

/// SCIP-backed implementation (model/src/solver/scip_solver.cpp).
class ScipBackend : public SolverBackend {
 public:
    ScipBackend();
    ~ScipBackend() override;
    bool available() const override;
    Solution solve(const LinearModel &, const SolverParams &) override;
    void setWarmStart(const std::vector<double> &seed) override;

 private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

/// Backend that only exports `.lp`/MPS and never solves (Doc 05 §9, CI w/o SCIP).
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
std::unique_ptr<SolverBackend> makeSolver(bool prefer_scip, std::string dump_dir = "");

}  // namespace ralloc

#endif  // RALLOC_SCIP_SOLVER_H_
