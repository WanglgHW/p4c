/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * LinearModel helpers + CPLEX .lp exporter (Doc 05 §9). Self-contained: no
 * solver dependency, so it is always built and unit-tested.
 */
#include "ralloc/linear_model.h"

#include <cmath>
#include <sstream>

namespace ralloc {

void LinearModel::addLinear(const std::string &name, const std::vector<VarRef> &vars,
                            const std::vector<double> &coeffs, Sense sense, double rhs) {
    Row r;
    r.name = name;
    r.vars = vars;
    r.coeffs = coeffs;
    r.sense = sense;
    r.rhs = rhs;
    rows_.push_back(std::move(r));
}

std::size_t LinearModel::numBinary() const {
    std::size_t n = 0;
    for (const auto &v : vars_)
        if (v.type == VarType::Binary) ++n;
    return n;
}

static const char *senseStr(Sense s) {
    switch (s) {
        case Sense::LE: return " <= ";
        case Sense::GE: return " >= ";
        case Sense::EQ: return " = ";
    }
    return " ? ";
}

static void emitRow(std::ostringstream &os, const LinearModel &m, const Row &r) {
    bool first = true;
    for (std::size_t i = 0; i < r.vars.size(); ++i) {
        double c = r.coeffs[i];
        if (c == 0.0) continue;
        os << (first ? "" : " ") << (c >= 0 && !first ? "+ " : (c < 0 ? "- " : ""));
        double a = c < 0 ? -c : c;
        if (a != 1.0) os << a << ' ';
        os << m.vars()[r.vars[i]].name;
        first = false;
    }
    if (first) os << "0";
    os << senseStr(r.sense) << r.rhs;
}

/// CPLEX LP format. Sufficient for SCIP/HiGHS/Gurobi import and golden tests.
std::string LinearModel::toLpString() const {
    std::ostringstream os;
    os << "\\ ralloc model: " << name_ << "\n";
    os << (obj_sense_ == ObjSense::Minimize ? "Minimize\n obj: " : "Maximize\n obj: ");
    bool first = true;
    for (const auto &v : vars_) {
        if (v.obj == 0.0) continue;
        os << (first ? "" : " ") << (v.obj >= 0 && !first ? "+ " : (v.obj < 0 ? "- " : ""));
        double a = v.obj < 0 ? -v.obj : v.obj;
        if (a != 1.0) os << a << ' ';
        os << v.name;
        first = false;
    }
    if (first) os << "0";
    os << "\nSubject To\n";
    for (const auto &r : rows_) {
        os << ' ' << (r.name.empty() ? "c" : r.name) << ": ";
        emitRow(os, *this, r);
        os << "\n";
    }
    // Indicator rows in LP "->" syntax.
    for (const auto &ir : indicators_) {
        os << ' ' << ir.name << ": " << vars_[ir.trigger].name << " = "
           << (ir.trigger_value ? 1 : 0) << " -> ";
        emitRow(os, *this, ir.implied);
        os << "\n";
    }
    // Bounds + integrality.
    os << "Bounds\n";
    for (const auto &v : vars_) {
        if (v.type == VarType::Binary) continue;
        os << ' ' << v.lb << " <= " << v.name << " <= " << v.ub << "\n";
    }
    os << "Binary\n";
    for (const auto &v : vars_)
        if (v.type == VarType::Binary) os << ' ' << v.name << "\n";
    os << "General\n";
    for (const auto &v : vars_)
        if (v.type == VarType::Integer) os << ' ' << v.name << "\n";
    os << "End\n";
    return os.str();
}

// ---------------------------------------------------------------------------
// MiniZinc exporter (OR-Tools CP-SAT backend).
// ---------------------------------------------------------------------------

/// Print a number the way MiniZinc wants it: an integral value becomes a bare
/// integer literal (so it stays in the int domain CP-SAT solves natively);
/// anything genuinely fractional falls back to a float literal.
static void fmtNum(std::ostringstream &os, double v) {
    if (std::isfinite(v) && v == std::floor(v) && std::fabs(v) < 9.0e15)
        os << static_cast<long long>(v);
    else
        os << v;
}

static const char *mznSense(Sense s) {
    switch (s) {
        case Sense::LE: return " <= ";
        case Sense::GE: return " >= ";
        case Sense::EQ: return " = ";
    }
    return " = ";
}

/// Emit `c0*v0 + c1*v1 + ...` for a row (zero-coeff terms dropped).
static void emitMznExpr(std::ostringstream &os, const Row &r) {
    bool first = true;
    for (std::size_t i = 0; i < r.vars.size(); ++i) {
        double c = r.coeffs[i];
        if (c == 0.0) continue;
        double a = c < 0 ? -c : c;
        os << (first ? (c < 0 ? "-" : "") : (c < 0 ? " - " : " + "));
        if (a != 1.0) {
            fmtNum(os, a);
            os << "*";
        }
        os << 'v' << r.vars[i];
        first = false;
    }
    if (first) os << '0';
}

/// A finite integer bound for MiniZinc domains (CP-SAT needs bounded ints).
static long long mznIntBound(double b, long long fallback) {
    if (!std::isfinite(b) || std::fabs(b) >= 9.0e15) return fallback;
    return static_cast<long long>(b);
}

std::string LinearModel::toMiniZincString() const {
    std::ostringstream os;
    os << "% ralloc model: " << name_ << " (MiniZinc / OR-Tools CP-SAT)\n";
    os << "% variables are v<i>, indexed by VarRef; see toMiniZincString().\n\n";

    // --- variable declarations ---
    for (std::size_t i = 0; i < vars_.size(); ++i) {
        const Var &v = vars_[i];
        switch (v.type) {
            case VarType::Binary:
                os << "var 0..1: v" << i << ";";
                break;
            case VarType::Integer:
                os << "var " << mznIntBound(v.lb, -1000000000) << ".."
                   << mznIntBound(v.ub, 1000000000) << ": v" << i << ";";
                break;
            case VarType::Continuous: {
                os << "var ";
                fmtNum(os, std::isfinite(v.lb) ? v.lb : -1.0e15);
                os << "..";
                fmtNum(os, std::isfinite(v.ub) ? v.ub : 1.0e15);
                os << ": v" << i << ";";
                break;
            }
        }
        os << "  % " << v.name << "\n";
    }
    os << "\n";

    // --- linear constraints ---
    for (const Row &r : rows_) {
        os << "constraint ";
        if (!r.name.empty()) os << "% " << r.name << "\n    ";
        emitMznExpr(os, r);
        os << mznSense(r.sense);
        fmtNum(os, r.rhs);
        os << ";\n";
    }

    // --- indicator constraints: (trigger = value) -> (row) ---
    for (const IndicatorRow &ir : indicators_) {
        os << "constraint (v" << ir.trigger << " = " << (ir.trigger_value ? 1 : 0)
           << ") -> (";
        emitMznExpr(os, ir.implied);
        os << mznSense(ir.implied.sense);
        fmtNum(os, ir.implied.rhs);
        os << ");  % " << ir.name << "\n";
    }
    os << "\n";

    // --- objective ---
    bool hasObj = false;
    std::ostringstream obj;
    {
        bool first = true;
        for (std::size_t i = 0; i < vars_.size(); ++i) {
            double c = vars_[i].obj;
            if (c == 0.0) continue;
            hasObj = true;
            double a = c < 0 ? -c : c;
            obj << (first ? (c < 0 ? "-" : "") : (c < 0 ? " - " : " + "));
            if (a != 1.0) {
                fmtNum(obj, a);
                obj << "*";
            }
            obj << 'v' << i;
            first = false;
        }
    }
    if (hasObj)
        os << "solve " << (obj_sense_ == ObjSense::Minimize ? "minimize" : "maximize")
           << " (" << obj.str() << ");\n\n";
    else
        os << "solve satisfy;\n\n";

    // --- output: one `v<i>=<value>` line per variable, parsed by the backend ---
    os << "output [\n";
    for (std::size_t i = 0; i < vars_.size(); ++i) {
        os << "  \"v" << i << "=\", show(v" << i << "), \"\\n\""
           << (i + 1 < vars_.size() ? "," : "") << "\n";
    }
    os << "];\n";
    return os.str();
}

}  // namespace ralloc
