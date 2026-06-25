#include "ir/ir-generated.h"   // IWYU pragma: keep

#include "ir/ir-inline.h"      // IWYU pragma: keep
#include "ir/json_generator.h" // IWYU pragma: keep
#include "ir/json_loader.h"    // IWYU pragma: keep
#include "ir/visitor.h"        // IWYU pragma: keep
#include "lib/algorithm.h"     // IWYU pragma: keep
#include "lib/log.h"           // IWYU pragma: keep

using namespace P4;

// The unpacker_table is the single registration point used by the JSON
// loader to materialize an IR node from its node_type_name. Keeping it
// in this single TU avoids fragmenting the registry across translation
// units. The explicit IR::Vector<...> instantiations that follow exist
// for the same reason: they must appear in exactly one TU.

std::map<cstring, NodeFactoryFn> IR::unpacker_table = {
    {"Type_Unknown"_cs, NodeFactoryFn(&IR::Type_Unknown::fromJSON)},
    {"Path"_cs, NodeFactoryFn(&IR::Path::fromJSON)},
    {"NamedExpression"_cs, NodeFactoryFn(&IR::NamedExpression::fromJSON)},
    {"AnnotationToken"_cs, NodeFactoryFn(&IR::AnnotationToken::fromJSON)},
    {"Annotation"_cs, NodeFactoryFn(&IR::Annotation::fromJSON)},
    {"Argument"_cs, NodeFactoryFn(&IR::Argument::fromJSON)},
    {"Type_Any"_cs, NodeFactoryFn(&IR::Type_Any::fromJSON)},
    {"Type_Fragment"_cs, NodeFactoryFn(&IR::Type_Fragment::fromJSON)},
    {"Type_Type"_cs, NodeFactoryFn(&IR::Type_Type::fromJSON)},
    {"Type_Boolean"_cs, NodeFactoryFn(&IR::Type_Boolean::fromJSON)},
    {"Type_State"_cs, NodeFactoryFn(&IR::Type_State::fromJSON)},
    {"Type_Bits"_cs, NodeFactoryFn(&IR::Type_Bits::fromJSON)},
    {"Type_Varbits"_cs, NodeFactoryFn(&IR::Type_Varbits::fromJSON)},
    {"Parameter"_cs, NodeFactoryFn(&IR::Parameter::fromJSON)},
    {"ParameterList"_cs, NodeFactoryFn(&IR::ParameterList::fromJSON)},
    {"Type_Var"_cs, NodeFactoryFn(&IR::Type_Var::fromJSON)},
    {"Type_InfInt"_cs, NodeFactoryFn(&IR::Type_InfInt::fromJSON)},
    {"Type_Dontcare"_cs, NodeFactoryFn(&IR::Type_Dontcare::fromJSON)},
    {"Type_Void"_cs, NodeFactoryFn(&IR::Type_Void::fromJSON)},
    {"Type_MatchKind"_cs, NodeFactoryFn(&IR::Type_MatchKind::fromJSON)},
    {"TypeParameters"_cs, NodeFactoryFn(&IR::TypeParameters::fromJSON)},
    {"StructField"_cs, NodeFactoryFn(&IR::StructField::fromJSON)},
    {"Type_Struct"_cs, NodeFactoryFn(&IR::Type_Struct::fromJSON)},
    {"Type_UnknownStruct"_cs, NodeFactoryFn(&IR::Type_UnknownStruct::fromJSON)},
    {"Type_HeaderUnion"_cs, NodeFactoryFn(&IR::Type_HeaderUnion::fromJSON)},
    {"Type_Header"_cs, NodeFactoryFn(&IR::Type_Header::fromJSON)},
    {"Type_Set"_cs, NodeFactoryFn(&IR::Type_Set::fromJSON)},
    {"Type_List"_cs, NodeFactoryFn(&IR::Type_List::fromJSON)},
    {"Type_Tuple"_cs, NodeFactoryFn(&IR::Type_Tuple::fromJSON)},
    {"Type_P4List"_cs, NodeFactoryFn(&IR::Type_P4List::fromJSON)},
    {"Type_Package"_cs, NodeFactoryFn(&IR::Type_Package::fromJSON)},
    {"Type_Parser"_cs, NodeFactoryFn(&IR::Type_Parser::fromJSON)},
    {"Type_Control"_cs, NodeFactoryFn(&IR::Type_Control::fromJSON)},
    {"Type_Name"_cs, NodeFactoryFn(&IR::Type_Name::fromJSON)},
    {"Type_Array"_cs, NodeFactoryFn(&IR::Type_Array::fromJSON)},
    {"Type_Specialized"_cs, NodeFactoryFn(&IR::Type_Specialized::fromJSON)},
    {"Type_SpecializedCanonical"_cs, NodeFactoryFn(&IR::Type_SpecializedCanonical::fromJSON)},
    {"Declaration_ID"_cs, NodeFactoryFn(&IR::Declaration_ID::fromJSON)},
    {"Type_String"_cs, NodeFactoryFn(&IR::Type_String::fromJSON)},
    {"Type_Enum"_cs, NodeFactoryFn(&IR::Type_Enum::fromJSON)},
    {"SerEnumMember"_cs, NodeFactoryFn(&IR::SerEnumMember::fromJSON)},
    {"Type_SerEnum"_cs, NodeFactoryFn(&IR::Type_SerEnum::fromJSON)},
    {"Type_Table"_cs, NodeFactoryFn(&IR::Type_Table::fromJSON)},
    {"Type_ActionEnum"_cs, NodeFactoryFn(&IR::Type_ActionEnum::fromJSON)},
    {"Type_Method"_cs, NodeFactoryFn(&IR::Type_Method::fromJSON)},
    {"ArgumentInfo"_cs, NodeFactoryFn(&IR::ArgumentInfo::fromJSON)},
    {"Type_MethodCall"_cs, NodeFactoryFn(&IR::Type_MethodCall::fromJSON)},
    {"Type_Action"_cs, NodeFactoryFn(&IR::Type_Action::fromJSON)},
    {"Method"_cs, NodeFactoryFn(&IR::Method::fromJSON)},
    {"Type_Typedef"_cs, NodeFactoryFn(&IR::Type_Typedef::fromJSON)},
    {"Type_Newtype"_cs, NodeFactoryFn(&IR::Type_Newtype::fromJSON)},
    {"Type_Extern"_cs, NodeFactoryFn(&IR::Type_Extern::fromJSON)},
    {"Neg"_cs, NodeFactoryFn(&IR::Neg::fromJSON)},
    {"UPlus"_cs, NodeFactoryFn(&IR::UPlus::fromJSON)},
    {"Cmpl"_cs, NodeFactoryFn(&IR::Cmpl::fromJSON)},
    {"LNot"_cs, NodeFactoryFn(&IR::LNot::fromJSON)},
    {"Mul"_cs, NodeFactoryFn(&IR::Mul::fromJSON)},
    {"MulAssign"_cs, NodeFactoryFn(&IR::MulAssign::fromJSON)},
    {"Div"_cs, NodeFactoryFn(&IR::Div::fromJSON)},
    {"DivAssign"_cs, NodeFactoryFn(&IR::DivAssign::fromJSON)},
    {"Mod"_cs, NodeFactoryFn(&IR::Mod::fromJSON)},
    {"ModAssign"_cs, NodeFactoryFn(&IR::ModAssign::fromJSON)},
    {"Add"_cs, NodeFactoryFn(&IR::Add::fromJSON)},
    {"AddAssign"_cs, NodeFactoryFn(&IR::AddAssign::fromJSON)},
    {"Sub"_cs, NodeFactoryFn(&IR::Sub::fromJSON)},
    {"SubAssign"_cs, NodeFactoryFn(&IR::SubAssign::fromJSON)},
    {"AddSat"_cs, NodeFactoryFn(&IR::AddSat::fromJSON)},
    {"AddSatAssign"_cs, NodeFactoryFn(&IR::AddSatAssign::fromJSON)},
    {"SubSat"_cs, NodeFactoryFn(&IR::SubSat::fromJSON)},
    {"SubSatAssign"_cs, NodeFactoryFn(&IR::SubSatAssign::fromJSON)},
    {"Shl"_cs, NodeFactoryFn(&IR::Shl::fromJSON)},
    {"ShlAssign"_cs, NodeFactoryFn(&IR::ShlAssign::fromJSON)},
    {"Shr"_cs, NodeFactoryFn(&IR::Shr::fromJSON)},
    {"ShrAssign"_cs, NodeFactoryFn(&IR::ShrAssign::fromJSON)},
    {"Equ"_cs, NodeFactoryFn(&IR::Equ::fromJSON)},
    {"Neq"_cs, NodeFactoryFn(&IR::Neq::fromJSON)},
    {"Lss"_cs, NodeFactoryFn(&IR::Lss::fromJSON)},
    {"Leq"_cs, NodeFactoryFn(&IR::Leq::fromJSON)},
    {"Grt"_cs, NodeFactoryFn(&IR::Grt::fromJSON)},
    {"Geq"_cs, NodeFactoryFn(&IR::Geq::fromJSON)},
    {"BAnd"_cs, NodeFactoryFn(&IR::BAnd::fromJSON)},
    {"BAndAssign"_cs, NodeFactoryFn(&IR::BAndAssign::fromJSON)},
    {"BOr"_cs, NodeFactoryFn(&IR::BOr::fromJSON)},
    {"BOrAssign"_cs, NodeFactoryFn(&IR::BOrAssign::fromJSON)},
    {"BXor"_cs, NodeFactoryFn(&IR::BXor::fromJSON)},
    {"BXorAssign"_cs, NodeFactoryFn(&IR::BXorAssign::fromJSON)},
    {"LAnd"_cs, NodeFactoryFn(&IR::LAnd::fromJSON)},
    {"LOr"_cs, NodeFactoryFn(&IR::LOr::fromJSON)},
    {"Dots"_cs, NodeFactoryFn(&IR::Dots::fromJSON)},
    {"NamedDots"_cs, NodeFactoryFn(&IR::NamedDots::fromJSON)},
    {"Constant"_cs, NodeFactoryFn(&IR::Constant::fromJSON)},
    {"BoolLiteral"_cs, NodeFactoryFn(&IR::BoolLiteral::fromJSON)},
    {"StringLiteral"_cs, NodeFactoryFn(&IR::StringLiteral::fromJSON)},
    {"PathExpression"_cs, NodeFactoryFn(&IR::PathExpression::fromJSON)},
    {"TypeNameExpression"_cs, NodeFactoryFn(&IR::TypeNameExpression::fromJSON)},
    {"Slice"_cs, NodeFactoryFn(&IR::Slice::fromJSON)},
    {"PlusSlice"_cs, NodeFactoryFn(&IR::PlusSlice::fromJSON)},
    {"Member"_cs, NodeFactoryFn(&IR::Member::fromJSON)},
    {"Concat"_cs, NodeFactoryFn(&IR::Concat::fromJSON)},
    {"ArrayIndex"_cs, NodeFactoryFn(&IR::ArrayIndex::fromJSON)},
    {"Range"_cs, NodeFactoryFn(&IR::Range::fromJSON)},
    {"Mask"_cs, NodeFactoryFn(&IR::Mask::fromJSON)},
    {"Mux"_cs, NodeFactoryFn(&IR::Mux::fromJSON)},
    {"DefaultExpression"_cs, NodeFactoryFn(&IR::DefaultExpression::fromJSON)},
    {"This"_cs, NodeFactoryFn(&IR::This::fromJSON)},
    {"Cast"_cs, NodeFactoryFn(&IR::Cast::fromJSON)},
    {"SelectCase"_cs, NodeFactoryFn(&IR::SelectCase::fromJSON)},
    {"SelectExpression"_cs, NodeFactoryFn(&IR::SelectExpression::fromJSON)},
    {"MethodCallExpression"_cs, NodeFactoryFn(&IR::MethodCallExpression::fromJSON)},
    {"ConstructorCallExpression"_cs, NodeFactoryFn(&IR::ConstructorCallExpression::fromJSON)},
    {"BaseListExpression"_cs, NodeFactoryFn(&IR::BaseListExpression::fromJSON)},
    {"ListExpression"_cs, NodeFactoryFn(&IR::ListExpression::fromJSON)},
    {"P4ListExpression"_cs, NodeFactoryFn(&IR::P4ListExpression::fromJSON)},
    {"StructExpression"_cs, NodeFactoryFn(&IR::StructExpression::fromJSON)},
    {"Invalid"_cs, NodeFactoryFn(&IR::Invalid::fromJSON)},
    {"InvalidHeader"_cs, NodeFactoryFn(&IR::InvalidHeader::fromJSON)},
    {"InvalidHeaderUnion"_cs, NodeFactoryFn(&IR::InvalidHeaderUnion::fromJSON)},
    {"ArrayExpression"_cs, NodeFactoryFn(&IR::ArrayExpression::fromJSON)},
    {"ListCompileTimeValue"_cs, NodeFactoryFn(&IR::ListCompileTimeValue::fromJSON)},
    {"P4ListCompileTimeValue"_cs, NodeFactoryFn(&IR::P4ListCompileTimeValue::fromJSON)},
    {"StructCompileTimeValue"_cs, NodeFactoryFn(&IR::StructCompileTimeValue::fromJSON)},
    {"CompileTimeMethodCall"_cs, NodeFactoryFn(&IR::CompileTimeMethodCall::fromJSON)},
    {"SymbolicVariable"_cs, NodeFactoryFn(&IR::SymbolicVariable::fromJSON)},
    {"ParserState"_cs, NodeFactoryFn(&IR::ParserState::fromJSON)},
    {"P4Parser"_cs, NodeFactoryFn(&IR::P4Parser::fromJSON)},
    {"P4Control"_cs, NodeFactoryFn(&IR::P4Control::fromJSON)},
    {"P4Action"_cs, NodeFactoryFn(&IR::P4Action::fromJSON)},
    {"Type_Error"_cs, NodeFactoryFn(&IR::Type_Error::fromJSON)},
    {"Declaration_MatchKind"_cs, NodeFactoryFn(&IR::Declaration_MatchKind::fromJSON)},
    {"ExpressionValue"_cs, NodeFactoryFn(&IR::ExpressionValue::fromJSON)},
    {"ExpressionListValue"_cs, NodeFactoryFn(&IR::ExpressionListValue::fromJSON)},
    {"ActionListElement"_cs, NodeFactoryFn(&IR::ActionListElement::fromJSON)},
    {"ActionList"_cs, NodeFactoryFn(&IR::ActionList::fromJSON)},
    {"KeyElement"_cs, NodeFactoryFn(&IR::KeyElement::fromJSON)},
    {"Key"_cs, NodeFactoryFn(&IR::Key::fromJSON)},
    {"Entry"_cs, NodeFactoryFn(&IR::Entry::fromJSON)},
    {"EntriesList"_cs, NodeFactoryFn(&IR::EntriesList::fromJSON)},
    {"Property"_cs, NodeFactoryFn(&IR::Property::fromJSON)},
    {"TableProperties"_cs, NodeFactoryFn(&IR::TableProperties::fromJSON)},
    {"P4Table"_cs, NodeFactoryFn(&IR::P4Table::fromJSON)},
    {"P4ValueSet"_cs, NodeFactoryFn(&IR::P4ValueSet::fromJSON)},
    {"Declaration_Variable"_cs, NodeFactoryFn(&IR::Declaration_Variable::fromJSON)},
    {"Declaration_Constant"_cs, NodeFactoryFn(&IR::Declaration_Constant::fromJSON)},
    {"Declaration_Instance"_cs, NodeFactoryFn(&IR::Declaration_Instance::fromJSON)},
    {"P4Program"_cs, NodeFactoryFn(&IR::P4Program::fromJSON)},
    {"ExitStatement"_cs, NodeFactoryFn(&IR::ExitStatement::fromJSON)},
    {"ReturnStatement"_cs, NodeFactoryFn(&IR::ReturnStatement::fromJSON)},
    {"EmptyStatement"_cs, NodeFactoryFn(&IR::EmptyStatement::fromJSON)},
    {"AssignmentStatement"_cs, NodeFactoryFn(&IR::AssignmentStatement::fromJSON)},
    {"IfStatement"_cs, NodeFactoryFn(&IR::IfStatement::fromJSON)},
    {"BreakStatement"_cs, NodeFactoryFn(&IR::BreakStatement::fromJSON)},
    {"ContinueStatement"_cs, NodeFactoryFn(&IR::ContinueStatement::fromJSON)},
    {"BlockStatement"_cs, NodeFactoryFn(&IR::BlockStatement::fromJSON)},
    {"MethodCallStatement"_cs, NodeFactoryFn(&IR::MethodCallStatement::fromJSON)},
    {"SwitchCase"_cs, NodeFactoryFn(&IR::SwitchCase::fromJSON)},
    {"SwitchStatement"_cs, NodeFactoryFn(&IR::SwitchStatement::fromJSON)},
    {"ForStatement"_cs, NodeFactoryFn(&IR::ForStatement::fromJSON)},
    {"ForInStatement"_cs, NodeFactoryFn(&IR::ForInStatement::fromJSON)},
    {"Function"_cs, NodeFactoryFn(&IR::Function::fromJSON)},
    {"TableBlock"_cs, NodeFactoryFn(&IR::TableBlock::fromJSON)},
    {"ParserBlock"_cs, NodeFactoryFn(&IR::ParserBlock::fromJSON)},
    {"ControlBlock"_cs, NodeFactoryFn(&IR::ControlBlock::fromJSON)},
    {"PackageBlock"_cs, NodeFactoryFn(&IR::PackageBlock::fromJSON)},
    {"ExternBlock"_cs, NodeFactoryFn(&IR::ExternBlock::fromJSON)},
    {"ToplevelBlock"_cs, NodeFactoryFn(&IR::ToplevelBlock::fromJSON)},
    {"Type_Block"_cs, NodeFactoryFn(&IR::Type_Block::fromJSON)},
    {"Type_Counter"_cs, NodeFactoryFn(&IR::Type_Counter::fromJSON)},
    {"Type_Expression"_cs, NodeFactoryFn(&IR::Type_Expression::fromJSON)},
    {"Type_FieldListCalculation"_cs, NodeFactoryFn(&IR::Type_FieldListCalculation::fromJSON)},
    {"Type_Meter"_cs, NodeFactoryFn(&IR::Type_Meter::fromJSON)},
    {"Type_Register"_cs, NodeFactoryFn(&IR::Type_Register::fromJSON)},
    {"Type_AnyTable"_cs, NodeFactoryFn(&IR::Type_AnyTable::fromJSON)},
    {"Header"_cs, NodeFactoryFn(&IR::Header::fromJSON)},
    {"HeaderStack"_cs, NodeFactoryFn(&IR::HeaderStack::fromJSON)},
    {"v1HeaderType"_cs, NodeFactoryFn(&IR::v1HeaderType::fromJSON)},
    {"Metadata"_cs, NodeFactoryFn(&IR::Metadata::fromJSON)},
    {"ConcreteHeaderRef"_cs, NodeFactoryFn(&IR::ConcreteHeaderRef::fromJSON)},
    {"HeaderStackItemRef"_cs, NodeFactoryFn(&IR::HeaderStackItemRef::fromJSON)},
    {"If"_cs, NodeFactoryFn(&IR::If::fromJSON)},
    {"NamedCond"_cs, NodeFactoryFn(&IR::NamedCond::fromJSON)},
    {"Apply"_cs, NodeFactoryFn(&IR::Apply::fromJSON)},
    {"Primitive"_cs, NodeFactoryFn(&IR::Primitive::fromJSON)},
    {"FieldList"_cs, NodeFactoryFn(&IR::FieldList::fromJSON)},
    {"FieldListCalculation"_cs, NodeFactoryFn(&IR::FieldListCalculation::fromJSON)},
    {"CalculatedField"_cs, NodeFactoryFn(&IR::CalculatedField::fromJSON)},
    {"ParserValueSet"_cs, NodeFactoryFn(&IR::ParserValueSet::fromJSON)},
    {"CaseEntry"_cs, NodeFactoryFn(&IR::CaseEntry::fromJSON)},
    {"V1Parser"_cs, NodeFactoryFn(&IR::V1Parser::fromJSON)},
    {"ParserException"_cs, NodeFactoryFn(&IR::ParserException::fromJSON)},
    {"Counter"_cs, NodeFactoryFn(&IR::Counter::fromJSON)},
    {"Meter"_cs, NodeFactoryFn(&IR::Meter::fromJSON)},
    {"Register"_cs, NodeFactoryFn(&IR::Register::fromJSON)},
    {"PrimitiveAction"_cs, NodeFactoryFn(&IR::PrimitiveAction::fromJSON)},
    {"NameList"_cs, NodeFactoryFn(&IR::NameList::fromJSON)},
    {"ActionArg"_cs, NodeFactoryFn(&IR::ActionArg::fromJSON)},
    {"ActionFunction"_cs, NodeFactoryFn(&IR::ActionFunction::fromJSON)},
    {"ActionProfile"_cs, NodeFactoryFn(&IR::ActionProfile::fromJSON)},
    {"ActionSelector"_cs, NodeFactoryFn(&IR::ActionSelector::fromJSON)},
    {"V1Table"_cs, NodeFactoryFn(&IR::V1Table::fromJSON)},
    {"V1Control"_cs, NodeFactoryFn(&IR::V1Control::fromJSON)},
    {"AttribLocal"_cs, NodeFactoryFn(&IR::AttribLocal::fromJSON)},
    {"AttribLocals"_cs, NodeFactoryFn(&IR::AttribLocals::fromJSON)},
    {"Attribute"_cs, NodeFactoryFn(&IR::Attribute::fromJSON)},
    {"GlobalRef"_cs, NodeFactoryFn(&IR::GlobalRef::fromJSON)},
    {"AttributeRef"_cs, NodeFactoryFn(&IR::AttributeRef::fromJSON)},
    {"V1Program"_cs, NodeFactoryFn(&IR::V1Program::fromJSON)},
    {"IntMod"_cs, NodeFactoryFn(&IR::IntMod::fromJSON)}};

template class IR::Vector<IR::Node>;
template class IR::IndexedVector<IR::Node>;
template class IR::Vector<IR::Type>;
template class IR::Vector<IR::StatOrDecl>;
template class IR::IndexedVector<IR::StatOrDecl>;
template class IR::Vector<IR::Declaration>;
template class IR::IndexedVector<IR::Declaration>;
template class IR::Vector<IR::Expression>;
template class IR::Vector<IR::NamedExpression>;
template class IR::IndexedVector<IR::NamedExpression>;
template class IR::Vector<IR::AnnotationToken>;
template class IR::Vector<IR::Annotation>;
template class IR::Vector<IR::Argument>;
template class IR::Vector<IR::Parameter>;
template class IR::IndexedVector<IR::Parameter>;
template class IR::Vector<IR::Type_Var>;
template class IR::IndexedVector<IR::Type_Var>;
template class IR::Vector<IR::StructField>;
template class IR::IndexedVector<IR::StructField>;
template class IR::Vector<IR::Declaration_ID>;
template class IR::IndexedVector<IR::Declaration_ID>;
template class IR::Vector<IR::SerEnumMember>;
template class IR::IndexedVector<IR::SerEnumMember>;
template class IR::Vector<IR::ArgumentInfo>;
template class IR::Vector<IR::Method>;
template class IR::Vector<IR::SelectCase>;
template class IR::Vector<IR::ParserState>;
template class IR::IndexedVector<IR::ParserState>;
template class IR::Vector<IR::ActionListElement>;
template class IR::IndexedVector<IR::ActionListElement>;
template class IR::Vector<IR::KeyElement>;
template class IR::Vector<IR::Entry>;
template class IR::Vector<IR::Property>;
template class IR::IndexedVector<IR::Property>;
template class IR::Vector<IR::SwitchCase>;
template class IR::Vector<IR::Primitive>;
template class IR::Vector<IR::CaseEntry>;

