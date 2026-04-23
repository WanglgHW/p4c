// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#ifndef DSLX_P4_ADAPTER_P4_DEPARSER_LOWER_H_
#define DSLX_P4_ADAPTER_P4_DEPARSER_LOWER_H_

#include <string>

#include "../dslx_ir/module.h"
#include "lower_context.h"

namespace P4::DSLX::adapter {

/// Append the gress deparser as a function `<gress>_deparser_apply` to
/// `module`. The function takes the headers value (and any threaded params
/// the deparser sees) and returns `bits[MAX_PACKET_BITS]`.
void LowerDeparser(const IR::P4Control* deparser, const LowerContext& ctx,
                   const std::string& gress_name, ::dslx_ir::Module* module);

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_P4_DEPARSER_LOWER_H_
