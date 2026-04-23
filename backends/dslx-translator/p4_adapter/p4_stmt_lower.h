// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Lowers a single P4 statement (assignment, if, method-call, decl) to a
// sequence of dslx_ir::Stmt, threading the (headers, meta, intrinsic) tuple.
// Shared between action bodies (DslxAction) and control bodies (DslxControl).

#ifndef DSLX_P4_ADAPTER_P4_STMT_LOWER_H_
#define DSLX_P4_ADAPTER_P4_STMT_LOWER_H_

#include <vector>

#include "../dslx_ir/ast.h"
#include "lower_context.h"

namespace P4::DSLX::adapter {

/// Lower a single P4 statement; appends to `out`.
/// `enable_table_apply` — only true inside control bodies; if true, table
/// `.apply()` calls are turned into `let bind = table_X_apply(...)`.
void LowerStmt(const IR::StatOrDecl* stmt, const LowerContext& ctx,
               std::vector<::dslx_ir::StmtPtr>* out,
               bool enable_table_apply);

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_P4_STMT_LOWER_H_
