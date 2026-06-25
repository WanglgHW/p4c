#include "ir/ir-generated.h"   // IWYU pragma: keep

#include "ir/ir-inline.h"      // IWYU pragma: keep
#include "ir/json_generator.h" // IWYU pragma: keep
#include "ir/json_loader.h"    // IWYU pragma: keep
#include "ir/visitor.h"        // IWYU pragma: keep
#include "lib/algorithm.h"     // IWYU pragma: keep
#include "lib/log.h"           // IWYU pragma: keep

using namespace P4;

// Method definitions for the base IR classes (interfaces, Type / StatOrDecl /
// Expression / Operation roots, plus Path, Annotation, Argument).

bool IR::CompileTimeValue::equiv(IR::CompileTimeValue const &other) const {
    return this->getNode()->equiv(*other.getNode());
}
int IR::Type::width_bits() const { BUG("width_bits() on type with unknown size: %1%", this); }
int IR::Type::min_width_bits() const { BUG("min_width_bits() on type of unknown size: %1%", this); }
int IR::Type::max_width_bits() const { BUG("max_width_bits() on type of unknown size: %1%", this); }
int IR::Type::min_or_fixed_width_bits() const {
    BUG("min_or_fixed_width_bits() on type of unknown size: %1%", this);
}
int IR::Type::max_or_fixed_width_bits() const {
    BUG("max_or_fixed_width_bits() on type of unknown size: %1%", this);
}
bool IR::Type::variable() const { return false; }
/// When possible returns the corresponding type that can be inserted
/// in a P4 program; may return a Type_Name
bool IR::Type::operator==(IR::Type const &a) const { return this->typeId() == a.typeId(); }
bool IR::Type::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    return true;
}
void IR::Type::toJSON(JSONGenerator &json) const { Node::toJSON(json); }
IR::Type::Type(JSONLoader &json) : Node(json) {}
bool IR::Type::operator==(IR::Node const &a) const { return a == *this; }
void IR::IGeneralNamespace::validate() const { checkDuplicateDeclarations(); }
const IR::ParameterList *IR::IContainer::getParameters() const {
    return getConstructorParameters();
}
IR::Type const *IR::Type_Base::getP4Type() const { return this; }
bool IR::Type_Base::variable() const { return false; }
bool IR::Type_Base::operator==(IR::Type_Base const &a) const {
    return Type::operator==(static_cast<const Type &>(a));
}
bool IR::Type_Base::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    return true;
}
void IR::Type_Base::toJSON(JSONGenerator &json) const { Type::toJSON(json); }
IR::Type_Base::Type_Base(JSONLoader &json) : Type(json) {}
bool IR::Type_Base::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Base::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Type_Unknown::toString() const { return "Unknown type"_cs; }
bool IR::Type_Unknown::operator==(IR::Type_Unknown const &a) const {
    return Type_Base::operator==(static_cast<const Type_Base &>(a));
}
bool IR::Type_Unknown::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Base::equiv(a_)) return false;
    return true;
}
void IR::Type_Unknown::toJSON(JSONGenerator &json) const { Type_Base::toJSON(json); }
IR::Type_Unknown::Type_Unknown(JSONLoader &json) : Type_Base(json) {}
IR::Node *IR::Type_Unknown::fromJSON(JSONLoader &json) { return new Type_Unknown(json); }
bool IR::Type_Unknown::operator==(IR::Type_Base const &a) const { return a == *this; }
bool IR::Type_Unknown::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Unknown::operator==(IR::Node const &a) const { return a == *this; }
bool IR::StatOrDecl::operator==(IR::StatOrDecl const &a) const {
    return this->typeId() == a.typeId();
}
bool IR::StatOrDecl::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    return true;
}
void IR::StatOrDecl::toJSON(JSONGenerator &json) const { Node::toJSON(json); }
IR::StatOrDecl::StatOrDecl(JSONLoader &json) : Node(json) {}
bool IR::StatOrDecl::operator==(IR::Node const &a) const { return a == *this; }
IR::ID IR::Declaration::getName() const { return name; }
bool IR::Declaration::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!StatOrDecl::equiv(a_)) return false;
    auto &a = static_cast<const Declaration &>(a_);

    { return name == a.name; /* ignore declid */ }
}
cstring IR::Declaration::toString() const { return externalName(); }
bool IR::Declaration::operator==(IR::Declaration const &a) const {
    return StatOrDecl::operator==(static_cast<const StatOrDecl &>(a)) && name == a.name &&
           declid == a.declid;
}
void IR::Declaration::dump_fields(std::ostream &out) const {
    StatOrDecl::dump_fields(out);
    out << " name=" << name;
    out << " declid=" << declid;
}
void IR::Declaration::toJSON(JSONGenerator &json) const {
    StatOrDecl::toJSON(json);
    json.emit("name", name);
    json.emit("declid", declid);
}
IR::Declaration::Declaration(JSONLoader &json) : StatOrDecl(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("declid", declid) || json.error("missing field declid");
}
bool IR::Declaration::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::Declaration::operator==(IR::Node const &a) const { return a == *this; }
IR::ID IR::Type_Declaration::getName() const { return name; }
bool IR::Type_Declaration::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type::equiv(a_)) return false;
    auto &a = static_cast<const Type_Declaration &>(a_);

    { return name == a.name; /* ignore declid */ }
}
cstring IR::Type_Declaration::toString() const { return externalName(); }
IR::Type const *IR::Type_Declaration::getP4Type() const { return new Type_Name(name); }
bool IR::Type_Declaration::operator==(IR::Type_Declaration const &a) const {
    return Type::operator==(static_cast<const Type &>(a)) && name == a.name && declid == a.declid;
}
void IR::Type_Declaration::dump_fields(std::ostream &out) const {
    Type::dump_fields(out);
    out << " name=" << name;
    out << " declid=" << declid;
}
void IR::Type_Declaration::toJSON(JSONGenerator &json) const {
    Type::toJSON(json);
    json.emit("name", name);
    json.emit("declid", declid);
}
IR::Type_Declaration::Type_Declaration(JSONLoader &json) : Type(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("declid", declid) || json.error("missing field declid");
}
bool IR::Type_Declaration::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Declaration::operator==(IR::Node const &a) const { return a == *this; }
void IR::Expression::visit_children(Visitor &v, char const *n) {
    (void)v;
    (void)n;
}
void IR::Expression::visit_children(Visitor &v, char const *n) const {
    (void)v;
    (void)n;
}
IRNODE_DEFINE_APPLY_OVERLOAD(Expression, , )
bool IR::Expression::operator==(IR::Expression const &a) const {
    return this->typeId() == a.typeId() && type == a.type;
}
bool IR::Expression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const Expression &>(a_);
    return (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr);
}
void IR::Expression::validate() const { CHECK_NULL(type); }
void IR::Expression::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("type", type);
}
IR::Expression::Expression(JSONLoader &json) : Node(json) {
    json.load("type", type) || json.error("missing field type");
}
bool IR::Expression::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Operation::toString() const { return getStringOp(); }
bool IR::Operation::operator==(IR::Operation const &a) const {
    return Expression::operator==(static_cast<const Expression &>(a));
}
bool IR::Operation::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Expression::equiv(a_)) return false;
    return true;
}
void IR::Operation::toJSON(JSONGenerator &json) const { Expression::toJSON(json); }
IR::Operation::Operation(JSONLoader &json) : Expression(json) {}
bool IR::Operation::operator==(IR::Expression const &a) const { return a == *this; }
bool IR::Operation::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::Path::toString() const {
    // This is the ORIGINAL name the user used
    return absl::StrCat(absolute ? "." : "", name.toString());
}
void IR::Path::dbprint(std::ostream &out) const { out << name; }
void IR::Path::validate() const {
    { BUG_CHECK(!name.name.isNullOrEmpty(), "Empty path"); }
}
bool IR::Path::operator==(IR::Path const &a) const {
    return this->typeId() == a.typeId() && name == a.name && absolute == a.absolute;
}
bool IR::Path::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const Path &>(a_);
    return name == a.name && absolute == a.absolute;
}
void IR::Path::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
    out << " absolute=" << absolute;
}
void IR::Path::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    json.emit("absolute", absolute);
}
IR::Path::Path(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("absolute", absolute) || json.error("missing field absolute");
}
IR::Node *IR::Path::fromJSON(JSONLoader &json) { return new Path(json); }
bool IR::Path::operator==(IR::Node const &a) const { return a == *this; }
bool IR::NamedExpression::operator==(IR::NamedExpression const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           expression == a.expression;
}
bool IR::NamedExpression::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const NamedExpression &>(a_);
    return (expression ? a.expression ? expression->equiv(*a.expression) : false
                       : a.expression == nullptr);
}
void IR::NamedExpression::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::NamedExpression::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::NamedExpression::validate() const { CHECK_NULL(expression); }
void IR::NamedExpression::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("expression", expression);
}
IR::NamedExpression::NamedExpression(JSONLoader &json) : Declaration(json) {
    json.load("expression", expression) || json.error("missing field expression");
}
IR::Node *IR::NamedExpression::fromJSON(JSONLoader &json) { return new NamedExpression(json); }
bool IR::NamedExpression::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::NamedExpression::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::NamedExpression::operator==(IR::Node const &a) const { return a == *this; }
void IR::AnnotationToken::dbprint(std::ostream &out) const { out << text; }
bool IR::AnnotationToken::operator==(IR::AnnotationToken const &a) const {
    return this->typeId() == a.typeId() && token_type == a.token_type && text == a.text &&
           constInfo == a.constInfo;
}
bool IR::AnnotationToken::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const AnnotationToken &>(a_);
    return token_type == a.token_type && text == a.text && constInfo == a.constInfo;
}
void IR::AnnotationToken::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " token_type=" << token_type;
    out << " text=" << text;
    out << " constInfo=" << constInfo;
}
void IR::AnnotationToken::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("token_type", token_type);
    json.emit("text", text);
    if (constInfo != nullptr) json.emit("constInfo", constInfo);
}
IR::AnnotationToken::AnnotationToken(JSONLoader &json) : Node(json) {
    json.load("token_type", token_type) || json.error("missing field token_type");
    json.load("text", text) || json.error("missing field text");
    json.load("constInfo", constInfo);
}
IR::Node *IR::AnnotationToken::fromJSON(JSONLoader &json) { return new AnnotationToken(json); }
bool IR::AnnotationToken::operator==(IR::Node const &a) const { return a == *this; }
IR::Annotation::Annotation(IR::ID n, intmax_t v, bool structured)
    : name(n), structured(structured) {
    body.emplace<ExpressionAnnotation>(new Constant(v));
}

IR::Annotation::Annotation(IR::ID n, cstring v, bool structured) : name(n), structured(structured) {
    body.emplace<ExpressionAnnotation>(new StringLiteral(v));
}

/// Indicates the control-plane name.
/// Action cannot be a default_action.
/// action can only be a default_action.
/// Code should be executed atomically.
/// Object should not be exposed to the control-plane.
/// P4-14 annotation for varbit fields.
/// P4-14 annotation for varbit fields.
/// Optional parameter annotation
/// Package documentation annotation.
/// Deprecation annotation.
/// Synchronous annotation.
/// extern function/method annotation.
/// extern function/method annotation.
/// noWarn annotation.
/// Match annotation (for value sets).
/// Used for recirculate, etc.
/// Used by compiler implementer to limit debug log to the annotated IR context.
/// annotation to disable certain optimization
/// annotation to mark block of inlined function
/// annotation for likely taken blocks/branchs
/// annotation for likely not taken blocks/branchs
cstring IR::Annotation::toString() const { return absl::StrCat("@", name); }
void IR::Annotation::validate() const {
    std::visit(
        [&](auto &&variant) {
            using T = std::decay_t<decltype(variant)>;
            if constexpr (std::is_same_v<T, IR::Vector<IR::AnnotationToken>>) {
                variant.validate();
            } else if constexpr (std::is_same_v<T, IR::Vector<IR::Expression>>) {
                variant.validate();
            } else if constexpr (std::is_same_v<T, IR::IndexedVector<IR::NamedExpression>>) {
                variant.validate();
            } else {
                BUG("Unexpected variant field");
            }
        },
        body);

    { BUG_CHECK(!name.name.isNullOrEmpty(), "empty annotation name"); }
}
/// Extracts name value from a name annotation
/// Extracts a single string argument; cstring::empty if the argument is not a string;
/// if error is true, emits an error if the argument is not a string
/// Whether the annotation body needs to be parsed.

/// If this is true this is a structured annotation, and there are some
/// constraints on its contents.
bool IR::Annotation::operator==(IR::Annotation const &a) const {
    return this->typeId() == a.typeId() && name == a.name && body == a.body &&
           structured == a.structured;
}
bool IR::Annotation::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const Annotation &>(a_);
    auto body_equivVisitor = [&](auto &&variant) -> bool {
        using T = std::decay_t<decltype(variant)>;
        if constexpr (std::is_same_v<T, Vector<AnnotationToken>>) {
            return variant.equiv(std::get<IR::Vector<IR::AnnotationToken>>(a.body));
        } else if constexpr (std::is_same_v<T, Vector<Expression>>) {
            return variant.equiv(std::get<IR::Vector<IR::Expression>>(a.body));
        } else if constexpr (std::is_same_v<T, IndexedVector<NamedExpression>>) {
            return variant.equiv(std::get<IR::IndexedVector<IR::NamedExpression>>(a.body));
        } else {
            BUG("Unexpected variant field");
        }
    };
    return name == a.name && body.index() == a.body.index() &&
           std::visit(body_equivVisitor, body) && structured == a.structured;
}
void IR::Annotation::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    std::visit(
        [&](auto &&variant) {
            using T = std::decay_t<decltype(variant)>;
            if constexpr (std::is_same_v<T, IR::Vector<IR::AnnotationToken>>) {
                v.visit(variant, "body::IR::Vector<IR::AnnotationToken>");
            } else if constexpr (std::is_same_v<T, IR::Vector<IR::Expression>>) {
                v.visit(variant, "body::IR::Vector<IR::Expression>");
            } else if constexpr (std::is_same_v<T, IR::IndexedVector<IR::NamedExpression>>) {
                v.visit(variant, "body::IR::IndexedVector<IR::NamedExpression>");
            } else {
                BUG("Unexpected variant field");
            }
        },
        body);
}
void IR::Annotation::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    std::visit(
        [&](auto &&variant) {
            using T = std::decay_t<decltype(variant)>;
            if constexpr (std::is_same_v<T, IR::Vector<IR::AnnotationToken>>) {
                v.visit(variant, "body::IR::Vector<IR::AnnotationToken>");
            } else if constexpr (std::is_same_v<T, IR::Vector<IR::Expression>>) {
                v.visit(variant, "body::IR::Vector<IR::Expression>");
            } else if constexpr (std::is_same_v<T, IR::IndexedVector<IR::NamedExpression>>) {
                v.visit(variant, "body::IR::IndexedVector<IR::NamedExpression>");
            } else {
                BUG("Unexpected variant field");
            }
        },
        body);
}
void IR::Annotation::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
    std::visit(
        [&](auto &&variant) {
            using T = std::decay_t<decltype(variant)>;
            if constexpr (std::is_same_v<T, IR::Vector<IR::AnnotationToken>>) {
            } else if constexpr (std::is_same_v<T, IR::Vector<IR::Expression>>) {
            } else if constexpr (std::is_same_v<T, IR::IndexedVector<IR::NamedExpression>>) {
            } else {
                BUG("Unexpected variant field");
            }
        },
        body);
    out << " structured=" << structured;
}
void IR::Annotation::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    json.emit("body", body);
    json.emit("structured", structured);
}
IR::Annotation::Annotation(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("body", body) || json.error("missing field body");
    json.load("structured", structured) || json.error("missing field structured");
}
IR::Node *IR::Annotation::fromJSON(JSONLoader &json) { return new Annotation(json); }
bool IR::Annotation::operator==(IR::Node const &a) const { return a == *this; }
void IR::Argument::dbprint(std::ostream &out) const {
    out << (name.name.isNullOrEmpty() ? "" : name.name + " = ") << expression;
}
void IR::Argument::validate() const {
    CHECK_NULL(expression);
    { CHECK_NULL(expression); }
}
cstring IR::Argument::toString() const {
    std::string result = "";
    if (!name.name.isNullOrEmpty()) absl::StrAppend(&result, name, " = ");
    return absl::StrCat(result, expression);
}
bool IR::Argument::operator==(IR::Argument const &a) const {
    return this->typeId() == a.typeId() && name == a.name && expression == a.expression;
}
bool IR::Argument::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const Argument &>(a_);
    return name == a.name && (expression ? a.expression ? expression->equiv(*a.expression) : false
                                         : a.expression == nullptr);
}
void IR::Argument::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::Argument::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::Argument::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " name=" << name;
}
void IR::Argument::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("name", name);
    json.emit("expression", expression);
}
IR::Argument::Argument(JSONLoader &json) : Node(json) {
    json.load("name", name) || json.error("missing field name");
    json.load("expression", expression) || json.error("missing field expression");
}
IR::Node *IR::Argument::fromJSON(JSONLoader &json) { return new Argument(json); }
bool IR::Argument::operator==(IR::Node const &a) const { return a == *this; }
