// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Top-level orchestrator: lowers an entire TNA Pipeline package to a single
// dslx_ir Module. This is the only file in p4_adapter/ that the public
// dslxBackend translation driver needs to call.

#ifndef DSLX_P4_ADAPTER_P4_TO_DSLX_H_
#define DSLX_P4_ADAPTER_P4_TO_DSLX_H_

#include <memory>

#include "../dslx_ir/module.h"
#include "frontends/common/resolveReferences/referenceMap.h"
#include "frontends/p4/typeMap.h"
#include "ir/ir.h"

namespace P4::DSLX::adapter {

struct LowerOptions {
    unsigned max_packet_bits = 12000;
    unsigned max_table_entries = 1024;
};

/// Lower a single TNA Pipeline package to a complete dslx_ir Module.
/// Returns nullptr if the pipeline cannot be analysed.
std::unique_ptr<::dslx_ir::Module> LowerPipelineToModule(
    const IR::P4Program* program, P4::ReferenceMap* refMap,
    P4::TypeMap* typeMap, const IR::PackageBlock* pipeline_block,
    const LowerOptions& opts);

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_P4_TO_DSLX_H_
