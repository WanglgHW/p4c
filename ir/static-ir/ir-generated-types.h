#ifndef IR_GENERATED_TYPES_H_
#define IR_GENERATED_TYPES_H_

// IR type classes: every Type_* node, Parameter / ParameterList,
// TypeParameters, StructField, Method, ArgumentInfo, SerEnumMember.

#include "ir/ir-generated-base.h"

/*
   This file contains IR related to representating the type hierarchy.
   Some of these classes never appear in the IR tree, they are just
   synthesized by the type-checker.
*/
namespace P4 {
namespace IR {
enum class Direction { None, In, Out, InOut };

inline cstring directionToString(IR::Direction direction) {
    switch (direction) {
        case IR::Direction::None:
            return "<none>"_cs;
        case IR::Direction::In:
            return "in"_cs;
        case IR::Direction::Out:
            return "out"_cs;
        case IR::Direction::InOut:
            return "inout"_cs;
        default:
            BUG("Unhandled case");
    }
}
}  // namespace IR

inline std::ostream &operator<<(std::ostream &out, IR::Direction d) {
    switch (d) {
        case IR::Direction::None:
            break;
        case IR::Direction::In:
            out << "in";
            break;
        case IR::Direction::Out:
            out << "out";
            break;
        case IR::Direction::InOut:
            out << "inout";
            break;
        default:
            BUG("Unhandled case");
    }
    return out;
}

// FIXME: should accept string_view
inline bool operator>>(cstring s, IR::Direction &d) {
    if (!s || s == cstring::empty)
        d = IR::Direction::None;
    else if (s == "in")
        d = IR::Direction::In;
    else if (s == "out")
        d = IR::Direction::Out;
    else if (s == "inout")
        d = IR::Direction::InOut;
    else
        return false;
    return true;
}

}  // namespace P4

namespace P4::IR {
/// This represents a type that can unify with any other type.
/// It is the original type of Dots (...) expressions.
/// There is no syntax to represent this type.
/// Treated like a type variable so that unification can assign it a value.
class Type_Any : public Type, public virtual ITypeVar {
 protected:
    void *operator new(size_t size) { return ::operator new(size); }
// FIXME: Remove this #ifdefine check once we switch to C++20
#if defined(__cpp_sized_deallocation) && __cpp_sized_deallocation >= 201309L
    void operator delete(void *p, size_t size) { return ::operator delete(p, size); }
#else
    void operator delete(void *p) { return ::operator delete(p); }
#endif
    static long nextId;

 public:
    long declid = nextId++;
    cstring getVarName() const override;
    int getDeclId() const override;
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    bool operator==(IR::Type_Any const &a) const override;
    static const IR::Type_Any *get();
    static const IR::Type_Any *get(Util::SourceInfo const &si);
    IR::Type const *getP4Type() const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Any"_cs; }
    static cstring static_type_name() { return "Type_Any"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Any(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Any(Util::SourceInfo srcInfo) : Type(srcInfo) { validate(); }
    Type_Any() { validate(); }
    IRNODE_SUBCLASS(Type_Any)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Any, NodeKind::Type_Any, Type, ITypeVar);
};
}  // namespace P4::IR
namespace P4::IR {
/// This type is a fragment of another type.
/// This is used in conjunction with Type_Any to typecheck
/// expressions containing ... (Dots).
/// After unification this type replaces Type_Any.
/// For example:
/// struct S { bit<32> s; bit<16> t; }
/// S s = { s = 2, ... };
/// The type assigned to 'type' by unification will be
/// Type_Fragment { type = Type_UnknownStruct { t: Type_Bits<15> } }.
/// In other words, the type of the ... expression is a
/// fragment of a struct that contains just the field t.
class Type_Fragment : public Type {
 public:
    const IR::Type *type = nullptr;
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    IR::Type const *getP4Type() const override;
    bool operator==(IR::Type_Fragment const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_Fragment"_cs; }
    static cstring static_type_name() { return "Type_Fragment"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Fragment(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Fragment(Util::SourceInfo srcInfo, const IR::Type *type) : Type(srcInfo), type(type) {
        validate();
    }
    Type_Fragment(const IR::Type *type) : type(type) { validate(); }
    IRNODE_SUBCLASS(Type_Fragment)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Fragment, NodeKind::Type_Fragment, Type);
};
}  // namespace P4::IR
namespace P4::IR {
/// Represents the type of a type.
/// For example, in a declaration like
/// bit<32> x;
/// The type of x is Type_Bits(32);
/// The type of 'bit<32>' is Type_Type(Type_Bits(32))
/// TypeType should not appear in the program IR, just in the TypeMap produced
/// by type-checking.
class Type_Type : public Type {
 public:
    const IR::Type *type = nullptr;
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    IR::Type const *getP4Type() const override;
    void validate() const override;
    bool operator==(IR::Type_Type const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_Type"_cs; }
    static cstring static_type_name() { return "Type_Type"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Type(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Type(Util::SourceInfo srcInfo, const IR::Type *type) : Type(srcInfo), type(type) {
        validate();
    }
    Type_Type(const IR::Type *type) : type(type) { validate(); }
    IRNODE_SUBCLASS(Type_Type)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Type, NodeKind::Type_Type, Type);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Boolean : public Type_Base {
 protected:
    void *operator new(size_t size) { return ::operator new(size); }
// FIXME: Remove this #ifdefine check once we switch to C++20
#if defined(__cpp_sized_deallocation) && __cpp_sized_deallocation >= 201309L
    void operator delete(void *p, size_t size) { return ::operator delete(p, size); }
#else
    void operator delete(void *p) { return ::operator delete(p); }
#endif
 public:
    static const IR::Type_Boolean *get();
    static const IR::Type_Boolean *get(Util::SourceInfo const &si);
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    int min_or_fixed_width_bits() const override;
    int max_or_fixed_width_bits() const override;
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_Boolean const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Boolean"_cs; }
    static cstring static_type_name() { return "Type_Boolean"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Boolean(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Boolean(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_Boolean() { validate(); }
    IRNODE_SUBCLASS(Type_Boolean)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Boolean, NodeKind::Type_Boolean, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
/// The type of a parser state
class Type_State : public Type_Base {
 protected:
    void *operator new(size_t size) { return ::operator new(size); }
// FIXME: Remove this #ifdefine check once we switch to C++20
#if defined(__cpp_sized_deallocation) && __cpp_sized_deallocation >= 201309L
    void operator delete(void *p, size_t size) { return ::operator delete(p, size); }
#else
    void operator delete(void *p) { return ::operator delete(p); }
#endif
 public:
    static const IR::Type_State *get();
    static const IR::Type_State *get(Util::SourceInfo const &si);
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_State const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_State"_cs; }
    static cstring static_type_name() { return "Type_State"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_State(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_State(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_State() { validate(); }
    IRNODE_SUBCLASS(Type_State)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_State, NodeKind::Type_State, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
/// Represents both bit<> and int<> types in P4-14 and P4-16
class Type_Bits : public Type_Base {
 protected:
    void *operator new(size_t size) { return ::operator new(size); }
// FIXME: Remove this #ifdefine check once we switch to C++20
#if defined(__cpp_sized_deallocation) && __cpp_sized_deallocation >= 201309L
    void operator delete(void *p, size_t size) { return ::operator delete(p, size); }
#else
    void operator delete(void *p) { return ::operator delete(p); }
#endif
 public:
    int size = 0;

    const IR::Expression *expression = nullptr;

    bool isSigned;
    static const IR::Type_Bits *get(Util::SourceInfo const &si, const IR::Expression *expression,
                                    bool isSigned = false);
    static const IR::Type_Bits *get(Util::SourceInfo const &si, int sz, bool isSigned = false);
    static const IR::Type_Bits *get(int sz, bool isSigned = false);
    cstring baseName() const { return isSigned ? "int"_cs : "bit"_cs; }
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_Bits const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_Bits"_cs; }
    static cstring static_type_name() { return "Type_Bits"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Bits(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Bits(Util::SourceInfo srcInfo, int size, const IR::Expression *expression, bool isSigned)
        : Type_Base(srcInfo), size(size), expression(expression), isSigned(isSigned) {
        validate();
    }
    Type_Bits(int size, const IR::Expression *expression, bool isSigned)
        : size(size), expression(expression), isSigned(isSigned) {
        validate();
    }
    Type_Bits(Util::SourceInfo srcInfo, const IR::Expression *expression, bool isSigned)
        : Type_Base(srcInfo), expression(expression), isSigned(isSigned) {
        validate();
    }
    Type_Bits(const IR::Expression *expression, bool isSigned)
        : expression(expression), isSigned(isSigned) {
        validate();
    }
    Type_Bits(Util::SourceInfo srcInfo, int size, bool isSigned)
        : Type_Base(srcInfo), size(size), isSigned(isSigned) {
        validate();
    }
    Type_Bits(int size, bool isSigned) : size(size), isSigned(isSigned) { validate(); }
    Type_Bits(Util::SourceInfo srcInfo, bool isSigned) : Type_Base(srcInfo), isSigned(isSigned) {
        validate();
    }
    Type_Bits(bool isSigned) : isSigned(isSigned) { validate(); }
    IRNODE_SUBCLASS(Type_Bits)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Bits, NodeKind::Type_Bits, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Varbits : public Type_Base {
 protected:
    void *operator new(size_t size) { return ::operator new(size); }
// FIXME: Remove this #ifdefine check once we switch to C++20
#if defined(__cpp_sized_deallocation) && __cpp_sized_deallocation >= 201309L
    void operator delete(void *p, size_t size) { return ::operator delete(p, size); }
#else
    void operator delete(void *p) { return ::operator delete(p); }
#endif
 public:
    int size = 0;

    const IR::Expression *expression = nullptr;

    static const IR::Type_Varbits *get(Util::SourceInfo const &si, const IR::Expression *expr);
    static const IR::Type_Varbits *get(Util::SourceInfo const &si, int size);
    static const IR::Type_Varbits *get(int size);
    static const IR::Type_Varbits *get();
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    int min_or_fixed_width_bits() const override;
    int max_or_fixed_width_bits() const override;
    virtual bool variable() const override;
    bool operator==(IR::Type_Varbits const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_Varbits"_cs; }
    static cstring static_type_name() { return "Type_Varbits"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Varbits(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Varbits(Util::SourceInfo srcInfo, int size, const IR::Expression *expression)
        : Type_Base(srcInfo), size(size), expression(expression) {
        validate();
    }
    Type_Varbits(int size, const IR::Expression *expression) : size(size), expression(expression) {
        validate();
    }
    Type_Varbits(Util::SourceInfo srcInfo, const IR::Expression *expression)
        : Type_Base(srcInfo), expression(expression) {
        validate();
    }
    Type_Varbits(const IR::Expression *expression) : expression(expression) { validate(); }
    Type_Varbits(Util::SourceInfo srcInfo, int size) : Type_Base(srcInfo), size(size) {
        validate();
    }
    Type_Varbits(int size) : size(size) { validate(); }
    Type_Varbits(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_Varbits() { validate(); }
    IRNODE_SUBCLASS(Type_Varbits)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Varbits, NodeKind::Type_Varbits, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class Parameter : public Declaration, public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    Direction direction;
    const IR::Type *type = nullptr;
    const IR::Expression *defaultValue = nullptr;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    bool hasOut() const {
        return direction == IR::Direction::Out || direction == IR::Direction::InOut;
    }
    bool isOptional() const { return getAnnotation(Annotation::optionalAnnotation) != nullptr; }
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Parameter const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Parameter"_cs; }
    static cstring static_type_name() { return "Parameter"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Parameter(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Parameter(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
              Direction direction, const IR::Type *type, const IR::Expression *defaultValue)
        : Declaration(srcInfo, name),
          annotations(annotations),
          direction(direction),
          type(type),
          defaultValue(defaultValue) {
        validate();
    }
    Parameter(IR::ID name, IR::Vector<IR::Annotation> annotations, Direction direction,
              const IR::Type *type, const IR::Expression *defaultValue)
        : Declaration(name),
          annotations(annotations),
          direction(direction),
          type(type),
          defaultValue(defaultValue) {
        validate();
    }
    Parameter(Util::SourceInfo srcInfo, IR::ID name, Direction direction, const IR::Type *type,
              const IR::Expression *defaultValue)
        : Declaration(srcInfo, name), direction(direction), type(type), defaultValue(defaultValue) {
        validate();
    }
    Parameter(IR::ID name, Direction direction, const IR::Type *type,
              const IR::Expression *defaultValue)
        : Declaration(name), direction(direction), type(type), defaultValue(defaultValue) {
        validate();
    }
    Parameter(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
              Direction direction, const IR::Type *type)
        : Declaration(srcInfo, name), annotations(annotations), direction(direction), type(type) {
        validate();
    }
    Parameter(IR::ID name, IR::Vector<IR::Annotation> annotations, Direction direction,
              const IR::Type *type)
        : Declaration(name), annotations(annotations), direction(direction), type(type) {
        validate();
    }
    Parameter(Util::SourceInfo srcInfo, IR::ID name, Direction direction, const IR::Type *type)
        : Declaration(srcInfo, name), direction(direction), type(type) {
        validate();
    }
    Parameter(IR::ID name, Direction direction, const IR::Type *type)
        : Declaration(name), direction(direction), type(type) {
        validate();
    }
    IRNODE_SUBCLASS(Parameter)
    DECLARE_TYPEINFO_WITH_TYPEID(Parameter, NodeKind::Parameter, Declaration, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class ParameterList : public Node, public virtual ISimpleNamespace {
 public:
    IR::IndexedVector<IR::Parameter> parameters;
    void validate() const override;
    Util::Enumerator<const IR::Parameter *> *getEnumerator() const {
        return parameters.getEnumerator();
    }
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    size_t size() const { return parameters.size(); }
    bool empty() const { return size() == 0; }
    const IR::Parameter *getParameter(cstring name) const {
        return parameters.getDeclaration<Parameter>(name);
    }
    const IR::Parameter *getParameter(std::string_view name) const {
        return parameters.getDeclaration<Parameter>(name);
    }
    const IR::Parameter *getParameter(unsigned index) const {
        for (auto &param : parameters)
            if (0 == index--) return param;
        BUG("Only %1% parameters; index #%2% requested", size(), size() + index);
    }
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    void push_back(IR::Parameter const *p) { parameters.push_back(p); }
    cstring toString() const override;
    auto begin() const -> decltype(parameters.begin()) { return parameters.begin(); }
    auto end() const -> decltype(parameters.end()) { return parameters.end(); }
    bool operator==(IR::ParameterList const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "ParameterList"_cs; }
    static cstring static_type_name() { return "ParameterList"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ParameterList(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    ParameterList(Util::SourceInfo srcInfo, IR::IndexedVector<IR::Parameter> parameters)
        : Node(srcInfo), parameters(parameters) {
        validate();
    }
    ParameterList(IR::IndexedVector<IR::Parameter> parameters) : parameters(parameters) {
        validate();
    }
    ParameterList(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    ParameterList() { validate(); }
    IRNODE_SUBCLASS(ParameterList)
    DECLARE_TYPEINFO_WITH_TYPEID(ParameterList, NodeKind::ParameterList, Node, ISimpleNamespace);
};
}  // namespace P4::IR
namespace P4::IR {
/// Represents a type variable written by the user
class Type_Var : public Type_Declaration, public virtual ITypeVar {
 public:
    cstring getVarName() const override;
    int getDeclId() const override;
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    bool operator==(IR::Type_Var const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Var"_cs; }
    static cstring static_type_name() { return "Type_Var"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Var(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Var(Util::SourceInfo srcInfo, IR::ID name) : Type_Declaration(srcInfo, name) {
        validate();
    }
    Type_Var(IR::ID name) : Type_Declaration(name) { validate(); }
    IRNODE_SUBCLASS(Type_Var)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Var, NodeKind::Type_Var, Type_Declaration, ITypeVar);
};
}  // namespace P4::IR
namespace P4::IR {
/// Stands for the 'int' type: infinite precision constant
/// However, we represent it as a type variable, because we use
/// type unification to discover the correct type for the constants
/// in some contexts.
class Type_InfInt : public Type, public virtual ITypeVar {
 protected:
    void *operator new(size_t size) { return ::operator new(size); }
// FIXME: Remove this #ifdefine check once we switch to C++20
#if defined(__cpp_sized_deallocation) && __cpp_sized_deallocation >= 201309L
    void operator delete(void *p, size_t size) { return ::operator delete(p, size); }
#else
    void operator delete(void *p) { return ::operator delete(p); }
#endif
    long declid = nextId++;

 private:
    static long nextId;

 public:
    cstring getVarName() const override;
    int getDeclId() const override;
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    bool operator==(IR::Type_InfInt const &a) const override;
    static const IR::Type_InfInt *get();
    static const IR::Type_InfInt *get(Util::SourceInfo const &si);
    bool equiv(IR::Node const &a_) const override;
    IR::Type const *getP4Type() const override;
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    cstring node_type_name() const override { return "Type_InfInt"_cs; }
    static cstring static_type_name() { return "Type_InfInt"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_InfInt(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_InfInt(Util::SourceInfo srcInfo) : Type(srcInfo) { validate(); }
    Type_InfInt() { validate(); }
    IRNODE_SUBCLASS(Type_InfInt)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_InfInt, NodeKind::Type_InfInt, Type, ITypeVar);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Dontcare : public Type_Base {
 protected:
    void *operator new(size_t size) { return ::operator new(size); }
// FIXME: Remove this #ifdefine check once we switch to C++20
#if defined(__cpp_sized_deallocation) && __cpp_sized_deallocation >= 201309L
    void operator delete(void *p, size_t size) { return ::operator delete(p, size); }
#else
    void operator delete(void *p) { return ::operator delete(p); }
#endif
 public:
    cstring toString() const override;
    static const IR::Type_Dontcare *get();
    static const IR::Type_Dontcare *get(Util::SourceInfo const &si);
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_Dontcare const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Dontcare"_cs; }
    static cstring static_type_name() { return "Type_Dontcare"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Dontcare(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Dontcare(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_Dontcare() { validate(); }
    IRNODE_SUBCLASS(Type_Dontcare)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Dontcare, NodeKind::Type_Dontcare, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Void : public Type_Base {
 protected:
    void *operator new(size_t size) { return ::operator new(size); }
// FIXME: Remove this #ifdefine check once we switch to C++20
#if defined(__cpp_sized_deallocation) && __cpp_sized_deallocation >= 201309L
    void operator delete(void *p, size_t size) { return ::operator delete(p, size); }
#else
    void operator delete(void *p) { return ::operator delete(p); }
#endif
 public:
    cstring toString() const override;
    static const IR::Type_Void *get();
    static const IR::Type_Void *get(Util::SourceInfo const &si);
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_Void const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Void"_cs; }
    static cstring static_type_name() { return "Type_Void"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Void(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Void(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_Void() { validate(); }
    IRNODE_SUBCLASS(Type_Void)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Void, NodeKind::Type_Void, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_MatchKind : public Type_Base {
 protected:
    void *operator new(size_t size) { return ::operator new(size); }
// FIXME: Remove this #ifdefine check once we switch to C++20
#if defined(__cpp_sized_deallocation) && __cpp_sized_deallocation >= 201309L
    void operator delete(void *p, size_t size) { return ::operator delete(p, size); }
#else
    void operator delete(void *p) { return ::operator delete(p); }
#endif
 public:
    cstring toString() const override;
    static const IR::Type_MatchKind *get();
    static const IR::Type_MatchKind *get(Util::SourceInfo const &si);
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_MatchKind const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_MatchKind"_cs; }
    static cstring static_type_name() { return "Type_MatchKind"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_MatchKind(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_MatchKind(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_MatchKind() { validate(); }
    IRNODE_SUBCLASS(Type_MatchKind)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_MatchKind, NodeKind::Type_MatchKind, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class TypeParameters : public Node, public virtual ISimpleNamespace {
 public:
    IR::IndexedVector<IR::Type_Var> parameters;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    bool empty() const { return parameters.empty(); }
    size_t size() const { return parameters.size(); }
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    void push_back(const IR::Type_Var *tv) { parameters.push_back(tv); }
    void validate() const override;
    cstring toString() const override;
    bool operator==(IR::TypeParameters const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "TypeParameters"_cs; }
    static cstring static_type_name() { return "TypeParameters"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    TypeParameters(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    TypeParameters(Util::SourceInfo srcInfo, IR::IndexedVector<IR::Type_Var> parameters)
        : Node(srcInfo), parameters(parameters) {
        validate();
    }
    TypeParameters(IR::IndexedVector<IR::Type_Var> parameters) : parameters(parameters) {
        validate();
    }
    TypeParameters(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    TypeParameters() { validate(); }
    IRNODE_SUBCLASS(TypeParameters)
    DECLARE_TYPEINFO_WITH_TYPEID(TypeParameters, NodeKind::TypeParameters, Node, ISimpleNamespace);
};
}  // namespace P4::IR
namespace P4::IR {
class StructField : public Declaration, public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::Type *type = nullptr;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    bool operator==(IR::StructField const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "StructField"_cs; }
    static cstring static_type_name() { return "StructField"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    StructField(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    StructField(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::Type *type)
        : Declaration(srcInfo, name), annotations(annotations), type(type) {
        validate();
    }
    StructField(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::Type *type)
        : Declaration(name), annotations(annotations), type(type) {
        validate();
    }
    StructField(Util::SourceInfo srcInfo, IR::ID name, const IR::Type *type)
        : Declaration(srcInfo, name), type(type) {
        validate();
    }
    StructField(IR::ID name, const IR::Type *type) : Declaration(name), type(type) { validate(); }
    IRNODE_SUBCLASS(StructField)
    DECLARE_TYPEINFO_WITH_TYPEID(StructField, NodeKind::StructField, Declaration, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_StructLike : public Type_Declaration,
                        public virtual INestedNamespace,
                        public virtual ISimpleNamespace,
                        public virtual IAnnotated,
                        public virtual IMayBeGenericType {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::TypeParameters *typeParameters = new TypeParameters();
    IR::IndexedVector<IR::StructField> fields;
    const IR::TypeParameters *getTypeParameters() const override;
    std::vector<const IR::INamespace *> getNestedNamespaces() const override;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::StructField *getField(cstring name) const {
        return fields.getDeclaration<StructField>(name);
    }
    int getFieldIndex(cstring name) const {
        int index_pos = 0;
        for (auto f : fields) {
            if (f->name == name) return index_pos;
            index_pos++;
        }
        return -1;
    }
    /// This function returns start offset of the given field name in bits.
    /// If the given name is not a valid field name, -1 is returned.
    /// The given offset may not be correct if varbit field(s) present in between.
    /// Offset for all fields will be correct if:
    ///  - the type has only fixed width fields
    ///  - the type has fixed width fields with only one varbit field as a last member.
    int getFieldBitOffset(cstring name) const {
        int offset = 0;
        for (auto f : fields) {
            if (f->name == name) {
                return offset;
            }
            offset += f->type->width_bits();
        }
        return -1;
    }
    virtual bool variable() const override;
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    void validate() const override;
    void dbprint(std::ostream &out) const override;
    IRNODE_DECLARE_APPLY_OVERLOAD(Type_StructLike)
    bool operator==(IR::Type_StructLike const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_StructLike"_cs; }
    static cstring static_type_name() { return "Type_StructLike"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_StructLike(JSONLoader &json);
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Type_StructLike(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                    const IR::TypeParameters *typeParameters,
                    IR::IndexedVector<IR::StructField> fields)
        : Type_Declaration(srcInfo, name),
          annotations(annotations),
          typeParameters(typeParameters),
          fields(fields) {
        validate();
    }
    Type_StructLike(IR::ID name, IR::Vector<IR::Annotation> annotations,
                    const IR::TypeParameters *typeParameters,
                    IR::IndexedVector<IR::StructField> fields)
        : Type_Declaration(name),
          annotations(annotations),
          typeParameters(typeParameters),
          fields(fields) {
        validate();
    }
    Type_StructLike(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                    IR::IndexedVector<IR::StructField> fields)
        : Type_Declaration(srcInfo, name), typeParameters(typeParameters), fields(fields) {
        validate();
    }
    Type_StructLike(IR::ID name, const IR::TypeParameters *typeParameters,
                    IR::IndexedVector<IR::StructField> fields)
        : Type_Declaration(name), typeParameters(typeParameters), fields(fields) {
        validate();
    }
    Type_StructLike(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                    IR::IndexedVector<IR::StructField> fields)
        : Type_Declaration(srcInfo, name), annotations(annotations), fields(fields) {
        validate();
    }
    Type_StructLike(IR::ID name, IR::Vector<IR::Annotation> annotations,
                    IR::IndexedVector<IR::StructField> fields)
        : Type_Declaration(name), annotations(annotations), fields(fields) {
        validate();
    }
    Type_StructLike(Util::SourceInfo srcInfo, IR::ID name,
                    IR::IndexedVector<IR::StructField> fields)
        : Type_Declaration(srcInfo, name), fields(fields) {
        validate();
    }
    Type_StructLike(IR::ID name, IR::IndexedVector<IR::StructField> fields)
        : Type_Declaration(name), fields(fields) {
        validate();
    }
    Type_StructLike(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                    const IR::TypeParameters *typeParameters)
        : Type_Declaration(srcInfo, name),
          annotations(annotations),
          typeParameters(typeParameters) {
        validate();
    }
    Type_StructLike(IR::ID name, IR::Vector<IR::Annotation> annotations,
                    const IR::TypeParameters *typeParameters)
        : Type_Declaration(name), annotations(annotations), typeParameters(typeParameters) {
        validate();
    }
    Type_StructLike(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_Declaration(srcInfo, name), typeParameters(typeParameters) {
        validate();
    }
    Type_StructLike(IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_Declaration(name), typeParameters(typeParameters) {
        validate();
    }
    Type_StructLike(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(srcInfo, name), annotations(annotations) {
        validate();
    }
    Type_StructLike(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(name), annotations(annotations) {
        validate();
    }
    Type_StructLike(Util::SourceInfo srcInfo, IR::ID name) : Type_Declaration(srcInfo, name) {
        validate();
    }
    Type_StructLike(IR::ID name) : Type_Declaration(name) { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Type_StructLike)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_StructLike, NodeKind::Type_StructLike, Type_Declaration,
                                 INestedNamespace, ISimpleNamespace, IAnnotated, IMayBeGenericType);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Struct : public Type_StructLike {
 public:
    cstring toString() const override;
    bool operator==(IR::Type_Struct const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Struct"_cs; }
    static cstring static_type_name() { return "Type_Struct"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Struct(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_StructLike const &a) const override;
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Struct(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::TypeParameters *typeParameters, IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, annotations, typeParameters, fields) {
        validate();
    }
    Type_Struct(IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::TypeParameters *typeParameters, IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, annotations, typeParameters, fields) {
        validate();
    }
    Type_Struct(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, typeParameters, fields) {
        validate();
    }
    Type_Struct(IR::ID name, const IR::TypeParameters *typeParameters,
                IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, typeParameters, fields) {
        validate();
    }
    Type_Struct(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, annotations, fields) {
        validate();
    }
    Type_Struct(IR::ID name, IR::Vector<IR::Annotation> annotations,
                IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, annotations, fields) {
        validate();
    }
    Type_Struct(Util::SourceInfo srcInfo, IR::ID name, IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, fields) {
        validate();
    }
    Type_Struct(IR::ID name, IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, fields) {
        validate();
    }
    Type_Struct(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::TypeParameters *typeParameters)
        : Type_StructLike(srcInfo, name, annotations, typeParameters) {
        validate();
    }
    Type_Struct(IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::TypeParameters *typeParameters)
        : Type_StructLike(name, annotations, typeParameters) {
        validate();
    }
    Type_Struct(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_StructLike(srcInfo, name, typeParameters) {
        validate();
    }
    Type_Struct(IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_StructLike(name, typeParameters) {
        validate();
    }
    Type_Struct(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_StructLike(srcInfo, name, annotations) {
        validate();
    }
    Type_Struct(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_StructLike(name, annotations) {
        validate();
    }
    Type_Struct(Util::SourceInfo srcInfo, IR::ID name) : Type_StructLike(srcInfo, name) {
        validate();
    }
    Type_Struct(IR::ID name) : Type_StructLike(name) { validate(); }
    IRNODE_SUBCLASS(Type_Struct)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Struct, NodeKind::Type_Struct, Type_StructLike);
};
}  // namespace P4::IR
namespace P4::IR {
/// This is the type of a struct-valued expression whose
/// exact struct type is yet unknown; we only know the field names
/// and some information about their types.
class Type_UnknownStruct : public Type_StructLike {
 public:
    bool operator==(IR::Type_UnknownStruct const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_UnknownStruct"_cs; }
    static cstring static_type_name() { return "Type_UnknownStruct"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_UnknownStruct(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_StructLike const &a) const override;
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_UnknownStruct(Util::SourceInfo srcInfo, IR::ID name,
                       IR::Vector<IR::Annotation> annotations,
                       const IR::TypeParameters *typeParameters,
                       IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, annotations, typeParameters, fields) {
        validate();
    }
    Type_UnknownStruct(IR::ID name, IR::Vector<IR::Annotation> annotations,
                       const IR::TypeParameters *typeParameters,
                       IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, annotations, typeParameters, fields) {
        validate();
    }
    Type_UnknownStruct(Util::SourceInfo srcInfo, IR::ID name,
                       const IR::TypeParameters *typeParameters,
                       IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, typeParameters, fields) {
        validate();
    }
    Type_UnknownStruct(IR::ID name, const IR::TypeParameters *typeParameters,
                       IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, typeParameters, fields) {
        validate();
    }
    Type_UnknownStruct(Util::SourceInfo srcInfo, IR::ID name,
                       IR::Vector<IR::Annotation> annotations,
                       IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, annotations, fields) {
        validate();
    }
    Type_UnknownStruct(IR::ID name, IR::Vector<IR::Annotation> annotations,
                       IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, annotations, fields) {
        validate();
    }
    Type_UnknownStruct(Util::SourceInfo srcInfo, IR::ID name,
                       IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, fields) {
        validate();
    }
    Type_UnknownStruct(IR::ID name, IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, fields) {
        validate();
    }
    Type_UnknownStruct(Util::SourceInfo srcInfo, IR::ID name,
                       IR::Vector<IR::Annotation> annotations,
                       const IR::TypeParameters *typeParameters)
        : Type_StructLike(srcInfo, name, annotations, typeParameters) {
        validate();
    }
    Type_UnknownStruct(IR::ID name, IR::Vector<IR::Annotation> annotations,
                       const IR::TypeParameters *typeParameters)
        : Type_StructLike(name, annotations, typeParameters) {
        validate();
    }
    Type_UnknownStruct(Util::SourceInfo srcInfo, IR::ID name,
                       const IR::TypeParameters *typeParameters)
        : Type_StructLike(srcInfo, name, typeParameters) {
        validate();
    }
    Type_UnknownStruct(IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_StructLike(name, typeParameters) {
        validate();
    }
    Type_UnknownStruct(Util::SourceInfo srcInfo, IR::ID name,
                       IR::Vector<IR::Annotation> annotations)
        : Type_StructLike(srcInfo, name, annotations) {
        validate();
    }
    Type_UnknownStruct(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_StructLike(name, annotations) {
        validate();
    }
    Type_UnknownStruct(Util::SourceInfo srcInfo, IR::ID name) : Type_StructLike(srcInfo, name) {
        validate();
    }
    Type_UnknownStruct(IR::ID name) : Type_StructLike(name) { validate(); }
    IRNODE_SUBCLASS(Type_UnknownStruct)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_UnknownStruct, NodeKind::Type_UnknownStruct, Type_StructLike);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_HeaderUnion : public Type_StructLike {
 public:
    cstring toString() const override;

    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    /// start offset of any field in a union is 0
    int getFieldBitOffset(cstring name) const {
        for (auto f : fields) {
            if (f->name == name) {
                return 0;
            }
        }
        return -1;
    }
    bool operator==(IR::Type_HeaderUnion const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_HeaderUnion"_cs; }
    static cstring static_type_name() { return "Type_HeaderUnion"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_HeaderUnion(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_StructLike const &a) const override;
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_HeaderUnion(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                     const IR::TypeParameters *typeParameters,
                     IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, annotations, typeParameters, fields) {
        validate();
    }
    Type_HeaderUnion(IR::ID name, IR::Vector<IR::Annotation> annotations,
                     const IR::TypeParameters *typeParameters,
                     IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, annotations, typeParameters, fields) {
        validate();
    }
    Type_HeaderUnion(Util::SourceInfo srcInfo, IR::ID name,
                     const IR::TypeParameters *typeParameters,
                     IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, typeParameters, fields) {
        validate();
    }
    Type_HeaderUnion(IR::ID name, const IR::TypeParameters *typeParameters,
                     IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, typeParameters, fields) {
        validate();
    }
    Type_HeaderUnion(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                     IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, annotations, fields) {
        validate();
    }
    Type_HeaderUnion(IR::ID name, IR::Vector<IR::Annotation> annotations,
                     IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, annotations, fields) {
        validate();
    }
    Type_HeaderUnion(Util::SourceInfo srcInfo, IR::ID name,
                     IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, fields) {
        validate();
    }
    Type_HeaderUnion(IR::ID name, IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, fields) {
        validate();
    }
    Type_HeaderUnion(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                     const IR::TypeParameters *typeParameters)
        : Type_StructLike(srcInfo, name, annotations, typeParameters) {
        validate();
    }
    Type_HeaderUnion(IR::ID name, IR::Vector<IR::Annotation> annotations,
                     const IR::TypeParameters *typeParameters)
        : Type_StructLike(name, annotations, typeParameters) {
        validate();
    }
    Type_HeaderUnion(Util::SourceInfo srcInfo, IR::ID name,
                     const IR::TypeParameters *typeParameters)
        : Type_StructLike(srcInfo, name, typeParameters) {
        validate();
    }
    Type_HeaderUnion(IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_StructLike(name, typeParameters) {
        validate();
    }
    Type_HeaderUnion(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_StructLike(srcInfo, name, annotations) {
        validate();
    }
    Type_HeaderUnion(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_StructLike(name, annotations) {
        validate();
    }
    Type_HeaderUnion(Util::SourceInfo srcInfo, IR::ID name) : Type_StructLike(srcInfo, name) {
        validate();
    }
    Type_HeaderUnion(IR::ID name) : Type_StructLike(name) { validate(); }
    IRNODE_SUBCLASS(Type_HeaderUnion)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_HeaderUnion, NodeKind::Type_HeaderUnion, Type_StructLike);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Header : public Type_StructLike {
 public:
    static const cstring setValid;
    static const cstring setInvalid;
    static const cstring isValid;
    cstring toString() const override;
    bool operator==(IR::Type_Header const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Header"_cs; }
    static cstring static_type_name() { return "Type_Header"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Header(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_StructLike const &a) const override;
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Header(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::TypeParameters *typeParameters, IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, annotations, typeParameters, fields) {
        validate();
    }
    Type_Header(IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::TypeParameters *typeParameters, IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, annotations, typeParameters, fields) {
        validate();
    }
    Type_Header(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, typeParameters, fields) {
        validate();
    }
    Type_Header(IR::ID name, const IR::TypeParameters *typeParameters,
                IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, typeParameters, fields) {
        validate();
    }
    Type_Header(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, annotations, fields) {
        validate();
    }
    Type_Header(IR::ID name, IR::Vector<IR::Annotation> annotations,
                IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, annotations, fields) {
        validate();
    }
    Type_Header(Util::SourceInfo srcInfo, IR::ID name, IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(srcInfo, name, fields) {
        validate();
    }
    Type_Header(IR::ID name, IR::IndexedVector<IR::StructField> fields)
        : Type_StructLike(name, fields) {
        validate();
    }
    Type_Header(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::TypeParameters *typeParameters)
        : Type_StructLike(srcInfo, name, annotations, typeParameters) {
        validate();
    }
    Type_Header(IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::TypeParameters *typeParameters)
        : Type_StructLike(name, annotations, typeParameters) {
        validate();
    }
    Type_Header(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_StructLike(srcInfo, name, typeParameters) {
        validate();
    }
    Type_Header(IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_StructLike(name, typeParameters) {
        validate();
    }
    Type_Header(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_StructLike(srcInfo, name, annotations) {
        validate();
    }
    Type_Header(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_StructLike(name, annotations) {
        validate();
    }
    Type_Header(Util::SourceInfo srcInfo, IR::ID name) : Type_StructLike(srcInfo, name) {
        validate();
    }
    Type_Header(IR::ID name) : Type_StructLike(name) { validate(); }
    IRNODE_SUBCLASS(Type_Header)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Header, NodeKind::Type_Header, Type_StructLike);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Set : public Type {
 public:
    const IR::Type *elementType = nullptr;
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    IR::Type const *getP4Type() const override;
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    bool operator==(IR::Type_Set const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_Set"_cs; }
    static cstring static_type_name() { return "Type_Set"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Set(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Set(Util::SourceInfo srcInfo, const IR::Type *elementType)
        : Type(srcInfo), elementType(elementType) {
        validate();
    }
    Type_Set(const IR::Type *elementType) : elementType(elementType) { validate(); }
    IRNODE_SUBCLASS(Type_Set)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Set, NodeKind::Type_Set, Type);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Indexed : public virtual INode {
 public:
    virtual size_t getSize() const = 0;
    virtual const IR::Type *at(size_t index) const = 0;
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Indexed, NodeKind::Type_Indexed, INode);
};
}  // namespace P4::IR
namespace P4::IR {
/// Base class for Type_List, and Type_Tuple
class Type_BaseList : public Type, public virtual Type_Indexed {
 public:
    IR::Vector<IR::Type> components;
    void validate() const override;
    size_t getSize() const override;
    const IR::Type *at(size_t index) const override;
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    cstring asString(char const *name) const;
    cstring toString() const override;
    bool operator==(IR::Type_BaseList const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_BaseList"_cs; }
    static cstring static_type_name() { return "Type_BaseList"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_BaseList(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Type_BaseList(Util::SourceInfo srcInfo, IR::Vector<IR::Type> components)
        : Type(srcInfo), components(components) {
        validate();
    }
    Type_BaseList(IR::Vector<IR::Type> components) : components(components) { validate(); }
    Type_BaseList(Util::SourceInfo srcInfo) : Type(srcInfo) { validate(); }
    Type_BaseList() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Type_BaseList)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_BaseList, NodeKind::Type_BaseList, Type, Type_Indexed);
};
}  // namespace P4::IR
namespace P4::IR {
/// The type of an expressionList; can be unified with both Type_Tuple and Type_Struct
class Type_List : public Type_BaseList {
 public:
    IR::Type const *getP4Type() const override;

    cstring toString() const override;
    bool operator==(IR::Type_List const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_List"_cs; }
    static cstring static_type_name() { return "Type_List"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_List(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_BaseList const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_List(Util::SourceInfo srcInfo, IR::Vector<IR::Type> components)
        : Type_BaseList(srcInfo, components) {
        validate();
    }
    Type_List(IR::Vector<IR::Type> components) : Type_BaseList(components) { validate(); }
    Type_List(Util::SourceInfo srcInfo) : Type_BaseList(srcInfo) { validate(); }
    Type_List() { validate(); }
    IRNODE_SUBCLASS(Type_List)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_List, NodeKind::Type_List, Type_BaseList);
};
}  // namespace P4::IR
namespace P4::IR {
/// The type of a tuple.
class Type_Tuple : public Type_BaseList {
 public:
    IR::Type const *getP4Type() const override;
    cstring toString() const override;
    bool operator==(IR::Type_Tuple const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Tuple"_cs; }
    static cstring static_type_name() { return "Type_Tuple"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Tuple(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_BaseList const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Tuple(Util::SourceInfo srcInfo, IR::Vector<IR::Type> components)
        : Type_BaseList(srcInfo, components) {
        validate();
    }
    Type_Tuple(IR::Vector<IR::Type> components) : Type_BaseList(components) { validate(); }
    Type_Tuple(Util::SourceInfo srcInfo) : Type_BaseList(srcInfo) { validate(); }
    Type_Tuple() { validate(); }
    IRNODE_SUBCLASS(Type_Tuple)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Tuple, NodeKind::Type_Tuple, Type_BaseList);
};
}  // namespace P4::IR
namespace P4::IR {
/// The type of a P4ListExpression.
class Type_P4List : public Type {
 public:
    const IR::Type *elementType = nullptr;
    IR::Type const *getP4Type() const override;
    cstring toString() const override;
    bool operator==(IR::Type_P4List const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_P4List"_cs; }
    static cstring static_type_name() { return "Type_P4List"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_P4List(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_P4List(Util::SourceInfo srcInfo, const IR::Type *elementType)
        : Type(srcInfo), elementType(elementType) {
        validate();
    }
    Type_P4List(const IR::Type *elementType) : elementType(elementType) { validate(); }
    IRNODE_SUBCLASS(Type_P4List)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_P4List, NodeKind::Type_P4List, Type);
};
}  // namespace P4::IR
namespace P4::IR {
/// The type of an architectural block.
/// Abstract base for Type_Control, Type_Parser and Type_Package
class Type_ArchBlock : public Type_Declaration,
                       public virtual IMayBeGenericType,
                       public virtual IAnnotated,
                       public virtual ISimpleNamespace {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::TypeParameters *typeParameters = new TypeParameters;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    const IR::TypeParameters *getTypeParameters() const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    bool operator==(IR::Type_ArchBlock const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_ArchBlock"_cs; }
    static cstring static_type_name() { return "Type_ArchBlock"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_ArchBlock(JSONLoader &json);
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Type_ArchBlock(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                   const IR::TypeParameters *typeParameters)
        : Type_Declaration(srcInfo, name),
          annotations(annotations),
          typeParameters(typeParameters) {
        validate();
    }
    Type_ArchBlock(IR::ID name, IR::Vector<IR::Annotation> annotations,
                   const IR::TypeParameters *typeParameters)
        : Type_Declaration(name), annotations(annotations), typeParameters(typeParameters) {
        validate();
    }
    Type_ArchBlock(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_Declaration(srcInfo, name), typeParameters(typeParameters) {
        validate();
    }
    Type_ArchBlock(IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_Declaration(name), typeParameters(typeParameters) {
        validate();
    }
    Type_ArchBlock(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(srcInfo, name), annotations(annotations) {
        validate();
    }
    Type_ArchBlock(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(name), annotations(annotations) {
        validate();
    }
    Type_ArchBlock(Util::SourceInfo srcInfo, IR::ID name) : Type_Declaration(srcInfo, name) {
        validate();
    }
    Type_ArchBlock(IR::ID name) : Type_Declaration(name) { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Type_ArchBlock)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_ArchBlock, NodeKind::Type_ArchBlock, Type_Declaration,
                                 IMayBeGenericType, IAnnotated, ISimpleNamespace);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Package : public Type_ArchBlock,
                     public virtual IContainer,
                     public virtual ISimpleNamespace {
 public:
    const IR::Type *getType() const override;
    const IR::ParameterList *constructorParams = nullptr;
    const IR::Type_Method *getConstructorMethodType() const override;
    const IR::ParameterList *getConstructorParameters() const override;
    cstring toString() const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    bool operator==(IR::Type_Package const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_Package"_cs; }
    static cstring static_type_name() { return "Type_Package"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Package(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_ArchBlock const &a) const override;
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Package(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                 const IR::TypeParameters *typeParameters,
                 const IR::ParameterList *constructorParams)
        : Type_ArchBlock(srcInfo, name, annotations, typeParameters),
          constructorParams(constructorParams) {
        validate();
    }
    Type_Package(IR::ID name, IR::Vector<IR::Annotation> annotations,
                 const IR::TypeParameters *typeParameters,
                 const IR::ParameterList *constructorParams)
        : Type_ArchBlock(name, annotations, typeParameters), constructorParams(constructorParams) {
        validate();
    }
    Type_Package(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                 const IR::ParameterList *constructorParams)
        : Type_ArchBlock(srcInfo, name, typeParameters), constructorParams(constructorParams) {
        validate();
    }
    Type_Package(IR::ID name, const IR::TypeParameters *typeParameters,
                 const IR::ParameterList *constructorParams)
        : Type_ArchBlock(name, typeParameters), constructorParams(constructorParams) {
        validate();
    }
    Type_Package(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                 const IR::ParameterList *constructorParams)
        : Type_ArchBlock(srcInfo, name, annotations), constructorParams(constructorParams) {
        validate();
    }
    Type_Package(IR::ID name, IR::Vector<IR::Annotation> annotations,
                 const IR::ParameterList *constructorParams)
        : Type_ArchBlock(name, annotations), constructorParams(constructorParams) {
        validate();
    }
    Type_Package(Util::SourceInfo srcInfo, IR::ID name, const IR::ParameterList *constructorParams)
        : Type_ArchBlock(srcInfo, name), constructorParams(constructorParams) {
        validate();
    }
    Type_Package(IR::ID name, const IR::ParameterList *constructorParams)
        : Type_ArchBlock(name), constructorParams(constructorParams) {
        validate();
    }
    IRNODE_SUBCLASS(Type_Package)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Package, NodeKind::Type_Package, Type_ArchBlock, IContainer,
                                 ISimpleNamespace);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Parser : public Type_ArchBlock, public virtual IApply {
 public:
    const IR::ParameterList *applyParams = nullptr;
    const IR::Type_Method *getApplyMethodType() const override;
    const IR::ParameterList *getApplyParameters() const override;
    cstring toString() const override;
    bool operator==(IR::Type_Parser const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_Parser"_cs; }
    static cstring static_type_name() { return "Type_Parser"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Parser(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_ArchBlock const &a) const override;
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Parser(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::TypeParameters *typeParameters, const IR::ParameterList *applyParams)
        : Type_ArchBlock(srcInfo, name, annotations, typeParameters), applyParams(applyParams) {
        validate();
    }
    Type_Parser(IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::TypeParameters *typeParameters, const IR::ParameterList *applyParams)
        : Type_ArchBlock(name, annotations, typeParameters), applyParams(applyParams) {
        validate();
    }
    Type_Parser(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                const IR::ParameterList *applyParams)
        : Type_ArchBlock(srcInfo, name, typeParameters), applyParams(applyParams) {
        validate();
    }
    Type_Parser(IR::ID name, const IR::TypeParameters *typeParameters,
                const IR::ParameterList *applyParams)
        : Type_ArchBlock(name, typeParameters), applyParams(applyParams) {
        validate();
    }
    Type_Parser(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::ParameterList *applyParams)
        : Type_ArchBlock(srcInfo, name, annotations), applyParams(applyParams) {
        validate();
    }
    Type_Parser(IR::ID name, IR::Vector<IR::Annotation> annotations,
                const IR::ParameterList *applyParams)
        : Type_ArchBlock(name, annotations), applyParams(applyParams) {
        validate();
    }
    Type_Parser(Util::SourceInfo srcInfo, IR::ID name, const IR::ParameterList *applyParams)
        : Type_ArchBlock(srcInfo, name), applyParams(applyParams) {
        validate();
    }
    Type_Parser(IR::ID name, const IR::ParameterList *applyParams)
        : Type_ArchBlock(name), applyParams(applyParams) {
        validate();
    }
    IRNODE_SUBCLASS(Type_Parser)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Parser, NodeKind::Type_Parser, Type_ArchBlock, IApply);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Control : public Type_ArchBlock, public virtual IApply {
 public:
    const IR::ParameterList *applyParams = nullptr;
    const IR::Type_Method *getApplyMethodType() const override;
    const IR::ParameterList *getApplyParameters() const override;
    cstring toString() const override;
    bool operator==(IR::Type_Control const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_Control"_cs; }
    static cstring static_type_name() { return "Type_Control"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Control(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_ArchBlock const &a) const override;
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Control(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                 const IR::TypeParameters *typeParameters, const IR::ParameterList *applyParams)
        : Type_ArchBlock(srcInfo, name, annotations, typeParameters), applyParams(applyParams) {
        validate();
    }
    Type_Control(IR::ID name, IR::Vector<IR::Annotation> annotations,
                 const IR::TypeParameters *typeParameters, const IR::ParameterList *applyParams)
        : Type_ArchBlock(name, annotations, typeParameters), applyParams(applyParams) {
        validate();
    }
    Type_Control(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                 const IR::ParameterList *applyParams)
        : Type_ArchBlock(srcInfo, name, typeParameters), applyParams(applyParams) {
        validate();
    }
    Type_Control(IR::ID name, const IR::TypeParameters *typeParameters,
                 const IR::ParameterList *applyParams)
        : Type_ArchBlock(name, typeParameters), applyParams(applyParams) {
        validate();
    }
    Type_Control(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                 const IR::ParameterList *applyParams)
        : Type_ArchBlock(srcInfo, name, annotations), applyParams(applyParams) {
        validate();
    }
    Type_Control(IR::ID name, IR::Vector<IR::Annotation> annotations,
                 const IR::ParameterList *applyParams)
        : Type_ArchBlock(name, annotations), applyParams(applyParams) {
        validate();
    }
    Type_Control(Util::SourceInfo srcInfo, IR::ID name, const IR::ParameterList *applyParams)
        : Type_ArchBlock(srcInfo, name), applyParams(applyParams) {
        validate();
    }
    Type_Control(IR::ID name, const IR::ParameterList *applyParams)
        : Type_ArchBlock(name), applyParams(applyParams) {
        validate();
    }
    IRNODE_SUBCLASS(Type_Control)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Control, NodeKind::Type_Control, Type_ArchBlock, IApply);
};
}  // namespace P4::IR
namespace P4::IR {
/// A type referred by name
class Type_Name : public Type {
 public:
    const IR::Path *path = nullptr;
    Type_Name(IR::ID id);
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    IR::Type const *getP4Type() const override;
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    bool operator==(IR::Type_Name const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_Name"_cs; }
    static cstring static_type_name() { return "Type_Name"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Name(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Name(Util::SourceInfo srcInfo, const IR::Path *path) : Type(srcInfo), path(path) {
        validate();
    }
    Type_Name(const IR::Path *path) : path(path) { validate(); }
    IRNODE_SUBCLASS(Type_Name)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Name, NodeKind::Type_Name, Type);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Array : public virtual Type_Indexed, public Type {
 public:
    const IR::Type *elementType = nullptr;
    const IR::Expression *size = nullptr;
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    bool sizeKnown() const;
    size_t getSize() const override;
    const IR::Type *at(size_t index) const override;
    static const cstring next;
    static const cstring last;
    static const cstring arraySize;
    static const cstring lastIndex;
    static const cstring push_front;
    static const cstring pop_front;
    IR::Type const *getP4Type() const override;
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    bool operator==(IR::Type_Array const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_Array"_cs; }
    static cstring static_type_name() { return "Type_Array"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Array(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Array(Util::SourceInfo srcInfo, const IR::Type *elementType, const IR::Expression *size)
        : Type(srcInfo), elementType(elementType), size(size) {
        validate();
    }
    Type_Array(const IR::Type *elementType, const IR::Expression *size)
        : elementType(elementType), size(size) {
        validate();
    }
    IRNODE_SUBCLASS(Type_Array)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Array, NodeKind::Type_Array, Type_Indexed, Type);
};
}  // namespace P4::IR
namespace P4::IR {
/** Given a declaration
   extern E<T> { ... }
   Type_Specialized represents a type such
   E<bit<32>>
   baseType is Type_Name E, arguments is a vector containing Type_Bits(32) */
class Type_Specialized : public Type {
 public:
    const IR::Type_Name *baseType = nullptr;
    const IR::Vector<IR::Type> *arguments = nullptr;
    void validate() const override;
    IR::Type const *getP4Type() const override;
    cstring toString() const override;
    Type_Specialized(cstring bt, std::initializer_list<const IR::Type *> args);
    bool operator==(IR::Type_Specialized const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_Specialized"_cs; }
    static cstring static_type_name() { return "Type_Specialized"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Specialized(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Specialized(Util::SourceInfo srcInfo, const IR::Type_Name *baseType,
                     const IR::Vector<IR::Type> *arguments)
        : Type(srcInfo), baseType(baseType), arguments(arguments) {
        validate();
    }
    Type_Specialized(const IR::Type_Name *baseType, const IR::Vector<IR::Type> *arguments)
        : baseType(baseType), arguments(arguments) {
        validate();
    }
    IRNODE_SUBCLASS(Type_Specialized)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Specialized, NodeKind::Type_Specialized, Type);
};
}  // namespace P4::IR
namespace P4::IR {
/** Canonical representation of a Type_Specialized;
   only used by the type-checker, never in the IR tree. */
class Type_SpecializedCanonical : public Type {
 public:
    const IR::Type *baseType = nullptr;
    /// canonical baseType; always IMayBeGenericType
    const IR::Vector<IR::Type> *arguments = nullptr;
    /// canonical type arguments
    /// 'substituted' is baseType with all type
    /// variables substituted with the arguments.
    const IR::Type *substituted = nullptr;

    void validate() const override;
    IR::Type const *getP4Type() const override;
    cstring toString() const override;
    bool operator==(IR::Type_SpecializedCanonical const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_SpecializedCanonical"_cs; }
    static cstring static_type_name() { return "Type_SpecializedCanonical"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_SpecializedCanonical(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_SpecializedCanonical(Util::SourceInfo srcInfo, const IR::Type *baseType,
                              const IR::Vector<IR::Type> *arguments, const IR::Type *substituted)
        : Type(srcInfo), baseType(baseType), arguments(arguments), substituted(substituted) {
        validate();
    }
    Type_SpecializedCanonical(const IR::Type *baseType, const IR::Vector<IR::Type> *arguments,
                              const IR::Type *substituted)
        : baseType(baseType), arguments(arguments), substituted(substituted) {
        validate();
    }
    IRNODE_SUBCLASS(Type_SpecializedCanonical)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_SpecializedCanonical, NodeKind::Type_SpecializedCanonical,
                                 Type);
};
}  // namespace P4::IR
namespace P4::IR {
/// A declaration that consists of just an identifier, e.g., an enum member
class Declaration_ID : public Declaration, public virtual CompileTimeValue {
 public:
    bool operator==(IR::Declaration_ID const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Declaration_ID"_cs; }
    static cstring static_type_name() { return "Declaration_ID"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Declaration_ID(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Declaration_ID(Util::SourceInfo srcInfo, IR::ID name) : Declaration(srcInfo, name) {
        validate();
    }
    Declaration_ID(IR::ID name) : Declaration(name) { validate(); }
    IRNODE_SUBCLASS(Declaration_ID)
    DECLARE_TYPEINFO_WITH_TYPEID(Declaration_ID, NodeKind::Declaration_ID, Declaration,
                                 CompileTimeValue);
};
}  // namespace P4::IR
namespace P4::IR {
/// The type of a string literal
class Type_String : public Type_Base {
 public:
 protected:
    void *operator new(size_t size) { return ::operator new(size); }
// FIXME: Remove this #ifdefine check once we switch to C++20
#if defined(__cpp_sized_deallocation) && __cpp_sized_deallocation >= 201309L
    void operator delete(void *p, size_t size) { return ::operator delete(p, size); }
#else
    void operator delete(void *p) { return ::operator delete(p); }
#endif
 public:
    static const IR::Type_String *get();
    static const IR::Type_String *get(Util::SourceInfo const &si);
    cstring toString() const override;
    bool operator==(IR::Type_String const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_String"_cs; }
    static cstring static_type_name() { return "Type_String"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_String(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_String(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_String() { validate(); }
    IRNODE_SUBCLASS(Type_String)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_String, NodeKind::Type_String, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Enum : public Type_Declaration,
                  public virtual ISimpleNamespace,
                  public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    IR::IndexedVector<IR::Declaration_ID> members;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    void validate() const override;
    bool operator==(IR::Type_Enum const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_Enum"_cs; }
    static cstring static_type_name() { return "Type_Enum"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Enum(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Enum(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
              IR::IndexedVector<IR::Declaration_ID> members)
        : Type_Declaration(srcInfo, name), annotations(annotations), members(members) {
        validate();
    }
    Type_Enum(IR::ID name, IR::Vector<IR::Annotation> annotations,
              IR::IndexedVector<IR::Declaration_ID> members)
        : Type_Declaration(name), annotations(annotations), members(members) {
        validate();
    }
    Type_Enum(Util::SourceInfo srcInfo, IR::ID name, IR::IndexedVector<IR::Declaration_ID> members)
        : Type_Declaration(srcInfo, name), members(members) {
        validate();
    }
    Type_Enum(IR::ID name, IR::IndexedVector<IR::Declaration_ID> members)
        : Type_Declaration(name), members(members) {
        validate();
    }
    IRNODE_SUBCLASS(Type_Enum)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Enum, NodeKind::Type_Enum, Type_Declaration, ISimpleNamespace,
                                 IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
/// A member of a serializable enum with a backing value
class SerEnumMember : public Declaration, public virtual CompileTimeValue {
 public:
    const IR::Expression *value = nullptr;
    void validate() const override;
    bool operator==(IR::SerEnumMember const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "SerEnumMember"_cs; }
    static cstring static_type_name() { return "SerEnumMember"_cs; }
    void toJSON(JSONGenerator &json) const override;
    SerEnumMember(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    SerEnumMember(Util::SourceInfo srcInfo, IR::ID name, const IR::Expression *value)
        : Declaration(srcInfo, name), value(value) {
        validate();
    }
    SerEnumMember(IR::ID name, const IR::Expression *value) : Declaration(name), value(value) {
        validate();
    }
    IRNODE_SUBCLASS(SerEnumMember)
    DECLARE_TYPEINFO_WITH_TYPEID(SerEnumMember, NodeKind::SerEnumMember, Declaration,
                                 CompileTimeValue);
};
}  // namespace P4::IR
namespace P4::IR {
/** A serializable enumeration with a backing type */
class Type_SerEnum : public Type_Declaration,
                     public virtual ISimpleNamespace,
                     public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::Type *type = nullptr;
    IR::IndexedVector<IR::SerEnumMember> members;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    void validate() const override;
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    bool operator==(IR::Type_SerEnum const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_SerEnum"_cs; }
    static cstring static_type_name() { return "Type_SerEnum"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_SerEnum(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_SerEnum(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                 const IR::Type *type, IR::IndexedVector<IR::SerEnumMember> members)
        : Type_Declaration(srcInfo, name), annotations(annotations), type(type), members(members) {
        validate();
    }
    Type_SerEnum(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::Type *type,
                 IR::IndexedVector<IR::SerEnumMember> members)
        : Type_Declaration(name), annotations(annotations), type(type), members(members) {
        validate();
    }
    Type_SerEnum(Util::SourceInfo srcInfo, IR::ID name, const IR::Type *type,
                 IR::IndexedVector<IR::SerEnumMember> members)
        : Type_Declaration(srcInfo, name), type(type), members(members) {
        validate();
    }
    Type_SerEnum(IR::ID name, const IR::Type *type, IR::IndexedVector<IR::SerEnumMember> members)
        : Type_Declaration(name), type(type), members(members) {
        validate();
    }
    IRNODE_SUBCLASS(Type_SerEnum)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_SerEnum, NodeKind::Type_SerEnum, Type_Declaration,
                                 ISimpleNamespace, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Table : public Type, public virtual IApply {
 public:
    const IR::P4Table *table = nullptr;
    const IR::Type_Method *getApplyMethodType() const override;
    const IR::ParameterList *getApplyParameters() const override;
    /// names for the fields of the struct returned
    /// by applying a table
    static const IR::ID hit;
    static const IR::ID miss;
    static const IR::ID action_run;
    IR::Type const *getP4Type() const override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_Table const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_Table"_cs; }
    static cstring static_type_name() { return "Type_Table"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Table(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Table(Util::SourceInfo srcInfo, const IR::P4Table *table) : Type(srcInfo), table(table) {
        validate();
    }
    Type_Table(const IR::P4Table *table) : table(table) { validate(); }
    IRNODE_SUBCLASS(Type_Table)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Table, NodeKind::Type_Table, Type, IApply);
};
}  // namespace P4::IR
namespace P4::IR {
/// A special enum-like anonymous type that
/// represents all actions in a table's action list.
/// Used for 'switch' statements.
class Type_ActionEnum : public Type {
 public:
    const IR::ActionList *actionList = nullptr;
    bool contains(cstring name) const;
    IR::Type const *getP4Type() const override;
    bool operator==(IR::Type_ActionEnum const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_ActionEnum"_cs; }
    static cstring static_type_name() { return "Type_ActionEnum"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_ActionEnum(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_ActionEnum(Util::SourceInfo srcInfo, const IR::ActionList *actionList)
        : Type(srcInfo), actionList(actionList) {
        validate();
    }
    Type_ActionEnum(const IR::ActionList *actionList) : actionList(actionList) { validate(); }
    IRNODE_SUBCLASS(Type_ActionEnum)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_ActionEnum, NodeKind::Type_ActionEnum, Type);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_MethodBase : public Type,
                        public virtual IMayBeGenericType,
                        public virtual ISimpleNamespace {
 public:
    const IR::TypeParameters *typeParameters = new TypeParameters();
    const IR::Type *returnType = nullptr;

    const IR::ParameterList *parameters = nullptr;
    size_t maxParameterCount() const { return parameters->size(); }
    size_t minParameterCount() const {
        size_t rv = 0;
        for (auto p : *parameters)
            if (!p->isOptional()) ++rv;
        return rv;
    }
    const IR::TypeParameters *getTypeParameters() const override;
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    IR::Type const *getP4Type() const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    bool operator==(IR::Type_MethodBase const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_MethodBase"_cs; }
    static cstring static_type_name() { return "Type_MethodBase"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_MethodBase(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Type_MethodBase(Util::SourceInfo srcInfo, const IR::TypeParameters *typeParameters,
                    const IR::Type *returnType, const IR::ParameterList *parameters)
        : Type(srcInfo),
          typeParameters(typeParameters),
          returnType(returnType),
          parameters(parameters) {
        validate();
    }
    Type_MethodBase(const IR::TypeParameters *typeParameters, const IR::Type *returnType,
                    const IR::ParameterList *parameters)
        : typeParameters(typeParameters), returnType(returnType), parameters(parameters) {
        validate();
    }
    Type_MethodBase(Util::SourceInfo srcInfo, const IR::Type *returnType,
                    const IR::ParameterList *parameters)
        : Type(srcInfo), returnType(returnType), parameters(parameters) {
        validate();
    }
    Type_MethodBase(const IR::Type *returnType, const IR::ParameterList *parameters)
        : returnType(returnType), parameters(parameters) {
        validate();
    }
    Type_MethodBase(Util::SourceInfo srcInfo, const IR::TypeParameters *typeParameters,
                    const IR::ParameterList *parameters)
        : Type(srcInfo), typeParameters(typeParameters), parameters(parameters) {
        validate();
    }
    Type_MethodBase(const IR::TypeParameters *typeParameters, const IR::ParameterList *parameters)
        : typeParameters(typeParameters), parameters(parameters) {
        validate();
    }
    Type_MethodBase(Util::SourceInfo srcInfo, const IR::ParameterList *parameters)
        : Type(srcInfo), parameters(parameters) {
        validate();
    }
    Type_MethodBase(const IR::ParameterList *parameters) : parameters(parameters) { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Type_MethodBase)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_MethodBase, NodeKind::Type_MethodBase, Type,
                                 IMayBeGenericType, ISimpleNamespace);
};
}  // namespace P4::IR
namespace P4::IR {
/// Type for a method or function.
class Type_Method : public Type_MethodBase {
 public:
    cstring name;
    cstring toString() const override;
    bool operator==(IR::Type_Method const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Method"_cs; }
    static cstring static_type_name() { return "Type_Method"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Method(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_MethodBase const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Method(Util::SourceInfo srcInfo, const IR::TypeParameters *typeParameters,
                const IR::Type *returnType, const IR::ParameterList *parameters, cstring name)
        : Type_MethodBase(srcInfo, typeParameters, returnType, parameters), name(name) {
        validate();
    }
    Type_Method(const IR::TypeParameters *typeParameters, const IR::Type *returnType,
                const IR::ParameterList *parameters, cstring name)
        : Type_MethodBase(typeParameters, returnType, parameters), name(name) {
        validate();
    }
    Type_Method(Util::SourceInfo srcInfo, const IR::Type *returnType,
                const IR::ParameterList *parameters, cstring name)
        : Type_MethodBase(srcInfo, returnType, parameters), name(name) {
        validate();
    }
    Type_Method(const IR::Type *returnType, const IR::ParameterList *parameters, cstring name)
        : Type_MethodBase(returnType, parameters), name(name) {
        validate();
    }
    Type_Method(Util::SourceInfo srcInfo, const IR::TypeParameters *typeParameters,
                const IR::ParameterList *parameters, cstring name)
        : Type_MethodBase(srcInfo, typeParameters, parameters), name(name) {
        validate();
    }
    Type_Method(const IR::TypeParameters *typeParameters, const IR::ParameterList *parameters,
                cstring name)
        : Type_MethodBase(typeParameters, parameters), name(name) {
        validate();
    }
    Type_Method(Util::SourceInfo srcInfo, const IR::ParameterList *parameters, cstring name)
        : Type_MethodBase(srcInfo, parameters), name(name) {
        validate();
    }
    Type_Method(const IR::ParameterList *parameters, cstring name)
        : Type_MethodBase(parameters), name(name) {
        validate();
    }
    IRNODE_SUBCLASS(Type_Method)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Method, NodeKind::Type_Method, Type_MethodBase);
};
}  // namespace P4::IR
namespace P4::IR {
/// Describes an argument of a MethodCall
/// Never used in the program IR; only used by typechecker.
class ArgumentInfo : public Node {
 public:
    bool leftValue;
    bool compileTimeConstant;
    const IR::Type *type = nullptr;
    const IR::Argument *argument = nullptr;
    cstring toString() const override;
    bool operator==(IR::ArgumentInfo const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "ArgumentInfo"_cs; }
    static cstring static_type_name() { return "ArgumentInfo"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ArgumentInfo(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    ArgumentInfo(Util::SourceInfo srcInfo, bool leftValue, bool compileTimeConstant,
                 const IR::Type *type, const IR::Argument *argument)
        : Node(srcInfo),
          leftValue(leftValue),
          compileTimeConstant(compileTimeConstant),
          type(type),
          argument(argument) {
        validate();
    }
    ArgumentInfo(bool leftValue, bool compileTimeConstant, const IR::Type *type,
                 const IR::Argument *argument)
        : leftValue(leftValue),
          compileTimeConstant(compileTimeConstant),
          type(type),
          argument(argument) {
        validate();
    }
    IRNODE_SUBCLASS(ArgumentInfo)
    DECLARE_TYPEINFO_WITH_TYPEID(ArgumentInfo, NodeKind::ArgumentInfo, Node);
};
}  // namespace P4::IR
namespace P4::IR {
/// Used to represent the type of a MethodCallExpression
/// for unification.
/// Never appears in the program IR; only used by the typechecker.
class Type_MethodCall : public Type {
 public:
    const IR::Vector<IR::Type> *typeArguments = nullptr;
    const IR::Type_Var *returnType = nullptr;
    const IR::Vector<IR::ArgumentInfo> *arguments = nullptr;
    void validate() const override;
    IR::Type const *getP4Type() const override;
    cstring toString() const override;
    bool operator==(IR::Type_MethodCall const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_MethodCall"_cs; }
    static cstring static_type_name() { return "Type_MethodCall"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_MethodCall(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_MethodCall(Util::SourceInfo srcInfo, const IR::Vector<IR::Type> *typeArguments,
                    const IR::Type_Var *returnType, const IR::Vector<IR::ArgumentInfo> *arguments)
        : Type(srcInfo),
          typeArguments(typeArguments),
          returnType(returnType),
          arguments(arguments) {
        validate();
    }
    Type_MethodCall(const IR::Vector<IR::Type> *typeArguments, const IR::Type_Var *returnType,
                    const IR::Vector<IR::ArgumentInfo> *arguments)
        : typeArguments(typeArguments), returnType(returnType), arguments(arguments) {
        validate();
    }
    IRNODE_SUBCLASS(Type_MethodCall)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_MethodCall, NodeKind::Type_MethodCall, Type);
};
}  // namespace P4::IR
namespace P4::IR {
/// Actions look a lot like methods in many respects.
/// However, invoking an action returns another action
/// Having different IR nodes allows performing different transforms in visitors
class Type_Action : public Type_MethodBase {
 public:
    bool operator==(IR::Type_Action const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Action"_cs; }
    static cstring static_type_name() { return "Type_Action"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Action(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_MethodBase const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Action(Util::SourceInfo srcInfo, const IR::TypeParameters *typeParameters,
                const IR::Type *returnType, const IR::ParameterList *parameters)
        : Type_MethodBase(srcInfo, typeParameters, returnType, parameters) {
        validate();
    }
    Type_Action(const IR::TypeParameters *typeParameters, const IR::Type *returnType,
                const IR::ParameterList *parameters)
        : Type_MethodBase(typeParameters, returnType, parameters) {
        validate();
    }
    Type_Action(Util::SourceInfo srcInfo, const IR::Type *returnType,
                const IR::ParameterList *parameters)
        : Type_MethodBase(srcInfo, returnType, parameters) {
        validate();
    }
    Type_Action(const IR::Type *returnType, const IR::ParameterList *parameters)
        : Type_MethodBase(returnType, parameters) {
        validate();
    }
    Type_Action(Util::SourceInfo srcInfo, const IR::TypeParameters *typeParameters,
                const IR::ParameterList *parameters)
        : Type_MethodBase(srcInfo, typeParameters, parameters) {
        validate();
    }
    Type_Action(const IR::TypeParameters *typeParameters, const IR::ParameterList *parameters)
        : Type_MethodBase(typeParameters, parameters) {
        validate();
    }
    Type_Action(Util::SourceInfo srcInfo, const IR::ParameterList *parameters)
        : Type_MethodBase(srcInfo, parameters) {
        validate();
    }
    Type_Action(const IR::ParameterList *parameters) : Type_MethodBase(parameters) { validate(); }
    IRNODE_SUBCLASS(Type_Action)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Action, NodeKind::Type_Action, Type_MethodBase);
};
}  // namespace P4::IR
namespace P4::IR {
class Method : public Declaration,
               public virtual IAnnotated,
               public virtual IFunctional,
               public virtual ISimpleNamespace {
 public:
    const IR::Type_Method *type = nullptr;
    bool isAbstract = false;
    IR::Vector<IR::Annotation> annotations;
    size_t maxParameterCount() const { return type->maxParameterCount(); }
    size_t minParameterCount() const { return type->minParameterCount(); }
    void setAbstract() { isAbstract = true; }
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    const IR::ParameterList *getParameters() const override;

    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    bool operator==(IR::Method const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Method"_cs; }
    static cstring static_type_name() { return "Method"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Method(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Method(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Method *type, bool isAbstract,
           IR::Vector<IR::Annotation> annotations)
        : Declaration(srcInfo, name), type(type), isAbstract(isAbstract), annotations(annotations) {
        validate();
    }
    Method(IR::ID name, const IR::Type_Method *type, bool isAbstract,
           IR::Vector<IR::Annotation> annotations)
        : Declaration(name), type(type), isAbstract(isAbstract), annotations(annotations) {
        validate();
    }
    Method(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Method *type,
           IR::Vector<IR::Annotation> annotations)
        : Declaration(srcInfo, name), type(type), annotations(annotations) {
        validate();
    }
    Method(IR::ID name, const IR::Type_Method *type, IR::Vector<IR::Annotation> annotations)
        : Declaration(name), type(type), annotations(annotations) {
        validate();
    }
    Method(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Method *type, bool isAbstract)
        : Declaration(srcInfo, name), type(type), isAbstract(isAbstract) {
        validate();
    }
    Method(IR::ID name, const IR::Type_Method *type, bool isAbstract)
        : Declaration(name), type(type), isAbstract(isAbstract) {
        validate();
    }
    Method(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Method *type)
        : Declaration(srcInfo, name), type(type) {
        validate();
    }
    Method(IR::ID name, const IR::Type_Method *type) : Declaration(name), type(type) { validate(); }
    IRNODE_SUBCLASS(Method)
    DECLARE_TYPEINFO_WITH_TYPEID(Method, NodeKind::Method, Declaration, IAnnotated, IFunctional,
                                 ISimpleNamespace);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Typedef : public Type_Declaration, public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::Type *type = nullptr;
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    bool operator==(IR::Type_Typedef const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_Typedef"_cs; }
    static cstring static_type_name() { return "Type_Typedef"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Typedef(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Typedef(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                 const IR::Type *type)
        : Type_Declaration(srcInfo, name), annotations(annotations), type(type) {
        validate();
    }
    Type_Typedef(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::Type *type)
        : Type_Declaration(name), annotations(annotations), type(type) {
        validate();
    }
    Type_Typedef(Util::SourceInfo srcInfo, IR::ID name, const IR::Type *type)
        : Type_Declaration(srcInfo, name), type(type) {
        validate();
    }
    Type_Typedef(IR::ID name, const IR::Type *type) : Type_Declaration(name), type(type) {
        validate();
    }
    IRNODE_SUBCLASS(Type_Typedef)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Typedef, NodeKind::Type_Typedef, Type_Declaration,
                                 IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
/// A newtype is similar to typedef, but it introduces a new type; the
/// the new type does not inherit any
/// of the operations of the original type.  The new type has
/// assignment, equality, and casts to/from the original type.
/// The keyword for newtype is actually `type'.
class Type_Newtype : public Type_Declaration, public virtual IAnnotated {
 public:
    IR::Vector<IR::Annotation> annotations;
    const IR::Type *type = nullptr;
    int width_bits() const override;
    int min_width_bits() const override;
    int max_width_bits() const override;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    bool operator==(IR::Type_Newtype const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Type_Newtype"_cs; }
    static cstring static_type_name() { return "Type_Newtype"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Newtype(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Newtype(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations,
                 const IR::Type *type)
        : Type_Declaration(srcInfo, name), annotations(annotations), type(type) {
        validate();
    }
    Type_Newtype(IR::ID name, IR::Vector<IR::Annotation> annotations, const IR::Type *type)
        : Type_Declaration(name), annotations(annotations), type(type) {
        validate();
    }
    Type_Newtype(Util::SourceInfo srcInfo, IR::ID name, const IR::Type *type)
        : Type_Declaration(srcInfo, name), type(type) {
        validate();
    }
    Type_Newtype(IR::ID name, const IR::Type *type) : Type_Declaration(name), type(type) {
        validate();
    }
    IRNODE_SUBCLASS(Type_Newtype)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Newtype, NodeKind::Type_Newtype, Type_Declaration,
                                 IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
/// An 'extern' black-box (not a function)
class Type_Extern : public Type_Declaration,
                    public virtual INestedNamespace,
                    public virtual IGeneralNamespace,
                    public virtual IMayBeGenericType,
                    public virtual IAnnotated {
 public:
    const IR::TypeParameters *typeParameters = new TypeParameters;
    IR::Vector<IR::Method> methods;

    IR::NameMap<IR::Attribute, ordered_map> attributes;

    IR::Vector<IR::Annotation> annotations;
    std::vector<const IR::INamespace *> getNestedNamespaces() const override;
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::TypeParameters *getTypeParameters() const override;
    void validate() const override;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    /// Returns the method that matches the specified arguments.
    /// Returns nullptr if no method or more than one method match.
    /// In the latter case it also reports an error.
    const IR::Method *lookupMethod(IR::ID name, const IR::Vector<IR::Argument> *arguments) const;
    /// Returns the constructor that matches the specified arguments.
    /// Returns nullptr if no constructor or more than one constructor matches.
    /// In the latter case it also reports an error.
    const IR::Method *lookupConstructor(const IR::Vector<IR::Argument> *arguments) const;
    bool operator==(IR::Type_Extern const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Type_Extern"_cs; }
    static cstring static_type_name() { return "Type_Extern"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Type_Extern(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Declaration const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                IR::Vector<IR::Method> methods, IR::NameMap<IR::Attribute, ordered_map> attributes,
                IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(srcInfo, name),
          typeParameters(typeParameters),
          methods(methods),
          attributes(attributes),
          annotations(annotations) {
        validate();
    }
    Type_Extern(IR::ID name, const IR::TypeParameters *typeParameters,
                IR::Vector<IR::Method> methods, IR::NameMap<IR::Attribute, ordered_map> attributes,
                IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(name),
          typeParameters(typeParameters),
          methods(methods),
          attributes(attributes),
          annotations(annotations) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Method> methods,
                IR::NameMap<IR::Attribute, ordered_map> attributes,
                IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(srcInfo, name),
          methods(methods),
          attributes(attributes),
          annotations(annotations) {
        validate();
    }
    Type_Extern(IR::ID name, IR::Vector<IR::Method> methods,
                IR::NameMap<IR::Attribute, ordered_map> attributes,
                IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(name),
          methods(methods),
          attributes(attributes),
          annotations(annotations) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                IR::NameMap<IR::Attribute, ordered_map> attributes,
                IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(srcInfo, name),
          typeParameters(typeParameters),
          attributes(attributes),
          annotations(annotations) {
        validate();
    }
    Type_Extern(IR::ID name, const IR::TypeParameters *typeParameters,
                IR::NameMap<IR::Attribute, ordered_map> attributes,
                IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(name),
          typeParameters(typeParameters),
          attributes(attributes),
          annotations(annotations) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name,
                IR::NameMap<IR::Attribute, ordered_map> attributes,
                IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(srcInfo, name), attributes(attributes), annotations(annotations) {
        validate();
    }
    Type_Extern(IR::ID name, IR::NameMap<IR::Attribute, ordered_map> attributes,
                IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(name), attributes(attributes), annotations(annotations) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                IR::Vector<IR::Method> methods, IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(srcInfo, name),
          typeParameters(typeParameters),
          methods(methods),
          annotations(annotations) {
        validate();
    }
    Type_Extern(IR::ID name, const IR::TypeParameters *typeParameters,
                IR::Vector<IR::Method> methods, IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(name),
          typeParameters(typeParameters),
          methods(methods),
          annotations(annotations) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Method> methods,
                IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(srcInfo, name), methods(methods), annotations(annotations) {
        validate();
    }
    Type_Extern(IR::ID name, IR::Vector<IR::Method> methods, IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(name), methods(methods), annotations(annotations) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(srcInfo, name),
          typeParameters(typeParameters),
          annotations(annotations) {
        validate();
    }
    Type_Extern(IR::ID name, const IR::TypeParameters *typeParameters,
                IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(name), typeParameters(typeParameters), annotations(annotations) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(srcInfo, name), annotations(annotations) {
        validate();
    }
    Type_Extern(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Type_Declaration(name), annotations(annotations) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                IR::Vector<IR::Method> methods, IR::NameMap<IR::Attribute, ordered_map> attributes)
        : Type_Declaration(srcInfo, name),
          typeParameters(typeParameters),
          methods(methods),
          attributes(attributes) {
        validate();
    }
    Type_Extern(IR::ID name, const IR::TypeParameters *typeParameters,
                IR::Vector<IR::Method> methods, IR::NameMap<IR::Attribute, ordered_map> attributes)
        : Type_Declaration(name),
          typeParameters(typeParameters),
          methods(methods),
          attributes(attributes) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Method> methods,
                IR::NameMap<IR::Attribute, ordered_map> attributes)
        : Type_Declaration(srcInfo, name), methods(methods), attributes(attributes) {
        validate();
    }
    Type_Extern(IR::ID name, IR::Vector<IR::Method> methods,
                IR::NameMap<IR::Attribute, ordered_map> attributes)
        : Type_Declaration(name), methods(methods), attributes(attributes) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                IR::NameMap<IR::Attribute, ordered_map> attributes)
        : Type_Declaration(srcInfo, name), typeParameters(typeParameters), attributes(attributes) {
        validate();
    }
    Type_Extern(IR::ID name, const IR::TypeParameters *typeParameters,
                IR::NameMap<IR::Attribute, ordered_map> attributes)
        : Type_Declaration(name), typeParameters(typeParameters), attributes(attributes) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name,
                IR::NameMap<IR::Attribute, ordered_map> attributes)
        : Type_Declaration(srcInfo, name), attributes(attributes) {
        validate();
    }
    Type_Extern(IR::ID name, IR::NameMap<IR::Attribute, ordered_map> attributes)
        : Type_Declaration(name), attributes(attributes) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters,
                IR::Vector<IR::Method> methods)
        : Type_Declaration(srcInfo, name), typeParameters(typeParameters), methods(methods) {
        validate();
    }
    Type_Extern(IR::ID name, const IR::TypeParameters *typeParameters,
                IR::Vector<IR::Method> methods)
        : Type_Declaration(name), typeParameters(typeParameters), methods(methods) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Method> methods)
        : Type_Declaration(srcInfo, name), methods(methods) {
        validate();
    }
    Type_Extern(IR::ID name, IR::Vector<IR::Method> methods)
        : Type_Declaration(name), methods(methods) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_Declaration(srcInfo, name), typeParameters(typeParameters) {
        validate();
    }
    Type_Extern(IR::ID name, const IR::TypeParameters *typeParameters)
        : Type_Declaration(name), typeParameters(typeParameters) {
        validate();
    }
    Type_Extern(Util::SourceInfo srcInfo, IR::ID name) : Type_Declaration(srcInfo, name) {
        validate();
    }
    Type_Extern(IR::ID name) : Type_Declaration(name) { validate(); }
    IRNODE_SUBCLASS(Type_Extern)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Extern, NodeKind::Type_Extern, Type_Declaration,
                                 INestedNamespace, IGeneralNamespace, IMayBeGenericType,
                                 IAnnotated);
};
}  // namespace P4::IR

#endif  /* IR_GENERATED_TYPES_H_ */
