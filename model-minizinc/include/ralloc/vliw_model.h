/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/vliw_model.h  --  M3: VLIW/action allocation Binary-ILP (Doc 03 §5).
 *
 * Solved per (stage, gress): assigns each active action to an imem (row,color)
 * with the ALU-disjointness coloring rule (V1-V4), and each action-data field
 * to a bus byte slot (V5-V6), under stateful caps (V7). If a (stage,gress) is
 * infeasible, produces a StageNoGood cut for M2 (coupling C5).
 */
#ifndef RALLOC_VLIW_MODEL_H_
#define RALLOC_VLIW_MODEL_H_

#include <optional>
#include <vector>

#include "ralloc/linear_model.h"
#include "ralloc/mau_model.h"   // StageNoGood
#include "ralloc/model_types.h"

namespace ralloc {

/// Sub-instance: the actions/adata active in one (stage, gress).
struct VliwSubproblem {
    int stage;
    Gress gress;
    std::vector<Id> action_ids;
    std::vector<Id> table_ids;     ///< source tables (for StageNoGood)
};

class VliwModelBuilder {
 public:
    explicit VliwModelBuilder(const ModelInputs &in) : in_(in) {}

    /// Partition the MAU result into per-(stage,gress) subproblems.
    std::vector<VliwSubproblem> partition(const MauResult &) const;

    /// Build the tiny MILP for one subproblem.
    LinearModel build(const VliwSubproblem &);

    /// Read one subproblem's solution.
    void readBack(const VliwSubproblem &, const std::vector<double> &var_values,
                  VliwResult *out) const;

    /// If `var_values` is empty (infeasible), build the no-good cut for M2.
    std::optional<StageNoGood> noGood(const VliwSubproblem &) const;

    VarRef rcol(Id action, int row, int color) const;  ///< rcol[a,row,color]
    VarRef slot(Id field, int bus_byte) const;         ///< slot[f,beta]

 private:
    const ModelInputs &in_;

    void addRowColoring(LinearModel &, const VliwSubproblem &);  ///< (25)-(27)
    void addActionData(LinearModel &, const VliwSubproblem &);   ///< (28)-(30)
    void addStatefulCaps(LinearModel &, const VliwSubproblem &); ///< (V7)
};

}  // namespace ralloc

#endif  // RALLOC_VLIW_MODEL_H_
