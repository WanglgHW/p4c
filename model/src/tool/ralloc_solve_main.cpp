/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc-solve — the standalone MILP solver process.
 *
 * Reads a model_input.json (ralloc::ModelInputs), solves M2 (MAU/memory) then
 * M3 (VLIW/action) with OR-Tools, and writes a model_out.json
 * (ralloc::ModelResults) for the compiler's resume phase. This is the ONLY
 * process that links/runs OR-Tools, so the solver no longer executes inside
 * p4c-barefoot's GC-overridden allocator (which made an in-process re-solve
 * crash); see model/doc.
 *
 * Usage:
 *   ralloc-solve <model_input.json> -o <model_out.json>
 *                [--time-limit <s>] [--gap <frac>] [--seed <n>]
 *                [--objective stage|power|phv|feasible|lex] [--dump-dir <dir>]
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "ralloc/model_json.h"
#include "ralloc/resource_model.h"

namespace {

void usage(const char *prog) {
    std::cerr << "usage: " << prog << " <model_input.json> -o <model_out.json>\n"
              << "       [--time-limit <s>] [--gap <frac>] [--seed <n>]\n"
              << "       [--objective stage|power|phv|feasible|lex] [--dump-dir <dir>]\n";
}

ralloc::Objective parseObjective(const std::string &s) {
    if (s == "stage") return ralloc::Objective::MinStages;
    if (s == "power") return ralloc::Objective::MinPower;
    if (s == "phv") return ralloc::Objective::MinPhv;
    if (s == "feasible") return ralloc::Objective::Feasibility;
    return ralloc::Objective::Lexicographic;
}

}  // namespace

int main(int argc, char **argv) {
    std::string in_path, out_path;
    ralloc::SolveOptions opt;
    opt.objective = ralloc::Objective::MinStages;  // matches the in-tree pass default
    opt.warm_start = true;
    opt.deterministic = true;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        auto next = [&](const char *flag) -> std::string {
            if (i + 1 >= argc) {
                std::cerr << "ralloc-solve: missing value for " << flag << "\n";
                std::exit(2);
            }
            return argv[++i];
        };
        if (a == "-o" || a == "--out") {
            out_path = next("-o");
        } else if (a == "--time-limit") {
            opt.time_limit_s = std::stod(next("--time-limit"));
        } else if (a == "--gap") {
            opt.mip_gap = std::stod(next("--gap"));
        } else if (a == "--seed") {
            opt.seed = static_cast<unsigned>(std::stoul(next("--seed")));
        } else if (a == "--objective") {
            opt.objective = parseObjective(next("--objective"));
        } else if (a == "--dump-dir") {
            opt.dump_dir = next("--dump-dir");
        } else if (a == "-h" || a == "--help") {
            usage(argv[0]);
            return 0;
        } else if (!a.empty() && a[0] == '-') {
            std::cerr << "ralloc-solve: unknown option " << a << "\n";
            usage(argv[0]);
            return 2;
        } else if (in_path.empty()) {
            in_path = a;
        } else {
            std::cerr << "ralloc-solve: unexpected argument " << a << "\n";
            usage(argv[0]);
            return 2;
        }
    }

    if (in_path.empty() || out_path.empty()) {
        usage(argv[0]);
        return 2;
    }

    ralloc::ModelInputs inputs;
    try {
        inputs = ralloc::readModelInputsFile(in_path);
    } catch (const std::exception &e) {
        std::cerr << "ralloc-solve: failed to read " << in_path << ": " << e.what() << "\n";
        return 1;
    }

    if (!ralloc::hasOrTools()) {
        std::cerr << "ralloc-solve: OR-Tools not linked — cannot solve (build with OR-Tools)\n";
        return 1;
    }

    // M2 over the legacy PHV (empty PhvResult => option-level ixbar demand), then
    // M3 for the resulting placement. Mirrors RallocModelPass (ralloc_model_pass.cpp).
    ralloc::ResourceModel model(opt);
    ralloc::SolveResult mau = model.solveMau(inputs, /*phv=*/{});
    if (!mau.usable()) {
        std::cerr << "ralloc-solve: MAU placement not usable (" << mau.message << ")\n";
        return 1;
    }
    ralloc::SolveResult vliw = model.solveVliw(inputs, mau.results.mau);
    if (vliw.usable()) mau.results.vliw = vliw.results.vliw;

    try {
        ralloc::writeModelResultsFile(mau.results, out_path);
    } catch (const std::exception &e) {
        std::cerr << "ralloc-solve: failed to write " << out_path << ": " << e.what() << "\n";
        return 1;
    }

    std::cerr << "ralloc-solve: solved — " << mau.results.mau.stages_used << " stage(s), "
              << mau.results.mau.tables.size() << " table(s); wrote " << out_path << "\n";
    return 0;
}
