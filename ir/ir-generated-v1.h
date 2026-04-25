#ifndef IR_GENERATED_V1_H_
#define IR_GENERATED_V1_H_

// Legacy P4-14 / v1model IR nodes: header / metadata declarations, V1Parser,
// Counter / Meter / Register and other Stateful / Attached objects, the
// V1Table / V1Control / V1Program structures, and IntMod.

#include "ir/ir-generated-declarations.h"

/*
  This file contains IR classes needed just for the P4 v1.0/v1.1 front-end.
*/
namespace P4 {

namespace IR {
enum class CounterType { NONE, PACKETS, BYTES, BOTH };
}

inline std::ostream &operator<<(std::ostream &out, IR::CounterType d) {
    switch (d) {
        case IR::CounterType::NONE:
            out << "NONE";
            break;
        case IR::CounterType::PACKETS:
            out << "PACKETS";
            break;
        case IR::CounterType::BYTES:
            out << "BYTES";
            break;
        case IR::CounterType::BOTH:
            out << "BOTH";
            break;
        default:
            BUG("Unhandled case");
    }
    return out;
}

inline bool operator>>(cstring s, IR::CounterType &ctr) {
    if (!s || s == "" || s == "NONE")
        ctr = IR::CounterType::NONE;
    else if (s == "PACKETS")
        ctr = IR::CounterType::PACKETS;
    else if (s == "BYTES")
        ctr = IR::CounterType::BYTES;
    else if (s == "BOTH")
        ctr = IR::CounterType::BOTH;
    else
        return false;
    return true;
}

}  // namespace P4


namespace P4::IR {
class Type_Block : public Type_Base {
 public:
    cstring toString() const override;
    static const IR::Type_Block *get();
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_Block const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Block"_cs; }
    static cstring static_type_name() { return "Type_Block"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Block(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Block(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_Block() { validate(); }
    IRNODE_SUBCLASS(Type_Block)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Block, NodeKind::Type_Block, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Counter : public Type_Base {
 public:
    cstring toString() const override;
    static const IR::Type_Counter *get();
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_Counter const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Counter"_cs; }
    static cstring static_type_name() { return "Type_Counter"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Counter(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Counter(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_Counter() { validate(); }
    IRNODE_SUBCLASS(Type_Counter)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Counter, NodeKind::Type_Counter, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Expression : public Type_Base {
 public:
    cstring toString() const override;
    static const IR::Type_Expression *get();
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_Expression const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Expression"_cs; }
    static cstring static_type_name() { return "Type_Expression"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Expression(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Expression(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_Expression() { validate(); }
    IRNODE_SUBCLASS(Type_Expression)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Expression, NodeKind::Type_Expression, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_FieldListCalculation : public Type_Base {
 public:
    cstring toString() const override;
    static const IR::Type_FieldListCalculation *get();
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_FieldListCalculation const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_FieldListCalculation"_cs; }
    static cstring static_type_name() { return "Type_FieldListCalculation"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_FieldListCalculation(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_FieldListCalculation(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_FieldListCalculation() { validate(); }
    IRNODE_SUBCLASS(Type_FieldListCalculation)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_FieldListCalculation, NodeKind::Type_FieldListCalculation,
                                 Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Meter : public Type_Base {
 public:
    cstring toString() const override;
    static const IR::Type_Meter *get();
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_Meter const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Meter"_cs; }
    static cstring static_type_name() { return "Type_Meter"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Meter(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Meter(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_Meter() { validate(); }
    IRNODE_SUBCLASS(Type_Meter)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Meter, NodeKind::Type_Meter, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_Register : public Type_Base {
 public:
    cstring toString() const override;
    static const IR::Type_Register *get();
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_Register const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_Register"_cs; }
    static cstring static_type_name() { return "Type_Register"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_Register(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_Register(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_Register() { validate(); }
    IRNODE_SUBCLASS(Type_Register)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_Register, NodeKind::Type_Register, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class Type_AnyTable : public Type_Base {
 public:
    cstring toString() const override;
    static const IR::Type_AnyTable *get();
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Type_AnyTable const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Type_AnyTable"_cs; }
    static cstring static_type_name() { return "Type_AnyTable"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Type_AnyTable(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Type_Base const &a) const override;
    bool operator==(IR::Type const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Type_AnyTable(Util::SourceInfo srcInfo) : Type_Base(srcInfo) { validate(); }
    Type_AnyTable() { validate(); }
    IRNODE_SUBCLASS(Type_AnyTable)
    DECLARE_TYPEINFO_WITH_TYPEID(Type_AnyTable, NodeKind::Type_AnyTable, Type_Base);
};
}  // namespace P4::IR
namespace P4::IR {
class HeaderOrMetadata : public Node, public virtual IAnnotated {
 public:
    IR::ID type_name;
    IR::ID name;
    IR::Vector<IR::Annotation> annotations;
    const IR::Type_StructLike *type = nullptr;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    HeaderOrMetadata(IR::ID n, const IR::Type_StructLike *t);
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::HeaderOrMetadata const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "HeaderOrMetadata"_cs; }
    static cstring static_type_name() { return "HeaderOrMetadata"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    HeaderOrMetadata(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;

 protected:
    HeaderOrMetadata(Util::SourceInfo srcInfo, IR::ID type_name, IR::ID name,
                     IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), type_name(type_name), name(name), annotations(annotations) {
        validate();
    }
    HeaderOrMetadata(IR::ID type_name, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : type_name(type_name), name(name), annotations(annotations) {
        validate();
    }
    HeaderOrMetadata(Util::SourceInfo srcInfo, IR::ID type_name, IR::ID name)
        : Node(srcInfo), type_name(type_name), name(name) {
        validate();
    }
    HeaderOrMetadata(IR::ID type_name, IR::ID name) : type_name(type_name), name(name) {
        validate();
    }
    IRNODE_ABSTRACT_SUBCLASS(HeaderOrMetadata)
    DECLARE_TYPEINFO_WITH_TYPEID(HeaderOrMetadata, NodeKind::HeaderOrMetadata, Node, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class Header : public HeaderOrMetadata {
 public:
    Header(IR::ID n, const IR::Type_Header *t);
    bool operator==(IR::Header const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Header"_cs; }
    static cstring static_type_name() { return "Header"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Header(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::HeaderOrMetadata const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Header(Util::SourceInfo srcInfo, IR::ID type_name, IR::ID name,
           IR::Vector<IR::Annotation> annotations)
        : HeaderOrMetadata(srcInfo, type_name, name, annotations) {
        validate();
    }
    Header(IR::ID type_name, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : HeaderOrMetadata(type_name, name, annotations) {
        validate();
    }
    Header(Util::SourceInfo srcInfo, IR::ID type_name, IR::ID name)
        : HeaderOrMetadata(srcInfo, type_name, name) {
        validate();
    }
    Header(IR::ID type_name, IR::ID name) : HeaderOrMetadata(type_name, name) { validate(); }
    IRNODE_SUBCLASS(Header)
    DECLARE_TYPEINFO_WITH_TYPEID(Header, NodeKind::Header, HeaderOrMetadata);
};
}  // namespace P4::IR
namespace P4::IR {
class HeaderStack : public HeaderOrMetadata {
 public:
    int size;
    HeaderStack(IR::ID n, const IR::Type_Header *t, int sz);
    bool operator==(IR::HeaderStack const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "HeaderStack"_cs; }
    static cstring static_type_name() { return "HeaderStack"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    HeaderStack(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::HeaderOrMetadata const &a) const override;
    bool operator==(IR::Node const &a) const override;
    HeaderStack(Util::SourceInfo srcInfo, IR::ID type_name, IR::ID name,
                IR::Vector<IR::Annotation> annotations, int size)
        : HeaderOrMetadata(srcInfo, type_name, name, annotations), size(size) {
        validate();
    }
    HeaderStack(IR::ID type_name, IR::ID name, IR::Vector<IR::Annotation> annotations, int size)
        : HeaderOrMetadata(type_name, name, annotations), size(size) {
        validate();
    }
    HeaderStack(Util::SourceInfo srcInfo, IR::ID type_name, IR::ID name, int size)
        : HeaderOrMetadata(srcInfo, type_name, name), size(size) {
        validate();
    }
    HeaderStack(IR::ID type_name, IR::ID name, int size)
        : HeaderOrMetadata(type_name, name), size(size) {
        validate();
    }
    IRNODE_SUBCLASS(HeaderStack)
    DECLARE_TYPEINFO_WITH_TYPEID(HeaderStack, NodeKind::HeaderStack, HeaderOrMetadata);
};
}  // namespace P4::IR
namespace P4::IR {
class v1HeaderType : public Node {
 public:
    IR::ID name;
    const IR::Type_Struct *as_metadata = nullptr;
    const IR::Type_Header *as_header = nullptr;
    v1HeaderType(IR::Type_Struct const *m, IR::Type_Header const *h = nullptr);
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::v1HeaderType const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "v1HeaderType"_cs; }
    static cstring static_type_name() { return "v1HeaderType"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    v1HeaderType(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    v1HeaderType(Util::SourceInfo srcInfo, IR::ID name, const IR::Type_Struct *as_metadata,
                 const IR::Type_Header *as_header)
        : Node(srcInfo), name(name), as_metadata(as_metadata), as_header(as_header) {
        validate();
    }
    v1HeaderType(IR::ID name, const IR::Type_Struct *as_metadata, const IR::Type_Header *as_header)
        : name(name), as_metadata(as_metadata), as_header(as_header) {
        validate();
    }
    IRNODE_SUBCLASS(v1HeaderType)
    DECLARE_TYPEINFO_WITH_TYPEID(v1HeaderType, NodeKind::v1HeaderType, Node);
};
}  // namespace P4::IR
namespace P4::IR {
class Metadata : public HeaderOrMetadata {
 public:
    Metadata(IR::ID n, const IR::Type_StructLike *t);
    bool operator==(IR::Metadata const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Metadata"_cs; }
    static cstring static_type_name() { return "Metadata"_cs; }
    void toJSON(JSONGenerator &json) const override;
    Metadata(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::HeaderOrMetadata const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Metadata(Util::SourceInfo srcInfo, IR::ID type_name, IR::ID name,
             IR::Vector<IR::Annotation> annotations)
        : HeaderOrMetadata(srcInfo, type_name, name, annotations) {
        validate();
    }
    Metadata(IR::ID type_name, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : HeaderOrMetadata(type_name, name, annotations) {
        validate();
    }
    Metadata(Util::SourceInfo srcInfo, IR::ID type_name, IR::ID name)
        : HeaderOrMetadata(srcInfo, type_name, name) {
        validate();
    }
    Metadata(IR::ID type_name, IR::ID name) : HeaderOrMetadata(type_name, name) { validate(); }
    IRNODE_SUBCLASS(Metadata)
    DECLARE_TYPEINFO_WITH_TYPEID(Metadata, NodeKind::Metadata, HeaderOrMetadata);
};
}  // namespace P4::IR
namespace P4::IR {
class HeaderRef : public Expression {
 public:
    virtual const IR::HeaderOrMetadata *baseRef() const = 0;
    bool operator==(IR::HeaderRef const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "HeaderRef"_cs; }
    static cstring static_type_name() { return "HeaderRef"_cs; }
    void toJSON(JSONGenerator &json) const override;
    HeaderRef(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    HeaderRef(Util::SourceInfo srcInfo, const IR::Type *type) : Expression(srcInfo, type) {
        validate();
    }
    HeaderRef(const IR::Type *type) : Expression(type) { validate(); }
    HeaderRef(Util::SourceInfo srcInfo) : Expression(srcInfo) { validate(); }
    HeaderRef() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(HeaderRef)
    DECLARE_TYPEINFO_WITH_TYPEID(HeaderRef, NodeKind::HeaderRef, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
class ConcreteHeaderRef : public HeaderRef {
 public:
    const IR::HeaderOrMetadata *ref = nullptr;
    const IR::HeaderOrMetadata *baseRef() const override;
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::ConcreteHeaderRef const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "ConcreteHeaderRef"_cs; }
    static cstring static_type_name() { return "ConcreteHeaderRef"_cs; }
    void toJSON(JSONGenerator &json) const override;
    ConcreteHeaderRef(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::HeaderRef const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ConcreteHeaderRef(Util::SourceInfo srcInfo, const IR::Type *type,
                      const IR::HeaderOrMetadata *ref)
        : HeaderRef(srcInfo, type), ref(ref) {
        {
            if (type->is<Type::Unknown>() && ref) type = ref->type;
        }
        validate();
    }
    ConcreteHeaderRef(const IR::Type *type, const IR::HeaderOrMetadata *ref)
        : HeaderRef(type), ref(ref) {
        {
            if (type->is<Type::Unknown>() && ref) type = ref->type;
        }
        validate();
    }
    ConcreteHeaderRef(Util::SourceInfo srcInfo, const IR::HeaderOrMetadata *ref)
        : HeaderRef(srcInfo), ref(ref) {
        {
            if (type->is<Type::Unknown>() && ref) type = ref->type;
        }
        validate();
    }
    ConcreteHeaderRef(const IR::HeaderOrMetadata *ref) : ref(ref) {
        {
            if (type->is<Type::Unknown>() && ref) type = ref->type;
        }
        validate();
    }
    IRNODE_SUBCLASS(ConcreteHeaderRef)
    DECLARE_TYPEINFO_WITH_TYPEID(ConcreteHeaderRef, NodeKind::ConcreteHeaderRef, HeaderRef);
};
}  // namespace P4::IR
namespace P4::IR {
class HeaderStackItemRef : public HeaderRef {
 public:
    const IR::Expression *base_ = nullptr;
    const IR::Expression *index_ = nullptr;
    const IR::Expression *base() const;
    /// Returns `nullptr` if the base is not `HeaderOrMetadata` (e.g. when this
    /// is stack ref of an expression such as `lookahead`).
    const IR::HeaderOrMetadata *baseRef() const override;
    const IR::Expression *index() const;
    void set_base(const IR::Expression *b);
    cstring toString() const override;
    bool operator==(IR::HeaderStackItemRef const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "HeaderStackItemRef"_cs; }
    static cstring static_type_name() { return "HeaderStackItemRef"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    HeaderStackItemRef(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::HeaderRef const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    HeaderStackItemRef(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *base_,
                       const IR::Expression *index_)
        : HeaderRef(srcInfo, type), base_(base_), index_(index_) {
        {
            if (type->is<Type::Unknown>() && base_)
                if (auto *hr = base_->to<HeaderRef>()) type = hr->baseRef()->type;
        }
        validate();
    }
    HeaderStackItemRef(const IR::Type *type, const IR::Expression *base_,
                       const IR::Expression *index_)
        : HeaderRef(type), base_(base_), index_(index_) {
        {
            if (type->is<Type::Unknown>() && base_)
                if (auto *hr = base_->to<HeaderRef>()) type = hr->baseRef()->type;
        }
        validate();
    }
    HeaderStackItemRef(Util::SourceInfo srcInfo, const IR::Expression *base_,
                       const IR::Expression *index_)
        : HeaderRef(srcInfo), base_(base_), index_(index_) {
        {
            if (type->is<Type::Unknown>() && base_)
                if (auto *hr = base_->to<HeaderRef>()) type = hr->baseRef()->type;
        }
        validate();
    }
    HeaderStackItemRef(const IR::Expression *base_, const IR::Expression *index_)
        : base_(base_), index_(index_) {
        {
            if (type->is<Type::Unknown>() && base_)
                if (auto *hr = base_->to<HeaderRef>()) type = hr->baseRef()->type;
        }
        validate();
    }
    IRNODE_SUBCLASS(HeaderStackItemRef)
    DECLARE_TYPEINFO_WITH_TYPEID(HeaderStackItemRef, NodeKind::HeaderStackItemRef, HeaderRef);
};
}  // namespace P4::IR
namespace P4::IR {
class If : public Expression {
 public:
    const IR::Expression *pred = nullptr;
    const IR::Vector<IR::Expression> *ifTrue = nullptr;
    const IR::Vector<IR::Expression> *ifFalse = nullptr;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    bool operator==(IR::If const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void validate() const override;
    cstring node_type_name() const override { return "If"_cs; }
    static cstring static_type_name() { return "If"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    If(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    If(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *pred,
       const IR::Vector<IR::Expression> *ifTrue, const IR::Vector<IR::Expression> *ifFalse)
        : Expression(srcInfo, type), pred(pred), ifTrue(ifTrue), ifFalse(ifFalse) {
        validate();
    }
    If(const IR::Type *type, const IR::Expression *pred, const IR::Vector<IR::Expression> *ifTrue,
       const IR::Vector<IR::Expression> *ifFalse)
        : Expression(type), pred(pred), ifTrue(ifTrue), ifFalse(ifFalse) {
        validate();
    }
    If(Util::SourceInfo srcInfo, const IR::Expression *pred,
       const IR::Vector<IR::Expression> *ifTrue, const IR::Vector<IR::Expression> *ifFalse)
        : Expression(srcInfo), pred(pred), ifTrue(ifTrue), ifFalse(ifFalse) {
        validate();
    }
    If(const IR::Expression *pred, const IR::Vector<IR::Expression> *ifTrue,
       const IR::Vector<IR::Expression> *ifFalse)
        : pred(pred), ifTrue(ifTrue), ifFalse(ifFalse) {
        validate();
    }
    IRNODE_SUBCLASS(If)
    DECLARE_TYPEINFO_WITH_TYPEID(If, NodeKind::If, Expression);
};
}  // namespace P4::IR
namespace P4::IR {

class NamedCond : public If {
 public:
    cstring name = unique_name();
    static cstring unique_name();
    NamedCond(IR::If const &i);
    bool operator==(IR::NamedCond const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "NamedCond"_cs; }
    static cstring static_type_name() { return "NamedCond"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    NamedCond(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::If const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    IRNODE_SUBCLASS(NamedCond)
    DECLARE_TYPEINFO_WITH_TYPEID(NamedCond, NodeKind::NamedCond, If);
};
}  // namespace P4::IR
namespace P4::IR {
class Apply : public Expression {
 public:
    IR::ID name;

    IR::NameMap<IR::Vector<IR::Expression>, ordered_map> actions = {};

    IR::NameMap<IR::Path> position = {};
    bool operator==(IR::Apply const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Apply"_cs; }
    static cstring static_type_name() { return "Apply"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Apply(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Apply(Util::SourceInfo srcInfo, const IR::Type *type, IR::ID name)
        : Expression(srcInfo, type), name(name) {
        validate();
    }
    Apply(const IR::Type *type, IR::ID name) : Expression(type), name(name) { validate(); }
    Apply(Util::SourceInfo srcInfo, IR::ID name) : Expression(srcInfo), name(name) { validate(); }
    Apply(IR::ID name) : name(name) { validate(); }
    Apply(Util::SourceInfo srcInfo, const IR::Type *type) : Expression(srcInfo, type) {
        validate();
    }
    Apply(const IR::Type *type) : Expression(type) { validate(); }
    Apply(Util::SourceInfo srcInfo) : Expression(srcInfo) { validate(); }
    Apply() { validate(); }
    IRNODE_SUBCLASS(Apply)
    DECLARE_TYPEINFO_WITH_TYPEID(Apply, NodeKind::Apply, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
class Primitive : public Operation {
 public:
    cstring name;
    IR::Vector<IR::Expression> operands = {};
    Primitive(cstring n, const IR::Vector<IR::Expression> *l);
    Primitive(Util::SourceInfo si, cstring n, const IR::Vector<IR::Expression> *l);
    Primitive(cstring n, const IR::Expression *a1);
    Primitive(Util::SourceInfo si, cstring n, const IR::Expression *a1);
    Primitive(cstring n, const IR::Expression *a1, const IR::Expression *a2);
    Primitive(Util::SourceInfo si, cstring n, const IR::Expression *a1, const IR::Expression *a2);
    Primitive(cstring n, const IR::Expression *a1, const IR::Vector<IR::Expression> *a2);
    Primitive(Util::SourceInfo si, cstring n, const IR::Expression *a1,
              const IR::Vector<IR::Expression> *a2);
    Primitive(cstring n, const IR::Expression *a1, const IR::Expression *a2,
              const IR::Expression *a3);
    Primitive(Util::SourceInfo si, cstring n, const IR::Expression *a1, const IR::Expression *a2,
              const IR::Expression *a3);
    virtual bool isOutput(int operand_index) const;
    virtual unsigned inferOperandTypes() const;
    virtual const IR::Type *inferOperandType(int operand) const;
    virtual void typecheck() const;
    IRNODE_DECLARE_APPLY_OVERLOAD(Primitive)
    cstring getStringOp() const override { return cstring(name); }
    int getPrecedence() const override { return DBPrint::Prec_Postfix; }
    bool operator==(IR::Primitive const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Primitive"_cs; }
    static cstring static_type_name() { return "Primitive"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Primitive(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Primitive(Util::SourceInfo srcInfo, const IR::Type *type, cstring name)
        : Operation(srcInfo, type), name(name) {
        validate();
    }
    Primitive(const IR::Type *type, cstring name) : Operation(type), name(name) { validate(); }
    Primitive(Util::SourceInfo srcInfo, cstring name) : Operation(srcInfo), name(name) {
        validate();
    }
    Primitive(cstring name) : name(name) { validate(); }
    IRNODE_SUBCLASS(Primitive)
    DECLARE_TYPEINFO_WITH_TYPEID(Primitive, NodeKind::Primitive, Operation);
};
}  // namespace P4::IR
namespace P4::IR {
class FieldList : public Node, public virtual IAnnotated {
 public:
    IR::ID name;
    bool payload = false;
    IR::Vector<IR::Annotation> annotations;
    IR::Vector<IR::Expression> fields = {};
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    bool operator==(IR::FieldList const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "FieldList"_cs; }
    static cstring static_type_name() { return "FieldList"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    FieldList(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    FieldList(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), name(name), annotations(annotations) {
        validate();
    }
    FieldList(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : name(name), annotations(annotations) {
        validate();
    }
    FieldList(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), annotations(annotations) {
        validate();
    }
    FieldList(IR::Vector<IR::Annotation> annotations) : annotations(annotations) { validate(); }
    FieldList(Util::SourceInfo srcInfo, IR::ID name) : Node(srcInfo), name(name) { validate(); }
    FieldList(IR::ID name) : name(name) { validate(); }
    FieldList(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    FieldList() { validate(); }
    IRNODE_SUBCLASS(FieldList)
    DECLARE_TYPEINFO_WITH_TYPEID(FieldList, NodeKind::FieldList, Node, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class FieldListCalculation : public Node, public virtual IAnnotated {
 public:
    IR::ID name;
    const IR::NameList *input = nullptr;
    const IR::FieldList *input_fields = nullptr;
    const IR::NameList *algorithm = nullptr;
    int output_width = 0;
    IR::Vector<IR::Annotation> annotations;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    bool operator==(IR::FieldListCalculation const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "FieldListCalculation"_cs; }
    static cstring static_type_name() { return "FieldListCalculation"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    FieldListCalculation(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    FieldListCalculation(Util::SourceInfo srcInfo, IR::ID name,
                         IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), name(name), annotations(annotations) {
        validate();
    }
    FieldListCalculation(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : name(name), annotations(annotations) {
        validate();
    }
    FieldListCalculation(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), annotations(annotations) {
        validate();
    }
    FieldListCalculation(IR::Vector<IR::Annotation> annotations) : annotations(annotations) {
        validate();
    }
    FieldListCalculation(Util::SourceInfo srcInfo, IR::ID name) : Node(srcInfo), name(name) {
        validate();
    }
    FieldListCalculation(IR::ID name) : name(name) { validate(); }
    FieldListCalculation(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    FieldListCalculation() { validate(); }
    IRNODE_SUBCLASS(FieldListCalculation)
    DECLARE_TYPEINFO_WITH_TYPEID(FieldListCalculation, NodeKind::FieldListCalculation, Node,
                                 IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class CalculatedField : public Node, public virtual IAnnotated {
 public:
    const IR::Expression *field = nullptr;
    class update_or_verify {
     public:
        Util::SourceInfo srcInfo;
        bool update = false;
        IR::ID name;
        const IR::Expression *cond = nullptr;
        update_or_verify();

        bool operator==(IR::CalculatedField::update_or_verify const &a) const;
        void toJSON(JSONGenerator &json) const;
        update_or_verify(JSONLoader &json);
        static IR::CalculatedField::update_or_verify *fromJSON(JSONLoader &json);
        update_or_verify(Util::SourceInfo srcInfo, bool update, IR::ID name,
                         const IR::Expression *cond)
            : srcInfo(srcInfo), update(update), name(name), cond(cond) {}
        update_or_verify(Util::SourceInfo srcInfo, IR::ID name, const IR::Expression *cond)
            : srcInfo(srcInfo), name(name), cond(cond) {}
    };
    safe_vector<update_or_verify> specs = {};
    IR::Vector<IR::Annotation> annotations;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    bool operator==(IR::CalculatedField const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void validate() const override;
    cstring node_type_name() const override { return "CalculatedField"_cs; }
    static cstring static_type_name() { return "CalculatedField"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    CalculatedField(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    CalculatedField(Util::SourceInfo srcInfo, const IR::Expression *field,
                    IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), field(field), annotations(annotations) {
        validate();
    }
    CalculatedField(const IR::Expression *field, IR::Vector<IR::Annotation> annotations)
        : field(field), annotations(annotations) {
        validate();
    }
    CalculatedField(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), annotations(annotations) {
        validate();
    }
    CalculatedField(IR::Vector<IR::Annotation> annotations) : annotations(annotations) {
        validate();
    }
    CalculatedField(Util::SourceInfo srcInfo, const IR::Expression *field)
        : Node(srcInfo), field(field) {
        validate();
    }
    CalculatedField(const IR::Expression *field) : field(field) { validate(); }
    CalculatedField(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    CalculatedField() { validate(); }
    IRNODE_SUBCLASS(CalculatedField)
    DECLARE_TYPEINFO_WITH_TYPEID(CalculatedField, NodeKind::CalculatedField, Node, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class ParserValueSet : public Node, public virtual IAnnotated {
 public:
    IR::ID name;
    IR::Vector<IR::Annotation> annotations;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    bool operator==(IR::ParserValueSet const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "ParserValueSet"_cs; }
    static cstring static_type_name() { return "ParserValueSet"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ParserValueSet(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    ParserValueSet(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), name(name), annotations(annotations) {
        validate();
    }
    ParserValueSet(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : name(name), annotations(annotations) {
        validate();
    }
    ParserValueSet(Util::SourceInfo srcInfo, IR::ID name) : Node(srcInfo), name(name) {
        validate();
    }
    ParserValueSet(IR::ID name) : name(name) { validate(); }
    IRNODE_SUBCLASS(ParserValueSet)
    DECLARE_TYPEINFO_WITH_TYPEID(ParserValueSet, NodeKind::ParserValueSet, Node, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class CaseEntry : public Node {
 public:
    safe_vector<std::pair<const IR::Expression *, const IR::Constant *>> values = {};
    IR::ID action;
    bool operator==(IR::CaseEntry const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "CaseEntry"_cs; }
    static cstring static_type_name() { return "CaseEntry"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    CaseEntry(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    CaseEntry(Util::SourceInfo srcInfo, IR::ID action) : Node(srcInfo), action(action) {
        validate();
    }
    CaseEntry(IR::ID action) : action(action) { validate(); }
    CaseEntry(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    CaseEntry() { validate(); }
    IRNODE_SUBCLASS(CaseEntry)
    DECLARE_TYPEINFO_WITH_TYPEID(CaseEntry, NodeKind::CaseEntry, Node);
};
}  // namespace P4::IR
namespace P4::IR {
class V1Parser : public Node, public virtual IAnnotated {
 public:
    IR::ID name;
    IR::Vector<IR::Expression> stmts = {};
    const IR::Vector<IR::Expression> *select = nullptr;
    const IR::Vector<IR::CaseEntry> *cases = nullptr;
    IR::ID default_return = {};
    IR::ID parse_error = {};
    bool drop = false;
    IR::Vector<IR::Annotation> annotations;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    cstring toString() const override;
    bool operator==(IR::V1Parser const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "V1Parser"_cs; }
    static cstring static_type_name() { return "V1Parser"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    V1Parser(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    V1Parser(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), name(name), annotations(annotations) {
        validate();
    }
    V1Parser(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : name(name), annotations(annotations) {
        validate();
    }
    V1Parser(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), annotations(annotations) {
        validate();
    }
    V1Parser(IR::Vector<IR::Annotation> annotations) : annotations(annotations) { validate(); }
    V1Parser(Util::SourceInfo srcInfo, IR::ID name) : Node(srcInfo), name(name) { validate(); }
    V1Parser(IR::ID name) : name(name) { validate(); }
    V1Parser(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    V1Parser() { validate(); }
    IRNODE_SUBCLASS(V1Parser)
    DECLARE_TYPEINFO_WITH_TYPEID(V1Parser, NodeKind::V1Parser, Node, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class ParserException : public Node {
 public:
    bool operator==(IR::ParserException const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "ParserException"_cs; }
    static cstring static_type_name() { return "ParserException"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ParserException(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    ParserException(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    ParserException() { validate(); }
    IRNODE_SUBCLASS(ParserException)
    DECLARE_TYPEINFO_WITH_TYPEID(ParserException, NodeKind::ParserException, Node);
};
}  // namespace P4::IR
namespace P4::IR {
class Attached : public Node, public virtual IInstance, public virtual IAnnotated {
 public:
    IR::ID name;
    IR::Vector<IR::Annotation> annotations;
    IR::ID Name() const override;
    virtual char const *kind() const = 0;
    const IR::Type *getType() const override;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    virtual bool indexed() const;
    IR::Attached *clone_rename(char const *ext) const;
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    bool operator==(IR::Attached const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "Attached"_cs; }
    static cstring static_type_name() { return "Attached"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Attached(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;

 protected:
    Attached(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), name(name), annotations(annotations) {
        validate();
    }
    Attached(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : name(name), annotations(annotations) {
        validate();
    }
    Attached(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), annotations(annotations) {
        validate();
    }
    Attached(IR::Vector<IR::Annotation> annotations) : annotations(annotations) { validate(); }
    Attached(Util::SourceInfo srcInfo, IR::ID name) : Node(srcInfo), name(name) { validate(); }
    Attached(IR::ID name) : name(name) { validate(); }
    Attached(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    Attached() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Attached)
    DECLARE_TYPEINFO_WITH_TYPEID(Attached, NodeKind::Attached, Node, IInstance, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class Stateful : public Attached {
 public:
    IR::ID table = {};
    bool direct = false;
    bool saturating = false;
    int instance_count = -1;
    virtual bool indexed() const override;
    int index_width() const;

    bool operator==(IR::Stateful const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Stateful"_cs; }
    static cstring static_type_name() { return "Stateful"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Stateful(JSONLoader &json);
    bool operator==(IR::Attached const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    Stateful(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Attached(srcInfo, name, annotations) {
        validate();
    }
    Stateful(IR::ID name, IR::Vector<IR::Annotation> annotations) : Attached(name, annotations) {
        validate();
    }
    Stateful(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Attached(srcInfo, annotations) {
        validate();
    }
    Stateful(IR::Vector<IR::Annotation> annotations) : Attached(annotations) { validate(); }
    Stateful(Util::SourceInfo srcInfo, IR::ID name) : Attached(srcInfo, name) { validate(); }
    Stateful(IR::ID name) : Attached(name) { validate(); }
    Stateful(Util::SourceInfo srcInfo) : Attached(srcInfo) { validate(); }
    Stateful() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(Stateful)
    DECLARE_TYPEINFO_WITH_TYPEID(Stateful, NodeKind::Stateful, Attached);
};
}  // namespace P4::IR
namespace P4::IR {
class CounterOrMeter : public Stateful {
 public:
    CounterType type = CounterType::NONE;
    void settype(cstring t);

    bool operator==(IR::CounterOrMeter const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "CounterOrMeter"_cs; }
    static cstring static_type_name() { return "CounterOrMeter"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    CounterOrMeter(JSONLoader &json);
    bool operator==(IR::Stateful const &a) const override;
    bool operator==(IR::Attached const &a) const override;
    bool operator==(IR::Node const &a) const override;

 protected:
    CounterOrMeter(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Stateful(srcInfo, name, annotations) {
        validate();
    }
    CounterOrMeter(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Stateful(name, annotations) {
        validate();
    }
    CounterOrMeter(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Stateful(srcInfo, annotations) {
        validate();
    }
    CounterOrMeter(IR::Vector<IR::Annotation> annotations) : Stateful(annotations) { validate(); }
    CounterOrMeter(Util::SourceInfo srcInfo, IR::ID name) : Stateful(srcInfo, name) { validate(); }
    CounterOrMeter(IR::ID name) : Stateful(name) { validate(); }
    CounterOrMeter(Util::SourceInfo srcInfo) : Stateful(srcInfo) { validate(); }
    CounterOrMeter() { validate(); }
    IRNODE_ABSTRACT_SUBCLASS(CounterOrMeter)
    DECLARE_TYPEINFO_WITH_TYPEID(CounterOrMeter, NodeKind::CounterOrMeter, Stateful);
};
}  // namespace P4::IR
namespace P4::IR {
class Counter : public CounterOrMeter {
 public:
    int max_width = -1;
    int min_width = -1;
    char const *kind() const override;
    IR::Type const *getType() const override;
    bool operator==(IR::Counter const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Counter"_cs; }
    static cstring static_type_name() { return "Counter"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Counter(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::CounterOrMeter const &a) const override;
    bool operator==(IR::Stateful const &a) const override;
    bool operator==(IR::Attached const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Counter(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : CounterOrMeter(srcInfo, name, annotations) {
        validate();
    }
    Counter(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : CounterOrMeter(name, annotations) {
        validate();
    }
    Counter(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : CounterOrMeter(srcInfo, annotations) {
        validate();
    }
    Counter(IR::Vector<IR::Annotation> annotations) : CounterOrMeter(annotations) { validate(); }
    Counter(Util::SourceInfo srcInfo, IR::ID name) : CounterOrMeter(srcInfo, name) { validate(); }
    Counter(IR::ID name) : CounterOrMeter(name) { validate(); }
    Counter(Util::SourceInfo srcInfo) : CounterOrMeter(srcInfo) { validate(); }
    Counter() { validate(); }
    IRNODE_SUBCLASS(Counter)
    DECLARE_TYPEINFO_WITH_TYPEID(Counter, NodeKind::Counter, CounterOrMeter);
};
}  // namespace P4::IR
namespace P4::IR {
class Meter : public CounterOrMeter {
 public:
    const IR::Expression *result = nullptr;
    const IR::Expression *pre_color = nullptr;
    IR::ID implementation = {};
    char const *kind() const override;
    const IR::Type *getType() const override;
    bool operator==(IR::Meter const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Meter"_cs; }
    static cstring static_type_name() { return "Meter"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Meter(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::CounterOrMeter const &a) const override;
    bool operator==(IR::Stateful const &a) const override;
    bool operator==(IR::Attached const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Meter(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : CounterOrMeter(srcInfo, name, annotations) {
        validate();
    }
    Meter(IR::ID name, IR::Vector<IR::Annotation> annotations) : CounterOrMeter(name, annotations) {
        validate();
    }
    Meter(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : CounterOrMeter(srcInfo, annotations) {
        validate();
    }
    Meter(IR::Vector<IR::Annotation> annotations) : CounterOrMeter(annotations) { validate(); }
    Meter(Util::SourceInfo srcInfo, IR::ID name) : CounterOrMeter(srcInfo, name) { validate(); }
    Meter(IR::ID name) : CounterOrMeter(name) { validate(); }
    Meter(Util::SourceInfo srcInfo) : CounterOrMeter(srcInfo) { validate(); }
    Meter() { validate(); }
    IRNODE_SUBCLASS(Meter)
    DECLARE_TYPEINFO_WITH_TYPEID(Meter, NodeKind::Meter, CounterOrMeter);
};
}  // namespace P4::IR
namespace P4::IR {
class Register : public Stateful {
 public:
    IR::ID layout = {};
    int width = -1;
    bool signed_ = false;

    char const *kind() const override;
    const IR::Type *getType() const override;
    bool operator==(IR::Register const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "Register"_cs; }
    static cstring static_type_name() { return "Register"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Register(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Stateful const &a) const override;
    bool operator==(IR::Attached const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Register(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Stateful(srcInfo, name, annotations) {
        validate();
    }
    Register(IR::ID name, IR::Vector<IR::Annotation> annotations) : Stateful(name, annotations) {
        validate();
    }
    Register(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Stateful(srcInfo, annotations) {
        validate();
    }
    Register(IR::Vector<IR::Annotation> annotations) : Stateful(annotations) { validate(); }
    Register(Util::SourceInfo srcInfo, IR::ID name) : Stateful(srcInfo, name) { validate(); }
    Register(IR::ID name) : Stateful(name) { validate(); }
    Register(Util::SourceInfo srcInfo) : Stateful(srcInfo) { validate(); }
    Register() { validate(); }
    IRNODE_SUBCLASS(Register)
    DECLARE_TYPEINFO_WITH_TYPEID(Register, NodeKind::Register, Stateful);
};
}  // namespace P4::IR
namespace P4::IR {
class PrimitiveAction : public Node {
 public:
    bool operator==(IR::PrimitiveAction const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "PrimitiveAction"_cs; }
    static cstring static_type_name() { return "PrimitiveAction"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    PrimitiveAction(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    PrimitiveAction(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    PrimitiveAction() { validate(); }
    IRNODE_SUBCLASS(PrimitiveAction)
    DECLARE_TYPEINFO_WITH_TYPEID(PrimitiveAction, NodeKind::PrimitiveAction, Node);
};
}  // namespace P4::IR
namespace P4::IR {
class NameList : public Node {
 public:
    safe_vector<IR::ID> names = {};
    NameList(Util::SourceInfo si, cstring n);
    NameList(Util::SourceInfo si, IR::ID n);
    void dump_fields(std::ostream &out) const override;
    bool operator==(IR::NameList const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "NameList"_cs; }
    static cstring static_type_name() { return "NameList"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    NameList(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    NameList(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    NameList() { validate(); }
    IRNODE_SUBCLASS(NameList)
    DECLARE_TYPEINFO_WITH_TYPEID(NameList, NodeKind::NameList, Node);
};
}  // namespace P4::IR
namespace P4::IR {
class ActionArg : public Expression {
 public:
    cstring action_name;
    IR::ID name;
    bool read = false;
    bool write = false;
    void dbprint(std::ostream &out) const override;
    cstring toString() const override;
    bool operator==(IR::ActionArg const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "ActionArg"_cs; }
    static cstring static_type_name() { return "ActionArg"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ActionArg(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ActionArg(Util::SourceInfo srcInfo, const IR::Type *type, cstring action_name, IR::ID name)
        : Expression(srcInfo, type), action_name(action_name), name(name) {
        {
            if (!srcInfo) srcInfo = name.srcInfo;
        }
        validate();
    }
    ActionArg(const IR::Type *type, cstring action_name, IR::ID name)
        : Expression(type), action_name(action_name), name(name) {
        {
            if (!srcInfo) srcInfo = name.srcInfo;
        }
        validate();
    }
    ActionArg(Util::SourceInfo srcInfo, cstring action_name, IR::ID name)
        : Expression(srcInfo), action_name(action_name), name(name) {
        {
            if (!srcInfo) srcInfo = name.srcInfo;
        }
        validate();
    }
    ActionArg(cstring action_name, IR::ID name) : action_name(action_name), name(name) {
        {
            if (!srcInfo) srcInfo = name.srcInfo;
        }
        validate();
    }
    IRNODE_SUBCLASS(ActionArg)
    DECLARE_TYPEINFO_WITH_TYPEID(ActionArg, NodeKind::ActionArg, Expression);
};
}  // namespace P4::IR
namespace P4::IR {

class ActionFunction : public Node, public virtual IAnnotated {
 public:
    IR::ID name;
    IR::Vector<IR::Primitive> action = {};
    safe_vector<const IR::ActionArg *> args = {};
    IR::Vector<IR::Annotation> annotations;
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    const IR::ActionArg *arg(cstring n) const;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring toString() const override;
    bool operator==(IR::ActionFunction const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void validate() const override;
    cstring node_type_name() const override { return "ActionFunction"_cs; }
    static cstring static_type_name() { return "ActionFunction"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ActionFunction(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    ActionFunction(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), name(name), annotations(annotations) {
        validate();
    }
    ActionFunction(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : name(name), annotations(annotations) {
        validate();
    }
    ActionFunction(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), annotations(annotations) {
        validate();
    }
    ActionFunction(IR::Vector<IR::Annotation> annotations) : annotations(annotations) {
        validate();
    }
    ActionFunction(Util::SourceInfo srcInfo, IR::ID name) : Node(srcInfo), name(name) {
        validate();
    }
    ActionFunction(IR::ID name) : name(name) { validate(); }
    ActionFunction(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    ActionFunction() { validate(); }
    IRNODE_SUBCLASS(ActionFunction)
    DECLARE_TYPEINFO_WITH_TYPEID(ActionFunction, NodeKind::ActionFunction, Node, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class ActionProfile : public Attached {
 public:
    IR::ID selector = {};
    safe_vector<IR::ID> actions = {};
    int size = 0;
    char const *kind() const override;
    bool indexed() const override;
    bool operator==(IR::ActionProfile const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "ActionProfile"_cs; }
    static cstring static_type_name() { return "ActionProfile"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ActionProfile(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Attached const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ActionProfile(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Attached(srcInfo, name, annotations) {
        validate();
    }
    ActionProfile(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Attached(name, annotations) {
        validate();
    }
    ActionProfile(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Attached(srcInfo, annotations) {
        validate();
    }
    ActionProfile(IR::Vector<IR::Annotation> annotations) : Attached(annotations) { validate(); }
    ActionProfile(Util::SourceInfo srcInfo, IR::ID name) : Attached(srcInfo, name) { validate(); }
    ActionProfile(IR::ID name) : Attached(name) { validate(); }
    ActionProfile(Util::SourceInfo srcInfo) : Attached(srcInfo) { validate(); }
    ActionProfile() { validate(); }
    IRNODE_SUBCLASS(ActionProfile)
    DECLARE_TYPEINFO_WITH_TYPEID(ActionProfile, NodeKind::ActionProfile, Attached);
};
}  // namespace P4::IR
namespace P4::IR {
class ActionSelector : public Attached {
 public:
    IR::ID key = {};
    const IR::FieldListCalculation *key_fields = nullptr;
    IR::ID mode = {};
    IR::ID type = {};
    char const *kind() const override;
    bool operator==(IR::ActionSelector const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "ActionSelector"_cs; }
    static cstring static_type_name() { return "ActionSelector"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    ActionSelector(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Attached const &a) const override;
    bool operator==(IR::Node const &a) const override;
    ActionSelector(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Attached(srcInfo, name, annotations) {
        validate();
    }
    ActionSelector(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Attached(name, annotations) {
        validate();
    }
    ActionSelector(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Attached(srcInfo, annotations) {
        validate();
    }
    ActionSelector(IR::Vector<IR::Annotation> annotations) : Attached(annotations) { validate(); }
    ActionSelector(Util::SourceInfo srcInfo, IR::ID name) : Attached(srcInfo, name) { validate(); }
    ActionSelector(IR::ID name) : Attached(name) { validate(); }
    ActionSelector(Util::SourceInfo srcInfo) : Attached(srcInfo) { validate(); }
    ActionSelector() { validate(); }
    IRNODE_SUBCLASS(ActionSelector)
    DECLARE_TYPEINFO_WITH_TYPEID(ActionSelector, NodeKind::ActionSelector, Attached);
};
}  // namespace P4::IR
namespace P4::IR {
class V1Table : public Node, public virtual IInstance, public virtual IAnnotated {
 public:
    IR::ID name;
    const IR::Vector<IR::Expression> *reads = 0;
    safe_vector<IR::ID> reads_types = {};
    int min_size = 0;
    int max_size = 0;
    int size = 0;
    IR::ID action_profile = {};
    safe_vector<IR::ID> actions = {};
    IR::ID default_action = {};
    bool default_action_is_const = false;
    const IR::Vector<IR::Expression> *default_action_args = 0;
    IR::TableProperties properties = {};

    IR::Vector<IR::Annotation> annotations;
    void addProperty(const IR::Property *prop);
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    cstring toString() const override;
    IR::ID Name() const override;
    const IR::Type *getType() const override;
    bool operator==(IR::V1Table const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "V1Table"_cs; }
    static cstring static_type_name() { return "V1Table"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    V1Table(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    V1Table(Util::SourceInfo srcInfo, IR::ID name, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), name(name), annotations(annotations) {
        validate();
    }
    V1Table(IR::ID name, IR::Vector<IR::Annotation> annotations)
        : name(name), annotations(annotations) {
        validate();
    }
    V1Table(Util::SourceInfo srcInfo, IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), annotations(annotations) {
        validate();
    }
    V1Table(IR::Vector<IR::Annotation> annotations) : annotations(annotations) { validate(); }
    V1Table(Util::SourceInfo srcInfo, IR::ID name) : Node(srcInfo), name(name) { validate(); }
    V1Table(IR::ID name) : name(name) { validate(); }
    V1Table(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    V1Table() { validate(); }
    IRNODE_SUBCLASS(V1Table)
    DECLARE_TYPEINFO_WITH_TYPEID(V1Table, NodeKind::V1Table, Node, IInstance, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class V1Control : public Node, public virtual IAnnotated {
 public:
    IR::ID name;
    const IR::Vector<IR::Expression> *code = nullptr;
    IR::Vector<IR::Annotation> annotations;
    V1Control(IR::ID n);
    V1Control(Util::SourceInfo si, IR::ID n);
    IRNODE_DECLARE_APPLY_OVERLOAD(V1Control)
    IR::Vector<IR::Annotation> const &getAnnotations() const override;
    IR::Vector<IR::Annotation> &getAnnotations() override;
    cstring toString() const override;
    bool operator==(IR::V1Control const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "V1Control"_cs; }
    static cstring static_type_name() { return "V1Control"_cs; }
    void dbprint(std::ostream &out) const override;
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    V1Control(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    V1Control(Util::SourceInfo srcInfo, IR::ID name, const IR::Vector<IR::Expression> *code,
              IR::Vector<IR::Annotation> annotations)
        : Node(srcInfo), name(name), code(code), annotations(annotations) {
        validate();
    }
    V1Control(IR::ID name, const IR::Vector<IR::Expression> *code,
              IR::Vector<IR::Annotation> annotations)
        : name(name), code(code), annotations(annotations) {
        validate();
    }
    V1Control(Util::SourceInfo srcInfo, IR::ID name, const IR::Vector<IR::Expression> *code)
        : Node(srcInfo), name(name), code(code) {
        validate();
    }
    V1Control(IR::ID name, const IR::Vector<IR::Expression> *code) : name(name), code(code) {
        validate();
    }
    IRNODE_SUBCLASS(V1Control)
    DECLARE_TYPEINFO_WITH_TYPEID(V1Control, NodeKind::V1Control, Node, IAnnotated);
};
}  // namespace P4::IR
namespace P4::IR {
class AttribLocal : public Expression, public virtual IDeclaration {
 public:
    IR::ID name;
    IR::ID getName() const override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::AttribLocal const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "AttribLocal"_cs; }
    static cstring static_type_name() { return "AttribLocal"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    AttribLocal(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    AttribLocal(Util::SourceInfo srcInfo, const IR::Type *type, IR::ID name)
        : Expression(srcInfo, type), name(name) {
        validate();
    }
    AttribLocal(const IR::Type *type, IR::ID name) : Expression(type), name(name) { validate(); }
    AttribLocal(Util::SourceInfo srcInfo, IR::ID name) : Expression(srcInfo), name(name) {
        validate();
    }
    AttribLocal(IR::ID name) : name(name) { validate(); }
    IRNODE_SUBCLASS(AttribLocal)
    DECLARE_TYPEINFO_WITH_TYPEID(AttribLocal, NodeKind::AttribLocal, Expression, IDeclaration);
};
}  // namespace P4::IR
namespace P4::IR {
class AttribLocals : public Node, public virtual ISimpleNamespace {
 public:
    IR::NameMap<IR::AttribLocal> locals = {};
    Util::Enumerator<const IR::IDeclaration *> *getDeclarations() const override;
    const IR::IDeclaration *getDeclByName(cstring name) const override;
    const IR::IDeclaration *getDeclByName(std::string_view name) const override;
    bool operator==(IR::AttribLocals const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "AttribLocals"_cs; }
    static cstring static_type_name() { return "AttribLocals"_cs; }
    void toJSON(JSONGenerator &json) const override;
    AttribLocals(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    AttribLocals(Util::SourceInfo srcInfo) : Node(srcInfo) { validate(); }
    AttribLocals() { validate(); }
    IRNODE_SUBCLASS(AttribLocals)
    DECLARE_TYPEINFO_WITH_TYPEID(AttribLocals, NodeKind::AttribLocals, Node, ISimpleNamespace);
};
}  // namespace P4::IR
namespace P4::IR {
class Attribute : public Declaration {
 public:
    const IR::Type *type = nullptr;
    const IR::AttribLocals *locals = nullptr;
    bool optional = false;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::Attribute const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "Attribute"_cs; }
    static cstring static_type_name() { return "Attribute"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    Attribute(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Declaration const &a) const override;
    bool operator==(IR::StatOrDecl const &a) const override;
    bool operator==(IR::Node const &a) const override;
    Attribute(Util::SourceInfo srcInfo, IR::ID name) : Declaration(srcInfo, name) { validate(); }
    Attribute(IR::ID name) : Declaration(name) { validate(); }
    IRNODE_SUBCLASS(Attribute)
    DECLARE_TYPEINFO_WITH_TYPEID(Attribute, NodeKind::Attribute, Declaration);
};
}  // namespace P4::IR
namespace P4::IR {
class GlobalRef : public Expression {
 public:
    const IR::Node *obj = nullptr;

    void validate() const override;
    cstring toString() const override;
    IR::ID Name() const;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::GlobalRef const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    cstring node_type_name() const override { return "GlobalRef"_cs; }
    static cstring static_type_name() { return "GlobalRef"_cs; }
    void toJSON(JSONGenerator &json) const override;
    GlobalRef(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    GlobalRef(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Node *obj)
        : Expression(srcInfo, type), obj(obj) {
        { type = obj->to<IInstance>()->getType(); }
        validate();
    }
    GlobalRef(const IR::Type *type, const IR::Node *obj) : Expression(type), obj(obj) {
        { type = obj->to<IInstance>()->getType(); }
        validate();
    }
    GlobalRef(Util::SourceInfo srcInfo, const IR::Node *obj) : Expression(srcInfo), obj(obj) {
        { type = obj->to<IInstance>()->getType(); }
        validate();
    }
    GlobalRef(const IR::Node *obj) : obj(obj) {
        { type = obj->to<IInstance>()->getType(); }
        validate();
    }
    IRNODE_SUBCLASS(GlobalRef)
    DECLARE_TYPEINFO_WITH_TYPEID(GlobalRef, NodeKind::GlobalRef, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
class AttributeRef : public Expression {
 public:
    cstring extern_name;
    const IR::Type_Extern *extern_type = nullptr;
    const IR::Attribute *attrib = nullptr;
    cstring toString() const override;
    void dbprint(std::ostream &out) const override;
    bool operator==(IR::AttributeRef const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "AttributeRef"_cs; }
    static cstring static_type_name() { return "AttributeRef"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    AttributeRef(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    AttributeRef(Util::SourceInfo srcInfo, const IR::Type *type, cstring extern_name,
                 const IR::Type_Extern *extern_type, const IR::Attribute *attrib)
        : Expression(srcInfo, type),
          extern_name(extern_name),
          extern_type(extern_type),
          attrib(attrib) {
        { type = attrib->type; }
        validate();
    }
    AttributeRef(const IR::Type *type, cstring extern_name, const IR::Type_Extern *extern_type,
                 const IR::Attribute *attrib)
        : Expression(type), extern_name(extern_name), extern_type(extern_type), attrib(attrib) {
        { type = attrib->type; }
        validate();
    }
    AttributeRef(Util::SourceInfo srcInfo, cstring extern_name, const IR::Type_Extern *extern_type,
                 const IR::Attribute *attrib)
        : Expression(srcInfo), extern_name(extern_name), extern_type(extern_type), attrib(attrib) {
        { type = attrib->type; }
        validate();
    }
    AttributeRef(cstring extern_name, const IR::Type_Extern *extern_type,
                 const IR::Attribute *attrib)
        : extern_name(extern_name), extern_type(extern_type), attrib(attrib) {
        { type = attrib->type; }
        validate();
    }
    IRNODE_SUBCLASS(AttributeRef)
    DECLARE_TYPEINFO_WITH_TYPEID(AttributeRef, NodeKind::AttributeRef, Expression);
};
}  // namespace P4::IR
namespace P4::IR {
class V1Program : public Node {
 public:
    IR::NameMap<IR::Node, std::multimap> scope;
    explicit V1Program();
    template <class T>
    const T *get(cstring name) const {
        return scope.get<T>(name);
    }
    void add(cstring name, IR::Node const *n);
    IRNODE_DECLARE_APPLY_OVERLOAD(V1Program)
    bool operator==(IR::V1Program const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    void visit_children(Visitor &v, char const *n) override;
    void visit_children(Visitor &v, char const *n) const override;
    void validate() const override;
    cstring node_type_name() const override { return "V1Program"_cs; }
    static cstring static_type_name() { return "V1Program"_cs; }
    void dbprint(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    V1Program(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Node const &a) const override;
    IRNODE_SUBCLASS(V1Program)
    DECLARE_TYPEINFO_WITH_TYPEID(V1Program, NodeKind::V1Program, Node);
};
}  // namespace P4::IR
namespace P4::IR {
// Represent a signed integer value using just 'width' bits.
// Special operation provided by BMv2
class IntMod : public Operation_Unary {
 public:
    unsigned width;
    cstring getStringOp() const override { return cstring("><"); }
    int getPrecedence() const override { return DBPrint::Prec_Low; }
    bool operator==(IR::IntMod const &a) const override;
    bool equiv(IR::Node const &a_) const override;
    cstring node_type_name() const override { return "IntMod"_cs; }
    static cstring static_type_name() { return "IntMod"_cs; }
    void dump_fields(std::ostream &out) const override;
    void toJSON(JSONGenerator &json) const override;
    IntMod(JSONLoader &json);
    static IR::Node *fromJSON(JSONLoader &json);
    bool operator==(IR::Operation_Unary const &a) const override;
    bool operator==(IR::Operation const &a) const override;
    bool operator==(IR::Expression const &a) const override;
    bool operator==(IR::Node const &a) const override;
    IntMod(Util::SourceInfo srcInfo, const IR::Type *type, const IR::Expression *expr,
           unsigned width)
        : Operation_Unary(srcInfo, type, expr), width(width) {
        validate();
    }
    IntMod(const IR::Type *type, const IR::Expression *expr, unsigned width)
        : Operation_Unary(type, expr), width(width) {
        validate();
    }
    IntMod(Util::SourceInfo srcInfo, const IR::Expression *expr, unsigned width)
        : Operation_Unary(srcInfo, expr), width(width) {
        validate();
    }
    IntMod(const IR::Expression *expr, unsigned width) : Operation_Unary(expr), width(width) {
        validate();
    }
    IRNODE_SUBCLASS(IntMod)
    DECLARE_TYPEINFO_WITH_TYPEID(IntMod, NodeKind::IntMod, Operation_Unary);
};
}  // namespace P4::IR

#endif  /* IR_GENERATED_V1_H_ */
