
// Generated from P4Parser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "P4Parser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by P4Parser.
 */
class  P4ParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(P4Parser::ProgramContext *ctx) = 0;
  virtual void exitProgram(P4Parser::ProgramContext *ctx) = 0;

  virtual void enterAnnExpressionList(P4Parser::AnnExpressionListContext *ctx) = 0;
  virtual void exitAnnExpressionList(P4Parser::AnnExpressionListContext *ctx) = 0;

  virtual void enterAnnKvList(P4Parser::AnnKvListContext *ctx) = 0;
  virtual void exitAnnKvList(P4Parser::AnnKvListContext *ctx) = 0;

  virtual void enterAnnIntegerList(P4Parser::AnnIntegerListContext *ctx) = 0;
  virtual void exitAnnIntegerList(P4Parser::AnnIntegerListContext *ctx) = 0;

  virtual void enterAnnIntOrStrList(P4Parser::AnnIntOrStrListContext *ctx) = 0;
  virtual void exitAnnIntOrStrList(P4Parser::AnnIntOrStrListContext *ctx) = 0;

  virtual void enterAnnStringList(P4Parser::AnnStringListContext *ctx) = 0;
  virtual void exitAnnStringList(P4Parser::AnnStringListContext *ctx) = 0;

  virtual void enterAnnExpression(P4Parser::AnnExpressionContext *ctx) = 0;
  virtual void exitAnnExpression(P4Parser::AnnExpressionContext *ctx) = 0;

  virtual void enterAnnInteger(P4Parser::AnnIntegerContext *ctx) = 0;
  virtual void exitAnnInteger(P4Parser::AnnIntegerContext *ctx) = 0;

  virtual void enterAnnIntOrStr(P4Parser::AnnIntOrStrContext *ctx) = 0;
  virtual void exitAnnIntOrStr(P4Parser::AnnIntOrStrContext *ctx) = 0;

  virtual void enterAnnStringLiteral(P4Parser::AnnStringLiteralContext *ctx) = 0;
  virtual void exitAnnStringLiteral(P4Parser::AnnStringLiteralContext *ctx) = 0;

  virtual void enterAnnExpressionPair(P4Parser::AnnExpressionPairContext *ctx) = 0;
  virtual void exitAnnExpressionPair(P4Parser::AnnExpressionPairContext *ctx) = 0;

  virtual void enterAnnIntegerPair(P4Parser::AnnIntegerPairContext *ctx) = 0;
  virtual void exitAnnIntegerPair(P4Parser::AnnIntegerPairContext *ctx) = 0;

  virtual void enterAnnStringPair(P4Parser::AnnStringPairContext *ctx) = 0;
  virtual void exitAnnStringPair(P4Parser::AnnStringPairContext *ctx) = 0;

  virtual void enterAnnExpressionTriple(P4Parser::AnnExpressionTripleContext *ctx) = 0;
  virtual void exitAnnExpressionTriple(P4Parser::AnnExpressionTripleContext *ctx) = 0;

  virtual void enterAnnIntegerTriple(P4Parser::AnnIntegerTripleContext *ctx) = 0;
  virtual void exitAnnIntegerTriple(P4Parser::AnnIntegerTripleContext *ctx) = 0;

  virtual void enterAnnStringTriple(P4Parser::AnnStringTripleContext *ctx) = 0;
  virtual void exitAnnStringTriple(P4Parser::AnnStringTripleContext *ctx) = 0;

  virtual void enterAnnP4rtTranslation(P4Parser::AnnP4rtTranslationContext *ctx) = 0;
  virtual void exitAnnP4rtTranslation(P4Parser::AnnP4rtTranslationContext *ctx) = 0;

  virtual void enterIntOrStr(P4Parser::IntOrStrContext *ctx) = 0;
  virtual void exitIntOrStr(P4Parser::IntOrStrContext *ctx) = 0;

  virtual void enterP4rtControllerType(P4Parser::P4rtControllerTypeContext *ctx) = 0;
  virtual void exitP4rtControllerType(P4Parser::P4rtControllerTypeContext *ctx) = 0;

  virtual void enterDeclaration(P4Parser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(P4Parser::DeclarationContext *ctx) = 0;

  virtual void enterNonTypeName(P4Parser::NonTypeNameContext *ctx) = 0;
  virtual void exitNonTypeName(P4Parser::NonTypeNameContext *ctx) = 0;

  virtual void enterName(P4Parser::NameContext *ctx) = 0;
  virtual void exitName(P4Parser::NameContext *ctx) = 0;

  virtual void enterNonTableKwName(P4Parser::NonTableKwNameContext *ctx) = 0;
  virtual void exitNonTableKwName(P4Parser::NonTableKwNameContext *ctx) = 0;

  virtual void enterAnnotationName(P4Parser::AnnotationNameContext *ctx) = 0;
  virtual void exitAnnotationName(P4Parser::AnnotationNameContext *ctx) = 0;

  virtual void enterOptAnnotations(P4Parser::OptAnnotationsContext *ctx) = 0;
  virtual void exitOptAnnotations(P4Parser::OptAnnotationsContext *ctx) = 0;

  virtual void enterAnnotations(P4Parser::AnnotationsContext *ctx) = 0;
  virtual void exitAnnotations(P4Parser::AnnotationsContext *ctx) = 0;

  virtual void enterAnnotation(P4Parser::AnnotationContext *ctx) = 0;
  virtual void exitAnnotation(P4Parser::AnnotationContext *ctx) = 0;

  virtual void enterAnnotationBody(P4Parser::AnnotationBodyContext *ctx) = 0;
  virtual void exitAnnotationBody(P4Parser::AnnotationBodyContext *ctx) = 0;

  virtual void enterAnnotationToken(P4Parser::AnnotationTokenContext *ctx) = 0;
  virtual void exitAnnotationToken(P4Parser::AnnotationTokenContext *ctx) = 0;

  virtual void enterOptTrailingComma(P4Parser::OptTrailingCommaContext *ctx) = 0;
  virtual void exitOptTrailingComma(P4Parser::OptTrailingCommaContext *ctx) = 0;

  virtual void enterParameterList(P4Parser::ParameterListContext *ctx) = 0;
  virtual void exitParameterList(P4Parser::ParameterListContext *ctx) = 0;

  virtual void enterNonEmptyParameterList(P4Parser::NonEmptyParameterListContext *ctx) = 0;
  virtual void exitNonEmptyParameterList(P4Parser::NonEmptyParameterListContext *ctx) = 0;

  virtual void enterParameter(P4Parser::ParameterContext *ctx) = 0;
  virtual void exitParameter(P4Parser::ParameterContext *ctx) = 0;

  virtual void enterDirection(P4Parser::DirectionContext *ctx) = 0;
  virtual void exitDirection(P4Parser::DirectionContext *ctx) = 0;

  virtual void enterSpecializedTypeRef(P4Parser::SpecializedTypeRefContext *ctx) = 0;
  virtual void exitSpecializedTypeRef(P4Parser::SpecializedTypeRefContext *ctx) = 0;

  virtual void enterHeaderStackTypeRef(P4Parser::HeaderStackTypeRefContext *ctx) = 0;
  virtual void exitHeaderStackTypeRef(P4Parser::HeaderStackTypeRefContext *ctx) = 0;

  virtual void enterTypeNameRef(P4Parser::TypeNameRefContext *ctx) = 0;
  virtual void exitTypeNameRef(P4Parser::TypeNameRefContext *ctx) = 0;

  virtual void enterTupleTypeRef(P4Parser::TupleTypeRefContext *ctx) = 0;
  virtual void exitTupleTypeRef(P4Parser::TupleTypeRefContext *ctx) = 0;

  virtual void enterBaseTypeRef(P4Parser::BaseTypeRefContext *ctx) = 0;
  virtual void exitBaseTypeRef(P4Parser::BaseTypeRefContext *ctx) = 0;

  virtual void enterP4listTypeRef(P4Parser::P4listTypeRefContext *ctx) = 0;
  virtual void exitP4listTypeRef(P4Parser::P4listTypeRefContext *ctx) = 0;

  virtual void enterNamedType(P4Parser::NamedTypeContext *ctx) = 0;
  virtual void exitNamedType(P4Parser::NamedTypeContext *ctx) = 0;

  virtual void enterPrefixedType(P4Parser::PrefixedTypeContext *ctx) = 0;
  virtual void exitPrefixedType(P4Parser::PrefixedTypeContext *ctx) = 0;

  virtual void enterTypeName(P4Parser::TypeNameContext *ctx) = 0;
  virtual void exitTypeName(P4Parser::TypeNameContext *ctx) = 0;

  virtual void enterP4listType(P4Parser::P4listTypeContext *ctx) = 0;
  virtual void exitP4listType(P4Parser::P4listTypeContext *ctx) = 0;

  virtual void enterTupleType(P4Parser::TupleTypeContext *ctx) = 0;
  virtual void exitTupleType(P4Parser::TupleTypeContext *ctx) = 0;

  virtual void enterSpecializedType(P4Parser::SpecializedTypeContext *ctx) = 0;
  virtual void exitSpecializedType(P4Parser::SpecializedTypeContext *ctx) = 0;

  virtual void enterBaseType(P4Parser::BaseTypeContext *ctx) = 0;
  virtual void exitBaseType(P4Parser::BaseTypeContext *ctx) = 0;

  virtual void enterTypeOrVoid(P4Parser::TypeOrVoidContext *ctx) = 0;
  virtual void exitTypeOrVoid(P4Parser::TypeOrVoidContext *ctx) = 0;

  virtual void enterOptTypeParameters(P4Parser::OptTypeParametersContext *ctx) = 0;
  virtual void exitOptTypeParameters(P4Parser::OptTypeParametersContext *ctx) = 0;

  virtual void enterTypeParameters(P4Parser::TypeParametersContext *ctx) = 0;
  virtual void exitTypeParameters(P4Parser::TypeParametersContext *ctx) = 0;

  virtual void enterTypeParameterList(P4Parser::TypeParameterListContext *ctx) = 0;
  virtual void exitTypeParameterList(P4Parser::TypeParameterListContext *ctx) = 0;

  virtual void enterTypeArg(P4Parser::TypeArgContext *ctx) = 0;
  virtual void exitTypeArg(P4Parser::TypeArgContext *ctx) = 0;

  virtual void enterTypeArgumentList(P4Parser::TypeArgumentListContext *ctx) = 0;
  virtual void exitTypeArgumentList(P4Parser::TypeArgumentListContext *ctx) = 0;

  virtual void enterRealTypeArg(P4Parser::RealTypeArgContext *ctx) = 0;
  virtual void exitRealTypeArg(P4Parser::RealTypeArgContext *ctx) = 0;

  virtual void enterRealTypeArgumentList(P4Parser::RealTypeArgumentListContext *ctx) = 0;
  virtual void exitRealTypeArgumentList(P4Parser::RealTypeArgumentListContext *ctx) = 0;

  virtual void enterTypeDeclaration(P4Parser::TypeDeclarationContext *ctx) = 0;
  virtual void exitTypeDeclaration(P4Parser::TypeDeclarationContext *ctx) = 0;

  virtual void enterDerivedTypeDeclaration(P4Parser::DerivedTypeDeclarationContext *ctx) = 0;
  virtual void exitDerivedTypeDeclaration(P4Parser::DerivedTypeDeclarationContext *ctx) = 0;

  virtual void enterHeaderTypeDeclaration(P4Parser::HeaderTypeDeclarationContext *ctx) = 0;
  virtual void exitHeaderTypeDeclaration(P4Parser::HeaderTypeDeclarationContext *ctx) = 0;

  virtual void enterStructTypeDeclaration(P4Parser::StructTypeDeclarationContext *ctx) = 0;
  virtual void exitStructTypeDeclaration(P4Parser::StructTypeDeclarationContext *ctx) = 0;

  virtual void enterHeaderUnionDeclaration(P4Parser::HeaderUnionDeclarationContext *ctx) = 0;
  virtual void exitHeaderUnionDeclaration(P4Parser::HeaderUnionDeclarationContext *ctx) = 0;

  virtual void enterStructFieldList(P4Parser::StructFieldListContext *ctx) = 0;
  virtual void exitStructFieldList(P4Parser::StructFieldListContext *ctx) = 0;

  virtual void enterStructField(P4Parser::StructFieldContext *ctx) = 0;
  virtual void exitStructField(P4Parser::StructFieldContext *ctx) = 0;

  virtual void enterEnumDeclaration(P4Parser::EnumDeclarationContext *ctx) = 0;
  virtual void exitEnumDeclaration(P4Parser::EnumDeclarationContext *ctx) = 0;

  virtual void enterSpecifiedIdentifierList(P4Parser::SpecifiedIdentifierListContext *ctx) = 0;
  virtual void exitSpecifiedIdentifierList(P4Parser::SpecifiedIdentifierListContext *ctx) = 0;

  virtual void enterSpecifiedIdentifier(P4Parser::SpecifiedIdentifierContext *ctx) = 0;
  virtual void exitSpecifiedIdentifier(P4Parser::SpecifiedIdentifierContext *ctx) = 0;

  virtual void enterErrorDeclaration(P4Parser::ErrorDeclarationContext *ctx) = 0;
  virtual void exitErrorDeclaration(P4Parser::ErrorDeclarationContext *ctx) = 0;

  virtual void enterMatchKindDeclaration(P4Parser::MatchKindDeclarationContext *ctx) = 0;
  virtual void exitMatchKindDeclaration(P4Parser::MatchKindDeclarationContext *ctx) = 0;

  virtual void enterIdentifierList(P4Parser::IdentifierListContext *ctx) = 0;
  virtual void exitIdentifierList(P4Parser::IdentifierListContext *ctx) = 0;

  virtual void enterTypedefDeclaration(P4Parser::TypedefDeclarationContext *ctx) = 0;
  virtual void exitTypedefDeclaration(P4Parser::TypedefDeclarationContext *ctx) = 0;

  virtual void enterPackageTypeDeclaration(P4Parser::PackageTypeDeclarationContext *ctx) = 0;
  virtual void exitPackageTypeDeclaration(P4Parser::PackageTypeDeclarationContext *ctx) = 0;

  virtual void enterParserDeclaration(P4Parser::ParserDeclarationContext *ctx) = 0;
  virtual void exitParserDeclaration(P4Parser::ParserDeclarationContext *ctx) = 0;

  virtual void enterParserTypeDeclaration(P4Parser::ParserTypeDeclarationContext *ctx) = 0;
  virtual void exitParserTypeDeclaration(P4Parser::ParserTypeDeclarationContext *ctx) = 0;

  virtual void enterParserLocalElements(P4Parser::ParserLocalElementsContext *ctx) = 0;
  virtual void exitParserLocalElements(P4Parser::ParserLocalElementsContext *ctx) = 0;

  virtual void enterParserLocalElement(P4Parser::ParserLocalElementContext *ctx) = 0;
  virtual void exitParserLocalElement(P4Parser::ParserLocalElementContext *ctx) = 0;

  virtual void enterParserStates(P4Parser::ParserStatesContext *ctx) = 0;
  virtual void exitParserStates(P4Parser::ParserStatesContext *ctx) = 0;

  virtual void enterParserState(P4Parser::ParserStateContext *ctx) = 0;
  virtual void exitParserState(P4Parser::ParserStateContext *ctx) = 0;

  virtual void enterParserStatements(P4Parser::ParserStatementsContext *ctx) = 0;
  virtual void exitParserStatements(P4Parser::ParserStatementsContext *ctx) = 0;

  virtual void enterParserStatement(P4Parser::ParserStatementContext *ctx) = 0;
  virtual void exitParserStatement(P4Parser::ParserStatementContext *ctx) = 0;

  virtual void enterParserBlockStatement(P4Parser::ParserBlockStatementContext *ctx) = 0;
  virtual void exitParserBlockStatement(P4Parser::ParserBlockStatementContext *ctx) = 0;

  virtual void enterTransitionStatement(P4Parser::TransitionStatementContext *ctx) = 0;
  virtual void exitTransitionStatement(P4Parser::TransitionStatementContext *ctx) = 0;

  virtual void enterStateExpression(P4Parser::StateExpressionContext *ctx) = 0;
  virtual void exitStateExpression(P4Parser::StateExpressionContext *ctx) = 0;

  virtual void enterSelectExpression(P4Parser::SelectExpressionContext *ctx) = 0;
  virtual void exitSelectExpression(P4Parser::SelectExpressionContext *ctx) = 0;

  virtual void enterSelectCaseList(P4Parser::SelectCaseListContext *ctx) = 0;
  virtual void exitSelectCaseList(P4Parser::SelectCaseListContext *ctx) = 0;

  virtual void enterSelectCase(P4Parser::SelectCaseContext *ctx) = 0;
  virtual void exitSelectCase(P4Parser::SelectCaseContext *ctx) = 0;

  virtual void enterKeysetExpression(P4Parser::KeysetExpressionContext *ctx) = 0;
  virtual void exitKeysetExpression(P4Parser::KeysetExpressionContext *ctx) = 0;

  virtual void enterTupleKeysetExpression(P4Parser::TupleKeysetExpressionContext *ctx) = 0;
  virtual void exitTupleKeysetExpression(P4Parser::TupleKeysetExpressionContext *ctx) = 0;

  virtual void enterSimpleExpressionList(P4Parser::SimpleExpressionListContext *ctx) = 0;
  virtual void exitSimpleExpressionList(P4Parser::SimpleExpressionListContext *ctx) = 0;

  virtual void enterReducedSimpleKeysetExpression(P4Parser::ReducedSimpleKeysetExpressionContext *ctx) = 0;
  virtual void exitReducedSimpleKeysetExpression(P4Parser::ReducedSimpleKeysetExpressionContext *ctx) = 0;

  virtual void enterSimpleKeysetExpression(P4Parser::SimpleKeysetExpressionContext *ctx) = 0;
  virtual void exitSimpleKeysetExpression(P4Parser::SimpleKeysetExpressionContext *ctx) = 0;

  virtual void enterValueSetDeclaration(P4Parser::ValueSetDeclarationContext *ctx) = 0;
  virtual void exitValueSetDeclaration(P4Parser::ValueSetDeclarationContext *ctx) = 0;

  virtual void enterControlDeclaration(P4Parser::ControlDeclarationContext *ctx) = 0;
  virtual void exitControlDeclaration(P4Parser::ControlDeclarationContext *ctx) = 0;

  virtual void enterControlTypeDeclaration(P4Parser::ControlTypeDeclarationContext *ctx) = 0;
  virtual void exitControlTypeDeclaration(P4Parser::ControlTypeDeclarationContext *ctx) = 0;

  virtual void enterControlLocalDeclarations(P4Parser::ControlLocalDeclarationsContext *ctx) = 0;
  virtual void exitControlLocalDeclarations(P4Parser::ControlLocalDeclarationsContext *ctx) = 0;

  virtual void enterControlLocalDeclaration(P4Parser::ControlLocalDeclarationContext *ctx) = 0;
  virtual void exitControlLocalDeclaration(P4Parser::ControlLocalDeclarationContext *ctx) = 0;

  virtual void enterControlBody(P4Parser::ControlBodyContext *ctx) = 0;
  virtual void exitControlBody(P4Parser::ControlBodyContext *ctx) = 0;

  virtual void enterExternDeclaration(P4Parser::ExternDeclarationContext *ctx) = 0;
  virtual void exitExternDeclaration(P4Parser::ExternDeclarationContext *ctx) = 0;

  virtual void enterMethodPrototypes(P4Parser::MethodPrototypesContext *ctx) = 0;
  virtual void exitMethodPrototypes(P4Parser::MethodPrototypesContext *ctx) = 0;

  virtual void enterFunctionPrototype(P4Parser::FunctionPrototypeContext *ctx) = 0;
  virtual void exitFunctionPrototype(P4Parser::FunctionPrototypeContext *ctx) = 0;

  virtual void enterMethodPrototype(P4Parser::MethodPrototypeContext *ctx) = 0;
  virtual void exitMethodPrototype(P4Parser::MethodPrototypeContext *ctx) = 0;

  virtual void enterInstantiation(P4Parser::InstantiationContext *ctx) = 0;
  virtual void exitInstantiation(P4Parser::InstantiationContext *ctx) = 0;

  virtual void enterOptObjInitializer(P4Parser::OptObjInitializerContext *ctx) = 0;
  virtual void exitOptObjInitializer(P4Parser::OptObjInitializerContext *ctx) = 0;

  virtual void enterObjDeclarations(P4Parser::ObjDeclarationsContext *ctx) = 0;
  virtual void exitObjDeclarations(P4Parser::ObjDeclarationsContext *ctx) = 0;

  virtual void enterObjDeclaration(P4Parser::ObjDeclarationContext *ctx) = 0;
  virtual void exitObjDeclaration(P4Parser::ObjDeclarationContext *ctx) = 0;

  virtual void enterOptConstructorParameters(P4Parser::OptConstructorParametersContext *ctx) = 0;
  virtual void exitOptConstructorParameters(P4Parser::OptConstructorParametersContext *ctx) = 0;

  virtual void enterTableDeclaration(P4Parser::TableDeclarationContext *ctx) = 0;
  virtual void exitTableDeclaration(P4Parser::TableDeclarationContext *ctx) = 0;

  virtual void enterTablePropertyList(P4Parser::TablePropertyListContext *ctx) = 0;
  virtual void exitTablePropertyList(P4Parser::TablePropertyListContext *ctx) = 0;

  virtual void enterTableProperty(P4Parser::TablePropertyContext *ctx) = 0;
  virtual void exitTableProperty(P4Parser::TablePropertyContext *ctx) = 0;

  virtual void enterOptCONST(P4Parser::OptCONSTContext *ctx) = 0;
  virtual void exitOptCONST(P4Parser::OptCONSTContext *ctx) = 0;

  virtual void enterKeyElementList(P4Parser::KeyElementListContext *ctx) = 0;
  virtual void exitKeyElementList(P4Parser::KeyElementListContext *ctx) = 0;

  virtual void enterKeyElement(P4Parser::KeyElementContext *ctx) = 0;
  virtual void exitKeyElement(P4Parser::KeyElementContext *ctx) = 0;

  virtual void enterActionList(P4Parser::ActionListContext *ctx) = 0;
  virtual void exitActionList(P4Parser::ActionListContext *ctx) = 0;

  virtual void enterActionRef(P4Parser::ActionRefContext *ctx) = 0;
  virtual void exitActionRef(P4Parser::ActionRefContext *ctx) = 0;

  virtual void enterPrefixedNonTypeName(P4Parser::PrefixedNonTypeNameContext *ctx) = 0;
  virtual void exitPrefixedNonTypeName(P4Parser::PrefixedNonTypeNameContext *ctx) = 0;

  virtual void enterEntry(P4Parser::EntryContext *ctx) = 0;
  virtual void exitEntry(P4Parser::EntryContext *ctx) = 0;

  virtual void enterEntryPriority(P4Parser::EntryPriorityContext *ctx) = 0;
  virtual void exitEntryPriority(P4Parser::EntryPriorityContext *ctx) = 0;

  virtual void enterEntriesList(P4Parser::EntriesListContext *ctx) = 0;
  virtual void exitEntriesList(P4Parser::EntriesListContext *ctx) = 0;

  virtual void enterActionDeclaration(P4Parser::ActionDeclarationContext *ctx) = 0;
  virtual void exitActionDeclaration(P4Parser::ActionDeclarationContext *ctx) = 0;

  virtual void enterVariableDeclaration(P4Parser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(P4Parser::VariableDeclarationContext *ctx) = 0;

  virtual void enterVariableDeclarationWithoutSemicolon(P4Parser::VariableDeclarationWithoutSemicolonContext *ctx) = 0;
  virtual void exitVariableDeclarationWithoutSemicolon(P4Parser::VariableDeclarationWithoutSemicolonContext *ctx) = 0;

  virtual void enterConstantDeclaration(P4Parser::ConstantDeclarationContext *ctx) = 0;
  virtual void exitConstantDeclaration(P4Parser::ConstantDeclarationContext *ctx) = 0;

  virtual void enterDeclarator(P4Parser::DeclaratorContext *ctx) = 0;
  virtual void exitDeclarator(P4Parser::DeclaratorContext *ctx) = 0;

  virtual void enterOptInitializer(P4Parser::OptInitializerContext *ctx) = 0;
  virtual void exitOptInitializer(P4Parser::OptInitializerContext *ctx) = 0;

  virtual void enterInitializer(P4Parser::InitializerContext *ctx) = 0;
  virtual void exitInitializer(P4Parser::InitializerContext *ctx) = 0;

  virtual void enterFunctionDeclaration(P4Parser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(P4Parser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterArgumentList(P4Parser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(P4Parser::ArgumentListContext *ctx) = 0;

  virtual void enterNonEmptyArgList(P4Parser::NonEmptyArgListContext *ctx) = 0;
  virtual void exitNonEmptyArgList(P4Parser::NonEmptyArgListContext *ctx) = 0;

  virtual void enterArgument(P4Parser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(P4Parser::ArgumentContext *ctx) = 0;

  virtual void enterExpressionList(P4Parser::ExpressionListContext *ctx) = 0;
  virtual void exitExpressionList(P4Parser::ExpressionListContext *ctx) = 0;

  virtual void enterKvList(P4Parser::KvListContext *ctx) = 0;
  virtual void exitKvList(P4Parser::KvListContext *ctx) = 0;

  virtual void enterKvPair(P4Parser::KvPairContext *ctx) = 0;
  virtual void exitKvPair(P4Parser::KvPairContext *ctx) = 0;

  virtual void enterStatement(P4Parser::StatementContext *ctx) = 0;
  virtual void exitStatement(P4Parser::StatementContext *ctx) = 0;

  virtual void enterMethodCallStmt(P4Parser::MethodCallStmtContext *ctx) = 0;
  virtual void exitMethodCallStmt(P4Parser::MethodCallStmtContext *ctx) = 0;

  virtual void enterTypeArgsMethodCallStmt(P4Parser::TypeArgsMethodCallStmtContext *ctx) = 0;
  virtual void exitTypeArgsMethodCallStmt(P4Parser::TypeArgsMethodCallStmtContext *ctx) = 0;

  virtual void enterAssignmentStmt(P4Parser::AssignmentStmtContext *ctx) = 0;
  virtual void exitAssignmentStmt(P4Parser::AssignmentStmtContext *ctx) = 0;

  virtual void enterMulAssignStmt(P4Parser::MulAssignStmtContext *ctx) = 0;
  virtual void exitMulAssignStmt(P4Parser::MulAssignStmtContext *ctx) = 0;

  virtual void enterDivAssignStmt(P4Parser::DivAssignStmtContext *ctx) = 0;
  virtual void exitDivAssignStmt(P4Parser::DivAssignStmtContext *ctx) = 0;

  virtual void enterModAssignStmt(P4Parser::ModAssignStmtContext *ctx) = 0;
  virtual void exitModAssignStmt(P4Parser::ModAssignStmtContext *ctx) = 0;

  virtual void enterAddAssignStmt(P4Parser::AddAssignStmtContext *ctx) = 0;
  virtual void exitAddAssignStmt(P4Parser::AddAssignStmtContext *ctx) = 0;

  virtual void enterSubAssignStmt(P4Parser::SubAssignStmtContext *ctx) = 0;
  virtual void exitSubAssignStmt(P4Parser::SubAssignStmtContext *ctx) = 0;

  virtual void enterAddSatAssignStmt(P4Parser::AddSatAssignStmtContext *ctx) = 0;
  virtual void exitAddSatAssignStmt(P4Parser::AddSatAssignStmtContext *ctx) = 0;

  virtual void enterSubSatAssignStmt(P4Parser::SubSatAssignStmtContext *ctx) = 0;
  virtual void exitSubSatAssignStmt(P4Parser::SubSatAssignStmtContext *ctx) = 0;

  virtual void enterShlAssignStmt(P4Parser::ShlAssignStmtContext *ctx) = 0;
  virtual void exitShlAssignStmt(P4Parser::ShlAssignStmtContext *ctx) = 0;

  virtual void enterShrAssignStmt(P4Parser::ShrAssignStmtContext *ctx) = 0;
  virtual void exitShrAssignStmt(P4Parser::ShrAssignStmtContext *ctx) = 0;

  virtual void enterBandAssignStmt(P4Parser::BandAssignStmtContext *ctx) = 0;
  virtual void exitBandAssignStmt(P4Parser::BandAssignStmtContext *ctx) = 0;

  virtual void enterBorAssignStmt(P4Parser::BorAssignStmtContext *ctx) = 0;
  virtual void exitBorAssignStmt(P4Parser::BorAssignStmtContext *ctx) = 0;

  virtual void enterBxorAssignStmt(P4Parser::BxorAssignStmtContext *ctx) = 0;
  virtual void exitBxorAssignStmt(P4Parser::BxorAssignStmtContext *ctx) = 0;

  virtual void enterEmptyStatement(P4Parser::EmptyStatementContext *ctx) = 0;
  virtual void exitEmptyStatement(P4Parser::EmptyStatementContext *ctx) = 0;

  virtual void enterExitStatement(P4Parser::ExitStatementContext *ctx) = 0;
  virtual void exitExitStatement(P4Parser::ExitStatementContext *ctx) = 0;

  virtual void enterReturnStatement(P4Parser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(P4Parser::ReturnStatementContext *ctx) = 0;

  virtual void enterConditionalStatement(P4Parser::ConditionalStatementContext *ctx) = 0;
  virtual void exitConditionalStatement(P4Parser::ConditionalStatementContext *ctx) = 0;

  virtual void enterBreakStatement(P4Parser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(P4Parser::BreakStatementContext *ctx) = 0;

  virtual void enterContinueStatement(P4Parser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(P4Parser::ContinueStatementContext *ctx) = 0;

  virtual void enterDirectApplication(P4Parser::DirectApplicationContext *ctx) = 0;
  virtual void exitDirectApplication(P4Parser::DirectApplicationContext *ctx) = 0;

  virtual void enterBlockStatement(P4Parser::BlockStatementContext *ctx) = 0;
  virtual void exitBlockStatement(P4Parser::BlockStatementContext *ctx) = 0;

  virtual void enterStatOrDeclList(P4Parser::StatOrDeclListContext *ctx) = 0;
  virtual void exitStatOrDeclList(P4Parser::StatOrDeclListContext *ctx) = 0;

  virtual void enterStatementOrDeclaration(P4Parser::StatementOrDeclarationContext *ctx) = 0;
  virtual void exitStatementOrDeclaration(P4Parser::StatementOrDeclarationContext *ctx) = 0;

  virtual void enterSwitchStatement(P4Parser::SwitchStatementContext *ctx) = 0;
  virtual void exitSwitchStatement(P4Parser::SwitchStatementContext *ctx) = 0;

  virtual void enterSwitchCases(P4Parser::SwitchCasesContext *ctx) = 0;
  virtual void exitSwitchCases(P4Parser::SwitchCasesContext *ctx) = 0;

  virtual void enterSwitchCase(P4Parser::SwitchCaseContext *ctx) = 0;
  virtual void exitSwitchCase(P4Parser::SwitchCaseContext *ctx) = 0;

  virtual void enterSwitchLabel(P4Parser::SwitchLabelContext *ctx) = 0;
  virtual void exitSwitchLabel(P4Parser::SwitchLabelContext *ctx) = 0;

  virtual void enterForStatement(P4Parser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(P4Parser::ForStatementContext *ctx) = 0;

  virtual void enterForInitStatements(P4Parser::ForInitStatementsContext *ctx) = 0;
  virtual void exitForInitStatements(P4Parser::ForInitStatementsContext *ctx) = 0;

  virtual void enterDeclOrAssignmentOrMethodCallStatement(P4Parser::DeclOrAssignmentOrMethodCallStatementContext *ctx) = 0;
  virtual void exitDeclOrAssignmentOrMethodCallStatement(P4Parser::DeclOrAssignmentOrMethodCallStatementContext *ctx) = 0;

  virtual void enterAssignmentOrMethodCallStatementWithoutSemicolon(P4Parser::AssignmentOrMethodCallStatementWithoutSemicolonContext *ctx) = 0;
  virtual void exitAssignmentOrMethodCallStatementWithoutSemicolon(P4Parser::AssignmentOrMethodCallStatementWithoutSemicolonContext *ctx) = 0;

  virtual void enterForUpdateStatements(P4Parser::ForUpdateStatementsContext *ctx) = 0;
  virtual void exitForUpdateStatements(P4Parser::ForUpdateStatementsContext *ctx) = 0;

  virtual void enterForCollectionExpr(P4Parser::ForCollectionExprContext *ctx) = 0;
  virtual void exitForCollectionExpr(P4Parser::ForCollectionExprContext *ctx) = 0;

  virtual void enterMemberLvalue(P4Parser::MemberLvalueContext *ctx) = 0;
  virtual void exitMemberLvalue(P4Parser::MemberLvalueContext *ctx) = 0;

  virtual void enterIndexLvalue(P4Parser::IndexLvalueContext *ctx) = 0;
  virtual void exitIndexLvalue(P4Parser::IndexLvalueContext *ctx) = 0;

  virtual void enterParenLvalue(P4Parser::ParenLvalueContext *ctx) = 0;
  virtual void exitParenLvalue(P4Parser::ParenLvalueContext *ctx) = 0;

  virtual void enterPlusSliceLvalue(P4Parser::PlusSliceLvalueContext *ctx) = 0;
  virtual void exitPlusSliceLvalue(P4Parser::PlusSliceLvalueContext *ctx) = 0;

  virtual void enterPathLvalue(P4Parser::PathLvalueContext *ctx) = 0;
  virtual void exitPathLvalue(P4Parser::PathLvalueContext *ctx) = 0;

  virtual void enterSliceLvalue(P4Parser::SliceLvalueContext *ctx) = 0;
  virtual void exitSliceLvalue(P4Parser::SliceLvalueContext *ctx) = 0;

  virtual void enterThisLvalue(P4Parser::ThisLvalueContext *ctx) = 0;
  virtual void exitThisLvalue(P4Parser::ThisLvalueContext *ctx) = 0;

  virtual void enterThisExpr(P4Parser::ThisExprContext *ctx) = 0;
  virtual void exitThisExpr(P4Parser::ThisExprContext *ctx) = 0;

  virtual void enterStructDotsExpr(P4Parser::StructDotsExprContext *ctx) = 0;
  virtual void exitStructDotsExpr(P4Parser::StructDotsExprContext *ctx) = 0;

  virtual void enterIntegerExpr(P4Parser::IntegerExprContext *ctx) = 0;
  virtual void exitIntegerExpr(P4Parser::IntegerExprContext *ctx) = 0;

  virtual void enterModExpr(P4Parser::ModExprContext *ctx) = 0;
  virtual void exitModExpr(P4Parser::ModExprContext *ctx) = 0;

  virtual void enterCastExpr(P4Parser::CastExprContext *ctx) = 0;
  virtual void exitCastExpr(P4Parser::CastExprContext *ctx) = 0;

  virtual void enterTrueExpr(P4Parser::TrueExprContext *ctx) = 0;
  virtual void exitTrueExpr(P4Parser::TrueExprContext *ctx) = 0;

  virtual void enterSubExpr(P4Parser::SubExprContext *ctx) = 0;
  virtual void exitSubExpr(P4Parser::SubExprContext *ctx) = 0;

  virtual void enterBandExpr(P4Parser::BandExprContext *ctx) = 0;
  virtual void exitBandExpr(P4Parser::BandExprContext *ctx) = 0;

  virtual void enterParenExpr(P4Parser::ParenExprContext *ctx) = 0;
  virtual void exitParenExpr(P4Parser::ParenExprContext *ctx) = 0;

  virtual void enterConcatExpr(P4Parser::ConcatExprContext *ctx) = 0;
  virtual void exitConcatExpr(P4Parser::ConcatExprContext *ctx) = 0;

  virtual void enterNeqExpr(P4Parser::NeqExprContext *ctx) = 0;
  virtual void exitNeqExpr(P4Parser::NeqExprContext *ctx) = 0;

  virtual void enterTypeCallExpr(P4Parser::TypeCallExprContext *ctx) = 0;
  virtual void exitTypeCallExpr(P4Parser::TypeCallExprContext *ctx) = 0;

  virtual void enterGrtExpr(P4Parser::GrtExprContext *ctx) = 0;
  virtual void exitGrtExpr(P4Parser::GrtExprContext *ctx) = 0;

  virtual void enterMethodCallExpr(P4Parser::MethodCallExprContext *ctx) = 0;
  virtual void exitMethodCallExpr(P4Parser::MethodCallExprContext *ctx) = 0;

  virtual void enterLandExpr(P4Parser::LandExprContext *ctx) = 0;
  virtual void exitLandExpr(P4Parser::LandExprContext *ctx) = 0;

  virtual void enterTernaryExpr(P4Parser::TernaryExprContext *ctx) = 0;
  virtual void exitTernaryExpr(P4Parser::TernaryExprContext *ctx) = 0;

  virtual void enterLorExpr(P4Parser::LorExprContext *ctx) = 0;
  virtual void exitLorExpr(P4Parser::LorExprContext *ctx) = 0;

  virtual void enterStructExpr(P4Parser::StructExprContext *ctx) = 0;
  virtual void exitStructExpr(P4Parser::StructExprContext *ctx) = 0;

  virtual void enterMulExpr(P4Parser::MulExprContext *ctx) = 0;
  virtual void exitMulExpr(P4Parser::MulExprContext *ctx) = 0;

  virtual void enterDivExpr(P4Parser::DivExprContext *ctx) = 0;
  virtual void exitDivExpr(P4Parser::DivExprContext *ctx) = 0;

  virtual void enterFalseExpr(P4Parser::FalseExprContext *ctx) = 0;
  virtual void exitFalseExpr(P4Parser::FalseExprContext *ctx) = 0;

  virtual void enterListExpr(P4Parser::ListExprContext *ctx) = 0;
  virtual void exitListExpr(P4Parser::ListExprContext *ctx) = 0;

  virtual void enterShrExpr(P4Parser::ShrExprContext *ctx) = 0;
  virtual void exitShrExpr(P4Parser::ShrExprContext *ctx) = 0;

  virtual void enterConstructorCallExpr(P4Parser::ConstructorCallExprContext *ctx) = 0;
  virtual void exitConstructorCallExpr(P4Parser::ConstructorCallExprContext *ctx) = 0;

  virtual void enterStringLiteralExpr(P4Parser::StringLiteralExprContext *ctx) = 0;
  virtual void exitStringLiteralExpr(P4Parser::StringLiteralExprContext *ctx) = 0;

  virtual void enterInvalidExpr(P4Parser::InvalidExprContext *ctx) = 0;
  virtual void exitInvalidExpr(P4Parser::InvalidExprContext *ctx) = 0;

  virtual void enterLnotExpr(P4Parser::LnotExprContext *ctx) = 0;
  virtual void exitLnotExpr(P4Parser::LnotExprContext *ctx) = 0;

  virtual void enterMemberExpr(P4Parser::MemberExprContext *ctx) = 0;
  virtual void exitMemberExpr(P4Parser::MemberExprContext *ctx) = 0;

  virtual void enterPlusSliceExpr(P4Parser::PlusSliceExprContext *ctx) = 0;
  virtual void exitPlusSliceExpr(P4Parser::PlusSliceExprContext *ctx) = 0;

  virtual void enterAddSatExpr(P4Parser::AddSatExprContext *ctx) = 0;
  virtual void exitAddSatExpr(P4Parser::AddSatExprContext *ctx) = 0;

  virtual void enterArrayIndexExpr(P4Parser::ArrayIndexExprContext *ctx) = 0;
  virtual void exitArrayIndexExpr(P4Parser::ArrayIndexExprContext *ctx) = 0;

  virtual void enterUplusExpr(P4Parser::UplusExprContext *ctx) = 0;
  virtual void exitUplusExpr(P4Parser::UplusExprContext *ctx) = 0;

  virtual void enterSliceExpr(P4Parser::SliceExprContext *ctx) = 0;
  virtual void exitSliceExpr(P4Parser::SliceExprContext *ctx) = 0;

  virtual void enterDotsExpr(P4Parser::DotsExprContext *ctx) = 0;
  virtual void exitDotsExpr(P4Parser::DotsExprContext *ctx) = 0;

  virtual void enterBorExpr(P4Parser::BorExprContext *ctx) = 0;
  virtual void exitBorExpr(P4Parser::BorExprContext *ctx) = 0;

  virtual void enterErrorMemberExpr(P4Parser::ErrorMemberExprContext *ctx) = 0;
  virtual void exitErrorMemberExpr(P4Parser::ErrorMemberExprContext *ctx) = 0;

  virtual void enterEqExpr(P4Parser::EqExprContext *ctx) = 0;
  virtual void exitEqExpr(P4Parser::EqExprContext *ctx) = 0;

  virtual void enterAddExpr(P4Parser::AddExprContext *ctx) = 0;
  virtual void exitAddExpr(P4Parser::AddExprContext *ctx) = 0;

  virtual void enterLssExpr(P4Parser::LssExprContext *ctx) = 0;
  virtual void exitLssExpr(P4Parser::LssExprContext *ctx) = 0;

  virtual void enterCmplExpr(P4Parser::CmplExprContext *ctx) = 0;
  virtual void exitCmplExpr(P4Parser::CmplExprContext *ctx) = 0;

  virtual void enterNegExpr(P4Parser::NegExprContext *ctx) = 0;
  virtual void exitNegExpr(P4Parser::NegExprContext *ctx) = 0;

  virtual void enterPathExpr(P4Parser::PathExprContext *ctx) = 0;
  virtual void exitPathExpr(P4Parser::PathExprContext *ctx) = 0;

  virtual void enterLeqExpr(P4Parser::LeqExprContext *ctx) = 0;
  virtual void exitLeqExpr(P4Parser::LeqExprContext *ctx) = 0;

  virtual void enterShlExpr(P4Parser::ShlExprContext *ctx) = 0;
  virtual void exitShlExpr(P4Parser::ShlExprContext *ctx) = 0;

  virtual void enterGeqExpr(P4Parser::GeqExprContext *ctx) = 0;
  virtual void exitGeqExpr(P4Parser::GeqExprContext *ctx) = 0;

  virtual void enterSubSatExpr(P4Parser::SubSatExprContext *ctx) = 0;
  virtual void exitSubSatExpr(P4Parser::SubSatExprContext *ctx) = 0;

  virtual void enterBxorExpr(P4Parser::BxorExprContext *ctx) = 0;
  virtual void exitBxorExpr(P4Parser::BxorExprContext *ctx) = 0;

  virtual void enterNonBraceExpression(P4Parser::NonBraceExpressionContext *ctx) = 0;
  virtual void exitNonBraceExpression(P4Parser::NonBraceExpressionContext *ctx) = 0;


};

