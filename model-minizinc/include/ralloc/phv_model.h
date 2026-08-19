/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * ralloc/phv_model.h  --  M1: PHV allocation Binary-ILP builder (Doc 03 §3).
 *
 * Builds a LinearModel whose optimum assigns each field slice to a (container,
 * bit-offset) honoring type/kind/alignment (P2,P6,P7,P10), no-overlap/overlay
 * (P3,P4), pack conflicts (P5), action-source reachability (P11) and crossbar
 * locality (P8/C1). Reads back into a PhvResult.
 */
#ifndef RALLOC_PHV_MODEL_H_
#define RALLOC_PHV_MODEL_H_

#include <unordered_map>

#include "ralloc/linear_model.h"
#include "ralloc/model_types.h"

namespace ralloc {

class PhvModelBuilder {
 public:
    explicit PhvModelBuilder(const ModelInputs &in) : in_(in) {}

    /// Emit the M1 MILP (variables x[s,c], p[s,c,o], u[c]; constraints 1-9).
    LinearModel build();

    /// Translate a solved variable assignment into PhvResult (containerOf(s),
    /// bit offsets, containers used).
    PhvResult readBack(const std::vector<double> &var_values) const;

    /// Coupling C1 export: for each table, the set of crossbar-byte ids its key
    /// can use given this PHV assignment (consumed by MauModelBuilder).
    std::unordered_map<Id, std::vector<Id>> exportKeyBytes(const PhvResult &) const;

    // Variable lookups (also used by readBack and warm-start seeding).
    VarRef x(Id slice, Id container) const;     ///< x[s,c]
    VarRef p(Id slice, Id container, int off) const;  ///< p[s,c,o]
    VarRef u(Id container) const;               ///< u[c]

 private:
    const ModelInputs &in_;
    // index maps populated in build()
    std::unordered_map<long long, VarRef> x_, p_;
    std::unordered_map<Id, VarRef> u_;

    void addAssignment(LinearModel &);     ///< (1)(2)(7)
    void addLegality(LinearModel &);       ///< (3)
    void addOverlap(LinearModel &);        ///< (4)(4')(5)(6)
    void addCrossbarLocality(LinearModel &); ///< (8)
    void addExtractorBalance(LinearModel &); ///< (9)
    void addObjective(LinearModel &);      ///< §3.3
};

}  // namespace ralloc

#endif  // RALLOC_PHV_MODEL_H_
