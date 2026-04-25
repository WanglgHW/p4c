#include "ir/ir-generated.h"   // IWYU pragma: keep

#include "ir/ir-inline.h"      // IWYU pragma: keep
#include "ir/json_generator.h" // IWYU pragma: keep
#include "ir/json_loader.h"    // IWYU pragma: keep
#include "ir/visitor.h"        // IWYU pragma: keep
#include "lib/algorithm.h"     // IWYU pragma: keep
#include "lib/log.h"           // IWYU pragma: keep

using namespace P4;

// Method definitions for IR type nodes.

cstring IR::Type_Any::getVarName() const { return absl::StrCat("int_", declid); }
int IR::Type_Any::getDeclId() const { return declid; }
void IR::Type_Any::dbprint(std::ostream &out) const { out << "ANYTYPE/" << declid; }
cstring IR::Type_Any::toString() const { return "ANYTYPE"_cs; }
bool IR::Type_Any::operator==(IR::Type_Any const &a) const { return declid == a.declid; }
IR::Type const *IR::Type_Any::getP4Type() const { return nullptr; }
bool IR::Type_Any::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_Any &>(a_);

    {
        (void)a;     // silence unused warning
        return true; /* ignore declid */
    }
}
void IR::Type_Any::dump_fields(std::ostream &out) const {
    Type::dump_fields(out);
    out << " declid=" << declid;
}
void IR::Type_Any::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("declid", declid);
}
IR::Type_Any::Type_Any(JSONLoader &json) : Type(json) {
    json.load("declid", declid) || json.error("missing field declid");
}
IR::Node *IR::Type_Any::fromJSON(JSONLoader &json) { return new Type_Any(json); }
bool IR::Type_Any::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Any::operator==(IR::Node const &a) const { return a == *this; }
void IR::Type_Fragment::dbprint(std::ostream &out) const { out << "FRAGMENT(" << type << ")"; }
cstring IR::Type_Fragment::toString() const { return absl::StrCat("FRAGMENT(", type, ")"); }
IR::Type const *IR::Type_Fragment::getP4Type() const { return nullptr; }
bool IR::Type_Fragment::operator==(IR::Type_Fragment const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && type == a.type;
}
bool IR::Type_Fragment::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_Fragment &>(a_);
    return (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr);
}
void IR::Type_Fragment::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(type, "type");
}
void IR::Type_Fragment::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(type, "type");
}
void IR::Type_Fragment::validate() const { CHECK_NULL(type); }
void IR::Type_Fragment::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("type", type);
}
IR::Type_Fragment::Type_Fragment(JSONLoader &json) : Type(json) {
    json.load("type", type) || json.error("missing field type");
}
IR::Node *IR::Type_Fragment::fromJSON(JSONLoader &json) { return new Type_Fragment(json); }
bool IR::Type_Fragment::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Fragment::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Type::toString() const { return absl::StrCat("Type(", type, ")"); }
void IR::Type_Type::dbprint(std::ostream &out) const { out << "Type(" << type << ")"; }
IR::Type const *IR::Type_Type::getP4Type() const { return type; }
void IR::Type_Type::validate() const {
    CHECK_NULL(type);
    { BUG_CHECK(!type->is<IR::Type_Type>(), "%1%: nested Type_Type", type); }
}
bool IR::Type_Type::operator==(IR::Type_Type const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && type == a.type;
}
bool IR::Type_Type::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_Type &>(a_);
    return (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr);
}
void IR::Type_Type::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(type, "type");
}
void IR::Type_Type::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(type, "type");
}
void IR::Type_Type::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("type", type);
}
IR::Type_Type::Type_Type(JSONLoader &json) : Type(json) {
    json.load("type", type) || json.error("missing field type");
}
IR::Node *IR::Type_Type::fromJSON(JSONLoader &json) { return new Type_Type(json); }
bool IR::Type_Type::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Type::operator==(IR::Node const &a) const { return a == *this; }
int IR::Type_Boolean::width_bits() const { return 1; }
int IR::Type_Boolean::min_width_bits() const {
    BUG("min_width_bits() on fixed-width type: %1%", this);
}
int IR::Type_Boolean::max_width_bits() const {
    BUG("max_width_bits() on fixed-width type: %1%", this);
}
int IR::Type_Boolean::min_or_fixed_width_bits() const { return width_bits(); }
int IR::Type_Boolean::max_or_fixed_width_bits() const { return width_bits(); }
cstring IR::Type_Boolean::toString() const { return "bool"_cs; }
void IR::Type_Boolean::dbprint(std::ostream &out) const { out << "bool"; }
bool IR::Type_Boolean::operator==(IR::Type_Boolean const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_Boolean::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_Boolean::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_Boolean::Type_Boolean(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_Boolean::fromJSON(JSONLoader &json) { return new Type_Boolean(json); }
bool IR::Type_Boolean::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_Boolean::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Boolean::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_State::toString() const { return "state"_cs; }
void IR::Type_State::dbprint(std::ostream &out) const { out << "state"; }
bool IR::Type_State::operator==(IR::Type_State const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_State::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_State::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_State::Type_State(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_State::fromJSON(JSONLoader &json) { return new Type_State(json); }
bool IR::Type_State::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_State::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_State::operator==(IR::Node const &a) const { return a == *this; }
int IR::Type_Bits::width_bits() const { return size; }
int IR::Type_Bits::min_width_bits() const {
    BUG("min_width_bits() on fixed-width type: %1%", this);
}
int IR::Type_Bits::max_width_bits() const {
    BUG("max_width_bits() on fixed-width type: %1%", this);
}
cstring IR::Type_Bits::toString() const { return absl::StrCat(baseName(), "<", size, ">"); }
void IR::Type_Bits::dbprint(std::ostream &out) const { out << toString(); }
bool IR::Type_Bits::operator==(IR::Type_Bits const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a)) && size == a.size &&
           expression == a.expression && isSigned == a.isSigned;
}
bool IR::Type_Bits::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    auto &a = static_cast<const Type_Bits &>(a_);
    return size == a.size &&
           (expression ? a.expression ? expression->equiv(*a.expression) : false
                       : a.expression == nullptr) &&
           isSigned == a.isSigned;
}
void IR::Type_Bits::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Base::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::Type_Bits::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Base::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::Type_Bits::dump_fields(std::ostream &out) const {
    Type_Base::dump_fields(out);
    out << " size=" << size;
    out << " isSigned=" << isSigned;
}
void IR::Type_Bits::toJSON(JSONGenerator &json) const {
    Type_Base::toJSON(json);
    json.emit("size", size);
    if (expression != nullptr) json.emit("expression", expression);
    json.emit("isSigned", isSigned);
}
IR::Type_Bits::Type_Bits(JSONLoader &json) : Type_Base(json) {
    json.load("size", size) || json.error("missing field size");
    json.load("expression", expression);
    json.load("isSigned", isSigned) || json.error("missing field isSigned");
}
IR::Node *IR::Type_Bits::fromJSON(JSONLoader &json) { return new Type_Bits(json); }
bool IR::Type_Bits::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_Bits::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Bits::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Varbits::toString() const { return absl::StrCat("varbit<", size, ">"); }
void IR::Type_Varbits::dbprint(std::ostream &out) const { out << "varbit<" << size << ">"; }
int IR::Type_Varbits::width_bits() const { return size; }
int IR::Type_Varbits::min_width_bits() const { return 0; }
int IR::Type_Varbits::max_width_bits() const { return size; }
int IR::Type_Varbits::min_or_fixed_width_bits() const { return min_width_bits(); }
int IR::Type_Varbits::max_or_fixed_width_bits() const { return max_width_bits(); }
bool IR::Type_Varbits::variable() const { return true; }
bool IR::Type_Varbits::operator==(IR::Type_Varbits const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a)) && size == a.size &&
           expression == a.expression;
}
bool IR::Type_Varbits::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    auto &a = static_cast<const Type_Varbits &>(a_);
    return size == a.size && (expression ? a.expression ? expression->equiv(*a.expression) : false
                                         : a.expression == nullptr);
}
void IR::Type_Varbits::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Base::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::Type_Varbits::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Base::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::Type_Varbits::dump_fields(std::ostream &out) const {
    Type_Base::dump_fields(out);
    out << " size=" << size;
}
void IR::Type_Varbits::toJSON(JSONGenerator &json) const {
    Type_Base::toJSON(json);
    json.emit("size", size);
    if (expression != nullptr) json.emit("expression", expression);
}
IR::Type_Varbits::Type_Varbits(JSONLoader &json) : Type_Base(json) {
    json.load("size", size) || json.error("missing field size");
    json.load("expression", expression);
}
IR::Node *IR::Type_Varbits::fromJSON(JSONLoader &json) { return new Type_Varbits(json); }
bool IR::Type_Varbits::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_Varbits::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Varbits::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::Parameter::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Parameter::getAnnotations() { return annotations; }
void IR::Parameter::dbprint(std::ostream &out) const {
    out << annotations << direction << (direction != IR::Direction::None ? " " : "") << type << ' '
        << name;
}
bool IR::Parameter::operator==(IR::Parameter const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           annotations == a.annotations && direction == a.direction && type == a.type &&
           defaultValue == a.defaultValue;
}
bool IR::Parameter::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Parameter &>(a_);
    return annotations.equiv(a.annotations) && direction == a.direction &&
           (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           (defaultValue ? a.defaultValue ? defaultValue->equiv(*a.defaultValue) : false
                         : a.defaultValue == nullptr);
}
void IR::Parameter::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    v.visit(defaultValue, "defaultValue");
}
void IR::Parameter::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    v.visit(defaultValue, "defaultValue");
}
void IR::Parameter::validate() const {
    annotations.validate();
    CHECK_NULL(type);
}
void IR::Parameter::dump_fields(std::ostream &out) const {
    Declaration::dump_fields(out);
    out << " direction=" << direction;
}
void IR::Parameter::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("direction", direction);
    json.emit("type", type);
    if (defaultValue != nullptr) json.emit("defaultValue", defaultValue);
}
IR::Parameter::Parameter(JSONLoader &json) : Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("direction", direction) || json.error("missing field direction");
    json.load("type", type) || json.error("missing field type");
    json.load("defaultValue", defaultValue);
}
IR::Node *IR::Parameter::fromJSON(JSONLoader &json) { return new Parameter(json); }
bool IR::Parameter::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::Parameter::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::Parameter::operator==(IR::Node const &a) const { return a == *this; }
void IR::ParameterList::validate() const {
    parameters.validate();
    { parameters.check_null(); }
}
Util::Enumerator<const IR::IDeclaration *> *IR::ParameterList::getDeclarations() const {
    return parameters.getDeclarations();
}
const IR::IDeclaration *IR::ParameterList::getDeclByName(cstring name) const {
    return getParameter(name);
}
const IR::IDeclaration *IR::ParameterList::getDeclByName(std::string_view name) const {
    return getParameter(name);
}
cstring IR::ParameterList::toString() const {
    return absl::StrJoin(parameters, ", ",
                         [](std::string *out, const auto *p) { absl::StrAppend(out, p); });
}
bool IR::ParameterList::operator==(IR::ParameterList const &a) const {
    return this->typeId() == a.typeId() && parameters == a.parameters;
}
bool IR::ParameterList::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const ParameterList &>(a_);
    return parameters.equiv(a.parameters);
}
void IR::ParameterList::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    parameters.visit_children(v, "parameters");
}
void IR::ParameterList::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    parameters.visit_children(v, "parameters");
}
void IR::ParameterList::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("parameters", parameters);
}
IR::ParameterList::ParameterList(JSONLoader &json) : Node(json) {
    json.load("parameters", parameters) || json.error("missing field parameters");
}
IR::Node *IR::ParameterList::fromJSON(JSONLoader &json) { return new ParameterList(json); }
bool IR::ParameterList::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Var::getVarName() const { return getName(); }
int IR::Type_Var::getDeclId() const { return declid; }
void IR::Type_Var::dbprint(std::ostream &out) const { out << name << "/" << getDeclId(); }
cstring IR::Type_Var::toString() const { return getName().toString(); }
bool IR::Type_Var::operator==(IR::Type_Var const &a) const {
    return Type_Declaration::operator==(static_cast<const Type_Declaration &>(a));
}
bool IR::Type_Var::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Declaration::equiv(a_)) return false;
    return true;
}
void IR::Type_Var::toJSON(JSONGenerator &json) const { Type_Declaration::toJSON(json); }
IR::Type_Var::Type_Var(JSONLoader &json) : Type_Declaration(json) {}
IR::Node *IR::Type_Var::fromJSON(JSONLoader &json) { return new Type_Var(json); }
bool IR::Type_Var::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_Var::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Var::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_InfInt::getVarName() const { return absl::StrCat("int_", declid); }
int IR::Type_InfInt::getDeclId() const { return declid; }
void IR::Type_InfInt::dbprint(std::ostream &out) const { out << "int/" << declid; }
cstring IR::Type_InfInt::toString() const { return "int"_cs; }
bool IR::Type_InfInt::operator==(IR::Type_InfInt const &a) const { return declid == a.declid; }
bool IR::Type_InfInt::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_InfInt &>(a_);

    {
        (void)a;     // silence unused warning
        return true; /* ignore declid */
    }
}
IR::Type const *IR::Type_InfInt::getP4Type() const { return this; }
int IR::Type_InfInt::width_bits() const { return 0; }
int IR::Type_InfInt::min_width_bits() const { BUG("min_width_bits() on unsized type: %1%", this); }
int IR::Type_InfInt::max_width_bits() const { BUG("max_width_bits() on unsized type: %1%", this); }
void IR::Type_InfInt::dump_fields(std::ostream &out) const {
    Type::dump_fields(out);
    out << " declid=" << declid;
}
void IR::Type_InfInt::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("declid", declid);
}
IR::Type_InfInt::Type_InfInt(JSONLoader &json) : Type(json) {
    json.load("declid", declid) || json.error("missing field declid");
}
IR::Node *IR::Type_InfInt::fromJSON(JSONLoader &json) { return new Type_InfInt(json); }
bool IR::Type_InfInt::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_InfInt::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Dontcare::toString() const { return "_"_cs; }
void IR::Type_Dontcare::dbprint(std::ostream &out) const { out << "_"; }
bool IR::Type_Dontcare::operator==(IR::Type_Dontcare const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_Dontcare::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_Dontcare::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_Dontcare::Type_Dontcare(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_Dontcare::fromJSON(JSONLoader &json) { return new Type_Dontcare(json); }
bool IR::Type_Dontcare::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_Dontcare::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Dontcare::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Void::toString() const { return "void"_cs; }
void IR::Type_Void::dbprint(std::ostream &out) const { out << "void"; }
bool IR::Type_Void::operator==(IR::Type_Void const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_Void::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_Void::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_Void::Type_Void(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_Void::fromJSON(JSONLoader &json) { return new Type_Void(json); }
bool IR::Type_Void::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_Void::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Void::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_MatchKind::toString() const { return "match_kind"_cs; }
void IR::Type_MatchKind::dbprint(std::ostream &out) const { out << "match_kind"; }
bool IR::Type_MatchKind::operator==(IR::Type_MatchKind const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_MatchKind::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_MatchKind::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_MatchKind::Type_MatchKind(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_MatchKind::fromJSON(JSONLoader &json) { return new Type_MatchKind(json); }
bool IR::Type_MatchKind::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_MatchKind::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_MatchKind::operator==(IR::Node const &a) const { return a == *this; }
Util::Enumerator<const IR::IDeclaration *> *IR::TypeParameters::getDeclarations() const {
    return parameters.getDeclarations();
}
const IR::IDeclaration *IR::TypeParameters::getDeclByName(cstring name) const {
    return parameters.getDeclaration(name);
}
const IR::IDeclaration *IR::TypeParameters::getDeclByName(std::string_view name) const {
    return parameters.getDeclaration(name);
}
void IR::TypeParameters::validate() const {
    parameters.validate();
    { parameters.check_null(); }
}
cstring IR::TypeParameters::toString() const {
    if (parameters.size() == 0) return cstring::empty;
    return absl::StrCat(
        "<",
        absl::StrJoin(parameters, ", ",
                      [](std::string *out, const auto *p) { absl::StrAppend(out, p); }),
        ">");
}
bool IR::TypeParameters::operator==(IR::TypeParameters const &a) const {
    return this->typeId() == a.typeId() && parameters == a.parameters;
}
bool IR::TypeParameters::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const TypeParameters &>(a_);
    return parameters.equiv(a.parameters);
}
void IR::TypeParameters::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    parameters.visit_children(v, "parameters");
}
void IR::TypeParameters::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    parameters.visit_children(v, "parameters");
}
void IR::TypeParameters::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("parameters", parameters);
}
IR::TypeParameters::TypeParameters(JSONLoader &json) : Node(json) {
    json.load("parameters", parameters) || json.error("missing field parameters");
}
IR::Node *IR::TypeParameters::fromJSON(JSONLoader &json) { return new TypeParameters(json); }
bool IR::TypeParameters::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::StructField::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::StructField::getAnnotations() { return annotations; }
bool IR::StructField::operator==(IR::StructField const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           annotations == a.annotations && type == a.type;
}
bool IR::StructField::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const StructField &>(a_);
    return annotations.equiv(a.annotations) &&
           (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr);
}
void IR::StructField::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
}
void IR::StructField::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
}
void IR::StructField::validate() const {
    annotations.validate();
    CHECK_NULL(type);
}
void IR::StructField::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("type", type);
}
IR::StructField::StructField(JSONLoader &json) : Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("type", type) || json.error("missing field type");
}
IR::Node *IR::StructField::fromJSON(JSONLoader &json) { return new StructField(json); }
bool IR::StructField::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::StructField::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::StructField::operator==(IR::Node const &a) const { return a == *this; }
const IR::TypeParameters *IR::Type_StructLike::getTypeParameters() const { return typeParameters; }
std::vector<const IR::INamespace *> IR::Type_StructLike::getNestedNamespaces() const {
    return {typeParameters};
}
IR::Vector<IR::Annotation> const &IR::Type_StructLike::getAnnotations() const {
    return annotations;
}
IR::Vector<IR::Annotation> &IR::Type_StructLike::getAnnotations() { return annotations; }
Util::Enumerator<const IR::IDeclaration *> *IR::Type_StructLike::getDeclarations() const {
    return fields.getDeclarations();
}
/// This function returns start offset of the given field name in bits.
/// If the given name is not a valid field name, -1 is returned.
/// The given offset may not be correct if varbit field(s) present in between.
/// Offset for all fields will be correct if:
///  - the type has only fixed width fields
///  - the type has fixed width fields with only one varbit field as a last member.
bool IR::Type_StructLike::variable() const {
    for (auto f : fields) {
        if (f->type->variable()) {
            return true;
        }
    }
    return false;
}
int IR::Type_StructLike::width_bits() const {
    int rv = 0;
    for (auto f : fields) {
        rv += f->type->width_bits();
    }
    return rv;
}
int IR::Type_StructLike::min_width_bits() const {
    int rv = 0;
    for (auto f : fields) {
        rv += f->type->min_or_fixed_width_bits();
    }
    return rv;
}
int IR::Type_StructLike::max_width_bits() const {
    int rv = 0;
    for (auto f : fields) {
        rv += f->type->max_or_fixed_width_bits();
    }
    return rv;
}
const IR::IDeclaration *IR::Type_StructLike::getDeclByName(cstring name) const {
    return fields.getDeclaration(name);
}
const IR::IDeclaration *IR::Type_StructLike::getDeclByName(std::string_view name) const {
    return fields.getDeclaration(name);
}
void IR::Type_StructLike::validate() const {
    annotations.validate();
    CHECK_NULL(typeParameters);
    fields.validate();
    { fields.check_null(); }
}
IRNODE_DEFINE_APPLY_OVERLOAD(Type_StructLike, , )
bool IR::Type_StructLike::operator==(IR::Type_StructLike const &a) const {
    return Type_Declaration::operator==(static_cast<const Type_Declaration &>(a)) &&
           annotations == a.annotations && typeParameters == a.typeParameters && fields == a.fields;
}
bool IR::Type_StructLike::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Type_StructLike &>(a_);
    return annotations.equiv(a.annotations) &&
           (typeParameters ? a.typeParameters ? typeParameters->equiv(*a.typeParameters) : false
                           : a.typeParameters == nullptr) &&
           fields.equiv(a.fields);
}
void IR::Type_StructLike::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(typeParameters, "typeParameters");
    fields.visit_children(v, "fields");
}
void IR::Type_StructLike::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(typeParameters, "typeParameters");
    fields.visit_children(v, "fields");
}
void IR::Type_StructLike::toJSON(JSONGenerator &json) const {
    Type_Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("typeParameters", typeParameters);
    json.emit("fields", fields);
}
IR::Type_StructLike::Type_StructLike(JSONLoader &json) : Type_Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("typeParameters", typeParameters) || json.error("missing field typeParameters");
    json.load("fields", fields) || json.error("missing field fields");
}
bool IR::Type_StructLike::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_StructLike::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_StructLike::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Struct::toString() const { return "struct "_cs + externalName(); }
bool IR::Type_Struct::operator==(IR::Type_Struct const &a) const {
    return Type_StructLike::operator==(static_cast<const Type_StructLike &>(a));
}
bool IR::Type_Struct::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_StructLike::equiv(a_)) return false;
    return true;
}
void IR::Type_Struct::toJSON(JSONGenerator &json) const { Type_StructLike::toJSON(json); }
IR::Type_Struct::Type_Struct(JSONLoader &json) : Type_StructLike(json) {}
IR::Node *IR::Type_Struct::fromJSON(JSONLoader &json) { return new Type_Struct(json); }
bool IR::Type_Struct::operator==(IR::Type_StructLike const &a) const { return a == *this; }
bool IR::Type_Struct::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_Struct::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Struct::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Type_UnknownStruct::operator==(IR::Type_UnknownStruct const &a) const {
    return Type_StructLike::operator==(static_cast<const Type_StructLike &>(a));
}
bool IR::Type_UnknownStruct::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_StructLike::equiv(a_)) return false;
    return true;
}
void IR::Type_UnknownStruct::toJSON(JSONGenerator &json) const { Type_StructLike::toJSON(json); }
IR::Type_UnknownStruct::Type_UnknownStruct(JSONLoader &json) : Type_StructLike(json) {}
IR::Node *IR::Type_UnknownStruct::fromJSON(JSONLoader &json) {
    return new Type_UnknownStruct(json);
}
bool IR::Type_UnknownStruct::operator==(IR::Type_StructLike const &a) const { return a == *this; }
bool IR::Type_UnknownStruct::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_UnknownStruct::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_UnknownStruct::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_HeaderUnion::toString() const { return "header_union "_cs + externalName(); }

int IR::Type_HeaderUnion::width_bits() const {
    int rv = 0;
    for (auto f : fields) rv = std::max(rv, f->type->width_bits());
    return rv;
}
int IR::Type_HeaderUnion::min_width_bits() const {
    if (fields.empty()) {
        return 0;
    }

    int rv = INT_MAX;
    for (auto f : fields) {
        rv = std::min(rv, f->type->min_or_fixed_width_bits());
    }
    return rv;
}
int IR::Type_HeaderUnion::max_width_bits() const {
    int rv = 0;
    for (auto f : fields) {
        rv = std::max(rv, f->type->max_or_fixed_width_bits());
    }
    return rv;
}
/// start offset of any field in a union is 0
bool IR::Type_HeaderUnion::operator==(IR::Type_HeaderUnion const &a) const {
    return Type_StructLike::operator==(static_cast<const Type_StructLike &>(a));
}
bool IR::Type_HeaderUnion::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_StructLike::equiv(a_)) return false;
    return true;
}
void IR::Type_HeaderUnion::toJSON(JSONGenerator &json) const { Type_StructLike::toJSON(json); }
IR::Type_HeaderUnion::Type_HeaderUnion(JSONLoader &json) : Type_StructLike(json) {}
IR::Node *IR::Type_HeaderUnion::fromJSON(JSONLoader &json) { return new Type_HeaderUnion(json); }
bool IR::Type_HeaderUnion::operator==(IR::Type_StructLike const &a) const { return a == *this; }
bool IR::Type_HeaderUnion::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_HeaderUnion::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_HeaderUnion::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Header::toString() const { return "header "_cs + externalName(); }
bool IR::Type_Header::operator==(IR::Type_Header const &a) const {
    return Type_StructLike::operator==(static_cast<const Type_StructLike &>(a));
}
bool IR::Type_Header::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_StructLike::equiv(a_)) return false;
    return true;
}
void IR::Type_Header::toJSON(JSONGenerator &json) const { Type_StructLike::toJSON(json); }
IR::Type_Header::Type_Header(JSONLoader &json) : Type_StructLike(json) {}
IR::Node *IR::Type_Header::fromJSON(JSONLoader &json) { return new Type_Header(json); }
bool IR::Type_Header::operator==(IR::Type_StructLike const &a) const { return a == *this; }
bool IR::Type_Header::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_Header::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Header::operator==(IR::Node const &a) const { return a == *this; }
void IR::Type_Set::dbprint(std::ostream &out) const {
    Node::dbprint(out);
    out << "<" << elementType << ">";
}
cstring IR::Type_Set::toString() const { return absl::StrCat("set<", elementType, ">"); }
IR::Type const *IR::Type_Set::getP4Type() const { return nullptr; }
int IR::Type_Set::width_bits() const {
    /// returning the width of the set elements, not the set itself, which doesn't
    /// really have a sensible size
    return elementType->width_bits();
}
int IR::Type_Set::min_width_bits() const { return elementType->min_width_bits(); }
int IR::Type_Set::max_width_bits() const { return elementType->max_width_bits(); }
bool IR::Type_Set::operator==(IR::Type_Set const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && elementType == a.elementType;
}
bool IR::Type_Set::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_Set &>(a_);
    return (elementType ? a.elementType ? elementType->equiv(*a.elementType) : false
                        : a.elementType == nullptr);
}
void IR::Type_Set::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(elementType, "elementType");
}
void IR::Type_Set::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(elementType, "elementType");
}
void IR::Type_Set::validate() const { CHECK_NULL(elementType); }
void IR::Type_Set::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("elementType", elementType);
}
IR::Type_Set::Type_Set(JSONLoader &json) : Type(json) {
    json.load("elementType", elementType) || json.error("missing field elementType");
}
IR::Node *IR::Type_Set::fromJSON(JSONLoader &json) { return new Type_Set(json); }
bool IR::Type_Set::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Set::operator==(IR::Node const &a) const { return a == *this; }
void IR::Type_BaseList::validate() const {
    components.validate();
    { components.check_null(); }
}
size_t IR::Type_BaseList::getSize() const { return components.size(); }
const IR::Type *IR::Type_BaseList::at(size_t index) const { return components.at(index); }
int IR::Type_BaseList::width_bits() const {
    /// returning sum of the width of the elements
    int rv = 0;
    for (auto f : components) {
        rv += f->width_bits();
    }
    return rv;
}
int IR::Type_BaseList::min_width_bits() const {
    int rv = 0;
    for (auto f : components) {
        rv += f->min_or_fixed_width_bits();
    }
    return rv;
}
int IR::Type_BaseList::max_width_bits() const {
    int rv = 0;
    for (auto f : components) {
        rv += f->max_or_fixed_width_bits();
    }
    return rv;
}
cstring IR::Type_BaseList::asString(char const *name) const {
    return absl::StrCat(
        name, "<",
        absl::StrJoin(components, ", ",
                      [](std::string *out, const auto *t) { absl::StrAppend(out, t); }),
        ">");
}
cstring IR::Type_BaseList::toString() const { return asString("baselist"); }
bool IR::Type_BaseList::operator==(IR::Type_BaseList const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && components == a.components;
}
bool IR::Type_BaseList::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_BaseList &>(a_);
    return components.equiv(a.components);
}
void IR::Type_BaseList::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    components.visit_children(v, "components");
}
void IR::Type_BaseList::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    components.visit_children(v, "components");
}
void IR::Type_BaseList::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("components", components);
}
IR::Type_BaseList::Type_BaseList(JSONLoader &json) : Type(json) {
    json.load("components", components) || json.error("missing field components");
}
bool IR::Type_BaseList::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_BaseList::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_List::toString() const { return asString("tuple"); }
bool IR::Type_List::operator==(IR::Type_List const &a) const {
    return Type_BaseList::operator==(static_cast<const Type_BaseList &>(a));
}
bool IR::Type_List::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_BaseList::equiv(a_)) return false;
    return true;
}
void IR::Type_List::toJSON(JSONGenerator &json) const { Type_BaseList::toJSON(json); }
IR::Type_List::Type_List(JSONLoader &json) : Type_BaseList(json) {}
IR::Node *IR::Type_List::fromJSON(JSONLoader &json) { return new Type_List(json); }
bool IR::Type_List::operator==(IR::Type_BaseList const &a) const { return a == *this; }
bool IR::Type_List::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_List::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Tuple::toString() const { return asString("tuple"); }
bool IR::Type_Tuple::operator==(IR::Type_Tuple const &a) const {
    return Type_BaseList::operator==(static_cast<const Type_BaseList &>(a));
}
bool IR::Type_Tuple::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_BaseList::equiv(a_)) return false;
    return true;
}
void IR::Type_Tuple::toJSON(JSONGenerator &json) const { Type_BaseList::toJSON(json); }
IR::Type_Tuple::Type_Tuple(JSONLoader &json) : Type_BaseList(json) {}
IR::Node *IR::Type_Tuple::fromJSON(JSONLoader &json) { return new Type_Tuple(json); }
bool IR::Type_Tuple::operator==(IR::Type_BaseList const &a) const { return a == *this; }
bool IR::Type_Tuple::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Tuple::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_P4List::toString() const { return absl::StrCat("list<", elementType, ">"); }
bool IR::Type_P4List::operator==(IR::Type_P4List const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && elementType == a.elementType;
}
bool IR::Type_P4List::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_P4List &>(a_);
    return (elementType ? a.elementType ? elementType->equiv(*a.elementType) : false
                        : a.elementType == nullptr);
}
void IR::Type_P4List::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(elementType, "elementType");
}
void IR::Type_P4List::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(elementType, "elementType");
}
void IR::Type_P4List::validate() const { CHECK_NULL(elementType); }
void IR::Type_P4List::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("elementType", elementType);
}
IR::Type_P4List::Type_P4List(JSONLoader &json) : Type(json) {
    json.load("elementType", elementType) || json.error("missing field elementType");
}
IR::Node *IR::Type_P4List::fromJSON(JSONLoader &json) { return new Type_P4List(json); }
bool IR::Type_P4List::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_P4List::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::Type_ArchBlock::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Type_ArchBlock::getAnnotations() { return annotations; }
const IR::TypeParameters *IR::Type_ArchBlock::getTypeParameters() const { return typeParameters; }
Util::Enumerator<const IR::IDeclaration *> *IR::Type_ArchBlock::getDeclarations() const {
    return typeParameters->getDeclarations();
}
const IR::IDeclaration *IR::Type_ArchBlock::getDeclByName(cstring name) const {
    return typeParameters->getDeclByName(name);
}
const IR::IDeclaration *IR::Type_ArchBlock::getDeclByName(std::string_view name) const {
    return typeParameters->getDeclByName(name);
}
bool IR::Type_ArchBlock::operator==(IR::Type_ArchBlock const &a) const {
    return Type_Declaration::operator==(static_cast<const Type_Declaration &>(a)) &&
           annotations == a.annotations && typeParameters == a.typeParameters;
}
bool IR::Type_ArchBlock::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Type_ArchBlock &>(a_);
    return annotations.equiv(a.annotations) &&
           (typeParameters ? a.typeParameters ? typeParameters->equiv(*a.typeParameters) : false
                           : a.typeParameters == nullptr);
}
void IR::Type_ArchBlock::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(typeParameters, "typeParameters");
}
void IR::Type_ArchBlock::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(typeParameters, "typeParameters");
}
void IR::Type_ArchBlock::validate() const {
    annotations.validate();
    CHECK_NULL(typeParameters);
}
void IR::Type_ArchBlock::toJSON(JSONGenerator &json) const {
    Type_Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("typeParameters", typeParameters);
}
IR::Type_ArchBlock::Type_ArchBlock(JSONLoader &json) : Type_Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("typeParameters", typeParameters) || json.error("missing field typeParameters");
}
bool IR::Type_ArchBlock::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_ArchBlock::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_ArchBlock::operator==(IR::Node const &a) const { return a == *this; }
const IR::Type *IR::Type_Package::getType() const { return this; }
const IR::ParameterList *IR::Type_Package::getConstructorParameters() const {
    return constructorParams;
}
cstring IR::Type_Package::toString() const { return "package "_cs + externalName(); }
Util::Enumerator<const IR::IDeclaration *> *IR::Type_Package::getDeclarations() const {
    return typeParameters->getDeclarations()->concat(constructorParams->getDeclarations());
}
const IR::IDeclaration *IR::Type_Package::getDeclByName(cstring name) const {
    auto decl = constructorParams->getDeclByName(name);
    if (!decl) decl = typeParameters->getDeclByName(name);
    return decl;
}
const IR::IDeclaration *IR::Type_Package::getDeclByName(std::string_view name) const {
    auto decl = constructorParams->getDeclByName(name);
    if (!decl) decl = typeParameters->getDeclByName(name);
    return decl;
}
bool IR::Type_Package::operator==(IR::Type_Package const &a) const {
    return Type_ArchBlock::operator==(static_cast<const Type_ArchBlock &>(a)) &&
           constructorParams == a.constructorParams;
}
bool IR::Type_Package::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_ArchBlock::equiv(a_)) return false;
    auto &a = static_cast<const Type_Package &>(a_);
    return (constructorParams
                ? a.constructorParams ? constructorParams->equiv(*a.constructorParams) : false
                : a.constructorParams == nullptr);
}
void IR::Type_Package::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_ArchBlock::visit_children(v, n);
    v.visit(constructorParams, "constructorParams");
}
void IR::Type_Package::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_ArchBlock::visit_children(v, n);
    v.visit(constructorParams, "constructorParams");
}
void IR::Type_Package::validate() const { CHECK_NULL(constructorParams); }
void IR::Type_Package::toJSON(JSONGenerator &json) const {
    Type_ArchBlock::toJSON(json);
    json.emit("constructorParams", constructorParams);
}
IR::Type_Package::Type_Package(JSONLoader &json) : Type_ArchBlock(json) {
    json.load("constructorParams", constructorParams) ||
        json.error("missing field constructorParams");
}
IR::Node *IR::Type_Package::fromJSON(JSONLoader &json) { return new Type_Package(json); }
bool IR::Type_Package::operator==(IR::Type_ArchBlock const &a) const { return a == *this; }
bool IR::Type_Package::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_Package::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Package::operator==(IR::Node const &a) const { return a == *this; }
const IR::ParameterList *IR::Type_Parser::getApplyParameters() const { return applyParams; }
cstring IR::Type_Parser::toString() const { return "parser "_cs + externalName(); }
bool IR::Type_Parser::operator==(IR::Type_Parser const &a) const {
    return Type_ArchBlock::operator==(static_cast<const Type_ArchBlock &>(a)) &&
           applyParams == a.applyParams;
}
bool IR::Type_Parser::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_ArchBlock::equiv(a_)) return false;
    auto &a = static_cast<const Type_Parser &>(a_);
    return (applyParams ? a.applyParams ? applyParams->equiv(*a.applyParams) : false
                        : a.applyParams == nullptr);
}
void IR::Type_Parser::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_ArchBlock::visit_children(v, n);
    v.visit(applyParams, "applyParams");
}
void IR::Type_Parser::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_ArchBlock::visit_children(v, n);
    v.visit(applyParams, "applyParams");
}
void IR::Type_Parser::validate() const { CHECK_NULL(applyParams); }
void IR::Type_Parser::toJSON(JSONGenerator &json) const {
    Type_ArchBlock::toJSON(json);
    json.emit("applyParams", applyParams);
}
IR::Type_Parser::Type_Parser(JSONLoader &json) : Type_ArchBlock(json) {
    json.load("applyParams", applyParams) || json.error("missing field applyParams");
}
IR::Node *IR::Type_Parser::fromJSON(JSONLoader &json) { return new Type_Parser(json); }
bool IR::Type_Parser::operator==(IR::Type_ArchBlock const &a) const { return a == *this; }
bool IR::Type_Parser::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_Parser::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Parser::operator==(IR::Node const &a) const { return a == *this; }
const IR::ParameterList *IR::Type_Control::getApplyParameters() const { return applyParams; }
cstring IR::Type_Control::toString() const { return "control "_cs + externalName(); }
bool IR::Type_Control::operator==(IR::Type_Control const &a) const {
    return Type_ArchBlock::operator==(static_cast<const Type_ArchBlock &>(a)) &&
           applyParams == a.applyParams;
}
bool IR::Type_Control::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_ArchBlock::equiv(a_)) return false;
    auto &a = static_cast<const Type_Control &>(a_);
    return (applyParams ? a.applyParams ? applyParams->equiv(*a.applyParams) : false
                        : a.applyParams == nullptr);
}
void IR::Type_Control::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_ArchBlock::visit_children(v, n);
    v.visit(applyParams, "applyParams");
}
void IR::Type_Control::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_ArchBlock::visit_children(v, n);
    v.visit(applyParams, "applyParams");
}
void IR::Type_Control::validate() const { CHECK_NULL(applyParams); }
void IR::Type_Control::toJSON(JSONGenerator &json) const {
    Type_ArchBlock::toJSON(json);
    json.emit("applyParams", applyParams);
}
IR::Type_Control::Type_Control(JSONLoader &json) : Type_ArchBlock(json) {
    json.load("applyParams", applyParams) || json.error("missing field applyParams");
}
IR::Node *IR::Type_Control::fromJSON(JSONLoader &json) { return new Type_Control(json); }
bool IR::Type_Control::operator==(IR::Type_ArchBlock const &a) const { return a == *this; }
bool IR::Type_Control::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_Control::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Control::operator==(IR::Node const &a) const { return a == *this; }
IR::Type_Name::Type_Name(IR::ID id) : Type(id.srcInfo), path(new IR::Path(id)) {}
cstring IR::Type_Name::toString() const { return path->name; }
void IR::Type_Name::dbprint(std::ostream &out) const { out << path->toString(); }
IR::Type const *IR::Type_Name::getP4Type() const { return this; }
int IR::Type_Name::width_bits() const {
    BUG("Type_Name is not a canonical type, use getTypeType()?");
    return 0;
}
int IR::Type_Name::min_width_bits() const {
    BUG("Type_Name is not a canonical type, use getTypeType()?");
    return 0;
}
int IR::Type_Name::max_width_bits() const {
    BUG("Type_Name is not a canonical type, use getTypeType()?");
    return 0;
}
bool IR::Type_Name::operator==(IR::Type_Name const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && path == a.path;
}
bool IR::Type_Name::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_Name &>(a_);
    return (path ? a.path ? path->equiv(*a.path) : false : a.path == nullptr);
}
void IR::Type_Name::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(path, "path");
}
void IR::Type_Name::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(path, "path");
}
void IR::Type_Name::validate() const { CHECK_NULL(path); }
void IR::Type_Name::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("path", path);
}
IR::Type_Name::Type_Name(JSONLoader &json) : Type(json) {
    json.load("path", path) || json.error("missing field path");
}
IR::Node *IR::Type_Name::fromJSON(JSONLoader &json) { return new Type_Name(json); }
bool IR::Type_Name::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Name::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Array::toString() const {
    return absl::StrCat(elementType, "[", sizeKnown() ? size->toString() : "?"_cs, "]");
}
void IR::Type_Array::dbprint(std::ostream &out) const { out << elementType << "[" << size << "]"; }
IR::Type const *IR::Type_Array::getP4Type() const {
    return new IR::Type_Array(srcInfo, elementType->getP4Type(), size);
}
int IR::Type_Array::width_bits() const { return getSize() * elementType->width_bits(); }
int IR::Type_Array::min_width_bits() const { BUG("min_width_bits on a stack: %1%", this); }
int IR::Type_Array::max_width_bits() const { BUG("max_width_bits on a stack: %1%", this); }
bool IR::Type_Array::operator==(IR::Type_Array const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && elementType == a.elementType &&
           size == a.size;
}
bool IR::Type_Array::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_Array &>(a_);
    return (elementType ? a.elementType ? elementType->equiv(*a.elementType) : false
                        : a.elementType == nullptr) &&
           (size ? a.size ? size->equiv(*a.size) : false : a.size == nullptr);
}
void IR::Type_Array::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(elementType, "elementType");
    v.visit(size, "size");
}
void IR::Type_Array::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(elementType, "elementType");
    v.visit(size, "size");
}
void IR::Type_Array::validate() const {
    CHECK_NULL(elementType);
    CHECK_NULL(size);
}
void IR::Type_Array::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("elementType", elementType);
    json.emit("size", size);
}
IR::Type_Array::Type_Array(JSONLoader &json) : Type(json) {
    json.load("elementType", elementType) || json.error("missing field elementType");
    json.load("size", size) || json.error("missing field size");
}
IR::Node *IR::Type_Array::fromJSON(JSONLoader &json) { return new Type_Array(json); }
bool IR::Type_Array::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Array::operator==(IR::Node const &a) const { return a == *this; }
void IR::Type_Specialized::validate() const {
    CHECK_NULL(baseType);
    CHECK_NULL(arguments);
    { arguments->check_null(); }
}
cstring IR::Type_Specialized::toString() const {
    return absl::StrCat(
        baseType, "<",
        absl::StrJoin(*arguments, ", ",
                      [](std::string *out, const auto *t) { absl::StrAppend(out, t); }),
        ">");
}
IR::Type_Specialized::Type_Specialized(cstring bt, std::initializer_list<const IR::Type *> args)
    : baseType(new Type_Name(bt)), arguments(new Vector<Type>(args)) {}
bool IR::Type_Specialized::operator==(IR::Type_Specialized const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && baseType == a.baseType &&
           arguments == a.arguments;
}
bool IR::Type_Specialized::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_Specialized &>(a_);
    return (baseType ? a.baseType ? baseType->equiv(*a.baseType) : false : a.baseType == nullptr) &&
           (arguments ? a.arguments ? arguments->equiv(*a.arguments) : false
                      : a.arguments == nullptr);
}
void IR::Type_Specialized::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(baseType, "baseType");
    v.visit(arguments, "arguments");
}
void IR::Type_Specialized::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(baseType, "baseType");
    v.visit(arguments, "arguments");
}
void IR::Type_Specialized::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("baseType", baseType);
    json.emit("arguments", arguments);
}
IR::Type_Specialized::Type_Specialized(JSONLoader &json) : Type(json) {
    json.load("baseType", baseType) || json.error("missing field baseType");
    json.load("arguments", arguments) || json.error("missing field arguments");
}
IR::Node *IR::Type_Specialized::fromJSON(JSONLoader &json) { return new Type_Specialized(json); }
bool IR::Type_Specialized::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Specialized::operator==(IR::Node const &a) const { return a == *this; }
void IR::Type_SpecializedCanonical::validate() const {
    CHECK_NULL(baseType);
    CHECK_NULL(arguments);
    CHECK_NULL(substituted);
    {
        arguments->check_null();
        BUG_CHECK(baseType->is<IMayBeGenericType>(), "base type %1% is not generic", baseType);
        BUG_CHECK(substituted->is<IMayBeGenericType>(), "substituted %1% is not generic",
                  substituted);
    }
}
cstring IR::Type_SpecializedCanonical::toString() const {
    return baseType->toString() + "<...>"_cs;
}
bool IR::Type_SpecializedCanonical::operator==(IR::Type_SpecializedCanonical const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && baseType == a.baseType &&
           arguments == a.arguments && substituted == a.substituted;
}
bool IR::Type_SpecializedCanonical::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_SpecializedCanonical &>(a_);
    return (baseType ? a.baseType ? baseType->equiv(*a.baseType) : false : a.baseType == nullptr) &&
           (arguments ? a.arguments ? arguments->equiv(*a.arguments) : false
                      : a.arguments == nullptr) &&
           (substituted ? a.substituted ? substituted->equiv(*a.substituted) : false
                        : a.substituted == nullptr);
}
void IR::Type_SpecializedCanonical::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(baseType, "baseType");
    v.visit(arguments, "arguments");
    v.visit(substituted, "substituted");
}
void IR::Type_SpecializedCanonical::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(baseType, "baseType");
    v.visit(arguments, "arguments");
    v.visit(substituted, "substituted");
}
void IR::Type_SpecializedCanonical::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("baseType", baseType);
    json.emit("arguments", arguments);
    json.emit("substituted", substituted);
}
IR::Type_SpecializedCanonical::Type_SpecializedCanonical(JSONLoader &json) : Type(json) {
    json.load("baseType", baseType) || json.error("missing field baseType");
    json.load("arguments", arguments) || json.error("missing field arguments");
    json.load("substituted", substituted) || json.error("missing field substituted");
}
IR::Node *IR::Type_SpecializedCanonical::fromJSON(JSONLoader &json) {
    return new Type_SpecializedCanonical(json);
}
bool IR::Type_SpecializedCanonical::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_SpecializedCanonical::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Declaration_ID::operator==(IR::Declaration_ID const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a));
}
bool IR::Declaration_ID::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    return true;
}
void IR::Declaration_ID::toJSON(JSONGenerator &json) const { Declaration::toJSON(json); }
IR::Declaration_ID::Declaration_ID(JSONLoader &json) : Declaration(json) {}
IR::Node *IR::Declaration_ID::fromJSON(JSONLoader &json) { return new Declaration_ID(json); }
bool IR::Declaration_ID::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::Declaration_ID::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::Declaration_ID::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_String::toString() const { return "string"_cs; }
bool IR::Type_String::operator==(IR::Type_String const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_String::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_String::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_String::Type_String(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_String::fromJSON(JSONLoader &json) { return new Type_String(json); }
bool IR::Type_String::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_String::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_String::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::Type_Enum::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Type_Enum::getAnnotations() { return annotations; }
Util::Enumerator<const IR::IDeclaration *> *IR::Type_Enum::getDeclarations() const {
    return members.getDeclarations();
}
const IR::IDeclaration *IR::Type_Enum::getDeclByName(cstring name) const {
    return members.getDeclaration(name);
}
const IR::IDeclaration *IR::Type_Enum::getDeclByName(std::string_view name) const {
    return members.getDeclaration(name);
}
void IR::Type_Enum::validate() const {
    annotations.validate();
    members.validate();
    { members.check_null(); }
}
bool IR::Type_Enum::operator==(IR::Type_Enum const &a) const {
    return Type_Declaration::operator==(static_cast<const Type_Declaration &>(a)) &&
           annotations == a.annotations && members == a.members;
}
bool IR::Type_Enum::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Type_Enum &>(a_);
    return annotations.equiv(a.annotations) && members.equiv(a.members);
}
void IR::Type_Enum::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    members.visit_children(v, "members");
}
void IR::Type_Enum::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    members.visit_children(v, "members");
}
void IR::Type_Enum::toJSON(JSONGenerator &json) const {
    Type_Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("members", members);
}
IR::Type_Enum::Type_Enum(JSONLoader &json) : Type_Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("members", members) || json.error("missing field members");
}
IR::Node *IR::Type_Enum::fromJSON(JSONLoader &json) { return new Type_Enum(json); }
bool IR::Type_Enum::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_Enum::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Enum::operator==(IR::Node const &a) const { return a == *this; }
void IR::SerEnumMember::validate() const {
    CHECK_NULL(value);
    { CHECK_NULL(value); }
}
bool IR::SerEnumMember::operator==(IR::SerEnumMember const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) && value == a.value;
}
bool IR::SerEnumMember::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const SerEnumMember &>(a_);
    return (value ? a.value ? value->equiv(*a.value) : false : a.value == nullptr);
}
void IR::SerEnumMember::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    v.visit(value, "value");
}
void IR::SerEnumMember::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    v.visit(value, "value");
}
void IR::SerEnumMember::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("value", value);
}
IR::SerEnumMember::SerEnumMember(JSONLoader &json) : Declaration(json) {
    json.load("value", value) || json.error("missing field value");
}
IR::Node *IR::SerEnumMember::fromJSON(JSONLoader &json) { return new SerEnumMember(json); }
bool IR::SerEnumMember::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::SerEnumMember::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::SerEnumMember::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::Type_SerEnum::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Type_SerEnum::getAnnotations() { return annotations; }
Util::Enumerator<const IR::IDeclaration *> *IR::Type_SerEnum::getDeclarations() const {
    return members.getDeclarations();
}
const IR::IDeclaration *IR::Type_SerEnum::getDeclByName(cstring name) const {
    return members.getDeclaration(name);
}
const IR::IDeclaration *IR::Type_SerEnum::getDeclByName(std::string_view name) const {
    return members.getDeclaration(name);
}
void IR::Type_SerEnum::validate() const {
    annotations.validate();
    CHECK_NULL(type);
    members.validate();
    { members.check_null(); }
}
int IR::Type_SerEnum::width_bits() const { return type->width_bits(); }
int IR::Type_SerEnum::min_width_bits() const { return type->min_width_bits(); }
int IR::Type_SerEnum::max_width_bits() const { return type->max_width_bits(); }
bool IR::Type_SerEnum::operator==(IR::Type_SerEnum const &a) const {
    return Type_Declaration::operator==(static_cast<const Type_Declaration &>(a)) &&
           annotations == a.annotations && type == a.type && members == a.members;
}
bool IR::Type_SerEnum::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Type_SerEnum &>(a_);
    return annotations.equiv(a.annotations) &&
           (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           members.equiv(a.members);
}
void IR::Type_SerEnum::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    members.visit_children(v, "members");
}
void IR::Type_SerEnum::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    members.visit_children(v, "members");
}
void IR::Type_SerEnum::toJSON(JSONGenerator &json) const {
    Type_Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("type", type);
    json.emit("members", members);
}
IR::Type_SerEnum::Type_SerEnum(JSONLoader &json) : Type_Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("type", type) || json.error("missing field type");
    json.load("members", members) || json.error("missing field members");
}
IR::Node *IR::Type_SerEnum::fromJSON(JSONLoader &json) { return new Type_SerEnum(json); }
bool IR::Type_SerEnum::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_SerEnum::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_SerEnum::operator==(IR::Node const &a) const { return a == *this; }
const IR::ParameterList *IR::Type_Table::getApplyParameters() const { return new ParameterList(); }
/// names for the fields of the struct returned
/// by applying a table
IR::Type const *IR::Type_Table::getP4Type() const { return nullptr; }
void IR::Type_Table::dbprint(std::ostream &out) const { out << table->name; }
bool IR::Type_Table::operator==(IR::Type_Table const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && table == a.table;
}
bool IR::Type_Table::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_Table &>(a_);
    return (table ? a.table ? table->equiv(*a.table) : false : a.table == nullptr);
}
void IR::Type_Table::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(table, "table");
}
void IR::Type_Table::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(table, "table");
}
void IR::Type_Table::validate() const { CHECK_NULL(table); }
void IR::Type_Table::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("table", table);
}
IR::Type_Table::Type_Table(JSONLoader &json) : Type(json) {
    json.load("table", table) || json.error("missing field table");
}
IR::Node *IR::Type_Table::fromJSON(JSONLoader &json) { return new Type_Table(json); }
bool IR::Type_Table::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Table::operator==(IR::Node const &a) const { return a == *this; }
IR::Type const *IR::Type_ActionEnum::getP4Type() const { return nullptr; }
bool IR::Type_ActionEnum::operator==(IR::Type_ActionEnum const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && actionList == a.actionList;
}
bool IR::Type_ActionEnum::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_ActionEnum &>(a_);
    return (actionList ? a.actionList ? actionList->equiv(*a.actionList) : false
                       : a.actionList == nullptr);
}
void IR::Type_ActionEnum::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(actionList, "actionList");
}
void IR::Type_ActionEnum::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(actionList, "actionList");
}
void IR::Type_ActionEnum::validate() const { CHECK_NULL(actionList); }
void IR::Type_ActionEnum::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("actionList", actionList);
}
IR::Type_ActionEnum::Type_ActionEnum(JSONLoader &json) : Type(json) {
    json.load("actionList", actionList) || json.error("missing field actionList");
}
IR::Node *IR::Type_ActionEnum::fromJSON(JSONLoader &json) { return new Type_ActionEnum(json); }
bool IR::Type_ActionEnum::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_ActionEnum::operator==(IR::Node const &a) const { return a == *this; }
const IR::TypeParameters *IR::Type_MethodBase::getTypeParameters() const { return typeParameters; }
cstring IR::Type_MethodBase::toString() const { return "<Method>"_cs; }
IR::Type const *IR::Type_MethodBase::getP4Type() const { return nullptr; }
Util::Enumerator<const IR::IDeclaration *> *IR::Type_MethodBase::getDeclarations() const {
    return typeParameters->getDeclarations()->concat(parameters->getDeclarations());
}
const IR::IDeclaration *IR::Type_MethodBase::getDeclByName(cstring name) const {
    auto decl = parameters->getDeclByName(name);
    if (!decl) decl = typeParameters->getDeclByName(name);
    return decl;
}
const IR::IDeclaration *IR::Type_MethodBase::getDeclByName(std::string_view name) const {
    auto decl = parameters->getDeclByName(name);
    if (!decl) decl = typeParameters->getDeclByName(name);
    return decl;
}
bool IR::Type_MethodBase::operator==(IR::Type_MethodBase const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && typeParameters == a.typeParameters &&
           returnType == a.returnType && parameters == a.parameters;
}
bool IR::Type_MethodBase::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_MethodBase &>(a_);
    return (typeParameters ? a.typeParameters ? typeParameters->equiv(*a.typeParameters) : false
                           : a.typeParameters == nullptr) &&
           (returnType ? a.returnType ? returnType->equiv(*a.returnType) : false
                       : a.returnType == nullptr) &&
           (parameters ? a.parameters ? parameters->equiv(*a.parameters) : false
                       : a.parameters == nullptr);
}
void IR::Type_MethodBase::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(typeParameters, "typeParameters");
    v.visit(returnType, "returnType");
    v.visit(parameters, "parameters");
}
void IR::Type_MethodBase::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(typeParameters, "typeParameters");
    v.visit(returnType, "returnType");
    v.visit(parameters, "parameters");
}
void IR::Type_MethodBase::validate() const {
    CHECK_NULL(typeParameters);
    CHECK_NULL(parameters);
}
void IR::Type_MethodBase::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("typeParameters", typeParameters);
    if (returnType != nullptr) json.emit("returnType", returnType);
    json.emit("parameters", parameters);
}
IR::Type_MethodBase::Type_MethodBase(JSONLoader &json) : Type(json) {
    json.load("typeParameters", typeParameters) || json.error("missing field typeParameters");
    json.load("returnType", returnType);
    json.load("parameters", parameters) || json.error("missing field parameters");
}
bool IR::Type_MethodBase::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_MethodBase::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Method::toString() const { return name; }
bool IR::Type_Method::operator==(IR::Type_Method const &a) const {
    return Type_MethodBase::operator==(static_cast<const Type_MethodBase &>(a)) && name == a.name;
}
bool IR::Type_Method::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_MethodBase::equiv(a_)) return false;
    auto &a = static_cast<const Type_Method &>(a_);
    return name == a.name;
}
void IR::Type_Method::dump_fields(std::ostream &out) const {
    Type_MethodBase::dump_fields(out);
    out << " name=" << name;
}
void IR::Type_Method::toJSON(JSONGenerator &json) const {
    Type_MethodBase::toJSON(json);
    json.emit("name", name);
}
IR::Type_Method::Type_Method(JSONLoader &json) : Type_MethodBase(json) {
    json.load("name", name) || json.error("missing field name");
}
IR::Node *IR::Type_Method::fromJSON(JSONLoader &json) { return new Type_Method(json); }
bool IR::Type_Method::operator==(IR::Type_MethodBase const &a) const { return a == *this; }
bool IR::Type_Method::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Method::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::ArgumentInfo::toString() const { return argument->toString(); }
bool IR::ArgumentInfo::operator==(IR::ArgumentInfo const &a) const {
    return this->typeId() == a.typeId() && leftValue == a.leftValue &&
           compileTimeConstant == a.compileTimeConstant && type == a.type && argument == a.argument;
}
bool IR::ArgumentInfo::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const ArgumentInfo &>(a_);
    return leftValue == a.leftValue && compileTimeConstant == a.compileTimeConstant &&
           (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           (argument ? a.argument ? argument->equiv(*a.argument) : false : a.argument == nullptr);
}
void IR::ArgumentInfo::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    v.visit(type, "type");
    v.visit(argument, "argument");
}
void IR::ArgumentInfo::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    v.visit(type, "type");
    v.visit(argument, "argument");
}
void IR::ArgumentInfo::validate() const {
    CHECK_NULL(type);
    CHECK_NULL(argument);
}
void IR::ArgumentInfo::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " leftValue=" << leftValue;
    out << " compileTimeConstant=" << compileTimeConstant;
}
void IR::ArgumentInfo::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("leftValue", leftValue);
    json.emit("compileTimeConstant", compileTimeConstant);
    json.emit("type", type);
    json.emit("argument", argument);
}
IR::ArgumentInfo::ArgumentInfo(JSONLoader &json) : Node(json) {
    json.load("leftValue", leftValue) || json.error("missing field leftValue");
    json.load("compileTimeConstant", compileTimeConstant) ||
        json.error("missing field compileTimeConstant");
    json.load("type", type) || json.error("missing field type");
    json.load("argument", argument) || json.error("missing field argument");
}
IR::Node *IR::ArgumentInfo::fromJSON(JSONLoader &json) { return new ArgumentInfo(json); }
bool IR::ArgumentInfo::operator==(IR::Node const &a) const { return a == *this; }
void IR::Type_MethodCall::validate() const {
    CHECK_NULL(typeArguments);
    CHECK_NULL(returnType);
    CHECK_NULL(arguments);
    {
        typeArguments->check_null();
        arguments->check_null();
    }
}
IR::Type const *IR::Type_MethodCall::getP4Type() const { return nullptr; }
cstring IR::Type_MethodCall::toString() const { return "<Method call>"_cs; }
bool IR::Type_MethodCall::operator==(IR::Type_MethodCall const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && typeArguments == a.typeArguments &&
           returnType == a.returnType && arguments == a.arguments;
}
bool IR::Type_MethodCall::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_MethodCall &>(a_);
    return (typeArguments ? a.typeArguments ? typeArguments->equiv(*a.typeArguments) : false
                          : a.typeArguments == nullptr) &&
           (returnType ? a.returnType ? returnType->equiv(*a.returnType) : false
                       : a.returnType == nullptr) &&
           (arguments ? a.arguments ? arguments->equiv(*a.arguments) : false
                      : a.arguments == nullptr);
}
void IR::Type_MethodCall::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type::visit_children(v, n);
    v.visit(typeArguments, "typeArguments");
    v.visit(returnType, "returnType");
    v.visit(arguments, "arguments");
}
void IR::Type_MethodCall::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type::visit_children(v, n);
    v.visit(typeArguments, "typeArguments");
    v.visit(returnType, "returnType");
    v.visit(arguments, "arguments");
}
void IR::Type_MethodCall::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("typeArguments", typeArguments);
    json.emit("returnType", returnType);
    json.emit("arguments", arguments);
}
IR::Type_MethodCall::Type_MethodCall(JSONLoader &json) : Type(json) {
    json.load("typeArguments", typeArguments) || json.error("missing field typeArguments");
    json.load("returnType", returnType) || json.error("missing field returnType");
    json.load("arguments", arguments) || json.error("missing field arguments");
}
IR::Node *IR::Type_MethodCall::fromJSON(JSONLoader &json) { return new Type_MethodCall(json); }
bool IR::Type_MethodCall::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_MethodCall::operator==(IR::Node const &a) const { return a == *this; }
bool IR::Type_Action::operator==(IR::Type_Action const &a) const {
    return Type_MethodBase::operator==(static_cast<const Type_MethodBase &>(a));
}
bool IR::Type_Action::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_MethodBase::equiv(a_)) return false;
    return true;
}
void IR::Type_Action::toJSON(JSONGenerator &json) const { Type_MethodBase::toJSON(json); }
IR::Type_Action::Type_Action(JSONLoader &json) : Type_MethodBase(json) {}
IR::Node *IR::Type_Action::fromJSON(JSONLoader &json) { return new Type_Action(json); }
bool IR::Type_Action::operator==(IR::Type_MethodBase const &a) const { return a == *this; }
bool IR::Type_Action::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Action::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::Method::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Method::getAnnotations() { return annotations; }
const IR::ParameterList *IR::Method::getParameters() const { return type->parameters; }

const IR::IDeclaration *IR::Method::getDeclByName(cstring name) const {
    return type->parameters->getDeclByName(name);
}
const IR::IDeclaration *IR::Method::getDeclByName(std::string_view name) const {
    return type->parameters->getDeclByName(name);
}
Util::Enumerator<const IR::IDeclaration *> *IR::Method::getDeclarations() const {
    return type->parameters->getDeclarations();
}
bool IR::Method::operator==(IR::Method const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) && type == a.type &&
           isAbstract == a.isAbstract && annotations == a.annotations;
}
bool IR::Method::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Method &>(a_);
    return (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           isAbstract == a.isAbstract && annotations.equiv(a.annotations);
}
void IR::Method::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    v.visit(type, "type");
    annotations.visit_children(v, "annotations");
}
void IR::Method::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    v.visit(type, "type");
    annotations.visit_children(v, "annotations");
}
void IR::Method::validate() const {
    CHECK_NULL(type);
    annotations.validate();
}
void IR::Method::dump_fields(std::ostream &out) const {
    Declaration::dump_fields(out);
    out << " isAbstract=" << isAbstract;
}
void IR::Method::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("type", type);
    json.emit("isAbstract", isAbstract);
    json.emit("annotations", annotations);
}
IR::Method::Method(JSONLoader &json) : Declaration(json) {
    json.load("type", type) || json.error("missing field type");
    json.load("isAbstract", isAbstract) || json.error("missing field isAbstract");
    json.load("annotations", annotations) || json.error("missing field annotations");
}
IR::Node *IR::Method::fromJSON(JSONLoader &json) { return new Method(json); }
bool IR::Method::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::Method::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::Method::operator==(IR::Node const &a) const { return a == *this; }
int IR::Type_Typedef::width_bits() const { return type->width_bits(); }
int IR::Type_Typedef::min_width_bits() const { return type->min_width_bits(); }
int IR::Type_Typedef::max_width_bits() const { return type->max_width_bits(); }
IR::Vector<IR::Annotation> const &IR::Type_Typedef::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Type_Typedef::getAnnotations() { return annotations; }
bool IR::Type_Typedef::operator==(IR::Type_Typedef const &a) const {
    return Type_Declaration::operator==(static_cast<const Type_Declaration &>(a)) &&
           annotations == a.annotations && type == a.type;
}
bool IR::Type_Typedef::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Type_Typedef &>(a_);
    return annotations.equiv(a.annotations) &&
           (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr);
}
void IR::Type_Typedef::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
}
void IR::Type_Typedef::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
}
void IR::Type_Typedef::validate() const {
    annotations.validate();
    CHECK_NULL(type);
}
void IR::Type_Typedef::toJSON(JSONGenerator &json) const {
    Type_Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("type", type);
}
IR::Type_Typedef::Type_Typedef(JSONLoader &json) : Type_Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("type", type) || json.error("missing field type");
}
IR::Node *IR::Type_Typedef::fromJSON(JSONLoader &json) { return new Type_Typedef(json); }
bool IR::Type_Typedef::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_Typedef::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Typedef::operator==(IR::Node const &a) const { return a == *this; }
int IR::Type_Newtype::width_bits() const { return type->width_bits(); }
int IR::Type_Newtype::min_width_bits() const { return type->min_width_bits(); }
int IR::Type_Newtype::max_width_bits() const { return type->max_width_bits(); }
IR::Vector<IR::Annotation> const &IR::Type_Newtype::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Type_Newtype::getAnnotations() { return annotations; }
bool IR::Type_Newtype::operator==(IR::Type_Newtype const &a) const {
    return Type_Declaration::operator==(static_cast<const Type_Declaration &>(a)) &&
           annotations == a.annotations && type == a.type;
}
bool IR::Type_Newtype::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Type_Newtype &>(a_);
    return annotations.equiv(a.annotations) &&
           (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr);
}
void IR::Type_Newtype::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
}
void IR::Type_Newtype::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
}
void IR::Type_Newtype::validate() const {
    annotations.validate();
    CHECK_NULL(type);
}
void IR::Type_Newtype::toJSON(JSONGenerator &json) const {
    Type_Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("type", type);
}
IR::Type_Newtype::Type_Newtype(JSONLoader &json) : Type_Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("type", type) || json.error("missing field type");
}
IR::Node *IR::Type_Newtype::fromJSON(JSONLoader &json) { return new Type_Newtype(json); }
bool IR::Type_Newtype::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_Newtype::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Newtype::operator==(IR::Node const &a) const { return a == *this; }
std::vector<const IR::INamespace *> IR::Type_Extern::getNestedNamespaces() const {
    return {typeParameters};
}
Util::Enumerator<const IR::IDeclaration *> *IR::Type_Extern::getDeclarations() const {
    return attributes.valueEnumerator()->as<const IDeclaration *>()->concat(
        methods.getEnumerator()->as<const IDeclaration *>());
}
const IR::TypeParameters *IR::Type_Extern::getTypeParameters() const { return typeParameters; }
void IR::Type_Extern::validate() const {
    CHECK_NULL(typeParameters);
    methods.validate();
    attributes.validate();
    annotations.validate();
    { methods.check_null(); }
}
IR::Vector<IR::Annotation> const &IR::Type_Extern::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Type_Extern::getAnnotations() { return annotations; }
/// Returns the method that matches the specified arguments.
/// Returns nullptr if no method or more than one method match.
/// In the latter case it also reports an error.
/// Returns the constructor that matches the specified arguments.
/// Returns nullptr if no constructor or more than one constructor matches.
/// In the latter case it also reports an error.
const IR::Method *IR::Type_Extern::lookupConstructor(
    const IR::Vector<IR::Argument> *arguments) const {
    return lookupMethod(name, arguments);
}
bool IR::Type_Extern::operator==(IR::Type_Extern const &a) const {
    return Type_Declaration::operator==(static_cast<const Type_Declaration &>(a)) &&
           typeParameters == a.typeParameters && methods == a.methods &&
           attributes == a.attributes && annotations == a.annotations;
}
bool IR::Type_Extern::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Type_Extern &>(a_);
    return (typeParameters ? a.typeParameters ? typeParameters->equiv(*a.typeParameters) : false
                           : a.typeParameters == nullptr) &&
           methods.equiv(a.methods) && attributes.equiv(a.attributes) &&
           annotations.equiv(a.annotations);
}
void IR::Type_Extern::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Declaration::visit_children(v, n);
    v.visit(typeParameters, "typeParameters");
    methods.visit_children(v, "methods");
    attributes.visit_children(v, "attributes");
    annotations.visit_children(v, "annotations");
}
void IR::Type_Extern::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Declaration::visit_children(v, n);
    v.visit(typeParameters, "typeParameters");
    methods.visit_children(v, "methods");
    attributes.visit_children(v, "attributes");
    annotations.visit_children(v, "annotations");
}
void IR::Type_Extern::toJSON(JSONGenerator &json) const {
    Type_Declaration::toJSON(json);
    json.emit("typeParameters", typeParameters);
    json.emit("methods", methods);
    json.emit("attributes", attributes);
    json.emit("annotations", annotations);
}
IR::Type_Extern::Type_Extern(JSONLoader &json) : Type_Declaration(json) {
    json.load("typeParameters", typeParameters) || json.error("missing field typeParameters");
    json.load("methods", methods) || json.error("missing field methods");
    json.load("attributes", attributes) || json.error("missing field attributes");
    json.load("annotations", annotations) || json.error("missing field annotations");
}
IR::Node *IR::Type_Extern::fromJSON(JSONLoader &json) { return new Type_Extern(json); }
bool IR::Type_Extern::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_Extern::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Extern::operator==(IR::Node const &a) const { return a == *this; }
