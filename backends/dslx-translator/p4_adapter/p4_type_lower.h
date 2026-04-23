// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Lowers P4 IR types to dslx_ir TypeAnnotation nodes.

#ifndef DSLX_P4_ADAPTER_P4_TYPE_LOWER_H_
#define DSLX_P4_ADAPTER_P4_TYPE_LOWER_H_

#include <string>

#include "../dslx_ir/ast.h"
#include "frontends/p4/typeMap.h"
#include "ir/ir.h"

namespace P4::DSLX::adapter {

/// Lower a P4 IR type to a dslx_ir TypeAnnotation.
/// Caller owns the returned node.
::dslx_ir::TypePtr LowerType(const IR::Type* type, P4::TypeMap* typeMap);

/// DSLX struct/header name a P4 named type lowers to (CamelCase for
/// intrinsic metadata, capitalized first letter for others).
std::string DslxNameForType(const IR::Type* type);
std::string DslxNameForHeader(const IR::Type_Header* ht);
std::string DslxNameForStruct(const IR::Type_Struct* st);

/// Bit-width of a P4 type in bits, or 0 if not statically known.
int WidthOfType(const IR::Type* type, P4::TypeMap* typeMap);

/// Default-value initializer expression for a P4 type, as a dslx_ir Expr.
::dslx_ir::ExprPtr DefaultValueOf(const IR::Type* type, P4::TypeMap* typeMap);

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_P4_TYPE_LOWER_H_
