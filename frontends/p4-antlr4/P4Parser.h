
// Generated from P4Parser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  P4Parser : public antlr4::Parser {
public:
  enum {
    ABSTRACT = 1, ACTION = 2, ACTIONS = 3, APPLY = 4, BOOL = 5, BIT = 6, 
    BREAK = 7, CONST = 8, CONTINUE = 9, CONTROL = 10, DEFAULT = 11, ELSE = 12, 
    ENTRIES = 13, ENUM = 14, ERROR = 15, EXIT = 16, EXTERN = 17, FALSE = 18, 
    FOR = 19, HEADER = 20, HEADER_UNION = 21, IF = 22, IN = 23, INOUT = 24, 
    INT = 25, KEY = 26, LIST = 27, MATCH_KIND = 28, TYPE = 29, OUT = 30, 
    PACKAGE = 31, PARSER = 32, PRIORITY = 33, RETURN = 34, SELECT = 35, 
    STATE = 36, STRING_KW = 37, STRUCT = 38, SWITCH = 39, TABLE = 40, THIS = 41, 
    TRANSITION = 42, TRUE = 43, TUPLE = 44, TYPEDEF = 45, VARBIT = 46, VALUE_SET = 47, 
    VOID = 48, ASSIGN_PLUS_SAT = 49, ASSIGN_MINUS_SAT = 50, PLUS_SAT = 51, 
    MINUS_SAT = 52, ASSIGN_SHL = 53, ASSIGN_SHR = 54, DOTS = 55, MASK = 56, 
    LOG_AND = 57, LOG_OR = 58, EQ = 59, NEQ = 60, GEQ = 61, LEQ = 62, SHL = 63, 
    PP = 64, RANGE = 65, ASSIGN_PLUS = 66, ASSIGN_MINUS = 67, ASSIGN_MUL = 68, 
    ASSIGN_DIV = 69, ASSIGN_MOD = 70, ASSIGN_BIT_AND = 71, ASSIGN_BIT_OR = 72, 
    ASSIGN_XOR = 73, INVALID_TOK = 74, ASSIGN = 75, PLUS = 76, MINUS = 77, 
    MUL = 78, DIV = 79, MOD = 80, GT = 81, LT = 82, BIT_AND = 83, BIT_OR = 84, 
    BIT_XOR = 85, BIT_NOT = 86, LOG_NOT = 87, COLON = 88, SEMICOLON = 89, 
    COMMA = 90, DOT = 91, QUESTION = 92, AT = 93, LBRAK = 94, RBRAK = 95, 
    LPAR = 96, RPAR = 97, LCURL = 98, RCURL = 99, DONTCARE = 100, INTEGER = 101, 
    IDENTIFIER = 102, STRING_LITERAL = 103, LINE_DIRECTIVE = 104, WS = 105, 
    BLOCK_COMMENT = 106, LINE_COMMENT = 107
  };

  enum {
    RuleProgram = 0, RuleAnnExpressionList = 1, RuleAnnKvList = 2, RuleAnnIntegerList = 3, 
    RuleAnnIntOrStrList = 4, RuleAnnStringList = 5, RuleAnnExpression = 6, 
    RuleAnnInteger = 7, RuleAnnIntOrStr = 8, RuleAnnStringLiteral = 9, RuleAnnExpressionPair = 10, 
    RuleAnnIntegerPair = 11, RuleAnnStringPair = 12, RuleAnnExpressionTriple = 13, 
    RuleAnnIntegerTriple = 14, RuleAnnStringTriple = 15, RuleAnnP4rtTranslation = 16, 
    RuleIntOrStr = 17, RuleP4rtControllerType = 18, RuleDeclaration = 19, 
    RuleNonTypeName = 20, RuleName = 21, RuleNonTableKwName = 22, RuleAnnotationName = 23, 
    RuleOptAnnotations = 24, RuleAnnotations = 25, RuleAnnotation = 26, 
    RuleAnnotationBody = 27, RuleAnnotationToken = 28, RuleOptTrailingComma = 29, 
    RuleParameterList = 30, RuleNonEmptyParameterList = 31, RuleParameter = 32, 
    RuleDirection = 33, RuleTypeRef = 34, RuleNamedType = 35, RulePrefixedType = 36, 
    RuleTypeName = 37, RuleP4listType = 38, RuleTupleType = 39, RuleSpecializedType = 40, 
    RuleBaseType = 41, RuleTypeOrVoid = 42, RuleOptTypeParameters = 43, 
    RuleTypeParameters = 44, RuleTypeParameterList = 45, RuleTypeArg = 46, 
    RuleTypeArgumentList = 47, RuleRealTypeArg = 48, RuleRealTypeArgumentList = 49, 
    RuleTypeDeclaration = 50, RuleDerivedTypeDeclaration = 51, RuleHeaderTypeDeclaration = 52, 
    RuleStructTypeDeclaration = 53, RuleHeaderUnionDeclaration = 54, RuleStructFieldList = 55, 
    RuleStructField = 56, RuleEnumDeclaration = 57, RuleSpecifiedIdentifierList = 58, 
    RuleSpecifiedIdentifier = 59, RuleErrorDeclaration = 60, RuleMatchKindDeclaration = 61, 
    RuleIdentifierList = 62, RuleTypedefDeclaration = 63, RulePackageTypeDeclaration = 64, 
    RuleParserDeclaration = 65, RuleParserTypeDeclaration = 66, RuleParserLocalElements = 67, 
    RuleParserLocalElement = 68, RuleParserStates = 69, RuleParserState = 70, 
    RuleParserStatements = 71, RuleParserStatement = 72, RuleParserBlockStatement = 73, 
    RuleTransitionStatement = 74, RuleStateExpression = 75, RuleSelectExpression = 76, 
    RuleSelectCaseList = 77, RuleSelectCase = 78, RuleKeysetExpression = 79, 
    RuleTupleKeysetExpression = 80, RuleSimpleExpressionList = 81, RuleReducedSimpleKeysetExpression = 82, 
    RuleSimpleKeysetExpression = 83, RuleValueSetDeclaration = 84, RuleControlDeclaration = 85, 
    RuleControlTypeDeclaration = 86, RuleControlLocalDeclarations = 87, 
    RuleControlLocalDeclaration = 88, RuleControlBody = 89, RuleExternDeclaration = 90, 
    RuleMethodPrototypes = 91, RuleFunctionPrototype = 92, RuleMethodPrototype = 93, 
    RuleInstantiation = 94, RuleOptObjInitializer = 95, RuleObjDeclarations = 96, 
    RuleObjDeclaration = 97, RuleOptConstructorParameters = 98, RuleTableDeclaration = 99, 
    RuleTablePropertyList = 100, RuleTableProperty = 101, RuleOptCONST = 102, 
    RuleKeyElementList = 103, RuleKeyElement = 104, RuleActionList = 105, 
    RuleActionRef = 106, RulePrefixedNonTypeName = 107, RuleEntry = 108, 
    RuleEntryPriority = 109, RuleEntriesList = 110, RuleActionDeclaration = 111, 
    RuleVariableDeclaration = 112, RuleVariableDeclarationWithoutSemicolon = 113, 
    RuleConstantDeclaration = 114, RuleDeclarator = 115, RuleOptInitializer = 116, 
    RuleInitializer = 117, RuleFunctionDeclaration = 118, RuleArgumentList = 119, 
    RuleNonEmptyArgList = 120, RuleArgument = 121, RuleExpressionList = 122, 
    RuleKvList = 123, RuleKvPair = 124, RuleStatement = 125, RuleAssignmentOrMethodCallStatement = 126, 
    RuleEmptyStatement = 127, RuleExitStatement = 128, RuleReturnStatement = 129, 
    RuleConditionalStatement = 130, RuleBreakStatement = 131, RuleContinueStatement = 132, 
    RuleDirectApplication = 133, RuleBlockStatement = 134, RuleStatOrDeclList = 135, 
    RuleStatementOrDeclaration = 136, RuleSwitchStatement = 137, RuleSwitchCases = 138, 
    RuleSwitchCase = 139, RuleSwitchLabel = 140, RuleForStatement = 141, 
    RuleForInitStatements = 142, RuleDeclOrAssignmentOrMethodCallStatement = 143, 
    RuleAssignmentOrMethodCallStatementWithoutSemicolon = 144, RuleForUpdateStatements = 145, 
    RuleForCollectionExpr = 146, RuleLvalue = 147, RuleExpression = 148, 
    RuleNonBraceExpression = 149
  };

  explicit P4Parser(antlr4::TokenStream *input);

  P4Parser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~P4Parser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class AnnExpressionListContext;
  class AnnKvListContext;
  class AnnIntegerListContext;
  class AnnIntOrStrListContext;
  class AnnStringListContext;
  class AnnExpressionContext;
  class AnnIntegerContext;
  class AnnIntOrStrContext;
  class AnnStringLiteralContext;
  class AnnExpressionPairContext;
  class AnnIntegerPairContext;
  class AnnStringPairContext;
  class AnnExpressionTripleContext;
  class AnnIntegerTripleContext;
  class AnnStringTripleContext;
  class AnnP4rtTranslationContext;
  class IntOrStrContext;
  class P4rtControllerTypeContext;
  class DeclarationContext;
  class NonTypeNameContext;
  class NameContext;
  class NonTableKwNameContext;
  class AnnotationNameContext;
  class OptAnnotationsContext;
  class AnnotationsContext;
  class AnnotationContext;
  class AnnotationBodyContext;
  class AnnotationTokenContext;
  class OptTrailingCommaContext;
  class ParameterListContext;
  class NonEmptyParameterListContext;
  class ParameterContext;
  class DirectionContext;
  class TypeRefContext;
  class NamedTypeContext;
  class PrefixedTypeContext;
  class TypeNameContext;
  class P4listTypeContext;
  class TupleTypeContext;
  class SpecializedTypeContext;
  class BaseTypeContext;
  class TypeOrVoidContext;
  class OptTypeParametersContext;
  class TypeParametersContext;
  class TypeParameterListContext;
  class TypeArgContext;
  class TypeArgumentListContext;
  class RealTypeArgContext;
  class RealTypeArgumentListContext;
  class TypeDeclarationContext;
  class DerivedTypeDeclarationContext;
  class HeaderTypeDeclarationContext;
  class StructTypeDeclarationContext;
  class HeaderUnionDeclarationContext;
  class StructFieldListContext;
  class StructFieldContext;
  class EnumDeclarationContext;
  class SpecifiedIdentifierListContext;
  class SpecifiedIdentifierContext;
  class ErrorDeclarationContext;
  class MatchKindDeclarationContext;
  class IdentifierListContext;
  class TypedefDeclarationContext;
  class PackageTypeDeclarationContext;
  class ParserDeclarationContext;
  class ParserTypeDeclarationContext;
  class ParserLocalElementsContext;
  class ParserLocalElementContext;
  class ParserStatesContext;
  class ParserStateContext;
  class ParserStatementsContext;
  class ParserStatementContext;
  class ParserBlockStatementContext;
  class TransitionStatementContext;
  class StateExpressionContext;
  class SelectExpressionContext;
  class SelectCaseListContext;
  class SelectCaseContext;
  class KeysetExpressionContext;
  class TupleKeysetExpressionContext;
  class SimpleExpressionListContext;
  class ReducedSimpleKeysetExpressionContext;
  class SimpleKeysetExpressionContext;
  class ValueSetDeclarationContext;
  class ControlDeclarationContext;
  class ControlTypeDeclarationContext;
  class ControlLocalDeclarationsContext;
  class ControlLocalDeclarationContext;
  class ControlBodyContext;
  class ExternDeclarationContext;
  class MethodPrototypesContext;
  class FunctionPrototypeContext;
  class MethodPrototypeContext;
  class InstantiationContext;
  class OptObjInitializerContext;
  class ObjDeclarationsContext;
  class ObjDeclarationContext;
  class OptConstructorParametersContext;
  class TableDeclarationContext;
  class TablePropertyListContext;
  class TablePropertyContext;
  class OptCONSTContext;
  class KeyElementListContext;
  class KeyElementContext;
  class ActionListContext;
  class ActionRefContext;
  class PrefixedNonTypeNameContext;
  class EntryContext;
  class EntryPriorityContext;
  class EntriesListContext;
  class ActionDeclarationContext;
  class VariableDeclarationContext;
  class VariableDeclarationWithoutSemicolonContext;
  class ConstantDeclarationContext;
  class DeclaratorContext;
  class OptInitializerContext;
  class InitializerContext;
  class FunctionDeclarationContext;
  class ArgumentListContext;
  class NonEmptyArgListContext;
  class ArgumentContext;
  class ExpressionListContext;
  class KvListContext;
  class KvPairContext;
  class StatementContext;
  class AssignmentOrMethodCallStatementContext;
  class EmptyStatementContext;
  class ExitStatementContext;
  class ReturnStatementContext;
  class ConditionalStatementContext;
  class BreakStatementContext;
  class ContinueStatementContext;
  class DirectApplicationContext;
  class BlockStatementContext;
  class StatOrDeclListContext;
  class StatementOrDeclarationContext;
  class SwitchStatementContext;
  class SwitchCasesContext;
  class SwitchCaseContext;
  class SwitchLabelContext;
  class ForStatementContext;
  class ForInitStatementsContext;
  class DeclOrAssignmentOrMethodCallStatementContext;
  class AssignmentOrMethodCallStatementWithoutSemicolonContext;
  class ForUpdateStatementsContext;
  class ForCollectionExprContext;
  class LvalueContext;
  class ExpressionContext;
  class NonBraceExpressionContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  AnnExpressionListContext : public antlr4::ParserRuleContext {
  public:
    AnnExpressionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionListContext *expressionList();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnExpressionListContext* annExpressionList();

  class  AnnKvListContext : public antlr4::ParserRuleContext {
  public:
    AnnKvListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    KvListContext *kvList();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnKvListContext* annKvList();

  class  AnnIntegerListContext : public antlr4::ParserRuleContext {
  public:
    AnnIntegerListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> INTEGER();
    antlr4::tree::TerminalNode* INTEGER(size_t i);
    antlr4::tree::TerminalNode *EOF();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnIntegerListContext* annIntegerList();

  class  AnnIntOrStrListContext : public antlr4::ParserRuleContext {
  public:
    AnnIntOrStrListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IntOrStrContext *> intOrStr();
    IntOrStrContext* intOrStr(size_t i);
    antlr4::tree::TerminalNode *EOF();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnIntOrStrListContext* annIntOrStrList();

  class  AnnStringListContext : public antlr4::ParserRuleContext {
  public:
    AnnStringListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING_LITERAL();
    antlr4::tree::TerminalNode* STRING_LITERAL(size_t i);
    antlr4::tree::TerminalNode *EOF();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnStringListContext* annStringList();

  class  AnnExpressionContext : public antlr4::ParserRuleContext {
  public:
    AnnExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnExpressionContext* annExpression();

  class  AnnIntegerContext : public antlr4::ParserRuleContext {
  public:
    AnnIntegerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnIntegerContext* annInteger();

  class  AnnIntOrStrContext : public antlr4::ParserRuleContext {
  public:
    AnnIntOrStrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IntOrStrContext *intOrStr();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnIntOrStrContext* annIntOrStr();

  class  AnnStringLiteralContext : public antlr4::ParserRuleContext {
  public:
    AnnStringLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnStringLiteralContext* annStringLiteral();

  class  AnnExpressionPairContext : public antlr4::ParserRuleContext {
  public:
    AnnExpressionPairContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnExpressionPairContext* annExpressionPair();

  class  AnnIntegerPairContext : public antlr4::ParserRuleContext {
  public:
    AnnIntegerPairContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> INTEGER();
    antlr4::tree::TerminalNode* INTEGER(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnIntegerPairContext* annIntegerPair();

  class  AnnStringPairContext : public antlr4::ParserRuleContext {
  public:
    AnnStringPairContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING_LITERAL();
    antlr4::tree::TerminalNode* STRING_LITERAL(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnStringPairContext* annStringPair();

  class  AnnExpressionTripleContext : public antlr4::ParserRuleContext {
  public:
    AnnExpressionTripleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnExpressionTripleContext* annExpressionTriple();

  class  AnnIntegerTripleContext : public antlr4::ParserRuleContext {
  public:
    AnnIntegerTripleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> INTEGER();
    antlr4::tree::TerminalNode* INTEGER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnIntegerTripleContext* annIntegerTriple();

  class  AnnStringTripleContext : public antlr4::ParserRuleContext {
  public:
    AnnStringTripleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING_LITERAL();
    antlr4::tree::TerminalNode* STRING_LITERAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnStringTripleContext* annStringTriple();

  class  AnnP4rtTranslationContext : public antlr4::ParserRuleContext {
  public:
    AnnP4rtTranslationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *COMMA();
    P4rtControllerTypeContext *p4rtControllerType();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnP4rtTranslationContext* annP4rtTranslation();

  class  IntOrStrContext : public antlr4::ParserRuleContext {
  public:
    IntOrStrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntOrStrContext* intOrStr();

  class  P4rtControllerTypeContext : public antlr4::ParserRuleContext {
  public:
    P4rtControllerTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_KW();
    antlr4::tree::TerminalNode *BIT();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  P4rtControllerTypeContext* p4rtControllerType();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstantDeclarationContext *constantDeclaration();
    ExternDeclarationContext *externDeclaration();
    ActionDeclarationContext *actionDeclaration();
    ParserDeclarationContext *parserDeclaration();
    TypeDeclarationContext *typeDeclaration();
    ControlDeclarationContext *controlDeclaration();
    InstantiationContext *instantiation();
    ErrorDeclarationContext *errorDeclaration();
    MatchKindDeclarationContext *matchKindDeclaration();
    FunctionDeclarationContext *functionDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationContext* declaration();

  class  NonTypeNameContext : public antlr4::ParserRuleContext {
  public:
    NonTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *APPLY();
    antlr4::tree::TerminalNode *KEY();
    antlr4::tree::TerminalNode *ACTIONS();
    antlr4::tree::TerminalNode *STATE();
    antlr4::tree::TerminalNode *ENTRIES();
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *PRIORITY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NonTypeNameContext* nonTypeName();

  class  NameContext : public antlr4::ParserRuleContext {
  public:
    NameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NonTypeNameContext *nonTypeName();
    antlr4::tree::TerminalNode *LIST();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameContext* name();

  class  NonTableKwNameContext : public antlr4::ParserRuleContext {
  public:
    NonTableKwNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *APPLY();
    antlr4::tree::TerminalNode *STATE();
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *PRIORITY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NonTableKwNameContext* nonTableKwName();

  class  AnnotationNameContext : public antlr4::ParserRuleContext {
  public:
    AnnotationNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ABSTRACT();
    antlr4::tree::TerminalNode *ACTION();
    antlr4::tree::TerminalNode *ACTIONS();
    antlr4::tree::TerminalNode *APPLY();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *BIT();
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *CONST();
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *CONTROL();
    antlr4::tree::TerminalNode *DEFAULT();
    antlr4::tree::TerminalNode *ELSE();
    antlr4::tree::TerminalNode *ENTRIES();
    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *ERROR();
    antlr4::tree::TerminalNode *EXIT();
    antlr4::tree::TerminalNode *EXTERN();
    antlr4::tree::TerminalNode *FALSE();
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *HEADER();
    antlr4::tree::TerminalNode *HEADER_UNION();
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *INOUT();
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *KEY();
    antlr4::tree::TerminalNode *MATCH_KIND();
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *OUT();
    antlr4::tree::TerminalNode *PARSER();
    antlr4::tree::TerminalNode *PACKAGE();
    antlr4::tree::TerminalNode *PRIORITY();
    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *SELECT();
    antlr4::tree::TerminalNode *STATE();
    antlr4::tree::TerminalNode *STRING_KW();
    antlr4::tree::TerminalNode *STRUCT();
    antlr4::tree::TerminalNode *SWITCH();
    antlr4::tree::TerminalNode *TABLE();
    antlr4::tree::TerminalNode *THIS();
    antlr4::tree::TerminalNode *TRANSITION();
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *TUPLE();
    antlr4::tree::TerminalNode *TYPEDEF();
    antlr4::tree::TerminalNode *VARBIT();
    antlr4::tree::TerminalNode *VALUE_SET();
    antlr4::tree::TerminalNode *LIST();
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *DONTCARE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationNameContext* annotationName();

  class  OptAnnotationsContext : public antlr4::ParserRuleContext {
  public:
    OptAnnotationsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnnotationsContext *annotations();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptAnnotationsContext* optAnnotations();

  class  AnnotationsContext : public antlr4::ParserRuleContext {
  public:
    AnnotationsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AnnotationContext *> annotation();
    AnnotationContext* annotation(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationsContext* annotations();

  class  AnnotationContext : public antlr4::ParserRuleContext {
  public:
    AnnotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT();
    AnnotationNameContext *annotationName();
    antlr4::tree::TerminalNode *LPAR();
    AnnotationBodyContext *annotationBody();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *LBRAK();
    ExpressionListContext *expressionList();
    OptTrailingCommaContext *optTrailingComma();
    antlr4::tree::TerminalNode *RBRAK();
    KvListContext *kvList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationContext* annotation();

  class  AnnotationBodyContext : public antlr4::ParserRuleContext {
  public:
    AnnotationBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AnnotationBodyContext *> annotationBody();
    AnnotationBodyContext* annotationBody(size_t i);
    antlr4::tree::TerminalNode *LPAR();
    antlr4::tree::TerminalNode *RPAR();
    AnnotationTokenContext *annotationToken();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationBodyContext* annotationBody();
  AnnotationBodyContext* annotationBody(int precedence);
  class  AnnotationTokenContext : public antlr4::ParserRuleContext {
  public:
    AnnotationTokenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *ABSTRACT();
    antlr4::tree::TerminalNode *ACTION();
    antlr4::tree::TerminalNode *ACTIONS();
    antlr4::tree::TerminalNode *APPLY();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *BIT();
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *CONST();
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *CONTROL();
    antlr4::tree::TerminalNode *DEFAULT();
    antlr4::tree::TerminalNode *ELSE();
    antlr4::tree::TerminalNode *ENTRIES();
    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *ERROR();
    antlr4::tree::TerminalNode *EXIT();
    antlr4::tree::TerminalNode *EXTERN();
    antlr4::tree::TerminalNode *FALSE();
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *HEADER();
    antlr4::tree::TerminalNode *HEADER_UNION();
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *INOUT();
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *KEY();
    antlr4::tree::TerminalNode *MATCH_KIND();
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *OUT();
    antlr4::tree::TerminalNode *PARSER();
    antlr4::tree::TerminalNode *PACKAGE();
    antlr4::tree::TerminalNode *PRIORITY();
    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *SELECT();
    antlr4::tree::TerminalNode *STATE();
    antlr4::tree::TerminalNode *STRING_KW();
    antlr4::tree::TerminalNode *STRUCT();
    antlr4::tree::TerminalNode *SWITCH();
    antlr4::tree::TerminalNode *TABLE();
    antlr4::tree::TerminalNode *THIS();
    antlr4::tree::TerminalNode *TRANSITION();
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *TUPLE();
    antlr4::tree::TerminalNode *TYPEDEF();
    antlr4::tree::TerminalNode *VARBIT();
    antlr4::tree::TerminalNode *VALUE_SET();
    antlr4::tree::TerminalNode *LIST();
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *DONTCARE();
    antlr4::tree::TerminalNode *MASK();
    antlr4::tree::TerminalNode *RANGE();
    antlr4::tree::TerminalNode *SHL();
    antlr4::tree::TerminalNode *LOG_AND();
    antlr4::tree::TerminalNode *LOG_OR();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *GEQ();
    antlr4::tree::TerminalNode *LEQ();
    antlr4::tree::TerminalNode *PP();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *PLUS_SAT();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *MINUS_SAT();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *MOD();
    antlr4::tree::TerminalNode *BIT_OR();
    antlr4::tree::TerminalNode *BIT_AND();
    antlr4::tree::TerminalNode *BIT_XOR();
    antlr4::tree::TerminalNode *BIT_NOT();
    antlr4::tree::TerminalNode *LBRAK();
    antlr4::tree::TerminalNode *RBRAK();
    antlr4::tree::TerminalNode *LCURL();
    antlr4::tree::TerminalNode *RCURL();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LOG_NOT();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *QUESTION();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *AT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationTokenContext* annotationToken();

  class  OptTrailingCommaContext : public antlr4::ParserRuleContext {
  public:
    OptTrailingCommaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COMMA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptTrailingCommaContext* optTrailingComma();

  class  ParameterListContext : public antlr4::ParserRuleContext {
  public:
    ParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NonEmptyParameterListContext *nonEmptyParameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterListContext* parameterList();

  class  NonEmptyParameterListContext : public antlr4::ParserRuleContext {
  public:
    NonEmptyParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParameterContext *> parameter();
    ParameterContext* parameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NonEmptyParameterListContext* nonEmptyParameterList();

  class  ParameterContext : public antlr4::ParserRuleContext {
  public:
    ParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    DirectionContext *direction();
    TypeRefContext *typeRef();
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *ASSIGN();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterContext* parameter();

  class  DirectionContext : public antlr4::ParserRuleContext {
  public:
    DirectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *OUT();
    antlr4::tree::TerminalNode *INOUT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DirectionContext* direction();

  class  TypeRefContext : public antlr4::ParserRuleContext {
  public:
    TypeRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TypeRefContext() = default;
    void copyFrom(TypeRefContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SpecializedTypeRefContext : public TypeRefContext {
  public:
    SpecializedTypeRefContext(TypeRefContext *ctx);

    SpecializedTypeContext *specializedType();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  HeaderStackTypeRefContext : public TypeRefContext {
  public:
    HeaderStackTypeRefContext(TypeRefContext *ctx);

    TypeRefContext *typeRef();
    antlr4::tree::TerminalNode *LBRAK();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRAK();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeNameRefContext : public TypeRefContext {
  public:
    TypeNameRefContext(TypeRefContext *ctx);

    TypeNameContext *typeName();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TupleTypeRefContext : public TypeRefContext {
  public:
    TupleTypeRefContext(TypeRefContext *ctx);

    TupleTypeContext *tupleType();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BaseTypeRefContext : public TypeRefContext {
  public:
    BaseTypeRefContext(TypeRefContext *ctx);

    BaseTypeContext *baseType();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  P4listTypeRefContext : public TypeRefContext {
  public:
    P4listTypeRefContext(TypeRefContext *ctx);

    P4listTypeContext *p4listType();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TypeRefContext* typeRef();
  TypeRefContext* typeRef(int precedence);
  class  NamedTypeContext : public antlr4::ParserRuleContext {
  public:
    NamedTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    SpecializedTypeContext *specializedType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamedTypeContext* namedType();

  class  PrefixedTypeContext : public antlr4::ParserRuleContext {
  public:
    PrefixedTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrefixedTypeContext* prefixedType();

  class  TypeNameContext : public antlr4::ParserRuleContext {
  public:
    TypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrefixedTypeContext *prefixedType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeNameContext* typeName();

  class  P4listTypeContext : public antlr4::ParserRuleContext {
  public:
    P4listTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LIST();
    antlr4::tree::TerminalNode *LT();
    TypeArgContext *typeArg();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  P4listTypeContext* p4listType();

  class  TupleTypeContext : public antlr4::ParserRuleContext {
  public:
    TupleTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TUPLE();
    antlr4::tree::TerminalNode *LT();
    TypeArgumentListContext *typeArgumentList();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TupleTypeContext* tupleType();

  class  SpecializedTypeContext : public antlr4::ParserRuleContext {
  public:
    SpecializedTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    antlr4::tree::TerminalNode *LT();
    TypeArgumentListContext *typeArgumentList();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SpecializedTypeContext* specializedType();

  class  BaseTypeContext : public antlr4::ParserRuleContext {
  public:
    BaseTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *MATCH_KIND();
    antlr4::tree::TerminalNode *ERROR();
    antlr4::tree::TerminalNode *BIT();
    antlr4::tree::TerminalNode *STRING_KW();
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *VARBIT();
    antlr4::tree::TerminalNode *LPAR();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BaseTypeContext* baseType();

  class  TypeOrVoidContext : public antlr4::ParserRuleContext {
  public:
    TypeOrVoidContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeRefContext *typeRef();
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeOrVoidContext* typeOrVoid();

  class  OptTypeParametersContext : public antlr4::ParserRuleContext {
  public:
    OptTypeParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeParametersContext *typeParameters();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptTypeParametersContext* optTypeParameters();

  class  TypeParametersContext : public antlr4::ParserRuleContext {
  public:
    TypeParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    TypeParameterListContext *typeParameterList();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeParametersContext* typeParameters();

  class  TypeParameterListContext : public antlr4::ParserRuleContext {
  public:
    TypeParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NameContext *> name();
    NameContext* name(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeParameterListContext* typeParameterList();

  class  TypeArgContext : public antlr4::ParserRuleContext {
  public:
    TypeArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeRefContext *typeRef();
    NonTypeNameContext *nonTypeName();
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *DONTCARE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeArgContext* typeArg();

  class  TypeArgumentListContext : public antlr4::ParserRuleContext {
  public:
    TypeArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeArgContext *> typeArg();
    TypeArgContext* typeArg(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeArgumentListContext* typeArgumentList();

  class  RealTypeArgContext : public antlr4::ParserRuleContext {
  public:
    RealTypeArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeRefContext *typeRef();
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *DONTCARE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RealTypeArgContext* realTypeArg();

  class  RealTypeArgumentListContext : public antlr4::ParserRuleContext {
  public:
    RealTypeArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RealTypeArgContext *realTypeArg();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    std::vector<TypeArgContext *> typeArg();
    TypeArgContext* typeArg(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RealTypeArgumentListContext* realTypeArgumentList();

  class  TypeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    TypeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DerivedTypeDeclarationContext *derivedTypeDeclaration();
    TypedefDeclarationContext *typedefDeclaration();
    antlr4::tree::TerminalNode *SEMICOLON();
    ParserTypeDeclarationContext *parserTypeDeclaration();
    ControlTypeDeclarationContext *controlTypeDeclaration();
    PackageTypeDeclarationContext *packageTypeDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeDeclarationContext* typeDeclaration();

  class  DerivedTypeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    DerivedTypeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    HeaderTypeDeclarationContext *headerTypeDeclaration();
    HeaderUnionDeclarationContext *headerUnionDeclaration();
    StructTypeDeclarationContext *structTypeDeclaration();
    EnumDeclarationContext *enumDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DerivedTypeDeclarationContext* derivedTypeDeclaration();

  class  HeaderTypeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    HeaderTypeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *HEADER();
    NameContext *name();
    OptTypeParametersContext *optTypeParameters();
    antlr4::tree::TerminalNode *LCURL();
    StructFieldListContext *structFieldList();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  HeaderTypeDeclarationContext* headerTypeDeclaration();

  class  StructTypeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    StructTypeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *STRUCT();
    NameContext *name();
    OptTypeParametersContext *optTypeParameters();
    antlr4::tree::TerminalNode *LCURL();
    StructFieldListContext *structFieldList();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructTypeDeclarationContext* structTypeDeclaration();

  class  HeaderUnionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    HeaderUnionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *HEADER_UNION();
    NameContext *name();
    OptTypeParametersContext *optTypeParameters();
    antlr4::tree::TerminalNode *LCURL();
    StructFieldListContext *structFieldList();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  HeaderUnionDeclarationContext* headerUnionDeclaration();

  class  StructFieldListContext : public antlr4::ParserRuleContext {
  public:
    StructFieldListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StructFieldContext *> structField();
    StructFieldContext* structField(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructFieldListContext* structFieldList();

  class  StructFieldContext : public antlr4::ParserRuleContext {
  public:
    StructFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    TypeRefContext *typeRef();
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructFieldContext* structField();

  class  EnumDeclarationContext : public antlr4::ParserRuleContext {
  public:
    EnumDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *ENUM();
    NameContext *name();
    antlr4::tree::TerminalNode *LCURL();
    IdentifierListContext *identifierList();
    OptTrailingCommaContext *optTrailingComma();
    antlr4::tree::TerminalNode *RCURL();
    TypeRefContext *typeRef();
    SpecifiedIdentifierListContext *specifiedIdentifierList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EnumDeclarationContext* enumDeclaration();

  class  SpecifiedIdentifierListContext : public antlr4::ParserRuleContext {
  public:
    SpecifiedIdentifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SpecifiedIdentifierContext *> specifiedIdentifier();
    SpecifiedIdentifierContext* specifiedIdentifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SpecifiedIdentifierListContext* specifiedIdentifierList();

  class  SpecifiedIdentifierContext : public antlr4::ParserRuleContext {
  public:
    SpecifiedIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NameContext *name();
    antlr4::tree::TerminalNode *ASSIGN();
    InitializerContext *initializer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SpecifiedIdentifierContext* specifiedIdentifier();

  class  ErrorDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ErrorDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ERROR();
    antlr4::tree::TerminalNode *LCURL();
    IdentifierListContext *identifierList();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ErrorDeclarationContext* errorDeclaration();

  class  MatchKindDeclarationContext : public antlr4::ParserRuleContext {
  public:
    MatchKindDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MATCH_KIND();
    antlr4::tree::TerminalNode *LCURL();
    IdentifierListContext *identifierList();
    OptTrailingCommaContext *optTrailingComma();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchKindDeclarationContext* matchKindDeclaration();

  class  IdentifierListContext : public antlr4::ParserRuleContext {
  public:
    IdentifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NameContext *> name();
    NameContext* name(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierListContext* identifierList();

  class  TypedefDeclarationContext : public antlr4::ParserRuleContext {
  public:
    TypedefDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *TYPEDEF();
    TypeRefContext *typeRef();
    DeclaratorContext *declarator();
    DerivedTypeDeclarationContext *derivedTypeDeclaration();
    antlr4::tree::TerminalNode *TYPE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypedefDeclarationContext* typedefDeclaration();

  class  PackageTypeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    PackageTypeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *PACKAGE();
    NameContext *name();
    OptTypeParametersContext *optTypeParameters();
    antlr4::tree::TerminalNode *LPAR();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *RPAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PackageTypeDeclarationContext* packageTypeDeclaration();

  class  ParserDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ParserDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParserTypeDeclarationContext *parserTypeDeclaration();
    OptConstructorParametersContext *optConstructorParameters();
    antlr4::tree::TerminalNode *LCURL();
    ParserLocalElementsContext *parserLocalElements();
    ParserStatesContext *parserStates();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParserDeclarationContext* parserDeclaration();

  class  ParserTypeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ParserTypeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *PARSER();
    NameContext *name();
    OptTypeParametersContext *optTypeParameters();
    antlr4::tree::TerminalNode *LPAR();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *RPAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParserTypeDeclarationContext* parserTypeDeclaration();

  class  ParserLocalElementsContext : public antlr4::ParserRuleContext {
  public:
    ParserLocalElementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParserLocalElementContext *> parserLocalElement();
    ParserLocalElementContext* parserLocalElement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParserLocalElementsContext* parserLocalElements();

  class  ParserLocalElementContext : public antlr4::ParserRuleContext {
  public:
    ParserLocalElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstantDeclarationContext *constantDeclaration();
    InstantiationContext *instantiation();
    VariableDeclarationContext *variableDeclaration();
    ValueSetDeclarationContext *valueSetDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParserLocalElementContext* parserLocalElement();

  class  ParserStatesContext : public antlr4::ParserRuleContext {
  public:
    ParserStatesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParserStateContext *> parserState();
    ParserStateContext* parserState(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParserStatesContext* parserStates();

  class  ParserStateContext : public antlr4::ParserRuleContext {
  public:
    ParserStateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *STATE();
    NameContext *name();
    antlr4::tree::TerminalNode *LCURL();
    ParserStatementsContext *parserStatements();
    TransitionStatementContext *transitionStatement();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParserStateContext* parserState();

  class  ParserStatementsContext : public antlr4::ParserRuleContext {
  public:
    ParserStatementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParserStatementContext *> parserStatement();
    ParserStatementContext* parserStatement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParserStatementsContext* parserStatements();

  class  ParserStatementContext : public antlr4::ParserRuleContext {
  public:
    ParserStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentOrMethodCallStatementContext *assignmentOrMethodCallStatement();
    DirectApplicationContext *directApplication();
    EmptyStatementContext *emptyStatement();
    VariableDeclarationContext *variableDeclaration();
    ConstantDeclarationContext *constantDeclaration();
    ParserBlockStatementContext *parserBlockStatement();
    ConditionalStatementContext *conditionalStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParserStatementContext* parserStatement();

  class  ParserBlockStatementContext : public antlr4::ParserRuleContext {
  public:
    ParserBlockStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *LCURL();
    ParserStatementsContext *parserStatements();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParserBlockStatementContext* parserBlockStatement();

  class  TransitionStatementContext : public antlr4::ParserRuleContext {
  public:
    TransitionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRANSITION();
    StateExpressionContext *stateExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TransitionStatementContext* transitionStatement();

  class  StateExpressionContext : public antlr4::ParserRuleContext {
  public:
    StateExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NameContext *name();
    antlr4::tree::TerminalNode *SEMICOLON();
    SelectExpressionContext *selectExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StateExpressionContext* stateExpression();

  class  SelectExpressionContext : public antlr4::ParserRuleContext {
  public:
    SelectExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SELECT();
    antlr4::tree::TerminalNode *LPAR();
    ExpressionListContext *expressionList();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *LCURL();
    SelectCaseListContext *selectCaseList();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectExpressionContext* selectExpression();

  class  SelectCaseListContext : public antlr4::ParserRuleContext {
  public:
    SelectCaseListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SelectCaseContext *> selectCase();
    SelectCaseContext* selectCase(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectCaseListContext* selectCaseList();

  class  SelectCaseContext : public antlr4::ParserRuleContext {
  public:
    SelectCaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    KeysetExpressionContext *keysetExpression();
    antlr4::tree::TerminalNode *COLON();
    NameContext *name();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectCaseContext* selectCase();

  class  KeysetExpressionContext : public antlr4::ParserRuleContext {
  public:
    KeysetExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TupleKeysetExpressionContext *tupleKeysetExpression();
    SimpleKeysetExpressionContext *simpleKeysetExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeysetExpressionContext* keysetExpression();

  class  TupleKeysetExpressionContext : public antlr4::ParserRuleContext {
  public:
    TupleKeysetExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAR();
    SimpleKeysetExpressionContext *simpleKeysetExpression();
    antlr4::tree::TerminalNode *COMMA();
    SimpleExpressionListContext *simpleExpressionList();
    antlr4::tree::TerminalNode *RPAR();
    ReducedSimpleKeysetExpressionContext *reducedSimpleKeysetExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TupleKeysetExpressionContext* tupleKeysetExpression();

  class  SimpleExpressionListContext : public antlr4::ParserRuleContext {
  public:
    SimpleExpressionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SimpleKeysetExpressionContext *> simpleKeysetExpression();
    SimpleKeysetExpressionContext* simpleKeysetExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleExpressionListContext* simpleExpressionList();

  class  ReducedSimpleKeysetExpressionContext : public antlr4::ParserRuleContext {
  public:
    ReducedSimpleKeysetExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *MASK();
    antlr4::tree::TerminalNode *RANGE();
    antlr4::tree::TerminalNode *DEFAULT();
    antlr4::tree::TerminalNode *DONTCARE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReducedSimpleKeysetExpressionContext* reducedSimpleKeysetExpression();

  class  SimpleKeysetExpressionContext : public antlr4::ParserRuleContext {
  public:
    SimpleKeysetExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *MASK();
    antlr4::tree::TerminalNode *RANGE();
    antlr4::tree::TerminalNode *DEFAULT();
    antlr4::tree::TerminalNode *DONTCARE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleKeysetExpressionContext* simpleKeysetExpression();

  class  ValueSetDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ValueSetDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *VALUE_SET();
    antlr4::tree::TerminalNode *LT();
    BaseTypeContext *baseType();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LPAR();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAR();
    NameContext *name();
    antlr4::tree::TerminalNode *SEMICOLON();
    TupleTypeContext *tupleType();
    TypeNameContext *typeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueSetDeclarationContext* valueSetDeclaration();

  class  ControlDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ControlDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ControlTypeDeclarationContext *controlTypeDeclaration();
    OptConstructorParametersContext *optConstructorParameters();
    antlr4::tree::TerminalNode *LCURL();
    ControlLocalDeclarationsContext *controlLocalDeclarations();
    antlr4::tree::TerminalNode *APPLY();
    ControlBodyContext *controlBody();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ControlDeclarationContext* controlDeclaration();

  class  ControlTypeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ControlTypeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *CONTROL();
    NameContext *name();
    OptTypeParametersContext *optTypeParameters();
    antlr4::tree::TerminalNode *LPAR();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *RPAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ControlTypeDeclarationContext* controlTypeDeclaration();

  class  ControlLocalDeclarationsContext : public antlr4::ParserRuleContext {
  public:
    ControlLocalDeclarationsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ControlLocalDeclarationContext *> controlLocalDeclaration();
    ControlLocalDeclarationContext* controlLocalDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ControlLocalDeclarationsContext* controlLocalDeclarations();

  class  ControlLocalDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ControlLocalDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstantDeclarationContext *constantDeclaration();
    ActionDeclarationContext *actionDeclaration();
    TableDeclarationContext *tableDeclaration();
    InstantiationContext *instantiation();
    VariableDeclarationContext *variableDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ControlLocalDeclarationContext* controlLocalDeclaration();

  class  ControlBodyContext : public antlr4::ParserRuleContext {
  public:
    ControlBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockStatementContext *blockStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ControlBodyContext* controlBody();

  class  ExternDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ExternDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *EXTERN();
    NonTypeNameContext *nonTypeName();
    OptTypeParametersContext *optTypeParameters();
    antlr4::tree::TerminalNode *LCURL();
    MethodPrototypesContext *methodPrototypes();
    antlr4::tree::TerminalNode *RCURL();
    FunctionPrototypeContext *functionPrototype();
    antlr4::tree::TerminalNode *SEMICOLON();
    NameContext *name();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExternDeclarationContext* externDeclaration();

  class  MethodPrototypesContext : public antlr4::ParserRuleContext {
  public:
    MethodPrototypesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MethodPrototypeContext *> methodPrototype();
    MethodPrototypeContext* methodPrototype(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MethodPrototypesContext* methodPrototypes();

  class  FunctionPrototypeContext : public antlr4::ParserRuleContext {
  public:
    FunctionPrototypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeOrVoidContext *typeOrVoid();
    NameContext *name();
    OptTypeParametersContext *optTypeParameters();
    antlr4::tree::TerminalNode *LPAR();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *RPAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionPrototypeContext* functionPrototype();

  class  MethodPrototypeContext : public antlr4::ParserRuleContext {
  public:
    MethodPrototypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    FunctionPrototypeContext *functionPrototype();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *ABSTRACT();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAR();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *RPAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MethodPrototypeContext* methodPrototype();

  class  InstantiationContext : public antlr4::ParserRuleContext {
  public:
    InstantiationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnnotationsContext *annotations();
    TypeRefContext *typeRef();
    antlr4::tree::TerminalNode *LPAR();
    ArgumentListContext *argumentList();
    antlr4::tree::TerminalNode *RPAR();
    DeclaratorContext *declarator();
    OptObjInitializerContext *optObjInitializer();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InstantiationContext* instantiation();

  class  OptObjInitializerContext : public antlr4::ParserRuleContext {
  public:
    OptObjInitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *LCURL();
    ObjDeclarationsContext *objDeclarations();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptObjInitializerContext* optObjInitializer();

  class  ObjDeclarationsContext : public antlr4::ParserRuleContext {
  public:
    ObjDeclarationsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ObjDeclarationContext *> objDeclaration();
    ObjDeclarationContext* objDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ObjDeclarationsContext* objDeclarations();

  class  ObjDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ObjDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionDeclarationContext *functionDeclaration();
    InstantiationContext *instantiation();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ObjDeclarationContext* objDeclaration();

  class  OptConstructorParametersContext : public antlr4::ParserRuleContext {
  public:
    OptConstructorParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAR();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *RPAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptConstructorParametersContext* optConstructorParameters();

  class  TableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    TableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *TABLE();
    NameContext *name();
    antlr4::tree::TerminalNode *LCURL();
    TablePropertyListContext *tablePropertyList();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TableDeclarationContext* tableDeclaration();

  class  TablePropertyListContext : public antlr4::ParserRuleContext {
  public:
    TablePropertyListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TablePropertyContext *> tableProperty();
    TablePropertyContext* tableProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TablePropertyListContext* tablePropertyList();

  class  TablePropertyContext : public antlr4::ParserRuleContext {
  public:
    TablePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEY();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *LCURL();
    KeyElementListContext *keyElementList();
    antlr4::tree::TerminalNode *RCURL();
    antlr4::tree::TerminalNode *ACTIONS();
    ActionListContext *actionList();
    OptAnnotationsContext *optAnnotations();
    OptCONSTContext *optCONST();
    antlr4::tree::TerminalNode *ENTRIES();
    EntriesListContext *entriesList();
    NonTableKwNameContext *nonTableKwName();
    InitializerContext *initializer();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TablePropertyContext* tableProperty();

  class  OptCONSTContext : public antlr4::ParserRuleContext {
  public:
    OptCONSTContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONST();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptCONSTContext* optCONST();

  class  KeyElementListContext : public antlr4::ParserRuleContext {
  public:
    KeyElementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<KeyElementContext *> keyElement();
    KeyElementContext* keyElement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeyElementListContext* keyElementList();

  class  KeyElementContext : public antlr4::ParserRuleContext {
  public:
    KeyElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *COLON();
    NameContext *name();
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeyElementContext* keyElement();

  class  ActionListContext : public antlr4::ParserRuleContext {
  public:
    ActionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<OptAnnotationsContext *> optAnnotations();
    OptAnnotationsContext* optAnnotations(size_t i);
    std::vector<ActionRefContext *> actionRef();
    ActionRefContext* actionRef(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ActionListContext* actionList();

  class  ActionRefContext : public antlr4::ParserRuleContext {
  public:
    ActionRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrefixedNonTypeNameContext *prefixedNonTypeName();
    antlr4::tree::TerminalNode *LPAR();
    ArgumentListContext *argumentList();
    antlr4::tree::TerminalNode *RPAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ActionRefContext* actionRef();

  class  PrefixedNonTypeNameContext : public antlr4::ParserRuleContext {
  public:
    PrefixedNonTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NonTypeNameContext *nonTypeName();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrefixedNonTypeNameContext* prefixedNonTypeName();

  class  EntryContext : public antlr4::ParserRuleContext {
  public:
    EntryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptCONSTContext *optCONST();
    EntryPriorityContext *entryPriority();
    KeysetExpressionContext *keysetExpression();
    antlr4::tree::TerminalNode *COLON();
    ActionRefContext *actionRef();
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EntryContext* entry();

  class  EntryPriorityContext : public antlr4::ParserRuleContext {
  public:
    EntryPriorityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PRIORITY();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *LPAR();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EntryPriorityContext* entryPriority();

  class  EntriesListContext : public antlr4::ParserRuleContext {
  public:
    EntriesListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EntryContext *> entry();
    EntryContext* entry(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EntriesListContext* entriesList();

  class  ActionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ActionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *ACTION();
    NameContext *name();
    antlr4::tree::TerminalNode *LPAR();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *RPAR();
    BlockStatementContext *blockStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ActionDeclarationContext* actionDeclaration();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnnotationsContext *annotations();
    TypeRefContext *typeRef();
    DeclaratorContext *declarator();
    OptInitializerContext *optInitializer();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  VariableDeclarationWithoutSemicolonContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationWithoutSemicolonContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnnotationsContext *annotations();
    TypeRefContext *typeRef();
    DeclaratorContext *declarator();
    OptInitializerContext *optInitializer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationWithoutSemicolonContext* variableDeclarationWithoutSemicolon();

  class  ConstantDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ConstantDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *CONST();
    TypeRefContext *typeRef();
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *ASSIGN();
    InitializerContext *initializer();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantDeclarationContext* constantDeclaration();

  class  DeclaratorContext : public antlr4::ParserRuleContext {
  public:
    DeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NameContext *name();
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *LBRAK();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRAK();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclaratorContext* declarator();
  DeclaratorContext* declarator(int precedence);
  class  OptInitializerContext : public antlr4::ParserRuleContext {
  public:
    OptInitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSIGN();
    InitializerContext *initializer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptInitializerContext* optInitializer();

  class  InitializerContext : public antlr4::ParserRuleContext {
  public:
    InitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitializerContext* initializer();

  class  FunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    FunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AnnotationsContext *annotations();
    FunctionPrototypeContext *functionPrototype();
    BlockStatementContext *blockStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDeclarationContext* functionDeclaration();

  class  ArgumentListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NonEmptyArgListContext *nonEmptyArgList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentListContext* argumentList();

  class  NonEmptyArgListContext : public antlr4::ParserRuleContext {
  public:
    NonEmptyArgListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentContext *> argument();
    ArgumentContext* argument(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NonEmptyArgListContext* nonEmptyArgList();

  class  ArgumentContext : public antlr4::ParserRuleContext {
  public:
    ArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    NameContext *name();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *DONTCARE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentContext* argument();

  class  ExpressionListContext : public antlr4::ParserRuleContext {
  public:
    ExpressionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionListContext* expressionList();

  class  KvListContext : public antlr4::ParserRuleContext {
  public:
    KvListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<KvPairContext *> kvPair();
    KvPairContext* kvPair(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KvListContext* kvList();

  class  KvPairContext : public antlr4::ParserRuleContext {
  public:
    KvPairContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NameContext *name();
    antlr4::tree::TerminalNode *ASSIGN();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KvPairContext* kvPair();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentOrMethodCallStatementContext *assignmentOrMethodCallStatement();
    DirectApplicationContext *directApplication();
    ConditionalStatementContext *conditionalStatement();
    EmptyStatementContext *emptyStatement();
    BlockStatementContext *blockStatement();
    ReturnStatementContext *returnStatement();
    BreakStatementContext *breakStatement();
    ContinueStatementContext *continueStatement();
    ExitStatementContext *exitStatement();
    SwitchStatementContext *switchStatement();
    ForStatementContext *forStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  AssignmentOrMethodCallStatementContext : public antlr4::ParserRuleContext {
  public:
    AssignmentOrMethodCallStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AssignmentOrMethodCallStatementContext() = default;
    void copyFrom(AssignmentOrMethodCallStatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ModAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    ModAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_MOD();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ShrAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    ShrAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_SHR();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BorAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    BorAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_BIT_OR();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BandAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    BandAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_BIT_AND();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddSatAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    AddSatAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_PLUS_SAT();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    AddAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_PLUS();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MethodCallStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    MethodCallStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *LPAR();
    ArgumentListContext *argumentList();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DivAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    DivAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_DIV();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SubSatAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    SubSatAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_MINUS_SAT();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BxorAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    BxorAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_XOR();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeArgsMethodCallStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    TypeArgsMethodCallStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *LT();
    TypeArgumentListContext *typeArgumentList();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LPAR();
    ArgumentListContext *argumentList();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ShlAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    ShlAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_SHL();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MulAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    MulAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_MUL();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignmentStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    AssignmentStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SubAssignStmtContext : public AssignmentOrMethodCallStatementContext {
  public:
    SubAssignStmtContext(AssignmentOrMethodCallStatementContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *ASSIGN_MINUS();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AssignmentOrMethodCallStatementContext* assignmentOrMethodCallStatement();

  class  EmptyStatementContext : public antlr4::ParserRuleContext {
  public:
    EmptyStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EmptyStatementContext* emptyStatement();

  class  ExitStatementContext : public antlr4::ParserRuleContext {
  public:
    ExitStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXIT();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExitStatementContext* exitStatement();

  class  ReturnStatementContext : public antlr4::ParserRuleContext {
  public:
    ReturnStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *SEMICOLON();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnStatementContext* returnStatement();

  class  ConditionalStatementContext : public antlr4::ParserRuleContext {
  public:
    ConditionalStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LPAR();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAR();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *ELSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionalStatementContext* conditionalStatement();

  class  BreakStatementContext : public antlr4::ParserRuleContext {
  public:
    BreakStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BreakStatementContext* breakStatement();

  class  ContinueStatementContext : public antlr4::ParserRuleContext {
  public:
    ContinueStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ContinueStatementContext* continueStatement();

  class  DirectApplicationContext : public antlr4::ParserRuleContext {
  public:
    DirectApplicationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *APPLY();
    antlr4::tree::TerminalNode *LPAR();
    ArgumentListContext *argumentList();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *SEMICOLON();
    SpecializedTypeContext *specializedType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DirectApplicationContext* directApplication();

  class  BlockStatementContext : public antlr4::ParserRuleContext {
  public:
    BlockStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *LCURL();
    StatOrDeclListContext *statOrDeclList();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockStatementContext* blockStatement();

  class  StatOrDeclListContext : public antlr4::ParserRuleContext {
  public:
    StatOrDeclListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementOrDeclarationContext *> statementOrDeclaration();
    StatementOrDeclarationContext* statementOrDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatOrDeclListContext* statOrDeclList();

  class  StatementOrDeclarationContext : public antlr4::ParserRuleContext {
  public:
    StatementOrDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableDeclarationContext *variableDeclaration();
    ConstantDeclarationContext *constantDeclaration();
    StatementContext *statement();
    InstantiationContext *instantiation();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementOrDeclarationContext* statementOrDeclaration();

  class  SwitchStatementContext : public antlr4::ParserRuleContext {
  public:
    SwitchStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SWITCH();
    antlr4::tree::TerminalNode *LPAR();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *LCURL();
    SwitchCasesContext *switchCases();
    antlr4::tree::TerminalNode *RCURL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SwitchStatementContext* switchStatement();

  class  SwitchCasesContext : public antlr4::ParserRuleContext {
  public:
    SwitchCasesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SwitchCaseContext *> switchCase();
    SwitchCaseContext* switchCase(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SwitchCasesContext* switchCases();

  class  SwitchCaseContext : public antlr4::ParserRuleContext {
  public:
    SwitchCaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SwitchLabelContext *switchLabel();
    antlr4::tree::TerminalNode *COLON();
    BlockStatementContext *blockStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SwitchCaseContext* switchCase();

  class  SwitchLabelContext : public antlr4::ParserRuleContext {
  public:
    SwitchLabelContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEFAULT();
    NonBraceExpressionContext *nonBraceExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SwitchLabelContext* switchLabel();

  class  ForStatementContext : public antlr4::ParserRuleContext {
  public:
    ForStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAnnotationsContext *optAnnotations();
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *LPAR();
    ForInitStatementsContext *forInitStatements();
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);
    ExpressionContext *expression();
    ForUpdateStatementsContext *forUpdateStatements();
    antlr4::tree::TerminalNode *RPAR();
    StatementContext *statement();
    TypeRefContext *typeRef();
    NameContext *name();
    antlr4::tree::TerminalNode *IN();
    ForCollectionExprContext *forCollectionExpr();
    AnnotationsContext *annotations();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForStatementContext* forStatement();

  class  ForInitStatementsContext : public antlr4::ParserRuleContext {
  public:
    ForInitStatementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DeclOrAssignmentOrMethodCallStatementContext *> declOrAssignmentOrMethodCallStatement();
    DeclOrAssignmentOrMethodCallStatementContext* declOrAssignmentOrMethodCallStatement(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForInitStatementsContext* forInitStatements();

  class  DeclOrAssignmentOrMethodCallStatementContext : public antlr4::ParserRuleContext {
  public:
    DeclOrAssignmentOrMethodCallStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableDeclarationWithoutSemicolonContext *variableDeclarationWithoutSemicolon();
    AssignmentOrMethodCallStatementWithoutSemicolonContext *assignmentOrMethodCallStatementWithoutSemicolon();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclOrAssignmentOrMethodCallStatementContext* declOrAssignmentOrMethodCallStatement();

  class  AssignmentOrMethodCallStatementWithoutSemicolonContext : public antlr4::ParserRuleContext {
  public:
    AssignmentOrMethodCallStatementWithoutSemicolonContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *LPAR();
    ArgumentListContext *argumentList();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *LT();
    TypeArgumentListContext *typeArgumentList();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *ASSIGN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ASSIGN_MUL();
    antlr4::tree::TerminalNode *ASSIGN_DIV();
    antlr4::tree::TerminalNode *ASSIGN_MOD();
    antlr4::tree::TerminalNode *ASSIGN_PLUS();
    antlr4::tree::TerminalNode *ASSIGN_MINUS();
    antlr4::tree::TerminalNode *ASSIGN_PLUS_SAT();
    antlr4::tree::TerminalNode *ASSIGN_MINUS_SAT();
    antlr4::tree::TerminalNode *ASSIGN_SHL();
    antlr4::tree::TerminalNode *ASSIGN_SHR();
    antlr4::tree::TerminalNode *ASSIGN_BIT_AND();
    antlr4::tree::TerminalNode *ASSIGN_BIT_OR();
    antlr4::tree::TerminalNode *ASSIGN_XOR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentOrMethodCallStatementWithoutSemicolonContext* assignmentOrMethodCallStatementWithoutSemicolon();

  class  ForUpdateStatementsContext : public antlr4::ParserRuleContext {
  public:
    ForUpdateStatementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AssignmentOrMethodCallStatementWithoutSemicolonContext *> assignmentOrMethodCallStatementWithoutSemicolon();
    AssignmentOrMethodCallStatementWithoutSemicolonContext* assignmentOrMethodCallStatementWithoutSemicolon(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForUpdateStatementsContext* forUpdateStatements();

  class  ForCollectionExprContext : public antlr4::ParserRuleContext {
  public:
    ForCollectionExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *RANGE();
    TypeRefContext *typeRef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForCollectionExprContext* forCollectionExpr();

  class  LvalueContext : public antlr4::ParserRuleContext {
  public:
    LvalueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LvalueContext() = default;
    void copyFrom(LvalueContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MemberLvalueContext : public LvalueContext {
  public:
    MemberLvalueContext(LvalueContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *DOT();
    NameContext *name();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IndexLvalueContext : public LvalueContext {
  public:
    IndexLvalueContext(LvalueContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *LBRAK();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRAK();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenLvalueContext : public LvalueContext {
  public:
    ParenLvalueContext(LvalueContext *ctx);

    antlr4::tree::TerminalNode *LPAR();
    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *RPAR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PlusSliceLvalueContext : public LvalueContext {
  public:
    PlusSliceLvalueContext(LvalueContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *LBRAK();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *RBRAK();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PathLvalueContext : public LvalueContext {
  public:
    PathLvalueContext(LvalueContext *ctx);

    PrefixedNonTypeNameContext *prefixedNonTypeName();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SliceLvalueContext : public LvalueContext {
  public:
    SliceLvalueContext(LvalueContext *ctx);

    LvalueContext *lvalue();
    antlr4::tree::TerminalNode *LBRAK();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *RBRAK();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ThisLvalueContext : public LvalueContext {
  public:
    ThisLvalueContext(LvalueContext *ctx);

    antlr4::tree::TerminalNode *THIS();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LvalueContext* lvalue();
  LvalueContext* lvalue(int precedence);
  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ThisExprContext : public ExpressionContext {
  public:
    ThisExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *THIS();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StructDotsExprContext : public ExpressionContext {
  public:
    StructDotsExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *LCURL();
    KvListContext *kvList();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *DOTS();
    OptTrailingCommaContext *optTrailingComma();
    antlr4::tree::TerminalNode *RCURL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntegerExprContext : public ExpressionContext {
  public:
    IntegerExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *INTEGER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ModExprContext : public ExpressionContext {
  public:
    ModExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *MOD();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CastExprContext : public ExpressionContext {
  public:
    CastExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAR();
    TypeRefContext *typeRef();
    antlr4::tree::TerminalNode *RPAR();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TrueExprContext : public ExpressionContext {
  public:
    TrueExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *TRUE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SubExprContext : public ExpressionContext {
  public:
    SubExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *MINUS();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BandExprContext : public ExpressionContext {
  public:
    BandExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *BIT_AND();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenExprContext : public ExpressionContext {
  public:
    ParenExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAR();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConcatExprContext : public ExpressionContext {
  public:
    ConcatExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *PP();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NeqExprContext : public ExpressionContext {
  public:
    NeqExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *NEQ();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeCallExprContext : public ExpressionContext {
  public:
    TypeCallExprContext(ExpressionContext *ctx);

    ExpressionContext *expression();
    antlr4::tree::TerminalNode *LT();
    RealTypeArgumentListContext *realTypeArgumentList();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LPAR();
    ArgumentListContext *argumentList();
    antlr4::tree::TerminalNode *RPAR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GrtExprContext : public ExpressionContext {
  public:
    GrtExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *GT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MethodCallExprContext : public ExpressionContext {
  public:
    MethodCallExprContext(ExpressionContext *ctx);

    ExpressionContext *expression();
    antlr4::tree::TerminalNode *LPAR();
    ArgumentListContext *argumentList();
    antlr4::tree::TerminalNode *RPAR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LandExprContext : public ExpressionContext {
  public:
    LandExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LOG_AND();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TernaryExprContext : public ExpressionContext {
  public:
    TernaryExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *QUESTION();
    antlr4::tree::TerminalNode *COLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LorExprContext : public ExpressionContext {
  public:
    LorExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LOG_OR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StructExprContext : public ExpressionContext {
  public:
    StructExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *LCURL();
    KvListContext *kvList();
    OptTrailingCommaContext *optTrailingComma();
    antlr4::tree::TerminalNode *RCURL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MulExprContext : public ExpressionContext {
  public:
    MulExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *MUL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DivExprContext : public ExpressionContext {
  public:
    DivExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *DIV();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FalseExprContext : public ExpressionContext {
  public:
    FalseExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *FALSE();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ListExprContext : public ExpressionContext {
  public:
    ListExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *LCURL();
    ExpressionListContext *expressionList();
    OptTrailingCommaContext *optTrailingComma();
    antlr4::tree::TerminalNode *RCURL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ShrExprContext : public ExpressionContext {
  public:
    ShrExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GT();
    antlr4::tree::TerminalNode* GT(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstructorCallExprContext : public ExpressionContext {
  public:
    ConstructorCallExprContext(ExpressionContext *ctx);

    NamedTypeContext *namedType();
    antlr4::tree::TerminalNode *LPAR();
    ArgumentListContext *argumentList();
    antlr4::tree::TerminalNode *RPAR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StringLiteralExprContext : public ExpressionContext {
  public:
    StringLiteralExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *STRING_LITERAL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InvalidExprContext : public ExpressionContext {
  public:
    InvalidExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *INVALID_TOK();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LnotExprContext : public ExpressionContext {
  public:
    LnotExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *LOG_NOT();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MemberExprContext : public ExpressionContext {
  public:
    MemberExprContext(ExpressionContext *ctx);

    ExpressionContext *expression();
    antlr4::tree::TerminalNode *DOT();
    NameContext *name();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PlusSliceExprContext : public ExpressionContext {
  public:
    PlusSliceExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LBRAK();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *RBRAK();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddSatExprContext : public ExpressionContext {
  public:
    AddSatExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *PLUS_SAT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayIndexExprContext : public ExpressionContext {
  public:
    ArrayIndexExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LBRAK();
    antlr4::tree::TerminalNode *RBRAK();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UplusExprContext : public ExpressionContext {
  public:
    UplusExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *PLUS();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SliceExprContext : public ExpressionContext {
  public:
    SliceExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LBRAK();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *RBRAK();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DotsExprContext : public ExpressionContext {
  public:
    DotsExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *DOTS();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BorExprContext : public ExpressionContext {
  public:
    BorExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *BIT_OR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ErrorMemberExprContext : public ExpressionContext {
  public:
    ErrorMemberExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *ERROR();
    antlr4::tree::TerminalNode *DOT();
    NameContext *name();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EqExprContext : public ExpressionContext {
  public:
    EqExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *EQ();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddExprContext : public ExpressionContext {
  public:
    AddExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *PLUS();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LssExprContext : public ExpressionContext {
  public:
    LssExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CmplExprContext : public ExpressionContext {
  public:
    CmplExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *BIT_NOT();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NegExprContext : public ExpressionContext {
  public:
    NegExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *MINUS();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PathExprContext : public ExpressionContext {
  public:
    PathExprContext(ExpressionContext *ctx);

    PrefixedNonTypeNameContext *prefixedNonTypeName();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LeqExprContext : public ExpressionContext {
  public:
    LeqExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LEQ();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ShlExprContext : public ExpressionContext {
  public:
    ShlExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *SHL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GeqExprContext : public ExpressionContext {
  public:
    GeqExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *GEQ();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SubSatExprContext : public ExpressionContext {
  public:
    SubSatExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *MINUS_SAT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BxorExprContext : public ExpressionContext {
  public:
    BxorExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *BIT_XOR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  NonBraceExpressionContext : public antlr4::ParserRuleContext {
  public:
    NonBraceExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NonBraceExpressionContext* nonBraceExpression();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool annotationBodySempred(AnnotationBodyContext *_localctx, size_t predicateIndex);
  bool typeRefSempred(TypeRefContext *_localctx, size_t predicateIndex);
  bool declaratorSempred(DeclaratorContext *_localctx, size_t predicateIndex);
  bool lvalueSempred(LvalueContext *_localctx, size_t predicateIndex);
  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

