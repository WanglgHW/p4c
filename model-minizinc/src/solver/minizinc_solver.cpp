/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * SolverBackend implementations backed by MiniZinc + OR-Tools CP-SAT.
 *
 * MiniZincBackend serialises a LinearModel to a `.mzn` file (LinearModel::
 * toMiniZincString), then runs `minizinc --solver <cp-sat> ...` as a child
 * process, capturing the FlatZinc solver's output on stdout. The output block
 * emitted by toMiniZincString prints one `v<i>=<value>` line per variable, plus
 * MiniZinc's standard solution/optimality markers:
 *
 *   ----------            a solution was printed (block separator)
 *   ==========            the last solution is proven optimal
 *   =====UNSATISFIABLE=== the model is infeasible
 *   =====UNKNOWN=====     search stopped with no solution (e.g. time limit)
 *   =====ERROR=====       MiniZinc / solver error
 *
 * There is no compile-time dependency on any solver library; availability is a
 * runtime probe of the `minizinc` binary. If it is missing, the facade forces
 * the legacy fallback (parallel to the old SCIP-less path).
 */
#include "ralloc/minizinc_solver.h"

#include <unistd.h>

#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace ralloc {

namespace {

std::string envOr(const char *key, const char *fallback) {
    const char *v = std::getenv(key);
    return (v && *v) ? std::string(v) : std::string(fallback);
}

/// Run a shell command, capturing merged stdout+stderr. Returns false if the
/// process could not be launched at all.
bool runCapture(const std::string &cmd, std::string *out, int *exit_code) {
    std::FILE *pipe = ::popen((cmd + " 2>&1").c_str(), "r");
    if (!pipe) return false;
    std::array<char, 4096> buf{};
    std::string acc;
    while (std::size_t n = std::fread(buf.data(), 1, buf.size(), pipe))
        acc.append(buf.data(), n);
    int rc = ::pclose(pipe);
    if (out) *out = std::move(acc);
    if (exit_code) *exit_code = rc;
    return true;
}

/// Single-quote a path for a POSIX shell command line.
std::string shellQuote(const std::string &s) {
    std::string q = "'";
    for (char c : s) {
        if (c == '\'')
            q += "'\\''";
        else
            q += c;
    }
    q += "'";
    return q;
}

}  // namespace

// ---------------------------------------------------------------------------
// MznExportBackend: write the .mzn and return "no solution" (CI path).
// ---------------------------------------------------------------------------
Solution MznExportBackend::solve(const LinearModel &m, const SolverParams &) {
    std::ofstream(out_path_) << m.toMiniZincString();
    Solution s;
    s.outcome = SolveOutcome::TimeoutNoSolution;  // export-only never solves
    return s;
}

// ---------------------------------------------------------------------------
// MiniZincBackend
// ---------------------------------------------------------------------------
struct MiniZincBackend::Impl {
    std::string minizinc = envOr("RALLOC_MINIZINC", "minizinc");
    std::string solver = envOr("RALLOC_MINIZINC_SOLVER", "cp-sat");
    std::vector<double> warm;  ///< stored for interface parity (see solve()).

    bool probe() const {
        std::string out;
        int rc = -1;
        if (!runCapture(shellQuote(minizinc) + " --version", &out, &rc)) return false;
        return rc == 0;
    }

    Solution run(const LinearModel &m, const SolverParams &p) {
        Solution out;

        // 1. Serialise the model. Keep it next to the dump path if requested so
        //    it can be inspected; otherwise use a unique temp file we remove.
        namespace fs = std::filesystem;
        bool keep = !p.dump_path.empty();
        fs::path mzn = keep ? fs::path(p.dump_path + ".mzn")
                            : fs::temp_directory_path() /
                                  ("ralloc_" + std::to_string(::getpid()) + "_" +
                                   std::to_string(reinterpret_cast<std::uintptr_t>(&m)) + ".mzn");
        {
            std::ofstream f(mzn);
            if (!f) {
                out.outcome = SolveOutcome::Error;
                return out;
            }
            f << m.toMiniZincString();
        }

        // 2. Build the command. `--time-limit` is milliseconds; `-p 1` keeps the
        //    CP-SAT search single-threaded for reproducibility.
        std::ostringstream cmd;
        cmd << shellQuote(minizinc) << " --solver " << shellQuote(solver);
        long long ms = static_cast<long long>(p.time_limit_s * 1000.0);
        if (ms > 0) cmd << " --time-limit " << ms;
        if (p.deterministic) cmd << " -p 1 -r " << p.seed;
        cmd << " " << shellQuote(mzn.string());

        // 3. Solve.
        auto t0 = std::chrono::steady_clock::now();
        std::string text;
        int rc = -1;
        bool launched = runCapture(cmd.str(), &text, &rc);
        auto t1 = std::chrono::steady_clock::now();
        out.solve_time_s = std::chrono::duration<double>(t1 - t0).count();

        if (!keep) {
            std::error_code ec;
            fs::remove(mzn, ec);
        }
        if (keep) std::ofstream(p.dump_path + ".log") << text;

        if (!launched) {
            out.outcome = SolveOutcome::Error;
            return out;
        }

        // 4. Parse markers + `v<i>=<value>` lines (last solution block wins).
        std::unordered_map<std::size_t, double> vals;
        bool sawUnsat = false, sawError = false, sawOptimal = false, parsedAny = false;
        std::istringstream in(text);
        std::string line;
        while (std::getline(in, line)) {
            if (line.rfind("=====UNSATISFIABLE", 0) == 0) {
                sawUnsat = true;
            } else if (line.rfind("=====ERROR", 0) == 0 ||
                       line.rfind("=====UNBOUNDED", 0) == 0) {
                sawError = true;
            } else if (line.rfind("==========", 0) == 0) {
                sawOptimal = true;
            } else if (line.size() > 2 && line[0] == 'v' &&
                       (line[1] >= '0' && line[1] <= '9')) {
                auto eq = line.find('=');
                if (eq == std::string::npos) continue;
                std::size_t idx = 0;
                try {
                    idx = static_cast<std::size_t>(std::stoul(line.substr(1, eq - 1)));
                } catch (...) {
                    continue;
                }
                std::string rhs = line.substr(eq + 1);
                double val = 0.0;
                if (rhs.rfind("true", 0) == 0) {
                    val = 1.0;
                } else if (rhs.rfind("false", 0) == 0) {
                    val = 0.0;
                } else {
                    try {
                        val = std::stod(rhs);
                    } catch (...) {
                        continue;
                    }
                }
                vals[idx] = val;
                parsedAny = true;
            }
        }

        // 5. Assemble the solution.
        if (sawError && !parsedAny) {
            out.outcome = SolveOutcome::Error;
            return out;
        }
        if (sawUnsat) {
            out.outcome = SolveOutcome::Infeasible;
            return out;
        }
        if (!parsedAny) {
            out.outcome = SolveOutcome::TimeoutNoSolution;
            return out;
        }

        out.values.assign(m.vars().size(), 0.0);
        for (const auto &kv : vals)
            if (kv.first < out.values.size()) out.values[kv.first] = kv.second;

        double obj = 0.0;
        for (std::size_t i = 0; i < m.vars().size(); ++i) obj += m.vars()[i].obj * out.values[i];
        out.objective = obj;
        out.outcome = sawOptimal ? SolveOutcome::Optimal : SolveOutcome::Feasible;
        if (out.outcome == SolveOutcome::Optimal) {
            out.bound = obj;
            out.gap = 0.0;
        }
        return out;
    }
};

MiniZincBackend::MiniZincBackend() : impl_(std::make_unique<Impl>()) {}
MiniZincBackend::~MiniZincBackend() = default;

bool MiniZincBackend::available() const {
    static const bool ok = impl_->probe();
    return ok;
}

void MiniZincBackend::setWarmStart(const std::vector<double> &seed) { impl_->warm = seed; }

Solution MiniZincBackend::solve(const LinearModel &m, const SolverParams &p) {
    if (!available()) {
        Solution s;
        s.outcome = SolveOutcome::Error;
        return s;
    }
    return impl_->run(m, p);
}

std::unique_ptr<SolverBackend> makeSolver(bool prefer_minizinc, std::string dump_dir) {
    if (prefer_minizinc) {
        auto b = std::make_unique<MiniZincBackend>();
        if (b->available()) return b;
    }
    return std::make_unique<MznExportBackend>(dump_dir.empty() ? "ralloc_model.mzn"
                                                               : dump_dir + "/ralloc_model.mzn");
}

}  // namespace ralloc
