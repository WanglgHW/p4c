// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Reusable DSLX-IR AST.  Derived in shape and naming from
// xls/dslx/frontend/ast.h (XLS_DSLX_EXPR_NODE_EACH / XLS_DSLX_AST_NODE_EACH),
// but rewritten from scratch as a tiny, header-only-friendly emit-side AST:
//
//   * No Abseil, no protobuf, no XLS IR — only <string>/<vector>/<memory>.
//   * No type checking, name resolution, or scope tracking — every NameRef
//     carries the literal identifier the frontend wants emitted.
//   * No source-position requirement; nodes are constructed by an adapter that
//     generally does not have meaningful Pos data.
//
// All node ownership is via std::unique_ptr.  Top-level decls are owned by
// the Module.  Walk happens through `Format(Formatter&)`, which is implemented
// by each concrete leaf in ast.cc.
//
// To target this IR from a NEW source DSL, write your own `<lang>_to_dslx`
// adapter that constructs these nodes — there is nothing P4-specific here.

#ifndef DSLX_IR_AST_H_
#define DSLX_IR_AST_H_

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "pos.h"

namespace dslx_ir {

class Formatter;
class Expr;
class Stmt;
class TypeAnnotation;

using ExprPtr = std::unique_ptr<Expr>;
using StmtPtr = std::unique_ptr<Stmt>;
using TypePtr = std::unique_ptr<TypeAnnotation>;

// =============================================================================
// Type annotations
// =============================================================================
// DSLX has its own type-syntax sublanguage. We model a small slice:
//   builtin:  bool, u8..u64, s8..s64, ()
//   bits[N]   parameterized by either a literal width or a const-name
//   Tname     reference to a named struct/enum/type alias
//   T[N]      array (N is an Expr — supports `MAX_TABLE_ENTRIES` references)
//   (T1,T2)   tuple

class TypeAnnotation {
 public:
    virtual ~TypeAnnotation() = default;
    virtual void Format(Formatter& f) const = 0;
    Span span;
};

class BuiltinType : public TypeAnnotation {
 public:
    explicit BuiltinType(std::string name) : name(std::move(name)) {}
    void Format(Formatter& f) const override;
    std::string name;  // "bool", "u8", "s32", "()", ...
};

// `bits[ <expr> ]` — expr is usually a Number or NameRef to a const.
class BitsType : public TypeAnnotation {
 public:
    explicit BitsType(ExprPtr width) : width(std::move(width)) {}
    void Format(Formatter& f) const override;
    ExprPtr width;
};

class TypeRef : public TypeAnnotation {
 public:
    explicit TypeRef(std::string name) : name(std::move(name)) {}
    void Format(Formatter& f) const override;
    std::string name;
};

class ArrayType : public TypeAnnotation {
 public:
    ArrayType(TypePtr elem, ExprPtr size)
        : elem(std::move(elem)), size(std::move(size)) {}
    void Format(Formatter& f) const override;
    TypePtr elem;
    ExprPtr size;
};

class TupleType : public TypeAnnotation {
 public:
    explicit TupleType(std::vector<TypePtr> members) : members(std::move(members)) {}
    void Format(Formatter& f) const override;
    std::vector<TypePtr> members;
};

// =============================================================================
// Expressions
// =============================================================================
class Expr {
 public:
    virtual ~Expr() = default;
    virtual void Format(Formatter& f) const = 0;
    Span span;
};

// `u32:5` / `s8:-1` / `bits[12]:0xff`
class Number : public Expr {
 public:
    Number(std::string type_prefix, std::string value)
        : type_prefix(std::move(type_prefix)), value(std::move(value)) {}
    void Format(Formatter& f) const override;
    std::string type_prefix;  // "" for bare numbers; "u32", "s8", "bits[N]"
    std::string value;        // already-rendered literal: "5", "0xff", "-1"
};

class BoolLiteral : public Expr {
 public:
    explicit BoolLiteral(bool v) : value(v) {}
    void Format(Formatter& f) const override;
    bool value;
};

// Bare identifier reference. We don't resolve to a NameDef — the adapter's
// responsibility is to pick correct DSLX identifiers up front.
class NameRef : public Expr {
 public:
    explicit NameRef(std::string name) : name(std::move(name)) {}
    void Format(Formatter& f) const override;
    std::string name;
};

class Attr : public Expr {
 public:
    Attr(ExprPtr lhs, std::string member)
        : lhs(std::move(lhs)), member(std::move(member)) {}
    void Format(Formatter& f) const override;
    ExprPtr lhs;
    std::string member;
};

class Index : public Expr {
 public:
    Index(ExprPtr lhs, ExprPtr index) : lhs(std::move(lhs)), index(std::move(index)) {}
    void Format(Formatter& f) const override;
    ExprPtr lhs;
    ExprPtr index;
};

// `lhs[start +: <type>]` — DSLX width-indexed bit slice.
class WidthSlice : public Expr {
 public:
    WidthSlice(ExprPtr lhs, ExprPtr start, TypePtr width_type)
        : lhs(std::move(lhs)), start(std::move(start)), width_type(std::move(width_type)) {}
    void Format(Formatter& f) const override;
    ExprPtr lhs;
    ExprPtr start;
    TypePtr width_type;
};

enum class BinopKind {
    kAdd, kSub, kMul, kBAnd, kBOr, kBXor,
    kShl, kShr, kEq, kNe, kLt, kLe, kGt, kGe,
    kLAnd, kLOr, kConcat,
};

class Binop : public Expr {
 public:
    Binop(BinopKind kind, ExprPtr lhs, ExprPtr rhs)
        : kind(kind), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
    void Format(Formatter& f) const override;
    BinopKind kind;
    ExprPtr lhs;
    ExprPtr rhs;
};

enum class UnopKind { kNeg, kInvert, kNot };

class Unop : public Expr {
 public:
    Unop(UnopKind kind, ExprPtr operand) : kind(kind), operand(std::move(operand)) {}
    void Format(Formatter& f) const override;
    UnopKind kind;
    ExprPtr operand;
};

class Cast : public Expr {
 public:
    Cast(ExprPtr operand, TypePtr to_type)
        : operand(std::move(operand)), to_type(std::move(to_type)) {}
    void Format(Formatter& f) const override;
    ExprPtr operand;
    TypePtr to_type;
};

// Expression-form `if c { a } else { b }` (DSLX has no ternary).
class Conditional : public Expr {
 public:
    Conditional(ExprPtr cond, ExprPtr if_true, ExprPtr if_false)
        : cond(std::move(cond)),
          if_true(std::move(if_true)),
          if_false(std::move(if_false)) {}
    void Format(Formatter& f) const override;
    ExprPtr cond;
    ExprPtr if_true;
    ExprPtr if_false;
};

// `Type { f1: v1, f2: v2 }`
class StructInstance : public Expr {
 public:
    using Field = std::pair<std::string, ExprPtr>;
    StructInstance(std::string type_name, std::vector<Field> fields)
        : type_name(std::move(type_name)), fields(std::move(fields)) {}
    void Format(Formatter& f) const override;
    std::string type_name;
    std::vector<Field> fields;
};

// `Type { f1: v1, ..base }`
class SplatStructInstance : public Expr {
 public:
    using Field = std::pair<std::string, ExprPtr>;
    SplatStructInstance(std::string type_name, std::vector<Field> fields, ExprPtr splat)
        : type_name(std::move(type_name)),
          fields(std::move(fields)),
          splat(std::move(splat)) {}
    void Format(Formatter& f) const override;
    std::string type_name;
    std::vector<Field> fields;
    ExprPtr splat;
};

class Invocation : public Expr {
 public:
    Invocation(ExprPtr callee, std::vector<ExprPtr> args)
        : callee(std::move(callee)), args(std::move(args)) {}
    void Format(Formatter& f) const override;
    ExprPtr callee;
    std::vector<ExprPtr> args;
};

class XlsTuple : public Expr {
 public:
    explicit XlsTuple(std::vector<ExprPtr> members) : members(std::move(members)) {}
    void Format(Formatter& f) const override;
    std::vector<ExprPtr> members;
};

class Array : public Expr {
 public:
    explicit Array(std::vector<ExprPtr> members) : members(std::move(members)) {}
    void Format(Formatter& f) const override;
    std::vector<ExprPtr> members;
};

// `zero!<T>()` — convenient zero initializer for any DSLX type.
class ZeroMacro : public Expr {
 public:
    explicit ZeroMacro(TypePtr type) : type(std::move(type)) {}
    void Format(Formatter& f) const override;
    TypePtr type;
};

class For : public Expr {
 public:
    // `for (index_name, acc_pat): (index_type, acc_type) in start..end { body }(init)`
    For(std::string index_name, std::string acc_pat, TypePtr index_type, TypePtr acc_type,
        ExprPtr start, ExprPtr end, std::unique_ptr<class Block> body, ExprPtr init)
        : index_name(std::move(index_name)),
          acc_pat(std::move(acc_pat)),
          index_type(std::move(index_type)),
          acc_type(std::move(acc_type)),
          start(std::move(start)),
          end(std::move(end)),
          body(std::move(body)),
          init(std::move(init)) {}
    void Format(Formatter& f) const override;
    std::string index_name;
    std::string acc_pat;
    TypePtr index_type;
    TypePtr acc_type;
    ExprPtr start;
    ExprPtr end;
    std::unique_ptr<Block> body;
    ExprPtr init;
};

// Escape hatch — emits the literal text verbatim. Useful for awkward
// constructs we don't want to model nodes for (e.g. a bit_slice_update call
// to a stdlib helper). XLS has the same idea (`VerbatimNode`).
class Verbatim : public Expr {
 public:
    explicit Verbatim(std::string text) : text(std::move(text)) {}
    void Format(Formatter& f) const override;
    std::string text;
};

// =============================================================================
// Statements & Blocks
// =============================================================================
// DSLX is expression-oriented: a function body is a Block whose final element
// is the tail expression. We model statements that come BEFORE that tail.

class Stmt {
 public:
    virtual ~Stmt() = default;
    virtual void Format(Formatter& f) const = 0;
};

// `let pat: T = value;` (T optional)
class Let : public Stmt {
 public:
    Let(std::string pat, TypePtr type, ExprPtr value)
        : pat(std::move(pat)), type(std::move(type)), value(std::move(value)) {}
    void Format(Formatter& f) const override;
    std::string pat;        // single name OR pre-formatted tuple pattern: "(a, b, c)"
    TypePtr type;           // nullable
    ExprPtr value;
};

// Comment line — `// text`
class CommentStmt : public Stmt {
 public:
    explicit CommentStmt(std::string text) : text(std::move(text)) {}
    void Format(Formatter& f) const override;
    std::string text;
};

// Bare expression line (rare in DSLX — used for trailing values inside If branches).
class ExprStmt : public Stmt {
 public:
    explicit ExprStmt(ExprPtr value) : value(std::move(value)) {}
    void Format(Formatter& f) const override;
    ExprPtr value;
};

// `{ stmt; stmt; tail }` — tail may be null (-> empty unit return).
class Block : public Expr {
 public:
    Block() = default;
    Block(std::vector<StmtPtr> stmts, ExprPtr tail)
        : stmts(std::move(stmts)), tail(std::move(tail)) {}
    void Format(Formatter& f) const override;
    std::vector<StmtPtr> stmts;
    ExprPtr tail;
};

// =============================================================================
// Top-level declarations
// =============================================================================
class Decl {
 public:
    virtual ~Decl() = default;
    virtual void Format(Formatter& f) const = 0;
};

class ConstDecl : public Decl {
 public:
    ConstDecl(std::string name, TypePtr type, ExprPtr value)
        : name(std::move(name)), type(std::move(type)), value(std::move(value)) {}
    void Format(Formatter& f) const override;
    std::string name;
    TypePtr type;
    ExprPtr value;
};

class TypeAlias : public Decl {
 public:
    TypeAlias(std::string name, TypePtr type)
        : name(std::move(name)), type(std::move(type)) {}
    void Format(Formatter& f) const override;
    std::string name;
    TypePtr type;
};

class StructDef : public Decl {
 public:
    using Field = std::pair<std::string, TypePtr>;
    StructDef(std::string name, std::vector<Field> fields, bool is_pub = true)
        : name(std::move(name)), fields(std::move(fields)), is_pub(is_pub) {}
    void Format(Formatter& f) const override;
    std::string name;
    std::vector<Field> fields;
    bool is_pub;
};

class Param {
 public:
    Param(std::string name, TypePtr type) : name(std::move(name)), type(std::move(type)) {}
    void Format(Formatter& f) const;
    std::string name;
    TypePtr type;
};

class Function : public Decl {
 public:
    Function(std::string name, std::vector<Param> params, TypePtr ret_type,
             std::unique_ptr<Block> body, bool is_pub = true)
        : name(std::move(name)),
          params(std::move(params)),
          ret_type(std::move(ret_type)),
          body(std::move(body)),
          is_pub(is_pub) {}
    void Format(Formatter& f) const override;
    std::string name;
    std::vector<Param> params;
    TypePtr ret_type;
    std::unique_ptr<Block> body;
    bool is_pub;
};

// Free-floating top-level comment (file header, section banner).
class CommentDecl : public Decl {
 public:
    explicit CommentDecl(std::string text) : text(std::move(text)) {}
    void Format(Formatter& f) const override;
    std::string text;
};

class BlankLineDecl : public Decl {
 public:
    void Format(Formatter& f) const override;
};

}  // namespace dslx_ir

#endif  // DSLX_IR_AST_H_
