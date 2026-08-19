/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * LinearModel helpers + CPLEX .lp exporter (Doc 05 §9). Self-contained: no
 * solver dependency, so it is always built and unit-tested.
 */
#include "ralloc/linear_model.h"

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

/// CPLEX LP format. Sufficient for OR-Tools/HiGHS/Gurobi import and golden tests.
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

}  // namespace ralloc
