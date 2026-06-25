/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/mau_model.h  --  M2: MAU placement + memory MILP builder (Doc 03 §4).
 *
 * Decides, per table: stage, layout option, (optionally) exact RAM cells.
 * Enforces logical-id/SRAM/TCAM/mapram/ixbar/hash/ALU/gateway per-stage budgets
 * (T2,T5-T12), dependency ordering (T3), splitting (T13), attached co-residence
 * (T14). Objective: min stages (O1) > power (O3) > spread (O4).
 */
#ifndef RALLOC_MAU_MODEL_H_
#define RALLOC_MAU_MODEL_H_

#include <unordered_map>
#include <vector>

#include "ralloc/linear_model.h"
#include "ralloc/model_types.h"

namespace ralloc {

/// Optional coupling cut from M3 (Doc 05 §5): tables that cannot share a stage.
struct StageNoGood {
    int stage;
    std::vector<Id> tables;   ///< Sum y[t,stage] <= |tables|-1
};

class MauModelBuilder {
 public:
    /// `key_bytes` is the coupling-C1 parameter from PhvModelBuilder (may be
    /// empty, in which case option-level ixbar demand is used).
    MauModelBuilder(const ModelInputs &in,
                    std::unordered_map<Id, std::vector<Id>> key_bytes = {})
        : in_(in), key_bytes_(std::move(key_bytes)) {}

    LinearModel build();

    /// Add Benders-style no-good cuts before re-solving (Doc 05 §5).
    void addCuts(LinearModel &, const std::vector<StageNoGood> &);

    MauResult readBack(const std::vector<double> &var_values) const;

    // Variable lookups.
    VarRef s(Id table, Id option, int stage) const;   ///< s[t,o,k]
    VarRef y(Id table, int stage) const;              ///< y[t,k]
    VarRef useStage(int stage) const;                 ///< useStage[k]

 private:
    const ModelInputs &in_;
    std::unordered_map<Id, std::vector<Id>> key_bytes_;
    std::unordered_map<long long, VarRef> s_, y_, xb_;
    std::unordered_map<int, VarRef> use_;

    void addSelection(LinearModel &);        ///< (10)(10a-c)(11)(12)
    void addCapacities(LinearModel &);       ///< (13)-(23)
    void addCrossbarBytes(LinearModel &);    ///< (17a)(17b) using key_bytes_
    void addDependencies(LinearModel &);     ///< (24)
    void addFineMemory(LinearModel &);       ///< §4.5 (optional)
    void addObjective(LinearModel &);        ///< §4.3
};

}  // namespace ralloc

#endif  // RALLOC_MAU_MODEL_H_
