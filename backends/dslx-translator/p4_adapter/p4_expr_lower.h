// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Lowers P4 IR expressions to dslx_ir Expr nodes.

#ifndef DSLX_P4_ADAPTER_P4_EXPR_LOWER_H_
#define DSLX_P4_ADAPTER_P4_EXPR_LOWER_H_

#include "../dslx_ir/ast.h"
#include "lower_context.h"

namespace P4::DSLX::adapter {

/// Recursively lower a P4 expression to a dslx_ir Expr.
::dslx_ir::ExprPtr LowerExpr(const IR::Expression* expr, const LowerContext& ctx);

/// Convenience: render an expression to a textual identifier (used for
/// table-key naming where we need a stable string instead of an Expr).
std::string ExprToTextualName(const IR::Expression* expr,
                              const LowerContext& ctx);

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_P4_EXPR_LOWER_H_
