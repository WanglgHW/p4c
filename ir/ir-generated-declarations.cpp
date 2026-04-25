#include "ir/ir-generated.h"   // IWYU pragma: keep

#include "ir/ir-inline.h"      // IWYU pragma: keep
#include "ir/json_generator.h" // IWYU pragma: keep
#include "ir/json_loader.h"    // IWYU pragma: keep
#include "ir/visitor.h"        // IWYU pragma: keep
#include "lib/algorithm.h"     // IWYU pragma: keep
#include "lib/log.h"           // IWYU pragma: keep

using namespace P4;

// Method definitions for top-level P4 declarations.

IR::Vector<IR::Annotation> const &IR::ParserState::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::ParserState::getAnnotations() { return annotations; }
Util::Enumerator<const IR::IDeclaration *> *IR::ParserState::getDeclarations() const {
    return components.getDeclarations();
}
IR::IDeclaration const *IR::ParserState::getDeclByName(cstring name) const {
    return components.getDeclaration(name);
}
IR::IDeclaration const *IR::ParserState::getDeclByName(std::string_view name) const {
    return components.getDeclaration(name);
}
void IR::ParserState::validate() const {
    annotations.validate();
    components.validate();
    {
        if (selectExpression != nullptr)
            BUG_CHECK(selectExpression->is<IR::PathExpression>() ||
                          selectExpression->is<IR::SelectExpression>(),
                      "%1%: unexpected select expression", selectExpression);
    }
}
bool IR::ParserState::operator==(IR::ParserState const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           annotations == a.annotations && components == a.components &&
           selectExpression == a.selectExpression;
}
bool IR::ParserState::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const ParserState &>(a_);
    return annotations.equiv(a.annotations) && components.equiv(a.components) &&
           (selectExpression
                ? a.selectExpression ? selectExpression->equiv(*a.selectExpression) : false
                : a.selectExpression == nullptr);
}
void IR::ParserState::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    components.visit_children(v, "components");
    v.visit(selectExpression, "selectExpression");
}
void IR::ParserState::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    components.visit_children(v, "components");
    v.visit(selectExpression, "selectExpression");
}
void IR::ParserState::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("components", components);
    if (selectExpression != nullptr) json.emit("selectExpression", selectExpression);
}
IR::ParserState::ParserState(JSONLoader &json) : Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("components", components) || json.error("missing field components");
    json.load("selectExpression", selectExpression);
}
IR::Node *IR::ParserState::fromJSON(JSONLoader &json) { return new ParserState(json); }
bool IR::ParserState::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::ParserState::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::ParserState::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::P4Parser::getAnnotations() const {
    return type->getAnnotations();
}
IR::Vector<IR::Annotation> &IR::P4Parser::getAnnotations() {
    BUG("cannot modify annotations");
    return *new Vector<Annotation>();
}
const IR::TypeParameters *IR::P4Parser::getTypeParameters() const {
    return type->getTypeParameters();
}
std::vector<const IR::INamespace *> IR::P4Parser::getNestedNamespaces() const {
    return {type->typeParameters, type->applyParams, constructorParams};
}
Util::Enumerator<const IR::IDeclaration *> *IR::P4Parser::getDeclarations() const {
    return parserLocals.getDeclarations()->concat(states.getDeclarations());
}
const IR::IDeclaration *IR::P4Parser::getDeclByName(cstring name) const {
    auto decl = parserLocals.getDeclaration(name);
    if (!decl) decl = states.getDeclaration(name);
    return decl;
}
const IR::IDeclaration *IR::P4Parser::getDeclByName(std::string_view name) const {
    auto decl = parserLocals.getDeclaration(name);
    if (!decl) decl = states.getDeclaration(name);
    return decl;
}
const IR::Type_Method *IR::P4Parser::getApplyMethodType() const {
    return type->getApplyMethodType();
}
const IR::ParameterList *IR::P4Parser::getApplyParameters() const {
    return type->getApplyParameters();
}
const IR::ParameterList *IR::P4Parser::getConstructorParameters() const {
    return constructorParams;
}
const IR::Type *IR::P4Parser::getType() const { return this->type; }
IRNODE_DEFINE_APPLY_OVERLOAD(P4Parser, , )
void IR::P4Parser::validate() const {
    CHECK_NULL(type);
    CHECK_NULL(constructorParams);
    parserLocals.validate();
    states.validate();
    {
        if (!(name == type->name)) BUG("Name mismatch for %1%: %2% != %3%", this, name, type->name);
        parserLocals.check_null();
        states.check_null();
        checkDuplicates();
        for (auto d : parserLocals) BUG_CHECK(!d->is<ParserState>(), "%1%: state in locals", d);
    }
}
cstring IR::P4Parser::toString() const { return "parser "_cs + externalName(); }
bool IR::P4Parser::operator==(IR::P4Parser const &a) const {
    return Type_Declaration::operator==(static_cast<const Type_Declaration &>(a)) &&
           type == a.type && constructorParams == a.constructorParams &&
           parserLocals == a.parserLocals && states == a.states;
}
bool IR::P4Parser::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Declaration::equiv(a_)) return false;
    auto &a = static_cast<const P4Parser &>(a_);
    return (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           (constructorParams
                ? a.constructorParams ? constructorParams->equiv(*a.constructorParams) : false
                : a.constructorParams == nullptr) &&
           parserLocals.equiv(a.parserLocals) && states.equiv(a.states);
}
void IR::P4Parser::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Declaration::visit_children(v, n);
    v.visit(type, "type");
    v.visit(constructorParams, "constructorParams");
    parserLocals.visit_children(v, "parserLocals");
    states.visit_children(v, "states");
}
void IR::P4Parser::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Declaration::visit_children(v, n);
    v.visit(type, "type");
    v.visit(constructorParams, "constructorParams");
    parserLocals.visit_children(v, "parserLocals");
    states.visit_children(v, "states");
}
void IR::P4Parser::toJSON(JSONGenerator &json) const {
    Type_Declaration::toJSON(json);
    json.emit("type", type);
    json.emit("constructorParams", constructorParams);
    json.emit("parserLocals", parserLocals);
    json.emit("states", states);
}
IR::P4Parser::P4Parser(JSONLoader &json) : Type_Declaration(json) {
    json.load("type", type) || json.error("missing field type");
    json.load("constructorParams", constructorParams) ||
        json.error("missing field constructorParams");
    json.load("parserLocals", parserLocals) || json.error("missing field parserLocals");
    json.load("states", states) || json.error("missing field states");
}
IR::Node *IR::P4Parser::fromJSON(JSONLoader &json) { return new P4Parser(json); }
bool IR::P4Parser::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::P4Parser::operator==(IR::Type const &a) const { return a == *this; }
bool IR::P4Parser::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::P4Control::getAnnotations() const {
    return type->getAnnotations();
}
IR::Vector<IR::Annotation> &IR::P4Control::getAnnotations() {
    BUG("cannot modify annotations");
    return *new Vector<Annotation>();
}
const IR::TypeParameters *IR::P4Control::getTypeParameters() const {
    return type->getTypeParameters();
}
std::vector<const IR::INamespace *> IR::P4Control::getNestedNamespaces() const {
    return {type->typeParameters, type->applyParams, constructorParams};
}
Util::Enumerator<const IR::IDeclaration *> *IR::P4Control::getDeclarations() const {
    return controlLocals.getDeclarations();
}
const IR::Type_Method *IR::P4Control::getApplyMethodType() const {
    return type->getApplyMethodType();
}
const IR::ParameterList *IR::P4Control::getApplyParameters() const {
    return type->getApplyParameters();
}
const IR::IDeclaration *IR::P4Control::getDeclByName(cstring name) const {
    return controlLocals.getDeclaration(name);
}
const IR::IDeclaration *IR::P4Control::getDeclByName(std::string_view name) const {
    return controlLocals.getDeclaration(name);
}
const IR::ParameterList *IR::P4Control::getConstructorParameters() const {
    return constructorParams;
}
const IR::Type *IR::P4Control::getType() const { return this->type; }
IRNODE_DEFINE_APPLY_OVERLOAD(P4Control, , )
void IR::P4Control::validate() const {
    CHECK_NULL(type);
    CHECK_NULL(constructorParams);
    controlLocals.validate();
    CHECK_NULL(body);
    {
        if (!(name == type->name)) BUG("Name mismatch for %1%: %2% != %3%", this, name, type->name);
        controlLocals.check_null();
    }
}
cstring IR::P4Control::toString() const { return "control "_cs + externalName(); }
bool IR::P4Control::operator==(IR::P4Control const &a) const {
    return Type_Declaration::operator==(static_cast<const Type_Declaration &>(a)) &&
           type == a.type && constructorParams == a.constructorParams &&
           controlLocals == a.controlLocals && body == a.body;
}
bool IR::P4Control::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Declaration::equiv(a_)) return false;
    auto &a = static_cast<const P4Control &>(a_);
    return (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           (constructorParams
                ? a.constructorParams ? constructorParams->equiv(*a.constructorParams) : false
                : a.constructorParams == nullptr) &&
           controlLocals.equiv(a.controlLocals) &&
           (body ? a.body ? body->equiv(*a.body) : false : a.body == nullptr);
}
void IR::P4Control::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Declaration::visit_children(v, n);
    v.visit(type, "type");
    v.visit(constructorParams, "constructorParams");
    controlLocals.visit_children(v, "controlLocals");
    v.visit(body, "body");
}
void IR::P4Control::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Declaration::visit_children(v, n);
    v.visit(type, "type");
    v.visit(constructorParams, "constructorParams");
    controlLocals.visit_children(v, "controlLocals");
    v.visit(body, "body");
}
void IR::P4Control::toJSON(JSONGenerator &json) const {
    Type_Declaration::toJSON(json);
    json.emit("type", type);
    json.emit("constructorParams", constructorParams);
    json.emit("controlLocals", controlLocals);
    json.emit("body", body);
}
IR::P4Control::P4Control(JSONLoader &json) : Type_Declaration(json) {
    json.load("type", type) || json.error("missing field type");
    json.load("constructorParams", constructorParams) ||
        json.error("missing field constructorParams");
    json.load("controlLocals", controlLocals) || json.error("missing field controlLocals");
    json.load("body", body) || json.error("missing field body");
}
IR::Node *IR::P4Control::fromJSON(JSONLoader &json) { return new P4Control(json); }
bool IR::P4Control::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::P4Control::operator==(IR::Type const &a) const { return a == *this; }
bool IR::P4Control::operator==(IR::Node const &a) const { return a == *this; }
Util::Enumerator<const IR::IDeclaration *> *IR::P4Action::getDeclarations() const {
    return parameters->getDeclarations();
}
const IR::IDeclaration *IR::P4Action::getDeclByName(cstring name) const {
    return parameters->getDeclByName(name);
}
const IR::IDeclaration *IR::P4Action::getDeclByName(std::string_view name) const {
    return parameters->getDeclByName(name);
}
IR::Vector<IR::Annotation> const &IR::P4Action::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::P4Action::getAnnotations() { return annotations; }
const IR::ParameterList *IR::P4Action::getParameters() const { return parameters; }
bool IR::P4Action::operator==(IR::P4Action const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           annotations == a.annotations && parameters == a.parameters && body == a.body;
}
bool IR::P4Action::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const P4Action &>(a_);
    return annotations.equiv(a.annotations) &&
           (parameters ? a.parameters ? parameters->equiv(*a.parameters) : false
                       : a.parameters == nullptr) &&
           (body ? a.body ? body->equiv(*a.body) : false : a.body == nullptr);
}
void IR::P4Action::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(parameters, "parameters");
    v.visit(body, "body");
}
void IR::P4Action::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(parameters, "parameters");
    v.visit(body, "body");
}
void IR::P4Action::validate() const {
    annotations.validate();
    CHECK_NULL(parameters);
    CHECK_NULL(body);
}
void IR::P4Action::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("parameters", parameters);
    json.emit("body", body);
}
IR::P4Action::P4Action(JSONLoader &json) : Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("parameters", parameters) || json.error("missing field parameters");
    json.load("body", body) || json.error("missing field body");
}
IR::Node *IR::P4Action::fromJSON(JSONLoader &json) { return new P4Action(json); }
bool IR::P4Action::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::P4Action::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::P4Action::operator==(IR::Node const &a) const { return a == *this; }
Util::Enumerator<const IR::IDeclaration *> *IR::Type_Error::getDeclarations() const {
    return members.getDeclarations();
}
const IR::IDeclaration *IR::Type_Error::getDeclByName(cstring name) const {
    return members.getDeclaration(name);
}
const IR::IDeclaration *IR::Type_Error::getDeclByName(std::string_view name) const {
    return members.getDeclaration(name);
}
void IR::Type_Error::validate() const {
    members.validate();
    { members.check_null(); }
}
bool IR::Type_Error::operator==(IR::Type_Error const &a) const {
    return Type_Declaration::operator==(static_cast<const Type_Declaration &>(a)) &&
           members == a.members;
}
bool IR::Type_Error::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Type_Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Type_Error &>(a_);
    return members.equiv(a.members);
}
void IR::Type_Error::visit_children(Visitor &v, char const *n) {
    (void)n;
    Type_Declaration::visit_children(v, n);
    members.visit_children(v, "members");
}
void IR::Type_Error::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Type_Declaration::visit_children(v, n);
    members.visit_children(v, "members");
}
void IR::Type_Error::toJSON(JSONGenerator &json) const {
    Type_Declaration::toJSON(json);
    json.emit("members", members);
}
IR::Type_Error::Type_Error(JSONLoader &json) : Type_Declaration(json) {
    json.load("members", members) || json.error("missing field members");
}
IR::Node *IR::Type_Error::fromJSON(JSONLoader &json) { return new Type_Error(json); }
bool IR::Type_Error::operator==(IR::Type_Declaration const &a) const { return a == *this; }
bool IR::Type_Error::operator==(IR::Type const &a) const { return a == *this; }
bool IR::Type_Error::operator==(IR::Node const &a) const { return a == *this; }
Util::Enumerator<const IR::IDeclaration *> *IR::Declaration_MatchKind::getDeclarations() const {
    return members.getDeclarations();
}
const IR::IDeclaration *IR::Declaration_MatchKind::getDeclByName(cstring name) const {
    return members.getDeclaration(name);
}
const IR::IDeclaration *IR::Declaration_MatchKind::getDeclByName(std::string_view name) const {
    return members.getDeclaration(name);
}
void IR::Declaration_MatchKind::validate() const {
    members.validate();
    { members.check_null(); }
}
bool IR::Declaration_MatchKind::operator==(IR::Declaration_MatchKind const &a) const {
    return this->typeId() == a.typeId() && members == a.members;
}
bool IR::Declaration_MatchKind::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const Declaration_MatchKind &>(a_);
    return members.equiv(a.members);
}
void IR::Declaration_MatchKind::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    members.visit_children(v, "members");
}
void IR::Declaration_MatchKind::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    members.visit_children(v, "members");
}
void IR::Declaration_MatchKind::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("members", members);
}
IR::Declaration_MatchKind::Declaration_MatchKind(JSONLoader &json) : Node(json) {
    json.load("members", members) || json.error("missing field members");
}
IR::Node *IR::Declaration_MatchKind::fromJSON(JSONLoader &json) {
    return new Declaration_MatchKind(json);
}
bool IR::Declaration_MatchKind::operator==(IR::Node const &a) const { return a == *this; }
bool IR::PropertyValue::operator==(IR::PropertyValue const &a) const {
    return this->typeId() == a.typeId();
}
bool IR::PropertyValue::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    return true;
}
void IR::PropertyValue::toJSON(JSONGenerator &json) const { Node::toJSON(json); }
IR::PropertyValue::PropertyValue(JSONLoader &json) : Node(json) {}
bool IR::PropertyValue::operator==(IR::Node const &a) const { return a == *this; }
void IR::ExpressionValue::dbprint(std::ostream &out) const { out << expression; }
bool IR::ExpressionValue::operator==(IR::ExpressionValue const &a) const {
    return PropertyValue::operator==(static_cast<const PropertyValue &>(a)) &&
           expression == a.expression;
}
bool IR::ExpressionValue::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!PropertyValue::equiv(a_)) return false;
    auto &a = static_cast<const ExpressionValue &>(a_);
    return (expression ? a.expression ? expression->equiv(*a.expression) : false
                       : a.expression == nullptr);
}
void IR::ExpressionValue::visit_children(Visitor &v, char const *n) {
    (void)n;
    PropertyValue::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::ExpressionValue::visit_children(Visitor &v, char const *n) const {
    (void)n;
    PropertyValue::visit_children(v, n);
    v.visit(expression, "expression");
}
void IR::ExpressionValue::validate() const { CHECK_NULL(expression); }
void IR::ExpressionValue::toJSON(JSONGenerator &json) const {
    PropertyValue::toJSON(json);
    json.emit("expression", expression);
}
IR::ExpressionValue::ExpressionValue(JSONLoader &json) : PropertyValue(json) {
    json.load("expression", expression) || json.error("missing field expression");
}
IR::Node *IR::ExpressionValue::fromJSON(JSONLoader &json) { return new ExpressionValue(json); }
bool IR::ExpressionValue::operator==(IR::PropertyValue const &a) const { return a == *this; }
bool IR::ExpressionValue::operator==(IR::Node const &a) const { return a == *this; }
void IR::ExpressionListValue::dbprint(std::ostream &out) const { out << expressions; }
bool IR::ExpressionListValue::operator==(IR::ExpressionListValue const &a) const {
    return PropertyValue::operator==(static_cast<const PropertyValue &>(a)) &&
           expressions == a.expressions;
}
bool IR::ExpressionListValue::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!PropertyValue::equiv(a_)) return false;
    auto &a = static_cast<const ExpressionListValue &>(a_);
    return expressions.equiv(a.expressions);
}
void IR::ExpressionListValue::visit_children(Visitor &v, char const *n) {
    (void)n;
    PropertyValue::visit_children(v, n);
    expressions.visit_children(v, "expressions");
}
void IR::ExpressionListValue::visit_children(Visitor &v, char const *n) const {
    (void)n;
    PropertyValue::visit_children(v, n);
    expressions.visit_children(v, "expressions");
}
void IR::ExpressionListValue::validate() const { expressions.validate(); }
void IR::ExpressionListValue::toJSON(JSONGenerator &json) const {
    PropertyValue::toJSON(json);
    json.emit("expressions", expressions);
}
IR::ExpressionListValue::ExpressionListValue(JSONLoader &json) : PropertyValue(json) {
    json.load("expressions", expressions) || json.error("missing field expressions");
}
IR::Node *IR::ExpressionListValue::fromJSON(JSONLoader &json) {
    return new ExpressionListValue(json);
}
bool IR::ExpressionListValue::operator==(IR::PropertyValue const &a) const { return a == *this; }
bool IR::ExpressionListValue::operator==(IR::Node const &a) const { return a == *this; }
void IR::ActionListElement::dbprint(std::ostream &out) const { out << annotations << expression; }
IR::ID IR::ActionListElement::getName() const { return getPath()->name; }
IR::Vector<IR::Annotation> const &IR::ActionListElement::getAnnotations() const {
    return annotations;
}
IR::Vector<IR::Annotation> &IR::ActionListElement::getAnnotations() { return annotations; }
void IR::ActionListElement::validate() const {
    annotations.validate();
    CHECK_NULL(expression);
    {
        BUG_CHECK(
            expression->is<IR::PathExpression>() || expression->is<IR::MethodCallExpression>(),
            "%1%: unexpected expression", expression);
    }
}
cstring IR::ActionListElement::toString() const { return getName().toString(); }
bool IR::ActionListElement::operator==(IR::ActionListElement const &a) const {
    return this->typeId() == a.typeId() && annotations == a.annotations &&
           expression == a.expression;
}
bool IR::ActionListElement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const ActionListElement &>(a_);
    return annotations.equiv(a.annotations) &&
           (expression ? a.expression ? expression->equiv(*a.expression) : false
                       : a.expression == nullptr);
}
void IR::ActionListElement::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(expression, "expression");
}
void IR::ActionListElement::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(expression, "expression");
}
void IR::ActionListElement::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("expression", expression);
}
IR::ActionListElement::ActionListElement(JSONLoader &json) : Node(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("expression", expression) || json.error("missing field expression");
}
IR::Node *IR::ActionListElement::fromJSON(JSONLoader &json) { return new ActionListElement(json); }
bool IR::ActionListElement::operator==(IR::Node const &a) const { return a == *this; }
void IR::ActionList::validate() const {
    actionList.validate();
    { actionList.check_null(); }
}
bool IR::ActionList::operator==(IR::ActionList const &a) const {
    return PropertyValue::operator==(static_cast<const PropertyValue &>(a)) &&
           actionList == a.actionList;
}
bool IR::ActionList::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!PropertyValue::equiv(a_)) return false;
    auto &a = static_cast<const ActionList &>(a_);
    return actionList.equiv(a.actionList);
}
void IR::ActionList::visit_children(Visitor &v, char const *n) {
    (void)n;
    PropertyValue::visit_children(v, n);
    actionList.visit_children(v, "actionList");
}
void IR::ActionList::visit_children(Visitor &v, char const *n) const {
    (void)n;
    PropertyValue::visit_children(v, n);
    actionList.visit_children(v, "actionList");
}
void IR::ActionList::toJSON(JSONGenerator &json) const {
    PropertyValue::toJSON(json);
    json.emit("actionList", actionList);
}
IR::ActionList::ActionList(JSONLoader &json) : PropertyValue(json) {
    json.load("actionList", actionList) || json.error("missing field actionList");
}
IR::Node *IR::ActionList::fromJSON(JSONLoader &json) { return new ActionList(json); }
bool IR::ActionList::operator==(IR::PropertyValue const &a) const { return a == *this; }
bool IR::ActionList::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::KeyElement::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::KeyElement::getAnnotations() { return annotations; }
IR::Node const *IR::KeyElement::transform_visit(Transform &v) {
    // call this from Transform::preorder(KeyElement) if the transform might split
    // the expression into a Vector<Expression>
    v.visit(annotations, "annotations");
    auto exp = v.apply_visitor(expression, "expression");
    v.visit(matchType, "matchType");
    v.prune();
    if (exp == expression) {
    } else if (auto vec = exp->to<Vector<Expression>>()) {
        auto *rv = new Vector<KeyElement>();
        for (auto el : *vec) {
            auto *kel = clone();
            kel->expression = el;
            rv->push_back(kel);
        }
        return rv;
    } else {
        expression = exp->to<IR::Expression>();
    }
    return this;
}
bool IR::KeyElement::operator==(IR::KeyElement const &a) const {
    return this->typeId() == a.typeId() && expression == a.expression && matchType == a.matchType &&
           annotations == a.annotations;
}
bool IR::KeyElement::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const KeyElement &>(a_);
    return (expression ? a.expression ? expression->equiv(*a.expression) : false
                       : a.expression == nullptr) &&
           (matchType ? a.matchType ? matchType->equiv(*a.matchType) : false
                      : a.matchType == nullptr) &&
           annotations.equiv(a.annotations);
}
void IR::KeyElement::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    v.visit(expression, "expression");
    v.visit(matchType, "matchType");
    annotations.visit_children(v, "annotations");
}
void IR::KeyElement::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    v.visit(expression, "expression");
    v.visit(matchType, "matchType");
    annotations.visit_children(v, "annotations");
}
void IR::KeyElement::validate() const {
    CHECK_NULL(expression);
    CHECK_NULL(matchType);
    annotations.validate();
}
void IR::KeyElement::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("expression", expression);
    json.emit("matchType", matchType);
    json.emit("annotations", annotations);
}
IR::KeyElement::KeyElement(JSONLoader &json) : Node(json) {
    json.load("expression", expression) || json.error("missing field expression");
    json.load("matchType", matchType) || json.error("missing field matchType");
    json.load("annotations", annotations) || json.error("missing field annotations");
}
IR::Node *IR::KeyElement::fromJSON(JSONLoader &json) { return new KeyElement(json); }
bool IR::KeyElement::operator==(IR::Node const &a) const { return a == *this; }
void IR::Key::validate() const {
    keyElements.validate();
    { keyElements.check_null(); }
}
bool IR::Key::operator==(IR::Key const &a) const {
    return PropertyValue::operator==(static_cast<const PropertyValue &>(a)) &&
           keyElements == a.keyElements;
}
bool IR::Key::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!PropertyValue::equiv(a_)) return false;
    auto &a = static_cast<const Key &>(a_);
    return keyElements.equiv(a.keyElements);
}
void IR::Key::visit_children(Visitor &v, char const *n) {
    (void)n;
    PropertyValue::visit_children(v, n);
    keyElements.visit_children(v, "keyElements");
}
void IR::Key::visit_children(Visitor &v, char const *n) const {
    (void)n;
    PropertyValue::visit_children(v, n);
    keyElements.visit_children(v, "keyElements");
}
void IR::Key::toJSON(JSONGenerator &json) const {
    PropertyValue::toJSON(json);
    json.emit("keyElements", keyElements);
}
IR::Key::Key(JSONLoader &json) : PropertyValue(json) {
    json.load("keyElements", keyElements) || json.error("missing field keyElements");
}
IR::Node *IR::Key::fromJSON(JSONLoader &json) { return new Key(json); }
bool IR::Key::operator==(IR::PropertyValue const &a) const { return a == *this; }
bool IR::Key::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::Entry::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Entry::getAnnotations() { return annotations; }
void IR::Entry::dbprint(std::ostream &out) const { out << annotations << keys << action; }
bool IR::Entry::operator==(IR::Entry const &a) const {
    return this->typeId() == a.typeId() && annotations == a.annotations && isConst == a.isConst &&
           priority == a.priority && keys == a.keys && action == a.action &&
           singleton == a.singleton;
}
bool IR::Entry::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const Entry &>(a_);
    return annotations.equiv(a.annotations) && isConst == a.isConst &&
           (priority ? a.priority ? priority->equiv(*a.priority) : false : a.priority == nullptr) &&
           (keys ? a.keys ? keys->equiv(*a.keys) : false : a.keys == nullptr) &&
           (action ? a.action ? action->equiv(*a.action) : false : a.action == nullptr) &&
           singleton == a.singleton;
}
void IR::Entry::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(priority, "priority");
    v.visit(keys, "keys");
    v.visit(action, "action");
}
void IR::Entry::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(priority, "priority");
    v.visit(keys, "keys");
    v.visit(action, "action");
}
void IR::Entry::validate() const {
    annotations.validate();
    CHECK_NULL(keys);
    CHECK_NULL(action);
}
void IR::Entry::dump_fields(std::ostream &out) const {
    Node::dump_fields(out);
    out << " isConst=" << isConst;
    out << " singleton=" << singleton;
}
void IR::Entry::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("isConst", isConst);
    if (priority != nullptr) json.emit("priority", priority);
    json.emit("keys", keys);
    json.emit("action", action);
    json.emit("singleton", singleton);
}
IR::Entry::Entry(JSONLoader &json) : Node(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("isConst", isConst) || json.error("missing field isConst");
    json.load("priority", priority);
    json.load("keys", keys) || json.error("missing field keys");
    json.load("action", action) || json.error("missing field action");
    json.load("singleton", singleton) || json.error("missing field singleton");
}
IR::Node *IR::Entry::fromJSON(JSONLoader &json) { return new Entry(json); }
bool IR::Entry::operator==(IR::Node const &a) const { return a == *this; }
void IR::EntriesList::dbprint(std::ostream &out) const { out << "{ " << entries << "}"; }
bool IR::EntriesList::operator==(IR::EntriesList const &a) const {
    return PropertyValue::operator==(static_cast<const PropertyValue &>(a)) && entries == a.entries;
}
bool IR::EntriesList::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!PropertyValue::equiv(a_)) return false;
    auto &a = static_cast<const EntriesList &>(a_);
    return entries.equiv(a.entries);
}
void IR::EntriesList::visit_children(Visitor &v, char const *n) {
    (void)n;
    PropertyValue::visit_children(v, n);
    entries.visit_children(v, "entries");
}
void IR::EntriesList::visit_children(Visitor &v, char const *n) const {
    (void)n;
    PropertyValue::visit_children(v, n);
    entries.visit_children(v, "entries");
}
void IR::EntriesList::validate() const { entries.validate(); }
void IR::EntriesList::toJSON(JSONGenerator &json) const {
    PropertyValue::toJSON(json);
    json.emit("entries", entries);
}
IR::EntriesList::EntriesList(JSONLoader &json) : PropertyValue(json) {
    json.load("entries", entries) || json.error("missing field entries");
}
IR::Node *IR::EntriesList::fromJSON(JSONLoader &json) { return new EntriesList(json); }
bool IR::EntriesList::operator==(IR::PropertyValue const &a) const { return a == *this; }
bool IR::EntriesList::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::Property::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Property::getAnnotations() { return annotations; }
void IR::Property::dbprint(std::ostream &out) const {
    out << annotations << (isConstant ? "const " : "") << name << " = " << value;
}
bool IR::Property::operator==(IR::Property const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           annotations == a.annotations && value == a.value && isConstant == a.isConstant;
}
bool IR::Property::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Property &>(a_);
    return annotations.equiv(a.annotations) &&
           (value ? a.value ? value->equiv(*a.value) : false : a.value == nullptr) &&
           isConstant == a.isConstant;
}
void IR::Property::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(value, "value");
}
void IR::Property::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(value, "value");
}
void IR::Property::validate() const {
    annotations.validate();
    CHECK_NULL(value);
}
void IR::Property::dump_fields(std::ostream &out) const {
    Declaration::dump_fields(out);
    out << " isConstant=" << isConstant;
}
void IR::Property::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("value", value);
    json.emit("isConstant", isConstant);
}
IR::Property::Property(JSONLoader &json) : Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("value", value) || json.error("missing field value");
    json.load("isConstant", isConstant) || json.error("missing field isConstant");
}
IR::Node *IR::Property::fromJSON(JSONLoader &json) { return new Property(json); }
bool IR::Property::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::Property::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::Property::operator==(IR::Node const &a) const { return a == *this; }
cstring IR::TableProperties::toString() const {
    return absl::StrCat("TableProperties(", properties.size(), ")");
}
Util::Enumerator<const IR::IDeclaration *> *IR::TableProperties::getDeclarations() const {
    return properties.getDeclarations();
}
const IR::IDeclaration *IR::TableProperties::getDeclByName(cstring name) const {
    return properties.getDeclaration(name);
}
const IR::IDeclaration *IR::TableProperties::getDeclByName(std::string_view name) const {
    return properties.getDeclaration(name);
}
void IR::TableProperties::validate() const {
    properties.validate();
    {
        properties.check_null();
        properties.validate();
    }
}
bool IR::TableProperties::operator==(IR::TableProperties const &a) const {
    return this->typeId() == a.typeId() && properties == a.properties;
}
bool IR::TableProperties::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const TableProperties &>(a_);
    return properties.equiv(a.properties);
}
void IR::TableProperties::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    properties.visit_children(v, "properties");
}
void IR::TableProperties::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    properties.visit_children(v, "properties");
}
void IR::TableProperties::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("properties", properties);
}
IR::TableProperties::TableProperties(JSONLoader &json) : Node(json) {
    json.load("properties", properties) || json.error("missing field properties");
}
IR::Node *IR::TableProperties::fromJSON(JSONLoader &json) { return new TableProperties(json); }
bool IR::TableProperties::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::P4Table::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::P4Table::getAnnotations() { return annotations; }
const IR::ParameterList *IR::P4Table::getApplyParameters() const { return new ParameterList(); }
bool IR::P4Table::operator==(IR::P4Table const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           annotations == a.annotations && properties == a.properties;
}
bool IR::P4Table::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const P4Table &>(a_);
    return annotations.equiv(a.annotations) &&
           (properties ? a.properties ? properties->equiv(*a.properties) : false
                       : a.properties == nullptr);
}
void IR::P4Table::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(properties, "properties");
}
void IR::P4Table::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(properties, "properties");
}
void IR::P4Table::validate() const {
    annotations.validate();
    CHECK_NULL(properties);
}
void IR::P4Table::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("properties", properties);
}
IR::P4Table::P4Table(JSONLoader &json) : Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("properties", properties) || json.error("missing field properties");
}
IR::Node *IR::P4Table::fromJSON(JSONLoader &json) { return new P4Table(json); }
bool IR::P4Table::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::P4Table::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::P4Table::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::P4ValueSet::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::P4ValueSet::getAnnotations() { return annotations; }
bool IR::P4ValueSet::operator==(IR::P4ValueSet const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           annotations == a.annotations && elementType == a.elementType && size == a.size;
}
bool IR::P4ValueSet::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const P4ValueSet &>(a_);
    return annotations.equiv(a.annotations) &&
           (elementType ? a.elementType ? elementType->equiv(*a.elementType) : false
                        : a.elementType == nullptr) &&
           (size ? a.size ? size->equiv(*a.size) : false : a.size == nullptr);
}
void IR::P4ValueSet::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(elementType, "elementType");
    v.visit(size, "size");
}
void IR::P4ValueSet::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(elementType, "elementType");
    v.visit(size, "size");
}
void IR::P4ValueSet::validate() const {
    annotations.validate();
    CHECK_NULL(elementType);
    CHECK_NULL(size);
}
void IR::P4ValueSet::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("elementType", elementType);
    json.emit("size", size);
}
IR::P4ValueSet::P4ValueSet(JSONLoader &json) : Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("elementType", elementType) || json.error("missing field elementType");
    json.load("size", size) || json.error("missing field size");
}
IR::Node *IR::P4ValueSet::fromJSON(JSONLoader &json) { return new P4ValueSet(json); }
bool IR::P4ValueSet::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::P4ValueSet::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::P4ValueSet::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::Declaration_Variable::getAnnotations() const {
    return annotations;
}
IR::Vector<IR::Annotation> &IR::Declaration_Variable::getAnnotations() { return annotations; }
void IR::Declaration_Variable::dbprint(std::ostream &out) const {
    out << annotations << type << ' ' << name;
    if (initializer) out << " = " << *initializer;
}
bool IR::Declaration_Variable::operator==(IR::Declaration_Variable const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           annotations == a.annotations && type == a.type && initializer == a.initializer;
}
bool IR::Declaration_Variable::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Declaration_Variable &>(a_);
    return annotations.equiv(a.annotations) &&
           (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           (initializer ? a.initializer ? initializer->equiv(*a.initializer) : false
                        : a.initializer == nullptr);
}
void IR::Declaration_Variable::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    v.visit(initializer, "initializer");
}
void IR::Declaration_Variable::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    v.visit(initializer, "initializer");
}
void IR::Declaration_Variable::validate() const {
    annotations.validate();
    CHECK_NULL(type);
}
void IR::Declaration_Variable::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("type", type);
    if (initializer != nullptr) json.emit("initializer", initializer);
}
IR::Declaration_Variable::Declaration_Variable(JSONLoader &json) : Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("type", type) || json.error("missing field type");
    json.load("initializer", initializer);
}
IR::Node *IR::Declaration_Variable::fromJSON(JSONLoader &json) {
    return new Declaration_Variable(json);
}
bool IR::Declaration_Variable::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::Declaration_Variable::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::Declaration_Variable::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::Declaration_Constant::getAnnotations() const {
    return annotations;
}
IR::Vector<IR::Annotation> &IR::Declaration_Constant::getAnnotations() { return annotations; }
cstring IR::Declaration_Constant::toString() const { return Declaration::toString(); }
void IR::Declaration_Constant::dbprint(std::ostream &out) const {
    out << annotations << type << ' ' << name << " = " << *initializer;
}
bool IR::Declaration_Constant::operator==(IR::Declaration_Constant const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           annotations == a.annotations && type == a.type && initializer == a.initializer;
}
bool IR::Declaration_Constant::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Declaration_Constant &>(a_);
    return annotations.equiv(a.annotations) &&
           (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           (initializer ? a.initializer ? initializer->equiv(*a.initializer) : false
                        : a.initializer == nullptr);
}
void IR::Declaration_Constant::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    v.visit(initializer, "initializer");
}
void IR::Declaration_Constant::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    v.visit(initializer, "initializer");
}
void IR::Declaration_Constant::validate() const {
    annotations.validate();
    CHECK_NULL(type);
    CHECK_NULL(initializer);
}
void IR::Declaration_Constant::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("type", type);
    json.emit("initializer", initializer);
}
IR::Declaration_Constant::Declaration_Constant(JSONLoader &json) : Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("type", type) || json.error("missing field type");
    json.load("initializer", initializer) || json.error("missing field initializer");
}
IR::Node *IR::Declaration_Constant::fromJSON(JSONLoader &json) {
    return new Declaration_Constant(json);
}
bool IR::Declaration_Constant::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::Declaration_Constant::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::Declaration_Constant::operator==(IR::Node const &a) const { return a == *this; }
IR::Vector<IR::Annotation> const &IR::Declaration_Instance::getAnnotations() const {
    return annotations;
}
IR::Vector<IR::Annotation> &IR::Declaration_Instance::getAnnotations() { return annotations; }
const IR::Type *IR::Declaration_Instance::getType() const { return type; }
IR::ID IR::Declaration_Instance::Name() const { return name; }
void IR::Declaration_Instance::validate() const {
    annotations.validate();
    CHECK_NULL(type);
    CHECK_NULL(arguments);
    properties.validate();
    { arguments->check_null(); }
}
bool IR::Declaration_Instance::operator==(IR::Declaration_Instance const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           annotations == a.annotations && type == a.type && arguments == a.arguments &&
           properties == a.properties && initializer == a.initializer;
}
bool IR::Declaration_Instance::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Declaration_Instance &>(a_);
    return annotations.equiv(a.annotations) &&
           (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           (arguments ? a.arguments ? arguments->equiv(*a.arguments) : false
                      : a.arguments == nullptr) &&
           properties.equiv(a.properties) &&
           (initializer ? a.initializer ? initializer->equiv(*a.initializer) : false
                        : a.initializer == nullptr);
}
void IR::Declaration_Instance::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    v.visit(arguments, "arguments");
    properties.visit_children(v, "properties");
    v.visit(initializer, "initializer");
}
void IR::Declaration_Instance::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    v.visit(arguments, "arguments");
    properties.visit_children(v, "properties");
    v.visit(initializer, "initializer");
}
void IR::Declaration_Instance::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("type", type);
    json.emit("arguments", arguments);
    json.emit("properties", properties);
    if (initializer != nullptr) json.emit("initializer", initializer);
}
IR::Declaration_Instance::Declaration_Instance(JSONLoader &json) : Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("type", type) || json.error("missing field type");
    json.load("arguments", arguments) || json.error("missing field arguments");
    json.load("properties", properties) || json.error("missing field properties");
    json.load("initializer", initializer);
}
IR::Node *IR::Declaration_Instance::fromJSON(JSONLoader &json) {
    return new Declaration_Instance(json);
}
bool IR::Declaration_Instance::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::Declaration_Instance::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::Declaration_Instance::operator==(IR::Node const &a) const { return a == *this; }
void IR::P4Program::validate() const {
    objects.validate();
    { objects.check_null(); }
}
IRNODE_DEFINE_APPLY_OVERLOAD(P4Program, , )
bool IR::P4Program::operator==(IR::P4Program const &a) const {
    return this->typeId() == a.typeId() && objects == a.objects;
}
bool IR::P4Program::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const P4Program &>(a_);
    return objects.equiv(a.objects);
}
void IR::P4Program::visit_children(Visitor &v, char const *n) {
    (void)n;
    Node::visit_children(v, n);
    objects.visit_children(v, "objects");
}
void IR::P4Program::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Node::visit_children(v, n);
    objects.visit_children(v, "objects");
}
void IR::P4Program::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("objects", objects);
}
IR::P4Program::P4Program(JSONLoader &json) : Node(json) {
    json.load("objects", objects) || json.error("missing field objects");
}
IR::Node *IR::P4Program::fromJSON(JSONLoader &json) { return new P4Program(json); }
bool IR::P4Program::operator==(IR::Node const &a) const { return a == *this; }
const IR::ParameterList *IR::Function::getParameters() const { return type->parameters; }
Util::Enumerator<const IR::IDeclaration *> *IR::Function::getDeclarations() const {
    return type->parameters->getDeclarations();
}
const IR::IDeclaration *IR::Function::getDeclByName(cstring name) const {
    return type->parameters->getDeclByName(name);
}
const IR::IDeclaration *IR::Function::getDeclByName(std::string_view name) const {
    return type->parameters->getDeclByName(name);
}
std::vector<const IR::INamespace *> IR::Function::getNestedNamespaces() const {
    return {type->typeParameters};
}
IR::Vector<IR::Annotation> const &IR::Function::getAnnotations() const { return annotations; }
IR::Vector<IR::Annotation> &IR::Function::getAnnotations() { return annotations; }
bool IR::Function::operator==(IR::Function const &a) const {
    return Declaration::operator==(static_cast<const Declaration &>(a)) &&
           annotations == a.annotations && type == a.type && body == a.body;
}
bool IR::Function::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Declaration::equiv(a_)) return false;
    auto &a = static_cast<const Function &>(a_);
    return annotations.equiv(a.annotations) &&
           (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           (body ? a.body ? body->equiv(*a.body) : false : a.body == nullptr);
}
void IR::Function::visit_children(Visitor &v, char const *n) {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    v.visit(body, "body");
}
void IR::Function::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Declaration::visit_children(v, n);
    annotations.visit_children(v, "annotations");
    v.visit(type, "type");
    v.visit(body, "body");
}
void IR::Function::validate() const {
    annotations.validate();
    CHECK_NULL(type);
    CHECK_NULL(body);
}
void IR::Function::toJSON(JSONGenerator &json) const {
    Declaration::toJSON(json);
    json.emit("annotations", annotations);
    json.emit("type", type);
    json.emit("body", body);
}
IR::Function::Function(JSONLoader &json) : Declaration(json) {
    json.load("annotations", annotations) || json.error("missing field annotations");
    json.load("type", type) || json.error("missing field type");
    json.load("body", body) || json.error("missing field body");
}
IR::Node *IR::Function::fromJSON(JSONLoader &json) { return new Function(json); }
bool IR::Function::operator==(IR::Declaration const &a) const { return a == *this; }
bool IR::Function::operator==(IR::StatOrDecl const &a) const { return a == *this; }
bool IR::Function::operator==(IR::Node const &a) const { return a == *this; }
void IR::Block::visit_children(Visitor &v, char const *n) {
    (void)v;
    (void)n;
}
void IR::Block::visit_children(Visitor &v, char const *n) const {
    (void)v;
    (void)n;
}
IR::IDeclaration const *IR::Block::getContainer() const { return nullptr; }
bool IR::Block::operator==(IR::Block const &a) const {
    return this->typeId() == a.typeId() && node == a.node && constantValue == a.constantValue;
}
bool IR::Block::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (this->typeId() != a_.typeId()) return false;
    auto &a = static_cast<const Block &>(a_);
    return (node ? a.node ? node->equiv(*a.node) : false : a.node == nullptr) &&
           constantValue == a.constantValue;
}
void IR::Block::validate() const { CHECK_NULL(node); }
void IR::Block::toJSON(JSONGenerator &json) const {
    Node::toJSON(json);
    json.emit("node", node);
    json.emit("constantValue", constantValue);
}
IR::Block::Block(JSONLoader &json) : Node(json) {
    json.load("node", node) || json.error("missing field node");
    json.load("constantValue", constantValue) || json.error("missing field constantValue");
}
bool IR::Block::operator==(IR::Node const &a) const { return a == *this; }
IR::IDeclaration const *IR::TableBlock::getContainer() const { return container; }
bool IR::TableBlock::operator==(IR::TableBlock const &a) const {
    return Block::operator==(static_cast<const Block &>(a)) && container == a.container;
}
bool IR::TableBlock::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Block::equiv(a_)) return false;
    auto &a = static_cast<const TableBlock &>(a_);
    return (container ? a.container ? container->equiv(*a.container) : false
                      : a.container == nullptr);
}
void IR::TableBlock::visit_children(Visitor &v, char const *n) {
    (void)n;
    Block::visit_children(v, n);
    v.visit(container, "container");
}
void IR::TableBlock::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Block::visit_children(v, n);
    v.visit(container, "container");
}
void IR::TableBlock::validate() const { CHECK_NULL(container); }
void IR::TableBlock::toJSON(JSONGenerator &json) const {
    Block::toJSON(json);
    json.emit("container", container);
}
IR::TableBlock::TableBlock(JSONLoader &json) : Block(json) {
    json.load("container", container) || json.error("missing field container");
}
IR::Node *IR::TableBlock::fromJSON(JSONLoader &json) { return new TableBlock(json); }
bool IR::TableBlock::operator==(IR::Block const &a) const { return a == *this; }
bool IR::TableBlock::operator==(IR::Node const &a) const { return a == *this; }
bool IR::InstantiatedBlock::operator==(IR::InstantiatedBlock const &a) const {
    return Block::operator==(static_cast<const Block &>(a)) && instanceType == a.instanceType;
}
bool IR::InstantiatedBlock::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Block::equiv(a_)) return false;
    auto &a = static_cast<const InstantiatedBlock &>(a_);
    return (instanceType ? a.instanceType ? instanceType->equiv(*a.instanceType) : false
                         : a.instanceType == nullptr);
}
void IR::InstantiatedBlock::visit_children(Visitor &v, char const *n) {
    (void)n;
    Block::visit_children(v, n);
    v.visit(instanceType, "instanceType");
}
void IR::InstantiatedBlock::visit_children(Visitor &v, char const *n) const {
    (void)n;
    Block::visit_children(v, n);
    v.visit(instanceType, "instanceType");
}
void IR::InstantiatedBlock::validate() const { CHECK_NULL(instanceType); }
void IR::InstantiatedBlock::toJSON(JSONGenerator &json) const {
    Block::toJSON(json);
    json.emit("instanceType", instanceType);
}
IR::InstantiatedBlock::InstantiatedBlock(JSONLoader &json) : Block(json) {
    json.load("instanceType", instanceType) || json.error("missing field instanceType");
}
bool IR::InstantiatedBlock::operator==(IR::Block const &a) const { return a == *this; }
bool IR::InstantiatedBlock::operator==(IR::Node const &a) const { return a == *this; }
const IR::ParameterList *IR::ParserBlock::getConstructorParameters() const {
    return container->constructorParams;
}
cstring IR::ParserBlock::toString() const { return container->toString(); }
IR::ID IR::ParserBlock::getName() const { return container->getName(); }
IR::IDeclaration const *IR::ParserBlock::getContainer() const { return container; }
bool IR::ParserBlock::operator==(IR::ParserBlock const &a) const {
    return InstantiatedBlock::operator==(static_cast<const InstantiatedBlock &>(a)) &&
           container == a.container;
}
bool IR::ParserBlock::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!InstantiatedBlock::equiv(a_)) return false;
    auto &a = static_cast<const ParserBlock &>(a_);
    return (container ? a.container ? container->equiv(*a.container) : false
                      : a.container == nullptr);
}
void IR::ParserBlock::visit_children(Visitor &v, char const *n) {
    (void)n;
    InstantiatedBlock::visit_children(v, n);
    v.visit(container, "container");
}
void IR::ParserBlock::visit_children(Visitor &v, char const *n) const {
    (void)n;
    InstantiatedBlock::visit_children(v, n);
    v.visit(container, "container");
}
void IR::ParserBlock::validate() const { CHECK_NULL(container); }
void IR::ParserBlock::toJSON(JSONGenerator &json) const {
    InstantiatedBlock::toJSON(json);
    json.emit("container", container);
}
IR::ParserBlock::ParserBlock(JSONLoader &json) : InstantiatedBlock(json) {
    json.load("container", container) || json.error("missing field container");
}
IR::Node *IR::ParserBlock::fromJSON(JSONLoader &json) { return new ParserBlock(json); }
bool IR::ParserBlock::operator==(IR::InstantiatedBlock const &a) const { return a == *this; }
bool IR::ParserBlock::operator==(IR::Block const &a) const { return a == *this; }
bool IR::ParserBlock::operator==(IR::Node const &a) const { return a == *this; }
const IR::ParameterList *IR::ControlBlock::getConstructorParameters() const {
    return container->constructorParams;
}
cstring IR::ControlBlock::toString() const { return container->toString(); }
IR::ID IR::ControlBlock::getName() const { return container->getName(); }
IR::IDeclaration const *IR::ControlBlock::getContainer() const { return container; }
bool IR::ControlBlock::operator==(IR::ControlBlock const &a) const {
    return InstantiatedBlock::operator==(static_cast<const InstantiatedBlock &>(a)) &&
           container == a.container;
}
bool IR::ControlBlock::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!InstantiatedBlock::equiv(a_)) return false;
    auto &a = static_cast<const ControlBlock &>(a_);
    return (container ? a.container ? container->equiv(*a.container) : false
                      : a.container == nullptr);
}
void IR::ControlBlock::visit_children(Visitor &v, char const *n) {
    (void)n;
    InstantiatedBlock::visit_children(v, n);
    v.visit(container, "container");
}
void IR::ControlBlock::visit_children(Visitor &v, char const *n) const {
    (void)n;
    InstantiatedBlock::visit_children(v, n);
    v.visit(container, "container");
}
void IR::ControlBlock::validate() const { CHECK_NULL(container); }
void IR::ControlBlock::toJSON(JSONGenerator &json) const {
    InstantiatedBlock::toJSON(json);
    json.emit("container", container);
}
IR::ControlBlock::ControlBlock(JSONLoader &json) : InstantiatedBlock(json) {
    json.load("container", container) || json.error("missing field container");
}
IR::Node *IR::ControlBlock::fromJSON(JSONLoader &json) { return new ControlBlock(json); }
bool IR::ControlBlock::operator==(IR::InstantiatedBlock const &a) const { return a == *this; }
bool IR::ControlBlock::operator==(IR::Block const &a) const { return a == *this; }
bool IR::ControlBlock::operator==(IR::Node const &a) const { return a == *this; }
const IR::ParameterList *IR::PackageBlock::getConstructorParameters() const {
    return type->constructorParams;
}
cstring IR::PackageBlock::toString() const { return type->toString(); }
IR::ID IR::PackageBlock::getName() const { return type->getName(); }
bool IR::PackageBlock::operator==(IR::PackageBlock const &a) const {
    return InstantiatedBlock::operator==(static_cast<const InstantiatedBlock &>(a)) &&
           type == a.type;
}
bool IR::PackageBlock::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!InstantiatedBlock::equiv(a_)) return false;
    auto &a = static_cast<const PackageBlock &>(a_);
    return (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr);
}
void IR::PackageBlock::visit_children(Visitor &v, char const *n) {
    (void)n;
    InstantiatedBlock::visit_children(v, n);
    v.visit(type, "type");
}
void IR::PackageBlock::visit_children(Visitor &v, char const *n) const {
    (void)n;
    InstantiatedBlock::visit_children(v, n);
    v.visit(type, "type");
}
void IR::PackageBlock::validate() const { CHECK_NULL(type); }
void IR::PackageBlock::toJSON(JSONGenerator &json) const {
    InstantiatedBlock::toJSON(json);
    json.emit("type", type);
}
IR::PackageBlock::PackageBlock(JSONLoader &json) : InstantiatedBlock(json) {
    json.load("type", type) || json.error("missing field type");
}
IR::Node *IR::PackageBlock::fromJSON(JSONLoader &json) { return new PackageBlock(json); }
bool IR::PackageBlock::operator==(IR::InstantiatedBlock const &a) const { return a == *this; }
bool IR::PackageBlock::operator==(IR::Block const &a) const { return a == *this; }
bool IR::PackageBlock::operator==(IR::Node const &a) const { return a == *this; }
const IR::ParameterList *IR::ExternBlock::getConstructorParameters() const {
    return constructor->type->parameters;
}
cstring IR::ExternBlock::toString() const { return type->toString(); }
IR::ID IR::ExternBlock::getName() const { return type->getName(); }
bool IR::ExternBlock::operator==(IR::ExternBlock const &a) const {
    return InstantiatedBlock::operator==(static_cast<const InstantiatedBlock &>(a)) &&
           type == a.type && constructor == a.constructor;
}
bool IR::ExternBlock::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!InstantiatedBlock::equiv(a_)) return false;
    auto &a = static_cast<const ExternBlock &>(a_);
    return (type ? a.type ? type->equiv(*a.type) : false : a.type == nullptr) &&
           (constructor ? a.constructor ? constructor->equiv(*a.constructor) : false
                        : a.constructor == nullptr);
}
void IR::ExternBlock::visit_children(Visitor &v, char const *n) {
    (void)n;
    InstantiatedBlock::visit_children(v, n);
    v.visit(type, "type");
    v.visit(constructor, "constructor");
}
void IR::ExternBlock::visit_children(Visitor &v, char const *n) const {
    (void)n;
    InstantiatedBlock::visit_children(v, n);
    v.visit(type, "type");
    v.visit(constructor, "constructor");
}
void IR::ExternBlock::validate() const {
    CHECK_NULL(type);
    CHECK_NULL(constructor);
}
void IR::ExternBlock::toJSON(JSONGenerator &json) const {
    InstantiatedBlock::toJSON(json);
    json.emit("type", type);
    json.emit("constructor", constructor);
}
IR::ExternBlock::ExternBlock(JSONLoader &json) : InstantiatedBlock(json) {
    json.load("type", type) || json.error("missing field type");
    json.load("constructor", constructor) || json.error("missing field constructor");
}
IR::Node *IR::ExternBlock::fromJSON(JSONLoader &json) { return new ExternBlock(json); }
bool IR::ExternBlock::operator==(IR::InstantiatedBlock const &a) const { return a == *this; }
bool IR::ExternBlock::operator==(IR::Block const &a) const { return a == *this; }
bool IR::ExternBlock::operator==(IR::Node const &a) const { return a == *this; }
const IR::P4Program *IR::ToplevelBlock::getProgram() const { return node->to<IR::P4Program>(); }
IR::ID IR::ToplevelBlock::getName() const { return "main"; }
void IR::ToplevelBlock::validate() const {
    { BUG_CHECK(node->is<IR::P4Program>(), "%1%: expected a P4Program", node); }
}
bool IR::ToplevelBlock::operator==(IR::ToplevelBlock const &a) const {
    return Block::operator==(static_cast<const Block &>(a));
}
bool IR::ToplevelBlock::equiv(IR::Node const &a_) const {
    if (static_cast<const Node *>(this) == &a_) return true;
    if (!Block::equiv(a_)) return false;
    return true;
}
void IR::ToplevelBlock::toJSON(JSONGenerator &json) const { Block::toJSON(json); }
IR::ToplevelBlock::ToplevelBlock(JSONLoader &json) : Block(json) {}
IR::Node *IR::ToplevelBlock::fromJSON(JSONLoader &json) { return new ToplevelBlock(json); }
bool IR::ToplevelBlock::operator==(IR::Block const &a) const { return a == *this; }
bool IR::ToplevelBlock::operator==(IR::Node const &a) const { return a == *this; }
