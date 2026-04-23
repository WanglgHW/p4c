
// Generated from P4Parser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "P4Parser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by P4Parser.
 */
class  P4ParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by P4Parser.
   */
    virtual std::any visitProgram(P4Parser::ProgramContext *context) = 0;

    virtual std::any visitDeclaration(P4Parser::DeclarationContext *context) = 0;

    virtual std::any visitNonTypeName(P4Parser::NonTypeNameContext *context) = 0;

    virtual std::any visitName(P4Parser::NameContext *context) = 0;

    virtual std::any visitNonTableKwName(P4Parser::NonTableKwNameContext *context) = 0;

    virtual std::any visitAnnotationName(P4Parser::AnnotationNameContext *context) = 0;

    virtual std::any visitOptAnnotations(P4Parser::OptAnnotationsContext *context) = 0;

    virtual std::any visitAnnotations(P4Parser::AnnotationsContext *context) = 0;

    virtual std::any visitAnnotation(P4Parser::AnnotationContext *context) = 0;

    virtual std::any visitAnnotationBody(P4Parser::AnnotationBodyContext *context) = 0;

    virtual std::any visitAnnotationToken(P4Parser::AnnotationTokenContext *context) = 0;

    virtual std::any visitOptTrailingComma(P4Parser::OptTrailingCommaContext *context) = 0;

    virtual std::any visitParameterList(P4Parser::ParameterListContext *context) = 0;

    virtual std::any visitNonEmptyParameterList(P4Parser::NonEmptyParameterListContext *context) = 0;

    virtual std::any visitParameter(P4Parser::ParameterContext *context) = 0;

    virtual std::any visitDirection(P4Parser::DirectionContext *context) = 0;

    virtual std::any visitSpecializedTypeRef(P4Parser::SpecializedTypeRefContext *context) = 0;

    virtual std::any visitHeaderStackTypeRef(P4Parser::HeaderStackTypeRefContext *context) = 0;

    virtual std::any visitTypeNameRef(P4Parser::TypeNameRefContext *context) = 0;

    virtual std::any visitTupleTypeRef(P4Parser::TupleTypeRefContext *context) = 0;

    virtual std::any visitBaseTypeRef(P4Parser::BaseTypeRefContext *context) = 0;

    virtual std::any visitP4listTypeRef(P4Parser::P4listTypeRefContext *context) = 0;

    virtual std::any visitNamedType(P4Parser::NamedTypeContext *context) = 0;

    virtual std::any visitPrefixedType(P4Parser::PrefixedTypeContext *context) = 0;

    virtual std::any visitTypeName(P4Parser::TypeNameContext *context) = 0;

    virtual std::any visitP4listType(P4Parser::P4listTypeContext *context) = 0;

    virtual std::any visitTupleType(P4Parser::TupleTypeContext *context) = 0;

    virtual std::any visitSpecializedType(P4Parser::SpecializedTypeContext *context) = 0;

    virtual std::any visitBaseType(P4Parser::BaseTypeContext *context) = 0;

    virtual std::any visitTypeOrVoid(P4Parser::TypeOrVoidContext *context) = 0;

    virtual std::any visitOptTypeParameters(P4Parser::OptTypeParametersContext *context) = 0;

    virtual std::any visitTypeParameters(P4Parser::TypeParametersContext *context) = 0;

    virtual std::any visitTypeParameterList(P4Parser::TypeParameterListContext *context) = 0;

    virtual std::any visitTypeArg(P4Parser::TypeArgContext *context) = 0;

    virtual std::any visitTypeArgumentList(P4Parser::TypeArgumentListContext *context) = 0;

    virtual std::any visitRealTypeArg(P4Parser::RealTypeArgContext *context) = 0;

    virtual std::any visitRealTypeArgumentList(P4Parser::RealTypeArgumentListContext *context) = 0;

    virtual std::any visitTypeDeclaration(P4Parser::TypeDeclarationContext *context) = 0;

    virtual std::any visitDerivedTypeDeclaration(P4Parser::DerivedTypeDeclarationContext *context) = 0;

    virtual std::any visitHeaderTypeDeclaration(P4Parser::HeaderTypeDeclarationContext *context) = 0;

    virtual std::any visitStructTypeDeclaration(P4Parser::StructTypeDeclarationContext *context) = 0;

    virtual std::any visitHeaderUnionDeclaration(P4Parser::HeaderUnionDeclarationContext *context) = 0;

    virtual std::any visitStructFieldList(P4Parser::StructFieldListContext *context) = 0;

    virtual std::any visitStructField(P4Parser::StructFieldContext *context) = 0;

    virtual std::any visitEnumDeclaration(P4Parser::EnumDeclarationContext *context) = 0;

    virtual std::any visitSpecifiedIdentifierList(P4Parser::SpecifiedIdentifierListContext *context) = 0;

    virtual std::any visitSpecifiedIdentifier(P4Parser::SpecifiedIdentifierContext *context) = 0;

    virtual std::any visitErrorDeclaration(P4Parser::ErrorDeclarationContext *context) = 0;

    virtual std::any visitMatchKindDeclaration(P4Parser::MatchKindDeclarationContext *context) = 0;

    virtual std::any visitIdentifierList(P4Parser::IdentifierListContext *context) = 0;

    virtual std::any visitTypedefDeclaration(P4Parser::TypedefDeclarationContext *context) = 0;

    virtual std::any visitPackageTypeDeclaration(P4Parser::PackageTypeDeclarationContext *context) = 0;

    virtual std::any visitParserDeclaration(P4Parser::ParserDeclarationContext *context) = 0;

    virtual std::any visitParserTypeDeclaration(P4Parser::ParserTypeDeclarationContext *context) = 0;

    virtual std::any visitParserLocalElements(P4Parser::ParserLocalElementsContext *context) = 0;

    virtual std::any visitParserLocalElement(P4Parser::ParserLocalElementContext *context) = 0;

    virtual std::any visitParserStates(P4Parser::ParserStatesContext *context) = 0;

    virtual std::any visitParserState(P4Parser::ParserStateContext *context) = 0;

    virtual std::any visitParserStatements(P4Parser::ParserStatementsContext *context) = 0;

    virtual std::any visitParserStatement(P4Parser::ParserStatementContext *context) = 0;

    virtual std::any visitParserBlockStatement(P4Parser::ParserBlockStatementContext *context) = 0;

    virtual std::any visitTransitionStatement(P4Parser::TransitionStatementContext *context) = 0;

    virtual std::any visitStateExpression(P4Parser::StateExpressionContext *context) = 0;

    virtual std::any visitSelectExpression(P4Parser::SelectExpressionContext *context) = 0;

    virtual std::any visitSelectCaseList(P4Parser::SelectCaseListContext *context) = 0;

    virtual std::any visitSelectCase(P4Parser::SelectCaseContext *context) = 0;

    virtual std::any visitKeysetExpression(P4Parser::KeysetExpressionContext *context) = 0;

    virtual std::any visitTupleKeysetExpression(P4Parser::TupleKeysetExpressionContext *context) = 0;

    virtual std::any visitSimpleExpressionList(P4Parser::SimpleExpressionListContext *context) = 0;

    virtual std::any visitReducedSimpleKeysetExpression(P4Parser::ReducedSimpleKeysetExpressionContext *context) = 0;

    virtual std::any visitSimpleKeysetExpression(P4Parser::SimpleKeysetExpressionContext *context) = 0;

    virtual std::any visitValueSetDeclaration(P4Parser::ValueSetDeclarationContext *context) = 0;

    virtual std::any visitControlDeclaration(P4Parser::ControlDeclarationContext *context) = 0;

    virtual std::any visitControlTypeDeclaration(P4Parser::ControlTypeDeclarationContext *context) = 0;

    virtual std::any visitControlLocalDeclarations(P4Parser::ControlLocalDeclarationsContext *context) = 0;

    virtual std::any visitControlLocalDeclaration(P4Parser::ControlLocalDeclarationContext *context) = 0;

    virtual std::any visitControlBody(P4Parser::ControlBodyContext *context) = 0;

    virtual std::any visitExternDeclaration(P4Parser::ExternDeclarationContext *context) = 0;

    virtual std::any visitMethodPrototypes(P4Parser::MethodPrototypesContext *context) = 0;

    virtual std::any visitFunctionPrototype(P4Parser::FunctionPrototypeContext *context) = 0;

    virtual std::any visitMethodPrototype(P4Parser::MethodPrototypeContext *context) = 0;

    virtual std::any visitInstantiation(P4Parser::InstantiationContext *context) = 0;

    virtual std::any visitOptObjInitializer(P4Parser::OptObjInitializerContext *context) = 0;

    virtual std::any visitObjDeclarations(P4Parser::ObjDeclarationsContext *context) = 0;

    virtual std::any visitObjDeclaration(P4Parser::ObjDeclarationContext *context) = 0;

    virtual std::any visitOptConstructorParameters(P4Parser::OptConstructorParametersContext *context) = 0;

    virtual std::any visitTableDeclaration(P4Parser::TableDeclarationContext *context) = 0;

    virtual std::any visitTablePropertyList(P4Parser::TablePropertyListContext *context) = 0;

    virtual std::any visitTableProperty(P4Parser::TablePropertyContext *context) = 0;

    virtual std::any visitOptCONST(P4Parser::OptCONSTContext *context) = 0;

    virtual std::any visitKeyElementList(P4Parser::KeyElementListContext *context) = 0;

    virtual std::any visitKeyElement(P4Parser::KeyElementContext *context) = 0;

    virtual std::any visitActionList(P4Parser::ActionListContext *context) = 0;

    virtual std::any visitActionRef(P4Parser::ActionRefContext *context) = 0;

    virtual std::any visitPrefixedNonTypeName(P4Parser::PrefixedNonTypeNameContext *context) = 0;

    virtual std::any visitEntry(P4Parser::EntryContext *context) = 0;

    virtual std::any visitEntryPriority(P4Parser::EntryPriorityContext *context) = 0;

    virtual std::any visitEntriesList(P4Parser::EntriesListContext *context) = 0;

    virtual std::any visitActionDeclaration(P4Parser::ActionDeclarationContext *context) = 0;

    virtual std::any visitVariableDeclaration(P4Parser::VariableDeclarationContext *context) = 0;

    virtual std::any visitVariableDeclarationWithoutSemicolon(P4Parser::VariableDeclarationWithoutSemicolonContext *context) = 0;

    virtual std::any visitConstantDeclaration(P4Parser::ConstantDeclarationContext *context) = 0;

    virtual std::any visitDeclarator(P4Parser::DeclaratorContext *context) = 0;

    virtual std::any visitOptInitializer(P4Parser::OptInitializerContext *context) = 0;

    virtual std::any visitInitializer(P4Parser::InitializerContext *context) = 0;

    virtual std::any visitFunctionDeclaration(P4Parser::FunctionDeclarationContext *context) = 0;

    virtual std::any visitArgumentList(P4Parser::ArgumentListContext *context) = 0;

    virtual std::any visitNonEmptyArgList(P4Parser::NonEmptyArgListContext *context) = 0;

    virtual std::any visitArgument(P4Parser::ArgumentContext *context) = 0;

    virtual std::any visitExpressionList(P4Parser::ExpressionListContext *context) = 0;

    virtual std::any visitKvList(P4Parser::KvListContext *context) = 0;

    virtual std::any visitKvPair(P4Parser::KvPairContext *context) = 0;

    virtual std::any visitStatement(P4Parser::StatementContext *context) = 0;

    virtual std::any visitMethodCallStmt(P4Parser::MethodCallStmtContext *context) = 0;

    virtual std::any visitTypeArgsMethodCallStmt(P4Parser::TypeArgsMethodCallStmtContext *context) = 0;

    virtual std::any visitAssignmentStmt(P4Parser::AssignmentStmtContext *context) = 0;

    virtual std::any visitMulAssignStmt(P4Parser::MulAssignStmtContext *context) = 0;

    virtual std::any visitDivAssignStmt(P4Parser::DivAssignStmtContext *context) = 0;

    virtual std::any visitModAssignStmt(P4Parser::ModAssignStmtContext *context) = 0;

    virtual std::any visitAddAssignStmt(P4Parser::AddAssignStmtContext *context) = 0;

    virtual std::any visitSubAssignStmt(P4Parser::SubAssignStmtContext *context) = 0;

    virtual std::any visitAddSatAssignStmt(P4Parser::AddSatAssignStmtContext *context) = 0;

    virtual std::any visitSubSatAssignStmt(P4Parser::SubSatAssignStmtContext *context) = 0;

    virtual std::any visitShlAssignStmt(P4Parser::ShlAssignStmtContext *context) = 0;

    virtual std::any visitShrAssignStmt(P4Parser::ShrAssignStmtContext *context) = 0;

    virtual std::any visitBandAssignStmt(P4Parser::BandAssignStmtContext *context) = 0;

    virtual std::any visitBorAssignStmt(P4Parser::BorAssignStmtContext *context) = 0;

    virtual std::any visitBxorAssignStmt(P4Parser::BxorAssignStmtContext *context) = 0;

    virtual std::any visitEmptyStatement(P4Parser::EmptyStatementContext *context) = 0;

    virtual std::any visitExitStatement(P4Parser::ExitStatementContext *context) = 0;

    virtual std::any visitReturnStatement(P4Parser::ReturnStatementContext *context) = 0;

    virtual std::any visitConditionalStatement(P4Parser::ConditionalStatementContext *context) = 0;

    virtual std::any visitBreakStatement(P4Parser::BreakStatementContext *context) = 0;

    virtual std::any visitContinueStatement(P4Parser::ContinueStatementContext *context) = 0;

    virtual std::any visitDirectApplication(P4Parser::DirectApplicationContext *context) = 0;

    virtual std::any visitBlockStatement(P4Parser::BlockStatementContext *context) = 0;

    virtual std::any visitStatOrDeclList(P4Parser::StatOrDeclListContext *context) = 0;

    virtual std::any visitStatementOrDeclaration(P4Parser::StatementOrDeclarationContext *context) = 0;

    virtual std::any visitSwitchStatement(P4Parser::SwitchStatementContext *context) = 0;

    virtual std::any visitSwitchCases(P4Parser::SwitchCasesContext *context) = 0;

    virtual std::any visitSwitchCase(P4Parser::SwitchCaseContext *context) = 0;

    virtual std::any visitSwitchLabel(P4Parser::SwitchLabelContext *context) = 0;

    virtual std::any visitForStatement(P4Parser::ForStatementContext *context) = 0;

    virtual std::any visitForInitStatements(P4Parser::ForInitStatementsContext *context) = 0;

    virtual std::any visitDeclOrAssignmentOrMethodCallStatement(P4Parser::DeclOrAssignmentOrMethodCallStatementContext *context) = 0;

    virtual std::any visitAssignmentOrMethodCallStatementWithoutSemicolon(P4Parser::AssignmentOrMethodCallStatementWithoutSemicolonContext *context) = 0;

    virtual std::any visitForUpdateStatements(P4Parser::ForUpdateStatementsContext *context) = 0;

    virtual std::any visitForCollectionExpr(P4Parser::ForCollectionExprContext *context) = 0;

    virtual std::any visitMemberLvalue(P4Parser::MemberLvalueContext *context) = 0;

    virtual std::any visitIndexLvalue(P4Parser::IndexLvalueContext *context) = 0;

    virtual std::any visitParenLvalue(P4Parser::ParenLvalueContext *context) = 0;

    virtual std::any visitPlusSliceLvalue(P4Parser::PlusSliceLvalueContext *context) = 0;

    virtual std::any visitPathLvalue(P4Parser::PathLvalueContext *context) = 0;

    virtual std::any visitSliceLvalue(P4Parser::SliceLvalueContext *context) = 0;

    virtual std::any visitThisLvalue(P4Parser::ThisLvalueContext *context) = 0;

    virtual std::any visitThisExpr(P4Parser::ThisExprContext *context) = 0;

    virtual std::any visitStructDotsExpr(P4Parser::StructDotsExprContext *context) = 0;

    virtual std::any visitIntegerExpr(P4Parser::IntegerExprContext *context) = 0;

    virtual std::any visitModExpr(P4Parser::ModExprContext *context) = 0;

    virtual std::any visitCastExpr(P4Parser::CastExprContext *context) = 0;

    virtual std::any visitTrueExpr(P4Parser::TrueExprContext *context) = 0;

    virtual std::any visitSubExpr(P4Parser::SubExprContext *context) = 0;

    virtual std::any visitBandExpr(P4Parser::BandExprContext *context) = 0;

    virtual std::any visitParenExpr(P4Parser::ParenExprContext *context) = 0;

    virtual std::any visitConcatExpr(P4Parser::ConcatExprContext *context) = 0;

    virtual std::any visitNeqExpr(P4Parser::NeqExprContext *context) = 0;

    virtual std::any visitTypeCallExpr(P4Parser::TypeCallExprContext *context) = 0;

    virtual std::any visitGrtExpr(P4Parser::GrtExprContext *context) = 0;

    virtual std::any visitMethodCallExpr(P4Parser::MethodCallExprContext *context) = 0;

    virtual std::any visitLandExpr(P4Parser::LandExprContext *context) = 0;

    virtual std::any visitTernaryExpr(P4Parser::TernaryExprContext *context) = 0;

    virtual std::any visitLorExpr(P4Parser::LorExprContext *context) = 0;

    virtual std::any visitStructExpr(P4Parser::StructExprContext *context) = 0;

    virtual std::any visitMulExpr(P4Parser::MulExprContext *context) = 0;

    virtual std::any visitDivExpr(P4Parser::DivExprContext *context) = 0;

    virtual std::any visitFalseExpr(P4Parser::FalseExprContext *context) = 0;

    virtual std::any visitListExpr(P4Parser::ListExprContext *context) = 0;

    virtual std::any visitShrExpr(P4Parser::ShrExprContext *context) = 0;

    virtual std::any visitConstructorCallExpr(P4Parser::ConstructorCallExprContext *context) = 0;

    virtual std::any visitStringLiteralExpr(P4Parser::StringLiteralExprContext *context) = 0;

    virtual std::any visitInvalidExpr(P4Parser::InvalidExprContext *context) = 0;

    virtual std::any visitLnotExpr(P4Parser::LnotExprContext *context) = 0;

    virtual std::any visitMemberExpr(P4Parser::MemberExprContext *context) = 0;

    virtual std::any visitPlusSliceExpr(P4Parser::PlusSliceExprContext *context) = 0;

    virtual std::any visitAddSatExpr(P4Parser::AddSatExprContext *context) = 0;

    virtual std::any visitArrayIndexExpr(P4Parser::ArrayIndexExprContext *context) = 0;

    virtual std::any visitUplusExpr(P4Parser::UplusExprContext *context) = 0;

    virtual std::any visitSliceExpr(P4Parser::SliceExprContext *context) = 0;

    virtual std::any visitDotsExpr(P4Parser::DotsExprContext *context) = 0;

    virtual std::any visitBorExpr(P4Parser::BorExprContext *context) = 0;

    virtual std::any visitErrorMemberExpr(P4Parser::ErrorMemberExprContext *context) = 0;

    virtual std::any visitEqExpr(P4Parser::EqExprContext *context) = 0;

    virtual std::any visitAddExpr(P4Parser::AddExprContext *context) = 0;

    virtual std::any visitLssExpr(P4Parser::LssExprContext *context) = 0;

    virtual std::any visitCmplExpr(P4Parser::CmplExprContext *context) = 0;

    virtual std::any visitNegExpr(P4Parser::NegExprContext *context) = 0;

    virtual std::any visitPathExpr(P4Parser::PathExprContext *context) = 0;

    virtual std::any visitLeqExpr(P4Parser::LeqExprContext *context) = 0;

    virtual std::any visitShlExpr(P4Parser::ShlExprContext *context) = 0;

    virtual std::any visitGeqExpr(P4Parser::GeqExprContext *context) = 0;

    virtual std::any visitSubSatExpr(P4Parser::SubSatExprContext *context) = 0;

    virtual std::any visitBxorExpr(P4Parser::BxorExprContext *context) = 0;

    virtual std::any visitNonBraceExpression(P4Parser::NonBraceExpressionContext *context) = 0;


};

