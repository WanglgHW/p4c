// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#ifndef DSLX_P4_ADAPTER_P4_PARSER_LOWER_H_
#define DSLX_P4_ADAPTER_P4_PARSER_LOWER_H_

#include <string>

#include "../dslx_ir/module.h"
#include "lower_context.h"

namespace P4::DSLX::adapter {

void LowerParser(const IR::P4Parser* parser, const LowerContext& ctx,
                 const std::string& gress_name, ::dslx_ir::Module* module);

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_P4_PARSER_LOWER_H_
