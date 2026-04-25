#ifndef IR_GENERATED_DECLARATIONS_H_
#define IR_GENERATED_DECLARATIONS_H_

// Top-level P4 declarations: ParserState, P4Parser, P4Control, P4Action,
// P4Table and supporting Property / Key / Entry / ActionList helpers,
// the Declaration_* family, Function, the Block hierarchy, and P4Program.

#include "ir/ir-generated-statements.h"

namespace P4::IR {
class ParserState : public virtual ISimpleNamespace, public Declaration, public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    IR::IndexedVector<IR::StatOrDecl> components;

    const IR::Expression *selectExpression = nullptr;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    IR::IDeclaration const *getDeclByName(cstring name) const override;
    IR::IDeclaration const *getDeclByName(std::string_view name) const override;
    static const cstring accept;
    static const cstring reject;
    static const cstring start;
    static const cstring verify;
    bool isBuiltin() const { return name == ParserState::accept || name == ParserState::reject; }
    void validate() const override;
    bool operator==(IR::ParserState const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "ParserState"_cs; }
    static cstring static_type_name() { return "ParserState"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ParserState(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ParserState(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                IR::IndexedVector<IR::StatOrDecl> components,
                const IR::Expression *selectExpression)
        : Declaration(srcInfo, name),
          annotations(annotations),
          components(components),
          selectExpression(selectExpression) {
        validate();
    }
    ParserState(IR::ID name, IR::Vector<IR::Annotation> annotations,
                IR::IndexedVector<IR::StatOrDecl> components,
                const IR::Expression *selectExpression)
        : Declaration(name),
          annotations(annotations),
          components(components),
          selectExpression(selectExpression) {
        validate();
    }
    ParserState(Util::SourceInfo srcInfo, IR::ID name, IR::IndexedVector<IR::StatOrDecl> components,
                const IR::Expression *selectExpression)
        : Declaration(srcInfo, name), components(components), selectExpression(selectExpression) {
        validate();
    }
    ParserState(IR::ID name, IR::IndexedVector<IR::StatOrDecl> components,
                const IR::Expression *selectExpression)
        : Declaration(name), components(components), selectExpression(selectExpression) {
        validate();
    }
    ParserState(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::Expression *selectExpression)
        : Declaration(srcInfo, name), annotations(annotations), selectExpression(selectExpression) {
        validate();
    }
    ParserState(IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::Expression *selectExpression)
        : Declaration(name), annotations(annotations), selectExpression(selectExpression) {
        validate();
    }
    ParserState(Util::SourceInfo srcInfo, IR::ID name, const IR::Expression *selectExpression)
        : Declaration(srcInfo, name), selectExpression(selectExpression) {
        validate();
    }
    ParserState(IR::ID name, const IR::Expression *selectExpression)
        : Declaration(name), selectExpression(selectExpression) {
        validate();
    }
    IRNODE_SUBCLASS(ParserState)
    DECLARE_TYPEINFO_WITH_TYPEID(ParserState, NodeKind::ParserState, ISimpleNamespace, Declaration,
                                 IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {

class P4Parser : public Type_Declaration,
                 public virtual INestedNamespace,
                 public virtual ISimpleNamespace,
                 public virtual IApply,
                 public virtual IContainer,
                 public virtual IAnnotated {
 public:
    const IR::Type_Parser *type = nullptr;
    const IR::ParameterList *constructorParams = new ParameterList;
    IR::IndexedVector<IR::Declaration> parserLocals;
    IR::IndexedVector<IR::ParserState> states;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    const IR::TypeParameters *getTypeParameters() const override;
    std::vector<const IR::INamespace *> getNestedNamespaces() const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    const IR::Type_Method *getApplyMethodType() const override;
    const IR::ParameterList *getApplyParameters() const override;
    const IR::Type_Method *getConstructorMethodType() const override;
    const IR::ParameterList *getConstructorParameters() const override;
    void checkDuplicates() const;
    const IR::Type *getType() const override;
    IRNODE_DECLARE_APPLY_OVERLOAD(P4Parser)
    void validate() const override;
    cstring toString() const override;
    bool operator==(IR::P4Parser const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "P4Parser"_cs; }
    static cstring static_type_name() { return "P4Parser"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    P4Parser(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    P4Parser(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Parser *type,
             const IR::ParameterList *constructorParams,
             IR::IndexedVector<IR::Declaration> parserLocals,
             IR::IndexedVector<IR::ParserState> states)
        : Type_Declaration(srcInfo, name),
          type(type),
          constructorParams(constructorParams),
          parserLocals(parserLocals),
          states(states) {
        validate();
    }
    P4Parser(IR::ID name, const IR::Type_Parser *type, const IR::ParameterList *constructorParams,
             IR::IndexedVector<IR::Declaration> parserLocals,
             IR::IndexedVector<IR::ParserState> states)
        : Type_Declaration(name),
          type(type),
          constructorParams(constructorParams),
          parserLocals(parserLocals),
          states(states) {
        validate();
    }
    P4Parser(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Parser *type,
             IR::IndexedVector<IR::Declaration> parserLocals,
             IR::IndexedVector<IR::ParserState> states)
        : Type_Declaration(srcInfo, name), type(type), parserLocals(parserLocals), states(states) {
        validate();
    }
    P4Parser(IR::ID name, const IR::Type_Parser *type,
             IR::IndexedVector<IR::Declaration> parserLocals,
             IR::IndexedVector<IR::ParserState> states)
        : Type_Declaration(name), type(type), parserLocals(parserLocals), states(states) {
        validate();
    }
    P4Parser(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Parser *type,
             const IR::ParameterList *constructorParams, IR::IndexedVector<IR::ParserState> states)
        : Type_Declaration(srcInfo, name),
          type(type),
          constructorParams(constructorParams),
          states(states) {
        validate();
    }
    P4Parser(IR::ID name, const IR::Type_Parser *type, const IR::ParameterList *constructorParams,
             IR::IndexedVector<IR::ParserState> states)
        : Type_Declaration(name), type(type), constructorParams(constructorParams), states(states) {
        validate();
    }
    P4Parser(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Parser *type,
             IR::IndexedVector<IR::ParserState> states)
        : Type_Declaration(srcInfo, name), type(type), states(states) {
        validate();
    }
    P4Parser(IR::ID name, const IR::Type_Parser *type, IR::IndexedVector<IR::ParserState> states)
        : Type_Declaration(name), type(type), states(states) {
        validate();
    }
    P4Parser(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Parser *type,
             const IR::ParameterList *constructorParams,
             IR::IndexedVector<IR::Declaration> parserLocals)
        : Type_Declaration(srcInfo, name),
          type(type),
          constructorParams(constructorParams),
          parserLocals(parserLocals) {
        validate();
    }
    P4Parser(IR::ID name, const IR::Type_Parser *type, const IR::ParameterList *constructorParams,
             IR::IndexedVector<IR::Declaration> parserLocals)
        : Type_Declaration(name),
          type(type),
          constructorParams(constructorParams),
          parserLocals(parserLocals) {
        validate();
    }
    P4Parser(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Parser *type,
             IR::IndexedVector<IR::Declaration> parserLocals)
        : Type_Declaration(srcInfo, name), type(type), parserLocals(parserLocals) {
        validate();
    }
    P4Parser(IR::ID name, const IR::Type_Parser *type,
             IR::IndexedVector<IR::Declaration> parserLocals)
        : Type_Declaration(name), type(type), parserLocals(parserLocals) {
        validate();
    }
    P4Parser(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Parser *type,
             const IR::ParameterList *constructorParams)
        : Type_Declaration(srcInfo, name), type(type), constructorParams(constructorParams) {
        validate();
    }
    P4Parser(IR::ID name, const IR::Type_Parser *type, const IR::ParameterList *constructorParams)
        : Type_Declaration(name), type(type), constructorParams(constructorParams) {
        validate();
    }
    P4Parser(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Parser *type)
        : Type_Declaration(srcInfo, name), type(type) {
        validate();
    }
    P4Parser(IR::ID name, const IR::Type_Parser *type) : Type_Declaration(name), type(type) {
        validate();
    }
    IRNODE_SUBCLASS(P4Parser)
    DECLARE_TYPEINFO_WITH_TYPEID(P4Parser, NodeKind::P4Parser, Type_Declaration, INestedNamespace,
                                 ISimpleNamespace, IApply, IContainer, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class P4Control : public Type_Declaration,
                  public virtual INestedNamespace,
                  public virtual ISimpleNamespace,
                  public virtual IApply,
                  public virtual IContainer,
                  public virtual IAnnotated {
 public:
    const IR::Type_Control *type = nullptr;
    const IR::ParameterList *constructorParams = new ParameterList;
    IR::IndexedVector<IR::Declaration> controlLocals;
    const IR::BlockStatement *body = nullptr;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    const IR::TypeParameters *getTypeParameters() const override;
    std::vector<const IR::INamespace *> getNestedNamespaces() const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::Type_Method *getApplyMethodType() const override;
    const IR::ParameterList *getApplyParameters() const override;
    const IR::Type_Method *getConstructorMethodType() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    const IR::ParameterList *getConstructorParameters() const override;
    const IR::Type *getType() const override;
    IRNODE_DECLARE_APPLY_OVERLOAD(P4Control)
    void validate() const override;
    cstring toString() const override;
    bool operator==(IR::P4Control const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "P4Control"_cs; }
    static cstring static_type_name() { return "P4Control"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    P4Control(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    P4Control(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Control *type,
              const IR::ParameterList *constructorParams,
              IR::IndexedVector<IR::Declaration> controlLocals, const IR::BlockStatement *body)
        : Type_Declaration(srcInfo, name),
          type(type),
          constructorParams(constructorParams),
          controlLocals(controlLocals),
          body(body) {
        validate();
    }
    P4Control(IR::ID name, const IR::Type_Control *type, const IR::ParameterList *constructorParams,
              IR::IndexedVector<IR::Declaration> controlLocals, const IR::BlockStatement *body)
        : Type_Declaration(name),
          type(type),
          constructorParams(constructorParams),
          controlLocals(controlLocals),
          body(body) {
        validate();
    }
    P4Control(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Control *type,
              IR::IndexedVector<IR::Declaration> controlLocals, const IR::BlockStatement *body)
        : Type_Declaration(srcInfo, name), type(type), controlLocals(controlLocals), body(body) {
        validate();
    }
    P4Control(IR::ID name, const IR::Type_Control *type,
              IR::IndexedVector<IR::Declaration> controlLocals, const IR::BlockStatement *body)
        : Type_Declaration(name), type(type), controlLocals(controlLocals), body(body) {
        validate();
    }
    P4Control(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Control *type,
              const IR::ParameterList *constructorParams, const IR::BlockStatement *body)
        : Type_Declaration(srcInfo, name),
          type(type),
          constructorParams(constructorParams),
          body(body) {
        validate();
    }
    P4Control(IR::ID name, const IR::Type_Control *type, const IR::ParameterList *constructorParams,
              const IR::BlockStatement *body)
        : Type_Declaration(name), type(type), constructorParams(constructorParams), body(body) {
        validate();
    }
    P4Control(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Control *type,
              const IR::BlockStatement *body)
        : Type_Declaration(srcInfo, name), type(type), body(body) {
        validate();
    }
    P4Control(IR::ID name, const IR::Type_Control *type, const IR::BlockStatement *body)
        : Type_Declaration(name), type(type), body(body) {
        validate();
    }
    IRNODE_SUBCLASS(P4Control)
    DECLARE_TYPEINFO_WITH_TYPEID(P4Control, NodeKind::P4Control, Type_Declaration, INestedNamespace,
                                 ISimpleNamespace, IApply, IContainer, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
/// A P4-16 action
class P4Action : public Declaration,
                 public virtual ISimpleNamespace,
                 public virtual IAnnotated,
                 public virtual IFunctional {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::ParameterList *parameters = nullptr;
    const IR::BlockStatement *body = nullptr;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    const IR::ParameterList *getParameters() const override;
    bool operator==(IR::P4Action const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "P4Action"_cs; }
    static cstring static_type_name() { return "P4Action"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    P4Action(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    P4Action(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
             const IR::ParameterList *parameters, const IR::BlockStatement *body)
        : Declaration(srcInfo, name), annotations(annotations), parameters(parameters), body(body) {
        validate();
    }
    P4Action(IR::ID name, IR::Vector<IR::Annotation> annotations,
             const IR::ParameterList *parameters, const IR::BlockStatement *body)
        : Declaration(name), annotations(annotations), parameters(parameters), body(body) {
        validate();
    }
    P4Action(Util::SourceInfo srcInfo, IR::ID name, const IR::ParameterList *parameters,
             const IR::BlockStatement *body)
        : Declaration(srcInfo, name), parameters(parameters), body(body) {
        validate();
    }
    P4Action(IR::ID name, const IR::ParameterList *parameters, const IR::BlockStatement *body)
        : Declaration(name), parameters(parameters), body(body) {
        validate();
    }
    IRNODE_SUBCLASS(P4Action)
    DECLARE_TYPEINFO_WITH_TYPEID(P4Action, NodeKind::P4Action, Declaration, ISimpleNamespace,
                                 IAnnotated, IFunctional);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Error : public virtual ISimpleNamespace, public Type_Declaration {
 public:
    static const cstring error;
    IR::IndexedVector<IR::Declaration_ID> members;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    void validate() const override;
    bool operator==(IR::Type_Error const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_Error"_cs; }
    static cstring static_type_name() { return "Type_Error"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Error(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Error(Util::SourceInfo srcInfo, IR::ID name, IR::IndexedVector<IR::Declaration_ID> members)
        : Type_Declaration(srcInfo, name), members(members) {
        validate();
    }
    Type_Error(IR::ID name, IR::IndexedVector<IR::Declaration_ID> members)
        : Type_Declaration(name), members(members) {
        validate();
    }
    Type_Error(Util::SourceInfo srcInfo, IR::ID name) : Type_Declaration(srcInfo, name) {
        validate();
    }
    Type_Error(IR::ID name) : Type_Declaration(name) { validate(); }
    IRNODE_SUBCLASS(Type_Error)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Error, NodeKind::Type_Error, ISimpleNamespace,
                                 Type_Declaration);
};
}  // namespace P4::IR
namespace P4::IR {

class Declaration_MatchKind : public Node, public virtual ISimpleNamespace {
 public:
    IR::IndexedVector<IR::Declaration_ID> members;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    void validate() const override;
    bool operator==(IR::Declaration_MatchKind const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Declaration_MatchKind"_cs; }
    static cstring static_type_name() { return "Declaration_MatchKind"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Declaration_MatchKind(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    Declaration_MatchKind(Util::SourceInfo srcInfo, IR::IndexedVector<IR::Declaration_ID> members)
        : Node(srcInfo), members(members) {
        validate();
    }
    Declaration_MatchKind(IR::IndexedVector<IR::Declaration_ID> members) : members(members) {
        validate();
    }
    Declaration_MatchKind(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    Declaration_MatchKind() { validate(); }
    IRNODE_SUBCLASS(Declaration_MatchKind)
    DECLARE_TYPEINFO_WITH_TYPEID(Declaration_MatchKind, NodeKind::Declaration_MatchKind, Node,
                                 ISimpleNamespace);
};
}  // namespace P4::IR
namespace P4::IR {
/// Table property value abstract base class
class PropertyValue : public Node {
 public:
    bool operator==(IR::PropertyValue const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "PropertyValue"_cs; }
    static cstring static_type_name() { return "PropertyValue"_cs; }
    void toJSON(JSONGenerator &json) const override;
    PropertyValue(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;

 protected:
    PropertyValue(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    PropertyValue() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(PropertyValue)
    DECLARE_TYPEINFO_WITH_TYPEID(PropertyValue, NodeKind::PropertyValue, Node);
};
}  // namespace P4::IR
namespace P4::IR {
/// A table property whose value is an expression
class ExpressionValue : public PropertyValue {
 public:
    const IR::Expression *expression = nullptr;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::ExpressionValue const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "ExpressionValue"_cs; }
    static cstring static_type_name() { return "ExpressionValue"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ExpressionValue(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::PropertyValue const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ExpressionValue(Util::SourceInfo srcInfo, const IR::Expression *expression)
        : PropertyValue(srcInfo), expression(expression) {
        validate();
    }
    ExpressionValue(const IR::Expression *expression) : expression(expression) { validate(); }
    IRNODE_SUBCLASS(ExpressionValue)
    DECLARE_TYPEINFO_WITH_TYPEID(ExpressionValue, NodeKind::ExpressionValue, PropertyValue);
};
}  // namespace P4::IR
namespace P4::IR {
class ExpressionListValue : public PropertyValue {
 public:
    IR::Vector<IR::Expression> expressions;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::ExpressionListValue const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "ExpressionListValue"_cs; }
    static cstring static_type_name() { return "ExpressionListValue"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ExpressionListValue(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::PropertyValue const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ExpressionListValue(Util::SourceInfo srcInfo, IR::Vector<IR::Expression> expressions)
        : PropertyValue(srcInfo), expressions(expressions) {
        validate();
    }
    ExpressionListValue(IR::Vector<IR::Expression> expressions) : expressions(expressions) {
        validate();
    }
    IRNODE_SUBCLASS(ExpressionListValue)
    DECLARE_TYPEINFO_WITH_TYPEID(ExpressionListValue, NodeKind::ExpressionListValue, PropertyValue);
};
}  // namespace P4::IR
namespace P4::IR {

class ActionListElement : public Node, public virtual IAnnotated, public virtual IDeclaration {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::Expression *expression = nullptr;

    void dbprint(std::ostream &out) const override;
    IR::ID getName() const override;
    const IR::Path *getPath() const;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    void validate() const override;
    cstring toString() const override;
    bool operator==(IR::ActionListElement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "ActionListElement"_cs; }
    static cstring static_type_name() { return "ActionListElement"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ActionListElement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    ActionListElement(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations,
                      const IR::Expression *expression)
        : Node(srcInfo), annotations(annotations), expression(expression) {
        validate();
    }
    ActionListElement(IR::Vector<IR::Annotation> annotations, const IR::Expression *expression)
        : annotations(annotations), expression(expression) {
        validate();
    }
    ActionListElement(Util::SourceInfo srcInfo, const IR::Expression *expression)
        : Node(srcInfo), expression(expression) {
        validate();
    }
    ActionListElement(const IR::Expression *expression) : expression(expression) { validate(); }
    IRNODE_SUBCLASS(ActionListElement)
    DECLARE_TYPEINFO_WITH_TYPEID(ActionListElement, NodeKind::ActionListElement, Node, IAnnotated,
                                 IDeclaration);
};
}  // namespace P4::IR
namespace P4::IR {

class ActionList : public PropertyValue {
 public:
    IR::IndexedVector<IR::ActionListElement> actionList;
    void validate() const override;
    size_t size() const { return actionList.size(); }
    void push_back(const IR::ActionListElement *e) { actionList.push_back(e); }
    const IR::ActionListElement *getDeclaration(cstring n) const {
        return actionList.getDeclaration<ActionListElement>(n);
    }
    bool operator==(IR::ActionList const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "ActionList"_cs; }
    static cstring static_type_name() { return "ActionList"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ActionList(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::PropertyValue const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ActionList(Util::SourceInfo srcInfo, IR::IndexedVector<IR::ActionListElement> actionList)
        : PropertyValue(srcInfo), actionList(actionList) {
        validate();
    }
    ActionList(IR::IndexedVector<IR::ActionListElement> actionList) : actionList(actionList) {
        validate();
    }
    IRNODE_SUBCLASS(ActionList)
    DECLARE_TYPEINFO_WITH_TYPEID(ActionList, NodeKind::ActionList, PropertyValue);
};
}  // namespace P4::IR
namespace P4::IR {
class KeyElement : public Node, public virtual IAnnotated {
 public:
    const IR::Expression *expression = nullptr;
    const IR::PathExpression *matchType = nullptr;
    IR::Vector<IR::Annotation> annotations;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    IR::Node const *transform_visit(Transform &v);
    bool operator==(IR::KeyElement const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "KeyElement"_cs; }
    static cstring static_type_name() { return "KeyElement"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    KeyElement(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    KeyElement(Util::SourceInfo srcInfo, const IR::Expression *expression,
               const IR::PathExpression *matchType, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), expression(expression), matchType(matchType), annotations(annotations) {
        validate();
    }
    KeyElement(const IR::Expression *expression, const IR::PathExpression *matchType,
               IR::Vector<IR::Annotation> annotations)
        : expression(expression), matchType(matchType), annotations(annotations) {
        validate();
    }
    KeyElement(Util::SourceInfo srcInfo, const IR::Expression *expression,
               const IR::PathExpression *matchType)
        : Node(srcInfo), expression(expression), matchType(matchType) {
        validate();
    }
    KeyElement(const IR::Expression *expression, const IR::PathExpression *matchType)
        : expression(expression), matchType(matchType) {
        validate();
    }
    IRNODE_SUBCLASS(KeyElement)
    DECLARE_TYPEINFO_WITH_TYPEID(KeyElement, NodeKind::KeyElement, Node, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {

class Key : public PropertyValue {
 public:
    IR::Vector<IR::KeyElement> keyElements;
    void validate() const override;
    void push_back(const IR::KeyElement *ke) { keyElements.push_back(ke); }
    bool operator==(IR::Key const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Key"_cs; }
    static cstring static_type_name() { return "Key"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Key(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::PropertyValue const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Key(Util::SourceInfo srcInfo, IR::Vector<IR::KeyElement> keyElements)
        : PropertyValue(srcInfo), keyElements(keyElements) {
        validate();
    }
    Key(IR::Vector<IR::KeyElement> keyElements) : keyElements(keyElements) { validate(); }
    IRNODE_SUBCLASS(Key)
    DECLARE_TYPEINFO_WITH_TYPEID(Key, NodeKind::Key, PropertyValue);
};
}  // namespace P4::IR
namespace P4::IR {
/// Pre-defined entry in a table
class Entry : public Node, public virtual IAnnotated {
 public:
    /// annotations are optional (supported annotations: @priority(value))
    IR::Vector<IR::Annotation> annotations;
    bool isConst;
    /// optional const annotation
    const IR::Expression *priority = nullptr;
    /// optional entry priority
    const IR::ListExpression *keys = nullptr;
    /// must be a tuple expression
    const IR::Expression *action = nullptr;
    /// typically a MethodCallExpression.
    /// The action must be defined in action list
    bool singleton;
    /// True if the entry is not a list.
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    const IR::ListExpression *getKeys() const { return keys; }
    const IR::Expression *getAction() const { return action; }
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Entry const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Entry"_cs; }
    static cstring static_type_name() { return "Entry"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Entry(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    Entry(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations, bool isConst,
          const IR::Expression *priority, const IR::ListExpression *keys,
          const IR::Expression *action, bool singleton)
        : Node(srcInfo),
          annotations(annotations),
          isConst(isConst),
          priority(priority),
          keys(keys),
          action(action),
          singleton(singleton) {
        validate();
    }
    Entry(IR::Vector<IR::Annotation> annotations, bool isConst, const IR::Expression *priority,
          const IR::ListExpression *keys, const IR::Expression *action, bool singleton)
        : annotations(annotations),
          isConst(isConst),
          priority(priority),
          keys(keys),
          action(action),
          singleton(singleton) {
        validate();
    }
    Entry(Util::SourceInfo srcInfo, bool isConst, const IR::Expression *priority,
          const IR::ListExpression *keys, const IR::Expression *action, bool singleton)
        : Node(srcInfo),
          isConst(isConst),
          priority(priority),
          keys(keys),
          action(action),
          singleton(singleton) {
        validate();
    }
    Entry(bool isConst, const IR::Expression *priority, const IR::ListExpression *keys,
          const IR::Expression *action, bool singleton)
        : isConst(isConst), priority(priority), keys(keys), action(action), singleton(singleton) {
        validate();
    }
    IRNODE_SUBCLASS(Entry)
    DECLARE_TYPEINFO_WITH_TYPEID(Entry, NodeKind::Entry, Node, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
/// List of predefined entries. Part of table properties
class EntriesList : public PropertyValue {
 public:
    IR::Vector<IR::Entry> entries;
    size_t size() const { return entries.size(); }
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::EntriesList const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "EntriesList"_cs; }
    static cstring static_type_name() { return "EntriesList"_cs; }
    void toJSON(JSONGenerator &json) const override;
    EntriesList(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::PropertyValue const &a) const override;
    bool operator==(IR::Node const &a) const override;
    EntriesList(Util::SourceInfo srcInfo, IR::Vector<IR::Entry> entries)
        : PropertyValue(srcInfo), entries(entries) {
        validate();
    }
    EntriesList(IR::Vector<IR::Entry> entries) : entries(entries) { validate(); }
    IRNODE_SUBCLASS(EntriesList)
    DECLARE_TYPEINFO_WITH_TYPEID(EntriesList, NodeKind::EntriesList, PropertyValue);
};
}  // namespace P4::IR
namespace P4::IR {
class Property : public Declaration, public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::PropertyValue *value = nullptr;
    bool isConstant;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Property const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Property"_cs; }
    static cstring static_type_name() { return "Property"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Property(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Property(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
             const IR::PropertyValue *value, bool isConstant)
        : Declaration(srcInfo, name),
          annotations(annotations),
          value(value),
          isConstant(isConstant) {
        validate();
    }
    Property(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::PropertyValue *value,
             bool isConstant)
        : Declaration(name), annotations(annotations), value(value), isConstant(isConstant) {
        validate();
    }
    Property(Util::SourceInfo srcInfo, IR::ID name, const IR::PropertyValue *value, bool isConstant)
        : Declaration(srcInfo, name), value(value), isConstant(isConstant) {
        validate();
    }
    Property(IR::ID name, const IR::PropertyValue *value, bool isConstant)
        : Declaration(name), value(value), isConstant(isConstant) {
        validate();
    }
    IRNODE_SUBCLASS(Property)
    DECLARE_TYPEINFO_WITH_TYPEID(Property, NodeKind::Property, Declaration, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class TableProperties : public Node, public virtual ISimpleNamespace {
 public:
    IR::IndexedVector<IR::Property> properties;
    cstring toString() const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::Property *getProperty(cstring name) const {
        return properties.getDeclaration<Property>(name);
    }
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::Property *getProperty(std::string_view name) const {
        return properties.getDeclaration<Property>(name);
    }
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    void push_back(const IR::Property *prop) { properties.push_back(prop); }
    static const cstring actionsPropertyName;
    static const cstring keyPropertyName;
    static const cstring defaultActionPropertyName;
    static const cstring entriesPropertyName;
    static const cstring sizePropertyName;
    void validate() const override;
    bool operator==(IR::TableProperties const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "TableProperties"_cs; }
    static cstring static_type_name() { return "TableProperties"_cs; }
    void toJSON(JSONGenerator &json) const override;
    TableProperties(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    TableProperties(Util::SourceInfo srcInfo, IR::IndexedVector<IR::Property> properties)
        : Node(srcInfo), properties(properties) {
        validate();
    }
    TableProperties(IR::IndexedVector<IR::Property> properties) : properties(properties) {
        validate();
    }
    TableProperties(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    TableProperties() { validate(); }
    IRNODE_SUBCLASS(TableProperties)
    DECLARE_TYPEINFO_WITH_TYPEID(TableProperties, NodeKind::TableProperties, Node,
                                 ISimpleNamespace);
};
}  // namespace P4::IR
namespace P4::IR {
class P4Table : public Declaration, public virtual IAnnotated, public virtual IApply {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::TableProperties *properties = nullptr;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    const IR::Type_Method *getApplyMethodType() const override;
    const IR::ParameterList *getApplyParameters() const override;
    const IR::ActionList *getActionList() const {
        if (auto ap = properties->getProperty(TableProperties::actionsPropertyName)) {
            if (auto al = ap->value->to<IR::ActionList>()) return al;
            ::P4::error(ErrorType::ERR_INVALID, "%1%: must be an action list", ap);
        }
        return nullptr;
    }
    const IR::Key *getKey() const {
        if (auto kp = properties->getProperty(TableProperties::keyPropertyName)) {
            if (auto k = kp->value->to<IR::Key>()) return k;
            ::P4::error(ErrorType::ERR_INVALID, "%1%: must be a key", kp);
        }
        return nullptr;
    }
    const IR::Expression *getDefaultAction() const {
        if (auto d = properties->getProperty(TableProperties::defaultActionPropertyName)) {
            if (auto ev = d->value->to<IR::ExpressionValue>()) return ev->expression;
            ::P4::error(ErrorType::ERR_INVALID, "%1%: must be an expression", d);
        }
        return nullptr;
    }
    const IR::Constant *getConstantProperty(cstring name) const {
        if (auto d = properties->getProperty(name)) {
            if (auto ev = d->value->to<IR::ExpressionValue>()) {
                if (auto k = ev->expression->to<IR::Constant>()) {
                    return k;
                }
            }
            error(ErrorType::ERR_INVALID, "%1% must be a constant numeric expression", d);
        }
        return nullptr;
    }
    const IR::BoolLiteral *getBooleanProperty(cstring name) const {
        if (auto d = properties->getProperty(name)) {
            if (auto ev = d->value->to<IR::ExpressionValue>()) {
                if (auto k = ev->expression->to<IR::BoolLiteral>()) {
                    return k;
                }
            }
            error(ErrorType::ERR_INVALID, "%1% must be a boolean expression", d);
        }
        return nullptr;
    }
    const IR::Constant *getSizeProperty() const {
        return getConstantProperty(TableProperties::sizePropertyName);
    }
    const IR::EntriesList *getEntries() const {
        if (auto ep = properties->getProperty(TableProperties::entriesPropertyName)) {
            if (auto el = ep->value->to<IR::EntriesList>()) return el;
            ::P4::error(ErrorType::ERR_INVALID, "%1%: must be a list of entries", ep);
        }
        return nullptr;
    }
    bool operator==(IR::P4Table const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "P4Table"_cs; }
    static cstring static_type_name() { return "P4Table"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    P4Table(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    P4Table(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
            const IR::TableProperties *properties)
        : Declaration(srcInfo, name), annotations(annotations), properties(properties) {
        validate();
    }
    P4Table(IR::ID name, IR::Vector<IR::Annotation> annotations,
            const IR::TableProperties *properties)
        : Declaration(name), annotations(annotations), properties(properties) {
        validate();
    }
    P4Table(Util::SourceInfo srcInfo, IR::ID name, const IR::TableProperties *properties)
        : Declaration(srcInfo, name), properties(properties) {
        validate();
    }
    P4Table(IR::ID name, const IR::TableProperties *properties)
        : Declaration(name), properties(properties) {
        validate();
    }
    IRNODE_SUBCLASS(P4Table)
    DECLARE_TYPEINFO_WITH_TYPEID(P4Table, NodeKind::P4Table, Declaration, IAnnotated, IApply);
};
}  // namespace P4::IR
namespace P4::IR {
class P4ValueSet : public Declaration, public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::Type *elementType = nullptr;
    const IR::Expression *size = nullptr;

    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    bool operator==(IR::P4ValueSet const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "P4ValueSet"_cs; }
    static cstring static_type_name() { return "P4ValueSet"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    P4ValueSet(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    P4ValueSet(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
               const IR::Type *elementType, const IR::Expression *size)
        : Declaration(srcInfo, name),
          annotations(annotations),
          elementType(elementType),
          size(size) {
        validate();
    }
    P4ValueSet(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::Type *elementType,
               const IR::Expression *size)
        : Declaration(name), annotations(annotations), elementType(elementType), size(size) {
        validate();
    }
    P4ValueSet(Util::SourceInfo srcInfo, IR::ID name, const IR::Type *elementType,
               const IR::Expression *size)
        : Declaration(srcInfo, name), elementType(elementType), size(size) {
        validate();
    }
    P4ValueSet(IR::ID name, const IR::Type *elementType, const IR::Expression *size)
        : Declaration(name), elementType(elementType), size(size) {
        validate();
    }
    IRNODE_SUBCLASS(P4ValueSet)
    DECLARE_TYPEINFO_WITH_TYPEID(P4ValueSet, NodeKind::P4ValueSet, Declaration, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class Declaration_Variable : public Declaration, public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::Type *type = nullptr;
    const IR::Expression *initializer = nullptr;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Declaration_Variable const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Declaration_Variable"_cs; }
    static cstring static_type_name() { return "Declaration_Variable"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Declaration_Variable(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Declaration_Variable(Util::SourceInfo srcInfo, IR::ID name,
                         IR::Vector<IR::Annotation> annotations, const IR::Type *type,
                         const IR::Expression *initializer)
        : Declaration(srcInfo, name),
          annotations(annotations),
          type(type),
          initializer(initializer) {
        validate();
    }
    Declaration_Variable(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::Type *type,
                         const IR::Expression *initializer)
        : Declaration(name), annotations(annotations), type(type), initializer(initializer) {
        validate();
    }
    Declaration_Variable(Util::SourceInfo srcInfo, IR::ID name, const IR::Type *type,
                         const IR::Expression *initializer)
        : Declaration(srcInfo, name), type(type), initializer(initializer) {
        validate();
    }
    Declaration_Variable(IR::ID name, const IR::Type *type, const IR::Expression *initializer)
        : Declaration(name), type(type), initializer(initializer) {
        validate();
    }
    Declaration_Variable(Util::SourceInfo srcInfo, IR::ID name,
                         IR::Vector<IR::Annotation> annotations, const IR::Type *type)
        : Declaration(srcInfo, name), annotations(annotations), type(type) {
        validate();
    }
    Declaration_Variable(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::Type *type)
        : Declaration(name), annotations(annotations), type(type) {
        validate();
    }
    Declaration_Variable(Util::SourceInfo srcInfo, IR::ID name, const IR::Type *type)
        : Declaration(srcInfo, name), type(type) {
        validate();
    }
    Declaration_Variable(IR::ID name, const IR::Type *type) : Declaration(name), type(type) {
        validate();
    }
    IRNODE_SUBCLASS(Declaration_Variable)
    DECLARE_TYPEINFO_WITH_TYPEID(Declaration_Variable, NodeKind::Declaration_Variable, Declaration,
                                 IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class Declaration_Constant : public Declaration, public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::Type *type = nullptr;
    const IR::Expression *initializer = nullptr;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Declaration_Constant const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Declaration_Constant"_cs; }
    static cstring static_type_name() { return "Declaration_Constant"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Declaration_Constant(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Declaration_Constant(Util::SourceInfo srcInfo, IR::ID name,
                         IR::Vector<IR::Annotation> annotations, const IR::Type *type,
                         const IR::Expression *initializer)
        : Declaration(srcInfo, name),
          annotations(annotations),
          type(type),
          initializer(initializer) {
        validate();
    }
    Declaration_Constant(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::Type *type,
                         const IR::Expression *initializer)
        : Declaration(name), annotations(annotations), type(type), initializer(initializer) {
        validate();
    }
    Declaration_Constant(Util::SourceInfo srcInfo, IR::ID name, const IR::Type *type,
                         const IR::Expression *initializer)
        : Declaration(srcInfo, name), type(type), initializer(initializer) {
        validate();
    }
    Declaration_Constant(IR::ID name, const IR::Type *type, const IR::Expression *initializer)
        : Declaration(name), type(type), initializer(initializer) {
        validate();
    }
    IRNODE_SUBCLASS(Declaration_Constant)
    DECLARE_TYPEINFO_WITH_TYPEID(Declaration_Constant, NodeKind::Declaration_Constant, Declaration,
                                 IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
/// Like a variable, but for a statically allocated instance.
/// The syntax is Contructor(args) name = initializer;
/// Initializers are an experimental features, used for externs with
/// abstract methods.
class Declaration_Instance : public Declaration,
                             public virtual IAnnotated,
                             public virtual IInstance {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::Type *type = nullptr;

    const IR::Vector<IR::Argument> *arguments = nullptr;
    IR::NameMap<IR::Property> properties = {};

    const IR::BlockStatement *initializer = nullptr;

    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    const IR::Type *getType() const override;
    IR::ID Name() const override;
    void validate() const override;
    bool operator==(IR::Declaration_Instance const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Declaration_Instance"_cs; }
    static cstring static_type_name() { return "Declaration_Instance"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Declaration_Instance(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Declaration_Instance(Util::SourceInfo srcInfo, IR::ID name,
                         IR::Vector<IR::Annotation> annotations, const IR::Type *type,
                         const IR::Vector<IR::Argument> *arguments,
                         const IR::BlockStatement *initializer)
        : Declaration(srcInfo, name),
          annotations(annotations),
          type(type),
          arguments(arguments),
          initializer(initializer) {
        validate();
    }
    Declaration_Instance(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::Type *type,
                         const IR::Vector<IR::Argument> *arguments,
                         const IR::BlockStatement *initializer)
        : Declaration(name),
          annotations(annotations),
          type(type),
          arguments(arguments),
          initializer(initializer) {
        validate();
    }
    Declaration_Instance(Util::SourceInfo srcInfo, IR::ID name, const IR::Type *type,
                         const IR::Vector<IR::Argument> *arguments,
                         const IR::BlockStatement *initializer)
        : Declaration(srcInfo, name), type(type), arguments(arguments), initializer(initializer) {
        validate();
    }
    Declaration_Instance(IR::ID name, const IR::Type *type,
                         const IR::Vector<IR::Argument> *arguments,
                         const IR::BlockStatement *initializer)
        : Declaration(name), type(type), arguments(arguments), initializer(initializer) {
        validate();
    }
    Declaration_Instance(Util::SourceInfo srcInfo, IR::ID name,
                         IR::Vector<IR::Annotation> annotations, const IR::Type *type,
                         const IR::Vector<IR::Argument> *arguments)
        : Declaration(srcInfo, name), annotations(annotations), type(type), arguments(arguments) {
        validate();
    }
    Declaration_Instance(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::Type *type,
                         const IR::Vector<IR::Argument> *arguments)
        : Declaration(name), annotations(annotations), type(type), arguments(arguments) {
        validate();
    }
    Declaration_Instance(Util::SourceInfo srcInfo, IR::ID name, const IR::Type *type,
                         const IR::Vector<IR::Argument> *arguments)
        : Declaration(srcInfo, name), type(type), arguments(arguments) {
        validate();
    }
    Declaration_Instance(IR::ID name, const IR::Type *type,
                         const IR::Vector<IR::Argument> *arguments)
        : Declaration(name), type(type), arguments(arguments) {
        validate();
    }
    IRNODE_SUBCLASS(Declaration_Instance)
    DECLARE_TYPEINFO_WITH_TYPEID(Declaration_Instance, NodeKind::Declaration_Instance, Declaration,
                                 IAnnotated, IInstance);
};
}  // namespace P4::IR
namespace P4::IR {
/// Toplevel program representation
class P4Program : public Node, public virtual IGeneralNamespace {
 public:
    /// Top-level program objects.
    /// This is not an IndexedVector because:
    /// - we allow overloaded function-like objects.
    /// - not all objects in a P4Program are declarations (e.g., match_kind is not).
    IR::Vector<IR::Node> objects;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    void validate() const override;
    static const cstring main;
    IRNODE_DECLARE_APPLY_OVERLOAD(P4Program)
    bool operator==(IR::P4Program const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "P4Program"_cs; }
    static cstring static_type_name() { return "P4Program"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    P4Program(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    P4Program(Util::SourceInfo srcInfo, IR::Vector<IR::Node> objects)
        : Node(srcInfo), objects(objects) {
        validate();
    }
    P4Program(IR::Vector<IR::Node> objects) : objects(objects) { validate(); }
    P4Program(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    P4Program() { validate(); }
    IRNODE_SUBCLASS(P4Program)
    DECLARE_TYPEINFO_WITH_TYPEID(P4Program, NodeKind::P4Program, Node, IGeneralNamespace);
};
}  // namespace P4::IR
namespace P4::IR {
/////////////////////////////////////////////////////////////
class Function : public Declaration,
                 public virtual IFunctional,
                 public virtual IAnnotated,
                 public virtual ISimpleNamespace,
                 public virtual INestedNamespace {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::Type_Method *type = nullptr;
    const IR::BlockStatement *body = nullptr;
    const IR::ParameterList *getParameters() const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    std::vector<const IR::INamespace *> getNestedNamespaces() const override;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    bool operator==(IR::Function const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Function"_cs; }
    static cstring static_type_name() { return "Function"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Function(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Function(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
             const IR::Type_Method *type, const IR::BlockStatement *body)
        : Declaration(srcInfo, name), annotations(annotations), type(type), body(body) {
        validate();
    }
    Function(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::Type_Method *type,
             const IR::BlockStatement *body)
        : Declaration(name), annotations(annotations), type(type), body(body) {
        validate();
    }
    Function(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Method *type,
             const IR::BlockStatement *body)
        : Declaration(srcInfo, name), type(type), body(body) {
        validate();
    }
    Function(IR::ID name, const IR::Type_Method *type, const IR::BlockStatement *body)
        : Declaration(name), type(type), body(body) {
        validate();
    }
    IRNODE_SUBCLASS(Function)
    DECLARE_TYPEINFO_WITH_TYPEID(Function, NodeKind::Function, Declaration, IFunctional, IAnnotated,
                                 ISimpleNamespace, INestedNamespace);
};
}  // namespace P4::IR
namespace P4::IR {
/////////////////////////////////////////////////////////////
/**
 * Block is the base class for IR nodes produced by the evaluator.
 * A block represents a compile-time allocated resource.
 * Blocks are not visited using visitors, so the visit_children()
 * method is empty.  Users have to write custom visitors to
 * traverse the constantValue map.
 */
class Block : public Node, public virtual CompileTimeValue {
 public:
    const IR::Node *node = nullptr;
    /// Node that evaluates to this block.
    /// This is either a Declaration_Instance or a ConstructorCallExpression.
    /// One value for each Node inside that evaluates to a compile-time constant.
    /// This includes all constructor parameters, and all inner nested blocks.
    ordered_map<const IR::Node *, const IR::CompileTimeValue *> constantValue = {};
    virtual void dbprint(std::ostream &out) const override;
    virtual void dbprint_recursive(std::ostream &out) const;
    /// value can be null for parameters which are optional
    void setValue(const IR::Node *node, const IR::CompileTimeValue *value);
    bool hasValue(const IR::Node *node) const {
        return constantValue.find(node) != constantValue.end();
    }
    const IR::CompileTimeValue *getValue(const IR::Node *node) const {
        CHECK_NULL(node);
        auto it = constantValue.find(node);
        BUG_CHECK(it != constantValue.end(), "%1%: No such node %2%", this, node);
        return it->second;
    }
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    virtual IR::IDeclaration const *getContainer() const;
    bool operator==(IR::Block const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Block"_cs; }
    static cstring static_type_name() { return "Block"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Block(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;

 protected:
    Block(Util::SourceInfo srcInfo, const IR::Node *node) : Node(srcInfo), node(node) {
        validate();
    }
    Block(const IR::Node *node) : node(node) { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Block)
    DECLARE_TYPEINFO_WITH_TYPEID(Block, NodeKind::Block, Node, CompileTimeValue);
};
}  // namespace P4::IR
namespace P4::IR {
class TableBlock : public Block {
 public:
    const IR::P4Table *container = nullptr;
    IR::IDeclaration const *getContainer() const override;
    bool operator==(IR::TableBlock const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "TableBlock"_cs; }
    static cstring static_type_name() { return "TableBlock"_cs; }
    void toJSON(JSONGenerator &json) const override;
    TableBlock(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Block const &a) const override;
    bool operator==(IR::Node const &a) const override;
    TableBlock(Util::SourceInfo srcInfo, const IR::Node *node, const IR::P4Table *container)
        : Block(srcInfo, node), container(container) {
        validate();
    }
    TableBlock(const IR::Node *node, const IR::P4Table *container)
        : Block(node), container(container) {
        validate();
    }
    IRNODE_SUBCLASS(TableBlock)
    DECLARE_TYPEINFO_WITH_TYPEID(TableBlock, NodeKind::TableBlock, Block);
};
}  // namespace P4::IR
namespace P4::IR {
/// An object that has been instantiated
class InstantiatedBlock : public Block, public virtual IDeclaration {
 public:
    const IR::Type *instanceType = nullptr;

    virtual const IR::ParameterList *getConstructorParameters() const = 0;
    void instantiate(std::vector<const IR::CompileTimeValue *> *args);
    /// @return the argument that the given parameter was instantiated with.
    /// It's a fatal error if no such parameter exists.
    const IR::CompileTimeValue *getParameterValue(cstring paramName) const;
    /// @return the argument that the given parameter was instantiated with, or
    /// null if no such parameter exists.
    const IR::CompileTimeValue *findParameterValue(cstring paramName) const;
    virtual void dbprint(std::ostream &out) const override;
    bool operator==(IR::InstantiatedBlock const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "InstantiatedBlock"_cs; }
    static cstring static_type_name() { return "InstantiatedBlock"_cs; }
    void toJSON(JSONGenerator &json) const override;
    InstantiatedBlock(JSONLoader &json);
    bool operator==(IR::Block const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    InstantiatedBlock(Util::SourceInfo srcInfo, const IR::Node *node, const IR::Type *instanceType)
        : Block(srcInfo, node), instanceType(instanceType) {
        validate();
    }
    InstantiatedBlock(const IR::Node *node, const IR::Type *instanceType)
        : Block(node), instanceType(instanceType) {
        validate();
    }
    IRNODE_ABSTRACT_SUBCLASS(InstantiatedBlock)
    DECLARE_TYPEINFO_WITH_TYPEID(InstantiatedBlock, NodeKind::InstantiatedBlock, Block,
                                 IDeclaration);
};
}  // namespace P4::IR
namespace P4::IR {
class ParserBlock : public InstantiatedBlock {
 public:
    const IR::P4Parser *container = nullptr;
    const IR::ParameterList *getConstructorParameters() const override;
    cstring toString() const override;
    IR::ID getName() const override;
    IR::IDeclaration const *getContainer() const override;
    bool operator==(IR::ParserBlock const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "ParserBlock"_cs; }
    static cstring static_type_name() { return "ParserBlock"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ParserBlock(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::InstantiatedBlock const &a) const override;
    bool operator==(IR::Block const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ParserBlock(Util::SourceInfo srcInfo, const IR::Node *node, const IR::Type *instanceType,
                const IR::P4Parser *container)
        : InstantiatedBlock(srcInfo, node, instanceType), container(container) {
        validate();
    }
    ParserBlock(const IR::Node *node, const IR::Type *instanceType, const IR::P4Parser *container)
        : InstantiatedBlock(node, instanceType), container(container) {
        validate();
    }
    IRNODE_SUBCLASS(ParserBlock)
    DECLARE_TYPEINFO_WITH_TYPEID(ParserBlock, NodeKind::ParserBlock, InstantiatedBlock);
};
}  // namespace P4::IR
namespace P4::IR {
class ControlBlock : public InstantiatedBlock {
 public:
    const IR::P4Control *container = nullptr;
    const IR::ParameterList *getConstructorParameters() const override;
    cstring toString() const override;
    IR::ID getName() const override;
    IR::IDeclaration const *getContainer() const override;
    bool operator==(IR::ControlBlock const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "ControlBlock"_cs; }
    static cstring static_type_name() { return "ControlBlock"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ControlBlock(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::InstantiatedBlock const &a) const override;
    bool operator==(IR::Block const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ControlBlock(Util::SourceInfo srcInfo, const IR::Node *node, const IR::Type *instanceType,
                 const IR::P4Control *container)
        : InstantiatedBlock(srcInfo, node, instanceType), container(container) {
        validate();
    }
    ControlBlock(const IR::Node *node, const IR::Type *instanceType, const IR::P4Control *container)
        : InstantiatedBlock(node, instanceType), container(container) {
        validate();
    }
    IRNODE_SUBCLASS(ControlBlock)
    DECLARE_TYPEINFO_WITH_TYPEID(ControlBlock, NodeKind::ControlBlock, InstantiatedBlock);
};
}  // namespace P4::IR
namespace P4::IR {
class PackageBlock : public InstantiatedBlock {
 public:
    const IR::Type_Package *type = nullptr;
    const IR::ParameterList *getConstructorParameters() const override;
    cstring toString() const override;
    IR::ID getName() const override;
    bool operator==(IR::PackageBlock const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "PackageBlock"_cs; }
    static cstring static_type_name() { return "PackageBlock"_cs; }
    void toJSON(JSONGenerator &json) const override;
    PackageBlock(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::InstantiatedBlock const &a) const override;
    bool operator==(IR::Block const &a) const override;
    bool operator==(IR::Node const &a) const override;
    PackageBlock(Util::SourceInfo srcInfo, const IR::Node *node, const IR::Type *instanceType,
                 const IR::Type_Package *type)
        : InstantiatedBlock(srcInfo, node, instanceType), type(type) {
        validate();
    }
    PackageBlock(const IR::Node *node, const IR::Type *instanceType, const IR::Type_Package *type)
        : InstantiatedBlock(node, instanceType), type(type) {
        validate();
    }
    IRNODE_SUBCLASS(PackageBlock)
    DECLARE_TYPEINFO_WITH_TYPEID(PackageBlock, NodeKind::PackageBlock, InstantiatedBlock);
};
}  // namespace P4::IR
namespace P4::IR {
class ExternBlock : public InstantiatedBlock {
 public:
    const IR::Type_Extern *type = nullptr;
    const IR::Method *constructor = nullptr;

    const IR::ParameterList *getConstructorParameters() const override;
    cstring toString() const override;
    IR::ID getName() const override;
    bool operator==(IR::ExternBlock const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "ExternBlock"_cs; }
    static cstring static_type_name() { return "ExternBlock"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ExternBlock(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::InstantiatedBlock const &a) const override;
    bool operator==(IR::Block const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ExternBlock(Util::SourceInfo srcInfo, const IR::Node *node, const IR::Type *instanceType,
                const IR::Type_Extern *type, const IR::Method *constructor)
        : InstantiatedBlock(srcInfo, node, instanceType), type(type), constructor(constructor) {
        validate();
    }
    ExternBlock(const IR::Node *node, const IR::Type *instanceType, const IR::Type_Extern *type,
                const IR::Method *constructor)
        : InstantiatedBlock(node, instanceType), type(type), constructor(constructor) {
        validate();
    }
    IRNODE_SUBCLASS(ExternBlock)
    DECLARE_TYPEINFO_WITH_TYPEID(ExternBlock, NodeKind::ExternBlock, InstantiatedBlock);
};
}  // namespace P4::IR
namespace P4::IR {
/// Represents the program as a whole
class ToplevelBlock : public Block, public virtual IDeclaration {
 public:
    const IR::P4Program *getProgram() const;
    const IR::PackageBlock *getMain() const;
    IR::ID getName() const override;
    void validate() const override;
    bool operator==(IR::ToplevelBlock const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "ToplevelBlock"_cs; }
    static cstring static_type_name() { return "ToplevelBlock"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ToplevelBlock(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Block const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ToplevelBlock(Util::SourceInfo srcInfo, const IR::Node *node) : Block(srcInfo, node) {
        validate();
    }
    ToplevelBlock(const IR::Node *node) : Block(node) { validate(); }
    IRNODE_SUBCLASS(ToplevelBlock)
    DECLARE_TYPEINFO_WITH_TYPEID(ToplevelBlock, NodeKind::ToplevelBlock, Block, IDeclaration);
};
}  // namespace P4::IR

#endif  /* IR_GENERATED_DECLARATIONS_H_ */
