/*
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef FRONTENDS_P4_ANTLR4_P4IRCONSTRUCTOR_H_
#define FRONTENDS_P4_ANTLR4_P4IRCONSTRUCTOR_H_

#include "frontends/common/constantParsing.h"
#include "frontends/p4/symbol_table.h"
#include "ir/ir.h"
#include "lib/cstring.h"

#include "antlr4SourceInfo.h"
#include "P4Parser.h"

// Alias the ANTLR4-generated P4Parser (global namespace) for clarity.
using Antlr4P4Parser = ::P4Parser;

namespace P4ANTLR {

/// Visits the ANTLR4 parse tree and constructs p4c IR nodes.
class P4IRConstructor {
 public:
    P4IRConstructor(const SourceInfoFactory &sourceInfoFactory,
                    P4::Util::InputSources *sources);

    /// Force every node built by this constructor to carry @p si as its source
    /// position, ignoring the per-token positions derived from the input stream.
    ///
    /// Used when re-parsing an annotation body (see Antlr4ParserDriver's
    /// `runFragment`): the fragment is lexed from reconstructed text whose
    /// positions bear no relation to the original file, so without an override
    /// the nodes land at line 1. That breaks `ResolveReferences`, which uses
    /// source positions to enforce declaration-before-use ordering and would
    /// otherwise filter out in-scope declarations (e.g. the method names in a
    /// `@synchronous(...)` annotation). Setting the override to the annotation's
    /// real position restores the original Bison-frontend behaviour.
    void setSrcInfoOverride(const P4::Util::SourceInfo &si) { srcInfoOverride = si; }

    /// Entry point: visit program and return IR::P4Program.
    const P4::IR::P4Program *visitProgram(Antlr4P4Parser::ProgramContext *ctx);

    // Annotation-body fragment entry points. Driven by Antlr4ParserDriver
    // when `ParseAnnotations` re-parses an annotation body.
    P4::IR::Vector<P4::IR::Expression> *visitAnnExpressionList(
        Antlr4P4Parser::AnnExpressionListContext *ctx);
    P4::IR::IndexedVector<P4::IR::NamedExpression> *visitAnnKvList(
        Antlr4P4Parser::AnnKvListContext *ctx);
    P4::IR::Vector<P4::IR::Expression> *visitAnnIntegerList(
        Antlr4P4Parser::AnnIntegerListContext *ctx);
    P4::IR::Vector<P4::IR::Expression> *visitAnnIntOrStrList(
        Antlr4P4Parser::AnnIntOrStrListContext *ctx);
    P4::IR::Vector<P4::IR::Expression> *visitAnnStringList(
        Antlr4P4Parser::AnnStringListContext *ctx);

    P4::IR::Expression *visitAnnExpression(Antlr4P4Parser::AnnExpressionContext *ctx);
    P4::IR::Constant *visitAnnInteger(Antlr4P4Parser::AnnIntegerContext *ctx);
    P4::IR::Expression *visitAnnIntOrStr(Antlr4P4Parser::AnnIntOrStrContext *ctx);
    P4::IR::StringLiteral *visitAnnStringLiteral(
        Antlr4P4Parser::AnnStringLiteralContext *ctx);

    P4::IR::Vector<P4::IR::Expression> *visitAnnExpressionPair(
        Antlr4P4Parser::AnnExpressionPairContext *ctx);
    P4::IR::Vector<P4::IR::Expression> *visitAnnIntegerPair(
        Antlr4P4Parser::AnnIntegerPairContext *ctx);
    P4::IR::Vector<P4::IR::Expression> *visitAnnStringPair(
        Antlr4P4Parser::AnnStringPairContext *ctx);

    P4::IR::Vector<P4::IR::Expression> *visitAnnExpressionTriple(
        Antlr4P4Parser::AnnExpressionTripleContext *ctx);
    P4::IR::Vector<P4::IR::Expression> *visitAnnIntegerTriple(
        Antlr4P4Parser::AnnIntegerTripleContext *ctx);
    P4::IR::Vector<P4::IR::Expression> *visitAnnStringTriple(
        Antlr4P4Parser::AnnStringTripleContext *ctx);

    P4::IR::Vector<P4::IR::Expression> *visitAnnP4rtTranslation(
        Antlr4P4Parser::AnnP4rtTranslationContext *ctx);

 private:
    P4::IR::Expression *visitIntOrStr(Antlr4P4Parser::IntOrStrContext *ctx);
    P4::IR::Expression *visitP4rtControllerType(
        Antlr4P4Parser::P4rtControllerTypeContext *ctx);
    // Source info helper
    P4::Util::SourceInfo srcInfo(antlr4::ParserRuleContext *ctx) const;
    P4::Util::SourceInfo srcInfo(antlr4::Token *token) const;
    P4::Util::SourceInfo srcInfo(antlr4::Token *start, antlr4::Token *stop) const;

    // Name helpers
    P4::IR::ID *visitName(Antlr4P4Parser::NameContext *ctx);
    P4::IR::ID *visitNonTypeName(Antlr4P4Parser::NonTypeNameContext *ctx);
    P4::IR::ID *visitNonTableKwName(Antlr4P4Parser::NonTableKwNameContext *ctx);
    P4::IR::ID *visitAnnotationName(Antlr4P4Parser::AnnotationNameContext *ctx);

    // Annotations
    P4::IR::Vector<P4::IR::Annotation> *visitOptAnnotations(
        Antlr4P4Parser::OptAnnotationsContext *ctx);
    P4::IR::Vector<P4::IR::Annotation> *visitAnnotations(
        Antlr4P4Parser::AnnotationsContext *ctx);
    P4::IR::Annotation *visitAnnotation(Antlr4P4Parser::AnnotationContext *ctx);
    P4::IR::Vector<P4::IR::AnnotationToken> *visitAnnotationBody(
        Antlr4P4Parser::AnnotationBodyContext *ctx);
    P4::IR::AnnotationToken *makeAnnotationToken(antlr4::Token *token);

    // Parameters
    P4::IR::IndexedVector<P4::IR::Parameter> *visitParameterList(
        Antlr4P4Parser::ParameterListContext *ctx);
    P4::IR::Parameter *visitParameter(Antlr4P4Parser::ParameterContext *ctx);
    P4::IR::Direction visitDirection(Antlr4P4Parser::DirectionContext *ctx);

    // Types
    const P4::IR::Type *visitTypeRef(Antlr4P4Parser::TypeRefContext *ctx);
    const P4::IR::Type *visitBaseType(Antlr4P4Parser::BaseTypeContext *ctx);
    P4::IR::Type_Name *visitTypeName(Antlr4P4Parser::TypeNameContext *ctx);
    P4::IR::Type_Name *visitTypeName(const std::string &text, P4::Util::SourceInfo si);
    const P4::IR::Type *visitSpecializedType(Antlr4P4Parser::SpecializedTypeContext *ctx);
    const P4::IR::Type *visitP4listType(Antlr4P4Parser::P4listTypeContext *ctx);
    const P4::IR::Type *visitTupleType(Antlr4P4Parser::TupleTypeContext *ctx);
    const P4::IR::Type *visitTypeOrVoid(Antlr4P4Parser::TypeOrVoidContext *ctx);
    const P4::IR::Type *visitNamedType(Antlr4P4Parser::NamedTypeContext *ctx);
    P4::IR::TypeParameters *visitOptTypeParameters(
        Antlr4P4Parser::OptTypeParametersContext *ctx);
    P4::IR::TypeParameters *visitTypeParameters(
        Antlr4P4Parser::TypeParametersContext *ctx);
    const P4::IR::Type *visitTypeArg(Antlr4P4Parser::TypeArgContext *ctx);
    P4::IR::Vector<P4::IR::Type> *visitTypeArgumentList(
        Antlr4P4Parser::TypeArgumentListContext *ctx);
    P4::IR::Vector<P4::IR::Type> *visitRealTypeArgumentList(
        Antlr4P4Parser::RealTypeArgumentListContext *ctx);

    // Declarations
    P4::IR::Node *visitDeclaration(Antlr4P4Parser::DeclarationContext *ctx);
    P4::IR::Declaration *visitConstantDeclaration(
        Antlr4P4Parser::ConstantDeclarationContext *ctx);
    P4::IR::Declaration *visitVariableDeclaration(
        Antlr4P4Parser::VariableDeclarationContext *ctx);
    P4::IR::Declaration *visitVariableDeclarationWithoutSemicolon(
        Antlr4P4Parser::VariableDeclarationWithoutSemicolonContext *ctx);
    P4::IR::Declaration *visitInstantiation(Antlr4P4Parser::InstantiationContext *ctx);

    struct NameTypePair {
        P4::IR::ID *name;
        const P4::IR::Type *type;
    };
    NameTypePair visitDeclarator(Antlr4P4Parser::DeclaratorContext *ctx,
                                const P4::IR::Type *baseType);

    P4::IR::Expression *visitOptInitializer(Antlr4P4Parser::OptInitializerContext *ctx);
    P4::IR::Expression *visitInitializer(Antlr4P4Parser::InitializerContext *ctx);

    // Type declarations
    P4::IR::Type_Declaration *visitTypeDeclaration(
        Antlr4P4Parser::TypeDeclarationContext *ctx);
    P4::IR::Type_Declaration *visitDerivedTypeDeclaration(
        Antlr4P4Parser::DerivedTypeDeclarationContext *ctx);
    P4::IR::Type_Declaration *visitHeaderTypeDeclaration(
        Antlr4P4Parser::HeaderTypeDeclarationContext *ctx);
    P4::IR::Type_Declaration *visitStructTypeDeclaration(
        Antlr4P4Parser::StructTypeDeclarationContext *ctx);
    P4::IR::Type_Declaration *visitHeaderUnionDeclaration(
        Antlr4P4Parser::HeaderUnionDeclarationContext *ctx);
    P4::IR::IndexedVector<P4::IR::StructField> *visitStructFieldList(
        Antlr4P4Parser::StructFieldListContext *ctx);
    P4::IR::StructField *visitStructField(Antlr4P4Parser::StructFieldContext *ctx);
    P4::IR::Type_Declaration *visitEnumDeclaration(
        Antlr4P4Parser::EnumDeclarationContext *ctx);
    P4::IR::IndexedVector<P4::IR::SerEnumMember> *visitSpecifiedIdentifierList(
        Antlr4P4Parser::SpecifiedIdentifierListContext *ctx);
    P4::IR::SerEnumMember *visitSpecifiedIdentifier(
        Antlr4P4Parser::SpecifiedIdentifierContext *ctx);
    P4::IR::Type_Error *visitErrorDeclaration(
        Antlr4P4Parser::ErrorDeclarationContext *ctx);
    P4::IR::Node *visitMatchKindDeclaration(
        Antlr4P4Parser::MatchKindDeclarationContext *ctx);
    P4::IR::IndexedVector<P4::IR::Declaration_ID> *visitIdentifierList(
        Antlr4P4Parser::IdentifierListContext *ctx);
    P4::IR::Type_Declaration *visitTypedefDeclaration(
        Antlr4P4Parser::TypedefDeclarationContext *ctx);
    P4::IR::Type_Declaration *visitPackageTypeDeclaration(
        Antlr4P4Parser::PackageTypeDeclarationContext *ctx);

    // Extern
    P4::IR::Node *visitExternDeclaration(Antlr4P4Parser::ExternDeclarationContext *ctx);
    P4::IR::Vector<P4::IR::Method> *visitMethodPrototypes(
        Antlr4P4Parser::MethodPrototypesContext *ctx);
    P4::IR::Method *visitFunctionPrototype(Antlr4P4Parser::FunctionPrototypeContext *ctx);
    P4::IR::Method *visitMethodPrototype(Antlr4P4Parser::MethodPrototypeContext *ctx);

    // Parser
    P4::IR::Type_Declaration *visitParserDeclaration(
        Antlr4P4Parser::ParserDeclarationContext *ctx);
    P4::IR::Type_Parser *visitParserTypeDeclaration(
        Antlr4P4Parser::ParserTypeDeclarationContext *ctx);
    P4::IR::IndexedVector<P4::IR::Declaration> *visitParserLocalElements(
        Antlr4P4Parser::ParserLocalElementsContext *ctx);
    P4::IR::Declaration *visitParserLocalElement(
        Antlr4P4Parser::ParserLocalElementContext *ctx);
    P4::IR::IndexedVector<P4::IR::ParserState> *visitParserStates(
        Antlr4P4Parser::ParserStatesContext *ctx);
    P4::IR::ParserState *visitParserState(Antlr4P4Parser::ParserStateContext *ctx);
    P4::IR::IndexedVector<P4::IR::StatOrDecl> *visitParserStatements(
        Antlr4P4Parser::ParserStatementsContext *ctx);
    P4::IR::StatOrDecl *visitParserStatement(Antlr4P4Parser::ParserStatementContext *ctx);
    P4::IR::BlockStatement *visitParserBlockStatement(
        Antlr4P4Parser::ParserBlockStatementContext *ctx);
    P4::IR::Expression *visitTransitionStatement(
        Antlr4P4Parser::TransitionStatementContext *ctx);
    P4::IR::Expression *visitStateExpression(Antlr4P4Parser::StateExpressionContext *ctx);
    P4::IR::Expression *visitSelectExpression(
        Antlr4P4Parser::SelectExpressionContext *ctx);
    P4::IR::Vector<P4::IR::SelectCase> *visitSelectCaseList(
        Antlr4P4Parser::SelectCaseListContext *ctx);
    P4::IR::SelectCase *visitSelectCase(Antlr4P4Parser::SelectCaseContext *ctx);
    P4::IR::Expression *visitKeysetExpression(
        Antlr4P4Parser::KeysetExpressionContext *ctx);
    P4::IR::Vector<P4::IR::Expression> *visitTupleKeysetExpression(
        Antlr4P4Parser::TupleKeysetExpressionContext *ctx);
    P4::IR::Expression *visitSimpleKeysetExpression(
        Antlr4P4Parser::SimpleKeysetExpressionContext *ctx);
    P4::IR::Expression *visitReducedSimpleKeysetExpression(
        Antlr4P4Parser::ReducedSimpleKeysetExpressionContext *ctx);
    P4::IR::Declaration *visitValueSetDeclaration(
        Antlr4P4Parser::ValueSetDeclarationContext *ctx);

    // Control
    P4::IR::Type_Declaration *visitControlDeclaration(
        Antlr4P4Parser::ControlDeclarationContext *ctx);
    P4::IR::Type_Control *visitControlTypeDeclaration(
        Antlr4P4Parser::ControlTypeDeclarationContext *ctx);
    P4::IR::IndexedVector<P4::IR::Declaration> *visitControlLocalDeclarations(
        Antlr4P4Parser::ControlLocalDeclarationsContext *ctx);
    P4::IR::Declaration *visitControlLocalDeclaration(
        Antlr4P4Parser::ControlLocalDeclarationContext *ctx);

    // Action
    P4::IR::Declaration *visitActionDeclaration(
        Antlr4P4Parser::ActionDeclarationContext *ctx);

    // Table
    P4::IR::Declaration *visitTableDeclaration(
        Antlr4P4Parser::TableDeclarationContext *ctx);
    P4::IR::IndexedVector<P4::IR::Property> *visitTablePropertyList(
        Antlr4P4Parser::TablePropertyListContext *ctx);
    P4::IR::Property *visitTableProperty(Antlr4P4Parser::TablePropertyContext *ctx);
    P4::IR::Vector<P4::IR::KeyElement> *visitKeyElementList(
        Antlr4P4Parser::KeyElementListContext *ctx);
    P4::IR::KeyElement *visitKeyElement(Antlr4P4Parser::KeyElementContext *ctx);
    P4::IR::IndexedVector<P4::IR::ActionListElement> *visitActionList(
        Antlr4P4Parser::ActionListContext *ctx);
    P4::IR::Expression *visitActionRef(Antlr4P4Parser::ActionRefContext *ctx);
    P4::IR::Path *visitPrefixedNonTypeName(Antlr4P4Parser::PrefixedNonTypeNameContext *ctx);
    P4::IR::Vector<P4::IR::Entry> *visitEntriesList(
        Antlr4P4Parser::EntriesListContext *ctx);
    P4::IR::Entry *visitEntry(Antlr4P4Parser::EntryContext *ctx);
    P4::IR::Expression *visitEntryPriority(Antlr4P4Parser::EntryPriorityContext *ctx);
    bool visitOptCONST(Antlr4P4Parser::OptCONSTContext *ctx);

    // Function
    P4::IR::Declaration *visitFunctionDeclaration(
        Antlr4P4Parser::FunctionDeclarationContext *ctx);

    // Arguments
    P4::IR::Vector<P4::IR::Argument> *visitArgumentList(
        Antlr4P4Parser::ArgumentListContext *ctx);
    P4::IR::Argument *visitArgument(Antlr4P4Parser::ArgumentContext *ctx);
    P4::IR::Vector<P4::IR::Expression> *visitExpressionList(
        Antlr4P4Parser::ExpressionListContext *ctx);

    // KV pairs
    P4::IR::IndexedVector<P4::IR::NamedExpression> *visitKvList(
        Antlr4P4Parser::KvListContext *ctx);
    P4::IR::NamedExpression *visitKvPair(Antlr4P4Parser::KvPairContext *ctx);

    // Statements
    P4::IR::Statement *visitStatement(Antlr4P4Parser::StatementContext *ctx);
    P4::IR::Statement *visitAssignmentOrMethodCallStatement(
        Antlr4P4Parser::AssignmentOrMethodCallStatementContext *ctx);
    P4::IR::Statement *visitEmptyStatement(Antlr4P4Parser::EmptyStatementContext *ctx);
    P4::IR::Statement *visitExitStatement(Antlr4P4Parser::ExitStatementContext *ctx);
    P4::IR::Statement *visitReturnStatement(Antlr4P4Parser::ReturnStatementContext *ctx);
    P4::IR::Statement *visitConditionalStatement(
        Antlr4P4Parser::ConditionalStatementContext *ctx);
    P4::IR::Statement *visitBreakStatement(Antlr4P4Parser::BreakStatementContext *ctx);
    P4::IR::Statement *visitContinueStatement(
        Antlr4P4Parser::ContinueStatementContext *ctx);
    P4::IR::Statement *visitDirectApplication(
        Antlr4P4Parser::DirectApplicationContext *ctx);
    P4::IR::BlockStatement *visitBlockStatement(
        Antlr4P4Parser::BlockStatementContext *ctx);
    P4::IR::BlockStatement *visitControlBody(Antlr4P4Parser::ControlBodyContext *ctx);
    P4::IR::IndexedVector<P4::IR::StatOrDecl> *visitStatOrDeclList(
        Antlr4P4Parser::StatOrDeclListContext *ctx);
    P4::IR::StatOrDecl *visitStatementOrDeclaration(
        Antlr4P4Parser::StatementOrDeclarationContext *ctx);
    P4::IR::Statement *visitSwitchStatement(Antlr4P4Parser::SwitchStatementContext *ctx);
    P4::IR::Vector<P4::IR::SwitchCase> *visitSwitchCases(
        Antlr4P4Parser::SwitchCasesContext *ctx);
    P4::IR::SwitchCase *visitSwitchCase(Antlr4P4Parser::SwitchCaseContext *ctx);
    P4::IR::Expression *visitSwitchLabel(Antlr4P4Parser::SwitchLabelContext *ctx);
    P4::IR::Statement *visitForStatement(Antlr4P4Parser::ForStatementContext *ctx);

    // Instantiation helpers
    P4::IR::IndexedVector<P4::IR::Parameter> *visitOptConstructorParameters(
        Antlr4P4Parser::OptConstructorParametersContext *ctx);
    P4::IR::BlockStatement *visitOptObjInitializer(
        Antlr4P4Parser::OptObjInitializerContext *ctx);

    // Expressions
    P4::IR::Expression *visitExpression(Antlr4P4Parser::ExpressionContext *ctx);
    P4::IR::Expression *visitNonBraceExpression(
        Antlr4P4Parser::NonBraceExpressionContext *ctx);

    // Lvalue
    P4::IR::Expression *visitLvalue(Antlr4P4Parser::LvalueContext *ctx);

    // Integer parsing helper
    P4::IR::Constant *parseIntegerToken(antlr4::Token *token);

    // Integer constant helper
    P4::UnparsedConstant tokenToUnparsedConstant(const std::string &text);

    SourceInfoFactory sourceInfoFactory;
    P4::Util::InputSources *sources;
    P4::Util::ProgramStructure *structure;

    /// When valid, overrides the source position of every constructed node.
    /// See setSrcInfoOverride().
    P4::Util::SourceInfo srcInfoOverride;

    /// All error declarations are merged
    P4::IR::Type_Error *allErrors = nullptr;
};

}  // namespace P4ANTLR

#endif /* FRONTENDS_P4_ANTLR4_P4IRCONSTRUCTOR_H_ */
