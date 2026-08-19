/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/resource_model.h
 * ============================================================================
 *   MAIN PUBLIC INTERFACE for the Tofino MILP resource allocator.
 * ============================================================================
 *
 * This is THE header bf-p4c includes. It exposes a single facade class
 * `ResourceModel` that runs the staged MILP pipeline (Doc 00 §3):
 *
 *     M1 PHV  ->  M2 MAU/memory  ->  M3 VLIW/action   (+ coupling cuts)
 *
 * solved with MiniZinc + OR-Tools CP-SAT, and returns a `ModelResults` that the compiler
 * writes back into PhvInfo / TableResourceAlloc / InstructionMemory::Use via
 * the CompilerBridge (Doc 06 §4).
 *
 * Contract: the model is a best-effort OPTIMIZER. It either returns a valid,
 * objective-improved allocation, or signals a status that instructs the caller
 * to fall back to the legacy allocator (Doc 06 §5). It can never make a
 * legacy-compilable program fail.
 *
 * The model core links NO bf-p4c IR headers; see compiler_bridge.h for the
 * IR <-> ModelInputs/ModelResults translation.
 */
#ifndef RALLOC_RESOURCE_MODEL_H_
#define RALLOC_RESOURCE_MODEL_H_

#include <memory>
#include <string>
#include <vector>

#include "ralloc/model_types.h"

namespace ralloc {

// ---------------------------------------------------------------------------
// Configuration
// ---------------------------------------------------------------------------

/// Top-level objective selector (Doc 02 §5). Lexicographic by default.
enum class Objective {
    Feasibility,   ///< O5: find any legal allocation, fastest
    MinStages,     ///< O1: minimize MAU stages used (latency)
    MinPower,      ///< O3: minimize total stage power
    MinPhv,        ///< O2: minimize PHV containers used
    Lexicographic  ///< Feasibility > MinStages > MinPower > MinPhv (default)
};

enum class SolverChoice { MiniZinc, MznExportOnly };

struct SolveOptions {
    double time_limit_s = 120.0;        ///< per sub-model wall-clock budget
    double mip_gap = 0.05;              ///< accepted optimality gap
    Objective objective = Objective::Lexicographic;
    bool fine_memory = false;           ///< solve exact RAM-cell placement in M2
    int max_coupling_iters = 8;         ///< C1/C5 Benders loop cap (Doc 05 §5)
    bool warm_start = true;             ///< seed the solver from legacy/heuristic
    bool deterministic = true;          ///< fixed seed, single thread
    unsigned seed = 1;
    SolverChoice solver = SolverChoice::MiniZinc;
    std::string dump_dir;               ///< if non-empty, dump .mzn + logs
};

// ---------------------------------------------------------------------------
// Results & diagnostics
// ---------------------------------------------------------------------------

enum class SolveStatus {
    Optimal,            ///< proven optimal within gap
    Feasible,           ///< feasible incumbent, gap not closed
    Infeasible,         ///< proven infeasible -> caller must fall back
    TimeoutNoSolution,  ///< no incumbent in budget -> caller must fall back
    Error               ///< solver/setup error -> caller must fall back
};

/// Per-sub-model solver diagnostics (Doc 06 §7).
struct StageDiagnostics {
    std::string model_name;     ///< "M1-PHV", "M2-MAU", "M3-VLIW[k,gress]"
    SolveStatus status = SolveStatus::Error;
    double objective_value = 0.0;
    double best_bound = 0.0;
    double gap = 1.0;
    double solve_time_s = 0.0;
    std::size_t num_vars = 0;
    std::size_t num_rows = 0;
};

struct SolveResult {
    SolveStatus status = SolveStatus::Error;
    ModelResults results;
    std::vector<StageDiagnostics> per_stage;  ///< one per sub-model solved
    int coupling_iterations = 0;
    std::string message;                      ///< human-readable summary

    /// True iff the caller may use `results`; false => fall back to legacy.
    bool usable() const {
        return status == SolveStatus::Optimal || status == SolveStatus::Feasible;
    }
};

// ---------------------------------------------------------------------------
// Facade
// ---------------------------------------------------------------------------

/**
 * Drives the staged MILP pipeline. Stateless across calls except for the
 * configured options; create one per compile (cheap).
 */
class ResourceModel {
 public:
    explicit ResourceModel(SolveOptions options = {});
    ~ResourceModel();

    ResourceModel(const ResourceModel &) = delete;
    ResourceModel &operator=(const ResourceModel &) = delete;

    /// Run the full pipeline M1 -> M2 -> M3 with coupling cuts (Doc 03/05).
    /// `inputs` must pass validate() (Doc 04 §6) or the result is Error.
    SolveResult solve(const ModelInputs &inputs);

    // --- staged entry points (testing / partial adoption, Doc 06 §1) -------

    /// Solve only M1 (PHV). Result.results.phv is populated.
    SolveResult solvePhv(const ModelInputs &inputs);

    /// Solve M2 (MAU/memory) given a fixed PHV result (the coupling C1
    /// crossbar-byte parameter is read from `phv`). If `phv` is empty, M2 uses
    /// the option-level ixbar demand instead.
    SolveResult solveMau(const ModelInputs &inputs, const PhvResult &phv);

    /// Solve M3 (VLIW/action) for the given MAU placement.
    SolveResult solveVliw(const ModelInputs &inputs, const MauResult &mau);

    const SolveOptions &options() const { return options_; }
    void setOptions(SolveOptions o) { options_ = std::move(o); }

 private:
    SolveOptions options_;
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

/// Convenience free function: solve with default options.
inline SolveResult solveResourceAllocation(const ModelInputs &in, SolveOptions o = {}) {
    return ResourceModel(std::move(o)).solve(in);
}

/// Library/solver capability probe (Doc 05 §1). False if the `minizinc` binary
/// (with an OR-Tools CP-SAT backend) is not available at runtime.
bool hasMiniZinc();

/// Version string of the ralloc library.
const char *version();

}  // namespace ralloc

#endif  // RALLOC_RESOURCE_MODEL_H_
