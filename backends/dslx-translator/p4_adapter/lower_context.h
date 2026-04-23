// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Per-pipeline-block context shared across the small lowering passes
// (parser/control/action/table/deparser → dslx_ir nodes).
//
// This struct concentrates *all* of the P4-IR types the lowering passes need.
// Anything that touches `IR::*` lives in the p4_adapter/ tree only.

#ifndef DSLX_P4_ADAPTER_LOWER_CONTEXT_H_
#define DSLX_P4_ADAPTER_LOWER_CONTEXT_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "frontends/common/resolveReferences/referenceMap.h"
#include "frontends/p4/typeMap.h"
#include "ir/ir.h"

namespace P4::DSLX::adapter {

/// Describes one pipeline block (parser, control, or deparser) and its
/// typed parameters.
struct PipelineBlockInfo {
    const IR::IContainer* block = nullptr;
    std::string name;
    std::string headers_type_name;
    std::string meta_type_name;
    /// (param_var, dslx_type_name) for intrinsic metadata params
    std::vector<std::pair<std::string, std::string>> intrinsic_params;
    /// All threaded params (headers + meta + intrinsic) in declaration order
    std::vector<std::pair<std::string, std::string>> all_threaded;

    bool empty() const { return block == nullptr; }
};

struct GressPipeline {
    PipelineBlockInfo parser;
    PipelineBlockInfo control;
    PipelineBlockInfo deparser;
};

/// Read-only context object passed by reference to every lowering pass.
struct LowerContext {
    const IR::P4Program* program = nullptr;
    P4::ReferenceMap* refMap = nullptr;
    P4::TypeMap* typeMap = nullptr;
    /// The block being lowered.
    const PipelineBlockInfo* block_info = nullptr;
    /// P4 parameter name -> DSLX variable name (identity for now).
    std::map<std::string, std::string> param_name_map;
    /// Pipeline-wide constants (set once at program level).
    unsigned max_packet_bits = 12000;
    unsigned max_table_entries = 1024;
};

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_LOWER_CONTEXT_H_
