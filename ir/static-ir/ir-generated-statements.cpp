#include "ir/ir-generated.h"   // IWYU pragma: keep

#include "ir/ir-inline.h"      // IWYU pragma: keep
#include "ir/json_generator.h" // IWYU pragma: keep
#include "ir/json_loader.h"    // IWYU pragma: keep
#include "ir/visitor.h"        // IWYU pragma: keep
#include "lib/algorithm.h"     // IWYU pragma: keep
#include "lib/log.h"           // IWYU pragma: keep

using namespace P4;

// Method definitions for IR statement nodes (and compound *Assign ops).

// Out-of-line apply() overload for the Statement hierarchy. The macro
// expands to a non-virtual templated dispatch helper; it must be defined
// in the same TU that owns the rest of Statement's method bodies.
IRNODE_DEFINE_APPLY_OVERLOAD(Statement, , )

bool IR::Statement::operator==(IR::Statement const &a) const {
    return StatOrDecl::operator==(static_cast<const StatOrDecl &>(a));
}
bool IR::Statement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!StatOrDecl::equiv(a_)) return false;
    return true;
}
void IR::Statement::toJSON(JSONGenerator &json) const { StatOrDecl::toJSON(json); }
IR::Statement::Statement(JSONLoader &json) : StatOrDecl(json) {}
bool IR::Statement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::Statement::operator==(IR::Node const &a) const { return a == *this; }
bool IR::BaseAssignmentStatement::operator==(IR::BaseAssignmentStatement const &a) const {
    return Statement::operator==(static_cast<const Statement &>(a)) && left == a.left &&
           right == a.right;
}
bool IR::BaseAssignmentStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Statement::equiv(a_)) return false;
    auto &a = static_cast<const BaseAssignmentStatement &>(a_);
    return (left ? a.left ? left->equiv(*a.left) : false : a.left == nullptr) &&
           (right ? a.right ? right->equiv(*a.right) : false : a.right == nullptr);
}
void IR::BaseAssignmentStatement::visit_children(Visitor &v, char const *n) {
    (void)n;
    Statement::visit_children(v, n);
    v.visit(left, "left");
    v.visit(right, "right");
}
void IR::BaseAssignmentStatement::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Statement::visit_children(v, n);
    v.visit(left, "left");
    v.visit(right, "right");
}
void IR::BaseAssignmentStatement::validate() const {
    CHECK_NULL(left);
    CHECK_NULL(right);
}
void IR::BaseAssignmentStatement::toJSON(JSONGenerator &json) const {
    Statement::toJSON(json);
    json.emit("left", left);
    json.emit("right", right);
}
IR::BaseAssignmentStatement::BaseAssignmentStatement(JSONLoader &json) : Statement(json) {
    json.load("left", left) || json.error("missing field left");
    json.load("right", right) || json.error("missing field right");
}
bool IR::BaseAssignmentStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::BaseAssignmentStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::BaseAssignmentStatement::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::OpAssignmentStatement::toString() const {
    return absl::StrCat(left, " ", getStringOp(), "= ", right);
}
bool IR::OpAssignmentStatement::operator==(IR::OpAssignmentStatement const &a) const {
    return BaseAssignmentStatement::operator==(static_cast<const BaseAssignmentStatement &>(a));
}
bool IR::OpAssignmentStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!BaseAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::OpAssignmentStatement::toJSON(JSONGenerator &json) const {
    BaseAssignmentStatement::toJSON(json);
}
IR::OpAssignmentStatement::OpAssignmentStatement(JSONLoader &json)
    : BaseAssignmentStatement(json) {}
bool IR::OpAssignmentStatement::operator==(IR::BaseAssignmentStatement const &a) const {
    return a == *this;
}
bool IR::OpAssignmentStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::OpAssignmentStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::OpAssignmentStatement::operator==(IR::Node const &a) const { return a == *this; }
bool IR::MulAssign::operator==(IR::MulAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::MulAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::MulAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::MulAssign::MulAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::MulAssign::fromJSON(JSONLoader &json) { return new MulAssign(json); }
bool IR::MulAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::MulAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::MulAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::MulAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::MulAssign::operator==(IR::Node const &a) const { return a == *this; }
bool IR::DivAssign::operator==(IR::DivAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::DivAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::DivAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::DivAssign::DivAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::DivAssign::fromJSON(JSONLoader &json) { return new DivAssign(json); }
bool IR::DivAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::DivAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::DivAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::DivAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::DivAssign::operator==(IR::Node const &a) const { return a == *this; }
bool IR::ModAssign::operator==(IR::ModAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::ModAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::ModAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::ModAssign::ModAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::ModAssign::fromJSON(JSONLoader &json) { return new ModAssign(json); }
bool IR::ModAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::ModAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::ModAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::ModAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::ModAssign::operator==(IR::Node const &a) const { return a == *this; }
bool IR::AddAssign::operator==(IR::AddAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::AddAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::AddAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::AddAssign::AddAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::AddAssign::fromJSON(JSONLoader &json) { return new AddAssign(json); }
bool IR::AddAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::AddAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::AddAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::AddAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::AddAssign::operator==(IR::Node const &a) const { return a == *this; }
bool IR::SubAssign::operator==(IR::SubAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::SubAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::SubAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::SubAssign::SubAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::SubAssign::fromJSON(JSONLoader &json) { return new SubAssign(json); }
bool IR::SubAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::SubAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::SubAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::SubAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::SubAssign::operator==(IR::Node const &a) const { return a == *this; }
bool IR::AddSatAssign::operator==(IR::AddSatAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::AddSatAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::AddSatAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::AddSatAssign::AddSatAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::AddSatAssign::fromJSON(JSONLoader &json) { return new AddSatAssign(json); }
bool IR::AddSatAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::AddSatAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::AddSatAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::AddSatAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::AddSatAssign::operator==(IR::Node const &a) const { return a == *this; }
bool IR::SubSatAssign::operator==(IR::SubSatAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::SubSatAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::SubSatAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::SubSatAssign::SubSatAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::SubSatAssign::fromJSON(JSONLoader &json) { return new SubSatAssign(json); }
bool IR::SubSatAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::SubSatAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::SubSatAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::SubSatAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::SubSatAssign::operator==(IR::Node const &a) const { return a == *this; }
bool IR::ShlAssign::operator==(IR::ShlAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::ShlAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::ShlAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::ShlAssign::ShlAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::ShlAssign::fromJSON(JSONLoader &json) { return new ShlAssign(json); }
bool IR::ShlAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::ShlAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::ShlAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::ShlAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::ShlAssign::operator==(IR::Node const &a) const { return a == *this; }
bool IR::ShrAssign::operator==(IR::ShrAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::ShrAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::ShrAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::ShrAssign::ShrAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::ShrAssign::fromJSON(JSONLoader &json) { return new ShrAssign(json); }
bool IR::ShrAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::ShrAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::ShrAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::ShrAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::ShrAssign::operator==(IR::Node const &a) const { return a == *this; }
bool IR::BAndAssign::operator==(IR::BAndAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::BAndAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::BAndAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::BAndAssign::BAndAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::BAndAssign::fromJSON(JSONLoader &json) { return new BAndAssign(json); }
bool IR::BAndAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::BAndAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::BAndAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::BAndAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::BAndAssign::operator==(IR::Node const &a) const { return a == *this; }
bool IR::BOrAssign::operator==(IR::BOrAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::BOrAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::BOrAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::BOrAssign::BOrAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::BOrAssign::fromJSON(JSONLoader &json) { return new BOrAssign(json); }
bool IR::BOrAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::BOrAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::BOrAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::BOrAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::BOrAssign::operator==(IR::Node const &a) const { return a == *this; }
bool IR::BXorAssign::operator==(IR::BXorAssign const &a) const {
    return OpAssignmentStatement::operator==(static_cast<const OpAssignmentStatement &>(a));
}
bool IR::BXorAssign::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!OpAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::BXorAssign::toJSON(JSONGenerator &json) const { OpAssignmentStatement::toJSON(json); }
IR::BXorAssign::BXorAssign(JSONLoader &json) : OpAssignmentStatement(json) {}
IR::Node *IR::BXorAssign::fromJSON(JSONLoader &json) { return new BXorAssign(json); }
bool IR::BXorAssign::operator==(IR::OpAssignmentStatement const &a) const { return a == *this; }
bool IR::BXorAssign::operator==(IR::BaseAssignmentStatement const &a) const { return a == *this; }
bool IR::BXorAssign::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::BXorAssign::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::BXorAssign::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::ExitStatement::toString() const { return "exit"_cs; }
void IR::ExitStatement::dbprint(std::ostream &out) const { out << "exit"; }
bool IR::ExitStatement::operator==(IR::ExitStatement const &a) const {
    return Statement::operator==(static_cast<const Statement &>(a));
}
bool IR::ExitStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Statement::equiv(a_)) return false;
    return true;
}
void IR::ExitStatement::toJSON(JSONGenerator &json) const { Statement::toJSON(json); }
IR::ExitStatement::ExitStatement(JSONLoader &json) : Statement(json) {}
IR::Node *IR::ExitStatement::fromJSON(JSONLoader &json) { return new ExitStatement(json); }
bool IR::ExitStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::ExitStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::ExitStatement::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::ReturnStatement::toString() const {
    return absl::StrCat("return ", (expression ? expression->toString() : ""_cs));
}
bool IR::ReturnStatement::operator==(IR::ReturnStatement const &a) const {
    return Statement::operator==(static_cast<const Statement &>(a)) && expression == a.expression;
}
bool IR::ReturnStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Statement::equiv(a_)) return false;
    auto &a = static_cast<const ReturnStatement &>(a_);
    return (expression ? a.expression ? expression->equiv(*a.expression) : false
                       : a.expression == nullptr);
}
void IR::ReturnStatement::visit_children(Visitor &v, char const *n) {
    (void)n;
    Statement::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::ReturnStatement::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Statement::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::ReturnStatement::toJSON(JSONGenerator &json) const {
    Statement::toJSON(json);
    if (expression != nullptr) json.emit("expression", expression);
}
IR::ReturnStatement::ReturnStatement(JSONLoader &json) : Statement(json) {
    json.load("expression", expression);
}
IR::Node *IR::ReturnStatement::fromJSON(JSONLoader &json) { return new ReturnStatement(json); }
bool IR::ReturnStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::ReturnStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::ReturnStatement::operator==(IR::Node const &a) const { return a == *this; }
void IR::EmptyStatement::dbprint(std::ostream &out) const { out << ""; }
bool IR::EmptyStatement::operator==(IR::EmptyStatement const &a) const {
    return Statement::operator==(static_cast<const Statement &>(a));
}
bool IR::EmptyStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Statement::equiv(a_)) return false;
    return true;
}
void IR::EmptyStatement::toJSON(JSONGenerator &json) const { Statement::toJSON(json); }
IR::EmptyStatement::EmptyStatement(JSONLoader &json) : Statement(json) {}
IR::Node *IR::EmptyStatement::fromJSON(JSONLoader &json) { return new EmptyStatement(json); }
bool IR::EmptyStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::EmptyStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::EmptyStatement::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::AssignmentStatement::toString() const { return absl::StrCat(left, " = ", right); }
bool IR::AssignmentStatement::operator==(IR::AssignmentStatement const &a) const {
    return BaseAssignmentStatement::operator==(static_cast<const BaseAssignmentStatement &>(a));
}
bool IR::AssignmentStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!BaseAssignmentStatement::equiv(a_)) return false;
    return true;
}
void IR::AssignmentStatement::toJSON(JSONGenerator &json) const {
    BaseAssignmentStatement::toJSON(json);
}
IR::AssignmentStatement::AssignmentStatement(JSONLoader &json) : BaseAssignmentStatement(json) {}
IR::Node *IR::AssignmentStatement::fromJSON(JSONLoader &json) {
    return new AssignmentStatement(json);
}
bool IR::AssignmentStatement::operator==(IR::BaseAssignmentStatement const &a) const {
    return a == *this;
}
bool IR::AssignmentStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::AssignmentStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::AssignmentStatement::operator==(IR::Node const &a) const { return a == *this; }
void IR::IfStatement::visit_children(Visitor &v, char const *n) {
    (void)n;
    v.visit(condition, "condition");
    SplitFlowVisit<Statement>(v, ifTrue, ifFalse).run_visit();
}
void IR::IfStatement::visit_children(Visitor &v, char const *n) const {
    (void)n;
    v.visit(condition, "condition");
    SplitFlowVisit<Statement>(v, ifTrue, ifFalse).run_visit();
}
bool IR::IfStatement::operator==(IR::IfStatement const &a) const {
    return Statement::operator==(static_cast<const Statement &>(a)) && condition == a.condition &&
           ifTrue == a.ifTrue && ifFalse == a.ifFalse;
}
bool IR::IfStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Statement::equiv(a_)) return false;
    auto &a = static_cast<const IfStatement &>(a_);
    return (condition ? a.condition ? condition->equiv(*a.condition) : false
                      : a.condition == nullptr) &&
           (ifTrue ? a.ifTrue ? ifTrue->equiv(*a.ifTrue) : false : a.ifTrue == nullptr) &&
           (ifFalse ? a.ifFalse ? ifFalse->equiv(*a.ifFalse) : false : a.ifFalse == nullptr);
}
void IR::IfStatement::validate() const {
    CHECK_NULL(condition);
    CHECK_NULL(ifTrue);
}
void IR::IfStatement::toJSON(JSONGenerator &json) const {
    Statement::toJSON(json);
    json.emit("condition", condition);
    json.emit("ifTrue", ifTrue);
    if (ifFalse != nullptr) json.emit("ifFalse", ifFalse);
}
IR::IfStatement::IfStatement(JSONLoader &json) : Statement(json) {
    json.load("condition", condition) || json.error("missing field condition");
    json.load("ifTrue", ifTrue) || json.error("missing field ifTrue");
    json.load("ifFalse", ifFalse);
}
IR::Node *IR::IfStatement::fromJSON(JSONLoader &json) { return new IfStatement(json); }
bool IR::IfStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::IfStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::IfStatement::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::BreakStatement::toString() const { return "break"_cs; }
void IR::BreakStatement::dbprint(std::ostream &out) const { out << "break"; }

bool IR::BreakStatement::operator==(IR::BreakStatement const &a) const {
    return Statement::operator==(static_cast<const Statement &>(a));
}
bool IR::BreakStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Statement::equiv(a_)) return false;
    return true;
}
void IR::BreakStatement::toJSON(JSONGenerator &json) const { Statement::toJSON(json); }
IR::BreakStatement::BreakStatement(JSONLoader &json) : Statement(json) {}
IR::Node *IR::BreakStatement::fromJSON(JSONLoader &json) { return new BreakStatement(json); }
bool IR::BreakStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::BreakStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::BreakStatement::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::ContinueStatement::toString() const { return "continue"_cs; }
void IR::ContinueStatement::dbprint(std::ostream &out) const { out << "continue"; }

bool IR::ContinueStatement::operator==(IR::ContinueStatement const &a) const {
    return Statement::operator==(static_cast<const Statement &>(a));
}
bool IR::ContinueStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Statement::equiv(a_)) return false;
    return true;
}
void IR::ContinueStatement::toJSON(JSONGenerator &json) const { Statement::toJSON(json); }
IR::ContinueStatement::ContinueStatement(JSONLoader &json) : Statement(json) {}
IR::Node *IR::ContinueStatement::fromJSON(JSONLoader &json) { return new ContinueStatement(json); }
bool IR::ContinueStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::ContinueStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::ContinueStatement::operator==(IR::Node const &a) const { return a == *this; }
const IR::IDeclaration *IR::BlockStatement::getDeclByName(cstring name) const {
    return components.getDeclaration(name);
}
const IR::IDeclaration *IR::BlockStatement::getDeclByName(std::string_view name) const {
    return components.getDeclaration(name);
}
Util::Enumerator<const IR::IDeclaration *> *IR::BlockStatement::getDeclarations() const {
    return components.getDeclarations();
}
void IR::BlockStatement::push_back(const IR::StatOrDecl *st) { components.push_back(st); }
IR::Vector<IR::Annotation> const &IR::BlockStatement::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::BlockStatement::getAnnotations() { return annotations; }
bool IR::BlockStatement::operator==(IR::BlockStatement const &a) const {
    return Statement::operator==(static_cast<const Statement &>(a)) &&
           annotations == a.annotations && components == a.components;
}
bool IR::BlockStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Statement::equiv(a_)) return false;
    auto &a = static_cast<const BlockStatement &>(a_);
    return annotations.equiv(a.annotations) && components.equiv(a.components);
}
void IR::BlockStatement::visit_children(Visitor &v, char const *n) {
    (void)n;
    Statement::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    components.visit_children(v, "components");
}
void IR::BlockStatement::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Statement::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    components.visit_children(v, "components");
}
void IR::BlockStatement::validate() const {
    annotations.validate();
    components.validate();
}
void IR::BlockStatement::toJSON(JSONGenerator &json) const {
    Statement::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("components", components);
}
IR::BlockStatement::BlockStatement(JSONLoader &json) : Statement(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("components", components) || json.error("missing field components");
}
IR::Node *IR::BlockStatement::fromJSON(JSONLoader &json) { return new BlockStatement(json); }
bool IR::BlockStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::BlockStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::BlockStatement::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::MethodCallStatement::toString() const { return methodCall->toString(); }
bool IR::MethodCallStatement::operator==(IR::MethodCallStatement const &a) const {
    return Statement::operator==(static_cast<const Statement &>(a)) && methodCall == a.methodCall;
}
bool IR::MethodCallStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Statement::equiv(a_)) return false;
    auto &a = static_cast<const MethodCallStatement &>(a_);
    return (methodCall ? a.methodCall ? methodCall->equiv(*a.methodCall) : false
                       : a.methodCall == nullptr);
}
void IR::MethodCallStatement::visit_children(Visitor &v, char const *n) {
    (void)n;
    Statement::visit_children(v, n);
    v.visit(methodCall, "methodCall");
}
void IR::MethodCallStatement::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Statement::visit_children(v, n);
    v.visit(methodCall, "methodCall");
}
void IR::MethodCallStatement::validate() const { CHECK_NULL(methodCall); }
void IR::MethodCallStatement::toJSON(JSONGenerator &json) const {
    Statement::toJSON(json);
    json.emit("methodCall", methodCall);
}
IR::MethodCallStatement::MethodCallStatement(JSONLoader &json) : Statement(json) {
    json.load("methodCall", methodCall) || json.error("missing field methodCall");
}
IR::Node *IR::MethodCallStatement::fromJSON(JSONLoader &json) {
    return new MethodCallStatement(json);
}
bool IR::MethodCallStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::MethodCallStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::MethodCallStatement::operator==(IR::Node const &a) const { return a == *this; }
void IR::SwitchCase::validate() const {
    CHECK_NULL(label);
    {
        BUG_CHECK(statement == nullptr || statement->is<IR::BlockStatement>(),
                  "%1%: Expected a block statement", statement);
    }
}
bool IR::SwitchCase::operator==(IR::SwitchCase const &a) const {
    return this->typeId() == a.typeId() && label == a.label && statement == a.statement;
}
bool IR::SwitchCase::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const SwitchCase &>(a_);
    return (label ? a.label ? label->equiv(*a.label) : false : a.label == nullptr) &&
           (statement ? a.statement ? statement->equiv(*a.statement) : false
                      : a.statement == nullptr);
}
void IR::SwitchCase::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    v.visit(label, "label");
    v.visit(statement, "statement");
}
void IR::SwitchCase::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    v.visit(label, "label");
    v.visit(statement, "statement");
}
void IR::SwitchCase::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("label", label);
    if (statement != nullptr) json.emit("statement", statement);
}
IR::SwitchCase::SwitchCase(JSONLoader &json) : Node(json) {
    json.load("label", label) || json.error("missing field label");
    json.load("statement", statement);
}
IR::Node *IR::SwitchCase::fromJSON(JSONLoader &json) { return new SwitchCase(json); }
bool IR::SwitchCase::operator==(IR::Node const &a) const { return a == *this; }
void IR::SwitchStatement::visit_children(Visitor &v, char const *n) {
    (void)n;
    v.visit(expression, "expression");
    SplitFlowVisit<SwitchCase> split(v);
    for (auto &c : cases) split.addNode(c);
    split.run_visit();
}
void IR::SwitchStatement::visit_children(Visitor &v, char const *n) const {
    (void)n;
    v.visit(expression, "expression");
    SplitFlowVisit<SwitchCase> split(v);
    for (auto &c : cases) split.addNode(c);
    split.run_visit();
}
bool IR::SwitchStatement::operator==(IR::SwitchStatement const &a) const {
    return Statement::operator==(static_cast<const Statement &>(a)) && expression == a.expression &&
           cases == a.cases;
}
bool IR::SwitchStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Statement::equiv(a_)) return false;
    auto &a = static_cast<const SwitchStatement &>(a_);
    return (expression ? a.expression ? expression->equiv(*a.expression) : false
                       : a.expression == nullptr) &&
           cases.equiv(a.cases);
}
void IR::SwitchStatement::validate() const {
    CHECK_NULL(expression);
    cases.validate();
}
void IR::SwitchStatement::toJSON(JSONGenerator &json) const {
    Statement::toJSON(json);
    json.emit("expression", expression);
    json.emit("cases", cases);
}
IR::SwitchStatement::SwitchStatement(JSONLoader &json) : Statement(json) {
    json.load("expression", expression) || json.error("missing field expression");
    json.load("cases", cases) || json.error("missing field cases");
}
IR::Node *IR::SwitchStatement::fromJSON(JSONLoader &json) { return new SwitchStatement(json); }
bool IR::SwitchStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::SwitchStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::SwitchStatement::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::LoopStatement::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::LoopStatement::getAnnotations() { return annotations; }
bool IR::LoopStatement::operator==(IR::LoopStatement const &a) const {
    return Statement::operator==(static_cast<const Statement &>(a)) && annotations == a.annotations;
}
bool IR::LoopStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Statement::equiv(a_)) return false;
    auto &a = static_cast<const LoopStatement &>(a_);
    return annotations.equiv(a.annotations);
}
void IR::LoopStatement::visit_children(Visitor &v, char const *n) {
    (void)n;
    Statement::visit_children(v, n);
    annotations.visit_children(v, "annotations");
}
void IR::LoopStatement::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Statement::visit_children(v, n);
    annotations.visit_children(v, "annotations");
}
void IR::LoopStatement::validate() const { annotations.validate(); }
void IR::LoopStatement::toJSON(JSONGenerator &json) const {
    Statement::toJSON(json);
    json.emit("annotations", annotations);
}
IR::LoopStatement::LoopStatement(JSONLoader &json) : Statement(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
}
bool IR::LoopStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::LoopStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::LoopStatement::operator==(IR::Node const &a) const { return a == *this; }
const IR::IDeclaration *IR::ForStatement::getDeclByName(cstring name) const {
    return init.getDeclaration(name);
}
const IR::IDeclaration *IR::ForStatement::getDeclByName(std::string_view name) const {
    return init.getDeclaration(name);
}
Util::Enumerator<const IR::IDeclaration *> *IR::ForStatement::getDeclarations() const {
    return init.getDeclarations();
}
bool IR::ForStatement::operator==(IR::ForStatement const &a) const {
    return LoopStatement::operator==(static_cast<const LoopStatement &>(a)) && init == a.init &&
           condition == a.condition && updates == a.updates && body == a.body;
}
bool IR::ForStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!LoopStatement::equiv(a_)) return false;
    auto &a = static_cast<const ForStatement &>(a_);
    return init.equiv(a.init) &&
           (condition ? a.condition ? condition->equiv(*a.condition) : false
                      : a.condition == nullptr) &&
           updates.equiv(a.updates) &&
           (body ? a.body ? body->equiv(*a.body) : false : a.body == nullptr);
}
void IR::ForStatement::validate() const {
    init.validate();
    CHECK_NULL(condition);
    updates.validate();
    CHECK_NULL(body);
}
void IR::ForStatement::toJSON(JSONGenerator &json) const {
    LoopStatement::toJSON(json);
    json.emit("init", init);
    json.emit("condition", condition);
    json.emit("updates", updates);
    json.emit("body", body);
}
IR::ForStatement::ForStatement(JSONLoader &json) : LoopStatement(json) {
    json.load("init", init) || json.error("missing field init");
    json.load("condition", condition) || json.error("missing field condition");
    json.load("updates", updates) || json.error("missing field updates");
    json.load("body", body) || json.error("missing field body");
}
IR::Node *IR::ForStatement::fromJSON(JSONLoader &json) { return new ForStatement(json); }
bool IR::ForStatement::operator==(IR::LoopStatement const &a) const { return a == *this; }
bool IR::ForStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::ForStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::ForStatement::operator==(IR::Node const &a) const { return a == *this; }
IR::ForInStatement::ForInStatement(Util::SourceInfo si, const IR::Vector<IR::Annotation> *a,
                                   const IR::PathExpression *pe, const IR::Expression *c,
                                   const IR::Statement *b)
    : LoopStatement(si, *a), decl(nullptr), ref(pe), collection(c), body(b) {}
// The four constructors below are declared in ir-generated-statements.h but
// defined here so their bodies can dereference Declaration_Variable, whose
// full definition only becomes visible once ir-generated-declarations.h has
// been included by the umbrella header.
IR::ForInStatement::ForInStatement(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations,
                                   const IR::Declaration_Variable *decl,
                                   const IR::Expression *collection, const IR::Statement *body)
    : LoopStatement(srcInfo, annotations),
      decl(decl), collection(collection), body(body) {
    ref = new PathExpression(decl->name);
    validate();
}
IR::ForInStatement::ForInStatement(IR::Vector<IR::Annotation> annotations,
                                   const IR::Declaration_Variable *decl,
                                   const IR::Expression *collection, const IR::Statement *body)
    : LoopStatement(annotations), decl(decl), collection(collection), body(body) {
    ref = new PathExpression(decl->name);
    validate();
}
IR::ForInStatement::ForInStatement(Util::SourceInfo srcInfo, const IR::Declaration_Variable *decl,
                                   const IR::Expression *collection, const IR::Statement *body)
    : LoopStatement(srcInfo), decl(decl), collection(collection), body(body) {
    ref = new PathExpression(decl->name);
    validate();
}
IR::ForInStatement::ForInStatement(const IR::Declaration_Variable *decl,
                                   const IR::Expression *collection, const IR::Statement *body)
    : decl(decl), collection(collection), body(body) {
    ref = new PathExpression(decl->name);
    validate();
}
const IR::IDeclaration *IR::ForInStatement::getDeclByName(cstring name) const {
    return decl && decl->name == name ? decl : nullptr;
}
const IR::IDeclaration *IR::ForInStatement::getDeclByName(std::string_view name) const {
    return decl && decl->name.name == name ? decl : nullptr;
}
Util::Enumerator<const IR::IDeclaration *> *IR::ForInStatement::getDeclarations() const {
    if (decl) return new Util::SingleEnumerator<const IDeclaration *>(decl);
    return new Util::EmptyEnumerator<const IDeclaration *>();
}
bool IR::ForInStatement::operator==(IR::ForInStatement const &a) const {
    return LoopStatement::operator==(static_cast<const LoopStatement &>(a)) && decl == a.decl &&
           ref == a.ref && collection == a.collection && body == a.body;
}
bool IR::ForInStatement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!LoopStatement::equiv(a_)) return false;
    auto &a = static_cast<const ForInStatement &>(a_);
    return (decl ? a.decl ? decl->equiv(*a.decl) : false : a.decl == nullptr) &&
           (ref ? a.ref ? ref->equiv(*a.ref) : false : a.ref == nullptr) &&
           (collection ? a.collection ? collection->equiv(*a.collection) : false
                       : a.collection == nullptr) &&
           (body ? a.body ? body->equiv(*a.body) : false : a.body == nullptr);
}
void IR::ForInStatement::validate() const {
    CHECK_NULL(ref);
    CHECK_NULL(collection);
    CHECK_NULL(body);
}
void IR::ForInStatement::toJSON(JSONGenerator &json) const {
    LoopStatement::toJSON(json);
    if (decl != nullptr) json.emit("decl", decl);
    json.emit("ref", ref);
    json.emit("collection", collection);
    json.emit("body", body);
}
IR::ForInStatement::ForInStatement(JSONLoader &json) : LoopStatement(json) {
    json.load("decl", decl);
    json.load("ref", ref) || json.error("missing field ref");
    json.load("collection", collection) || json.error("missing field collection");
    json.load("body", body) || json.error("missing field body");
}
IR::Node *IR::ForInStatement::fromJSON(JSONLoader &json) { return new ForInStatement(json); }
bool IR::ForInStatement::operator==(IR::LoopStatement const &a) const { return a == *this; }
bool IR::ForInStatement::operator==(IR::Statement const &a) const { return a == *this; }
bool IR::ForInStatement::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::ForInStatement::operator==(IR::Node const &a) const { return a == *this; }
