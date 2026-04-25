#include "ir/ir-generated.h"   // IWYU pragma: keep

#include "ir/ir-inline.h"      // IWYU pragma: keep
#include "ir/json_generator.h" // IWYU pragma: keep
#include "ir/json_loader.h"    // IWYU pragma: keep
#include "ir/visitor.h"        // IWYU pragma: keep
#include "lib/algorithm.h"     // IWYU pragma: keep
#include "lib/log.h"           // IWYU pragma: keep

using namespace P4;

// Method definitions for legacy P4-14 / v1model IR nodes.

cstring IR::Type_Block::toString() const { return "block"_cs; }
void IR::Type_Block::dbprint(std::ostream &out) const { out << "block"; }
bool IR::Type_Block::operator==(IR::Type_Block const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_Block::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_Block::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_Block::Type_Block(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_Block::fromJSON(JSONLoader &json) { return new Type_Block(json); }
bool IR::Type_Block::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_Block::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Block::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Counter::toString() const { return "counter"_cs; }
void IR::Type_Counter::dbprint(std::ostream &out) const { out << "counter"; }
bool IR::Type_Counter::operator==(IR::Type_Counter const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_Counter::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_Counter::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_Counter::Type_Counter(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_Counter::fromJSON(JSONLoader &json) { return new Type_Counter(json); }
bool IR::Type_Counter::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_Counter::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Counter::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Expression::toString() const { return "expression"_cs; }
void IR::Type_Expression::dbprint(std::ostream &out) const { out << "expression"; }
bool IR::Type_Expression::operator==(IR::Type_Expression const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_Expression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_Expression::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_Expression::Type_Expression(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_Expression::fromJSON(JSONLoader &json) { return new Type_Expression(json); }
bool IR::Type_Expression::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_Expression::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Expression::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_FieldListCalculation::toString() const { return "field_list_calculation"_cs; }
void IR::Type_FieldListCalculation::dbprint(std::ostream &out) const {
    out << "field_list_calculation";
}
bool IR::Type_FieldListCalculation::operator==(IR::Type_FieldListCalculation const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_FieldListCalculation::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_FieldListCalculation::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_FieldListCalculation::Type_FieldListCalculation(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_FieldListCalculation::fromJSON(JSONLoader &json) {
    return new Type_FieldListCalculation(json);
}
bool IR::Type_FieldListCalculation::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_FieldListCalculation::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_FieldListCalculation::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Meter::toString() const { return "meter"_cs; }
void IR::Type_Meter::dbprint(std::ostream &out) const { out << "meter"; }
bool IR::Type_Meter::operator==(IR::Type_Meter const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_Meter::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_Meter::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_Meter::Type_Meter(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_Meter::fromJSON(JSONLoader &json) { return new Type_Meter(json); }
bool IR::Type_Meter::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_Meter::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Meter::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Register::toString() const { return "register"_cs; }
void IR::Type_Register::dbprint(std::ostream &out) const { out << "register"; }
bool IR::Type_Register::operator==(IR::Type_Register const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_Register::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_Register::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_Register::Type_Register(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_Register::fromJSON(JSONLoader &json) { return new Type_Register(json); }
bool IR::Type_Register::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_Register::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Register::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_AnyTable::toString() const { return "table"_cs; }
void IR::Type_AnyTable::dbprint(std::ostream &out) const { out << "table"; }
bool IR::Type_AnyTable::operator==(IR::Type_AnyTable const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_AnyTable::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_AnyTable::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_AnyTable::Type_AnyTable(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_AnyTable::fromJSON(JSONLoader &json) { return new Type_AnyTable(json); }
bool IR::Type_AnyTable::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_AnyTable::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_AnyTable::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::HeaderOrMetadata::getAnnotations() const {
    return annotations;
}
IR::Vector<IR::Annotation> &IR::HeaderOrMetadata::getAnnotations() { return annotations; }
IR::HeaderOrMetadata::HeaderOrMetadata(IR::ID n, const IR::Type_StructLike *t)
    : type_name(t->name), name(n), type(t) {}
void IR::HeaderOrMetadata::dbprint(std::ostream &out) const { out << type_name << ' ' << name; }
bool IR::HeaderOrMetadata::operator==(IR::HeaderOrMetadata const &a) const {
    return this->typeId() == a.typeId() && type_name == a.type_name && name == a.name &&
           annotations == a.annotations && type == a.type;
}
bool IR::HeaderOrMetadata::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const HeaderOrMetadata &>(a_);
    return type_name == a.type_name && name == a.name && annotations.equiv(a.annotations) &&
           (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr);
}
void IR::HeaderOrMetadata::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
}
void IR::HeaderOrMetadata::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
}
void IR::HeaderOrMetadata::validate() const { annotations.validate(); }
void IR::HeaderOrMetadata::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " type_name=" << type_name;
    out << " name=" << name;
}
void IR::HeaderOrMetadata::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("type_name", type_name);
    json.emit("name", name);
    json.emit("annotations", annotations);
    if (type != nullptr) json.emit("type", type);
}
IR::HeaderOrMetadata::HeaderOrMetadata(JSONLoader &json) : Node(json) {
    json.load("type_name", type_name) || json.error("missing field type_name");
    json.load("name", name) || json.error("missing field name");
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("type", type);
}
bool IR::HeaderOrMetadata::operator==(IR::Node const &a) const { return a == *this; }
IR::Header::Header(IR::ID n, const IR::Type_Header *t) : HeaderOrMetadata(n, t) {}
bool IR::Header::operator==(IR::Header const &a) const {
    return HeaderOrMetadata::operator==(static_cast<const HeaderOrMetadata &>(a));
}
bool IR::Header::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!HeaderOrMetadata::equiv(a_)) return false;
    return true;
}
void IR::Header::toJSON(JSONGenerator &json) const { HeaderOrMetadata::toJSON(json); }
IR::Header::Header(JSONLoader &json) : HeaderOrMetadata(json) {}
IR::Node *IR::Header::fromJSON(JSONLoader &json) { return new Header(json); }
bool IR::Header::operator==(IR::HeaderOrMetadata const &a) const { return a == *this; }
bool IR::Header::operator==(IR::Node const &a) const { return a == *this; }
IR::HeaderStack::HeaderStack(IR::ID n, const IR::Type_Header *t, int sz)
    : HeaderOrMetadata(n, t), size(sz) {}
bool IR::HeaderStack::operator==(IR::HeaderStack const &a) const {
    return HeaderOrMetadata::operator==(static_cast<const HeaderOrMetadata &>(a)) && size == a.size;
}
bool IR::HeaderStack::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!HeaderOrMetadata::equiv(a_)) return false;
    auto &a = static_cast<const HeaderStack &>(a_);
    return size == a.size;
}
void IR::HeaderStack::dump_fields(std::ostream &out) const {
    HeaderOrMetadata::dump_fields(out);
    out << " size=" << size;
}
void IR::HeaderStack::toJSON(JSONGenerator &json) const {
    HeaderOrMetadata::toJSON(json);
    json.emit("size", size);
}
IR::HeaderStack::HeaderStack(JSONLoader &json) : HeaderOrMetadata(json) {
    json.load("size", size) || json.error("missing field size");
}
IR::Node *IR::HeaderStack::fromJSON(JSONLoader &json) { return new HeaderStack(json); }
bool IR::HeaderStack::operator==(IR::HeaderOrMetadata const &a) const { return a == *this; }
bool IR::HeaderStack::operator==(IR::Node const &a) const { return a == *this; }
IR::v1HeaderType::v1HeaderType(IR::Type_Struct const *m, IR::Type_Header const *h)
    : v1HeaderType(Util::SourceInfo(), m->name, m, h) {}
void IR::v1HeaderType::dbprint(std::ostream &out) const { out << "header " << name; }
bool IR::v1HeaderType::operator==(IR::v1HeaderType const &a) const {
    return this->typeId() == a.typeId() && name == a.name && as_metadata == a.as_metadata &&
           as_header == a.as_header;
}
bool IR::v1HeaderType::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const v1HeaderType &>(a_);
    return name == a.name &&
           (as_metadata ? a.as_metadata ? as_metadata->equiv(*a.as_metadata) : false
                        : a.as_metadata == nullptr) &&
           (as_header ? a.as_header ? as_header->equiv(*a.as_header) : false
                      : a.as_header == nullptr);
}
void IR::v1HeaderType::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    v.visit(as_metadata, "as_metadata");
    v.visit(as_header, "as_header");
}
void IR::v1HeaderType::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    v.visit(as_metadata, "as_metadata");
    v.visit(as_header, "as_header");
}
void IR::v1HeaderType::validate() const { CHECK_NULL(as_metadata); }
void IR::v1HeaderType::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
}
void IR::v1HeaderType::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    json.emit("as_metadata", as_metadata);
    if (as_header != nullptr) json.emit("as_header", as_header);
}
IR::v1HeaderType::v1HeaderType(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("as_metadata", as_metadata) || json.error("missing field as_metadata");
    json.load("as_header", as_header);
}
IR::Node *IR::v1HeaderType::fromJSON(JSONLoader &json) { return new v1HeaderType(json); }
bool IR::v1HeaderType::operator==(IR::Node const &a) const { return a == *this; }
IR::Metadata::Metadata(IR::ID n, const IR::Type_StructLike *t) : HeaderOrMetadata(n, t) {}
bool IR::Metadata::operator==(IR::Metadata const &a) const {
    return HeaderOrMetadata::operator==(static_cast<const HeaderOrMetadata &>(a));
}
bool IR::Metadata::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!HeaderOrMetadata::equiv(a_)) return false;
    return true;
}
void IR::Metadata::toJSON(JSONGenerator &json) const { HeaderOrMetadata::toJSON(json); }
IR::Metadata::Metadata(JSONLoader &json) : HeaderOrMetadata(json) {}
IR::Node *IR::Metadata::fromJSON(JSONLoader &json) { return new Metadata(json); }
bool IR::Metadata::operator==(IR::HeaderOrMetadata const &a) const { return a == *this; }
bool IR::Metadata::operator==(IR::Node const &a) const { return a == *this; }
bool IR::HeaderRef::operator==(IR::HeaderRef const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a));
}
bool IR::HeaderRef::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    return true;
}
void IR::HeaderRef::toJSON(JSONGenerator &json) const { Expression::toJSON(json); }
IR::HeaderRef::HeaderRef(JSONLoader &json) : Expression(json) {}
bool IR::HeaderRef::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::HeaderRef::operator==(IR::Node const &a) const { return a == *this; }
const IR::HeaderOrMetadata *IR::ConcreteHeaderRef::baseRef() const { return ref; }
cstring IR::ConcreteHeaderRef::toString() const { return ref->name; }
void IR::ConcreteHeaderRef::dbprint(std::ostream &out) const { out << ref->name; }
bool IR::ConcreteHeaderRef::operator==(IR::ConcreteHeaderRef const &a) const {
    return HeaderRef::operator==(static_cast<const HeaderRef &>(a)) && ref == a.ref;
}
bool IR::ConcreteHeaderRef::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!HeaderRef::equiv(a_)) return false;
    auto &a = static_cast<const ConcreteHeaderRef &>(a_);
    return (ref ? a.ref ? ref->equiv(*a.ref) : false : a.ref == nullptr);
}
void IR::ConcreteHeaderRef::visit_children(Visitor &v, char const *n) {
    (void)n;
    HeaderRef::visit_children(v, n);
    v.visit(ref, "ref");
}
void IR::ConcreteHeaderRef::visit_children(Visitor &v, char const *n) const {
    (void)n;
    HeaderRef::visit_children(v, n);
    v.visit(ref, "ref");
}
void IR::ConcreteHeaderRef::validate() const { CHECK_NULL(ref); }
void IR::ConcreteHeaderRef::toJSON(JSONGenerator &json) const {
    HeaderRef::toJSON(json);
    json.emit("ref", ref);
}
IR::ConcreteHeaderRef::ConcreteHeaderRef(JSONLoader &json) : HeaderRef(json) {
    json.load("ref", ref) || json.error("missing field ref");
}
IR::Node *IR::ConcreteHeaderRef::fromJSON(JSONLoader &json) { return new ConcreteHeaderRef(json); }
bool IR::ConcreteHeaderRef::operator==(IR::HeaderRef const &a) const { return a == *this; }
bool IR::ConcreteHeaderRef::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::ConcreteHeaderRef::operator==(IR::Node const &a) const { return a == *this; }
const IR::Expression *IR::HeaderStackItemRef::base() const { return base_; }
/// Returns `nullptr` if the base is not `HeaderOrMetadata` (e.g. when this
/// is stack ref of an expression such as `lookahead`).
const IR::HeaderOrMetadata *IR::HeaderStackItemRef::baseRef() const {
    auto hdrRef = base_->to<HeaderRef>();
    return hdrRef ? hdrRef->baseRef() : nullptr;
}
const IR::Expression *IR::HeaderStackItemRef::index() const { return index_; }
void IR::HeaderStackItemRef::set_base(const IR::Expression *b) { base_ = b; }
cstring IR::HeaderStackItemRef::toString() const {
    return base_->toString() + "[" + index_->toString() + "]";
}
bool IR::HeaderStackItemRef::operator==(IR::HeaderStackItemRef const &a) const {
    return HeaderRef::operator==(static_cast<const HeaderRef &>(a)) && base_ == a.base_ &&
           index_ == a.index_;
}
bool IR::HeaderStackItemRef::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!HeaderRef::equiv(a_)) return false;
    auto &a = static_cast<const HeaderStackItemRef &>(a_);
    return (base_ ? a.base_ ? base_->equiv(*a.base_) : false : a.base_ == nullptr) &&
           (index_ ? a.index_ ? index_->equiv(*a.index_) : false : a.index_ == nullptr);
}
void IR::HeaderStackItemRef::visit_children(Visitor &v, char const *n) {
    (void)n;
    HeaderRef::visit_children(v, n);
    v.visit(base_, "base_");
    v.visit(index_, "index_");
}
void IR::HeaderStackItemRef::visit_children(Visitor &v, char const *n) const {
    (void)n;
    HeaderRef::visit_children(v, n);
    v.visit(base_, "base_");
    v.visit(index_, "index_");
}
void IR::HeaderStackItemRef::validate() const {
    CHECK_NULL(base_);
    CHECK_NULL(index_);
}
void IR::HeaderStackItemRef::toJSON(JSONGenerator &json) const {
    HeaderRef::toJSON(json);
    json.emit("base_", base_);
    json.emit("index_", index_);
}
IR::HeaderStackItemRef::HeaderStackItemRef(JSONLoader &json) : HeaderRef(json) {
    json.load("base_", base_) || json.error("missing field base_");
    json.load("index_", index_) || json.error("missing field index_");
}
IR::Node *IR::HeaderStackItemRef::fromJSON(JSONLoader &json) {
    return new HeaderStackItemRef(json);
}
bool IR::HeaderStackItemRef::operator==(IR::HeaderRef const &a) const { return a == *this; }
bool IR::HeaderStackItemRef::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::HeaderStackItemRef::operator==(IR::Node const &a) const { return a == *this; }
void IR::If::visit_children(Visitor &v, char const *n) {
    v.visit(pred, "pred");
    SplitFlowVisit<Vector<Expression>>(v, ifTrue, ifFalse).run_visit();
    Expression::visit_children(v, n);
}
void IR::If::visit_children(Visitor &v, char const *n) const {
    v.visit(pred, "pred");
    SplitFlowVisit<Vector<Expression>>(v, ifTrue, ifFalse).run_visit();
    Expression::visit_children(v, n);
}
bool IR::If::operator==(IR::If const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && pred == a.pred &&
           ifTrue == a.ifTrue && ifFalse == a.ifFalse;
}
bool IR::If::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const If &>(a_);
    return (pred ? a.pred ? pred->equiv(*a.pred) : false : a.pred == nullptr) &&
           (ifTrue ? a.ifTrue ? ifTrue->equiv(*a.ifTrue) : false : a.ifTrue == nullptr) &&
           (ifFalse ? a.ifFalse ? ifFalse->equiv(*a.ifFalse) : false : a.ifFalse == nullptr);
}
void IR::If::validate() const { CHECK_NULL(pred); }
void IR::If::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("pred", pred);
    if (ifTrue != nullptr) json.emit("ifTrue", ifTrue);
    if (ifFalse != nullptr) json.emit("ifFalse", ifFalse);
}
IR::If::If(JSONLoader &json) : Expression(json) {
    json.load("pred", pred) || json.error("missing field pred");
    json.load("ifTrue", ifTrue);
    json.load("ifFalse", ifFalse);
}
IR::Node *IR::If::fromJSON(JSONLoader &json) { return new If(json); }
bool IR::If::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::If::operator==(IR::Node const &a) const { return a == *this; }
IR::NamedCond::NamedCond(IR::If const &i) : If(i), name(unique_name()) {}
bool IR::NamedCond::operator==(IR::NamedCond const &a) const {
    return If::operator==(static_cast<const If &>(a));
}
bool IR::NamedCond::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!If::equiv(a_)) return false;
    auto &a = static_cast<const NamedCond &>(a_);
    return name == a.name;
}
void IR::NamedCond::dump_fields(std::ostream &out) const {
    If::dump_fields(out);
    out << " name=" << name;
}
void IR::NamedCond::toJSON(JSONGenerator &json) const {
    If::toJSON(json);
    json.emit("name", name);
}
IR::NamedCond::NamedCond(JSONLoader &json) : If(json) {
    json.load("name", name) || json.error("missing field name");
}
IR::Node *IR::NamedCond::fromJSON(JSONLoader &json) { return new NamedCond(json); }
bool IR::NamedCond::operator==(IR::If const &a) const { return a == *this; }
bool IR::NamedCond::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::NamedCond::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Apply::operator==(IR::Apply const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && name == a.name &&
           actions == a.actions && position == a.position;
}
bool IR::Apply::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const Apply &>(a_);
    return name == a.name && actions.equiv(a.actions) && position.equiv(a.position);
}
void IR::Apply::visit_children(Visitor &v, char const *n) {
    (void)n;
    Expression::visit_children(v, n);
    actions.visit_children(v, "actions");
    position.visit_children(v, "position");
}
void IR::Apply::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Expression::visit_children(v, n);
    actions.visit_children(v, "actions");
    position.visit_children(v, "position");
}
void IR::Apply::validate() const {
    actions.validate();
    position.validate();
}
void IR::Apply::dump_fields(std::ostream &out) const {
    Expression::dump_fields(out);
    out << " name=" << name;
}
void IR::Apply::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("name", name);
    json.emit("actions", actions);
    json.emit("position", position);
}
IR::Apply::Apply(JSONLoader &json) : Expression(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("actions", actions) || json.error("missing field actions");
    json.load("position", position) || json.error("missing field position");
}
IR::Node *IR::Apply::fromJSON(JSONLoader &json) { return new Apply(json); }
bool IR::Apply::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Apply::operator==(IR::Node const &a) const { return a == *this; }
IR::Primitive::Primitive(cstring n, const IR::Vector<IR::Expression> *l) : name(n) {
    if (l)
        for (auto e : *l) operands.push_back(e);
}
IR::Primitive::Primitive(Util::SourceInfo si, cstring n, const IR::Vector<IR::Expression> *l)
    : Operation(si), name(n) {
    if (l)
        for (auto e : *l) operands.push_back(e);
}
IR::Primitive::Primitive(cstring n, const IR::Expression *a1) : name(n) { operands.push_back(a1); }
IR::Primitive::Primitive(Util::SourceInfo si, cstring n, const IR::Expression *a1)
    : Operation(si), name(n) {
    operands.push_back(a1);
}
IR::Primitive::Primitive(cstring n, const IR::Expression *a1, const IR::Expression *a2) : name(n) {
    operands.push_back(a1);
    operands.push_back(a2);
}
IR::Primitive::Primitive(Util::SourceInfo si, cstring n, const IR::Expression *a1,
                         const IR::Expression *a2)
    : Operation(si), name(n) {
    operands.push_back(a1);
    operands.push_back(a2);
}
IR::Primitive::Primitive(cstring n, const IR::Expression *a1, const IR::Vector<IR::Expression> *a2)
    : name(n) {
    operands.push_back(a1);
    if (a2)
        for (auto e : *a2) operands.push_back(e);
}
IR::Primitive::Primitive(Util::SourceInfo si, cstring n, const IR::Expression *a1,
                         const IR::Vector<IR::Expression> *a2)
    : Operation(si), name(n) {
    operands.push_back(a1);
    if (a2)
        for (auto e : *a2) operands.push_back(e);
}
IR::Primitive::Primitive(cstring n, const IR::Expression *a1, const IR::Expression *a2,
                         const IR::Expression *a3)
    : name(n) {
    operands.push_back(a1);
    operands.push_back(a2);
    operands.push_back(a3);
}
IR::Primitive::Primitive(Util::SourceInfo si, cstring n, const IR::Expression *a1,
                         const IR::Expression *a2, const IR::Expression *a3)
    : Operation(si), name(n) {
    operands.push_back(a1);
    operands.push_back(a2);
    operands.push_back(a3);
}
IRNODE_DEFINE_APPLY_OVERLOAD(Primitive, , )
bool IR::Primitive::operator==(IR::Primitive const &a) const {
    return Operation::operator==(static_cast<const Operation &>(a)) && name == a.name &&
           operands == a.operands;
}
bool IR::Primitive::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation::equiv(a_)) return false;
    auto &a = static_cast<const Primitive &>(a_);
    return name == a.name && operands.equiv(a.operands);
}
void IR::Primitive::visit_children(Visitor &v, char const *n) {
    (void)n;
    Operation::visit_children(v, n);
    operands.visit_children(v, "operands");
}
void IR::Primitive::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Operation::visit_children(v, n);
    operands.visit_children(v, "operands");
}
void IR::Primitive::validate() const { operands.validate(); }
void IR::Primitive::dump_fields(std::ostream &out) const {
    Operation::dump_fields(out);
    out << " name=" << name;
}
void IR::Primitive::toJSON(JSONGenerator &json) const {
    Operation::toJSON(json);
    json.emit("name", name);
    json.emit("operands", operands);
}
IR::Primitive::Primitive(JSONLoader &json) : Operation(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("operands", operands) || json.error("missing field operands");
}
IR::Node *IR::Primitive::fromJSON(JSONLoader &json) { return new Primitive(json); }
bool IR::Primitive::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::Primitive::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Primitive::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::FieldList::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::FieldList::getAnnotations() { return annotations; }
bool IR::FieldList::operator==(IR::FieldList const &a) const {
    return this->typeId() == a.typeId() && name == a.name && payload == a.payload &&
           annotations == a.annotations && fields == a.fields;
}
bool IR::FieldList::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const FieldList &>(a_);
    return name == a.name && payload == a.payload && annotations.equiv(a.annotations) &&
           fields.equiv(a.fields);
}
void IR::FieldList::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    fields.visit_children(v, "fields");
}
void IR::FieldList::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    fields.visit_children(v, "fields");
}
void IR::FieldList::validate() const {
    annotations.validate();
    fields.validate();
}
void IR::FieldList::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
    out << " payload=" << payload;
}
void IR::FieldList::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    json.emit("payload", payload);
    json.emit("annotations", annotations);
    json.emit("fields", fields);
}
IR::FieldList::FieldList(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("payload", payload) || json.error("missing field payload");
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("fields", fields) || json.error("missing field fields");
}
IR::Node *IR::FieldList::fromJSON(JSONLoader &json) { return new FieldList(json); }
bool IR::FieldList::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::FieldListCalculation::getAnnotations() const {
    return annotations;
}
IR::Vector<IR::Annotation> &IR::FieldListCalculation::getAnnotations() { return annotations; }
bool IR::FieldListCalculation::operator==(IR::FieldListCalculation const &a) const {
    return this->typeId() == a.typeId() && name == a.name && input == a.input &&
           input_fields == a.input_fields && algorithm == a.algorithm &&
           output_width == a.output_width && annotations == a.annotations;
}
bool IR::FieldListCalculation::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const FieldListCalculation &>(a_);
    return name == a.name &&
           (input ? a.input ? input->equiv(*a.input) : false : a.input == nullptr) &&
           (input_fields ? a.input_fields ? input_fields->equiv(*a.input_fields) : false
                         : a.input_fields == nullptr) &&
           (algorithm ? a.algorithm ? algorithm->equiv(*a.algorithm) : false
                      : a.algorithm == nullptr) &&
           output_width == a.output_width && annotations.equiv(a.annotations);
}
void IR::FieldListCalculation::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    v.visit(input, "input");
    v.visit(input_fields, "input_fields");
    v.visit(algorithm, "algorithm");
    annotations.visit_children(v, "annotations");
}
void IR::FieldListCalculation::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    v.visit(input, "input");
    v.visit(input_fields, "input_fields");
    v.visit(algorithm, "algorithm");
    annotations.visit_children(v, "annotations");
}
void IR::FieldListCalculation::validate() const { annotations.validate(); }
void IR::FieldListCalculation::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
    out << " output_width=" << output_width;
}
void IR::FieldListCalculation::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    if (input != nullptr) json.emit("input", input);
    if (input_fields != nullptr) json.emit("input_fields", input_fields);
    if (algorithm != nullptr) json.emit("algorithm", algorithm);
    json.emit("output_width", output_width);
    json.emit("annotations", annotations);
}
IR::FieldListCalculation::FieldListCalculation(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("input", input);
    json.load("input_fields", input_fields);
    json.load("algorithm", algorithm);
    json.load("output_width", output_width) || json.error("missing field output_width");
    json.load("annotations", annotations) || json.error("missing field annotations");
}
IR::Node *IR::FieldListCalculation::fromJSON(JSONLoader &json) {
    return new FieldListCalculation(json);
}
bool IR::FieldListCalculation::operator==(IR::Node const &a) const { return a == *this; }
IR::CalculatedField::update_or_verify::update_or_verify() {}

bool IR::CalculatedField::update_or_verify::operator==(
    IR::CalculatedField::update_or_verify const &a) const {
    return update == a.update && name == a.name && cond == a.cond;
}
void IR::CalculatedField::update_or_verify::toJSON(JSONGenerator &json) const {
    json.emit("update", update);
    json.emit("name", name);
    json.emit("cond", cond);
}
IR::CalculatedField::update_or_verify::update_or_verify(JSONLoader &json) {
    json.load("update", update) || json.error("missing field update");
    json.load("name", name) || json.error("missing field name");
    json.load("cond", cond) || json.error("missing field cond");
}
IR::CalculatedField::update_or_verify *IR::CalculatedField::update_or_verify::fromJSON(
    JSONLoader &json) {
    return new update_or_verify(json);
}
IR::Vector<IR::Annotation> const &IR::CalculatedField::getAnnotations() const {
    return annotations;
}
IR::Vector<IR::Annotation> &IR::CalculatedField::getAnnotations() { return annotations; }
void IR::CalculatedField::visit_children(Visitor &v, char const *n) {
    (void)n;
    v.visit(field, "field");
    for (auto &s : specs) v.visit(s.cond, s.name.name.c_str());
    v.visit(annotations, "annotations");
}
void IR::CalculatedField::visit_children(Visitor &v, char const *n) const {
    (void)n;
    v.visit(field, "field");
    for (auto &s : specs) v.visit(s.cond, s.name.name.c_str());
    v.visit(annotations, "annotations");
}
bool IR::CalculatedField::operator==(IR::CalculatedField const &a) const {
    return this->typeId() == a.typeId() && field == a.field && specs == a.specs &&
           annotations == a.annotations;
}
bool IR::CalculatedField::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const CalculatedField &>(a_);
    return (field ? a.field ? field->equiv(*a.field) : false : a.field == nullptr) &&
           specs == a.specs && annotations.equiv(a.annotations);
}
void IR::CalculatedField::validate() const { annotations.validate(); }
void IR::CalculatedField::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    if (field != nullptr) json.emit("field", field);
    json.emit("specs", specs);
    json.emit("annotations", annotations);
}
IR::CalculatedField::CalculatedField(JSONLoader &json) : Node(json) {
    json.load("field", field);
    json.load("specs", specs) || json.error("missing field specs");
    json.load("annotations", annotations) || json.error("missing field annotations");
}
IR::Node *IR::CalculatedField::fromJSON(JSONLoader &json) { return new CalculatedField(json); }
bool IR::CalculatedField::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::ParserValueSet::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::ParserValueSet::getAnnotations() { return annotations; }
void IR::ParserValueSet::dbprint(std::ostream &out) const {
    out << node_type_name() << " " << name;
}
cstring IR::ParserValueSet::toString() const { return node_type_name() + " " + name; }
bool IR::ParserValueSet::operator==(IR::ParserValueSet const &a) const {
    return this->typeId() == a.typeId() && name == a.name && annotations == a.annotations;
}
bool IR::ParserValueSet::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const ParserValueSet &>(a_);
    return name == a.name && annotations.equiv(a.annotations);
}
void IR::ParserValueSet::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
}
void IR::ParserValueSet::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
}
void IR::ParserValueSet::validate() const { annotations.validate(); }
void IR::ParserValueSet::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
}
void IR::ParserValueSet::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    json.emit("annotations", annotations);
}
IR::ParserValueSet::ParserValueSet(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("annotations", annotations) || json.error("missing field annotations");
}
IR::Node *IR::ParserValueSet::fromJSON(JSONLoader &json) { return new ParserValueSet(json); }
bool IR::ParserValueSet::operator==(IR::Node const &a) const { return a == *this; }
bool IR::CaseEntry::operator==(IR::CaseEntry const &a) const {
    return this->typeId() == a.typeId() && values == a.values && action == a.action;
}
bool IR::CaseEntry::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const CaseEntry &>(a_);
    return values == a.values && action == a.action;
}
void IR::CaseEntry::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " action=" << action;
}
void IR::CaseEntry::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("values", values);
    json.emit("action", action);
}
IR::CaseEntry::CaseEntry(JSONLoader &json) : Node(json) {
    json.load("values", values) || json.error("missing field values");
    json.load("action", action) || json.error("missing field action");
}
IR::Node *IR::CaseEntry::fromJSON(JSONLoader &json) { return new CaseEntry(json); }
bool IR::CaseEntry::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::V1Parser::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::V1Parser::getAnnotations() { return annotations; }
cstring IR::V1Parser::toString() const { return node_type_name() + " " + name; }
bool IR::V1Parser::operator==(IR::V1Parser const &a) const {
    return this->typeId() == a.typeId() && name == a.name && stmts == a.stmts &&
           select == a.select && cases == a.cases && default_return == a.default_return &&
           parse_error == a.parse_error && drop == a.drop && annotations == a.annotations;
}
bool IR::V1Parser::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const V1Parser &>(a_);
    return name == a.name && stmts.equiv(a.stmts) &&
           (select ? a.select ? select->equiv(*a.select) : false : a.select == nullptr) &&
           (cases ? a.cases ? cases->equiv(*a.cases) : false : a.cases == nullptr) &&
           default_return == a.default_return && parse_error == a.parse_error && drop == a.drop &&
           annotations.equiv(a.annotations);
}
void IR::V1Parser::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    stmts.visit_children(v, "stmts");
    v.visit(select, "select");
    v.visit(cases, "cases");
    annotations.visit_children(v, "annotations");
}
void IR::V1Parser::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    stmts.visit_children(v, "stmts");
    v.visit(select, "select");
    v.visit(cases, "cases");
    annotations.visit_children(v, "annotations");
}
void IR::V1Parser::validate() const {
    stmts.validate();
    annotations.validate();
}
void IR::V1Parser::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
    out << " default_return=" << default_return;
    out << " parse_error=" << parse_error;
    out << " drop=" << drop;
}
void IR::V1Parser::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    json.emit("stmts", stmts);
    if (select != nullptr) json.emit("select", select);
    if (cases != nullptr) json.emit("cases", cases);
    json.emit("default_return", default_return);
    json.emit("parse_error", parse_error);
    json.emit("drop", drop);
    json.emit("annotations", annotations);
}
IR::V1Parser::V1Parser(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("stmts", stmts) || json.error("missing field stmts");
    json.load("select", select);
    json.load("cases", cases);
    json.load("default_return", default_return) || json.error("missing field default_return");
    json.load("parse_error", parse_error) || json.error("missing field parse_error");
    json.load("drop", drop) || json.error("missing field drop");
    json.load("annotations", annotations) || json.error("missing field annotations");
}
IR::Node *IR::V1Parser::fromJSON(JSONLoader &json) { return new V1Parser(json); }
bool IR::V1Parser::operator==(IR::Node const &a) const { return a == *this; }
bool IR::ParserException::operator==(IR::ParserException const &a) const {
    return this->typeId() == a.typeId();
}
bool IR::ParserException::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    return true;
}
void IR::ParserException::toJSON(JSONGenerator &json) const { Node::toJSON(json); }
IR::ParserException::ParserException(JSONLoader &json) : Node(json) {}
IR::Node *IR::ParserException::fromJSON(JSONLoader &json) { return new ParserException(json); }
bool IR::ParserException::operator==(IR::Node const &a) const { return a == *this; }
IR::ID IR::Attached::Name() const { return name; }
const IR::Type *IR::Attached::getType() const { return Type_Unknown::get(); }
IR::Vector<IR::Annotation> const &IR::Attached::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Attached::getAnnotations() { return annotations; }
bool IR::Attached::indexed() const { return false; }
IR::Attached *IR::Attached::clone_rename(char const *ext) const {
    Attached *rv = clone();
    rv->name = ID(Util::SourceInfo(), rv->name.name + ext);
    return rv;
}
void IR::Attached::dbprint(std::ostream &out) const { out << node_type_name() << " " << name; }
cstring IR::Attached::toString() const { return node_type_name() + " " + name; }
bool IR::Attached::operator==(IR::Attached const &a) const {
    return this->typeId() == a.typeId() && name == a.name && annotations == a.annotations;
}
bool IR::Attached::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const Attached &>(a_);
    return name == a.name && annotations.equiv(a.annotations);
}
void IR::Attached::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
}
void IR::Attached::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
}
void IR::Attached::validate() const { annotations.validate(); }
void IR::Attached::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
}
void IR::Attached::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    json.emit("annotations", annotations);
}
IR::Attached::Attached(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("annotations", annotations) || json.error("missing field annotations");
}
bool IR::Attached::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Stateful::indexed() const { return !direct; }

bool IR::Stateful::operator==(IR::Stateful const &a) const {
    return Attached::operator==(static_cast<const Attached &>(a)) && table == a.table &&
           direct == a.direct && saturating == a.saturating && instance_count == a.instance_count;
}
bool IR::Stateful::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Attached::equiv(a_)) return false;
    auto &a = static_cast<const Stateful &>(a_);
    return table == a.table && direct == a.direct && saturating == a.saturating &&
           instance_count == a.instance_count;
}
void IR::Stateful::dump_fields(std::ostream &out) const {
    Attached::dump_fields(out);
    out << " table=" << table;
    out << " direct=" << direct;
    out << " saturating=" << saturating;
    out << " instance_count=" << instance_count;
}
void IR::Stateful::toJSON(JSONGenerator &json) const {
    Attached::toJSON(json);
    json.emit("table", table);
    json.emit("direct", direct);
    json.emit("saturating", saturating);
    json.emit("instance_count", instance_count);
}
IR::Stateful::Stateful(JSONLoader &json) : Attached(json) {
    json.load("table", table) || json.error("missing field table");
    json.load("direct", direct) || json.error("missing field direct");
    json.load("saturating", saturating) || json.error("missing field saturating");
    json.load("instance_count", instance_count) || json.error("missing field instance_count");
}
bool IR::Stateful::operator==(IR::Attached const &a) const { return a == *this; }
bool IR::Stateful::operator==(IR::Node const &a) const { return a == *this; }
void IR::CounterOrMeter::settype(cstring t) {
    if (strcasecmp(t.c_str(), "packets") == 0)
        type = CounterType::PACKETS;
    else if (strcasecmp(t.c_str(), "bytes") == 0)
        type = CounterType::BYTES;
    else if (strcasecmp(t.c_str(), "packets_and_bytes") == 0 ||
             strcasecmp(t.c_str(), "PacketAndBytes") == 0)
        type = CounterType::BOTH;
    else
        error(ErrorType::ERR_UNKNOWN, "%s: Unknown type %s", srcInfo, t);
}

bool IR::CounterOrMeter::operator==(IR::CounterOrMeter const &a) const {
    return Stateful::operator==(static_cast<const Stateful &>(a)) && type == a.type;
}
bool IR::CounterOrMeter::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Stateful::equiv(a_)) return false;
    auto &a = static_cast<const CounterOrMeter &>(a_);
    return type == a.type;
}
void IR::CounterOrMeter::dump_fields(std::ostream &out) const {
    Stateful::dump_fields(out);
    out << " type=" << type;
}
void IR::CounterOrMeter::toJSON(JSONGenerator &json) const {
    Stateful::toJSON(json);
    json.emit("type", type);
}
IR::CounterOrMeter::CounterOrMeter(JSONLoader &json) : Stateful(json) {
    json.load("type", type) || json.error("missing field type");
}
bool IR::CounterOrMeter::operator==(IR::Stateful const &a) const { return a == *this; }
bool IR::CounterOrMeter::operator==(IR::Attached const &a) const { return a == *this; }
bool IR::CounterOrMeter::operator==(IR::Node const &a) const { return a == *this; }
char const *IR::Counter::kind() const { return "stats"; }
IR::Type const *IR::Counter::getType() const { return Type_Counter::get(); }
bool IR::Counter::operator==(IR::Counter const &a) const {
    return CounterOrMeter::operator==(static_cast<const CounterOrMeter &>(a)) &&
           max_width == a.max_width && min_width == a.min_width;
}
bool IR::Counter::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!CounterOrMeter::equiv(a_)) return false;
    auto &a = static_cast<const Counter &>(a_);
    return max_width == a.max_width && min_width == a.min_width;
}
void IR::Counter::dump_fields(std::ostream &out) const {
    CounterOrMeter::dump_fields(out);
    out << " max_width=" << max_width;
    out << " min_width=" << min_width;
}
void IR::Counter::toJSON(JSONGenerator &json) const {
    CounterOrMeter::toJSON(json);
    json.emit("max_width", max_width);
    json.emit("min_width", min_width);
}
IR::Counter::Counter(JSONLoader &json) : CounterOrMeter(json) {
    json.load("max_width", max_width) || json.error("missing field max_width");
    json.load("min_width", min_width) || json.error("missing field min_width");
}
IR::Node *IR::Counter::fromJSON(JSONLoader &json) { return new Counter(json); }
bool IR::Counter::operator==(IR::CounterOrMeter const &a) const { return a == *this; }
bool IR::Counter::operator==(IR::Stateful const &a) const { return a == *this; }
bool IR::Counter::operator==(IR::Attached const &a) const { return a == *this; }
bool IR::Counter::operator==(IR::Node const &a) const { return a == *this; }
char const *IR::Meter::kind() const { return "meter"; }
const IR::Type *IR::Meter::getType() const { return Type_Meter::get(); }
bool IR::Meter::operator==(IR::Meter const &a) const {
    return CounterOrMeter::operator==(static_cast<const CounterOrMeter &>(a)) &&
           result == a.result && pre_color == a.pre_color && implementation == a.implementation;
}
bool IR::Meter::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!CounterOrMeter::equiv(a_)) return false;
    auto &a = static_cast<const Meter &>(a_);
    return (result ? a.result ? result->equiv(*a.result) : false : a.result == nullptr) &&
           (pre_color ? a.pre_color ? pre_color->equiv(*a.pre_color) : false
                      : a.pre_color == nullptr) &&
           implementation == a.implementation;
}
void IR::Meter::visit_children(Visitor &v, char const *n) {
    (void)n;
    CounterOrMeter::visit_children(v, n);
    v.visit(result, "result");
    v.visit(pre_color, "pre_color");
}
void IR::Meter::visit_children(Visitor &v, char const *n) const {
    (void)n;
    CounterOrMeter::visit_children(v, n);
    v.visit(result, "result");
    v.visit(pre_color, "pre_color");
}
void IR::Meter::dump_fields(std::ostream &out) const {
    CounterOrMeter::dump_fields(out);
    out << " implementation=" << implementation;
}
void IR::Meter::toJSON(JSONGenerator &json) const {
    CounterOrMeter::toJSON(json);
    if (result != nullptr) json.emit("result", result);
    if (pre_color != nullptr) json.emit("pre_color", pre_color);
    json.emit("implementation", implementation);
}
IR::Meter::Meter(JSONLoader &json) : CounterOrMeter(json) {
    json.load("result", result);
    json.load("pre_color", pre_color);
    json.load("implementation", implementation) || json.error("missing field implementation");
}
IR::Node *IR::Meter::fromJSON(JSONLoader &json) { return new Meter(json); }
bool IR::Meter::operator==(IR::CounterOrMeter const &a) const { return a == *this; }
bool IR::Meter::operator==(IR::Stateful const &a) const { return a == *this; }
bool IR::Meter::operator==(IR::Attached const &a) const { return a == *this; }
bool IR::Meter::operator==(IR::Node const &a) const { return a == *this; }
char const *IR::Register::kind() const { return "register"; }
const IR::Type *IR::Register::getType() const { return Type_Register::get(); }
bool IR::Register::operator==(IR::Register const &a) const {
    return Stateful::operator==(static_cast<const Stateful &>(a)) && layout == a.layout &&
           width == a.width && signed_ == a.signed_;
}
bool IR::Register::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Stateful::equiv(a_)) return false;
    auto &a = static_cast<const Register &>(a_);
    return layout == a.layout && width == a.width && signed_ == a.signed_;
}
void IR::Register::dump_fields(std::ostream &out) const {
    Stateful::dump_fields(out);
    out << " layout=" << layout;
    out << " width=" << width;
    out << " signed_=" << signed_;
}
void IR::Register::toJSON(JSONGenerator &json) const {
    Stateful::toJSON(json);
    json.emit("layout", layout);
    json.emit("width", width);
    json.emit("signed_", signed_);
}
IR::Register::Register(JSONLoader &json) : Stateful(json) {
    json.load("layout", layout) || json.error("missing field layout");
    json.load("width", width) || json.error("missing field width");
    json.load("signed_", signed_) || json.error("missing field signed_");
}
IR::Node *IR::Register::fromJSON(JSONLoader &json) { return new Register(json); }
bool IR::Register::operator==(IR::Stateful const &a) const { return a == *this; }
bool IR::Register::operator==(IR::Attached const &a) const { return a == *this; }
bool IR::Register::operator==(IR::Node const &a) const { return a == *this; }
bool IR::PrimitiveAction::operator==(IR::PrimitiveAction const &a) const {
    return this->typeId() == a.typeId();
}
bool IR::PrimitiveAction::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    return true;
}
void IR::PrimitiveAction::toJSON(JSONGenerator &json) const { Node::toJSON(json); }
IR::PrimitiveAction::PrimitiveAction(JSONLoader &json) : Node(json) {}
IR::Node *IR::PrimitiveAction::fromJSON(JSONLoader &json) { return new PrimitiveAction(json); }
bool IR::PrimitiveAction::operator==(IR::Node const &a) const { return a == *this; }
IR::NameList::NameList(Util::SourceInfo si, cstring n) { names.emplace_back(si, n); }
IR::NameList::NameList(Util::SourceInfo si, IR::ID n) { names.emplace_back(si, n); }
void IR::NameList::dump_fields(std::ostream &out) const { out << "names=" << names; }
bool IR::NameList::operator==(IR::NameList const &a) const {
    return this->typeId() == a.typeId() && names == a.names;
}
bool IR::NameList::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const NameList &>(a_);
    return names == a.names;
}
void IR::NameList::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("names", names);
}
IR::NameList::NameList(JSONLoader &json) : Node(json) {
    json.load("names", names) || json.error("missing field names");
}
IR::Node *IR::NameList::fromJSON(JSONLoader &json) { return new NameList(json); }
bool IR::NameList::operator==(IR::Node const &a) const { return a == *this; }
void IR::ActionArg::dbprint(std::ostream &out) const { out << action_name << ':' << name; }
cstring IR::ActionArg::toString() const { return name.name; }
bool IR::ActionArg::operator==(IR::ActionArg const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) &&
           action_name == a.action_name && name == a.name && read == a.read && write == a.write;
}
bool IR::ActionArg::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const ActionArg &>(a_);
    return action_name == a.action_name && name == a.name && read == a.read && write == a.write;
}
void IR::ActionArg::dump_fields(std::ostream &out) const {
    Expression::dump_fields(out);
    out << " action_name=" << action_name;
    out << " name=" << name;
    out << " read=" << read;
    out << " write=" << write;
}
void IR::ActionArg::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("action_name", action_name);
    json.emit("name", name);
    json.emit("read", read);
    json.emit("write", write);
}
IR::ActionArg::ActionArg(JSONLoader &json) : Expression(json) {
    json.load("action_name", action_name) || json.error("missing field action_name");
    json.load("name", name) || json.error("missing field name");
    json.load("read", read) || json.error("missing field read");
    json.load("write", write) || json.error("missing field write");
}
IR::Node *IR::ActionArg::fromJSON(JSONLoader &json) { return new ActionArg(json); }
bool IR::ActionArg::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::ActionArg::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::ActionFunction::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::ActionFunction::getAnnotations() { return annotations; }
const IR::ActionArg *IR::ActionFunction::arg(cstring n) const {
    for (auto a : args)
        if (a->name == n) return a;
    return nullptr;
}
void IR::ActionFunction::visit_children(Visitor &v, char const *n) {
    (void)n;
    v.visit(action, "action");
    // DANGER -- visiting action first so type inferencing will push types to
    // DANGER -- action args based on use.  This is immoral.
    for (auto &a : args) v.visit(a, "arg");
    v.visit(annotations, "annotations");
}
void IR::ActionFunction::visit_children(Visitor &v, char const *n) const {
    (void)n;
    v.visit(action, "action");
    // DANGER -- visiting action first so type inferencing will push types to
    // DANGER -- action args based on use.  This is immoral.
    for (auto &a : args) v.visit(a, "arg");
    v.visit(annotations, "annotations");
}
cstring IR::ActionFunction::toString() const {
    return "action "_cs + name + " {\n"_cs + cstring::join(action.begin(), action.end(), ";\n") +
           " }"_cs;
}
bool IR::ActionFunction::operator==(IR::ActionFunction const &a) const {
    return this->typeId() == a.typeId() && name == a.name && action == a.action && args == a.args &&
           annotations == a.annotations;
}
bool IR::ActionFunction::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const ActionFunction &>(a_);
    return name == a.name && action.equiv(a.action) && args == a.args &&
           annotations.equiv(a.annotations);
}
void IR::ActionFunction::validate() const {
    action.validate();
    annotations.validate();
}
void IR::ActionFunction::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
}
void IR::ActionFunction::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    json.emit("action", action);
    json.emit("args", args);
    json.emit("annotations", annotations);
}
IR::ActionFunction::ActionFunction(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("action", action) || json.error("missing field action");
    json.load("args", args) || json.error("missing field args");
    json.load("annotations", annotations) || json.error("missing field annotations");
}
IR::Node *IR::ActionFunction::fromJSON(JSONLoader &json) { return new ActionFunction(json); }
bool IR::ActionFunction::operator==(IR::Node const &a) const { return a == *this; }
char const *IR::ActionProfile::kind() const { return "action_profile"; }
bool IR::ActionProfile::indexed() const { return true; }
bool IR::ActionProfile::operator==(IR::ActionProfile const &a) const {
    return Attached::operator==(static_cast<const Attached &>(a)) && selector == a.selector &&
           actions == a.actions && size == a.size;
}
bool IR::ActionProfile::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Attached::equiv(a_)) return false;
    auto &a = static_cast<const ActionProfile &>(a_);
    return selector == a.selector && actions == a.actions && size == a.size;
}
void IR::ActionProfile::dump_fields(std::ostream &out) const {
    Attached::dump_fields(out);
    out << " selector=" << selector;
    out << " size=" << size;
}
void IR::ActionProfile::toJSON(JSONGenerator &json) const {
    Attached::toJSON(json);
    json.emit("selector", selector);
    json.emit("actions", actions);
    json.emit("size", size);
}
IR::ActionProfile::ActionProfile(JSONLoader &json) : Attached(json) {
    json.load("selector", selector) || json.error("missing field selector");
    json.load("actions", actions) || json.error("missing field actions");
    json.load("size", size) || json.error("missing field size");
}
IR::Node *IR::ActionProfile::fromJSON(JSONLoader &json) { return new ActionProfile(json); }
bool IR::ActionProfile::operator==(IR::Attached const &a) const { return a == *this; }
bool IR::ActionProfile::operator==(IR::Node const &a) const { return a == *this; }
char const *IR::ActionSelector::kind() const { return "action_selector"; }
bool IR::ActionSelector::operator==(IR::ActionSelector const &a) const {
    return Attached::operator==(static_cast<const Attached &>(a)) && key == a.key &&
           key_fields == a.key_fields && mode == a.mode && type == a.type;
}
bool IR::ActionSelector::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Attached::equiv(a_)) return false;
    auto &a = static_cast<const ActionSelector &>(a_);
    return key == a.key &&
           (key_fields ? a.key_fields ? key_fields->equiv(*a.key_fields) : false
                       : a.key_fields == nullptr) &&
           mode == a.mode && type == a.type;
}
void IR::ActionSelector::visit_children(Visitor &v, char const *n) {
    (void)n;
    Attached::visit_children(v, n);
    v.visit(key_fields, "key_fields");
}
void IR::ActionSelector::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Attached::visit_children(v, n);
    v.visit(key_fields, "key_fields");
}
void IR::ActionSelector::dump_fields(std::ostream &out) const {
    Attached::dump_fields(out);
    out << " key=" << key;
    out << " mode=" << mode;
    out << " type=" << type;
}
void IR::ActionSelector::toJSON(JSONGenerator &json) const {
    Attached::toJSON(json);
    json.emit("key", key);
    if (key_fields != nullptr) json.emit("key_fields", key_fields);
    json.emit("mode", mode);
    json.emit("type", type);
}
IR::ActionSelector::ActionSelector(JSONLoader &json) : Attached(json) {
    json.load("key", key) || json.error("missing field key");
    json.load("key_fields", key_fields);
    json.load("mode", mode) || json.error("missing field mode");
    json.load("type", type) || json.error("missing field type");
}
IR::Node *IR::ActionSelector::fromJSON(JSONLoader &json) { return new ActionSelector(json); }
bool IR::ActionSelector::operator==(IR::Attached const &a) const { return a == *this; }
bool IR::ActionSelector::operator==(IR::Node const &a) const { return a == *this; }
void IR::V1Table::addProperty(const IR::Property *prop) { properties.push_back(prop); }
IR::Vector<IR::Annotation> const &IR::V1Table::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::V1Table::getAnnotations() { return annotations; }
cstring IR::V1Table::toString() const { return node_type_name() + " " + name; }
IR::ID IR::V1Table::Name() const { return name; }
const IR::Type *IR::V1Table::getType() const { return Type_AnyTable::get(); }
bool IR::V1Table::operator==(IR::V1Table const &a) const {
    return this->typeId() == a.typeId() && name == a.name && reads == a.reads &&
           reads_types == a.reads_types && min_size == a.min_size && max_size == a.max_size &&
           size == a.size && action_profile == a.action_profile && actions == a.actions &&
           default_action == a.default_action &&
           default_action_is_const == a.default_action_is_const &&
           default_action_args == a.default_action_args && properties == a.properties &&
           annotations == a.annotations;
}
bool IR::V1Table::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const V1Table &>(a_);
    return name == a.name &&
           (reads ? a.reads ? reads->equiv(*a.reads) : false : a.reads == nullptr) &&
           reads_types == a.reads_types && min_size == a.min_size && max_size == a.max_size &&
           size == a.size && action_profile == a.action_profile && actions == a.actions &&
           default_action == a.default_action &&
           default_action_is_const == a.default_action_is_const &&
           (default_action_args
                ? a.default_action_args ? default_action_args->equiv(*a.default_action_args) : false
                : a.default_action_args == nullptr) &&
           properties.equiv(a.properties) && annotations.equiv(a.annotations);
}
void IR::V1Table::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    v.visit(reads, "reads");
    v.visit(default_action_args, "default_action_args");
    properties.visit_children(v, "properties");
    annotations.visit_children(v, "annotations");
}
void IR::V1Table::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    v.visit(reads, "reads");
    v.visit(default_action_args, "default_action_args");
    properties.visit_children(v, "properties");
    annotations.visit_children(v, "annotations");
}
void IR::V1Table::validate() const {
    properties.validate();
    annotations.validate();
}
void IR::V1Table::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
    out << " min_size=" << min_size;
    out << " max_size=" << max_size;
    out << " size=" << size;
    out << " action_profile=" << action_profile;
    out << " default_action=" << default_action;
    out << " default_action_is_const=" << default_action_is_const;
}
void IR::V1Table::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    if (reads != nullptr) json.emit("reads", reads);
    json.emit("reads_types", reads_types);
    json.emit("min_size", min_size);
    json.emit("max_size", max_size);
    json.emit("size", size);
    json.emit("action_profile", action_profile);
    json.emit("actions", actions);
    json.emit("default_action", default_action);
    json.emit("default_action_is_const", default_action_is_const);
    if (default_action_args != nullptr) json.emit("default_action_args", default_action_args);
    json.emit("properties", properties);
    json.emit("annotations", annotations);
}
IR::V1Table::V1Table(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("reads", reads);
    json.load("reads_types", reads_types) || json.error("missing field reads_types");
    json.load("min_size", min_size) || json.error("missing field min_size");
    json.load("max_size", max_size) || json.error("missing field max_size");
    json.load("size", size) || json.error("missing field size");
    json.load("action_profile", action_profile) || json.error("missing field action_profile");
    json.load("actions", actions) || json.error("missing field actions");
    json.load("default_action", default_action) || json.error("missing field default_action");
    json.load("default_action_is_const", default_action_is_const) ||
        json.error("missing field default_action_is_const");
    json.load("default_action_args", default_action_args);
    json.load("properties", properties) || json.error("missing field properties");
    json.load("annotations", annotations) || json.error("missing field annotations");
}
IR::Node *IR::V1Table::fromJSON(JSONLoader &json) { return new V1Table(json); }
bool IR::V1Table::operator==(IR::Node const &a) const { return a == *this; }
IR::V1Control::V1Control(IR::ID n) : name(n), code(new Vector<Expression>()) {}
IR::V1Control::V1Control(Util::SourceInfo si, IR::ID n)
    : Node(si), name(n), code(new Vector<Expression>()) {}
IRNODE_DEFINE_APPLY_OVERLOAD(V1Control, , )
IR::Vector<IR::Annotation> const &IR::V1Control::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::V1Control::getAnnotations() { return annotations; }
cstring IR::V1Control::toString() const { return node_type_name() + " " + name; }
bool IR::V1Control::operator==(IR::V1Control const &a) const {
    return this->typeId() == a.typeId() && name == a.name && code == a.code &&
           annotations == a.annotations;
}
bool IR::V1Control::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const V1Control &>(a_);
    return name == a.name && (code ? a.code ? code->equiv(*a.code) : false : a.code == nullptr) &&
           annotations.equiv(a.annotations);
}
void IR::V1Control::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    v.visit(code, "code");
    annotations.visit_children(v, "annotations");
}
void IR::V1Control::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    v.visit(code, "code");
    annotations.visit_children(v, "annotations");
}
void IR::V1Control::validate() const {
    CHECK_NULL(code);
    annotations.validate();
}
void IR::V1Control::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
}
void IR::V1Control::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    json.emit("code", code);
    json.emit("annotations", annotations);
}
IR::V1Control::V1Control(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("code", code) || json.error("missing field code");
    json.load("annotations", annotations) || json.error("missing field annotations");
}
IR::Node *IR::V1Control::fromJSON(JSONLoader &json) { return new V1Control(json); }
bool IR::V1Control::operator==(IR::Node const &a) const { return a == *this; }
IR::ID IR::AttribLocal::getName() const { return name; }
void IR::AttribLocal::dbprint(std::ostream &out) const { out << name; }
bool IR::AttribLocal::operator==(IR::AttribLocal const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && name == a.name;
}
bool IR::AttribLocal::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const AttribLocal &>(a_);
    return name == a.name;
}
void IR::AttribLocal::dump_fields(std::ostream &out) const {
    Expression::dump_fields(out);
    out << " name=" << name;
}
void IR::AttribLocal::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("name", name);
}
IR::AttribLocal::AttribLocal(JSONLoader &json) : Expression(json) {
    json.load("name", name) || json.error("missing field name");
}
IR::Node *IR::AttribLocal::fromJSON(JSONLoader &json) { return new AttribLocal(json); }
bool IR::AttribLocal::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::AttribLocal::operator==(IR::Node const &a) const { return a == *this; }
Util::Enumerator<const IR::IDeclaration *> *IR::AttribLocals::getDeclarations() const {
    return locals.valueEnumerator()->as<const IDeclaration *>();
}
const IR::IDeclaration *IR::AttribLocals::getDeclByName(cstring name) const { return locals[name]; }
const IR::IDeclaration *IR::AttribLocals::getDeclByName(std::string_view name) const {
    return locals[cstring(name)];
}
bool IR::AttribLocals::operator==(IR::AttribLocals const &a) const {
    return this->typeId() == a.typeId() && locals == a.locals;
}
bool IR::AttribLocals::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const AttribLocals &>(a_);
    return locals.equiv(a.locals);
}
void IR::AttribLocals::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    locals.visit_children(v, "locals");
}
void IR::AttribLocals::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    locals.visit_children(v, "locals");
}
void IR::AttribLocals::validate() const { locals.validate(); }
void IR::AttribLocals::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("locals", locals);
}
IR::AttribLocals::AttribLocals(JSONLoader &json) : Node(json) {
    json.load("locals", locals) || json.error("missing field locals");
}
IR::Node *IR::AttribLocals::fromJSON(JSONLoader &json) { return new AttribLocals(json); }
bool IR::AttribLocals::operator==(IR::Node const &a) const { return a == *this; }
void IR::Attribute::dbprint(std::ostream &out) const {
    if (type) out << type << ' ';
    out << name;
}
bool IR::Attribute::operator==(IR::Attribute const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) && type == a.type &&
           locals == a.locals && optional == a.optional;
}
bool IR::Attribute::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Attribute &>(a_);
    return (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           (locals ? a.locals ? locals->equiv(*a.locals) : false : a.locals == nullptr) &&
           optional == a.optional;
}
void IR::Attribute::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    v.visit(type, "type");
    v.visit(locals, "locals");
}
void IR::Attribute::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    v.visit(type, "type");
    v.visit(locals, "locals");
}
void IR::Attribute::dump_fields(std::ostream &out) const {
    Declaration::dump_fields(out);
    out << " optional=" << optional;
}
void IR::Attribute::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    if (type != nullptr) json.emit("type", type);
    if (locals != nullptr) json.emit("locals", locals);
    json.emit("optional", optional);
}
IR::Attribute::Attribute(JSONLoader &json) : Declaration(json) {
    json.load("type", type);
    json.load("locals", locals);
    json.load("optional", optional) || json.error("missing field optional");
}
IR::Node *IR::Attribute::fromJSON(JSONLoader &json) { return new Attribute(json); }
bool IR::Attribute::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::Attribute::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::Attribute::operator==(IR::Node const &a) const { return a == *this; }
void IR::GlobalRef::validate() const {
    CHECK_NULL(obj);
    { BUG_CHECK(obj->is<IInstance>(), "Invalid object %1%", obj); }
}
cstring IR::GlobalRef::toString() const { return obj->to<IInstance>()->toString(); }
IR::ID IR::GlobalRef::Name() const { return obj->to<IInstance>()->Name(); }
void IR::GlobalRef::dbprint(std::ostream &out) const { out << obj->to<IInstance>()->Name(); }
bool IR::GlobalRef::operator==(IR::GlobalRef const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) && obj == a.obj;
}
bool IR::GlobalRef::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const GlobalRef &>(a_);
    return (obj ? a.obj ? obj->equiv(*a.obj) : false : a.obj == nullptr);
}
void IR::GlobalRef::visit_children(Visitor &v, char const *n) {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(obj, "obj");
}
void IR::GlobalRef::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(obj, "obj");
}
void IR::GlobalRef::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("obj", obj);
}
IR::GlobalRef::GlobalRef(JSONLoader &json) : Expression(json) {
    json.load("obj", obj) || json.error("missing field obj");
}
IR::Node *IR::GlobalRef::fromJSON(JSONLoader &json) { return new GlobalRef(json); }
bool IR::GlobalRef::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::GlobalRef::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::AttributeRef::toString() const { return attrib->name; }
void IR::AttributeRef::dbprint(std::ostream &out) const { out << attrib->name; }
bool IR::AttributeRef::operator==(IR::AttributeRef const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a)) &&
           extern_name == a.extern_name && extern_type == a.extern_type && attrib == a.attrib;
}
bool IR::AttributeRef::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    auto &a = static_cast<const AttributeRef &>(a_);
    return extern_name == a.extern_name &&
           (extern_type ? a.extern_type ? extern_type->equiv(*a.extern_type) : false
                        : a.extern_type == nullptr) &&
           (attrib ? a.attrib ? attrib->equiv(*a.attrib) : false : a.attrib == nullptr);
}
void IR::AttributeRef::visit_children(Visitor &v, char const *n) {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(extern_type, "extern_type");
    v.visit(attrib, "attrib");
}
void IR::AttributeRef::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Expression::visit_children(v, n);
    v.visit(extern_type, "extern_type");
    v.visit(attrib, "attrib");
}
void IR::AttributeRef::validate() const {
    CHECK_NULL(extern_type);
    CHECK_NULL(attrib);
}
void IR::AttributeRef::dump_fields(std::ostream &out) const {
    Expression::dump_fields(out);
    out << " extern_name=" << extern_name;
}
void IR::AttributeRef::toJSON(JSONGenerator &json) const {
    Expression::toJSON(json);
    json.emit("extern_name", extern_name);
    json.emit("extern_type", extern_type);
    json.emit("attrib", attrib);
}
IR::AttributeRef::AttributeRef(JSONLoader &json) : Expression(json) {
    json.load("extern_name", extern_name) || json.error("missing field extern_name");
    json.load("extern_type", extern_type) || json.error("missing field extern_type");
    json.load("attrib", attrib) || json.error("missing field attrib");
}
IR::Node *IR::AttributeRef::fromJSON(JSONLoader &json) { return new AttributeRef(json); }
bool IR::AttributeRef::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::AttributeRef::operator==(IR::Node const &a) const { return a == *this; }
void IR::V1Program::add(cstring name, IR::Node const *n) { scope.add(name, n); }
IRNODE_DEFINE_APPLY_OVERLOAD(V1Program, , )
bool IR::V1Program::operator==(IR::V1Program const &a) const {
    return this->typeId() == a.typeId() && scope == a.scope;
}
bool IR::V1Program::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const V1Program &>(a_);
    return scope.equiv(a.scope);
}
void IR::V1Program::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    scope.visit_children(v, "scope");
}
void IR::V1Program::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    scope.visit_children(v, "scope");
}
void IR::V1Program::validate() const { scope.validate(); }
void IR::V1Program::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("scope", scope);
}
IR::V1Program::V1Program(JSONLoader &json) : Node(json) {
    json.load("scope", scope) || json.error("missing field scope");
}
IR::Node *IR::V1Program::fromJSON(JSONLoader &json) { return new V1Program(json); }
bool IR::V1Program::operator==(IR::Node const &a) const { return a == *this; }
bool IR::IntMod::operator==(IR::IntMod const &a) const {
    return Operation_Unary::operator==(static_cast<const Operation_Unary &>(a)) && width == a.width;
}
bool IR::IntMod::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Operation_Unary::equiv(a_)) return false;
    auto &a = static_cast<const IntMod &>(a_);
    return width == a.width;
}
void IR::IntMod::dump_fields(std::ostream &out) const {
    Operation_Unary::dump_fields(out);
    out << " width=" << width;
}
void IR::IntMod::toJSON(JSONGenerator &json) const {
    Operation_Unary::toJSON(json);
    json.emit("width", width);
}
IR::IntMod::IntMod(JSONLoader &json) : Operation_Unary(json) {
    json.load("width", width) || json.error("missing field width");
}
IR::Node *IR::IntMod::fromJSON(JSONLoader &json) { return new IntMod(json); }
bool IR::IntMod::operator==(IR::Operation_Unary const &a) const { return a == *this; }
bool IR::IntMod::operator==(IR::Operation const &a) const { return a == *this; }
bool IR::IntMod::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::IntMod::operator==(IR::Node const &a) const { return a == *this; }