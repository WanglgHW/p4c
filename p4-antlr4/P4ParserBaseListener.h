
// Generated from P4Parser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "P4ParserListener.h"


/**
 * This class provides an empty implementation of P4ParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  P4ParserBaseListener : public P4ParserListener {
public:

  virtual void enterProgram(P4Parser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(P4Parser::ProgramContext * /*ctx*/) override { }

  virtual void enterDeclaration(P4Parser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(P4Parser::DeclarationContext * /*ctx*/) override { }

  virtual void enterNonTypeName(P4Parser::NonTypeNameContext * /*ctx*/) override { }
  virtual void exitNonTypeName(P4Parser::NonTypeNameContext * /*ctx*/) override { }

  virtual void enterName(P4Parser::NameContext * /*ctx*/) override { }
  virtual void exitName(P4Parser::NameContext * /*ctx*/) override { }

  virtual void enterNonTableKwName(P4Parser::NonTableKwNameContext * /*ctx*/) override { }
  virtual void exitNonTableKwName(P4Parser::NonTableKwNameContext * /*ctx*/) override { }

  virtual void enterAnnotationName(P4Parser::AnnotationNameContext * /*ctx*/) override { }
  virtual void exitAnnotationName(P4Parser::AnnotationNameContext * /*ctx*/) override { }

  virtual void enterOptAnnotations(P4Parser::OptAnnotationsContext * /*ctx*/) override { }
  virtual void exitOptAnnotations(P4Parser::OptAnnotationsContext * /*ctx*/) override { }

  virtual void enterAnnotations(P4Parser::AnnotationsContext * /*ctx*/) override { }
  virtual void exitAnnotations(P4Parser::AnnotationsContext * /*ctx*/) override { }

  virtual void enterAnnotation(P4Parser::AnnotationContext * /*ctx*/) override { }
  virtual void exitAnnotation(P4Parser::AnnotationContext * /*ctx*/) override { }

  virtual void enterAnnotationBody(P4Parser::AnnotationBodyContext * /*ctx*/) override { }
  virtual void exitAnnotationBody(P4Parser::AnnotationBodyContext * /*ctx*/) override { }

  virtual void enterAnnotationToken(P4Parser::AnnotationTokenContext * /*ctx*/) override { }
  virtual void exitAnnotationToken(P4Parser::AnnotationTokenContext * /*ctx*/) override { }

  virtual void enterOptTrailingComma(P4Parser::OptTrailingCommaContext * /*ctx*/) override { }
  virtual void exitOptTrailingComma(P4Parser::OptTrailingCommaContext * /*ctx*/) override { }

  virtual void enterParameterList(P4Parser::ParameterListContext * /*ctx*/) override { }
  virtual void exitParameterList(P4Parser::ParameterListContext * /*ctx*/) override { }

  virtual void enterNonEmptyParameterList(P4Parser::NonEmptyParameterListContext * /*ctx*/) override { }
  virtual void exitNonEmptyParameterList(P4Parser::NonEmptyParameterListContext * /*ctx*/) override { }

  virtual void enterParameter(P4Parser::ParameterContext * /*ctx*/) override { }
  virtual void exitParameter(P4Parser::ParameterContext * /*ctx*/) override { }

  virtual void enterDirection(P4Parser::DirectionContext * /*ctx*/) override { }
  virtual void exitDirection(P4Parser::DirectionContext * /*ctx*/) override { }

  virtual void enterSpecializedTypeRef(P4Parser::SpecializedTypeRefContext * /*ctx*/) override { }
  virtual void exitSpecializedTypeRef(P4Parser::SpecializedTypeRefContext * /*ctx*/) override { }

  virtual void enterHeaderStackTypeRef(P4Parser::HeaderStackTypeRefContext * /*ctx*/) override { }
  virtual void exitHeaderStackTypeRef(P4Parser::HeaderStackTypeRefContext * /*ctx*/) override { }

  virtual void enterTypeNameRef(P4Parser::TypeNameRefContext * /*ctx*/) override { }
  virtual void exitTypeNameRef(P4Parser::TypeNameRefContext * /*ctx*/) override { }

  virtual void enterTupleTypeRef(P4Parser::TupleTypeRefContext * /*ctx*/) override { }
  virtual void exitTupleTypeRef(P4Parser::TupleTypeRefContext * /*ctx*/) override { }

  virtual void enterBaseTypeRef(P4Parser::BaseTypeRefContext * /*ctx*/) override { }
  virtual void exitBaseTypeRef(P4Parser::BaseTypeRefContext * /*ctx*/) override { }

  virtual void enterP4listTypeRef(P4Parser::P4listTypeRefContext * /*ctx*/) override { }
  virtual void exitP4listTypeRef(P4Parser::P4listTypeRefContext * /*ctx*/) override { }

  virtual void enterNamedType(P4Parser::NamedTypeContext * /*ctx*/) override { }
  virtual void exitNamedType(P4Parser::NamedTypeContext * /*ctx*/) override { }

  virtual void enterPrefixedType(P4Parser::PrefixedTypeContext * /*ctx*/) override { }
  virtual void exitPrefixedType(P4Parser::PrefixedTypeContext * /*ctx*/) override { }

  virtual void enterTypeName(P4Parser::TypeNameContext * /*ctx*/) override { }
  virtual void exitTypeName(P4Parser::TypeNameContext * /*ctx*/) override { }

  virtual void enterP4listType(P4Parser::P4listTypeContext * /*ctx*/) override { }
  virtual void exitP4listType(P4Parser::P4listTypeContext * /*ctx*/) override { }

  virtual void enterTupleType(P4Parser::TupleTypeContext * /*ctx*/) override { }
  virtual void exitTupleType(P4Parser::TupleTypeContext * /*ctx*/) override { }

  virtual void enterSpecializedType(P4Parser::SpecializedTypeContext * /*ctx*/) override { }
  virtual void exitSpecializedType(P4Parser::SpecializedTypeContext * /*ctx*/) override { }

  virtual void enterBaseType(P4Parser::BaseTypeContext * /*ctx*/) override { }
  virtual void exitBaseType(P4Parser::BaseTypeContext * /*ctx*/) override { }

  virtual void enterTypeOrVoid(P4Parser::TypeOrVoidContext * /*ctx*/) override { }
  virtual void exitTypeOrVoid(P4Parser::TypeOrVoidContext * /*ctx*/) override { }

  virtual void enterOptTypeParameters(P4Parser::OptTypeParametersContext * /*ctx*/) override { }
  virtual void exitOptTypeParameters(P4Parser::OptTypeParametersContext * /*ctx*/) override { }

  virtual void enterTypeParameters(P4Parser::TypeParametersContext * /*ctx*/) override { }
  virtual void exitTypeParameters(P4Parser::TypeParametersContext * /*ctx*/) override { }

  virtual void enterTypeParameterList(P4Parser::TypeParameterListContext * /*ctx*/) override { }
  virtual void exitTypeParameterList(P4Parser::TypeParameterListContext * /*ctx*/) override { }

  virtual void enterTypeArg(P4Parser::TypeArgContext * /*ctx*/) override { }
  virtual void exitTypeArg(P4Parser::TypeArgContext * /*ctx*/) override { }

  virtual void enterTypeArgumentList(P4Parser::TypeArgumentListContext * /*ctx*/) override { }
  virtual void exitTypeArgumentList(P4Parser::TypeArgumentListContext * /*ctx*/) override { }

  virtual void enterRealTypeArg(P4Parser::RealTypeArgContext * /*ctx*/) override { }
  virtual void exitRealTypeArg(P4Parser::RealTypeArgContext * /*ctx*/) override { }

  virtual void enterRealTypeArgumentList(P4Parser::RealTypeArgumentListContext * /*ctx*/) override { }
  virtual void exitRealTypeArgumentList(P4Parser::RealTypeArgumentListContext * /*ctx*/) override { }

  virtual void enterTypeDeclaration(P4Parser::TypeDeclarationContext * /*ctx*/) override { }
  virtual void exitTypeDeclaration(P4Parser::TypeDeclarationContext * /*ctx*/) override { }

  virtual void enterDerivedTypeDeclaration(P4Parser::DerivedTypeDeclarationContext * /*ctx*/) override { }
  virtual void exitDerivedTypeDeclaration(P4Parser::DerivedTypeDeclarationContext * /*ctx*/) override { }

  virtual void enterHeaderTypeDeclaration(P4Parser::HeaderTypeDeclarationContext * /*ctx*/) override { }
  virtual void exitHeaderTypeDeclaration(P4Parser::HeaderTypeDeclarationContext * /*ctx*/) override { }

  virtual void enterStructTypeDeclaration(P4Parser::StructTypeDeclarationContext * /*ctx*/) override { }
  virtual void exitStructTypeDeclaration(P4Parser::StructTypeDeclarationContext * /*ctx*/) override { }

  virtual void enterHeaderUnionDeclaration(P4Parser::HeaderUnionDeclarationContext * /*ctx*/) override { }
  virtual void exitHeaderUnionDeclaration(P4Parser::HeaderUnionDeclarationContext * /*ctx*/) override { }

  virtual void enterStructFieldList(P4Parser::StructFieldListContext * /*ctx*/) override { }
  virtual void exitStructFieldList(P4Parser::StructFieldListContext * /*ctx*/) override { }

  virtual void enterStructField(P4Parser::StructFieldContext * /*ctx*/) override { }
  virtual void exitStructField(P4Parser::StructFieldContext * /*ctx*/) override { }

  virtual void enterEnumDeclaration(P4Parser::EnumDeclarationContext * /*ctx*/) override { }
  virtual void exitEnumDeclaration(P4Parser::EnumDeclarationContext * /*ctx*/) override { }

  virtual void enterSpecifiedIdentifierList(P4Parser::SpecifiedIdentifierListContext * /*ctx*/) override { }
  virtual void exitSpecifiedIdentifierList(P4Parser::SpecifiedIdentifierListContext * /*ctx*/) override { }

  virtual void enterSpecifiedIdentifier(P4Parser::SpecifiedIdentifierContext * /*ctx*/) override { }
  virtual void exitSpecifiedIdentifier(P4Parser::SpecifiedIdentifierContext * /*ctx*/) override { }

  virtual void enterErrorDeclaration(P4Parser::ErrorDeclarationContext * /*ctx*/) override { }
  virtual void exitErrorDeclaration(P4Parser::ErrorDeclarationContext * /*ctx*/) override { }

  virtual void enterMatchKindDeclaration(P4Parser::MatchKindDeclarationContext * /*ctx*/) override { }
  virtual void exitMatchKindDeclaration(P4Parser::MatchKindDeclarationContext * /*ctx*/) override { }

  virtual void enterIdentifierList(P4Parser::IdentifierListContext * /*ctx*/) override { }
  virtual void exitIdentifierList(P4Parser::IdentifierListContext * /*ctx*/) override { }

  virtual void enterTypedefDeclaration(P4Parser::TypedefDeclarationContext * /*ctx*/) override { }
  virtual void exitTypedefDeclaration(P4Parser::TypedefDeclarationContext * /*ctx*/) override { }

  virtual void enterPackageTypeDeclaration(P4Parser::PackageTypeDeclarationContext * /*ctx*/) override { }
  virtual void exitPackageTypeDeclaration(P4Parser::PackageTypeDeclarationContext * /*ctx*/) override { }

  virtual void enterParserDeclaration(P4Parser::ParserDeclarationContext * /*ctx*/) override { }
  virtual void exitParserDeclaration(P4Parser::ParserDeclarationContext * /*ctx*/) override { }

  virtual void enterParserTypeDeclaration(P4Parser::ParserTypeDeclarationContext * /*ctx*/) override { }
  virtual void exitParserTypeDeclaration(P4Parser::ParserTypeDeclarationContext * /*ctx*/) override { }

  virtual void enterParserLocalElements(P4Parser::ParserLocalElementsContext * /*ctx*/) override { }
  virtual void exitParserLocalElements(P4Parser::ParserLocalElementsContext * /*ctx*/) override { }

  virtual void enterParserLocalElement(P4Parser::ParserLocalElementContext * /*ctx*/) override { }
  virtual void exitParserLocalElement(P4Parser::ParserLocalElementContext * /*ctx*/) override { }

  virtual void enterParserStates(P4Parser::ParserStatesContext * /*ctx*/) override { }
  virtual void exitParserStates(P4Parser::ParserStatesContext * /*ctx*/) override { }

  virtual void enterParserState(P4Parser::ParserStateContext * /*ctx*/) override { }
  virtual void exitParserState(P4Parser::ParserStateContext * /*ctx*/) override { }

  virtual void enterParserStatements(P4Parser::ParserStatementsContext * /*ctx*/) override { }
  virtual void exitParserStatements(P4Parser::ParserStatementsContext * /*ctx*/) override { }

  virtual void enterParserStatement(P4Parser::ParserStatementContext * /*ctx*/) override { }
  virtual void exitParserStatement(P4Parser::ParserStatementContext * /*ctx*/) override { }

  virtual void enterParserBlockStatement(P4Parser::ParserBlockStatementContext * /*ctx*/) override { }
  virtual void exitParserBlockStatement(P4Parser::ParserBlockStatementContext * /*ctx*/) override { }

  virtual void enterTransitionStatement(P4Parser::TransitionStatementContext * /*ctx*/) override { }
  virtual void exitTransitionStatement(P4Parser::TransitionStatementContext * /*ctx*/) override { }

  virtual void enterStateExpression(P4Parser::StateExpressionContext * /*ctx*/) override { }
  virtual void exitStateExpression(P4Parser::StateExpressionContext * /*ctx*/) override { }

  virtual void enterSelectExpression(P4Parser::SelectExpressionContext * /*ctx*/) override { }
  virtual void exitSelectExpression(P4Parser::SelectExpressionContext * /*ctx*/) override { }

  virtual void enterSelectCaseList(P4Parser::SelectCaseListContext * /*ctx*/) override { }
  virtual void exitSelectCaseList(P4Parser::SelectCaseListContext * /*ctx*/) override { }

  virtual void enterSelectCase(P4Parser::SelectCaseContext * /*ctx*/) override { }
  virtual void exitSelectCase(P4Parser::SelectCaseContext * /*ctx*/) override { }

  virtual void enterKeysetExpression(P4Parser::KeysetExpressionContext * /*ctx*/) override { }
  virtual void exitKeysetExpression(P4Parser::KeysetExpressionContext * /*ctx*/) override { }

  virtual void enterTupleKeysetExpression(P4Parser::TupleKeysetExpressionContext * /*ctx*/) override { }
  virtual void exitTupleKeysetExpression(P4Parser::TupleKeysetExpressionContext * /*ctx*/) override { }

  virtual void enterSimpleExpressionList(P4Parser::SimpleExpressionListContext * /*ctx*/) override { }
  virtual void exitSimpleExpressionList(P4Parser::SimpleExpressionListContext * /*ctx*/) override { }

  virtual void enterReducedSimpleKeysetExpression(P4Parser::ReducedSimpleKeysetExpressionContext * /*ctx*/) override { }
  virtual void exitReducedSimpleKeysetExpression(P4Parser::ReducedSimpleKeysetExpressionContext * /*ctx*/) override { }

  virtual void enterSimpleKeysetExpression(P4Parser::SimpleKeysetExpressionContext * /*ctx*/) override { }
  virtual void exitSimpleKeysetExpression(P4Parser::SimpleKeysetExpressionContext * /*ctx*/) override { }

  virtual void enterValueSetDeclaration(P4Parser::ValueSetDeclarationContext * /*ctx*/) override { }
  virtual void exitValueSetDeclaration(P4Parser::ValueSetDeclarationContext * /*ctx*/) override { }

  virtual void enterControlDeclaration(P4Parser::ControlDeclarationContext * /*ctx*/) override { }
  virtual void exitControlDeclaration(P4Parser::ControlDeclarationContext * /*ctx*/) override { }

  virtual void enterControlTypeDeclaration(P4Parser::ControlTypeDeclarationContext * /*ctx*/) override { }
  virtual void exitControlTypeDeclaration(P4Parser::ControlTypeDeclarationContext * /*ctx*/) override { }

  virtual void enterControlLocalDeclarations(P4Parser::ControlLocalDeclarationsContext * /*ctx*/) override { }
  virtual void exitControlLocalDeclarations(P4Parser::ControlLocalDeclarationsContext * /*ctx*/) override { }

  virtual void enterControlLocalDeclaration(P4Parser::ControlLocalDeclarationContext * /*ctx*/) override { }
  virtual void exitControlLocalDeclaration(P4Parser::ControlLocalDeclarationContext * /*ctx*/) override { }

  virtual void enterControlBody(P4Parser::ControlBodyContext * /*ctx*/) override { }
  virtual void exitControlBody(P4Parser::ControlBodyContext * /*ctx*/) override { }

  virtual void enterExternDeclaration(P4Parser::ExternDeclarationContext * /*ctx*/) override { }
  virtual void exitExternDeclaration(P4Parser::ExternDeclarationContext * /*ctx*/) override { }

  virtual void enterMethodPrototypes(P4Parser::MethodPrototypesContext * /*ctx*/) override { }
  virtual void exitMethodPrototypes(P4Parser::MethodPrototypesContext * /*ctx*/) override { }

  virtual void enterFunctionPrototype(P4Parser::FunctionPrototypeContext * /*ctx*/) override { }
  virtual void exitFunctionPrototype(P4Parser::FunctionPrototypeContext * /*ctx*/) override { }

  virtual void enterMethodPrototype(P4Parser::MethodPrototypeContext * /*ctx*/) override { }
  virtual void exitMethodPrototype(P4Parser::MethodPrototypeContext * /*ctx*/) override { }

  virtual void enterInstantiation(P4Parser::InstantiationContext * /*ctx*/) override { }
  virtual void exitInstantiation(P4Parser::InstantiationContext * /*ctx*/) override { }

  virtual void enterOptObjInitializer(P4Parser::OptObjInitializerContext * /*ctx*/) override { }
  virtual void exitOptObjInitializer(P4Parser::OptObjInitializerContext * /*ctx*/) override { }

  virtual void enterObjDeclarations(P4Parser::ObjDeclarationsContext * /*ctx*/) override { }
  virtual void exitObjDeclarations(P4Parser::ObjDeclarationsContext * /*ctx*/) override { }

  virtual void enterObjDeclaration(P4Parser::ObjDeclarationContext * /*ctx*/) override { }
  virtual void exitObjDeclaration(P4Parser::ObjDeclarationContext * /*ctx*/) override { }

  virtual void enterOptConstructorParameters(P4Parser::OptConstructorParametersContext * /*ctx*/) override { }
  virtual void exitOptConstructorParameters(P4Parser::OptConstructorParametersContext * /*ctx*/) override { }

  virtual void enterTableDeclaration(P4Parser::TableDeclarationContext * /*ctx*/) override { }
  virtual void exitTableDeclaration(P4Parser::TableDeclarationContext * /*ctx*/) override { }

  virtual void enterTablePropertyList(P4Parser::TablePropertyListContext * /*ctx*/) override { }
  virtual void exitTablePropertyList(P4Parser::TablePropertyListContext * /*ctx*/) override { }

  virtual void enterTableProperty(P4Parser::TablePropertyContext * /*ctx*/) override { }
  virtual void exitTableProperty(P4Parser::TablePropertyContext * /*ctx*/) override { }

  virtual void enterOptCONST(P4Parser::OptCONSTContext * /*ctx*/) override { }
  virtual void exitOptCONST(P4Parser::OptCONSTContext * /*ctx*/) override { }

  virtual void enterKeyElementList(P4Parser::KeyElementListContext * /*ctx*/) override { }
  virtual void exitKeyElementList(P4Parser::KeyElementListContext * /*ctx*/) override { }

  virtual void enterKeyElement(P4Parser::KeyElementContext * /*ctx*/) override { }
  virtual void exitKeyElement(P4Parser::KeyElementContext * /*ctx*/) override { }

  virtual void enterActionList(P4Parser::ActionListContext * /*ctx*/) override { }
  virtual void exitActionList(P4Parser::ActionListContext * /*ctx*/) override { }

  virtual void enterActionRef(P4Parser::ActionRefContext * /*ctx*/) override { }
  virtual void exitActionRef(P4Parser::ActionRefContext * /*ctx*/) override { }

  virtual void enterPrefixedNonTypeName(P4Parser::PrefixedNonTypeNameContext * /*ctx*/) override { }
  virtual void exitPrefixedNonTypeName(P4Parser::PrefixedNonTypeNameContext * /*ctx*/) override { }

  virtual void enterEntry(P4Parser::EntryContext * /*ctx*/) override { }
  virtual void exitEntry(P4Parser::EntryContext * /*ctx*/) override { }

  virtual void enterEntryPriority(P4Parser::EntryPriorityContext * /*ctx*/) override { }
  virtual void exitEntryPriority(P4Parser::EntryPriorityContext * /*ctx*/) override { }

  virtual void enterEntriesList(P4Parser::EntriesListContext * /*ctx*/) override { }
  virtual void exitEntriesList(P4Parser::EntriesListContext * /*ctx*/) override { }

  virtual void enterActionDeclaration(P4Parser::ActionDeclarationContext * /*ctx*/) override { }
  virtual void exitActionDeclaration(P4Parser::ActionDeclarationContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(P4Parser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(P4Parser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterVariableDeclarationWithoutSemicolon(P4Parser::VariableDeclarationWithoutSemicolonContext * /*ctx*/) override { }
  virtual void exitVariableDeclarationWithoutSemicolon(P4Parser::VariableDeclarationWithoutSemicolonContext * /*ctx*/) override { }

  virtual void enterConstantDeclaration(P4Parser::ConstantDeclarationContext * /*ctx*/) override { }
  virtual void exitConstantDeclaration(P4Parser::ConstantDeclarationContext * /*ctx*/) override { }

  virtual void enterDeclarator(P4Parser::DeclaratorContext * /*ctx*/) override { }
  virtual void exitDeclarator(P4Parser::DeclaratorContext * /*ctx*/) override { }

  virtual void enterOptInitializer(P4Parser::OptInitializerContext * /*ctx*/) override { }
  virtual void exitOptInitializer(P4Parser::OptInitializerContext * /*ctx*/) override { }

  virtual void enterInitializer(P4Parser::InitializerContext * /*ctx*/) override { }
  virtual void exitInitializer(P4Parser::InitializerContext * /*ctx*/) override { }

  virtual void enterFunctionDeclaration(P4Parser::FunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionDeclaration(P4Parser::FunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterArgumentList(P4Parser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(P4Parser::ArgumentListContext * /*ctx*/) override { }

  virtual void enterNonEmptyArgList(P4Parser::NonEmptyArgListContext * /*ctx*/) override { }
  virtual void exitNonEmptyArgList(P4Parser::NonEmptyArgListContext * /*ctx*/) override { }

  virtual void enterArgument(P4Parser::ArgumentContext * /*ctx*/) override { }
  virtual void exitArgument(P4Parser::ArgumentContext * /*ctx*/) override { }

  virtual void enterExpressionList(P4Parser::ExpressionListContext * /*ctx*/) override { }
  virtual void exitExpressionList(P4Parser::ExpressionListContext * /*ctx*/) override { }

  virtual void enterKvList(P4Parser::KvListContext * /*ctx*/) override { }
  virtual void exitKvList(P4Parser::KvListContext * /*ctx*/) override { }

  virtual void enterKvPair(P4Parser::KvPairContext * /*ctx*/) override { }
  virtual void exitKvPair(P4Parser::KvPairContext * /*ctx*/) override { }

  virtual void enterStatement(P4Parser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(P4Parser::StatementContext * /*ctx*/) override { }

  virtual void enterMethodCallStmt(P4Parser::MethodCallStmtContext * /*ctx*/) override { }
  virtual void exitMethodCallStmt(P4Parser::MethodCallStmtContext * /*ctx*/) override { }

  virtual void enterTypeArgsMethodCallStmt(P4Parser::TypeArgsMethodCallStmtContext * /*ctx*/) override { }
  virtual void exitTypeArgsMethodCallStmt(P4Parser::TypeArgsMethodCallStmtContext * /*ctx*/) override { }

  virtual void enterAssignmentStmt(P4Parser::AssignmentStmtContext * /*ctx*/) override { }
  virtual void exitAssignmentStmt(P4Parser::AssignmentStmtContext * /*ctx*/) override { }

  virtual void enterMulAssignStmt(P4Parser::MulAssignStmtContext * /*ctx*/) override { }
  virtual void exitMulAssignStmt(P4Parser::MulAssignStmtContext * /*ctx*/) override { }

  virtual void enterDivAssignStmt(P4Parser::DivAssignStmtContext * /*ctx*/) override { }
  virtual void exitDivAssignStmt(P4Parser::DivAssignStmtContext * /*ctx*/) override { }

  virtual void enterModAssignStmt(P4Parser::ModAssignStmtContext * /*ctx*/) override { }
  virtual void exitModAssignStmt(P4Parser::ModAssignStmtContext * /*ctx*/) override { }

  virtual void enterAddAssignStmt(P4Parser::AddAssignStmtContext * /*ctx*/) override { }
  virtual void exitAddAssignStmt(P4Parser::AddAssignStmtContext * /*ctx*/) override { }

  virtual void enterSubAssignStmt(P4Parser::SubAssignStmtContext * /*ctx*/) override { }
  virtual void exitSubAssignStmt(P4Parser::SubAssignStmtContext * /*ctx*/) override { }

  virtual void enterAddSatAssignStmt(P4Parser::AddSatAssignStmtContext * /*ctx*/) override { }
  virtual void exitAddSatAssignStmt(P4Parser::AddSatAssignStmtContext * /*ctx*/) override { }

  virtual void enterSubSatAssignStmt(P4Parser::SubSatAssignStmtContext * /*ctx*/) override { }
  virtual void exitSubSatAssignStmt(P4Parser::SubSatAssignStmtContext * /*ctx*/) override { }

  virtual void enterShlAssignStmt(P4Parser::ShlAssignStmtContext * /*ctx*/) override { }
  virtual void exitShlAssignStmt(P4Parser::ShlAssignStmtContext * /*ctx*/) override { }

  virtual void enterShrAssignStmt(P4Parser::ShrAssignStmtContext * /*ctx*/) override { }
  virtual void exitShrAssignStmt(P4Parser::ShrAssignStmtContext * /*ctx*/) override { }

  virtual void enterBandAssignStmt(P4Parser::BandAssignStmtContext * /*ctx*/) override { }
  virtual void exitBandAssignStmt(P4Parser::BandAssignStmtContext * /*ctx*/) override { }

  virtual void enterBorAssignStmt(P4Parser::BorAssignStmtContext * /*ctx*/) override { }
  virtual void exitBorAssignStmt(P4Parser::BorAssignStmtContext * /*ctx*/) override { }

  virtual void enterBxorAssignStmt(P4Parser::BxorAssignStmtContext * /*ctx*/) override { }
  virtual void exitBxorAssignStmt(P4Parser::BxorAssignStmtContext * /*ctx*/) override { }

  virtual void enterEmptyStatement(P4Parser::EmptyStatementContext * /*ctx*/) override { }
  virtual void exitEmptyStatement(P4Parser::EmptyStatementContext * /*ctx*/) override { }

  virtual void enterExitStatement(P4Parser::ExitStatementContext * /*ctx*/) override { }
  virtual void exitExitStatement(P4Parser::ExitStatementContext * /*ctx*/) override { }

  virtual void enterReturnStatement(P4Parser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(P4Parser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterConditionalStatement(P4Parser::ConditionalStatementContext * /*ctx*/) override { }
  virtual void exitConditionalStatement(P4Parser::ConditionalStatementContext * /*ctx*/) override { }

  virtual void enterBreakStatement(P4Parser::BreakStatementContext * /*ctx*/) override { }
  virtual void exitBreakStatement(P4Parser::BreakStatementContext * /*ctx*/) override { }

  virtual void enterContinueStatement(P4Parser::ContinueStatementContext * /*ctx*/) override { }
  virtual void exitContinueStatement(P4Parser::ContinueStatementContext * /*ctx*/) override { }

  virtual void enterDirectApplication(P4Parser::DirectApplicationContext * /*ctx*/) override { }
  virtual void exitDirectApplication(P4Parser::DirectApplicationContext * /*ctx*/) override { }

  virtual void enterBlockStatement(P4Parser::BlockStatementContext * /*ctx*/) override { }
  virtual void exitBlockStatement(P4Parser::BlockStatementContext * /*ctx*/) override { }

  virtual void enterStatOrDeclList(P4Parser::StatOrDeclListContext * /*ctx*/) override { }
  virtual void exitStatOrDeclList(P4Parser::StatOrDeclListContext * /*ctx*/) override { }

  virtual void enterStatementOrDeclaration(P4Parser::StatementOrDeclarationContext * /*ctx*/) override { }
  virtual void exitStatementOrDeclaration(P4Parser::StatementOrDeclarationContext * /*ctx*/) override { }

  virtual void enterSwitchStatement(P4Parser::SwitchStatementContext * /*ctx*/) override { }
  virtual void exitSwitchStatement(P4Parser::SwitchStatementContext * /*ctx*/) override { }

  virtual void enterSwitchCases(P4Parser::SwitchCasesContext * /*ctx*/) override { }
  virtual void exitSwitchCases(P4Parser::SwitchCasesContext * /*ctx*/) override { }

  virtual void enterSwitchCase(P4Parser::SwitchCaseContext * /*ctx*/) override { }
  virtual void exitSwitchCase(P4Parser::SwitchCaseContext * /*ctx*/) override { }

  virtual void enterSwitchLabel(P4Parser::SwitchLabelContext * /*ctx*/) override { }
  virtual void exitSwitchLabel(P4Parser::SwitchLabelContext * /*ctx*/) override { }

  virtual void enterForStatement(P4Parser::ForStatementContext * /*ctx*/) override { }
  virtual void exitForStatement(P4Parser::ForStatementContext * /*ctx*/) override { }

  virtual void enterForInitStatements(P4Parser::ForInitStatementsContext * /*ctx*/) override { }
  virtual void exitForInitStatements(P4Parser::ForInitStatementsContext * /*ctx*/) override { }

  virtual void enterDeclOrAssignmentOrMethodCallStatement(P4Parser::DeclOrAssignmentOrMethodCallStatementContext * /*ctx*/) override { }
  virtual void exitDeclOrAssignmentOrMethodCallStatement(P4Parser::DeclOrAssignmentOrMethodCallStatementContext * /*ctx*/) override { }

  virtual void enterAssignmentOrMethodCallStatementWithoutSemicolon(P4Parser::AssignmentOrMethodCallStatementWithoutSemicolonContext * /*ctx*/) override { }
  virtual void exitAssignmentOrMethodCallStatementWithoutSemicolon(P4Parser::AssignmentOrMethodCallStatementWithoutSemicolonContext * /*ctx*/) override { }

  virtual void enterForUpdateStatements(P4Parser::ForUpdateStatementsContext * /*ctx*/) override { }
  virtual void exitForUpdateStatements(P4Parser::ForUpdateStatementsContext * /*ctx*/) override { }

  virtual void enterForCollectionExpr(P4Parser::ForCollectionExprContext * /*ctx*/) override { }
  virtual void exitForCollectionExpr(P4Parser::ForCollectionExprContext * /*ctx*/) override { }

  virtual void enterMemberLvalue(P4Parser::MemberLvalueContext * /*ctx*/) override { }
  virtual void exitMemberLvalue(P4Parser::MemberLvalueContext * /*ctx*/) override { }

  virtual void enterIndexLvalue(P4Parser::IndexLvalueContext * /*ctx*/) override { }
  virtual void exitIndexLvalue(P4Parser::IndexLvalueContext * /*ctx*/) override { }

  virtual void enterParenLvalue(P4Parser::ParenLvalueContext * /*ctx*/) override { }
  virtual void exitParenLvalue(P4Parser::ParenLvalueContext * /*ctx*/) override { }

  virtual void enterPlusSliceLvalue(P4Parser::PlusSliceLvalueContext * /*ctx*/) override { }
  virtual void exitPlusSliceLvalue(P4Parser::PlusSliceLvalueContext * /*ctx*/) override { }

  virtual void enterPathLvalue(P4Parser::PathLvalueContext * /*ctx*/) override { }
  virtual void exitPathLvalue(P4Parser::PathLvalueContext * /*ctx*/) override { }

  virtual void enterSliceLvalue(P4Parser::SliceLvalueContext * /*ctx*/) override { }
  virtual void exitSliceLvalue(P4Parser::SliceLvalueContext * /*ctx*/) override { }

  virtual void enterThisLvalue(P4Parser::ThisLvalueContext * /*ctx*/) override { }
  virtual void exitThisLvalue(P4Parser::ThisLvalueContext * /*ctx*/) override { }

  virtual void enterThisExpr(P4Parser::ThisExprContext * /*ctx*/) override { }
  virtual void exitThisExpr(P4Parser::ThisExprContext * /*ctx*/) override { }

  virtual void enterStructDotsExpr(P4Parser::StructDotsExprContext * /*ctx*/) override { }
  virtual void exitStructDotsExpr(P4Parser::StructDotsExprContext * /*ctx*/) override { }

  virtual void enterIntegerExpr(P4Parser::IntegerExprContext * /*ctx*/) override { }
  virtual void exitIntegerExpr(P4Parser::IntegerExprContext * /*ctx*/) override { }

  virtual void enterModExpr(P4Parser::ModExprContext * /*ctx*/) override { }
  virtual void exitModExpr(P4Parser::ModExprContext * /*ctx*/) override { }

  virtual void enterCastExpr(P4Parser::CastExprContext * /*ctx*/) override { }
  virtual void exitCastExpr(P4Parser::CastExprContext * /*ctx*/) override { }

  virtual void enterTrueExpr(P4Parser::TrueExprContext * /*ctx*/) override { }
  virtual void exitTrueExpr(P4Parser::TrueExprContext * /*ctx*/) override { }

  virtual void enterSubExpr(P4Parser::SubExprContext * /*ctx*/) override { }
  virtual void exitSubExpr(P4Parser::SubExprContext * /*ctx*/) override { }

  virtual void enterBandExpr(P4Parser::BandExprContext * /*ctx*/) override { }
  virtual void exitBandExpr(P4Parser::BandExprContext * /*ctx*/) override { }

  virtual void enterParenExpr(P4Parser::ParenExprContext * /*ctx*/) override { }
  virtual void exitParenExpr(P4Parser::ParenExprContext * /*ctx*/) override { }

  virtual void enterConcatExpr(P4Parser::ConcatExprContext * /*ctx*/) override { }
  virtual void exitConcatExpr(P4Parser::ConcatExprContext * /*ctx*/) override { }

  virtual void enterNeqExpr(P4Parser::NeqExprContext * /*ctx*/) override { }
  virtual void exitNeqExpr(P4Parser::NeqExprContext * /*ctx*/) override { }

  virtual void enterTypeCallExpr(P4Parser::TypeCallExprContext * /*ctx*/) override { }
  virtual void exitTypeCallExpr(P4Parser::TypeCallExprContext * /*ctx*/) override { }

  virtual void enterGrtExpr(P4Parser::GrtExprContext * /*ctx*/) override { }
  virtual void exitGrtExpr(P4Parser::GrtExprContext * /*ctx*/) override { }

  virtual void enterMethodCallExpr(P4Parser::MethodCallExprContext * /*ctx*/) override { }
  virtual void exitMethodCallExpr(P4Parser::MethodCallExprContext * /*ctx*/) override { }

  virtual void enterLandExpr(P4Parser::LandExprContext * /*ctx*/) override { }
  virtual void exitLandExpr(P4Parser::LandExprContext * /*ctx*/) override { }

  virtual void enterTernaryExpr(P4Parser::TernaryExprContext * /*ctx*/) override { }
  virtual void exitTernaryExpr(P4Parser::TernaryExprContext * /*ctx*/) override { }

  virtual void enterLorExpr(P4Parser::LorExprContext * /*ctx*/) override { }
  virtual void exitLorExpr(P4Parser::LorExprContext * /*ctx*/) override { }

  virtual void enterStructExpr(P4Parser::StructExprContext * /*ctx*/) override { }
  virtual void exitStructExpr(P4Parser::StructExprContext * /*ctx*/) override { }

  virtual void enterMulExpr(P4Parser::MulExprContext * /*ctx*/) override { }
  virtual void exitMulExpr(P4Parser::MulExprContext * /*ctx*/) override { }

  virtual void enterDivExpr(P4Parser::DivExprContext * /*ctx*/) override { }
  virtual void exitDivExpr(P4Parser::DivExprContext * /*ctx*/) override { }

  virtual void enterFalseExpr(P4Parser::FalseExprContext * /*ctx*/) override { }
  virtual void exitFalseExpr(P4Parser::FalseExprContext * /*ctx*/) override { }

  virtual void enterListExpr(P4Parser::ListExprContext * /*ctx*/) override { }
  virtual void exitListExpr(P4Parser::ListExprContext * /*ctx*/) override { }

  virtual void enterShrExpr(P4Parser::ShrExprContext * /*ctx*/) override { }
  virtual void exitShrExpr(P4Parser::ShrExprContext * /*ctx*/) override { }

  virtual void enterConstructorCallExpr(P4Parser::ConstructorCallExprContext * /*ctx*/) override { }
  virtual void exitConstructorCallExpr(P4Parser::ConstructorCallExprContext * /*ctx*/) override { }

  virtual void enterStringLiteralExpr(P4Parser::StringLiteralExprContext * /*ctx*/) override { }
  virtual void exitStringLiteralExpr(P4Parser::StringLiteralExprContext * /*ctx*/) override { }

  virtual void enterInvalidExpr(P4Parser::InvalidExprContext * /*ctx*/) override { }
  virtual void exitInvalidExpr(P4Parser::InvalidExprContext * /*ctx*/) override { }

  virtual void enterLnotExpr(P4Parser::LnotExprContext * /*ctx*/) override { }
  virtual void exitLnotExpr(P4Parser::LnotExprContext * /*ctx*/) override { }

  virtual void enterMemberExpr(P4Parser::MemberExprContext * /*ctx*/) override { }
  virtual void exitMemberExpr(P4Parser::MemberExprContext * /*ctx*/) override { }

  virtual void enterPlusSliceExpr(P4Parser::PlusSliceExprContext * /*ctx*/) override { }
  virtual void exitPlusSliceExpr(P4Parser::PlusSliceExprContext * /*ctx*/) override { }

  virtual void enterAddSatExpr(P4Parser::AddSatExprContext * /*ctx*/) override { }
  virtual void exitAddSatExpr(P4Parser::AddSatExprContext * /*ctx*/) override { }

  virtual void enterArrayIndexExpr(P4Parser::ArrayIndexExprContext * /*ctx*/) override { }
  virtual void exitArrayIndexExpr(P4Parser::ArrayIndexExprContext * /*ctx*/) override { }

  virtual void enterUplusExpr(P4Parser::UplusExprContext * /*ctx*/) override { }
  virtual void exitUplusExpr(P4Parser::UplusExprContext * /*ctx*/) override { }

  virtual void enterSliceExpr(P4Parser::SliceExprContext * /*ctx*/) override { }
  virtual void exitSliceExpr(P4Parser::SliceExprContext * /*ctx*/) override { }

  virtual void enterDotsExpr(P4Parser::DotsExprContext * /*ctx*/) override { }
  virtual void exitDotsExpr(P4Parser::DotsExprContext * /*ctx*/) override { }

  virtual void enterBorExpr(P4Parser::BorExprContext * /*ctx*/) override { }
  virtual void exitBorExpr(P4Parser::BorExprContext * /*ctx*/) override { }

  virtual void enterErrorMemberExpr(P4Parser::ErrorMemberExprContext * /*ctx*/) override { }
  virtual void exitErrorMemberExpr(P4Parser::ErrorMemberExprContext * /*ctx*/) override { }

  virtual void enterEqExpr(P4Parser::EqExprContext * /*ctx*/) override { }
  virtual void exitEqExpr(P4Parser::EqExprContext * /*ctx*/) override { }

  virtual void enterAddExpr(P4Parser::AddExprContext * /*ctx*/) override { }
  virtual void exitAddExpr(P4Parser::AddExprContext * /*ctx*/) override { }

  virtual void enterLssExpr(P4Parser::LssExprContext * /*ctx*/) override { }
  virtual void exitLssExpr(P4Parser::LssExprContext * /*ctx*/) override { }

  virtual void enterCmplExpr(P4Parser::CmplExprContext * /*ctx*/) override { }
  virtual void exitCmplExpr(P4Parser::CmplExprContext * /*ctx*/) override { }

  virtual void enterNegExpr(P4Parser::NegExprContext * /*ctx*/) override { }
  virtual void exitNegExpr(P4Parser::NegExprContext * /*ctx*/) override { }

  virtual void enterPathExpr(P4Parser::PathExprContext * /*ctx*/) override { }
  virtual void exitPathExpr(P4Parser::PathExprContext * /*ctx*/) override { }

  virtual void enterLeqExpr(P4Parser::LeqExprContext * /*ctx*/) override { }
  virtual void exitLeqExpr(P4Parser::LeqExprContext * /*ctx*/) override { }

  virtual void enterShlExpr(P4Parser::ShlExprContext * /*ctx*/) override { }
  virtual void exitShlExpr(P4Parser::ShlExprContext * /*ctx*/) override { }

  virtual void enterGeqExpr(P4Parser::GeqExprContext * /*ctx*/) override { }
  virtual void exitGeqExpr(P4Parser::GeqExprContext * /*ctx*/) override { }

  virtual void enterSubSatExpr(P4Parser::SubSatExprContext * /*ctx*/) override { }
  virtual void exitSubSatExpr(P4Parser::SubSatExprContext * /*ctx*/) override { }

  virtual void enterBxorExpr(P4Parser::BxorExprContext * /*ctx*/) override { }
  virtual void exitBxorExpr(P4Parser::BxorExprContext * /*ctx*/) override { }

  virtual void enterNonBraceExpression(P4Parser::NonBraceExpressionContext * /*ctx*/) override { }
  virtual void exitNonBraceExpression(P4Parser::NonBraceExpressionContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

