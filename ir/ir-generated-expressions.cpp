#include "ir/ir-generated.h"   // IWYU pragma: keep

#include "ir/ir-inline.h"      // IWYU pragma: keep
#include "ir/json_generator.h" // IWYU pragma: keep
#include "ir/json_loader.h"    // IWYU pragma: keep
#include "ir/visitor.h"        // IWYU pragma: keep
#include "lib/algorithm.h"     // IWYU pragma: keep
#include "lib/log.h"           // IWYU pragma: keep

using namespace P4;

// Method definitions for IR expression nodes.

cstring IR::Operation_Unary::toString() const { return getStringOp() + expr->toString(); }
bool IR::Operation_Unary::operator==(IR::Operation_Unary const &a) const {
    return Operation::operator==(static_cast<const Operation &>(a)) && expr == a.expr;
}
bool IR::Operation_Unary::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation::equiv(a_)) return false;
    auto &a = static_cast<const Operation_Unary &>(a_);
    return (expr ? a.expr ? expr->equiv(*a.expr) : false : a.expr == nullptr);
}
void IR::Operation_Unary::visit_children(Visitor &v, char const *n) {
    (void)n;
    Operation::visit_children(v, n);
    v.visit(expr, "expr");
}
void IR::Operation_Unary::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Operation::visit_children(v, n);
    v.visit(expr, "expr");
}
void IR::Operation_Unary::validate() const { CHECK_NULL(expr); }
void IR::Operation_Unary::toJSON(JSONGenerator &json) const {
    Operation::toJSON(json);
    json.emit("expr", expr);
}
IR::Operation_Unary::Operation_Unary(JSONLoader &json) : Operation(json) {
    json.load("expr", expr) || json.error("missing field expr");
}
bool IR::Operation_Unary::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Operation_Unary::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Operation_Unary::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Neg::operator==(IR::Neg const &a) const {
    return Operation_Unary::operator==(static_cast<const Operation_Unary &>(a));
}
bool IR::Neg::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Unary::equiv(a_)) return false;
    return true;
}
void IR::Neg::toJSON(JSONGenerator &json) const { Operation_Unary::toJSON(json); }
IR::Neg::Neg(JSONLoader &json) : Operation_Unary(json) {}
IR::Node *IR::Neg::fromJSON(JSONLoader &json) { return new Neg(json); }
bool IR::Neg::operator==(IR::Operation_Unary const &a) const { return a == *this; }
bool IR::Neg::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Neg::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Neg::operator==(IR::Node const &a) const { return a == *this; }
bool IR::UPlus::operator==(IR::UPlus const &a) const {
    return Operation_Unary::operator==(static_cast<const Operation_Unary &>(a));
}
bool IR::UPlus::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Unary::equiv(a_)) return false;
    return true;
}
void IR::UPlus::toJSON(JSONGenerator &json) const { Operation_Unary::toJSON(json); }
IR::UPlus::UPlus(JSONLoader &json) : Operation_Unary(json) {}
IR::Node *IR::UPlus::fromJSON(JSONLoader &json) { return new UPlus(json); }
bool IR::UPlus::operator==(IR::Operation_Unary const &a) const { return a == *this; }
bool IR::UPlus::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::UPlus::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::UPlus::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Cmpl::operator==(IR::Cmpl const &a) const {
    return Operation_Unary::operator==(static_cast<const Operation_Unary &>(a));
}
bool IR::Cmpl::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Unary::equiv(a_)) return false;
    return true;
}
void IR::Cmpl::toJSON(JSONGenerator &json) const { Operation_Unary::toJSON(json); }
IR::Cmpl::Cmpl(JSONLoader &json) : Operation_Unary(json) {}
IR::Node *IR::Cmpl::fromJSON(JSONLoader &json) { return new Cmpl(json); }
bool IR::Cmpl::operator==(IR::Operation_Unary const &a) const { return a == *this; }
bool IR::Cmpl::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Cmpl::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Cmpl::operator==(IR::Node const &a) const { return a == *this; }
bool IR::LNot::operator==(IR::LNot const &a) const {
    return Operation_Unary::operator==(static_cast<const Operation_Unary &>(a));
}
bool IR::LNot::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Unary::equiv(a_)) return false;
    return true;
}
void IR::LNot::toJSON(JSONGenerator &json) const { Operation_Unary::toJSON(json); }
IR::LNot::LNot(JSONLoader &json) : Operation_Unary(json) {}
IR::Node *IR::LNot::fromJSON(JSONLoader &json) { return new LNot(json); }
bool IR::LNot::operator==(IR::Operation_Unary const &a) const { return a == *this; }
bool IR::LNot::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::LNot::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::LNot::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Operation_Binary::toString() const {
    // FIXME: Do not use debug printing to render user-side strings
    std::stringstream tmp;
    tmp << DBPrint::Prec_Low;
    dbprint(tmp);
    return tmp.str();
}
bool IR::Operation_Binary::operator==(IR::Operation_Binary const &a) const {
    return Operation::operator==(static_cast<const Operation &>(a)) && left == a.left &&
           right == a.right;
}
bool IR::Operation_Binary::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation::equiv(a_)) return false;
    auto &a = static_cast<const Operation_Binary &>(a_);
    return (left ? a.left ? left->equiv(*a.left) : false : a.left == nullptr) &&
           (right ? a.right ? right->equiv(*a.right) : false : a.right == nullptr);
}
void IR::Operation_Binary::visit_children(Visitor &v, char const *n) {
    (void)n;
    Operation::visit_children(v, n);
    v.visit(left, "left");
    v.visit(right, "right");
}
void IR::Operation_Binary::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Operation::visit_children(v, n);
    v.visit(left, "left");
    v.visit(right, "right");
}
void IR::Operation_Binary::validate() const {
    CHECK_NULL(left);
    CHECK_NULL(right);
}
void IR::Operation_Binary::toJSON(JSONGenerator &json) const {
    Operation::toJSON(json);
    json.emit("left", left);
    json.emit("right", right);
}
IR::Operation_Binary::Operation_Binary(JSONLoader &json) : Operation(json) {
    json.load("left", left) || json.error("missing field left");
    json.load("right", right) || json.error("missing field right");
}
bool IR::Operation_Binary::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Operation_Binary::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Operation_Binary::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Operation_Ternary::operator==(IR::Operation_Ternary const &a) const {
    return Operation::operator==(static_cast<const Operation &>(a)) && e0 == a.e0 && e1 == a.e1 &&
           e2 == a.e2;
}
bool IR::Operation_Ternary::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation::equiv(a_)) return false;
    auto &a = static_cast<const Operation_Ternary &>(a_);
    return (e0 ? a.e0 ? e0->equiv(*a.e0) : false : a.e0 == nullptr) &&
           (e1 ? a.e1 ? e1->equiv(*a.e1) : false : a.e1 == nullptr) &&
           (e2 ? a.e2 ? e2->equiv(*a.e2) : false : a.e2 == nullptr);
}
void IR::Operation_Ternary::visit_children(Visitor &v, char const *n) {
    (void)n;
    Operation::visit_children(v, n);
    v.visit(e0, "e0");
    v.visit(e1, "e1");
    v.visit(e2, "e2");
}
void IR::Operation_Ternary::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Operation::visit_children(v, n);
    v.visit(e0, "e0");
    v.visit(e1, "e1");
    v.visit(e2, "e2");
}
void IR::Operation_Ternary::validate() const {
    CHECK_NULL(e0);
    CHECK_NULL(e1);
    CHECK_NULL(e2);
}
void IR::Operation_Ternary::toJSON(JSONGenerator &json) const {
    Operation::toJSON(json);
    json.emit("e0", e0);
    json.emit("e1", e1);
    json.emit("e2", e2);
}
IR::Operation_Ternary::Operation_Ternary(JSONLoader &json) : Operation(json) {
    json.load("e0", e0) || json.error("missing field e0");
    json.load("e1", e1) || json.error("missing field e1");
    json.load("e2", e2) || json.error("missing field e2");
}
bool IR::Operation_Ternary::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Operation_Ternary::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Operation_Ternary::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Operation_Relation::operator==(IR::Operation_Relation const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::Operation_Relation::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::Operation_Relation::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::Operation_Relation::Operation_Relation(JSONLoader &json) : Operation_Binary(json) {}
bool IR::Operation_Relation::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Operation_Relation::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Operation_Relation::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Operation_Relation::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Mul::operator==(IR::Mul const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::Mul::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::Mul::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::Mul::Mul(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::Mul::fromJSON(JSONLoader &json) { return new Mul(json); }
bool IR::Mul::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Mul::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Mul::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Mul::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Div::operator==(IR::Div const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::Div::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::Div::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::Div::Div(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::Div::fromJSON(JSONLoader &json) { return new Div(json); }
bool IR::Div::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Div::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Div::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Div::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Mod::operator==(IR::Mod const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::Mod::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::Mod::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::Mod::Mod(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::Mod::fromJSON(JSONLoader &json) { return new Mod(json); }
bool IR::Mod::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Mod::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Mod::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Mod::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Add::operator==(IR::Add const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::Add::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::Add::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::Add::Add(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::Add::fromJSON(JSONLoader &json) { return new Add(json); }
bool IR::Add::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Add::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Add::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Add::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Sub::operator==(IR::Sub const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::Sub::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::Sub::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::Sub::Sub(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::Sub::fromJSON(JSONLoader &json) { return new Sub(json); }
bool IR::Sub::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Sub::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Sub::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Sub::operator==(IR::Node const &a) const { return a == *this; }
bool IR::AddSat::operator==(IR::AddSat const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::AddSat::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::AddSat::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::AddSat::AddSat(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::AddSat::fromJSON(JSONLoader &json) { return new AddSat(json); }
bool IR::AddSat::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::AddSat::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::AddSat::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::AddSat::operator==(IR::Node const &a) const { return a == *this; }
bool IR::SubSat::operator==(IR::SubSat const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::SubSat::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::SubSat::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::SubSat::SubSat(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::SubSat::fromJSON(JSONLoader &json) { return new SubSat(json); }
bool IR::SubSat::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::SubSat::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::SubSat::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::SubSat::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Shl::operator==(IR::Shl const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::Shl::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::Shl::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::Shl::Shl(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::Shl::fromJSON(JSONLoader &json) { return new Shl(json); }
bool IR::Shl::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Shl::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Shl::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Shl::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Shr::operator==(IR::Shr const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::Shr::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::Shr::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::Shr::Shr(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::Shr::fromJSON(JSONLoader &json) { return new Shr(json); }
bool IR::Shr::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Shr::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Shr::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Shr::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Equ::operator==(IR::Equ const &a) const {
    return Operation_Relation::operator==(static_cast<const Operation_Relation &>(a));
}
bool IR::Equ::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Relation::equiv(a_)) return false;
    return true;
}
void IR::Equ::toJSON(JSONGenerator &json) const { Operation_Relation::toJSON(json); }
IR::Equ::Equ(JSONLoader &json) : Operation_Relation(json) {}
IR::Node *IR::Equ::fromJSON(JSONLoader &json) { return new Equ(json); }
bool IR::Equ::operator==(IR::Operation_Relation const &a) const { return a == *this; }
bool IR::Equ::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Equ::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Equ::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Equ::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Neq::operator==(IR::Neq const &a) const {
    return Operation_Relation::operator==(static_cast<const Operation_Relation &>(a));
}
bool IR::Neq::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Relation::equiv(a_)) return false;
    return true;
}
void IR::Neq::toJSON(JSONGenerator &json) const { Operation_Relation::toJSON(json); }
IR::Neq::Neq(JSONLoader &json) : Operation_Relation(json) {}
IR::Node *IR::Neq::fromJSON(JSONLoader &json) { return new Neq(json); }
bool IR::Neq::operator==(IR::Operation_Relation const &a) const { return a == *this; }
bool IR::Neq::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Neq::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Neq::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Neq::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Lss::operator==(IR::Lss const &a) const {
    return Operation_Relation::operator==(static_cast<const Operation_Relation &>(a));
}
bool IR::Lss::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Relation::equiv(a_)) return false;
    return true;
}
void IR::Lss::toJSON(JSONGenerator &json) const { Operation_Relation::toJSON(json); }
IR::Lss::Lss(JSONLoader &json) : Operation_Relation(json) {}
IR::Node *IR::Lss::fromJSON(JSONLoader &json) { return new Lss(json); }
bool IR::Lss::operator==(IR::Operation_Relation const &a) const { return a == *this; }
bool IR::Lss::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Lss::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Lss::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Lss::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Leq::operator==(IR::Leq const &a) const {
    return Operation_Relation::operator==(static_cast<const Operation_Relation &>(a));
}
bool IR::Leq::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Relation::equiv(a_)) return false;
    return true;
}
void IR::Leq::toJSON(JSONGenerator &json) const { Operation_Relation::toJSON(json); }
IR::Leq::Leq(JSONLoader &json) : Operation_Relation(json) {}
IR::Node *IR::Leq::fromJSON(JSONLoader &json) { return new Leq(json); }
bool IR::Leq::operator==(IR::Operation_Relation const &a) const { return a == *this; }
bool IR::Leq::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Leq::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Leq::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Leq::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Grt::operator==(IR::Grt const &a) const {
    return Operation_Relation::operator==(static_cast<const Operation_Relation &>(a));
}
bool IR::Grt::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Relation::equiv(a_)) return false;
    return true;
}
void IR::Grt::toJSON(JSONGenerator &json) const { Operation_Relation::toJSON(json); }
IR::Grt::Grt(JSONLoader &json) : Operation_Relation(json) {}
IR::Node *IR::Grt::fromJSON(JSONLoader &json) { return new Grt(json); }
bool IR::Grt::operator==(IR::Operation_Relation const &a) const { return a == *this; }
bool IR::Grt::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Grt::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Grt::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Grt::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Geq::operator==(IR::Geq const &a) const {
    return Operation_Relation::operator==(static_cast<const Operation_Relation &>(a));
}
bool IR::Geq::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Relation::equiv(a_)) return false;
    return true;
}
void IR::Geq::toJSON(JSONGenerator &json) const { Operation_Relation::toJSON(json); }
IR::Geq::Geq(JSONLoader &json) : Operation_Relation(json) {}
IR::Node *IR::Geq::fromJSON(JSONLoader &json) { return new Geq(json); }
bool IR::Geq::operator==(IR::Operation_Relation const &a) const { return a == *this; }
bool IR::Geq::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Geq::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Geq::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Geq::operator==(IR::Node const &a) const { return a == *this; }
bool IR::BAnd::operator==(IR::BAnd const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::BAnd::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::BAnd::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::BAnd::BAnd(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::BAnd::fromJSON(JSONLoader &json) { return new BAnd(json); }
bool IR::BAnd::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::BAnd::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::BAnd::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::BAnd::operator==(IR::Node const &a) const { return a == *this; }
bool IR::BOr::operator==(IR::BOr const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::BOr::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::BOr::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::BOr::BOr(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::BOr::fromJSON(JSONLoader &json) { return new BOr(json); }
bool IR::BOr::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::BOr::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::BOr::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::BOr::operator==(IR::Node const &a) const { return a == *this; }
bool IR::BXor::operator==(IR::BXor const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::BXor::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::BXor::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::BXor::BXor(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::BXor::fromJSON(JSONLoader &json) { return new BXor(json); }
bool IR::BXor::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::BXor::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::BXor::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::BXor::operator==(IR::Node const &a) const { return a == *this; }
bool IR::LAnd::operator==(IR::LAnd const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::LAnd::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::LAnd::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::LAnd::LAnd(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::LAnd::fromJSON(JSONLoader &json) { return new LAnd(json); }
bool IR::LAnd::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::LAnd::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::LAnd::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::LAnd::operator==(IR::Node const &a) const { return a == *this; }
bool IR::LOr::operator==(IR::LOr const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::LOr::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::LOr::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::LOr::LOr(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::LOr::fromJSON(JSONLoader &json) { return new LOr(json); }
bool IR::LOr::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::LOr::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::LOr::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::LOr::operator==(IR::Node const &a) const { return a == *this; }
void IR::Dots::dbprint(std::ostream &out) const { out << "..."; }
cstring IR::Dots::toString() const { return "..."_cs; }
bool IR::Dots::operator==(IR::Dots const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a));
}
bool IR::Dots::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    return true;
}
void IR::Dots::toJSON(JSONGenerator &json) const { Expression::toJSON(json); }
IR::Dots::Dots(JSONLoader &json) : Expression(json) {}
IR::Node *IR::Dots::fromJSON(JSONLoader &json) { return new Dots(json); }
bool IR::Dots::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Dots::operator==(IR::Node const &a) const { return a == *this; }
void IR::NamedDots::dbprint(std::ostream &out) const { out << "..."; }
cstring IR::NamedDots::toString() const { return "..."_cs; }
bool IR::NamedDots::operator==(IR::NamedDots const &a) const {
    return NamedExpression::operator==(static_cast<const NamedExpression &>(a));
}
bool IR::NamedDots::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!NamedExpression::equiv(a_)) return false;
    return true;
}
void IR::NamedDots::toJSON(JSONGenerator &json) const { NamedExpression::toJSON(json); }
IR::NamedDots::NamedDots(JSONLoader &json) : NamedExpression(json) {}
IR::Node *IR::NamedDots::fromJSON(JSONLoader &json) { return new NamedDots(json); }
bool IR::NamedDots::operator==(IR::NamedExpression const &a) const { return a == *this; }
bool IR::NamedDots::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::NamedDots::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::NamedDots::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Literal::operator==(IR::Literal const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a));
}
bool IR::Literal::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    return true;
}
void IR::Literal::toJSON(JSONGenerator &json) const { Expression::toJSON(json); }
IR::Literal::Literal(JSONLoader &json) : Expression(json) {}
bool IR::Literal::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Literal::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Constant::toString() const {
    unsigned width;
    bool sign;
    if (const IR::Type_Bits *tb = type->to<IR::Type_Bits>()) {
        width = tb->size;
        sign = tb->isSigned;
    } else {
        width = 0;
        sign = false;
    }
    return Util::toString(value, width, sign, base);
}
void IR::Constant::visit_children(Visitor &v, char const *n) {
    (void)n;
    v.visit(type, "type");
}
void IR::Constant::visit_children(Visitor &v, char const *n) const {
    (void)n;
    v.visit(type, "type");
}
bool IR::Constant::operator==(IR::Constant const &a) const {
    return Literal::operator==(static_cast<const Literal &>(a)) && value == a.value &&
           base == a.base;
}
bool IR::Constant::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Literal::equiv(a_)) return false;
    auto &a = static_cast<const Constant &>(a_);
    return value == a.value && base == a.base;
}
void IR::Constant::dump_fields(std::ostream &out) const {
    Literal::dump_fields(out);
    out << " value=" << value;
    out << " base=" << base;
}
void IR::Constant::toJSON(JSONGenerator &json) const {
    Literal::toJSON(json);
    json.emit("value", value);
    json.emit("base", base);
}
IR::Constant::Constant(JSONLoader &json) : Literal(json) {
    json.load("value", value) || json.error("missing field value");
    json.load("base", base) || json.error("missing field base");
}
IR::Node *IR::Constant::fromJSON(JSONLoader &json) { return new Constant(json); }
bool IR::Constant::operator==(IR::Literal const &a) const { return a == *this; }
bool IR::Constant::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Constant::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::BoolLiteral::toString() const { return value ? "true"_cs : "false"_cs; }
/// @return a bool literal. Both booleans are interned.
bool IR::BoolLiteral::operator==(IR::BoolLiteral const &a) const {
    return Literal::operator==(static_cast<const Literal &>(a)) && value == a.value;
}
bool IR::BoolLiteral::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Literal::equiv(a_)) return false;
    auto &a = static_cast<const BoolLiteral &>(a_);
    return value == a.value;
}
void IR::BoolLiteral::dump_fields(std::ostream &out) const {
    Literal::dump_fields(out);
    out << " value=" << value;
}
void IR::BoolLiteral::toJSON(JSONGenerator &json) const {
    Literal::toJSON(json);
    json.emit("value", value);
}
IR::BoolLiteral::BoolLiteral(JSONLoader &json) : Literal(json) {
    json.load("value", value) || json.error("missing field value");
}
IR::Node *IR::BoolLiteral::fromJSON(JSONLoader &json) { return new BoolLiteral(json); }
bool IR::BoolLiteral::operator==(IR::Literal const &a) const { return a == *this; }
bool IR::BoolLiteral::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::BoolLiteral::operator==(IR::Node const &a) const { return a == *this; }
void IR::StringLiteral::validate() const {
    {
        if (value.isNull()) BUG("null StringLiteral");
    }
}
cstring IR::StringLiteral::toString() const { return absl::StrCat("\"", value.escapeJson(), "\""); }
/// @returns a string literal. The value is cached.
bool IR::StringLiteral::operator==(IR::StringLiteral const &a) const {
    return Literal::operator==(static_cast<const Literal &>(a)) && value == a.value;
}
bool IR::StringLiteral::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Literal::equiv(a_)) return false;
    auto &a = static_cast<const StringLiteral &>(a_);
    return value == a.value;
}
void IR::StringLiteral::dump_fields(std::ostream &out) const {
    Literal::dump_fields(out);
    out << " value=" << value;
}
void IR::StringLiteral::toJSON(JSONGenerator &json) const {
    Literal::toJSON(json);
    json.emit("value", value);
}
IR::StringLiteral::StringLiteral(JSONLoader &json) : Literal(json) {
    json.load("value", value) || json.error("missing field value");
}
IR::Node *IR::StringLiteral::fromJSON(JSONLoader &json) { return new StringLiteral(json); }
bool IR::StringLiteral::operator==(IR::Literal const &a) const { return a == *this; }
bool IR::StringLiteral::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::StringLiteral::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::PathExpression::toString() const { return path->toString(); }
bool IR::PathExpression::operator==(IR::PathExpression const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && path == a.path;
}
bool IR::PathExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const PathExpression &>(a_);
    return (path ? a.path ? path->equiv(*a.path) : false : a.path == nullptr);
}
void IR::PathExpression::visit_children(Visitor &v, char const *n) {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(path, "path");
}
void IR::PathExpression::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(path, "path");
}
void IR::PathExpression::validate() const { CHECK_NULL(path); }
void IR::PathExpression::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("path", path);
}
IR::PathExpression::PathExpression(JSONLoader &json) : Expression(json) {
    json.load("path", path) || json.error("missing field path");
}
IR::Node *IR::PathExpression::fromJSON(JSONLoader &json) { return new PathExpression(json); }
bool IR::PathExpression::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::PathExpression::operator==(IR::Node const &a) const { return a == *this; }
void IR::TypeNameExpression::dbprint(std::ostream &out) const { out << typeName; }
cstring IR::TypeNameExpression::toString() const { return typeName->toString(); }
void IR::TypeNameExpression::validate() const {
    CHECK_NULL(typeName);
    {
        BUG_CHECK(typeName->is<Type_Name>() || typeName->is<Type_Specialized>(),
                  "%1% unexpected type in TypeNameExpression", typeName);
    }
}
bool IR::TypeNameExpression::operator==(IR::TypeNameExpression const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && typeName == a.typeName;
}
bool IR::TypeNameExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const TypeNameExpression &>(a_);
    return (typeName ? a.typeName ? typeName->equiv(*a.typeName) : false : a.typeName == nullptr);
}
void IR::TypeNameExpression::visit_children(Visitor &v, char const *n) {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(typeName, "typeName");
}
void IR::TypeNameExpression::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(typeName, "typeName");
}
void IR::TypeNameExpression::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("typeName", typeName);
}
IR::TypeNameExpression::TypeNameExpression(JSONLoader &json) : Expression(json) {
    json.load("typeName", typeName) || json.error("missing field typeName");
}
IR::Node *IR::TypeNameExpression::fromJSON(JSONLoader &json) {
    return new TypeNameExpression(json);
}
bool IR::TypeNameExpression::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::TypeNameExpression::operator==(IR::Node const &a) const { return a == *this; }
bool IR::AbstractSlice::operator==(IR::AbstractSlice const &a) const {
    return Operation_Ternary::operator==(static_cast<const Operation_Ternary &>(a));
}
bool IR::AbstractSlice::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Ternary::equiv(a_)) return false;
    return true;
}
void IR::AbstractSlice::toJSON(JSONGenerator &json) const { Operation_Ternary::toJSON(json); }
IR::AbstractSlice::AbstractSlice(JSONLoader &json) : Operation_Ternary(json) {}
bool IR::AbstractSlice::operator==(IR::Operation_Ternary const &a) const { return a == *this; }
bool IR::AbstractSlice::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::AbstractSlice::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::AbstractSlice::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Slice::toString() const { return absl::StrCat(e0, "[", e1, ":", e2, "]"); }

unsigned IR::Slice::getH() const { return e1->checkedTo<IR::Constant>()->asUnsigned(); }
unsigned IR::Slice::getL() const { return e2->checkedTo<IR::Constant>()->asUnsigned(); }

bool IR::Slice::operator==(IR::Slice const &a) const {
    return AbstractSlice::operator==(static_cast<const AbstractSlice &>(a));
}
bool IR::Slice::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!AbstractSlice::equiv(a_)) return false;
    return true;
}
void IR::Slice::toJSON(JSONGenerator &json) const { AbstractSlice::toJSON(json); }
IR::Slice::Slice(JSONLoader &json) : AbstractSlice(json) {}
IR::Node *IR::Slice::fromJSON(JSONLoader &json) { return new Slice(json); }
bool IR::Slice::operator==(IR::AbstractSlice const &a) const { return a == *this; }
bool IR::Slice::operator==(IR::Operation_Ternary const &a) const { return a == *this; }
bool IR::Slice::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Slice::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Slice::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::PlusSlice::toString() const { return absl::StrCat(e0, "[", e1, "+:", e2, "]"); }
unsigned IR::PlusSlice::getH() const {
    BUG_CHECK(e1->is<IR::Constant>(), "non-const PlusSlice not handled");
    return e1->to<IR::Constant>()->asUnsigned() + e2->checkedTo<IR::Constant>()->asUnsigned() - 1;
}
unsigned IR::PlusSlice::getL() const {
    BUG_CHECK(e1->is<IR::Constant>(), "non-const PlusSlice not handled");
    return e1->to<IR::Constant>()->asUnsigned();
}
bool IR::PlusSlice::operator==(IR::PlusSlice const &a) const {
    return AbstractSlice::operator==(static_cast<const AbstractSlice &>(a));
}
bool IR::PlusSlice::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!AbstractSlice::equiv(a_)) return false;
    return true;
}
void IR::PlusSlice::toJSON(JSONGenerator &json) const { AbstractSlice::toJSON(json); }
IR::PlusSlice::PlusSlice(JSONLoader &json) : AbstractSlice(json) {}
IR::Node *IR::PlusSlice::fromJSON(JSONLoader &json) { return new PlusSlice(json); }
bool IR::PlusSlice::operator==(IR::AbstractSlice const &a) const { return a == *this; }
bool IR::PlusSlice::operator==(IR::Operation_Ternary const &a) const { return a == *this; }
bool IR::PlusSlice::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::PlusSlice::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::PlusSlice::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Member::toString() const { return absl::StrCat(expr, ".", member); }
bool IR::Member::operator==(IR::Member const &a) const {
    return Operation_Unary::operator==(static_cast<const Operation_Unary &>(a)) &&
           member == a.member;
}
bool IR::Member::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Unary::equiv(a_)) return false;
    auto &a = static_cast<const Member &>(a_);
    return member == a.member;
}
void IR::Member::dump_fields(std::ostream &out) const {
    Operation_Unary::dump_fields(out);
    out << " member=" << member;
}
void IR::Member::toJSON(JSONGenerator &json) const {
    Operation_Unary::toJSON(json);
    json.emit("member", member);
}
IR::Member::Member(JSONLoader &json) : Operation_Unary(json) {
    json.load("member", member) || json.error("missing field member");
}
IR::Node *IR::Member::fromJSON(JSONLoader &json) { return new Member(json); }
bool IR::Member::operator==(IR::Operation_Unary const &a) const { return a == *this; }
bool IR::Member::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Member::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Member::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Concat::operator==(IR::Concat const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::Concat::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::Concat::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::Concat::Concat(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::Concat::fromJSON(JSONLoader &json) { return new Concat(json); }
bool IR::Concat::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Concat::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Concat::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Concat::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::ArrayIndex::toString() const { return absl::StrCat(left, "[", right, "]"); }
bool IR::ArrayIndex::operator==(IR::ArrayIndex const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::ArrayIndex::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::ArrayIndex::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::ArrayIndex::ArrayIndex(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::ArrayIndex::fromJSON(JSONLoader &json) { return new ArrayIndex(json); }
bool IR::ArrayIndex::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::ArrayIndex::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::ArrayIndex::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::ArrayIndex::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Range::operator==(IR::Range const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::Range::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::Range::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::Range::Range(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::Range::fromJSON(JSONLoader &json) { return new Range(json); }
bool IR::Range::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Range::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Range::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Range::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Mask::operator==(IR::Mask const &a) const {
    return Operation_Binary::operator==(static_cast<const Operation_Binary &>(a));
}
bool IR::Mask::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Binary::equiv(a_)) return false;
    return true;
}
void IR::Mask::toJSON(JSONGenerator &json) const { Operation_Binary::toJSON(json); }
IR::Mask::Mask(JSONLoader &json) : Operation_Binary(json) {}
IR::Node *IR::Mask::fromJSON(JSONLoader &json) { return new Mask(json); }
bool IR::Mask::operator==(IR::Operation_Binary const &a) const { return a == *this; }
bool IR::Mask::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Mask::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Mask::operator==(IR::Node const &a) const { return a == *this; }
void IR::Mux::visit_children(Visitor &v, char const *n) {
    (void)n;
    v.visit(e0, "e0");
    SplitFlowVisit<Expression>(v, e1, e2).run_visit();
}
void IR::Mux::visit_children(Visitor &v, char const *n) const {
    (void)n;
    v.visit(e0, "e0");
    SplitFlowVisit<Expression>(v, e1, e2).run_visit();
}
bool IR::Mux::operator==(IR::Mux const &a) const {
    return Operation_Ternary::operator==(static_cast<const Operation_Ternary &>(a));
}
bool IR::Mux::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Ternary::equiv(a_)) return false;
    return true;
}
void IR::Mux::toJSON(JSONGenerator &json) const { Operation_Ternary::toJSON(json); }
IR::Mux::Mux(JSONLoader &json) : Operation_Ternary(json) {}
IR::Node *IR::Mux::fromJSON(JSONLoader &json) { return new Mux(json); }
bool IR::Mux::operator==(IR::Operation_Ternary const &a) const { return a == *this; }
bool IR::Mux::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Mux::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Mux::operator==(IR::Node const &a) const { return a == *this; }
bool IR::DefaultExpression::operator==(IR::DefaultExpression const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a));
}
bool IR::DefaultExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    return true;
}
void IR::DefaultExpression::toJSON(JSONGenerator &json) const { Expression::toJSON(json); }
IR::DefaultExpression::DefaultExpression(JSONLoader &json) : Expression(json) {}
IR::Node *IR::DefaultExpression::fromJSON(JSONLoader &json) { return new DefaultExpression(json); }
bool IR::DefaultExpression::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::DefaultExpression::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::This::toString() const { return "this"_cs; }
bool IR::This::operator==(IR::This const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && id == a.id;
}
bool IR::This::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const This &>(a_);
    return id == a.id;
}
void IR::This::dump_fields(std::ostream &out) const {
    Expression::dump_fields(out);
    out << " id=" << id;
}
void IR::This::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("id", id);
}
IR::This::This(JSONLoader &json) : Expression(json) {
    json.load("id", id) || json.error("missing field id");
}
IR::Node *IR::This::fromJSON(JSONLoader &json) { return new This(json); }
bool IR::This::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::This::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Cast::toString() const { return absl::StrCat("(", destType, ")", expr); }
void IR::Cast::validate() const {
    CHECK_NULL(destType);
    { BUG_CHECK(!destType->is<Type_Unknown>(), "%1%: Cannot cast to unknown type", this); }
}
bool IR::Cast::operator==(IR::Cast const &a) const {
    return Operation_Unary::operator==(static_cast<const Operation_Unary &>(a)) &&
           destType == a.destType && implicit == a.implicit;
}
bool IR::Cast::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Unary::equiv(a_)) return false;
    auto &a = static_cast<const Cast &>(a_);
    return (destType ? a.destType ? destType->equiv(*a.destType) : false : a.destType == nullptr) &&
           implicit == a.implicit;
}
void IR::Cast::visit_children(Visitor &v, char const *n) {
    (void)n;
    Operation_Unary::visit_children(v, n);
    v.visit(destType, "destType");
}
void IR::Cast::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Operation_Unary::visit_children(v, n);
    v.visit(destType, "destType");
}
void IR::Cast::dump_fields(std::ostream &out) const {
    Operation_Unary::dump_fields(out);
    out << " implicit=" << implicit;
}
void IR::Cast::toJSON(JSONGenerator &json) const {
    Operation_Unary::toJSON(json);
    json.emit("destType", destType);
    json.emit("implicit", implicit);
}
IR::Cast::Cast(JSONLoader &json) : Operation_Unary(json) {
    json.load("destType", destType) || json.error("missing field destType");
    json.load("implicit", implicit) || json.error("missing field implicit");
}
IR::Node *IR::Cast::fromJSON(JSONLoader &json) { return new Cast(json); }
bool IR::Cast::operator==(IR::Operation_Unary const &a) const { return a == *this; }
bool IR::Cast::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Cast::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Cast::operator==(IR::Node const &a) const { return a == *this; }
void IR::SelectCase::dbprint(std::ostream &out) const { out << keyset << ": " << state; }
bool IR::SelectCase::operator==(IR::SelectCase const &a) const {
    return this->typeId() == a.typeId() && keyset == a.keyset && state == a.state;
}
bool IR::SelectCase::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const SelectCase &>(a_);
    return (keyset ? a.keyset ? keyset->equiv(*a.keyset) : false : a.keyset == nullptr) &&
           (state ? a.state ? state->equiv(*a.state) : false : a.state == nullptr);
}
void IR::SelectCase::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    v.visit(keyset, "keyset");
    v.visit(state, "state");
}
void IR::SelectCase::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    v.visit(keyset, "keyset");
    v.visit(state, "state");
}
void IR::SelectCase::validate() const {
    CHECK_NULL(keyset);
    CHECK_NULL(state);
}
void IR::SelectCase::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("keyset", keyset);
    json.emit("state", state);
}
IR::SelectCase::SelectCase(JSONLoader &json) : Node(json) {
    json.load("keyset", keyset) || json.error("missing field keyset");
    json.load("state", state) || json.error("missing field state");
}
IR::Node *IR::SelectCase::fromJSON(JSONLoader &json) { return new SelectCase(json); }
bool IR::SelectCase::operator==(IR::Node const &a) const { return a == *this; }
void IR::SelectExpression::visit_children(Visitor &v, char const *n) {
    (void)n;
    v.visit(select, "select");
    SplitFlowVisitVector<SelectCase>(v, selectCases).run_visit();
}
void IR::SelectExpression::visit_children(Visitor &v, char const *n) const {
    (void)n;
    v.visit(select, "select");
    SplitFlowVisitVector<SelectCase>(v, selectCases).run_visit();
}
bool IR::SelectExpression::operator==(IR::SelectExpression const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && select == a.select &&
           selectCases == a.selectCases;
}
bool IR::SelectExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const SelectExpression &>(a_);
    return (select ? a.select ? select->equiv(*a.select) : false : a.select == nullptr) &&
           selectCases.equiv(a.selectCases);
}
void IR::SelectExpression::validate() const {
    CHECK_NULL(select);
    selectCases.validate();
}
void IR::SelectExpression::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("select", select);
    json.emit("selectCases", selectCases);
}
IR::SelectExpression::SelectExpression(JSONLoader &json) : Expression(json) {
    json.load("select", select) || json.error("missing field select");
    json.load("selectCases", selectCases) || json.error("missing field selectCases");
}
IR::Node *IR::SelectExpression::fromJSON(JSONLoader &json) { return new SelectExpression(json); }
bool IR::SelectExpression::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::SelectExpression::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::MethodCallExpression::toString() const {
    return absl::StrCat(
        method, "(",
        absl::StrJoin(*arguments, ", ",
                      [](std::string *out, const Argument *arg) { absl::StrAppend(out, arg); }),
        ")");
}
void IR::MethodCallExpression::validate() const {
    CHECK_NULL(method);
    CHECK_NULL(typeArguments);
    CHECK_NULL(arguments);
    {
        typeArguments->check_null();
        arguments->check_null();
    }
}
IR::MethodCallExpression::MethodCallExpression(
    const IR::Expression *m, std::initializer_list<IR::Expression const *> const &a)
    : method(m), arguments(nullptr) {
    auto arguments = new Vector<Argument>;
    for (auto arg : a) arguments->push_back(new Argument(arg));
    this->arguments = arguments;
}
bool IR::MethodCallExpression::operator==(IR::MethodCallExpression const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && method == a.method &&
           typeArguments == a.typeArguments && arguments == a.arguments;
}
bool IR::MethodCallExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const MethodCallExpression &>(a_);
    return (method ? a.method ? method->equiv(*a.method) : false : a.method == nullptr) &&
           (typeArguments ? a.typeArguments ? typeArguments->equiv(*a.typeArguments) : false
                          : a.typeArguments == nullptr) &&
           (arguments ? a.arguments ? arguments->equiv(*a.arguments) : false
                      : a.arguments == nullptr);
}
void IR::MethodCallExpression::visit_children(Visitor &v, char const *n) {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(method, "method");
    v.visit(typeArguments, "typeArguments");
    v.visit(arguments, "arguments");
}
void IR::MethodCallExpression::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(method, "method");
    v.visit(typeArguments, "typeArguments");
    v.visit(arguments, "arguments");
}
void IR::MethodCallExpression::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("method", method);
    json.emit("typeArguments", typeArguments);
    json.emit("arguments", arguments);
}
IR::MethodCallExpression::MethodCallExpression(JSONLoader &json) : Expression(json) {
    json.load("method", method) || json.error("missing field method");
    json.load("typeArguments", typeArguments) || json.error("missing field typeArguments");
    json.load("arguments", arguments) || json.error("missing field arguments");
}
IR::Node *IR::MethodCallExpression::fromJSON(JSONLoader &json) {
    return new MethodCallExpression(json);
}
bool IR::MethodCallExpression::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::MethodCallExpression::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::ConstructorCallExpression::toString() const { return constructedType->toString(); }
void IR::ConstructorCallExpression::validate() const {
    CHECK_NULL(constructedType);
    CHECK_NULL(arguments);
    {
        BUG_CHECK(constructedType->is<Type_Name>() || constructedType->is<Type_Specialized>(),
                  "%1%: unexpected type", constructedType);
        arguments->check_null();
    }
}
bool IR::ConstructorCallExpression::operator==(IR::ConstructorCallExpression const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) &&
           constructedType == a.constructedType && arguments == a.arguments;
}
bool IR::ConstructorCallExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const ConstructorCallExpression &>(a_);
    return (constructedType ? a.constructedType ? constructedType->equiv(*a.constructedType) : false
                            : a.constructedType == nullptr) &&
           (arguments ? a.arguments ? arguments->equiv(*a.arguments) : false
                      : a.arguments == nullptr);
}
void IR::ConstructorCallExpression::visit_children(Visitor &v, char const *n) {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(constructedType, "constructedType");
    v.visit(arguments, "arguments");
}
void IR::ConstructorCallExpression::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(constructedType, "constructedType");
    v.visit(arguments, "arguments");
}
void IR::ConstructorCallExpression::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("constructedType", constructedType);
    json.emit("arguments", arguments);
}
IR::ConstructorCallExpression::ConstructorCallExpression(JSONLoader &json) : Expression(json) {
    json.load("constructedType", constructedType) || json.error("missing field constructedType");
    json.load("arguments", arguments) || json.error("missing field arguments");
}
IR::Node *IR::ConstructorCallExpression::fromJSON(JSONLoader &json) {
    return new ConstructorCallExpression(json);
}
bool IR::ConstructorCallExpression::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::ConstructorCallExpression::operator==(IR::Node const &a) const { return a == *this; }
void IR::BaseListExpression::validate() const {
    components.validate();
    { components.check_null(); }
}
cstring IR::BaseListExpression::toString() const {
    return components.empty()
               ? "{}"
               : absl::StrCat("{ ",
                              absl::StrJoin(components, ", ",
                                            [](std::string *out, const Expression *comp) {
                                                absl::StrAppend(out, comp);
                                            }),
                              " }");
}
bool IR::BaseListExpression::operator==(IR::BaseListExpression const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && components == a.components;
}
bool IR::BaseListExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const BaseListExpression &>(a_);
    return components.equiv(a.components);
}
void IR::BaseListExpression::visit_children(Visitor &v, char const *n) {
    (void)n;
    Expression::visit_children(v, n);
    components.visit_children(v, "components");
}
void IR::BaseListExpression::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Expression::visit_children(v, n);
    components.visit_children(v, "components");
}
void IR::BaseListExpression::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("components", components);
}
IR::BaseListExpression::BaseListExpression(JSONLoader &json) : Expression(json) {
    json.load("components", components) || json.error("missing field components");
}
IR::Node *IR::BaseListExpression::fromJSON(JSONLoader &json) {
    return new BaseListExpression(json);
}
bool IR::BaseListExpression::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::BaseListExpression::operator==(IR::Node const &a) const { return a == *this; }
bool IR::ListExpression::operator==(IR::ListExpression const &a) const {
    return BaseListExpression::operator==(static_cast<const BaseListExpression &>(a));
}
bool IR::ListExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!BaseListExpression::equiv(a_)) return false;
    return true;
}
void IR::ListExpression::toJSON(JSONGenerator &json) const { BaseListExpression::toJSON(json); }
IR::ListExpression::ListExpression(JSONLoader &json) : BaseListExpression(json) {}
IR::Node *IR::ListExpression::fromJSON(JSONLoader &json) { return new ListExpression(json); }
bool IR::ListExpression::operator==(IR::BaseListExpression const &a) const { return a == *this; }
bool IR::ListExpression::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::ListExpression::operator==(IR::Node const &a) const { return a == *this; }
bool IR::P4ListExpression::operator==(IR::P4ListExpression const &a) const {
    return BaseListExpression::operator==(static_cast<const BaseListExpression &>(a)) &&
           elementType == a.elementType;
}
bool IR::P4ListExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!BaseListExpression::equiv(a_)) return false;
    auto &a = static_cast<const P4ListExpression &>(a_);
    return (elementType ? a.elementType ? elementType->equiv(*a.elementType) : false
                        : a.elementType == nullptr);
}
void IR::P4ListExpression::visit_children(Visitor &v, char const *n) {
    (void)n;
    BaseListExpression::visit_children(v, n);
    v.visit(elementType, "elementType");
}
void IR::P4ListExpression::visit_children(Visitor &v, char const *n) const {
    (void)n;
    BaseListExpression::visit_children(v, n);
    v.visit(elementType, "elementType");
}
void IR::P4ListExpression::validate() const { CHECK_NULL(elementType); }
void IR::P4ListExpression::toJSON(JSONGenerator &json) const {
    BaseListExpression::toJSON(json);
    json.emit("elementType", elementType);
}
IR::P4ListExpression::P4ListExpression(JSONLoader &json) : BaseListExpression(json) {
    json.load("elementType", elementType) || json.error("missing field elementType");
}
IR::Node *IR::P4ListExpression::fromJSON(JSONLoader &json) { return new P4ListExpression(json); }
bool IR::P4ListExpression::operator==(IR::BaseListExpression const &a) const { return a == *this; }
bool IR::P4ListExpression::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::P4ListExpression::operator==(IR::Node const &a) const { return a == *this; }
void IR::StructExpression::validate() const {
    components.validate();
    {
        components.check_null();
        components.validate();
        BUG_CHECK(structType == nullptr || structType->is<IR::Type_Name>() ||
                      structType->is<IR::Type_Specialized>(),
                  "%1%: unexpected struct type", this);
    }
}
cstring IR::StructExpression::toString() const {
    return components.empty()
               ? "{}"
               : absl::StrCat("{ ",
                              absl::StrJoin(components, ", ",
                                            [](std::string *out, const NamedExpression *comp) {
                                                absl::StrAppend(out, comp, " = ", comp->expression);
                                            }),
                              " }");
}
bool IR::StructExpression::operator==(IR::StructExpression const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) &&
           structType == a.structType && components == a.components;
}
bool IR::StructExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const StructExpression &>(a_);
    return (structType ? a.structType ? structType->equiv(*a.structType) : false
                       : a.structType == nullptr) &&
           components.equiv(a.components);
}
void IR::StructExpression::visit_children(Visitor &v, char const *n) {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(structType, "structType");
    components.visit_children(v, "components");
}
void IR::StructExpression::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(structType, "structType");
    components.visit_children(v, "components");
}
void IR::StructExpression::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    if (structType != nullptr) json.emit("structType", structType);
    json.emit("components", components);
}
IR::StructExpression::StructExpression(JSONLoader &json) : Expression(json) {
    json.load("structType", structType);
    json.load("components", components) || json.error("missing field components");
}
IR::Node *IR::StructExpression::fromJSON(JSONLoader &json) { return new StructExpression(json); }
bool IR::StructExpression::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::StructExpression::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Invalid::operator==(IR::Invalid const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a));
}
bool IR::Invalid::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    return true;
}
void IR::Invalid::toJSON(JSONGenerator &json) const { Expression::toJSON(json); }
IR::Invalid::Invalid(JSONLoader &json) : Expression(json) {}
IR::Node *IR::Invalid::fromJSON(JSONLoader &json) { return new Invalid(json); }
bool IR::Invalid::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Invalid::operator==(IR::Node const &a) const { return a == *this; }
bool IR::InvalidHeader::operator==(IR::InvalidHeader const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && headerType == a.headerType;
}
bool IR::InvalidHeader::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const InvalidHeader &>(a_);
    return (headerType ? a.headerType ? headerType->equiv(*a.headerType) : false
                       : a.headerType == nullptr);
}
void IR::InvalidHeader::visit_children(Visitor &v, char const *n) {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(headerType, "headerType");
}
void IR::InvalidHeader::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(headerType, "headerType");
}
void IR::InvalidHeader::validate() const { CHECK_NULL(headerType); }
void IR::InvalidHeader::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("headerType", headerType);
}
IR::InvalidHeader::InvalidHeader(JSONLoader &json) : Expression(json) {
    json.load("headerType", headerType) || json.error("missing field headerType");
}
IR::Node *IR::InvalidHeader::fromJSON(JSONLoader &json) { return new InvalidHeader(json); }
bool IR::InvalidHeader::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::InvalidHeader::operator==(IR::Node const &a) const { return a == *this; }
bool IR::InvalidHeaderUnion::operator==(IR::InvalidHeaderUnion const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) &&
           headerUnionType == a.headerUnionType;
}
bool IR::InvalidHeaderUnion::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const InvalidHeaderUnion &>(a_);
    return (headerUnionType ? a.headerUnionType ? headerUnionType->equiv(*a.headerUnionType) : false
                            : a.headerUnionType == nullptr);
}
void IR::InvalidHeaderUnion::visit_children(Visitor &v, char const *n) {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(headerUnionType, "headerUnionType");
}
void IR::InvalidHeaderUnion::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(headerUnionType, "headerUnionType");
}
void IR::InvalidHeaderUnion::validate() const { CHECK_NULL(headerUnionType); }
void IR::InvalidHeaderUnion::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("headerUnionType", headerUnionType);
}
IR::InvalidHeaderUnion::InvalidHeaderUnion(JSONLoader &json) : Expression(json) {
    json.load("headerUnionType", headerUnionType) || json.error("missing field headerUnionType");
}
IR::Node *IR::InvalidHeaderUnion::fromJSON(JSONLoader &json) {
    return new InvalidHeaderUnion(json);
}
bool IR::InvalidHeaderUnion::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::InvalidHeaderUnion::operator==(IR::Node const &a) const { return a == *this; }
void IR::ArrayExpression::validate() const {
    { components.check_null(); }
}
bool IR::ArrayExpression::operator==(IR::ArrayExpression const &a) const {
    return BaseListExpression::operator==(static_cast<const BaseListExpression &>(a)) &&
           arrayType == a.arrayType;
}
bool IR::ArrayExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!BaseListExpression::equiv(a_)) return false;
    auto &a = static_cast<const ArrayExpression &>(a_);
    return (arrayType ? a.arrayType ? arrayType->equiv(*a.arrayType) : false
                      : a.arrayType == nullptr);
}
void IR::ArrayExpression::visit_children(Visitor &v, char const *n) {
    (void)n;
    BaseListExpression::visit_children(v, n);
    v.visit(arrayType, "arrayType");
}
void IR::ArrayExpression::visit_children(Visitor &v, char const *n) const {
    (void)n;
    BaseListExpression::visit_children(v, n);
    v.visit(arrayType, "arrayType");
}
void IR::ArrayExpression::toJSON(JSONGenerator &json) const {
    BaseListExpression::toJSON(json);
    if (arrayType != nullptr) json.emit("arrayType", arrayType);
}
IR::ArrayExpression::ArrayExpression(JSONLoader &json) : BaseListExpression(json) {
    json.load("arrayType", arrayType);
}
IR::Node *IR::ArrayExpression::fromJSON(JSONLoader &json) { return new ArrayExpression(json); }
bool IR::ArrayExpression::operator==(IR::BaseListExpression const &a) const { return a == *this; }
bool IR::ArrayExpression::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::ArrayExpression::operator==(IR::Node const &a) const { return a == *this; }
void IR::ListCompileTimeValue::validate() const {
    components.validate();
    {
        for (auto v : components)
            BUG_CHECK(v->is<CompileTimeValue>(), "%1%: not a compile-time value", v);
    }
}
bool IR::ListCompileTimeValue::operator==(IR::ListCompileTimeValue const &a) const {
    return this->typeId() == a.typeId() && components == a.components;
}
bool IR::ListCompileTimeValue::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const ListCompileTimeValue &>(a_);
    return components.equiv(a.components);
}
void IR::ListCompileTimeValue::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    components.visit_children(v, "components");
}
void IR::ListCompileTimeValue::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    components.visit_children(v, "components");
}
void IR::ListCompileTimeValue::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("components", components);
}
IR::ListCompileTimeValue::ListCompileTimeValue(JSONLoader &json) : Node(json) {
    json.load("components", components) || json.error("missing field components");
}
IR::Node *IR::ListCompileTimeValue::fromJSON(JSONLoader &json) {
    return new ListCompileTimeValue(json);
}
bool IR::ListCompileTimeValue::operator==(IR::Node const &a) const { return a == *this; }
void IR::P4ListCompileTimeValue::validate() const {
    components.validate();
    {
        for (auto v : components)
            BUG_CHECK(v->is<CompileTimeValue>(), "%1%: not a compile-time value", v);
    }
}
bool IR::P4ListCompileTimeValue::operator==(IR::P4ListCompileTimeValue const &a) const {
    return this->typeId() == a.typeId() && components == a.components;
}
bool IR::P4ListCompileTimeValue::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const P4ListCompileTimeValue &>(a_);
    return components.equiv(a.components);
}
void IR::P4ListCompileTimeValue::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    components.visit_children(v, "components");
}
void IR::P4ListCompileTimeValue::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    components.visit_children(v, "components");
}
void IR::P4ListCompileTimeValue::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("components", components);
}
IR::P4ListCompileTimeValue::P4ListCompileTimeValue(JSONLoader &json) : Node(json) {
    json.load("components", components) || json.error("missing field components");
}
IR::Node *IR::P4ListCompileTimeValue::fromJSON(JSONLoader &json) {
    return new P4ListCompileTimeValue(json);
}
bool IR::P4ListCompileTimeValue::operator==(IR::Node const &a) const { return a == *this; }
void IR::StructCompileTimeValue::validate() const {
    components.validate();
    {
        for (auto v : components)
            BUG_CHECK(v->is<CompileTimeValue>(), "%1%: not a compile-time value", v);
    }
}
bool IR::StructCompileTimeValue::operator==(IR::StructCompileTimeValue const &a) const {
    return this->typeId() == a.typeId() && components == a.components;
}
bool IR::StructCompileTimeValue::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const StructCompileTimeValue &>(a_);
    return components.equiv(a.components);
}
void IR::StructCompileTimeValue::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    components.visit_children(v, "components");
}
void IR::StructCompileTimeValue::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    components.visit_children(v, "components");
}
void IR::StructCompileTimeValue::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("components", components);
}
IR::StructCompileTimeValue::StructCompileTimeValue(JSONLoader &json) : Node(json) {
    json.load("components", components) || json.error("missing field components");
}
IR::Node *IR::StructCompileTimeValue::fromJSON(JSONLoader &json) {
    return new StructCompileTimeValue(json);
}
bool IR::StructCompileTimeValue::operator==(IR::Node const &a) const { return a == *this; }
void IR::CompileTimeMethodCall::validate() const {
    {
        for (auto v : *arguments)
            BUG_CHECK(v->is<CompileTimeValue>(), "%1%: not a compile-time value", v);
    }
}
bool IR::CompileTimeMethodCall::operator==(IR::CompileTimeMethodCall const &a) const {
    return MethodCallExpression::operator==(static_cast<const MethodCallExpression &>(a));
}
bool IR::CompileTimeMethodCall::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!MethodCallExpression::equiv(a_)) return false;
    return true;
}
void IR::CompileTimeMethodCall::toJSON(JSONGenerator &json) const {
    MethodCallExpression::toJSON(json);
}
IR::CompileTimeMethodCall::CompileTimeMethodCall(JSONLoader &json) : MethodCallExpression(json) {}
IR::Node *IR::CompileTimeMethodCall::fromJSON(JSONLoader &json) {
    return new CompileTimeMethodCall(json);
}
bool IR::CompileTimeMethodCall::operator==(IR::MethodCallExpression const &a) const {
    return a == *this;
}
bool IR::CompileTimeMethodCall::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::CompileTimeMethodCall::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::SymbolicVariable::toString() const { return absl::StrCat("|", label, "(", type, ")|"); }
void IR::SymbolicVariable::dbprint(std::ostream &out) const {
    out << "|" + label + "(" << type << ")|";
}
bool IR::SymbolicVariable::operator==(IR::SymbolicVariable const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && label == a.label;
}
bool IR::SymbolicVariable::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const SymbolicVariable &>(a_);
    return label == a.label;
}
void IR::SymbolicVariable::dump_fields(std::ostream &out) const {
    Expression::dump_fields(out);
    out << " label=" << label;
}
void IR::SymbolicVariable::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("label", label);
}
IR::SymbolicVariable::SymbolicVariable(JSONLoader &json) : Expression(json) {
    json.load("label", label) || json.error("missing field label");
}
IR::Node *IR::SymbolicVariable::fromJSON(JSONLoader &json) { return new SymbolicVariable(json); }
bool IR::SymbolicVariable::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::SymbolicVariable::operator==(IR::Node const &a) const { return a == *this; }
