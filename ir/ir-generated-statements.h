#ifndef IR_GENERATED_STATEMENTS_H_
#define IR_GENERATED_STATEMENTS_H_

// IR statement nodes: Statement / BaseAssignmentStatement / OpAssignmentStatement
// roots, every *Assign compound assignment (which references the matching binop
// from ir-generated-expressions.h), plus AssignmentStatement / IfStatement /
// BlockStatement / SwitchStatement / loop and control-flow statements.

#include "ir/ir-generated-expressions.h"

namespace P4::IR {
///////////////////////////// Statements //////////////////////////
class Statement : public StatOrDecl {
 public:
    IRNODE_DECLARE_APPLY_OVERLOAD(Statement)
    bool operator==(IR::Statement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Statement"_cs; }
    static cstring static_type_name() { return "Statement"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Statement(JSONLoader &json);
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Statement(Util::SourceInfo srcInfo) : StatOrDecl(srcInfo) { validate(); }
    Statement() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Statement)
    DECLARE_TYPEINFO_WITH_TYPEID(Statement, NodeKind::Statement, StatOrDecl);
};
}  // namespace P4::IR
namespace P4::IR {
class BaseAssignmentStatement : public Statement {
 public:
    const IR::Expression *left = nullptr;
    const IR::Expression *right = nullptr;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "BaseAssignmentStatement"_cs; }
    static cstring static_type_name() { return "BaseAssignmentStatement"_cs; }
    void toJSON(JSONGenerator &json) const override;
    BaseAssignmentStatement(JSONLoader &json);
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    BaseAssignmentStatement(Util::SourceInfo srcInfo, const IR::Expression *left,
                            const IR::Expression *right)
        : Statement(srcInfo), left(left), right(right) {
        validate();
    }
    BaseAssignmentStatement(const IR::Expression *left, const IR::Expression *right)
        : left(left), right(right) {
        validate();
    }
    IRNODE_ABSTRACT_SUBCLASS(BaseAssignmentStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(BaseAssignmentStatement, NodeKind::BaseAssignmentStatement,
                                 Statement);
};
}  // namespace P4::IR
namespace P4::IR {
class OpAssignmentStatement : public BaseAssignmentStatement {
 public:
    virtual cstring getStringOp() const = 0;
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "OpAssignmentStatement"_cs; }
    static cstring static_type_name() { return "OpAssignmentStatement"_cs; }
    void toJSON(JSONGenerator &json) const override;
    OpAssignmentStatement(JSONLoader &json);
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    OpAssignmentStatement(Util::SourceInfo srcInfo, const IR::Expression *left,
                          const IR::Expression *right)
        : BaseAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    OpAssignmentStatement(const IR::Expression *left, const IR::Expression *right)
        : BaseAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_ABSTRACT_SUBCLASS(OpAssignmentStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(OpAssignmentStatement, NodeKind::OpAssignmentStatement,
                                 BaseAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class MulAssign : public OpAssignmentStatement {
 public:
    typedef Mul BinOp;
    cstring getStringOp() const override { return cstring("*"); }
    bool operator==(IR::MulAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "MulAssign"_cs; }
    static cstring static_type_name() { return "MulAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    MulAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    MulAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    MulAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(MulAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(MulAssign, NodeKind::MulAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class DivAssign : public OpAssignmentStatement {
 public:
    typedef Div BinOp;
    cstring getStringOp() const override { return cstring("/"); }
    bool operator==(IR::DivAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "DivAssign"_cs; }
    static cstring static_type_name() { return "DivAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    DivAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    DivAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    DivAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(DivAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(DivAssign, NodeKind::DivAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class ModAssign : public OpAssignmentStatement {
 public:
    typedef Mod BinOp;
    cstring getStringOp() const override { return cstring("%"); }
    bool operator==(IR::ModAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "ModAssign"_cs; }
    static cstring static_type_name() { return "ModAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ModAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ModAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    ModAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(ModAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(ModAssign, NodeKind::ModAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class AddAssign : public OpAssignmentStatement {
 public:
    typedef Add BinOp;
    cstring getStringOp() const override { return cstring("+"); }
    bool operator==(IR::AddAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "AddAssign"_cs; }
    static cstring static_type_name() { return "AddAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    AddAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    AddAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    AddAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(AddAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(AddAssign, NodeKind::AddAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class SubAssign : public OpAssignmentStatement {
 public:
    typedef Sub BinOp;
    cstring getStringOp() const override { return cstring("-"); }
    bool operator==(IR::SubAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "SubAssign"_cs; }
    static cstring static_type_name() { return "SubAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    SubAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    SubAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    SubAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(SubAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(SubAssign, NodeKind::SubAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class AddSatAssign : public OpAssignmentStatement {
 public:
    typedef AddSat BinOp;
    cstring getStringOp() const override { return cstring("|+|"); }
    bool operator==(IR::AddSatAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "AddSatAssign"_cs; }
    static cstring static_type_name() { return "AddSatAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    AddSatAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    AddSatAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    AddSatAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(AddSatAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(AddSatAssign, NodeKind::AddSatAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class SubSatAssign : public OpAssignmentStatement {
 public:
    typedef SubSat BinOp;
    cstring getStringOp() const override { return cstring("|-|"); }
    bool operator==(IR::SubSatAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "SubSatAssign"_cs; }
    static cstring static_type_name() { return "SubSatAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    SubSatAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    SubSatAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    SubSatAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(SubSatAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(SubSatAssign, NodeKind::SubSatAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class ShlAssign : public OpAssignmentStatement {
 public:
    typedef Shl BinOp;
    cstring getStringOp() const override { return cstring("<<"); }
    bool operator==(IR::ShlAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "ShlAssign"_cs; }
    static cstring static_type_name() { return "ShlAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ShlAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ShlAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    ShlAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(ShlAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(ShlAssign, NodeKind::ShlAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class ShrAssign : public OpAssignmentStatement {
 public:
    typedef Shr BinOp;
    cstring getStringOp() const override { return cstring(">>"); }
    bool operator==(IR::ShrAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "ShrAssign"_cs; }
    static cstring static_type_name() { return "ShrAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ShrAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ShrAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    ShrAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(ShrAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(ShrAssign, NodeKind::ShrAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class BAndAssign : public OpAssignmentStatement {
 public:
    typedef BAnd BinOp;
    cstring getStringOp() const override { return cstring("&"); }
    bool operator==(IR::BAndAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "BAndAssign"_cs; }
    static cstring static_type_name() { return "BAndAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    BAndAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    BAndAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    BAndAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(BAndAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(BAndAssign, NodeKind::BAndAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class BOrAssign : public OpAssignmentStatement {
 public:
    typedef BOr BinOp;
    cstring getStringOp() const override { return cstring("|"); }
    bool operator==(IR::BOrAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "BOrAssign"_cs; }
    static cstring static_type_name() { return "BOrAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    BOrAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    BOrAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    BOrAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(BOrAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(BOrAssign, NodeKind::BOrAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class BXorAssign : public OpAssignmentStatement {
 public:
    typedef BXor BinOp;
    cstring getStringOp() const override { return cstring("^"); }
    bool operator==(IR::BXorAssign const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "BXorAssign"_cs; }
    static cstring static_type_name() { return "BXorAssign"_cs; }
    void toJSON(JSONGenerator &json) const override;
    BXorAssign(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::OpAssignmentStatement const &a) const override;
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    BXorAssign(Util::SourceInfo srcInfo, const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    BXorAssign(const IR::Expression *left, const IR::Expression *right)
        : OpAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(BXorAssign)
    DECLARE_TYPEINFO_WITH_TYPEID(BXorAssign, NodeKind::BXorAssign, OpAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class ExitStatement : public Statement {
 public:
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::ExitStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "ExitStatement"_cs; }
    static cstring static_type_name() { return "ExitStatement"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ExitStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ExitStatement(Util::SourceInfo srcInfo) : Statement(srcInfo) { validate(); }
    ExitStatement() { validate(); }
    IRNODE_SUBCLASS(ExitStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(ExitStatement, NodeKind::ExitStatement, Statement);
};
}  // namespace P4::IR
namespace P4::IR {
class ReturnStatement : public Statement {
 public:
    const IR::Expression *expression = nullptr;
    cstring toString() const override;
    bool operator==(IR::ReturnStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "ReturnStatement"_cs; }
    static cstring static_type_name() { return "ReturnStatement"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ReturnStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ReturnStatement(Util::SourceInfo srcInfo, const IR::Expression *expression)
        : Statement(srcInfo), expression(expression) {
        validate();
    }
    ReturnStatement(const IR::Expression *expression) : expression(expression) { validate(); }
    IRNODE_SUBCLASS(ReturnStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(ReturnStatement, NodeKind::ReturnStatement, Statement);
};
}  // namespace P4::IR
namespace P4::IR {
class EmptyStatement : public Statement {
 public:
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::EmptyStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "EmptyStatement"_cs; }
    static cstring static_type_name() { return "EmptyStatement"_cs; }
    void toJSON(JSONGenerator &json) const override;
    EmptyStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    EmptyStatement(Util::SourceInfo srcInfo) : Statement(srcInfo) { validate(); }
    EmptyStatement() { validate(); }
    IRNODE_SUBCLASS(EmptyStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(EmptyStatement, NodeKind::EmptyStatement, Statement);
};
}  // namespace P4::IR
namespace P4::IR {
class AssignmentStatement : public BaseAssignmentStatement {
 public:
    cstring toString() const override;
    bool operator==(IR::AssignmentStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "AssignmentStatement"_cs; }
    static cstring static_type_name() { return "AssignmentStatement"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    AssignmentStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::BaseAssignmentStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    AssignmentStatement(Util::SourceInfo srcInfo, const IR::Expression *left,
                        const IR::Expression *right)
        : BaseAssignmentStatement(srcInfo, left, right) {
        validate();
    }
    AssignmentStatement(const IR::Expression *left, const IR::Expression *right)
        : BaseAssignmentStatement(left, right) {
        validate();
    }
    IRNODE_SUBCLASS(AssignmentStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(AssignmentStatement, NodeKind::AssignmentStatement,
                                 BaseAssignmentStatement);
};
}  // namespace P4::IR
namespace P4::IR {
class IfStatement : public Statement {
 public:
    const IR::Expression *condition = nullptr;
    const IR::Statement *ifTrue = nullptr;
    const IR::Statement *ifFalse = nullptr;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    bool operator==(IR::IfStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void validate() const override;
    cstring node_type_name() const override { return "IfStatement"_cs; }
    static cstring static_type_name() { return "IfStatement"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    IfStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    IfStatement(Util::SourceInfo srcInfo, const IR::Expression *condition,
                const IR::Statement *ifTrue, const IR::Statement *ifFalse)
        : Statement(srcInfo), condition(condition), ifTrue(ifTrue), ifFalse(ifFalse) {
        validate();
    }
    IfStatement(const IR::Expression *condition, const IR::Statement *ifTrue,
                const IR::Statement *ifFalse)
        : condition(condition), ifTrue(ifTrue), ifFalse(ifFalse) {
        validate();
    }
    IRNODE_SUBCLASS(IfStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(IfStatement, NodeKind::IfStatement, Statement);
};
}  // namespace P4::IR
namespace P4::IR {
class BreakStatement : public Statement {
 public:
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;

    bool operator==(IR::BreakStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "BreakStatement"_cs; }
    static cstring static_type_name() { return "BreakStatement"_cs; }
    void toJSON(JSONGenerator &json) const override;
    BreakStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    BreakStatement(Util::SourceInfo srcInfo) : Statement(srcInfo) { validate(); }
    BreakStatement() { validate(); }
    IRNODE_SUBCLASS(BreakStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(BreakStatement, NodeKind::BreakStatement, Statement);
};
}  // namespace P4::IR
namespace P4::IR {
class ContinueStatement : public Statement {
 public:
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;

    bool operator==(IR::ContinueStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "ContinueStatement"_cs; }
    static cstring static_type_name() { return "ContinueStatement"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ContinueStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ContinueStatement(Util::SourceInfo srcInfo) : Statement(srcInfo) { validate(); }
    ContinueStatement() { validate(); }
    IRNODE_SUBCLASS(ContinueStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(ContinueStatement, NodeKind::ContinueStatement, Statement);
};
}  // namespace P4::IR
namespace P4::IR {
class BlockStatement : public Statement,
                       public virtual ISimpleNamespace,
                       public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    IR::IndexedVector<IR::StatOrDecl> components;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    void push_back(const IR::StatOrDecl *st);
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    bool empty() const { return components.empty(); }
    void append(const IR::StatOrDecl *stmt);
    BlockStatement(std::initializer_list<const IR::StatOrDecl *> il) {
        for (auto el : il) append(el);
    }
    bool operator==(IR::BlockStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "BlockStatement"_cs; }
    static cstring static_type_name() { return "BlockStatement"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    BlockStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    BlockStatement(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations,
                   IR::IndexedVector<IR::StatOrDecl> components)
        : Statement(srcInfo), annotations(annotations), components(components) {
        validate();
    }
    BlockStatement(IR::Vector<IR::Annotation> annotations,
                   IR::IndexedVector<IR::StatOrDecl> components)
        : annotations(annotations), components(components) {
        validate();
    }
    BlockStatement(Util::SourceInfo srcInfo, IR::IndexedVector<IR::StatOrDecl> components)
        : Statement(srcInfo), components(components) {
        validate();
    }
    BlockStatement(IR::IndexedVector<IR::StatOrDecl> components) : components(components) {
        validate();
    }
    BlockStatement(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Statement(srcInfo), annotations(annotations) {
        validate();
    }
    BlockStatement(IR::Vector<IR::Annotation> annotations) : annotations(annotations) {
        validate();
    }
    BlockStatement(Util::SourceInfo srcInfo) : Statement(srcInfo) { validate(); }
    BlockStatement() { validate(); }
    IRNODE_SUBCLASS(BlockStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(BlockStatement, NodeKind::BlockStatement, Statement,
                                 ISimpleNamespace, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class MethodCallStatement : public Statement {
 public:
    const IR::MethodCallExpression *methodCall = nullptr;
    MethodCallStatement(Util::SourceInfo si, IR::ID m,
                        std::initializer_list<const IR::Argument *> const &a)
        : Statement(si), methodCall(new MethodCallExpression(si, m, a)) {}
    MethodCallStatement(Util::SourceInfo si, const IR::Expression *m,
                        std::initializer_list<const IR::Argument *> const &a)
        : Statement(si), methodCall(new MethodCallExpression(si, m, a)) {}
    cstring toString() const override;
    bool operator==(IR::MethodCallStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "MethodCallStatement"_cs; }
    static cstring static_type_name() { return "MethodCallStatement"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    MethodCallStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    MethodCallStatement(Util::SourceInfo srcInfo, const IR::MethodCallExpression *methodCall)
        : Statement(srcInfo), methodCall(methodCall) {
        {
            if (!srcInfo) srcInfo = methodCall->srcInfo;
        }
        validate();
    }
    MethodCallStatement(const IR::MethodCallExpression *methodCall) : methodCall(methodCall) {
        {
            if (!srcInfo) srcInfo = methodCall->srcInfo;
        }
        validate();
    }
    IRNODE_SUBCLASS(MethodCallStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(MethodCallStatement, NodeKind::MethodCallStatement, Statement);
};
}  // namespace P4::IR
namespace P4::IR {
class SwitchCase : public Node {
 public:
    const IR::Expression *label = nullptr;
    const IR::Statement *statement = nullptr;

    void validate() const override;
    bool operator==(IR::SwitchCase const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "SwitchCase"_cs; }
    static cstring static_type_name() { return "SwitchCase"_cs; }
    void toJSON(JSONGenerator &json) const override;
    SwitchCase(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    SwitchCase(Util::SourceInfo srcInfo, const IR::Expression *label,
               const IR::Statement *statement)
        : Node(srcInfo), label(label), statement(statement) {
        validate();
    }
    SwitchCase(const IR::Expression *label, const IR::Statement *statement)
        : label(label), statement(statement) {
        validate();
    }
    IRNODE_SUBCLASS(SwitchCase)
    DECLARE_TYPEINFO_WITH_TYPEID(SwitchCase, NodeKind::SwitchCase, Node);
};
}  // namespace P4::IR
namespace P4::IR {

class SwitchStatement : public Statement {
 public:
    const IR::Expression *expression = nullptr;
    IR::Vector<IR::SwitchCase> cases;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    bool operator==(IR::SwitchStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void validate() const override;
    cstring node_type_name() const override { return "SwitchStatement"_cs; }
    static cstring static_type_name() { return "SwitchStatement"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    SwitchStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    SwitchStatement(Util::SourceInfo srcInfo, const IR::Expression *expression,
                    IR::Vector<IR::SwitchCase> cases)
        : Statement(srcInfo), expression(expression), cases(cases) {
        validate();
    }
    SwitchStatement(const IR::Expression *expression, IR::Vector<IR::SwitchCase> cases)
        : expression(expression), cases(cases) {
        validate();
    }
    IRNODE_SUBCLASS(SwitchStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(SwitchStatement, NodeKind::SwitchStatement, Statement);
};
}  // namespace P4::IR
namespace P4::IR {

class LoopStatement : public Statement, public virtual ISimpleNamespace, public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    bool operator==(IR::LoopStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "LoopStatement"_cs; }
    static cstring static_type_name() { return "LoopStatement"_cs; }
    void toJSON(JSONGenerator &json) const override;
    LoopStatement(JSONLoader &json);
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    LoopStatement(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Statement(srcInfo), annotations(annotations) {
        validate();
    }
    LoopStatement(IR::Vector<IR::Annotation> annotations) : annotations(annotations) { validate(); }
    LoopStatement(Util::SourceInfo srcInfo) : Statement(srcInfo) { validate(); }
    LoopStatement() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(LoopStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(LoopStatement, NodeKind::LoopStatement, Statement,
                                 ISimpleNamespace, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class ForStatement : public LoopStatement {
 public:
    IR::IndexedVector<IR::StatOrDecl> init;
    const IR::Expression *condition = nullptr;
    IR::IndexedVector<IR::StatOrDecl> updates;
    const IR::Statement *body = nullptr;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    // template single implementation of const vs non-const ForStatement
    template <class THIS>
    static void visit_children(THIS *, Visitor &v);
    bool operator==(IR::ForStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void validate() const override;
    cstring node_type_name() const override { return "ForStatement"_cs; }
    static cstring static_type_name() { return "ForStatement"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ForStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::LoopStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ForStatement(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations,
                 IR::IndexedVector<IR::StatOrDecl> init, const IR::Expression *condition,
                 IR::IndexedVector<IR::StatOrDecl> updates, const IR::Statement *body)
        : LoopStatement(srcInfo, annotations),
          init(init),
          condition(condition),
          updates(updates),
          body(body) {
        validate();
    }
    ForStatement(IR::Vector<IR::Annotation> annotations, IR::IndexedVector<IR::StatOrDecl> init,
                 const IR::Expression *condition, IR::IndexedVector<IR::StatOrDecl> updates,
                 const IR::Statement *body)
        : LoopStatement(annotations),
          init(init),
          condition(condition),
          updates(updates),
          body(body) {
        validate();
    }
    ForStatement(Util::SourceInfo srcInfo, IR::IndexedVector<IR::StatOrDecl> init,
                 const IR::Expression *condition, IR::IndexedVector<IR::StatOrDecl> updates,
                 const IR::Statement *body)
        : LoopStatement(srcInfo), init(init), condition(condition), updates(updates), body(body) {
        validate();
    }
    ForStatement(IR::IndexedVector<IR::StatOrDecl> init, const IR::Expression *condition,
                 IR::IndexedVector<IR::StatOrDecl> updates, const IR::Statement *body)
        : init(init), condition(condition), updates(updates), body(body) {
        validate();
    }
    IRNODE_SUBCLASS(ForStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(ForStatement, NodeKind::ForStatement, LoopStatement);
};
}  // namespace P4::IR
namespace P4::IR {

class ForInStatement : public LoopStatement {
 public:
    const IR::Declaration_Variable *decl = nullptr;

    const IR::PathExpression *ref = nullptr;
    const IR::Expression *collection = nullptr;
    const IR::Statement *body = nullptr;
    ForInStatement(Util::SourceInfo si, const IR::Vector<IR::Annotation> *a,
                   const IR::PathExpression *pe, const IR::Expression *c, const IR::Statement *b);
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    // template single implementation of const vs non-const ForInStatement
    template <class THIS>
    static void visit_children(THIS *, Visitor &v);
    bool operator==(IR::ForInStatement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void validate() const override;
    cstring node_type_name() const override { return "ForInStatement"_cs; }
    static cstring static_type_name() { return "ForInStatement"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ForInStatement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::LoopStatement const &a) const override;
    bool operator==(IR::Statement const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    // These ForInStatement constructors are defined out-of-line in
    // ir-generated-statements.cpp because their bodies dereference
    // Declaration_Variable, whose full definition lives in
    // ir-generated-declarations.h (which is included after this header by
    // the umbrella ir-generated.h).
    ForInStatement(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations,
                   const IR::Declaration_Variable *decl, const IR::Expression *collection,
                   const IR::Statement *body);
    ForInStatement(IR::Vector<IR::Annotation> annotations, const IR::Declaration_Variable *decl,
                   const IR::Expression *collection, const IR::Statement *body);
    ForInStatement(Util::SourceInfo srcInfo, const IR::Declaration_Variable *decl,
                   const IR::Expression *collection, const IR::Statement *body);
    ForInStatement(const IR::Declaration_Variable *decl, const IR::Expression *collection,
                   const IR::Statement *body);
    IRNODE_SUBCLASS(ForInStatement)
    DECLARE_TYPEINFO_WITH_TYPEID(ForInStatement, NodeKind::ForInStatement, LoopStatement);
};
}  // namespace P4::IR

#endif  /* IR_GENERATED_STATEMENTS_H_ */
