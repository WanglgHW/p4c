/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/minizinc_solver.h  --  SolverBackend abstraction + MiniZinc backend.
 *
 * Model builders emit a solver-agnostic LinearModel; a SolverBackend solves it.
 * MiniZincBackend serialises the model to a `.mzn` file and drives it through
 * the MiniZinc toolchain using Google OR-Tools CP-SAT as the FlatZinc solver
 * (`minizinc --solver cp-sat ...`). Because every ralloc variable is binary and
 * all coefficients are integral, the problem is a pure integer program — exactly
 * what CP-SAT solves natively — so no big-M relaxation or LP rounding is needed.
 *
 * MiniZinc is invoked as an external process, so there is no compile-time
 * dependency on any solver library: availability is a runtime probe for the
 * `minizinc` binary (see MiniZincBackend::available()). If MiniZinc is absent
 * the facade forces legacy fallback, mirroring the old SCIP-less path.
 */
#ifndef RALLOC_MINIZINC_SOLVER_H_
#define RALLOC_MINIZINC_SOLVER_H_

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
    std::string dump_path;              ///< if set, keep the generated .mzn + log
};

/// A primal solution: value per LinearModel variable index.
struct Solution {
    SolveOutcome outcome = SolveOutcome::Error;
    std::vector<double> values;   ///< size == model.vars().size()
    double objective = 0.0;
    double bound = 0.0;
    double gap = 1.0;
    double solve_time_s = 0.0;
};

/// Abstract solver.
class SolverBackend {
 public:
    virtual ~SolverBackend() = default;
    virtual bool available() const = 0;
    virtual Solution solve(const LinearModel &, const SolverParams &) = 0;
    /// Warm-start hint: a (possibly partial) primal solution to seed the search.
    /// `seed[i]` is the value for variable i; NaN = unset.
    virtual void setWarmStart(const std::vector<double> &seed) = 0;
};

/// MiniZinc-backed implementation (model/src/solver/minizinc_solver.cpp).
///
/// Configuration (constructor defaults, overridable via environment):
///   RALLOC_MINIZINC          path to the `minizinc` binary   (default "minizinc")
///   RALLOC_MINIZINC_SOLVER   FlatZinc solver id/tag          (default "cp-sat")
class MiniZincBackend : public SolverBackend {
 public:
    MiniZincBackend();
    ~MiniZincBackend() override;
    bool available() const override;
    Solution solve(const LinearModel &, const SolverParams &) override;
    void setWarmStart(const std::vector<double> &seed) override;

 private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

/// Backend that only exports the `.mzn` model and never solves (CI without a
/// MiniZinc install; parallels the old `.lp` exporter).
class MznExportBackend : public SolverBackend {
 public:
    explicit MznExportBackend(std::string out_path) : out_path_(std::move(out_path)) {}
    bool available() const override { return true; }
    Solution solve(const LinearModel &, const SolverParams &) override;
    void setWarmStart(const std::vector<double> &) override {}

 private:
    std::string out_path_;
};

/// Factory honoring SolverChoice + runtime MiniZinc availability.
std::unique_ptr<SolverBackend> makeSolver(bool prefer_minizinc, std::string dump_dir = "");

}  // namespace ralloc

#endif  // RALLOC_MINIZINC_SOLVER_H_
