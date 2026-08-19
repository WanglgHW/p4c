/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/linear_model.h
 *
 * A solver-agnostic representation of a MILP (Doc 05 §1). Model builders emit a
 * LinearModel; a SolverBackend (MiniZinc/OR-Tools CP-SAT, or .mzn/.lp export)
 * consumes it. This isolates the formula logic (Doc 03) from any specific solver
 * API and enables .mzn/.lp export for cross-solver validation and unit tests.
 */
#ifndef RALLOC_LINEAR_MODEL_H_
#define RALLOC_LINEAR_MODEL_H_

#include <limits>
#include <string>
#include <vector>

namespace ralloc {

enum class VarType { Binary, Integer, Continuous };
enum class Sense { LE, GE, EQ };
enum class ObjSense { Minimize, Maximize };

using VarRef = int;   ///< index into LinearModel::vars

struct Var {
    std::string name;
    VarType type = VarType::Binary;
    double lb = 0.0;
    double ub = 1.0;
    double obj = 0.0;     ///< objective coefficient
};

/// A linear row: sum_i coeff[i]*var[i]  (sense)  rhs.
struct Row {
    std::string name;
    std::vector<VarRef> vars;
    std::vector<double> coeffs;
    Sense sense = Sense::LE;
    double rhs = 0.0;
};

/// Native indicator row (Doc 03 §8): when binary `trigger`==1, the linear row
/// must hold. Preferred over big-M; emitted as a MiniZinc implication
/// (`(trigger = v) -> (row)`) and supported natively by CP-SAT.
struct IndicatorRow {
    std::string name;
    VarRef trigger;
    bool trigger_value = true;
    Row implied;
};

/// Solver-agnostic MILP. Build incrementally, then hand to a SolverBackend.
class LinearModel {
 public:
    explicit LinearModel(std::string name = "ralloc") : name_(std::move(name)) {}

    VarRef addVar(std::string name, VarType t, double lb, double ub, double obj = 0.0) {
        vars_.push_back({std::move(name), t, lb, ub, obj});
        return static_cast<VarRef>(vars_.size()) - 1;
    }
    VarRef addBinary(std::string name, double obj = 0.0) {
        return addVar(std::move(name), VarType::Binary, 0.0, 1.0, obj);
    }

    void addRow(Row r) { rows_.push_back(std::move(r)); }
    void addIndicator(IndicatorRow r) { indicators_.push_back(std::move(r)); }

    /// Convenience: sum(vars) (sense) rhs.
    void addLinear(const std::string &name, const std::vector<VarRef> &vars,
                   const std::vector<double> &coeffs, Sense sense, double rhs);

    void setObjSense(ObjSense s) { obj_sense_ = s; }

    // --- accessors ---
    const std::string &name() const { return name_; }
    const std::vector<Var> &vars() const { return vars_; }
    const std::vector<Row> &rows() const { return rows_; }
    const std::vector<IndicatorRow> &indicators() const { return indicators_; }
    ObjSense objSense() const { return obj_sense_; }
    std::size_t numBinary() const;

    /// Emit CPLEX .lp text (used for export + golden tests, Doc 05 §9).
    std::string toLpString() const;

    /// Emit a MiniZinc model (`.mzn`). Variables are declared as `v0..vN`
    /// (indexed by VarRef) so arbitrary LP names never collide with MiniZinc
    /// identifier rules; the trailing `output` block prints `v<i>=<value>` lines
    /// that MiniZincBackend parses back. Since every ralloc variable is binary
    /// (and coefficients are integral), the emitted model is a pure integer
    /// program — the ideal shape for the OR-Tools CP-SAT backend.
    std::string toMiniZincString() const;

 private:
    std::string name_;
    std::vector<Var> vars_;
    std::vector<Row> rows_;
    std::vector<IndicatorRow> indicators_;
    ObjSense obj_sense_ = ObjSense::Minimize;
};

}  // namespace ralloc

#endif  // RALLOC_LINEAR_MODEL_H_
