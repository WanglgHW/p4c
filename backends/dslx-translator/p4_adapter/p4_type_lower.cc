// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "p4_type_lower.h"

#include <string>

#include "../dslx_ir/build.h"
#include "intrinsic_metadata.h"
#include "lib/error.h"

namespace P4::DSLX::adapter {

using ::dslx_ir::TypePtr;
using ::dslx_ir::ExprPtr;
namespace ir = ::dslx_ir;

std::string DslxNameForHeader(const IR::Type_Header* ht) {
    std::string n = std::string(ht->name.toString());
    return IsIntrinsicMetadataType(n) ? ToCamelCase(n) : CapitalizeFirst(n);
}

std::string DslxNameForStruct(const IR::Type_Struct* st) {
    std::string n = std::string(st->name.toString());
    return IsIntrinsicMetadataType(n) ? ToCamelCase(n) : CapitalizeFirst(n);
}

std::string DslxNameForType(const IR::Type* type) {
    if (auto h = type->to<IR::Type_Header>()) return DslxNameForHeader(h);
    if (auto s = type->to<IR::Type_Struct>()) return DslxNameForStruct(s);
    if (auto n = type->to<IR::Type_Name>()) {
        std::string nm = std::string(n->path->name.toString());
        return IsIntrinsicMetadataType(nm) ? ToCamelCase(nm) : CapitalizeFirst(nm);
    }
    return "/* unknown */";
}

TypePtr LowerType(const IR::Type* type, P4::TypeMap* typeMap) {
    if (type == nullptr) return ir::T_builtin("/* unknown */");
    if (type->is<IR::Type_Boolean>()) return ir::T_bool();
    if (auto tb = type->to<IR::Type_Bits>()) {
        if (tb->size > 64) {
            return ir::T_bits(ir::E_uN(32, std::to_string(tb->size)));
        }
        return tb->isSigned ? ir::T_s(tb->size) : ir::T_u(tb->size);
    }
    if (auto tn = type->to<IR::Type_Name>()) {
        std::string n = std::string(tn->path->name.toString());
        return ir::T_ref(IsIntrinsicMetadataType(n) ? ToCamelCase(n)
                                                    : CapitalizeFirst(n));
    }
    if (type->is<IR::Type_Void>()) return ir::T_unit();
    if (auto ts = type->to<IR::Type_Struct>()) {
        return ir::T_ref(DslxNameForStruct(ts));
    }
    if (auto th = type->to<IR::Type_Header>()) {
        return ir::T_ref(DslxNameForHeader(th));
    }
    if (type->is<IR::Type_Error>() || type->is<IR::Type_Enum>()) {
        return ir::T_u(32);
    }
    if (auto tse = type->to<IR::Type_SerEnum>()) {
        return LowerType(tse->type, typeMap);
    }
    if (auto ta = type->to<IR::Type_Array>()) {
        size_t size = ta->getSize();
        return ir::T_array(LowerType(ta->elementType, typeMap),
                            ir::E_uN(32, std::to_string(size)));
    }
    ::P4::error(ErrorType::ERR_UNSUPPORTED,
                "Unsupported type %1% for DSLX conversion", type);
    return ir::T_builtin("/* unsupported */");
}

int WidthOfType(const IR::Type* type, P4::TypeMap* typeMap) {
    if (type == nullptr) return 0;
    if (type->is<IR::Type_Boolean>()) return 1;
    if (auto tb = type->to<IR::Type_Bits>()) return tb->size;
    if (auto th = type->to<IR::Type_Header>()) {
        int total = 0;
        for (auto f : th->fields) {
            total += WidthOfType(typeMap->getType(f, false), typeMap);
        }
        return total;
    }
    if (auto ts = type->to<IR::Type_Struct>()) {
        int total = 0;
        for (auto f : ts->fields) {
            total += WidthOfType(typeMap->getType(f, false), typeMap);
        }
        return total;
    }
    return 0;
}

ExprPtr DefaultValueOf(const IR::Type* type, P4::TypeMap* typeMap) {
    if (type == nullptr) return ir::E_verbatim("/* unknown */");
    if (type->is<IR::Type_Boolean>()) return ir::E_bool(false);
    if (auto tb = type->to<IR::Type_Bits>()) {
        if (tb->size > 64) {
            return ir::E_verbatim("bits[" + std::to_string(tb->size) + "]:0");
        }
        std::string p = (tb->isSigned ? "s" : "u") + std::to_string(tb->size);
        return ir::E_num(p, "0");
    }
    if (type->is<IR::Type_Void>()) return ir::E_verbatim("()");
    if (type->is<IR::Type_Error>() || type->is<IR::Type_Enum>()) {
        return ir::E_uN(32, "0");
    }
    // Fall back to zero!<T>() — a valid DSLX initializer for any type.
    return ir::E_zero(LowerType(type, typeMap));
}

}  // namespace P4::DSLX::adapter
