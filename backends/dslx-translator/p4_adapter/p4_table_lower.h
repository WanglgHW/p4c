// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#ifndef DSLX_P4_ADAPTER_P4_TABLE_LOWER_H_
#define DSLX_P4_ADAPTER_P4_TABLE_LOWER_H_

#include <memory>

#include "../dslx_ir/ast.h"
#include "../dslx_ir/module.h"
#include "lower_context.h"

namespace P4::DSLX::adapter {

/// Add the entry-struct definition AND the table_<name>_apply function for
/// `table` to `module`.
void LowerTable(const IR::P4Table* table, const LowerContext& ctx,
                ::dslx_ir::Module* module);

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_P4_TABLE_LOWER_H_
