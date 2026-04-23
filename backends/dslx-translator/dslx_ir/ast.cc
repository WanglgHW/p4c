// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Format() implementations for every node in dslx_ir/ast.h.
// One file because the implementations are short and inter-dependent;
// keeping them together makes the syntactic conventions easy to audit.

#include "ast.h"

#include "formatter.h"
#include "module.h"

namespace dslx_ir {

namespace {

const char* BinopText(BinopKind k) {
    switch (k) {
        case BinopKind::kAdd: return "+";
        case BinopKind::kSub: return "-";
        case BinopKind::kMul: return "*";
        case BinopKind::kBAnd: return "&";
        case BinopKind::kBOr: return "|";
        case BinopKind::kBXor: return "^";
        case BinopKind::kShl: return "<<";
        case BinopKind::kShr: return ">>";
        case BinopKind::kEq: return "==";
        case BinopKind::kNe: return "!=";
        case BinopKind::kLt: return "<";
        case BinopKind::kLe: return "<=";
        case BinopKind::kGt: return ">";
        case BinopKind::kGe: return ">=";
        case BinopKind::kLAnd: return "&&";
        case BinopKind::kLOr: return "||";
        case BinopKind::kConcat: return "++";
    }
    return "?";
}

const char* UnopText(UnopKind k) {
    switch (k) {
        case UnopKind::kNeg: return "-";
        case UnopKind::kInvert: return "!";
        case UnopKind::kNot: return "!";
    }
    return "?";
}

}  // namespace

// ---------- Type annotations -------------------------------------------------

void BuiltinType::Format(Formatter& f) const { f.Write(name); }

void BitsType::Format(Formatter& f) const {
    f.Write("bits[");
    width->Format(f);
    f.Write("]");
}

void TypeRef::Format(Formatter& f) const { f.Write(name); }

void ArrayType::Format(Formatter& f) const {
    elem->Format(f);
    f.Write("[");
    size->Format(f);
    f.Write("]");
}

void TupleType::Format(Formatter& f) const {
    f.Write("(");
    for (std::size_t i = 0; i < members.size(); ++i) {
        if (i != 0) f.Write(", ");
        members[i]->Format(f);
    }
    f.Write(")");
}

// ---------- Expressions ------------------------------------------------------

void Number::Format(Formatter& f) const {
    if (!type_prefix.empty()) {
        f.Write(type_prefix);
        f.Write(":");
    }
    f.Write(value);
}

void BoolLiteral::Format(Formatter& f) const { f.Write(value ? "true" : "false"); }

void NameRef::Format(Formatter& f) const { f.Write(name); }

void Attr::Format(Formatter& f) const {
    lhs->Format(f);
    f.Write(".");
    f.Write(member);
}

void Index::Format(Formatter& f) const {
    lhs->Format(f);
    f.Write("[");
    index->Format(f);
    f.Write("]");
}

void WidthSlice::Format(Formatter& f) const {
    lhs->Format(f);
    f.Write("[");
    start->Format(f);
    f.Write(" +: ");
    width_type->Format(f);
    f.Write("]");
}

void Binop::Format(Formatter& f) const {
    f.Write("(");
    lhs->Format(f);
    f.Write(" ");
    f.Write(BinopText(kind));
    f.Write(" ");
    rhs->Format(f);
    f.Write(")");
}

void Unop::Format(Formatter& f) const {
    f.Write("(");
    f.Write(UnopText(kind));
    operand->Format(f);
    f.Write(")");
}

void Cast::Format(Formatter& f) const {
    f.Write("(");
    operand->Format(f);
    f.Write(" as ");
    to_type->Format(f);
    f.Write(")");
}

void Conditional::Format(Formatter& f) const {
    f.Write("if ");
    cond->Format(f);
    f.Write(" { ");
    if_true->Format(f);
    f.Write(" } else { ");
    if_false->Format(f);
    f.Write(" }");
}

void StructInstance::Format(Formatter& f) const {
    f.Write(type_name);
    f.Write(" { ");
    for (std::size_t i = 0; i < fields.size(); ++i) {
        if (i != 0) f.Write(", ");
        f.Write(fields[i].first);
        f.Write(": ");
        fields[i].second->Format(f);
    }
    f.Write(" }");
}

void SplatStructInstance::Format(Formatter& f) const {
    f.Write(type_name);
    f.Write(" { ");
    for (std::size_t i = 0; i < fields.size(); ++i) {
        if (i != 0) f.Write(", ");
        f.Write(fields[i].first);
        f.Write(": ");
        fields[i].second->Format(f);
    }
    if (!fields.empty()) f.Write(", ");
    f.Write("..");
    splat->Format(f);
    f.Write(" }");
}

void Invocation::Format(Formatter& f) const {
    callee->Format(f);
    f.Write("(");
    for (std::size_t i = 0; i < args.size(); ++i) {
        if (i != 0) f.Write(", ");
        args[i]->Format(f);
    }
    f.Write(")");
}

void XlsTuple::Format(Formatter& f) const {
    f.Write("(");
    for (std::size_t i = 0; i < members.size(); ++i) {
        if (i != 0) f.Write(", ");
        members[i]->Format(f);
    }
    if (members.size() == 1) f.Write(",");  // 1-tuple syntax
    f.Write(")");
}

void Array::Format(Formatter& f) const {
    f.Write("[");
    for (std::size_t i = 0; i < members.size(); ++i) {
        if (i != 0) f.Write(", ");
        members[i]->Format(f);
    }
    f.Write("]");
}

void ZeroMacro::Format(Formatter& f) const {
    f.Write("zero!<");
    type->Format(f);
    f.Write(">()");
}

void For::Format(Formatter& f) const {
    f.Write("for (");
    f.Write(index_name);
    f.Write(", ");
    f.Write(acc_pat);
    f.Write("): (");
    index_type->Format(f);
    f.Write(", ");
    acc_type->Format(f);
    f.Write(") in ");
    start->Format(f);
    f.Write("..");
    end->Format(f);
    f.Write(" ");
    body->Format(f);
    f.Write("(");
    init->Format(f);
    f.Write(")");
}

void Verbatim::Format(Formatter& f) const { f.Write(text); }

// ---------- Statements & Block ----------------------------------------------

void Let::Format(Formatter& f) const {
    f.EmitIndentIfNeeded();
    f.Write("let ");
    f.Write(pat);
    if (type) {
        f.Write(": ");
        type->Format(f);
    }
    f.Write(" = ");
    value->Format(f);
    f.Write(";");
    f.Newline();
}

void CommentStmt::Format(Formatter& f) const {
    f.EmitIndentIfNeeded();
    f.Write("// ");
    f.Write(text);
    f.Newline();
}

void ExprStmt::Format(Formatter& f) const {
    f.EmitIndentIfNeeded();
    value->Format(f);
    f.Newline();
}

void Block::Format(Formatter& f) const {
    f.Write("{");
    f.Newline();
    f.Indent();
    for (const auto& s : stmts) {
        s->Format(f);
    }
    if (tail) {
        f.EmitIndentIfNeeded();
        tail->Format(f);
        f.Newline();
    }
    f.Dedent();
    f.EmitIndentIfNeeded();
    f.Write("}");
}

// ---------- Top-level decls --------------------------------------------------

void ConstDecl::Format(Formatter& f) const {
    f.EmitIndentIfNeeded();
    f.Write("const ");
    f.Write(name);
    f.Write(": ");
    type->Format(f);
    f.Write(" = ");
    value->Format(f);
    f.Write(";");
    f.Newline();
}

void TypeAlias::Format(Formatter& f) const {
    f.EmitIndentIfNeeded();
    f.Write("type ");
    f.Write(name);
    f.Write(" = ");
    type->Format(f);
    f.Write(";");
    f.Newline();
}

void StructDef::Format(Formatter& f) const {
    f.EmitIndentIfNeeded();
    if (is_pub) f.Write("pub ");
    f.Write("struct ");
    f.Write(name);
    f.Write(" {");
    f.Newline();
    f.Indent();
    for (const auto& [fname, ftype] : fields) {
        f.EmitIndentIfNeeded();
        f.Write(fname);
        f.Write(": ");
        ftype->Format(f);
        f.Write(",");
        f.Newline();
    }
    f.Dedent();
    f.EmitIndentIfNeeded();
    f.Write("}");
    f.Newline();
}

void Param::Format(Formatter& f) const {
    f.Write(name);
    f.Write(": ");
    type->Format(f);
}

void Function::Format(Formatter& f) const {
    f.EmitIndentIfNeeded();
    if (is_pub) f.Write("pub ");
    f.Write("fn ");
    f.Write(name);
    f.Write("(");
    for (std::size_t i = 0; i < params.size(); ++i) {
        if (i != 0) f.Write(", ");
        params[i].Format(f);
    }
    f.Write(") -> ");
    ret_type->Format(f);
    f.Write(" ");
    body->Format(f);
    f.Newline();
}

void CommentDecl::Format(Formatter& f) const {
    f.EmitIndentIfNeeded();
    f.Write("// ");
    f.Write(text);
    f.Newline();
}

void BlankLineDecl::Format(Formatter& f) const { f.Newline(); }

}  // namespace dslx_ir
