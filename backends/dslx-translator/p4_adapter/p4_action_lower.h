// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Lowers P4 actions to dslx_ir Function declarations.

#ifndef DSLX_P4_ADAPTER_P4_ACTION_LOWER_H_
#define DSLX_P4_ADAPTER_P4_ACTION_LOWER_H_

#include <memory>

#include "../dslx_ir/ast.h"
#include "lower_context.h"

namespace P4::DSLX::adapter {

std::unique_ptr<::dslx_ir::Function> LowerAction(const IR::P4Action* action,
                                                  const LowerContext& ctx);

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_P4_ACTION_LOWER_H_
