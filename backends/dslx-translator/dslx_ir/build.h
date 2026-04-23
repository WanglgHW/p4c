// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Builder helpers for constructing dslx_ir nodes ergonomically.
// Adapters should prefer these over `std::make_unique<XlsTuple>(...)` for
// readability. None of them depend on anything outside dslx_ir/.

#ifndef DSLX_IR_BUILD_H_
#define DSLX_IR_BUILD_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "ast.h"

namespace dslx_ir {

inline TypePtr T_builtin(std::string n) {
    return std::make_unique<BuiltinType>(std::move(n));
}
inline TypePtr T_bool() { return T_builtin("bool"); }
inline TypePtr T_unit() { return T_builtin("()"); }
inline TypePtr T_u(int width) { return T_builtin("u" + std::to_string(width)); }
inline TypePtr T_s(int width) { return T_builtin("s" + std::to_string(width)); }
inline TypePtr T_ref(std::string name) {
    return std::make_unique<TypeRef>(std::move(name));
}
inline TypePtr T_bits(ExprPtr w) { return std::make_unique<BitsType>(std::move(w)); }
inline TypePtr T_array(TypePtr elem, ExprPtr size) {
    return std::make_unique<ArrayType>(std::move(elem), std::move(size));
}
inline TypePtr T_tuple(std::vector<TypePtr> ts) {
    return std::make_unique<TupleType>(std::move(ts));
}

inline ExprPtr E_name(std::string n) {
    return std::make_unique<NameRef>(std::move(n));
}
inline ExprPtr E_bool(bool v) { return std::make_unique<BoolLiteral>(v); }
inline ExprPtr E_num(std::string prefix, std::string val) {
    return std::make_unique<Number>(std::move(prefix), std::move(val));
}
inline ExprPtr E_uN(int width, std::string val) {
    return E_num("u" + std::to_string(width), std::move(val));
}
inline ExprPtr E_attr(ExprPtr lhs, std::string m) {
    return std::make_unique<Attr>(std::move(lhs), std::move(m));
}
inline ExprPtr E_index(ExprPtr lhs, ExprPtr i) {
    return std::make_unique<Index>(std::move(lhs), std::move(i));
}
inline ExprPtr E_call(ExprPtr callee, std::vector<ExprPtr> args) {
    return std::make_unique<Invocation>(std::move(callee), std::move(args));
}
inline ExprPtr E_call_named(std::string name, std::vector<ExprPtr> args) {
    return E_call(E_name(std::move(name)), std::move(args));
}
inline ExprPtr E_binop(BinopKind k, ExprPtr a, ExprPtr b) {
    return std::make_unique<Binop>(k, std::move(a), std::move(b));
}
inline ExprPtr E_unop(UnopKind k, ExprPtr a) {
    return std::make_unique<Unop>(k, std::move(a));
}
inline ExprPtr E_cast(ExprPtr v, TypePtr t) {
    return std::make_unique<Cast>(std::move(v), std::move(t));
}
inline ExprPtr E_cond(ExprPtr c, ExprPtr a, ExprPtr b) {
    return std::make_unique<Conditional>(std::move(c), std::move(a), std::move(b));
}
inline ExprPtr E_tuple(std::vector<ExprPtr> xs) {
    return std::make_unique<XlsTuple>(std::move(xs));
}
inline ExprPtr E_array(std::vector<ExprPtr> xs) {
    return std::make_unique<Array>(std::move(xs));
}
inline ExprPtr E_zero(TypePtr t) {
    return std::make_unique<ZeroMacro>(std::move(t));
}
inline ExprPtr E_struct(std::string tname, std::vector<StructInstance::Field> fs) {
    return std::make_unique<StructInstance>(std::move(tname), std::move(fs));
}
inline ExprPtr E_struct_splat(std::string tname,
                              std::vector<SplatStructInstance::Field> fs,
                              ExprPtr base) {
    return std::make_unique<SplatStructInstance>(std::move(tname), std::move(fs),
                                                  std::move(base));
}
inline ExprPtr E_verbatim(std::string text) {
    return std::make_unique<Verbatim>(std::move(text));
}
inline ExprPtr E_slice(ExprPtr lhs, ExprPtr start, TypePtr width_t) {
    return std::make_unique<WidthSlice>(std::move(lhs), std::move(start),
                                         std::move(width_t));
}

inline StmtPtr S_let(std::string pat, TypePtr t, ExprPtr v) {
    return std::make_unique<Let>(std::move(pat), std::move(t), std::move(v));
}
inline StmtPtr S_let_inferred(std::string pat, ExprPtr v) {
    return std::make_unique<Let>(std::move(pat), nullptr, std::move(v));
}
inline StmtPtr S_comment(std::string t) {
    return std::make_unique<CommentStmt>(std::move(t));
}
inline StmtPtr S_expr(ExprPtr e) {
    return std::make_unique<ExprStmt>(std::move(e));
}

inline std::unique_ptr<Block> B_make(std::vector<StmtPtr> stmts, ExprPtr tail) {
    return std::make_unique<Block>(std::move(stmts), std::move(tail));
}

}  // namespace dslx_ir

#endif  // DSLX_IR_BUILD_H_
