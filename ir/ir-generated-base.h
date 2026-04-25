#ifndef IR_GENERATED_BASE_H_
#define IR_GENERATED_BASE_H_

// IR base classes: interfaces, root abstract types, and shared
// extern template instantiations for IR::Vector / IR::IndexedVector.
// This header MUST be included (transitively) by every other ir-generated-*.h.

#include <functional>
#include <map>

#include "lib/big_int.h"  // IWYU pragma: keep
// Special IR classes and types
#include "ir/dbprint.h"         // IWYU pragma: keep
#include "ir/id.h"              // IWYU pragma: keep
#include "ir/indexed_vector.h"  // IWYU pragma: keep
#include "ir/namemap.h"         // IWYU pragma: keep
#include "ir/node.h"            // IWYU pragma: keep
#include "ir/nodemap.h"         // IWYU pragma: keep
#include "ir/vector.h"          // IWYU pragma: keep
#include "lib/ordered_map.h"    // IWYU pragma: keep

namespace P4 {

class JSONLoader;
using NodeFactoryFn = IR::Node *(*)(JSONLoader &);

namespace IR {
extern std::map<cstring, NodeFactoryFn> unpacker_table;
using namespace P4::literals;
}  // namespace IR
extern template class IR::Vector<IR::Node>;
extern template class IR::IndexedVector<IR::Node>;
extern template class IR::Vector<IR::Type>;
extern template class IR::Vector<IR::StatOrDecl>;
extern template class IR::IndexedVector<IR::StatOrDecl>;
extern template class IR::Vector<IR::Declaration>;
extern template class IR::IndexedVector<IR::Declaration>;
extern template class IR::Vector<IR::Expression>;
extern template class IR::Vector<IR::NamedExpression>;
extern template class IR::IndexedVector<IR::NamedExpression>;
extern template class IR::Vector<IR::AnnotationToken>;
extern template class IR::Vector<IR::Annotation>;
extern template class IR::Vector<IR::Argument>;
extern template class IR::Vector<IR::Parameter>;
extern template class IR::IndexedVector<IR::Parameter>;
extern template class IR::Vector<IR::Type_Var>;
extern template class IR::IndexedVector<IR::Type_Var>;
extern template class IR::Vector<IR::StructField>;
extern template class IR::IndexedVector<IR::StructField>;
extern template class IR::Vector<IR::Declaration_ID>;
extern template class IR::IndexedVector<IR::Declaration_ID>;
extern template class IR::Vector<IR::SerEnumMember>;
extern template class IR::IndexedVector<IR::SerEnumMember>;
extern template class IR::Vector<IR::ArgumentInfo>;
extern template class IR::Vector<IR::Method>;
extern template class IR::Vector<IR::SelectCase>;
extern template class IR::Vector<IR::ParserState>;
extern template class IR::IndexedVector<IR::ParserState>;
extern template class IR::Vector<IR::ActionListElement>;
extern template class IR::IndexedVector<IR::ActionListElement>;
extern template class IR::Vector<IR::KeyElement>;
extern template class IR::Vector<IR::Entry>;
extern template class IR::Vector<IR::Property>;
extern template class IR::IndexedVector<IR::Property>;
extern template class IR::Vector<IR::SwitchCase>;
extern template class IR::Vector<IR::Primitive>;
extern template class IR::Vector<IR::CaseEntry>;
}  // namespace P4

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "frontends/common/constantParsing.h"
#include "ir/annotations.h"

namespace P4::IR {
/// a value that can be evaluated at compile-time
class CompileTimeValue : public virtual INode {
 public:
    bool equiv(IR::CompileTimeValue const &other) const;
    DECLARE_TYPEINFO_WITH_TYPEID(CompileTimeValue, NodeKind::CompileTimeValue, INode);
};
}  // namespace P4::IR
namespace P4::IR {
/// Base class for P4 types
class Type : public Node {
 public:
    static const cstring minSizeInBits;
    static const cstring minSizeInBytes;
    static const cstring maxSizeInBits;
    static const cstring maxSizeInBytes;
    typedef Type_Unknown Unknown;
    typedef Type_Boolean Boolean;
    typedef Type_Bits Bits;
    typedef Type_String String;
    typedef Type_Varbits Varbits;
    typedef Type_Void Void;
    /// Well-defined only for types with fixed width
    virtual int width_bits() const;
    virtual int min_width_bits() const;
    virtual int max_width_bits() const;
    virtual int min_or_fixed_width_bits() const;
    virtual int max_or_fixed_width_bits() const;
    virtual bool variable() const;
    /// When possible returns the corresponding type that can be inserted
    /// in a P4 program; may return a Type_Name
    virtual IR::Type const *getP4Type() const = 0;
    bool operator==(IR::Type const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type"_cs; }
    static cstring static_type_name() { return "Type"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;

 protected:
    Type(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    Type() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Type)
    DECLARE_TYPEINFO_WITH_TYPEID(Type, NodeKind::Type, Node);
};
}  // namespace P4::IR
namespace P4::IR {
/// Implemented by all types that may be generic:
/// Control, Extern, Method, Package, and Parser
class IMayBeGenericType : public virtual INode {
 public:
    /// Allows the retrieval of type parameters
    virtual IR::TypeParameters const *getTypeParameters() const = 0;
    DECLARE_TYPEINFO_WITH_TYPEID(IMayBeGenericType, NodeKind::IMayBeGenericType, INode);
};
}  // namespace P4::IR
namespace P4::IR {
/// Implemented by objects with an 'apply' method: Parser, Control, Table
class IApply : public virtual INode {
 public:
    static const cstring applyMethodName;
    /// @returns the type signature of the apply method
    virtual IR::Type_Method const *getApplyMethodType() const = 0;
    virtual IR::ParameterList const *getApplyParameters() const = 0;
    DECLARE_TYPEINFO_WITH_TYPEID(IApply, NodeKind::IApply, INode);
};
}  // namespace P4::IR
namespace P4::IR {
/// base class for namespaces
class INamespace : public virtual INode {
 public:
    virtual Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const = 0;
    DECLARE_TYPEINFO_WITH_TYPEID(INamespace, NodeKind::INamespace, INode);
};
}  // namespace P4::IR
namespace P4::IR {
/// Does not allow two declarations with the same name
class ISimpleNamespace : public virtual INode, public virtual INamespace {
 public:
    virtual const IR::IDeclaration *getDeclByName(cstring name) const = 0;
    virtual const IR::IDeclaration *getDeclByName(std::string_view name) const = 0;
    DECLARE_TYPEINFO_WITH_TYPEID(ISimpleNamespace, NodeKind::ISimpleNamespace, INode, INamespace);
};
}  // namespace P4::IR
namespace P4::IR {
/// A general namespace can have multiple declarations with the same name
/// E.g., an extern can have multiple methods with the same name.
class IGeneralNamespace : public virtual INode, public virtual INamespace {
 public:
    virtual Util::Enumerator<const IR::IDeclaration *> *getDeclsByName(cstring name) const;
    /// prints an error if it finds duplicate names
    void checkDuplicateDeclarations() const;
    void validate() const override;
    DECLARE_TYPEINFO_WITH_TYPEID(IGeneralNamespace, NodeKind::IGeneralNamespace, INode, INamespace);
};
}  // namespace P4::IR
namespace P4::IR {

class INestedNamespace : public virtual INode, public virtual INamespace {
 public:
    virtual std::vector<const IR::INamespace *> getNestedNamespaces() const = 0;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    DECLARE_TYPEINFO_WITH_TYPEID(INestedNamespace, NodeKind::INestedNamespace, INode, INamespace);
};
}  // namespace P4::IR
namespace P4::IR {
/// Interface implemented by something that can be called
/// like a function.
class IFunctional : public virtual INode {
 public:
    /// The parameters of the functional object
    virtual const IR::ParameterList *getParameters() const = 0;
    /// Returns true if the parameters can be matched with the
    /// supplied arguments.
    bool callMatches(const IR::Vector<IR::Argument> *arguments) const;
    DECLARE_TYPEINFO_WITH_TYPEID(IFunctional, NodeKind::IFunctional, INode);
};
}  // namespace P4::IR
namespace P4::IR {
/// Implemented by things that look like type variables
class ITypeVar : public virtual INode {
 public:
    virtual cstring getVarName() const = 0;
    const IR::Type *asType() const { return to<Type>(); }
    virtual int getDeclId() const = 0;
    DECLARE_TYPEINFO_WITH_TYPEID(ITypeVar, NodeKind::ITypeVar, INode);
};
}  // namespace P4::IR
namespace P4::IR {
/// Implemented by P4Parser, P4Control and Type_Package
class IContainer : public virtual INode,
                   public virtual IMayBeGenericType,
                   public virtual IDeclaration,
                   public virtual IFunctional {
 public:
    virtual const IR::Type *getType() const = 0;
    /// The type of the constructor as a method
    virtual const IR::Type_Method *getConstructorMethodType() const = 0;
    virtual const IR::ParameterList *getConstructorParameters() const = 0;

    const IR::ParameterList *getParameters() const override;
    DECLARE_TYPEINFO_WITH_TYPEID(IContainer, NodeKind::IContainer, INode, IMayBeGenericType,
                                 IDeclaration, IFunctional);
};
}  // namespace P4::IR
namespace P4::IR {
/// This represents a primitive type
/// (called base type in the spec)
class Type_Base : public Type {
 public:
    IR::Type const *getP4Type() const override;
    virtual bool variable() const override;
    bool operator==(IR::Type_Base const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Base"_cs; }
    static cstring static_type_name() { return "Type_Base"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Base(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Type_Base(Util::SourceInfo srcInfo) : Type(srcInfo) { validate(); }
    Type_Base() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Type_Base)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Base, NodeKind::Type_Base, Type);
};
}  // namespace P4::IR
namespace P4::IR {
/// This is needed by Expression
class Type_Unknown : public Type_Base {
 public:
    static const IR::Type_Unknown *get();
    static const IR::Type_Unknown *get(Util::SourceInfo const &si);
    cstring toString() const override;
    bool operator==(IR::Type_Unknown const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Unknown"_cs; }
    static cstring static_type_name() { return "Type_Unknown"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Unknown(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Unknown(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_Unknown() { validate(); }
    IRNODE_SUBCLASS(Type_Unknown)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Unknown, NodeKind::Type_Unknown, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
/// A statement or a declaration
class StatOrDecl : public Node {
 public:
    bool operator==(IR::StatOrDecl const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "StatOrDecl"_cs; }
    static cstring static_type_name() { return "StatOrDecl"_cs; }
    void toJSON(JSONGenerator &json) const override;
    StatOrDecl(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;

 protected:
    StatOrDecl(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    StatOrDecl() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(StatOrDecl)
    DECLARE_TYPEINFO_WITH_TYPEID(StatOrDecl, NodeKind::StatOrDecl, Node);
};
}  // namespace P4::IR
namespace P4::IR {
/// Two declarations with the same name are not necessarily the same declaration.
/// That's why declid is used to distinguish them.
class Declaration : public StatOrDecl, public virtual IDeclaration {
 public:
    IR::ID name;
    long declid = nextId++;
    IR::ID getName() const override;
    bool equiv(IR::Node const &a_) const override;

 private:
    static long nextId;

 public:
    cstring toString() const override;
    bool operator==(IR::Declaration const &a) const override;
    cstring node_type_name() const override { return "Declaration"_cs; }
    static cstring static_type_name() { return "Declaration"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Declaration(JSONLoader &json);
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Declaration(Util::SourceInfo srcInfo, IR::ID name) : StatOrDecl(srcInfo), name(name) {
        validate();
    }
    Declaration(IR::ID name) : name(name) { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Declaration)
    DECLARE_TYPEINFO_WITH_TYPEID(Declaration, NodeKind::Declaration, StatOrDecl, IDeclaration);
};
}  // namespace P4::IR
namespace P4::IR {
/// A declaration which introduces a type.
/// Two declarations with the same name are not the same declaration
/// That's why declid is used to distinguish them.
/// (We don't use multiple inheritance, so we can't
/// inherit both Type and Declaration.)
class Type_Declaration : public Type, public virtual IDeclaration {
 public:
    IR::ID name;
    long declid = nextId++;
    IR::ID getName() const override;
    bool equiv(IR::Node const &a_) const override;

 private:
    static long nextId;

 public:
    cstring toString() const override;
    IR::Type const *getP4Type() const override;
    bool operator==(IR::Type_Declaration const &a) const override;
    cstring node_type_name() const override { return "Type_Declaration"_cs; }
    static cstring static_type_name() { return "Type_Declaration"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Declaration(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Type_Declaration(Util::SourceInfo srcInfo, IR::ID name) : Type(srcInfo), name(name) {
        validate();
    }
    Type_Declaration(IR::ID name) : name(name) { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Type_Declaration)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Declaration, NodeKind::Type_Declaration, Type, IDeclaration);
};
}  // namespace P4::IR
namespace P4::IR {
/// base class for expressions
class Expression : public Node {
 public:
    /// Note that the type field is not visited.
    /// Most P4_16 passes don't use this field.
    /// It is a used to hold the result of TypeInferencing for the expression.
    /// It is used by the P4_14 front-end and by some back-ends.
    /// It is not visited by the visitors by default (can be visited explicitly in preorder)
    const IR::Type *type = Type::Unknown::get();
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    IRNODE_DECLARE_APPLY_OVERLOAD(Expression)
    bool operator==(IR::Expression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Expression"_cs; }
    static cstring static_type_name() { return "Expression"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Expression(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;

 protected:
    Expression(Util::SourceInfo srcInfo, const IR::Type *type) : Node(srcInfo), type(type) {
        validate();
    }
    Expression(const IR::Type *type) : type(type) { validate(); }
    Expression(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    Expression() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Expression)
    DECLARE_TYPEINFO_WITH_TYPEID(Expression, NodeKind::Expression, Node);
};
}  // namespace P4::IR
namespace P4::IR {
class Operation : public Expression {
 public:
    virtual int getPrecedence() const = 0;
    virtual cstring getStringOp() const = 0;
    typedef Operation_Unary Unary;
    typedef Operation_Binary Binary;
    typedef Operation_Relation Relation;
    cstring toString() const override;
    bool operator==(IR::Operation const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Operation"_cs; }
    static cstring static_type_name() { return "Operation"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Operation(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Operation(Util::SourceInfo srcInfo, const IR::Type *type) : Expression(srcInfo, type) {
        validate();
    }
    Operation(const IR::Type *type) : Expression(type) { validate(); }
    Operation(Util::SourceInfo srcInfo) : Expression(srcInfo) { validate(); }
    Operation() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Operation)
    DECLARE_TYPEINFO_WITH_TYPEID(Operation, NodeKind::Operation, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
/// Currently paths can be absolute (starting with a dot) or relative
/// (just an identifier).  In a previous design paths could have
/// multiple components.
class Path : public Node {
 public:
    IR::ID name;
    bool absolute = false;
    bool isDontCare() const { return name.isDontCare(); }
    cstring toString() const override;
    cstring asString() const {
        // The CURRENT internal name
        return absl::StrCat(absolute ? "." : "", name);
    }
    void dbprint(std::ostream &out) const override;
    void validate() const override;
    bool operator==(IR::Path const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Path"_cs; }
    static cstring static_type_name() { return "Path"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Path(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    Path(Util::SourceInfo srcInfo, IR::ID name, bool absolute)
        : Node(srcInfo), name(name), absolute(absolute) {
        {
            if (!srcInfo) srcInfo = name.srcInfo;
        }
        validate();
    }
    Path(IR::ID name, bool absolute) : name(name), absolute(absolute) {
        {
            if (!srcInfo) srcInfo = name.srcInfo;
        }
        validate();
    }
    Path(Util::SourceInfo srcInfo, IR::ID name) : Node(srcInfo), name(name) {
        {
            if (!srcInfo) srcInfo = name.srcInfo;
        }
        validate();
    }
    Path(IR::ID name) : name(name) {
        {
            if (!srcInfo) srcInfo = name.srcInfo;
        }
        validate();
    }
    IRNODE_SUBCLASS(Path)
    DECLARE_TYPEINFO_WITH_TYPEID(Path, NodeKind::Path, Node);
};
}  // namespace P4::IR
namespace P4::IR {
/// Handy class used in several NamedMaps
class NamedExpression : public Declaration {
 public:
    const IR::Expression *expression = nullptr;
    bool operator==(IR::NamedExpression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "NamedExpression"_cs; }
    static cstring static_type_name() { return "NamedExpression"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    NamedExpression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    NamedExpression(Util::SourceInfo srcInfo, IR::ID name, const IR::Expression *expression)
        : Declaration(srcInfo, name), expression(expression) {
        validate();
    }
    NamedExpression(IR::ID name, const IR::Expression *expression)
        : Declaration(name), expression(expression) {
        validate();
    }
    IRNODE_SUBCLASS(NamedExpression)
    DECLARE_TYPEINFO_WITH_TYPEID(NamedExpression, NodeKind::NamedExpression, Declaration);
};
}  // namespace P4::IR
namespace P4::IR {
/// A token in an unparsed annotation.
/// `token_type` holds the ANTLR4 P4Lexer token id for this token (e.g.
/// `::P4Lexer::STRING_LITERAL`). It is stored as a plain int so this .def file
/// does not need to drag in the generated lexer header.
class AnnotationToken : public Node {
 public:
    int token_type;

    cstring text;
    UnparsedConstant *constInfo = nullptr;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::AnnotationToken const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "AnnotationToken"_cs; }
    static cstring static_type_name() { return "AnnotationToken"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    AnnotationToken(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    AnnotationToken(Util::SourceInfo srcInfo, int token_type, cstring text,
                    UnparsedConstant *constInfo)
        : Node(srcInfo), token_type(token_type), text(text), constInfo(constInfo) {
        validate();
    }
    AnnotationToken(int token_type, cstring text, UnparsedConstant *constInfo)
        : token_type(token_type), text(text), constInfo(constInfo) {
        validate();
    }
    AnnotationToken(Util::SourceInfo srcInfo, int token_type, cstring text)
        : Node(srcInfo), token_type(token_type), text(text) {
        validate();
    }
    AnnotationToken(int token_type, cstring text) : token_type(token_type), text(text) {
        validate();
    }
    IRNODE_SUBCLASS(AnnotationToken)
    DECLARE_TYPEINFO_WITH_TYPEID(AnnotationToken, NodeKind::AnnotationToken, Node);
};
}  // namespace P4::IR
namespace P4::IR {
/// Annotations are used to provide additional information to the compiler
/// Most P4 entities can be optionally annotated
class Annotation : public Node {
 public:
    IR::ID name;
    using UnparsedAnnotation = IR::Vector<IR::AnnotationToken>;
    using ExpressionAnnotation = IR::Vector<IR::Expression>;
    using KVAnnotation = IR::IndexedVector<IR::NamedExpression>;
    /// For annotations parsed from P4-16 source.
    Annotation(Util::SourceInfo si, IR::ID n, IR::Vector<IR::AnnotationToken> const &a)
        : Node(si), name(n), body(a), structured(false) {}

    Annotation(Util::SourceInfo si, IR::ID n, IR::Vector<IR::AnnotationToken> const &a,
               bool structured)
        : Node(si), name(n), body(a), structured(structured) {}

    Annotation(Util::SourceInfo si, IR::ID n, std::initializer_list<IR::Expression const *> a,
               bool structured = false)
        : Node(si), name(n), body(a), structured(structured) {}
    Annotation(Util::SourceInfo si, IR::ID n, IR::Expression const *a, bool structured = false)
        : Node(si), name(n), body(), structured(structured) {
        body.emplace<ExpressionAnnotation>(a);
    }
    Annotation(Util::SourceInfo si, IR::ID n, IR::Vector<IR::Expression> const &a,
               bool structured = false)
        : Node(si), name(n), body(a), structured(structured) {}
    Annotation(Util::SourceInfo si, IR::ID n, IR::IndexedVector<IR::NamedExpression> const &kv,
               bool structured = false)
        : Node(si), name(n), body(kv), structured(structured) {}
    Annotation(IR::ID n, IR::Expression const *a, bool structured = false)
        : name(n), body(), structured(structured) {
        body.emplace<ExpressionAnnotation>(a);
    }
    Annotation(IR::ID n, std::initializer_list<IR::Expression const *> a, bool structured = false)
        : name(n), body(a), structured(structured) {}
    Annotation(IR::ID n, IR::Vector<IR::Expression> const &a, bool structured = false)
        : name(n), body(a), structured(structured) {}
    Annotation(IR::ID n, intmax_t v, bool structured = false);

    Annotation(IR::ID n, cstring v, bool structured = false);

    static const cstring nameAnnotation;
    /// Indicates the control-plane name.
    static const cstring tableOnlyAnnotation;
    /// Action cannot be a default_action.
    static const cstring defaultOnlyAnnotation;
    /// action can only be a default_action.
    static const cstring atomicAnnotation;
    /// Code should be executed atomically.
    static const cstring hiddenAnnotation;
    /// Object should not be exposed to the control-plane.
    static const cstring lengthAnnotation;
    /// P4-14 annotation for varbit fields.
    static const cstring maxLengthAnnotation;
    /// P4-14 annotation for varbit fields.
    static const cstring optionalAnnotation;
    /// Optional parameter annotation
    static const cstring pkginfoAnnotation;
    /// Package documentation annotation.
    static const cstring deprecatedAnnotation;
    /// Deprecation annotation.
    static const cstring synchronousAnnotation;
    /// Synchronous annotation.
    static const cstring pureAnnotation;
    /// extern function/method annotation.
    static const cstring noSideEffectsAnnotation;
    /// extern function/method annotation.
    static const cstring noWarnAnnotation;
    /// noWarn annotation.
    static const cstring matchAnnotation;
    /// Match annotation (for value sets).
    static const cstring fieldListAnnotation;
    /// Used for recirculate, etc.
    static const cstring debugLoggingAnnotation;
    /// Used by compiler implementer to limit debug log to the annotated IR context.
    static const cstring disableOptimizationAnnotation;
    /// annotation to disable certain optimization
    static const cstring inlinedFromAnnotation;
    /// annotation to mark block of inlined function
    static const cstring likelyAnnotation;
    /// annotation for likely taken blocks/branchs
    static const cstring unlikelyAnnotation;
    /// annotation for likely not taken blocks/branchs
    cstring toString() const override;
    void validate() const override;
    /// Extracts name value from a name annotation
    cstring getName() const;
    /// Extracts a single string argument; cstring::empty if the argument is not a string;
    /// if error is true, emits an error if the argument is not a string
    cstring getSingleString(bool error = true) const;
    /// Whether the annotation body needs to be parsed.
    bool needsParsing() const { return std::holds_alternative<UnparsedAnnotation>(body); }
    enum class Kind { Unparsed, Unstructured, StructuredKVList, StructuredExpressionList };
    IR::Annotation::Kind annotationKind() const {
        if (needsParsing()) return Kind::Unparsed;
        if (!structured) return Kind::Unstructured;
        if (std::holds_alternative<ExpressionAnnotation>(body))
            return Kind::StructuredExpressionList;
        if (std::holds_alternative<KVAnnotation>(body)) return Kind::StructuredKVList;

        BUG("Invalid annotation kind");
    }

    using body_variant = std::variant<IR::Vector<IR::AnnotationToken>, IR::Vector<IR::Expression>,
                                      IR::IndexedVector<IR::NamedExpression>>;
    body_variant body;
    auto &getUnparsed() {
        try {
            return std::get<UnparsedAnnotation>(body);
        } catch (const std::bad_variant_access &) {
            BUG("Annotation has been parsed already.");
        }
    }
    auto const &getUnparsed() const {
        try {
            return std::get<UnparsedAnnotation>(body);
        } catch (const std::bad_variant_access &) {
            BUG("Annotation has been parsed already.");
        }
    }
    auto &getExpr() {
        try {
            return std::get<ExpressionAnnotation>(body);
        } catch (const std::bad_variant_access &) {
            BUG("Annotation does not contain an expression list.");
        }
    }
    auto const &getExpr() const {
        try {
            return std::get<ExpressionAnnotation>(body);
        } catch (const std::bad_variant_access &) {
            BUG("Annotation does not contain an expression list.");
        }
    }
    const IR::Expression *getExpr(size_t idx) const {
        try {
            const auto &expr = getExpr();
            return expr[idx];
        } catch (const std::out_of_range &) {
            BUG("invalid annotation expression index");
        } catch (const std::bad_variant_access &) {
            BUG("Annotation does not contain an expression list.");
        }
    }
    auto &getKV() {
        try {
            return std::get<KVAnnotation>(body);
        } catch (const std::bad_variant_access &) {
            BUG("Annotation does not contain a key-value list.");
        }
    }
    auto const &getKV() const {
        try {
            return std::get<KVAnnotation>(body);
        } catch (const std::bad_variant_access &) {
            BUG("Annotation does not contain a key-value list.");
        }
    }
    /// If this is true this is a structured annotation, and there are some
    /// constraints on its contents.
    bool structured;
    bool operator==(IR::Annotation const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Annotation"_cs; }
    static cstring static_type_name() { return "Annotation"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Annotation(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    Annotation(Util::SourceInfo srcInfo, IR::ID name, body_variant body, bool structured)
        : Node(srcInfo), name(name), body(body), structured(structured) {
        {
            if (!srcInfo) srcInfo = name.srcInfo;
        }
        validate();
    }
    Annotation(IR::ID name, body_variant body, bool structured)
        : name(name), body(body), structured(structured) {
        {
            if (!srcInfo) srcInfo = name.srcInfo;
        }
        validate();
    }
    IRNODE_SUBCLASS(Annotation)
    DECLARE_TYPEINFO_WITH_TYPEID(Annotation, NodeKind::Annotation, Node);
};
}  // namespace P4::IR
namespace P4::IR {
/// Implemented by all objects that can have annotations
// FIXME: Use CRTP to get access to the fields directly
class IAnnotated : public virtual INode {
 public:
    virtual IR::Vector<IR::Annotation> const &getAnnotations() const = 0;
    virtual IR::Vector<IR::Annotation> &getAnnotations() = 0;
    const IR::Annotation *getAnnotation(cstring name) const {
        const auto &annotations = getAnnotations();
        return get(annotations, name);
    }
    /// Checks if there is annotation @name
    bool hasAnnotation(cstring name) const {
        const auto &annotations = getAnnotations();
        return get(annotations, name) != nullptr;
    }
    /// Checks if there is annotation @name and it is the only annotation on the
    /// node
    bool hasOnlyAnnotation(cstring name) const {
        const auto &annotations = getAnnotations();
        return annotations.size() == 1 && get(annotations, name) != nullptr;
    }
    /// Check if there are any annotations
    bool hasAnnotations() const {
        const auto &annotations = getAnnotations();
        return !annotations.empty();
    }
    void addAnnotation(const IR::Annotation *annot) {
        auto &annotations = getAnnotations();
        annotations.push_back(annot);
    }
    void addAnnotation(cstring name, const IR::Expression *expr, bool structured = false) {
        addAnnotation(new Annotation(name, {expr}, structured));
    }
    /// Add annotation if another annotation with the same name is not
    /// already present.
    void addAnnotationIfNew(cstring name, const IR::Expression *expr, bool structured = false) {
        Annotations::addIfNew(getAnnotations(), name, expr, structured);
    }
    void addAnnotationIfNew(const IR::Annotation *ann) {
        Annotations::addIfNew(getAnnotations(), ann);
    }
    /// If annotations with the same name are already present, remove them;
    /// add this annotation.
    void addOrReplaceAnnotation(cstring name, const IR::Expression *expr, bool structured = false) {
        Annotations::addOrReplace(getAnnotations(), name, expr, structured);
    }
    void addOrReplaceAnnotation(const IR::Annotation *ann) {
        Annotations::addOrReplace(getAnnotations(), ann);
    }
    DECLARE_TYPEINFO_WITH_TYPEID(IAnnotated, NodeKind::IAnnotated, INode);
};
}  // namespace P4::IR
namespace P4::IR {
class IInstance : public virtual INode {
 public:
    virtual IR::ID Name() const = 0;
    virtual const IR::Type *getType() const = 0;
    DECLARE_TYPEINFO_WITH_TYPEID(IInstance, NodeKind::IInstance, INode);
};
}  // namespace P4::IR
namespace P4::IR {
/// An argument to a function call (or constructor call)
/// Arguments may have optional names
class Argument : public Node {
 public:
    /// If an argument has no name the name.name is nullptr.
    IR::ID name;
    const IR::Expression *expression = nullptr;
    void dbprint(std::ostream &out) const override;
    void validate() const override;
    cstring toString() const override;
    bool operator==(IR::Argument const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Argument"_cs; }
    static cstring static_type_name() { return "Argument"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Argument(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    Argument(Util::SourceInfo srcInfo, IR::ID name, const IR::Expression *expression)
        : Node(srcInfo), name(name), expression(expression) {
        {
            if (!srcInfo && expression) srcInfo = expression->srcInfo;
        }
        validate();
    }
    Argument(IR::ID name, const IR::Expression *expression) : name(name), expression(expression) {
        {
            if (!srcInfo && expression) srcInfo = expression->srcInfo;
        }
        validate();
    }
    Argument(Util::SourceInfo srcInfo, const IR::Expression *expression)
        : Node(srcInfo), expression(expression) {
        {
            if (!srcInfo && expression) srcInfo = expression->srcInfo;
        }
        validate();
    }
    Argument(const IR::Expression *expression) : expression(expression) {
        {
            if (!srcInfo && expression) srcInfo = expression->srcInfo;
        }
        validate();
    }
    IRNODE_SUBCLASS(Argument)
    DECLARE_TYPEINFO_WITH_TYPEID(Argument, NodeKind::Argument, Node);
};
}  // namespace P4::IR

#endif  /* IR_GENERATED_BASE_H_ */
