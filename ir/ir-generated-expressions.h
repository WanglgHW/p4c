#ifndef IR_GENERATED_EXPRESSIONS_H_
#define IR_GENERATED_EXPRESSIONS_H_

// IR expression nodes: Operation_Unary / Operation_Binary / Operation_Ternary /
// Operation_Relation abstracts plus every concrete arithmetic, logical,
// comparison, bitwise, slice, member, list, struct, literal, and call expression.

#include "ir/ir-generated-types.h"

namespace P4::IR {
/* This file contains the IR classes for all expressions.
   The base classes are in base.def */
class Operation_Unary : public Operation {
 public:
    const IR::Expression *expr = nullptr;
    int getPrecedence() const override { return DBPrint::Prec_Prefix; }
    cstring toString() const override;
    bool operator==(IR::Operation_Unary const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Operation_Unary"_cs; }
    static cstring static_type_name() { return "Operation_Unary"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Operation_Unary(JSONLoader &json);
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Operation_Unary(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *expr)
        : Operation(srcInfo, type), expr(expr) {
        {
            if (!srcInfo && expr) srcInfo = expr->srcInfo;
            if (type->is<Type::Unknown>() && expr) type = expr->type;
        }
        validate();
    }
    Operation_Unary(const IR::Type *type, const IR::Expression *expr)
        : Operation(type), expr(expr) {
        {
            if (!srcInfo && expr) srcInfo = expr->srcInfo;
            if (type->is<Type::Unknown>() && expr) type = expr->type;
        }
        validate();
    }
    Operation_Unary(Util::SourceInfo srcInfo, const IR::Expression *expr)
        : Operation(srcInfo), expr(expr) {
        {
            if (!srcInfo && expr) srcInfo = expr->srcInfo;
            if (type->is<Type::Unknown>() && expr) type = expr->type;
        }
        validate();
    }
    Operation_Unary(const IR::Expression *expr) : expr(expr) {
        {
            if (!srcInfo && expr) srcInfo = expr->srcInfo;
            if (type->is<Type::Unknown>() && expr) type = expr->type;
        }
        validate();
    }
    IRNODE_ABSTRACT_SUBCLASS(Operation_Unary)
    DECLARE_TYPEINFO_WITH_TYPEID(Operation_Unary, NodeKind::Operation_Unary, Operation);
};
}  // namespace P4::IR
namespace P4::IR {
class Neg : public Operation_Unary {
 public:
    cstring getStringOp() const override { return cstring("-"); }
    bool operator==(IR::Neg const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Neg"_cs; }
    static cstring static_type_name() { return "Neg"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Neg(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Unary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Neg(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *expr)
        : Operation_Unary(srcInfo, type, expr) {
        validate();
    }
    Neg(const IR::Type *type, const IR::Expression *expr) : Operation_Unary(type, expr) {
        validate();
    }
    Neg(Util::SourceInfo srcInfo, const IR::Expression *expr) : Operation_Unary(srcInfo, expr) {
        validate();
    }
    Neg(const IR::Expression *expr) : Operation_Unary(expr) { validate(); }
    IRNODE_SUBCLASS(Neg)
    DECLARE_TYPEINFO_WITH_TYPEID(Neg, NodeKind::Neg, Operation_Unary);
};
}  // namespace P4::IR
namespace P4::IR {
class UPlus : public Operation_Unary {
 public:
    cstring getStringOp() const override { return cstring("+"); }
    bool operator==(IR::UPlus const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "UPlus"_cs; }
    static cstring static_type_name() { return "UPlus"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    UPlus(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Unary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    UPlus(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *expr)
        : Operation_Unary(srcInfo, type, expr) {
        validate();
    }
    UPlus(const IR::Type *type, const IR::Expression *expr) : Operation_Unary(type, expr) {
        validate();
    }
    UPlus(Util::SourceInfo srcInfo, const IR::Expression *expr) : Operation_Unary(srcInfo, expr) {
        validate();
    }
    UPlus(const IR::Expression *expr) : Operation_Unary(expr) { validate(); }
    IRNODE_SUBCLASS(UPlus)
    DECLARE_TYPEINFO_WITH_TYPEID(UPlus, NodeKind::UPlus, Operation_Unary);
};
}  // namespace P4::IR
namespace P4::IR {
class Cmpl : public Operation_Unary {
 public:
    cstring getStringOp() const override { return cstring("~"); }
    bool operator==(IR::Cmpl const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Cmpl"_cs; }
    static cstring static_type_name() { return "Cmpl"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Cmpl(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Unary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Cmpl(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *expr)
        : Operation_Unary(srcInfo, type, expr) {
        validate();
    }
    Cmpl(const IR::Type *type, const IR::Expression *expr) : Operation_Unary(type, expr) {
        validate();
    }
    Cmpl(Util::SourceInfo srcInfo, const IR::Expression *expr) : Operation_Unary(srcInfo, expr) {
        validate();
    }
    Cmpl(const IR::Expression *expr) : Operation_Unary(expr) { validate(); }
    IRNODE_SUBCLASS(Cmpl)
    DECLARE_TYPEINFO_WITH_TYPEID(Cmpl, NodeKind::Cmpl, Operation_Unary);
};
}  // namespace P4::IR
namespace P4::IR {
class LNot : public Operation_Unary {
 public:
    cstring getStringOp() const override { return cstring("!"); }
    bool operator==(IR::LNot const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "LNot"_cs; }
    static cstring static_type_name() { return "LNot"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    LNot(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Unary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    LNot(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *expr)
        : Operation_Unary(srcInfo, type, expr) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    LNot(const IR::Type *type, const IR::Expression *expr) : Operation_Unary(type, expr) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    LNot(Util::SourceInfo srcInfo, const IR::Expression *expr) : Operation_Unary(srcInfo, expr) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    LNot(const IR::Expression *expr) : Operation_Unary(expr) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    IRNODE_SUBCLASS(LNot)
    DECLARE_TYPEINFO_WITH_TYPEID(LNot, NodeKind::LNot, Operation_Unary);
};
}  // namespace P4::IR
namespace P4::IR {
class Operation_Binary : public Operation {
 public:
    const IR::Expression *left = nullptr;
    const IR::Expression *right = nullptr;
    cstring toString() const override;
    bool operator==(IR::Operation_Binary const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Operation_Binary"_cs; }
    static cstring static_type_name() { return "Operation_Binary"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Operation_Binary(JSONLoader &json);
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Operation_Binary(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
                     const IR::Expression *right)
        : Operation(srcInfo, type), left(left), right(right) {
        {
            if (!srcInfo && left && right) srcInfo = left->srcInfo + right->srcInfo;
            if (type->is<Type::Unknown>() && left && right && left->type == right->type)
                type = left->type;
        }
        validate();
    }
    Operation_Binary(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation(type), left(left), right(right) {
        {
            if (!srcInfo && left && right) srcInfo = left->srcInfo + right->srcInfo;
            if (type->is<Type::Unknown>() && left && right && left->type == right->type)
                type = left->type;
        }
        validate();
    }
    Operation_Binary(Util::SourceInfo srcInfo, const IR::Expression *left,
                     const IR::Expression *right)
        : Operation(srcInfo), left(left), right(right) {
        {
            if (!srcInfo && left && right) srcInfo = left->srcInfo + right->srcInfo;
            if (type->is<Type::Unknown>() && left && right && left->type == right->type)
                type = left->type;
        }
        validate();
    }
    Operation_Binary(const IR::Expression *left, const IR::Expression *right)
        : left(left), right(right) {
        {
            if (!srcInfo && left && right) srcInfo = left->srcInfo + right->srcInfo;
            if (type->is<Type::Unknown>() && left && right && left->type == right->type)
                type = left->type;
        }
        validate();
    }
    IRNODE_ABSTRACT_SUBCLASS(Operation_Binary)
    DECLARE_TYPEINFO_WITH_TYPEID(Operation_Binary, NodeKind::Operation_Binary, Operation);
};
}  // namespace P4::IR
namespace P4::IR {
class Operation_Ternary : public Operation {
 public:
    const IR::Expression *e0 = nullptr;
    const IR::Expression *e1 = nullptr;
    const IR::Expression *e2 = nullptr;
    bool operator==(IR::Operation_Ternary const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Operation_Ternary"_cs; }
    static cstring static_type_name() { return "Operation_Ternary"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Operation_Ternary(JSONLoader &json);
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Operation_Ternary(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *e0,
                      const IR::Expression *e1, const IR::Expression *e2)
        : Operation(srcInfo, type), e0(e0), e1(e1), e2(e2) {
        {
            if (!srcInfo && e0 && e2) srcInfo = e0->srcInfo + e2->srcInfo;
        }
        validate();
    }
    Operation_Ternary(const IR::Type *type, const IR::Expression *e0, const IR::Expression *e1,
                      const IR::Expression *e2)
        : Operation(type), e0(e0), e1(e1), e2(e2) {
        {
            if (!srcInfo && e0 && e2) srcInfo = e0->srcInfo + e2->srcInfo;
        }
        validate();
    }
    Operation_Ternary(Util::SourceInfo srcInfo, const IR::Expression *e0, const IR::Expression *e1,
                      const IR::Expression *e2)
        : Operation(srcInfo), e0(e0), e1(e1), e2(e2) {
        {
            if (!srcInfo && e0 && e2) srcInfo = e0->srcInfo + e2->srcInfo;
        }
        validate();
    }
    Operation_Ternary(const IR::Expression *e0, const IR::Expression *e1, const IR::Expression *e2)
        : e0(e0), e1(e1), e2(e2) {
        {
            if (!srcInfo && e0 && e2) srcInfo = e0->srcInfo + e2->srcInfo;
        }
        validate();
    }
    IRNODE_ABSTRACT_SUBCLASS(Operation_Ternary)
    DECLARE_TYPEINFO_WITH_TYPEID(Operation_Ternary, NodeKind::Operation_Ternary, Operation);
};
}  // namespace P4::IR
namespace P4::IR {
class Operation_Relation : public Operation_Binary {
 public:
    bool operator==(IR::Operation_Relation const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Operation_Relation"_cs; }
    static cstring static_type_name() { return "Operation_Relation"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Operation_Relation(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Operation_Relation(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
                       const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    Operation_Relation(const IR::Type *type, const IR::Expression *left,
                       const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    Operation_Relation(Util::SourceInfo srcInfo, const IR::Expression *left,
                       const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    Operation_Relation(const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    IRNODE_ABSTRACT_SUBCLASS(Operation_Relation)
    DECLARE_TYPEINFO_WITH_TYPEID(Operation_Relation, NodeKind::Operation_Relation,
                                 Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class Mul : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("*"); }
    int getPrecedence() const override { return DBPrint::Prec_Mul; }
    bool operator==(IR::Mul const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Mul"_cs; }
    static cstring static_type_name() { return "Mul"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Mul(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Mul(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        validate();
    }
    Mul(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        validate();
    }
    Mul(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        validate();
    }
    Mul(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(Mul)
    DECLARE_TYPEINFO_WITH_TYPEID(Mul, NodeKind::Mul, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class Div : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("/"); }
    int getPrecedence() const override { return DBPrint::Prec_Div; }
    bool operator==(IR::Div const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Div"_cs; }
    static cstring static_type_name() { return "Div"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Div(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Div(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        validate();
    }
    Div(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        validate();
    }
    Div(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        validate();
    }
    Div(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(Div)
    DECLARE_TYPEINFO_WITH_TYPEID(Div, NodeKind::Div, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class Mod : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("%"); }
    int getPrecedence() const override { return DBPrint::Prec_Mod; }
    bool operator==(IR::Mod const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Mod"_cs; }
    static cstring static_type_name() { return "Mod"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Mod(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Mod(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        validate();
    }
    Mod(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        validate();
    }
    Mod(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        validate();
    }
    Mod(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(Mod)
    DECLARE_TYPEINFO_WITH_TYPEID(Mod, NodeKind::Mod, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class Add : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("+"); }
    int getPrecedence() const override { return DBPrint::Prec_Add; }
    bool operator==(IR::Add const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Add"_cs; }
    static cstring static_type_name() { return "Add"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Add(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Add(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        validate();
    }
    Add(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        validate();
    }
    Add(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        validate();
    }
    Add(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(Add)
    DECLARE_TYPEINFO_WITH_TYPEID(Add, NodeKind::Add, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class Sub : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("-"); }
    int getPrecedence() const override { return DBPrint::Prec_Sub; }
    bool operator==(IR::Sub const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Sub"_cs; }
    static cstring static_type_name() { return "Sub"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Sub(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Sub(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        validate();
    }
    Sub(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        validate();
    }
    Sub(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        validate();
    }
    Sub(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(Sub)
    DECLARE_TYPEINFO_WITH_TYPEID(Sub, NodeKind::Sub, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class AddSat : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("|+|"); }
    int getPrecedence() const override { return DBPrint::Prec_AddSat; }
    bool operator==(IR::AddSat const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "AddSat"_cs; }
    static cstring static_type_name() { return "AddSat"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    AddSat(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    AddSat(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
           const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        validate();
    }
    AddSat(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        validate();
    }
    AddSat(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        validate();
    }
    AddSat(const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(AddSat)
    DECLARE_TYPEINFO_WITH_TYPEID(AddSat, NodeKind::AddSat, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class SubSat : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("|-|"); }
    int getPrecedence() const override { return DBPrint::Prec_SubSat; }
    bool operator==(IR::SubSat const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "SubSat"_cs; }
    static cstring static_type_name() { return "SubSat"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    SubSat(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    SubSat(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
           const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        validate();
    }
    SubSat(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        validate();
    }
    SubSat(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        validate();
    }
    SubSat(const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(SubSat)
    DECLARE_TYPEINFO_WITH_TYPEID(SubSat, NodeKind::SubSat, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class Shl : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("<<"); }
    int getPrecedence() const override { return DBPrint::Prec_Shl; }
    bool operator==(IR::Shl const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Shl"_cs; }
    static cstring static_type_name() { return "Shl"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Shl(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Shl(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        {
            if (type->is<Type::Unknown>() && left) type = left->type;
        }
        validate();
    }
    Shl(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        {
            if (type->is<Type::Unknown>() && left) type = left->type;
        }
        validate();
    }
    Shl(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        {
            if (type->is<Type::Unknown>() && left) type = left->type;
        }
        validate();
    }
    Shl(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        {
            if (type->is<Type::Unknown>() && left) type = left->type;
        }
        validate();
    }
    IRNODE_SUBCLASS(Shl)
    DECLARE_TYPEINFO_WITH_TYPEID(Shl, NodeKind::Shl, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class Shr : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring(">>"); }
    int getPrecedence() const override { return DBPrint::Prec_Shr; }
    bool operator==(IR::Shr const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Shr"_cs; }
    static cstring static_type_name() { return "Shr"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Shr(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Shr(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        {
            if (type->is<Type::Unknown>() && left) type = left->type;
        }
        validate();
    }
    Shr(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        {
            if (type->is<Type::Unknown>() && left) type = left->type;
        }
        validate();
    }
    Shr(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        {
            if (type->is<Type::Unknown>() && left) type = left->type;
        }
        validate();
    }
    Shr(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        {
            if (type->is<Type::Unknown>() && left) type = left->type;
        }
        validate();
    }
    IRNODE_SUBCLASS(Shr)
    DECLARE_TYPEINFO_WITH_TYPEID(Shr, NodeKind::Shr, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class Equ : public Operation_Relation {
 public:
    cstring getStringOp() const override { return cstring("=="); }
    int getPrecedence() const override { return DBPrint::Prec_Equ; }
    bool operator==(IR::Equ const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Equ"_cs; }
    static cstring static_type_name() { return "Equ"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Equ(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Relation const &a) const override;
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Equ(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Relation(srcInfo, type, left, right) {
        validate();
    }
    Equ(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(type, left, right) {
        validate();
    }
    Equ(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(srcInfo, left, right) {
        validate();
    }
    Equ(const IR::Expression *left, const IR::Expression *right) : Operation_Relation(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(Equ)
    DECLARE_TYPEINFO_WITH_TYPEID(Equ, NodeKind::Equ, Operation_Relation);
};
}  // namespace P4::IR
namespace P4::IR {
class Neq : public Operation_Relation {
 public:
    cstring getStringOp() const override { return cstring("!="); }
    int getPrecedence() const override { return DBPrint::Prec_Neq; }
    bool operator==(IR::Neq const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Neq"_cs; }
    static cstring static_type_name() { return "Neq"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Neq(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Relation const &a) const override;
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Neq(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Relation(srcInfo, type, left, right) {
        validate();
    }
    Neq(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(type, left, right) {
        validate();
    }
    Neq(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(srcInfo, left, right) {
        validate();
    }
    Neq(const IR::Expression *left, const IR::Expression *right) : Operation_Relation(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(Neq)
    DECLARE_TYPEINFO_WITH_TYPEID(Neq, NodeKind::Neq, Operation_Relation);
};
}  // namespace P4::IR
namespace P4::IR {
class Lss : public Operation_Relation {
 public:
    cstring getStringOp() const override { return cstring("<"); }
    int getPrecedence() const override { return DBPrint::Prec_Lss; }
    bool operator==(IR::Lss const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Lss"_cs; }
    static cstring static_type_name() { return "Lss"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Lss(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Relation const &a) const override;
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Lss(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Relation(srcInfo, type, left, right) {
        validate();
    }
    Lss(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(type, left, right) {
        validate();
    }
    Lss(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(srcInfo, left, right) {
        validate();
    }
    Lss(const IR::Expression *left, const IR::Expression *right) : Operation_Relation(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(Lss)
    DECLARE_TYPEINFO_WITH_TYPEID(Lss, NodeKind::Lss, Operation_Relation);
};
}  // namespace P4::IR
namespace P4::IR {
class Leq : public Operation_Relation {
 public:
    cstring getStringOp() const override { return cstring("<="); }
    int getPrecedence() const override { return DBPrint::Prec_Leq; }
    bool operator==(IR::Leq const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Leq"_cs; }
    static cstring static_type_name() { return "Leq"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Leq(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Relation const &a) const override;
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Leq(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Relation(srcInfo, type, left, right) {
        validate();
    }
    Leq(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(type, left, right) {
        validate();
    }
    Leq(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(srcInfo, left, right) {
        validate();
    }
    Leq(const IR::Expression *left, const IR::Expression *right) : Operation_Relation(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(Leq)
    DECLARE_TYPEINFO_WITH_TYPEID(Leq, NodeKind::Leq, Operation_Relation);
};
}  // namespace P4::IR
namespace P4::IR {
class Grt : public Operation_Relation {
 public:
    cstring getStringOp() const override { return cstring(">"); }
    int getPrecedence() const override { return DBPrint::Prec_Grt; }
    bool operator==(IR::Grt const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Grt"_cs; }
    static cstring static_type_name() { return "Grt"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Grt(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Relation const &a) const override;
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Grt(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Relation(srcInfo, type, left, right) {
        validate();
    }
    Grt(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(type, left, right) {
        validate();
    }
    Grt(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(srcInfo, left, right) {
        validate();
    }
    Grt(const IR::Expression *left, const IR::Expression *right) : Operation_Relation(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(Grt)
    DECLARE_TYPEINFO_WITH_TYPEID(Grt, NodeKind::Grt, Operation_Relation);
};
}  // namespace P4::IR
namespace P4::IR {
class Geq : public Operation_Relation {
 public:
    cstring getStringOp() const override { return cstring(">="); }
    int getPrecedence() const override { return DBPrint::Prec_Geq; }
    bool operator==(IR::Geq const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Geq"_cs; }
    static cstring static_type_name() { return "Geq"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Geq(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Relation const &a) const override;
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Geq(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Relation(srcInfo, type, left, right) {
        validate();
    }
    Geq(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(type, left, right) {
        validate();
    }
    Geq(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Relation(srcInfo, left, right) {
        validate();
    }
    Geq(const IR::Expression *left, const IR::Expression *right) : Operation_Relation(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(Geq)
    DECLARE_TYPEINFO_WITH_TYPEID(Geq, NodeKind::Geq, Operation_Relation);
};
}  // namespace P4::IR
namespace P4::IR {
class BAnd : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("&"); }
    int getPrecedence() const override { return DBPrint::Prec_BAnd; }
    bool operator==(IR::BAnd const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "BAnd"_cs; }
    static cstring static_type_name() { return "BAnd"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    BAnd(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    BAnd(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
         const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        validate();
    }
    BAnd(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        validate();
    }
    BAnd(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        validate();
    }
    BAnd(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(BAnd)
    DECLARE_TYPEINFO_WITH_TYPEID(BAnd, NodeKind::BAnd, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class BOr : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("|"); }
    int getPrecedence() const override { return DBPrint::Prec_BOr; }
    bool operator==(IR::BOr const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "BOr"_cs; }
    static cstring static_type_name() { return "BOr"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    BOr(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    BOr(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        validate();
    }
    BOr(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        validate();
    }
    BOr(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        validate();
    }
    BOr(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(BOr)
    DECLARE_TYPEINFO_WITH_TYPEID(BOr, NodeKind::BOr, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class BXor : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("^"); }
    int getPrecedence() const override { return DBPrint::Prec_BXor; }
    bool operator==(IR::BXor const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "BXor"_cs; }
    static cstring static_type_name() { return "BXor"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    BXor(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    BXor(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
         const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        validate();
    }
    BXor(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        validate();
    }
    BXor(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        validate();
    }
    BXor(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(BXor)
    DECLARE_TYPEINFO_WITH_TYPEID(BXor, NodeKind::BXor, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class LAnd : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("&&"); }
    int getPrecedence() const override { return DBPrint::Prec_LAnd; }
    bool operator==(IR::LAnd const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "LAnd"_cs; }
    static cstring static_type_name() { return "LAnd"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    LAnd(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    LAnd(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
         const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    LAnd(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    LAnd(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    LAnd(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    IRNODE_SUBCLASS(LAnd)
    DECLARE_TYPEINFO_WITH_TYPEID(LAnd, NodeKind::LAnd, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class LOr : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("||"); }
    int getPrecedence() const override { return DBPrint::Prec_LOr; }
    bool operator==(IR::LOr const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "LOr"_cs; }
    static cstring static_type_name() { return "LOr"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    LOr(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    LOr(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
        const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    LOr(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    LOr(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    LOr(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        {
            // This sets the type only when no type is explicitly provided in the constructor.
            // If a type is provided in the constructor this assignment has no effect
            // because the type member is shadowed by the type parameter.
            type = Type::Boolean::get();
        }
        validate();
    }
    IRNODE_SUBCLASS(LOr)
    DECLARE_TYPEINFO_WITH_TYPEID(LOr, NodeKind::LOr, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
/// Represents the ... default initializer expression
class Dots : public Expression {
 public:
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    bool operator==(IR::Dots const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Dots"_cs; }
    static cstring static_type_name() { return "Dots"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Dots(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Dots(Util::SourceInfo srcInfo, const IR::Type *type) : Expression(srcInfo, type) { validate(); }
    Dots(const IR::Type *type) : Expression(type) { validate(); }
    Dots(Util::SourceInfo srcInfo) : Expression(srcInfo) { validate(); }
    Dots() { validate(); }
    IRNODE_SUBCLASS(Dots)
    DECLARE_TYPEINFO_WITH_TYPEID(Dots, NodeKind::Dots, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
/// Represents the ... default initializer expression
/// when used in a StructExpression.
class NamedDots : public NamedExpression {
 public:
    NamedDots() : NamedExpression("...", new Dots()) {}
    NamedDots(Util::SourceInfo srcInfo, const IR::Dots *dots)
        : NamedExpression(srcInfo, "..."_cs, dots) {
        CHECK_NULL(dots);
    }
    NamedDots(Util::SourceInfo srcInfo) : NamedExpression(srcInfo, "...", new Dots()) {}
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    bool operator==(IR::NamedDots const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "NamedDots"_cs; }
    static cstring static_type_name() { return "NamedDots"_cs; }
    void toJSON(JSONGenerator &json) const override;
    NamedDots(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::NamedExpression const &a) const override;
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    NamedDots(Util::SourceInfo srcInfo, IR::ID name, const IR::Expression *expression)
        : NamedExpression(srcInfo, name, expression) {
        validate();
    }
    NamedDots(IR::ID name, const IR::Expression *expression) : NamedExpression(name, expression) {
        validate();
    }
    IRNODE_SUBCLASS(NamedDots)
    DECLARE_TYPEINFO_WITH_TYPEID(NamedDots, NodeKind::NamedDots, NamedExpression);
};
}  // namespace P4::IR
namespace P4::IR {
class Literal : public Expression, public virtual CompileTimeValue {
 public:
    bool operator==(IR::Literal const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Literal"_cs; }
    static cstring static_type_name() { return "Literal"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Literal(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Literal(Util::SourceInfo srcInfo, const IR::Type *type) : Expression(srcInfo, type) {
        validate();
    }
    Literal(const IR::Type *type) : Expression(type) { validate(); }
    Literal(Util::SourceInfo srcInfo) : Expression(srcInfo) { validate(); }
    Literal() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Literal)
    DECLARE_TYPEINFO_WITH_TYPEID(Literal, NodeKind::Literal, Expression, CompileTimeValue);
};
}  // namespace P4::IR
namespace P4::IR {
/// This is an integer literal on arbitrary-precision.
class Constant : public Literal {
 public:
    big_int value;
    unsigned base;
    /// base used when reading/writing
    /// if noWarning is true, no warning is emitted
    void handleOverflow(bool noWarning);

    Constant(int v, unsigned base = 10) : Literal(Type_InfInt::get()), value(v), base(base) {}
    Constant(unsigned v, unsigned base = 10) : Literal(Type_InfInt::get()), value(v), base(base) {}
#if __WORDSIZE == 64
    Constant(intmax_t v, unsigned base = 10) : Literal(Type_InfInt::get()), value(v), base(base) {}
#else
    Constant(long v, unsigned base = 10) : Literal(Type_InfInt::get()), value(v), base(base) {}
    Constant(unsigned long v, unsigned base = 10)
        : Literal(Type_InfInt::get()), value(v), base(base) {}
    Constant(intmax_t v, unsigned base = 10) : Literal(Type_InfInt::get()), value(v), base(base) {}
#endif
    Constant(uint64_t v, unsigned base = 10) : Literal(Type_InfInt::get()), value(v), base(base) {}
    Constant(big_int v, unsigned base = 10) : Literal(Type_InfInt::get()), value(v), base(base) {}
    Constant(Util::SourceInfo si, big_int v, unsigned base = 10)
        : Literal(si, Type_InfInt::get()), value(v), base(base) {}
    Constant(IR::Type const *t, big_int v, unsigned base = 10, bool noWarning = false)
        : Literal(t), value(v), base(base) {
        CHECK_NULL(t);
        handleOverflow(noWarning);
    }
    Constant(Util::SourceInfo si, IR::Type const *t, big_int v, unsigned base = 10,
             bool noWarning = false)
        : Literal(si, t), value(v), base(base) {
        CHECK_NULL(t);
        handleOverflow(noWarning);
    }
    static Constant GetMask(unsigned width);
    /// @return a constant. Any constant returned here is interned. Base is always 10.
    static IR::Constant const *get(IR::Type const *t, big_int v, Util::SourceInfo si = {});
    bool fitsInt() const { return value >= INT_MIN && value <= INT_MAX; }
    bool fitsLong() const { return value >= LONG_MIN && value <= LONG_MAX; }
    bool fitsUint() const { return value >= 0 && value <= UINT_MAX; }
    bool fitsUint64() const { return value >= 0 && value <= UINT64_MAX; }
    bool fitsInt64() const { return value >= INT64_MIN && value <= INT64_MAX; }
    long asLong() const {
        if (!fitsLong())
            ::P4::error(ErrorType::ERR_OVERLIMIT, "%1$x: Value too large for long", this);
        return static_cast<long>(value);
    }
    int asInt() const {
        if (!fitsInt())
            ::P4::error(ErrorType::ERR_OVERLIMIT, "%1$x: Value too large for int", this);
        return static_cast<int>(value);
    }
    unsigned asUnsigned() const {
        if (!fitsUint())
            ::P4::error(ErrorType::ERR_OVERLIMIT, "%1$x: Value too large for unsigned int", this);
        return static_cast<unsigned>(value);
    }
    uint64_t asUint64() const {
        if (!fitsUint64())
            ::P4::error(ErrorType::ERR_OVERLIMIT, "%1$x: Value too large for uint64", this);
        return static_cast<uint64_t>(value);
    }
    int64_t asInt64() const {
        if (!fitsInt64())
            ::P4::error(ErrorType::ERR_OVERLIMIT, "%1$x: Value too large for int64", this);
        return static_cast<int64_t>(value);
    }

    Constant operator<<(const unsigned &shift) const;
    Constant operator>>(const unsigned &shift) const;
    Constant operator&(const Constant &c) const;
    Constant operator|(const Constant &c) const;
    Constant operator^(const Constant &c) const;
    Constant operator-(const Constant &c) const;
    Constant operator-() const;
    cstring toString() const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    bool operator==(IR::Constant const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Constant"_cs; }
    static cstring static_type_name() { return "Constant"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Constant(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Literal const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    IRNODE_SUBCLASS(Constant)
    DECLARE_TYPEINFO_WITH_TYPEID(Constant, NodeKind::Constant, Literal);
};
}  // namespace P4::IR
namespace P4::IR {
class BoolLiteral : public Literal {
 public:
    bool value;
    cstring toString() const override;
    /// @return a bool literal. Both booleans are interned.
    static IR::BoolLiteral const *get(bool value, Util::SourceInfo const &si = {});
    bool operator==(IR::BoolLiteral const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "BoolLiteral"_cs; }
    static cstring static_type_name() { return "BoolLiteral"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    BoolLiteral(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Literal const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    BoolLiteral(Util::SourceInfo srcInfo, const IR::Type *type, bool value)
        : Literal(srcInfo, type), value(value) {
        validate();
    }
    BoolLiteral(const IR::Type *type, bool value) : Literal(type), value(value) { validate(); }
    BoolLiteral(Util::SourceInfo srcInfo, bool value) : Literal(srcInfo), value(value) {
        validate();
    }
    BoolLiteral(bool value) : value(value) { validate(); }
    IRNODE_SUBCLASS(BoolLiteral)
    DECLARE_TYPEINFO_WITH_TYPEID(BoolLiteral, NodeKind::BoolLiteral, Literal);
};
}  // namespace P4::IR
namespace P4::IR {
class StringLiteral : public Literal {
 public:
    cstring value;
    void validate() const override;
    cstring toString() const override;
    StringLiteral(IR::ID v) : Literal(v.srcInfo), value(v.name) {}
    operator IR::ID() const { return IR::ID(srcInfo, value); }
    /// @returns a string literal. The value is cached.
    static IR::StringLiteral const *get(cstring value, IR::Type const *t = Type_String::get(),
                                        Util::SourceInfo const &si = {});
    bool operator==(IR::StringLiteral const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "StringLiteral"_cs; }
    static cstring static_type_name() { return "StringLiteral"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    StringLiteral(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Literal const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    StringLiteral(Util::SourceInfo srcInfo, const IR::Type *type, cstring value)
        : Literal(srcInfo, type), value(value) {
        validate();
    }
    StringLiteral(const IR::Type *type, cstring value) : Literal(type), value(value) { validate(); }
    StringLiteral(Util::SourceInfo srcInfo, cstring value) : Literal(srcInfo), value(value) {
        validate();
    }
    StringLiteral(cstring value) : value(value) { validate(); }
    IRNODE_SUBCLASS(StringLiteral)
    DECLARE_TYPEINFO_WITH_TYPEID(StringLiteral, NodeKind::StringLiteral, Literal);
};
}  // namespace P4::IR
namespace P4::IR {
class PathExpression : public Expression {
 public:
    const IR::Path *path = nullptr;
    PathExpression(const IR::Type *t, IR::ID id)
        : Expression(id.srcInfo, t), path(new IR::Path(id)) {}
    PathExpression(IR::ID id) : Expression(id.srcInfo), path(new IR::Path(id)) {}
    cstring toString() const override;
    bool operator==(IR::PathExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "PathExpression"_cs; }
    static cstring static_type_name() { return "PathExpression"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    PathExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    PathExpression(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Path *path)
        : Expression(srcInfo, type), path(path) {
        {
            if (!srcInfo && path) srcInfo = path->srcInfo;
        }
        validate();
    }
    PathExpression(const IR::Type *type, const IR::Path *path) : Expression(type), path(path) {
        {
            if (!srcInfo && path) srcInfo = path->srcInfo;
        }
        validate();
    }
    PathExpression(Util::SourceInfo srcInfo, const IR::Path *path)
        : Expression(srcInfo), path(path) {
        {
            if (!srcInfo && path) srcInfo = path->srcInfo;
        }
        validate();
    }
    PathExpression(const IR::Path *path) : path(path) {
        {
            if (!srcInfo && path) srcInfo = path->srcInfo;
        }
        validate();
    }
    IRNODE_SUBCLASS(PathExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(PathExpression, NodeKind::PathExpression, Expression);
};
}  // namespace P4::IR
namespace P4::IR {

class TypeNameExpression : public Expression {
 public:
    const IR::Type *typeName = nullptr;
    TypeNameExpression(IR::ID id)
        : Expression(id.srcInfo), typeName(new IR::Type_Name(new IR::Path(id))) {}
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    void validate() const override;
    bool operator==(IR::TypeNameExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "TypeNameExpression"_cs; }
    static cstring static_type_name() { return "TypeNameExpression"_cs; }
    void toJSON(JSONGenerator &json) const override;
    TypeNameExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    TypeNameExpression(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Type *typeName)
        : Expression(srcInfo, type), typeName(typeName) {
        {
            if (!srcInfo && typeName) srcInfo = typeName->srcInfo;
        }
        validate();
    }
    TypeNameExpression(const IR::Type *type, const IR::Type *typeName)
        : Expression(type), typeName(typeName) {
        {
            if (!srcInfo && typeName) srcInfo = typeName->srcInfo;
        }
        validate();
    }
    TypeNameExpression(Util::SourceInfo srcInfo, const IR::Type *typeName)
        : Expression(srcInfo), typeName(typeName) {
        {
            if (!srcInfo && typeName) srcInfo = typeName->srcInfo;
        }
        validate();
    }
    TypeNameExpression(const IR::Type *typeName) : typeName(typeName) {
        {
            if (!srcInfo && typeName) srcInfo = typeName->srcInfo;
        }
        validate();
    }
    IRNODE_SUBCLASS(TypeNameExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(TypeNameExpression, NodeKind::TypeNameExpression, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
class AbstractSlice : public Operation_Ternary {
 public:
    virtual unsigned getH() const = 0;
    virtual unsigned getL() const = 0;
    bool operator==(IR::AbstractSlice const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "AbstractSlice"_cs; }
    static cstring static_type_name() { return "AbstractSlice"_cs; }
    void toJSON(JSONGenerator &json) const override;
    AbstractSlice(JSONLoader &json);
    bool operator==(IR::Operation_Ternary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    AbstractSlice(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *e0,
                  const IR::Expression *e1, const IR::Expression *e2)
        : Operation_Ternary(srcInfo, type, e0, e1, e2) {
        validate();
    }
    AbstractSlice(const IR::Type *type, const IR::Expression *e0, const IR::Expression *e1,
                  const IR::Expression *e2)
        : Operation_Ternary(type, e0, e1, e2) {
        validate();
    }
    AbstractSlice(Util::SourceInfo srcInfo, const IR::Expression *e0, const IR::Expression *e1,
                  const IR::Expression *e2)
        : Operation_Ternary(srcInfo, e0, e1, e2) {
        validate();
    }
    AbstractSlice(const IR::Expression *e0, const IR::Expression *e1, const IR::Expression *e2)
        : Operation_Ternary(e0, e1, e2) {
        validate();
    }
    IRNODE_ABSTRACT_SUBCLASS(AbstractSlice)
    DECLARE_TYPEINFO_WITH_TYPEID(AbstractSlice, NodeKind::AbstractSlice, Operation_Ternary);
};
}  // namespace P4::IR
namespace P4::IR {
class Slice : public AbstractSlice {
 public:
    int getPrecedence() const override { return DBPrint::Prec_Postfix; }
    cstring getStringOp() const override { return cstring("[:]"); }
    cstring toString() const override;

    unsigned getH() const override;
    unsigned getL() const override;
    Slice(const IR::Expression *a, int hi, int lo)
        : AbstractSlice(IR::Type::Bits::get(hi - lo + 1), a, new Constant(hi), new Constant(lo)) {}
    Slice(Util::SourceInfo si, const IR::Expression *a, int hi, int lo)
        : AbstractSlice(si, IR::Type::Bits::get(hi - lo + 1), a, new Constant(hi),
                        new Constant(lo)) {}

    static const IR::Expression *make(const IR::Expression *a, unsigned hi, unsigned lo);
    bool operator==(IR::Slice const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Slice"_cs; }
    static cstring static_type_name() { return "Slice"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Slice(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::AbstractSlice const &a) const override;
    bool operator==(IR::Operation_Ternary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Slice(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *e0,
          const IR::Expression *e1, const IR::Expression *e2)
        : AbstractSlice(srcInfo, type, e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e1 && e1->is<Constant>() && e2 && e2->is<Constant>())
                type = IR::Type::Bits::get(getH() - getL() + 1);
        }
        validate();
    }
    Slice(const IR::Type *type, const IR::Expression *e0, const IR::Expression *e1,
          const IR::Expression *e2)
        : AbstractSlice(type, e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e1 && e1->is<Constant>() && e2 && e2->is<Constant>())
                type = IR::Type::Bits::get(getH() - getL() + 1);
        }
        validate();
    }
    Slice(Util::SourceInfo srcInfo, const IR::Expression *e0, const IR::Expression *e1,
          const IR::Expression *e2)
        : AbstractSlice(srcInfo, e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e1 && e1->is<Constant>() && e2 && e2->is<Constant>())
                type = IR::Type::Bits::get(getH() - getL() + 1);
        }
        validate();
    }
    Slice(const IR::Expression *e0, const IR::Expression *e1, const IR::Expression *e2)
        : AbstractSlice(e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e1 && e1->is<Constant>() && e2 && e2->is<Constant>())
                type = IR::Type::Bits::get(getH() - getL() + 1);
        }
        validate();
    }
    IRNODE_SUBCLASS(Slice)
    DECLARE_TYPEINFO_WITH_TYPEID(Slice, NodeKind::Slice, AbstractSlice);
};
}  // namespace P4::IR
namespace P4::IR {
class PlusSlice : public AbstractSlice {
 public:
    int getPrecedence() const override { return DBPrint::Prec_Postfix; }
    cstring getStringOp() const override { return cstring("[+:]"); }
    cstring toString() const override;
    unsigned getH() const override;
    unsigned getL() const override;
    PlusSlice(const IR::Expression *a, const IR::Expression *lo, int width)
        : AbstractSlice(IR::Type::Bits::get(width), a, lo, new Constant(width)) {}
    bool operator==(IR::PlusSlice const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "PlusSlice"_cs; }
    static cstring static_type_name() { return "PlusSlice"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    PlusSlice(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::AbstractSlice const &a) const override;
    bool operator==(IR::Operation_Ternary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    PlusSlice(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *e0,
              const IR::Expression *e1, const IR::Expression *e2)
        : AbstractSlice(srcInfo, type, e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e2 && e2->is<Constant>())
                type = IR::Type::Bits::get(e2->to<IR::Constant>()->asUnsigned());
        }
        validate();
    }
    PlusSlice(const IR::Type *type, const IR::Expression *e0, const IR::Expression *e1,
              const IR::Expression *e2)
        : AbstractSlice(type, e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e2 && e2->is<Constant>())
                type = IR::Type::Bits::get(e2->to<IR::Constant>()->asUnsigned());
        }
        validate();
    }
    PlusSlice(Util::SourceInfo srcInfo, const IR::Expression *e0, const IR::Expression *e1,
              const IR::Expression *e2)
        : AbstractSlice(srcInfo, e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e2 && e2->is<Constant>())
                type = IR::Type::Bits::get(e2->to<IR::Constant>()->asUnsigned());
        }
        validate();
    }
    PlusSlice(const IR::Expression *e0, const IR::Expression *e1, const IR::Expression *e2)
        : AbstractSlice(e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e2 && e2->is<Constant>())
                type = IR::Type::Bits::get(e2->to<IR::Constant>()->asUnsigned());
        }
        validate();
    }
    IRNODE_SUBCLASS(PlusSlice)
    DECLARE_TYPEINFO_WITH_TYPEID(PlusSlice, NodeKind::PlusSlice, AbstractSlice);
};
}  // namespace P4::IR
namespace P4::IR {
class Member : public Operation_Unary {
 public:
    int getPrecedence() const override { return DBPrint::Prec_Postfix; }
    IR::ID member;
    virtual int offset_bits() const;
    int lsb() const;
    int msb() const;
    cstring getStringOp() const override { return cstring("."); }
    cstring toString() const override;
    bool operator==(IR::Member const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Member"_cs; }
    static cstring static_type_name() { return "Member"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Member(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Unary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Member(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *expr,
           IR::ID member)
        : Operation_Unary(srcInfo, type, expr), member(member) {
        validate();
    }
    Member(const IR::Type *type, const IR::Expression *expr, IR::ID member)
        : Operation_Unary(type, expr), member(member) {
        validate();
    }
    Member(Util::SourceInfo srcInfo, const IR::Expression *expr, IR::ID member)
        : Operation_Unary(srcInfo, expr), member(member) {
        validate();
    }
    Member(const IR::Expression *expr, IR::ID member) : Operation_Unary(expr), member(member) {
        validate();
    }
    IRNODE_SUBCLASS(Member)
    DECLARE_TYPEINFO_WITH_TYPEID(Member, NodeKind::Member, Operation_Unary);
};
}  // namespace P4::IR
namespace P4::IR {
class Concat : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("++"); }
    int getPrecedence() const override { return DBPrint::Prec_Add; }
    bool operator==(IR::Concat const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Concat"_cs; }
    static cstring static_type_name() { return "Concat"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Concat(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Concat(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
           const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        {
            if (left && right) {
                auto lt = left->type->to<IR::Type::Bits>();
                auto rt = right->type->to<IR::Type::Bits>();
                if (lt && rt) type = IR::Type::Bits::get(lt->size + rt->size, lt->isSigned);
            }
        }
        validate();
    }
    Concat(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        {
            if (left && right) {
                auto lt = left->type->to<IR::Type::Bits>();
                auto rt = right->type->to<IR::Type::Bits>();
                if (lt && rt) type = IR::Type::Bits::get(lt->size + rt->size, lt->isSigned);
            }
        }
        validate();
    }
    Concat(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        {
            if (left && right) {
                auto lt = left->type->to<IR::Type::Bits>();
                auto rt = right->type->to<IR::Type::Bits>();
                if (lt && rt) type = IR::Type::Bits::get(lt->size + rt->size, lt->isSigned);
            }
        }
        validate();
    }
    Concat(const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(left, right) {
        {
            if (left && right) {
                auto lt = left->type->to<IR::Type::Bits>();
                auto rt = right->type->to<IR::Type::Bits>();
                if (lt && rt) type = IR::Type::Bits::get(lt->size + rt->size, lt->isSigned);
            }
        }
        validate();
    }
    IRNODE_SUBCLASS(Concat)
    DECLARE_TYPEINFO_WITH_TYPEID(Concat, NodeKind::Concat, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class ArrayIndex : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("[]"); }
    int getPrecedence() const override { return DBPrint::Prec_Postfix; }
    cstring toString() const override;
    bool operator==(IR::ArrayIndex const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "ArrayIndex"_cs; }
    static cstring static_type_name() { return "ArrayIndex"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ArrayIndex(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ArrayIndex(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
               const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        {
            if (auto st = left ? left->type->to<IR::Type_Array>() : nullptr) type = st->elementType;
        }
        validate();
    }
    ArrayIndex(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        {
            if (auto st = left ? left->type->to<IR::Type_Array>() : nullptr) type = st->elementType;
        }
        validate();
    }
    ArrayIndex(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        {
            if (auto st = left ? left->type->to<IR::Type_Array>() : nullptr) type = st->elementType;
        }
        validate();
    }
    ArrayIndex(const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(left, right) {
        {
            if (auto st = left ? left->type->to<IR::Type_Array>() : nullptr) type = st->elementType;
        }
        validate();
    }
    IRNODE_SUBCLASS(ArrayIndex)
    DECLARE_TYPEINFO_WITH_TYPEID(ArrayIndex, NodeKind::ArrayIndex, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class Range : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring(".."); }
    int getPrecedence() const override { return DBPrint::Prec_Low; }
    bool operator==(IR::Range const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Range"_cs; }
    static cstring static_type_name() { return "Range"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Range(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Range(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
          const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        {
            if (left && type == left->type && !left->type->is<Type::Unknown>())
                type = new Type_Set(left->type);
        }
        validate();
    }
    Range(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        {
            if (left && type == left->type && !left->type->is<Type::Unknown>())
                type = new Type_Set(left->type);
        }
        validate();
    }
    Range(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        {
            if (left && type == left->type && !left->type->is<Type::Unknown>())
                type = new Type_Set(left->type);
        }
        validate();
    }
    Range(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        {
            if (left && type == left->type && !left->type->is<Type::Unknown>())
                type = new Type_Set(left->type);
        }
        validate();
    }
    IRNODE_SUBCLASS(Range)
    DECLARE_TYPEINFO_WITH_TYPEID(Range, NodeKind::Range, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class Mask : public Operation_Binary {
 public:
    cstring getStringOp() const override { return cstring("&&&"); }
    int getPrecedence() const override { return DBPrint::Prec_Low; }
    bool operator==(IR::Mask const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Mask"_cs; }
    static cstring static_type_name() { return "Mask"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Mask(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Binary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Mask(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *left,
         const IR::Expression *right)
        : Operation_Binary(srcInfo, type, left, right) {
        {
            if (left && type == left->type && !left->type->is<Type::Unknown>())
                type = new Type_Set(left->type);
        }
        validate();
    }
    Mask(const IR::Type *type, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(type, left, right) {
        {
            if (left && type == left->type && !left->type->is<Type::Unknown>())
                type = new Type_Set(left->type);
        }
        validate();
    }
    Mask(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : Operation_Binary(srcInfo, left, right) {
        {
            if (left && type == left->type && !left->type->is<Type::Unknown>())
                type = new Type_Set(left->type);
        }
        validate();
    }
    Mask(const IR::Expression *left, const IR::Expression *right) : Operation_Binary(left, right) {
        {
            if (left && type == left->type && !left->type->is<Type::Unknown>())
                type = new Type_Set(left->type);
        }
        validate();
    }
    IRNODE_SUBCLASS(Mask)
    DECLARE_TYPEINFO_WITH_TYPEID(Mask, NodeKind::Mask, Operation_Binary);
};
}  // namespace P4::IR
namespace P4::IR {
class Mux : public Operation_Ternary {
 public:
    cstring getStringOp() const override { return cstring("?:"); }
    int getPrecedence() const override { return DBPrint::Prec_Low; }
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    bool operator==(IR::Mux const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Mux"_cs; }
    static cstring static_type_name() { return "Mux"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Mux(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Ternary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Mux(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *e0,
        const IR::Expression *e1, const IR::Expression *e2)
        : Operation_Ternary(srcInfo, type, e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e1 && e2 && e1->type == e2->type) type = e1->type;
        }
        validate();
    }
    Mux(const IR::Type *type, const IR::Expression *e0, const IR::Expression *e1,
        const IR::Expression *e2)
        : Operation_Ternary(type, e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e1 && e2 && e1->type == e2->type) type = e1->type;
        }
        validate();
    }
    Mux(Util::SourceInfo srcInfo, const IR::Expression *e0, const IR::Expression *e1,
        const IR::Expression *e2)
        : Operation_Ternary(srcInfo, e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e1 && e2 && e1->type == e2->type) type = e1->type;
        }
        validate();
    }
    Mux(const IR::Expression *e0, const IR::Expression *e1, const IR::Expression *e2)
        : Operation_Ternary(e0, e1, e2) {
        {
            if (type->is<Type::Unknown>() && e1 && e2 && e1->type == e2->type) type = e1->type;
        }
        validate();
    }
    IRNODE_SUBCLASS(Mux)
    DECLARE_TYPEINFO_WITH_TYPEID(Mux, NodeKind::Mux, Operation_Ternary);
};
}  // namespace P4::IR
namespace P4::IR {
class DefaultExpression : public Expression {
 public:
    bool operator==(IR::DefaultExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "DefaultExpression"_cs; }
    static cstring static_type_name() { return "DefaultExpression"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    DefaultExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    DefaultExpression(Util::SourceInfo srcInfo, const IR::Type *type) : Expression(srcInfo, type) {
        validate();
    }
    DefaultExpression(const IR::Type *type) : Expression(type) { validate(); }
    DefaultExpression(Util::SourceInfo srcInfo) : Expression(srcInfo) { validate(); }
    DefaultExpression() { validate(); }
    IRNODE_SUBCLASS(DefaultExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(DefaultExpression, NodeKind::DefaultExpression, Expression);
};
}  // namespace P4::IR
namespace P4::IR {

class This : public Expression {
 public:
    long id = nextId++;
    cstring toString() const override;

 private:
    static long nextId;

 public:
    bool operator==(IR::This const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "This"_cs; }
    static cstring static_type_name() { return "This"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    This(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    This(Util::SourceInfo srcInfo, const IR::Type *type) : Expression(srcInfo, type) { validate(); }
    This(const IR::Type *type) : Expression(type) { validate(); }
    This(Util::SourceInfo srcInfo) : Expression(srcInfo) { validate(); }
    This() { validate(); }
    IRNODE_SUBCLASS(This)
    DECLARE_TYPEINFO_WITH_TYPEID(This, NodeKind::This, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
class Cast : public Operation_Unary {
 public:
    /// These will generally always be the same, except when a cast to a type argument of
    /// a generic occurs.  Then at some point, the 'destType' will be specialized to a concrete
    /// type, and 'type' will only be updated later when type inferencing occurs
    const IR::Type *destType = type;
    bool implicit = false;
    int getPrecedence() const override { return DBPrint::Prec_Prefix; }
    cstring getStringOp() const override { return cstring("(cast)"); }
    cstring toString() const override;
    void validate() const override;
    bool operator==(IR::Cast const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Cast"_cs; }
    static cstring static_type_name() { return "Cast"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Cast(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Unary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Cast(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *expr, bool implicit)
        : Operation_Unary(srcInfo, type, expr), implicit(implicit) {
        validate();
    }
    Cast(const IR::Type *type, const IR::Expression *expr, bool implicit)
        : Operation_Unary(type, expr), implicit(implicit) {
        validate();
    }
    Cast(Util::SourceInfo srcInfo, const IR::Expression *expr, bool implicit)
        : Operation_Unary(srcInfo, expr), implicit(implicit) {
        validate();
    }
    Cast(const IR::Expression *expr, bool implicit) : Operation_Unary(expr), implicit(implicit) {
        validate();
    }
    Cast(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *expr)
        : Operation_Unary(srcInfo, type, expr) {
        validate();
    }
    Cast(const IR::Type *type, const IR::Expression *expr) : Operation_Unary(type, expr) {
        validate();
    }
    Cast(Util::SourceInfo srcInfo, const IR::Expression *expr) : Operation_Unary(srcInfo, expr) {
        validate();
    }
    Cast(const IR::Expression *expr) : Operation_Unary(expr) { validate(); }
    IRNODE_SUBCLASS(Cast)
    DECLARE_TYPEINFO_WITH_TYPEID(Cast, NodeKind::Cast, Operation_Unary);
};
}  // namespace P4::IR
namespace P4::IR {
class SelectCase : public Node {
 public:
    const IR::Expression *keyset = nullptr;
    const IR::PathExpression *state = nullptr;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::SelectCase const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "SelectCase"_cs; }
    static cstring static_type_name() { return "SelectCase"_cs; }
    void toJSON(JSONGenerator &json) const override;
    SelectCase(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    SelectCase(Util::SourceInfo srcInfo, const IR::Expression *keyset,
               const IR::PathExpression *state)
        : Node(srcInfo), keyset(keyset), state(state) {
        validate();
    }
    SelectCase(const IR::Expression *keyset, const IR::PathExpression *state)
        : keyset(keyset), state(state) {
        validate();
    }
    IRNODE_SUBCLASS(SelectCase)
    DECLARE_TYPEINFO_WITH_TYPEID(SelectCase, NodeKind::SelectCase, Node);
};
}  // namespace P4::IR
namespace P4::IR {
class SelectExpression : public Expression {
 public:
    const IR::ListExpression *select = nullptr;
    IR::Vector<IR::SelectCase> selectCases;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    bool operator==(IR::SelectExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void validate() const override;
    cstring node_type_name() const override { return "SelectExpression"_cs; }
    static cstring static_type_name() { return "SelectExpression"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    SelectExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    SelectExpression(Util::SourceInfo srcInfo, const IR::Type *type,
                     const IR::ListExpression *select, IR::Vector<IR::SelectCase> selectCases)
        : Expression(srcInfo, type), select(select), selectCases(selectCases) {
        validate();
    }
    SelectExpression(const IR::Type *type, const IR::ListExpression *select,
                     IR::Vector<IR::SelectCase> selectCases)
        : Expression(type), select(select), selectCases(selectCases) {
        validate();
    }
    SelectExpression(Util::SourceInfo srcInfo, const IR::ListExpression *select,
                     IR::Vector<IR::SelectCase> selectCases)
        : Expression(srcInfo), select(select), selectCases(selectCases) {
        validate();
    }
    SelectExpression(const IR::ListExpression *select, IR::Vector<IR::SelectCase> selectCases)
        : select(select), selectCases(selectCases) {
        validate();
    }
    IRNODE_SUBCLASS(SelectExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(SelectExpression, NodeKind::SelectExpression, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
class MethodCallExpression : public Expression {
 public:
    const IR::Expression *method = nullptr;
    const IR::Vector<IR::Type> *typeArguments = new Vector<Type>;
    const IR::Vector<IR::Argument> *arguments = new Vector<Argument>;
    cstring toString() const override;
    void validate() const override;
    MethodCallExpression(Util::SourceInfo si, IR::ID m,
                         std::initializer_list<const IR::Argument *> a)
        : Expression(si), method(new PathExpression(m)), arguments(new Vector<Argument>(a)) {}
    MethodCallExpression(Util::SourceInfo si, const IR::Expression *m,
                         std::initializer_list<const IR::Argument *> const &a)
        : Expression(si), method(m), arguments(new Vector<Argument>(a)) {}
    MethodCallExpression(const IR::Expression *m,
                         std::initializer_list<IR::Expression const *> const &a);
    bool operator==(IR::MethodCallExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "MethodCallExpression"_cs; }
    static cstring static_type_name() { return "MethodCallExpression"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    MethodCallExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    MethodCallExpression(Util::SourceInfo srcInfo, const IR::Type *type,
                         const IR::Expression *method, const IR::Vector<IR::Type> *typeArguments,
                         const IR::Vector<IR::Argument> *arguments)
        : Expression(srcInfo, type),
          method(method),
          typeArguments(typeArguments),
          arguments(arguments) {
        validate();
    }
    MethodCallExpression(const IR::Type *type, const IR::Expression *method,
                         const IR::Vector<IR::Type> *typeArguments,
                         const IR::Vector<IR::Argument> *arguments)
        : Expression(type), method(method), typeArguments(typeArguments), arguments(arguments) {
        validate();
    }
    MethodCallExpression(Util::SourceInfo srcInfo, const IR::Expression *method,
                         const IR::Vector<IR::Type> *typeArguments,
                         const IR::Vector<IR::Argument> *arguments)
        : Expression(srcInfo), method(method), typeArguments(typeArguments), arguments(arguments) {
        validate();
    }
    MethodCallExpression(const IR::Expression *method, const IR::Vector<IR::Type> *typeArguments,
                         const IR::Vector<IR::Argument> *arguments)
        : method(method), typeArguments(typeArguments), arguments(arguments) {
        validate();
    }
    MethodCallExpression(Util::SourceInfo srcInfo, const IR::Type *type,
                         const IR::Expression *method, const IR::Vector<IR::Argument> *arguments)
        : Expression(srcInfo, type), method(method), arguments(arguments) {
        validate();
    }
    MethodCallExpression(const IR::Type *type, const IR::Expression *method,
                         const IR::Vector<IR::Argument> *arguments)
        : Expression(type), method(method), arguments(arguments) {
        validate();
    }
    MethodCallExpression(Util::SourceInfo srcInfo, const IR::Expression *method,
                         const IR::Vector<IR::Argument> *arguments)
        : Expression(srcInfo), method(method), arguments(arguments) {
        validate();
    }
    MethodCallExpression(const IR::Expression *method, const IR::Vector<IR::Argument> *arguments)
        : method(method), arguments(arguments) {
        validate();
    }
    MethodCallExpression(Util::SourceInfo srcInfo, const IR::Type *type,
                         const IR::Expression *method, const IR::Vector<IR::Type> *typeArguments)
        : Expression(srcInfo, type), method(method), typeArguments(typeArguments) {
        validate();
    }
    MethodCallExpression(const IR::Type *type, const IR::Expression *method,
                         const IR::Vector<IR::Type> *typeArguments)
        : Expression(type), method(method), typeArguments(typeArguments) {
        validate();
    }
    MethodCallExpression(Util::SourceInfo srcInfo, const IR::Expression *method,
                         const IR::Vector<IR::Type> *typeArguments)
        : Expression(srcInfo), method(method), typeArguments(typeArguments) {
        validate();
    }
    MethodCallExpression(const IR::Expression *method, const IR::Vector<IR::Type> *typeArguments)
        : method(method), typeArguments(typeArguments) {
        validate();
    }
    MethodCallExpression(Util::SourceInfo srcInfo, const IR::Type *type,
                         const IR::Expression *method)
        : Expression(srcInfo, type), method(method) {
        validate();
    }
    MethodCallExpression(const IR::Type *type, const IR::Expression *method)
        : Expression(type), method(method) {
        validate();
    }
    MethodCallExpression(Util::SourceInfo srcInfo, const IR::Expression *method)
        : Expression(srcInfo), method(method) {
        validate();
    }
    MethodCallExpression(const IR::Expression *method) : method(method) { validate(); }
    IRNODE_SUBCLASS(MethodCallExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(MethodCallExpression, NodeKind::MethodCallExpression, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
class ConstructorCallExpression : public Expression {
 public:
    const IR::Type *constructedType = type;

    const IR::Vector<IR::Argument> *arguments = nullptr;
    cstring toString() const override;
    void validate() const override;
    bool operator==(IR::ConstructorCallExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "ConstructorCallExpression"_cs; }
    static cstring static_type_name() { return "ConstructorCallExpression"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ConstructorCallExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ConstructorCallExpression(Util::SourceInfo srcInfo, const IR::Type *type,
                              const IR::Vector<IR::Argument> *arguments)
        : Expression(srcInfo, type), arguments(arguments) {
        validate();
    }
    ConstructorCallExpression(const IR::Type *type, const IR::Vector<IR::Argument> *arguments)
        : Expression(type), arguments(arguments) {
        validate();
    }
    ConstructorCallExpression(Util::SourceInfo srcInfo, const IR::Vector<IR::Argument> *arguments)
        : Expression(srcInfo), arguments(arguments) {
        validate();
    }
    ConstructorCallExpression(const IR::Vector<IR::Argument> *arguments) : arguments(arguments) {
        validate();
    }
    IRNODE_SUBCLASS(ConstructorCallExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(ConstructorCallExpression, NodeKind::ConstructorCallExpression,
                                 Expression);
};
}  // namespace P4::IR
namespace P4::IR {
class BaseListExpression : public Expression {
 public:
    IR::Vector<IR::Expression> components;
    void validate() const override;
    size_t size() const { return components.size(); }
    void push_back(const IR::Expression *e) { components.push_back(e); }
    bool containsDots() const {
        if (components.empty()) return false;
        size_t size = components.size();
        return components.at(size - 1)->is<IR::Dots>();
    }
    cstring toString() const override;
    bool operator==(IR::BaseListExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "BaseListExpression"_cs; }
    static cstring static_type_name() { return "BaseListExpression"_cs; }
    void toJSON(JSONGenerator &json) const override;
    BaseListExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    BaseListExpression(Util::SourceInfo srcInfo, const IR::Type *type,
                       IR::Vector<IR::Expression> components)
        : Expression(srcInfo, type), components(components) {
        validate();
    }
    BaseListExpression(const IR::Type *type, IR::Vector<IR::Expression> components)
        : Expression(type), components(components) {
        validate();
    }
    BaseListExpression(Util::SourceInfo srcInfo, IR::Vector<IR::Expression> components)
        : Expression(srcInfo), components(components) {
        validate();
    }
    BaseListExpression(IR::Vector<IR::Expression> components) : components(components) {
        validate();
    }
    IRNODE_SUBCLASS(BaseListExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(BaseListExpression, NodeKind::BaseListExpression, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
/// Represents a list of expressions separated by commas
class ListExpression : public BaseListExpression {
 public:
    bool operator==(IR::ListExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "ListExpression"_cs; }
    static cstring static_type_name() { return "ListExpression"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ListExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::BaseListExpression const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ListExpression(Util::SourceInfo srcInfo, const IR::Type *type,
                   IR::Vector<IR::Expression> components)
        : BaseListExpression(srcInfo, type, components) {
        {
            validate();
            if (type->is<Type::Unknown>()) {
                Vector<Type> tuple;
                for (auto e : components) tuple.push_back(e->type);
                type = new Type_List(tuple);
            }
        }
        validate();
    }
    ListExpression(const IR::Type *type, IR::Vector<IR::Expression> components)
        : BaseListExpression(type, components) {
        {
            validate();
            if (type->is<Type::Unknown>()) {
                Vector<Type> tuple;
                for (auto e : components) tuple.push_back(e->type);
                type = new Type_List(tuple);
            }
        }
        validate();
    }
    ListExpression(Util::SourceInfo srcInfo, IR::Vector<IR::Expression> components)
        : BaseListExpression(srcInfo, components) {
        {
            validate();
            if (type->is<Type::Unknown>()) {
                Vector<Type> tuple;
                for (auto e : components) tuple.push_back(e->type);
                type = new Type_List(tuple);
            }
        }
        validate();
    }
    ListExpression(IR::Vector<IR::Expression> components) : BaseListExpression(components) {
        {
            validate();
            if (type->is<Type::Unknown>()) {
                Vector<Type> tuple;
                for (auto e : components) tuple.push_back(e->type);
                type = new Type_List(tuple);
            }
        }
        validate();
    }
    IRNODE_SUBCLASS(ListExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(ListExpression, NodeKind::ListExpression, BaseListExpression);
};
}  // namespace P4::IR
namespace P4::IR {
/// Represents P4 list expression, not to be confused with
/// ListExpression from above.
class P4ListExpression : public BaseListExpression {
 public:
    const IR::Type *elementType = nullptr;
    bool operator==(IR::P4ListExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "P4ListExpression"_cs; }
    static cstring static_type_name() { return "P4ListExpression"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    P4ListExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::BaseListExpression const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    P4ListExpression(Util::SourceInfo srcInfo, const IR::Type *type,
                     IR::Vector<IR::Expression> components, const IR::Type *elementType)
        : BaseListExpression(srcInfo, type, components), elementType(elementType) {
        {
            validate();
            if (type->is<Type::Unknown>()) {
                type = new Type_P4List(elementType);
            }
        }
        validate();
    }
    P4ListExpression(const IR::Type *type, IR::Vector<IR::Expression> components,
                     const IR::Type *elementType)
        : BaseListExpression(type, components), elementType(elementType) {
        {
            validate();
            if (type->is<Type::Unknown>()) {
                type = new Type_P4List(elementType);
            }
        }
        validate();
    }
    P4ListExpression(Util::SourceInfo srcInfo, IR::Vector<IR::Expression> components,
                     const IR::Type *elementType)
        : BaseListExpression(srcInfo, components), elementType(elementType) {
        {
            validate();
            if (type->is<Type::Unknown>()) {
                type = new Type_P4List(elementType);
            }
        }
        validate();
    }
    P4ListExpression(IR::Vector<IR::Expression> components, const IR::Type *elementType)
        : BaseListExpression(components), elementType(elementType) {
        {
            validate();
            if (type->is<Type::Unknown>()) {
                type = new Type_P4List(elementType);
            }
        }
        validate();
    }
    IRNODE_SUBCLASS(P4ListExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(P4ListExpression, NodeKind::P4ListExpression, BaseListExpression);
};
}  // namespace P4::IR
namespace P4::IR {
/// An expression that evaluates to a struct.
class StructExpression : public Expression {
 public:
    /// The struct or header type that is being intialized.
    /// May only be known after type checking; so it can be nullptr.
    const IR::Type *structType = nullptr;
    IR::IndexedVector<IR::NamedExpression> components;
    void validate() const override;
    size_t size() const { return components.size(); }
    const IR::NamedExpression *getField(cstring name) const {
        return components.getDeclaration<NamedExpression>(name);
    }
    bool containsDots() const {
        if (components.empty()) return false;
        size_t size = components.size();
        return components.at(size - 1)->is<IR::NamedDots>();
    }
    cstring toString() const override;
    bool operator==(IR::StructExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "StructExpression"_cs; }
    static cstring static_type_name() { return "StructExpression"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    StructExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    StructExpression(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Type *structType,
                     IR::IndexedVector<IR::NamedExpression> components)
        : Expression(srcInfo, type), structType(structType), components(components) {
        validate();
    }
    StructExpression(const IR::Type *type, const IR::Type *structType,
                     IR::IndexedVector<IR::NamedExpression> components)
        : Expression(type), structType(structType), components(components) {
        validate();
    }
    StructExpression(Util::SourceInfo srcInfo, const IR::Type *structType,
                     IR::IndexedVector<IR::NamedExpression> components)
        : Expression(srcInfo), structType(structType), components(components) {
        validate();
    }
    StructExpression(const IR::Type *structType, IR::IndexedVector<IR::NamedExpression> components)
        : structType(structType), components(components) {
        validate();
    }
    IRNODE_SUBCLASS(StructExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(StructExpression, NodeKind::StructExpression, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
/// Can be an invalid header or header_union
class Invalid : public Expression {
 public:
    bool operator==(IR::Invalid const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Invalid"_cs; }
    static cstring static_type_name() { return "Invalid"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Invalid(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Invalid(Util::SourceInfo srcInfo, const IR::Type *type) : Expression(srcInfo, type) {
        validate();
    }
    Invalid(const IR::Type *type) : Expression(type) { validate(); }
    Invalid(Util::SourceInfo srcInfo) : Expression(srcInfo) { validate(); }
    Invalid() { validate(); }
    IRNODE_SUBCLASS(Invalid)
    DECLARE_TYPEINFO_WITH_TYPEID(Invalid, NodeKind::Invalid, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
/// An expression that evaluates to an invalid header with the specified type.
class InvalidHeader : public Expression {
 public:
    const IR::Type *headerType = nullptr;
    bool operator==(IR::InvalidHeader const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "InvalidHeader"_cs; }
    static cstring static_type_name() { return "InvalidHeader"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    InvalidHeader(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    InvalidHeader(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Type *headerType)
        : Expression(srcInfo, type), headerType(headerType) {
        validate();
    }
    InvalidHeader(const IR::Type *type, const IR::Type *headerType)
        : Expression(type), headerType(headerType) {
        validate();
    }
    InvalidHeader(Util::SourceInfo srcInfo, const IR::Type *headerType)
        : Expression(srcInfo), headerType(headerType) {
        validate();
    }
    InvalidHeader(const IR::Type *headerType) : headerType(headerType) { validate(); }
    IRNODE_SUBCLASS(InvalidHeader)
    DECLARE_TYPEINFO_WITH_TYPEID(InvalidHeader, NodeKind::InvalidHeader, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
/// An expression that evaluates to an invalid header union with the specified type.
class InvalidHeaderUnion : public Expression {
 public:
    const IR::Type *headerUnionType = nullptr;
    bool operator==(IR::InvalidHeaderUnion const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "InvalidHeaderUnion"_cs; }
    static cstring static_type_name() { return "InvalidHeaderUnion"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    InvalidHeaderUnion(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    InvalidHeaderUnion(Util::SourceInfo srcInfo, const IR::Type *type,
                       const IR::Type *headerUnionType)
        : Expression(srcInfo, type), headerUnionType(headerUnionType) {
        validate();
    }
    InvalidHeaderUnion(const IR::Type *type, const IR::Type *headerUnionType)
        : Expression(type), headerUnionType(headerUnionType) {
        validate();
    }
    InvalidHeaderUnion(Util::SourceInfo srcInfo, const IR::Type *headerUnionType)
        : Expression(srcInfo), headerUnionType(headerUnionType) {
        validate();
    }
    InvalidHeaderUnion(const IR::Type *headerUnionType) : headerUnionType(headerUnionType) {
        validate();
    }
    IRNODE_SUBCLASS(InvalidHeaderUnion)
    DECLARE_TYPEINFO_WITH_TYPEID(InvalidHeaderUnion, NodeKind::InvalidHeaderUnion, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
/// An expression that evaluates to an array
class ArrayExpression : public BaseListExpression {
 public:
    /// May only be known after type checking; so it can be nullptr.
    const IR::Type *arrayType = nullptr;
    void validate() const override;
    bool operator==(IR::ArrayExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "ArrayExpression"_cs; }
    static cstring static_type_name() { return "ArrayExpression"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ArrayExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::BaseListExpression const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ArrayExpression(Util::SourceInfo srcInfo, const IR::Type *type,
                    IR::Vector<IR::Expression> components, const IR::Type *arrayType)
        : BaseListExpression(srcInfo, type, components), arrayType(arrayType) {
        validate();
    }
    ArrayExpression(const IR::Type *type, IR::Vector<IR::Expression> components,
                    const IR::Type *arrayType)
        : BaseListExpression(type, components), arrayType(arrayType) {
        validate();
    }
    ArrayExpression(Util::SourceInfo srcInfo, IR::Vector<IR::Expression> components,
                    const IR::Type *arrayType)
        : BaseListExpression(srcInfo, components), arrayType(arrayType) {
        validate();
    }
    ArrayExpression(IR::Vector<IR::Expression> components, const IR::Type *arrayType)
        : BaseListExpression(components), arrayType(arrayType) {
        validate();
    }
    IRNODE_SUBCLASS(ArrayExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(ArrayExpression, NodeKind::ArrayExpression, BaseListExpression);
};
}  // namespace P4::IR
namespace P4::IR {
/// A ListExpression where all the components are compile-time values.
/// This is used by the evaluator pass.
class ListCompileTimeValue : public Node, public virtual CompileTimeValue {
 public:
    IR::Vector<IR::Node> components;
    void validate() const override;
    bool operator==(IR::ListCompileTimeValue const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "ListCompileTimeValue"_cs; }
    static cstring static_type_name() { return "ListCompileTimeValue"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ListCompileTimeValue(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    ListCompileTimeValue(Util::SourceInfo srcInfo, IR::Vector<IR::Node> components)
        : Node(srcInfo), components(components) {
        validate();
    }
    ListCompileTimeValue(IR::Vector<IR::Node> components) : components(components) { validate(); }
    IRNODE_SUBCLASS(ListCompileTimeValue)
    DECLARE_TYPEINFO_WITH_TYPEID(ListCompileTimeValue, NodeKind::ListCompileTimeValue, Node,
                                 CompileTimeValue);
};
}  // namespace P4::IR
namespace P4::IR {
/// A P4ListExpression where all the components are compile-time values.
/// This is used by the evaluator pass.
class P4ListCompileTimeValue : public Node, public virtual CompileTimeValue {
 public:
    IR::Vector<IR::Node> components;
    void validate() const override;
    bool operator==(IR::P4ListCompileTimeValue const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "P4ListCompileTimeValue"_cs; }
    static cstring static_type_name() { return "P4ListCompileTimeValue"_cs; }
    void toJSON(JSONGenerator &json) const override;
    P4ListCompileTimeValue(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    P4ListCompileTimeValue(Util::SourceInfo srcInfo, IR::Vector<IR::Node> components)
        : Node(srcInfo), components(components) {
        validate();
    }
    P4ListCompileTimeValue(IR::Vector<IR::Node> components) : components(components) { validate(); }
    IRNODE_SUBCLASS(P4ListCompileTimeValue)
    DECLARE_TYPEINFO_WITH_TYPEID(P4ListCompileTimeValue, NodeKind::P4ListCompileTimeValue, Node,
                                 CompileTimeValue);
};
}  // namespace P4::IR
namespace P4::IR {
/// A StructExpression where all the components are compile-time values.
/// This is used by the evaluator pass.
class StructCompileTimeValue : public Node, public virtual CompileTimeValue {
 public:
    IR::Vector<IR::Node> components;
    void validate() const override;
    bool operator==(IR::StructCompileTimeValue const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "StructCompileTimeValue"_cs; }
    static cstring static_type_name() { return "StructCompileTimeValue"_cs; }
    void toJSON(JSONGenerator &json) const override;
    StructCompileTimeValue(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    StructCompileTimeValue(Util::SourceInfo srcInfo, IR::Vector<IR::Node> components)
        : Node(srcInfo), components(components) {
        validate();
    }
    StructCompileTimeValue(IR::Vector<IR::Node> components) : components(components) { validate(); }
    IRNODE_SUBCLASS(StructCompileTimeValue)
    DECLARE_TYPEINFO_WITH_TYPEID(StructCompileTimeValue, NodeKind::StructCompileTimeValue, Node,
                                 CompileTimeValue);
};
}  // namespace P4::IR
namespace P4::IR {
/// Experimental: an extern methond/function call with constant arguments to be
/// evaluated at compile time
class CompileTimeMethodCall : public MethodCallExpression, public virtual CompileTimeValue {
 public:
    CompileTimeMethodCall(const IR::MethodCallExpression *e) : MethodCallExpression(*e) {}
    void validate() const override;
    bool operator==(IR::CompileTimeMethodCall const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "CompileTimeMethodCall"_cs; }
    static cstring static_type_name() { return "CompileTimeMethodCall"_cs; }
    void toJSON(JSONGenerator &json) const override;
    CompileTimeMethodCall(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::MethodCallExpression const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    CompileTimeMethodCall(Util::SourceInfo srcInfo, const IR::Type *type,
                          const IR::Expression *method, const IR::Vector<IR::Type> *typeArguments,
                          const IR::Vector<IR::Argument> *arguments)
        : MethodCallExpression(srcInfo, type, method, typeArguments, arguments) {
        validate();
    }
    CompileTimeMethodCall(const IR::Type *type, const IR::Expression *method,
                          const IR::Vector<IR::Type> *typeArguments,
                          const IR::Vector<IR::Argument> *arguments)
        : MethodCallExpression(type, method, typeArguments, arguments) {
        validate();
    }
    CompileTimeMethodCall(Util::SourceInfo srcInfo, const IR::Expression *method,
                          const IR::Vector<IR::Type> *typeArguments,
                          const IR::Vector<IR::Argument> *arguments)
        : MethodCallExpression(srcInfo, method, typeArguments, arguments) {
        validate();
    }
    CompileTimeMethodCall(const IR::Expression *method, const IR::Vector<IR::Type> *typeArguments,
                          const IR::Vector<IR::Argument> *arguments)
        : MethodCallExpression(method, typeArguments, arguments) {
        validate();
    }
    CompileTimeMethodCall(Util::SourceInfo srcInfo, const IR::Type *type,
                          const IR::Expression *method, const IR::Vector<IR::Argument> *arguments)
        : MethodCallExpression(srcInfo, type, method, arguments) {
        validate();
    }
    CompileTimeMethodCall(const IR::Type *type, const IR::Expression *method,
                          const IR::Vector<IR::Argument> *arguments)
        : MethodCallExpression(type, method, arguments) {
        validate();
    }
    CompileTimeMethodCall(Util::SourceInfo srcInfo, const IR::Expression *method,
                          const IR::Vector<IR::Argument> *arguments)
        : MethodCallExpression(srcInfo, method, arguments) {
        validate();
    }
    CompileTimeMethodCall(const IR::Expression *method, const IR::Vector<IR::Argument> *arguments)
        : MethodCallExpression(method, arguments) {
        validate();
    }
    CompileTimeMethodCall(Util::SourceInfo srcInfo, const IR::Type *type,
                          const IR::Expression *method, const IR::Vector<IR::Type> *typeArguments)
        : MethodCallExpression(srcInfo, type, method, typeArguments) {
        validate();
    }
    CompileTimeMethodCall(const IR::Type *type, const IR::Expression *method,
                          const IR::Vector<IR::Type> *typeArguments)
        : MethodCallExpression(type, method, typeArguments) {
        validate();
    }
    CompileTimeMethodCall(Util::SourceInfo srcInfo, const IR::Expression *method,
                          const IR::Vector<IR::Type> *typeArguments)
        : MethodCallExpression(srcInfo, method, typeArguments) {
        validate();
    }
    CompileTimeMethodCall(const IR::Expression *method, const IR::Vector<IR::Type> *typeArguments)
        : MethodCallExpression(method, typeArguments) {
        validate();
    }
    CompileTimeMethodCall(Util::SourceInfo srcInfo, const IR::Type *type,
                          const IR::Expression *method)
        : MethodCallExpression(srcInfo, type, method) {
        validate();
    }
    CompileTimeMethodCall(const IR::Type *type, const IR::Expression *method)
        : MethodCallExpression(type, method) {
        validate();
    }
    CompileTimeMethodCall(Util::SourceInfo srcInfo, const IR::Expression *method)
        : MethodCallExpression(srcInfo, method) {
        validate();
    }
    CompileTimeMethodCall(const IR::Expression *method) : MethodCallExpression(method) {
        validate();
    }
    IRNODE_SUBCLASS(CompileTimeMethodCall)
    DECLARE_TYPEINFO_WITH_TYPEID(CompileTimeMethodCall, NodeKind::CompileTimeMethodCall,
                                 MethodCallExpression, CompileTimeValue);
};
}  // namespace P4::IR
namespace P4::IR {
/// Signifies that a particular expression is a symbolic variable with a label.
/// These variables are intended to be consumed by SMT/SAT solvers.
class SymbolicVariable : public Expression {
 public:
    /// The label of the symbolic variable.
    cstring label;
    /// A symbolic variable always has a type and no source info.
    SymbolicVariable(const IR::Type *type, cstring label) : Expression(type), label(label) {}
    /// Implements comparisons so that SymbolicVariables can be used as map keys.
    bool operator<(IR::SymbolicVariable const &other) const { return label < other.label; }
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::SymbolicVariable const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "SymbolicVariable"_cs; }
    static cstring static_type_name() { return "SymbolicVariable"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    SymbolicVariable(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    IRNODE_SUBCLASS(SymbolicVariable)
    DECLARE_TYPEINFO_WITH_TYPEID(SymbolicVariable, NodeKind::SymbolicVariable, Expression);
};
}  // namespace P4::IR

#endif  /* IR_GENERATED_EXPRESSIONS_H_ */
