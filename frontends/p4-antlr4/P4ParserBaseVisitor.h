
// Generated from P4Parser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "P4ParserVisitor.h"


/**
 * This class provides an empty implementation of P4ParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  P4ParserBaseVisitor : public P4ParserVisitor {
public:

  virtual std::any visitProgram(P4Parser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnExpressionList(P4Parser::AnnExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnKvList(P4Parser::AnnKvListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnIntegerList(P4Parser::AnnIntegerListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnIntOrStrList(P4Parser::AnnIntOrStrListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnStringList(P4Parser::AnnStringListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnExpression(P4Parser::AnnExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnInteger(P4Parser::AnnIntegerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnIntOrStr(P4Parser::AnnIntOrStrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnStringLiteral(P4Parser::AnnStringLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnExpressionPair(P4Parser::AnnExpressionPairContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnIntegerPair(P4Parser::AnnIntegerPairContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnStringPair(P4Parser::AnnStringPairContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnExpressionTriple(P4Parser::AnnExpressionTripleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnIntegerTriple(P4Parser::AnnIntegerTripleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnStringTriple(P4Parser::AnnStringTripleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnP4rtTranslation(P4Parser::AnnP4rtTranslationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntOrStr(P4Parser::IntOrStrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitP4rtControllerType(P4Parser::P4rtControllerTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(P4Parser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNonTypeName(P4Parser::NonTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitName(P4Parser::NameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNonTableKwName(P4Parser::NonTableKwNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotationName(P4Parser::AnnotationNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOptAnnotations(P4Parser::OptAnnotationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotations(P4Parser::AnnotationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotation(P4Parser::AnnotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotationBody(P4Parser::AnnotationBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotationToken(P4Parser::AnnotationTokenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOptTrailingComma(P4Parser::OptTrailingCommaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterList(P4Parser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNonEmptyParameterList(P4Parser::NonEmptyParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter(P4Parser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDirection(P4Parser::DirectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecializedTypeRef(P4Parser::SpecializedTypeRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitHeaderStackTypeRef(P4Parser::HeaderStackTypeRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeNameRef(P4Parser::TypeNameRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTupleTypeRef(P4Parser::TupleTypeRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBaseTypeRef(P4Parser::BaseTypeRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitP4listTypeRef(P4Parser::P4listTypeRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamedType(P4Parser::NamedTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefixedType(P4Parser::PrefixedTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeName(P4Parser::TypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitP4listType(P4Parser::P4listTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTupleType(P4Parser::TupleTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecializedType(P4Parser::SpecializedTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBaseType(P4Parser::BaseTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeOrVoid(P4Parser::TypeOrVoidContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOptTypeParameters(P4Parser::OptTypeParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeParameters(P4Parser::TypeParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeParameterList(P4Parser::TypeParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeArg(P4Parser::TypeArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeArgumentList(P4Parser::TypeArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRealTypeArg(P4Parser::RealTypeArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRealTypeArgumentList(P4Parser::RealTypeArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeDeclaration(P4Parser::TypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDerivedTypeDeclaration(P4Parser::DerivedTypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitHeaderTypeDeclaration(P4Parser::HeaderTypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructTypeDeclaration(P4Parser::StructTypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitHeaderUnionDeclaration(P4Parser::HeaderUnionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructFieldList(P4Parser::StructFieldListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructField(P4Parser::StructFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumDeclaration(P4Parser::EnumDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecifiedIdentifierList(P4Parser::SpecifiedIdentifierListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecifiedIdentifier(P4Parser::SpecifiedIdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitErrorDeclaration(P4Parser::ErrorDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMatchKindDeclaration(P4Parser::MatchKindDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierList(P4Parser::IdentifierListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypedefDeclaration(P4Parser::TypedefDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackageTypeDeclaration(P4Parser::PackageTypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParserDeclaration(P4Parser::ParserDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParserTypeDeclaration(P4Parser::ParserTypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParserLocalElements(P4Parser::ParserLocalElementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParserLocalElement(P4Parser::ParserLocalElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParserStates(P4Parser::ParserStatesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParserState(P4Parser::ParserStateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParserStatements(P4Parser::ParserStatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParserStatement(P4Parser::ParserStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParserBlockStatement(P4Parser::ParserBlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransitionStatement(P4Parser::TransitionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStateExpression(P4Parser::StateExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectExpression(P4Parser::SelectExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectCaseList(P4Parser::SelectCaseListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectCase(P4Parser::SelectCaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeysetExpression(P4Parser::KeysetExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTupleKeysetExpression(P4Parser::TupleKeysetExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleExpressionList(P4Parser::SimpleExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReducedSimpleKeysetExpression(P4Parser::ReducedSimpleKeysetExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleKeysetExpression(P4Parser::SimpleKeysetExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValueSetDeclaration(P4Parser::ValueSetDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitControlDeclaration(P4Parser::ControlDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitControlTypeDeclaration(P4Parser::ControlTypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitControlLocalDeclarations(P4Parser::ControlLocalDeclarationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitControlLocalDeclaration(P4Parser::ControlLocalDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitControlBody(P4Parser::ControlBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExternDeclaration(P4Parser::ExternDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethodPrototypes(P4Parser::MethodPrototypesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionPrototype(P4Parser::FunctionPrototypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethodPrototype(P4Parser::MethodPrototypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInstantiation(P4Parser::InstantiationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOptObjInitializer(P4Parser::OptObjInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjDeclarations(P4Parser::ObjDeclarationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjDeclaration(P4Parser::ObjDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOptConstructorParameters(P4Parser::OptConstructorParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTableDeclaration(P4Parser::TableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTablePropertyList(P4Parser::TablePropertyListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTableProperty(P4Parser::TablePropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOptCONST(P4Parser::OptCONSTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeyElementList(P4Parser::KeyElementListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeyElement(P4Parser::KeyElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitActionList(P4Parser::ActionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitActionRef(P4Parser::ActionRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefixedNonTypeName(P4Parser::PrefixedNonTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEntry(P4Parser::EntryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEntryPriority(P4Parser::EntryPriorityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEntriesList(P4Parser::EntriesListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitActionDeclaration(P4Parser::ActionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(P4Parser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclarationWithoutSemicolon(P4Parser::VariableDeclarationWithoutSemicolonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantDeclaration(P4Parser::ConstantDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclarator(P4Parser::DeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOptInitializer(P4Parser::OptInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitializer(P4Parser::InitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDeclaration(P4Parser::FunctionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(P4Parser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNonEmptyArgList(P4Parser::NonEmptyArgListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument(P4Parser::ArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionList(P4Parser::ExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKvList(P4Parser::KvListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKvPair(P4Parser::KvPairContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(P4Parser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethodCallStmt(P4Parser::MethodCallStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeArgsMethodCallStmt(P4Parser::TypeArgsMethodCallStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentStmt(P4Parser::AssignmentStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulAssignStmt(P4Parser::MulAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDivAssignStmt(P4Parser::DivAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitModAssignStmt(P4Parser::ModAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddAssignStmt(P4Parser::AddAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubAssignStmt(P4Parser::SubAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddSatAssignStmt(P4Parser::AddSatAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubSatAssignStmt(P4Parser::SubSatAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShlAssignStmt(P4Parser::ShlAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShrAssignStmt(P4Parser::ShrAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBandAssignStmt(P4Parser::BandAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBorAssignStmt(P4Parser::BorAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBxorAssignStmt(P4Parser::BxorAssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyStatement(P4Parser::EmptyStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExitStatement(P4Parser::ExitStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(P4Parser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionalStatement(P4Parser::ConditionalStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStatement(P4Parser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStatement(P4Parser::ContinueStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDirectApplication(P4Parser::DirectApplicationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStatement(P4Parser::BlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatOrDeclList(P4Parser::StatOrDeclListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementOrDeclaration(P4Parser::StatementOrDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSwitchStatement(P4Parser::SwitchStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSwitchCases(P4Parser::SwitchCasesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSwitchCase(P4Parser::SwitchCaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSwitchLabel(P4Parser::SwitchLabelContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStatement(P4Parser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForInitStatements(P4Parser::ForInitStatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclOrAssignmentOrMethodCallStatement(P4Parser::DeclOrAssignmentOrMethodCallStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentOrMethodCallStatementWithoutSemicolon(P4Parser::AssignmentOrMethodCallStatementWithoutSemicolonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForUpdateStatements(P4Parser::ForUpdateStatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForCollectionExpr(P4Parser::ForCollectionExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberLvalue(P4Parser::MemberLvalueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndexLvalue(P4Parser::IndexLvalueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenLvalue(P4Parser::ParenLvalueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPlusSliceLvalue(P4Parser::PlusSliceLvalueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPathLvalue(P4Parser::PathLvalueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSliceLvalue(P4Parser::SliceLvalueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitThisLvalue(P4Parser::ThisLvalueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitThisExpr(P4Parser::ThisExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructDotsExpr(P4Parser::StructDotsExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntegerExpr(P4Parser::IntegerExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitModExpr(P4Parser::ModExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCastExpr(P4Parser::CastExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrueExpr(P4Parser::TrueExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubExpr(P4Parser::SubExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBandExpr(P4Parser::BandExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpr(P4Parser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConcatExpr(P4Parser::ConcatExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNeqExpr(P4Parser::NeqExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeCallExpr(P4Parser::TypeCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGrtExpr(P4Parser::GrtExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethodCallExpr(P4Parser::MethodCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLandExpr(P4Parser::LandExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTernaryExpr(P4Parser::TernaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLorExpr(P4Parser::LorExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructExpr(P4Parser::StructExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulExpr(P4Parser::MulExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDivExpr(P4Parser::DivExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFalseExpr(P4Parser::FalseExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitListExpr(P4Parser::ListExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShrExpr(P4Parser::ShrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstructorCallExpr(P4Parser::ConstructorCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringLiteralExpr(P4Parser::StringLiteralExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInvalidExpr(P4Parser::InvalidExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLnotExpr(P4Parser::LnotExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberExpr(P4Parser::MemberExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPlusSliceExpr(P4Parser::PlusSliceExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddSatExpr(P4Parser::AddSatExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayIndexExpr(P4Parser::ArrayIndexExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUplusExpr(P4Parser::UplusExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSliceExpr(P4Parser::SliceExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDotsExpr(P4Parser::DotsExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBorExpr(P4Parser::BorExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitErrorMemberExpr(P4Parser::ErrorMemberExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqExpr(P4Parser::EqExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExpr(P4Parser::AddExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLssExpr(P4Parser::LssExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCmplExpr(P4Parser::CmplExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNegExpr(P4Parser::NegExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPathExpr(P4Parser::PathExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLeqExpr(P4Parser::LeqExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShlExpr(P4Parser::ShlExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGeqExpr(P4Parser::GeqExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubSatExpr(P4Parser::SubSatExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBxorExpr(P4Parser::BxorExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNonBraceExpression(P4Parser::NonBraceExpressionContext *ctx) override {
    return visitChildren(ctx);
  }


};

