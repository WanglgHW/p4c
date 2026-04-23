// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Helpers for the threaded "(headers, meta, intrinsic_md...)" tuple that
// flows through every TNA function. Centralised so parser/control/action
// lowerings stay single-purpose.

#ifndef DSLX_P4_ADAPTER_BINDING_HELPERS_H_
#define DSLX_P4_ADAPTER_BINDING_HELPERS_H_

#include <string>
#include <vector>

#include "../dslx_ir/ast.h"
#include "lower_context.h"

namespace P4::DSLX::adapter {

/// Pattern string for a let binding that captures the threaded tuple,
/// e.g. "headers" (1 param) or "(headers, meta, ig_intr_md)" (N params).
std::string BindingPattern(const PipelineBlockInfo& info);

/// Expression that is the threaded tuple of NameRefs, suitable as a
/// function tail-expression or call-arg value.
::dslx_ir::ExprPtr BindingExpr(const PipelineBlockInfo& info);

/// Type annotation for the function's return type — single type if N==1,
/// else a TupleType.
::dslx_ir::TypePtr BindingReturnType(const PipelineBlockInfo& info);

/// Param vector matching the threaded tuple.
std::vector<::dslx_ir::Param> BindingParams(const PipelineBlockInfo& info);

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_BINDING_HELPERS_H_
