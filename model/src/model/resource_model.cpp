/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ResourceModel facade: orchestrates the staged MILP pipeline
 *   M1 PHV -> M2 MAU/memory -> M3 VLIW  with C1/C5 coupling cuts (Doc 03/05).
 *
 * This file contains the real control flow; the numerical model construction is
 * delegated to the *ModelBuilder classes (see model/{phv,mau,vliw}_model.cpp).
 */
#include "ralloc/resource_model.h"

#include <utility>
#include <vector>

#include "ralloc/mau_model.h"
#include "ralloc/phv_model.h"
#include "ralloc/scip_solver.h"
#include "ralloc/vliw_model.h"

namespace ralloc {

#ifndef RALLOC_VERSION_STRING
#define RALLOC_VERSION_STRING "0.1.0"
#endif

const char *version() { return RALLOC_VERSION_STRING; }

bool hasScip() {
    ScipBackend b;
    return b.available();
}

struct ResourceModel::Impl {
    SolveOptions opt;
    std::unique_ptr<SolverBackend> solver;

    explicit Impl(SolveOptions o) : opt(std::move(o)) {
        solver = makeSolver(opt.solver == SolverChoice::Scip, opt.dump_dir);
    }

    SolverParams params(const char *model_name) const {
        SolverParams p;
        p.time_limit_s = opt.time_limit_s;
        p.gap = opt.mip_gap;
        p.deterministic = opt.deterministic;
        p.seed = opt.seed;
        p.emphasis_feasibility = opt.objective == Objective::Feasibility;
        if (!opt.dump_dir.empty()) p.dump_path = opt.dump_dir + "/" + model_name;
        return p;
    }
};

ResourceModel::ResourceModel(SolveOptions options)
    : options_(options), impl_(std::make_unique<Impl>(std::move(options))) {}
ResourceModel::~ResourceModel() = default;

static SolveStatus toStatus(SolveOutcome o) {
    switch (o) {
        case SolveOutcome::Optimal: return SolveStatus::Optimal;
        case SolveOutcome::Feasible: return SolveStatus::Feasible;
        case SolveOutcome::Infeasible: return SolveStatus::Infeasible;
        case SolveOutcome::TimeoutNoSolution: return SolveStatus::TimeoutNoSolution;
        case SolveOutcome::Error: return SolveStatus::Error;
    }
    return SolveStatus::Error;
}

static StageDiagnostics diag(const char *name, const LinearModel &m, const Solution &s) {
    StageDiagnostics d;
    d.model_name = name;
    d.status = toStatus(s.outcome);
    d.objective_value = s.objective;
    d.best_bound = s.bound;
    d.gap = s.gap;
    d.solve_time_s = s.solve_time_s;
    d.num_vars = m.vars().size();
    d.num_rows = m.rows().size();
    return d;
}

SolveResult ResourceModel::solvePhv(const ModelInputs &in) {
    SolveResult res;
    if (!impl_->solver->available()) {
        res.status = SolveStatus::Error;
        res.message = "no solver available (SCIP not linked)";
        return res;
    }
    PhvModelBuilder b(in);
    LinearModel m = b.build();
    Solution sol = impl_->solver->solve(m, impl_->params("M1-PHV"));
    res.per_stage.push_back(diag("M1-PHV", m, sol));
    res.status = toStatus(sol.outcome);
    if (res.usable()) res.results.phv = b.readBack(sol.values);
    return res;
}

SolveResult ResourceModel::solveMau(const ModelInputs &in, const PhvResult &phv) {
    SolveResult res;
    PhvModelBuilder pb(in);
    auto key_bytes = phv.assignments.empty()
                         ? std::unordered_map<Id, std::vector<Id>>{}
                         : pb.exportKeyBytes(phv);
    MauModelBuilder b(in, std::move(key_bytes));
    LinearModel m = b.build();
    Solution sol = impl_->solver->solve(m, impl_->params("M2-MAU"));
    res.per_stage.push_back(diag("M2-MAU", m, sol));
    res.status = toStatus(sol.outcome);
    if (res.usable()) {
        res.results.phv = phv;
        res.results.mau = b.readBack(sol.values);
    }
    return res;
}

SolveResult ResourceModel::solveVliw(const ModelInputs &in, const MauResult &mau) {
    SolveResult res;
    VliwModelBuilder b(in);
    res.status = SolveStatus::Optimal;
    res.results.mau = mau;
    for (const auto &sub : b.partition(mau)) {
        LinearModel m = b.build(sub);
        Solution sol = impl_->solver->solve(m, impl_->params("M3-VLIW"));
        res.per_stage.push_back(diag("M3-VLIW", m, sol));
        if (sol.outcome == SolveOutcome::Optimal || sol.outcome == SolveOutcome::Feasible) {
            b.readBack(sub, sol.values, &res.results.vliw);
        } else {
            // infeasible subproblem -> caller handles coupling cut (see solve()).
            res.status = SolveStatus::Infeasible;
            res.message = "VLIW infeasible at stage " + std::to_string(sub.stage);
            return res;
        }
    }
    return res;
}

SolveResult ResourceModel::solve(const ModelInputs &in) {
    // --- M1 PHV ---
    SolveResult phvRes = solvePhv(in);
    if (!phvRes.usable()) return phvRes;  // caller falls back (Doc 06 §5)

    // --- M2 MAU with C5 coupling loop (Doc 05 §5) ---
    PhvModelBuilder pb(in);
    auto key_bytes = pb.exportKeyBytes(phvRes.results.phv);
    MauModelBuilder mau(in, key_bytes);
    LinearModel mauModel = mau.build();
    std::vector<StageNoGood> cuts;

    SolveResult out;
    out.per_stage = phvRes.per_stage;
    out.results.phv = phvRes.results.phv;

    for (int iter = 0; iter < options_.max_coupling_iters; ++iter) {
        out.coupling_iterations = iter + 1;
        if (!cuts.empty()) {
            mauModel = mau.build();
            mau.addCuts(mauModel, cuts);
        }
        Solution mauSol = impl_->solver->solve(mauModel, impl_->params("M2-MAU"));
        out.per_stage.push_back(diag("M2-MAU", mauModel, mauSol));
        SolveStatus st = toStatus(mauSol.outcome);
        if (st != SolveStatus::Optimal && st != SolveStatus::Feasible) {
            out.status = st;
            out.message = "MAU placement infeasible / no solution";
            return out;
        }
        MauResult mauResult = mau.readBack(mauSol.values);

        // --- M3 VLIW per (stage, gress) ---
        VliwModelBuilder vb(in);
        bool all_ok = true;
        VliwResult vliw;
        for (const auto &sub : vb.partition(mauResult)) {
            LinearModel vm = vb.build(sub);
            Solution vs = impl_->solver->solve(vm, impl_->params("M3-VLIW"));
            out.per_stage.push_back(diag("M3-VLIW", vm, vs));
            if (vs.outcome == SolveOutcome::Optimal || vs.outcome == SolveOutcome::Feasible) {
                vb.readBack(sub, vs.values, &vliw);
            } else if (auto ng = vb.noGood(sub)) {  // coupling C5
                cuts.push_back(*ng);
                all_ok = false;
                break;
            } else {
                out.status = SolveStatus::Infeasible;
                out.message = "VLIW infeasible, no cut derivable";
                return out;
            }
        }
        if (all_ok) {
            out.status = SolveStatus::Optimal;
            out.results.mau = mauResult;
            out.results.vliw = vliw;
            return out;
        }
        // else: loop with the new cut(s)
    }

    out.status = SolveStatus::TimeoutNoSolution;
    out.message = "coupling iteration cap reached; fall back to legacy";
    return out;
}

}  // namespace ralloc
