parser grammar P4Parser;

options { tokenVocab=P4Lexer; }

//===----------------------------------------------------------------------===//
// Top-level program
//===----------------------------------------------------------------------===//

program
    : (declaration | SEMICOLON)* EOF
    ;

//===----------------------------------------------------------------------===//
// Annotation-body fragment entry points
//
// P4-16 annotations are captured by the main parser as an opaque token stream
// (`annotationBody`). They are re-parsed later by `ParseAnnotations` depending
// on the annotation name. Each fragment rule below is a separate parser entry
// point; end with EOF so the re-parser rejects trailing garbage.
//===----------------------------------------------------------------------===//

annExpressionList : expressionList EOF ;
annKvList         : kvList EOF ;
annIntegerList    : INTEGER (COMMA INTEGER)* EOF ;
annIntOrStrList   : intOrStr (COMMA intOrStr)* EOF ;
annStringList     : STRING_LITERAL (COMMA STRING_LITERAL)* EOF ;

annExpression     : expression EOF ;
annInteger        : INTEGER EOF ;
annIntOrStr       : intOrStr EOF ;
annStringLiteral  : STRING_LITERAL EOF ;

annExpressionPair : expression COMMA expression EOF ;
annIntegerPair    : INTEGER COMMA INTEGER EOF ;
annStringPair     : STRING_LITERAL COMMA STRING_LITERAL EOF ;

annExpressionTriple : expression COMMA expression COMMA expression EOF ;
annIntegerTriple    : INTEGER COMMA INTEGER COMMA INTEGER EOF ;
annStringTriple     : STRING_LITERAL COMMA STRING_LITERAL COMMA STRING_LITERAL EOF ;

annP4rtTranslation  : STRING_LITERAL COMMA p4rtControllerType EOF ;

intOrStr
    : INTEGER
    | STRING_LITERAL
    ;

// @p4runtime_translation second argument: either the `string` keyword,
// `bit<N>`, or a bare integer (legacy pre-P4RT-2.0 syntax).
p4rtControllerType
    : STRING_KW
    | BIT LT INTEGER GT
    | INTEGER
    ;

declaration
    : constantDeclaration
    | externDeclaration
    | actionDeclaration
    | parserDeclaration
    | typeDeclaration
    | controlDeclaration
    | instantiation
    | errorDeclaration
    | matchKindDeclaration
    | functionDeclaration
    ;

//===----------------------------------------------------------------------===//
// Names
//===----------------------------------------------------------------------===//

nonTypeName
    : IDENTIFIER
    | APPLY
    | KEY
    | ACTIONS
    | STATE
    | ENTRIES
    | TYPE
    | PRIORITY
    ;

name
    : nonTypeName
    | LIST
    ;

nonTableKwName
    : IDENTIFIER
    | APPLY
    | STATE
    | TYPE
    | PRIORITY
    ;

annotationName
    : IDENTIFIER
    | ABSTRACT | ACTION | ACTIONS | APPLY | BOOL | BIT | BREAK | CONST
    | CONTINUE | CONTROL | DEFAULT | ELSE | ENTRIES | ENUM | ERROR | EXIT
    | EXTERN | FALSE | FOR | HEADER | HEADER_UNION | IF | IN | INOUT | INT
    | KEY | MATCH_KIND | TYPE | OUT | PARSER | PACKAGE | PRIORITY | RETURN
    | SELECT | STATE | STRING_KW | STRUCT | SWITCH | TABLE | THIS
    | TRANSITION | TRUE | TUPLE | TYPEDEF | VARBIT | VALUE_SET | LIST | VOID
    | DONTCARE
    ;

//===----------------------------------------------------------------------===//
// Annotations
//===----------------------------------------------------------------------===//

optAnnotations
    : /* empty */
    | annotations
    ;

annotations
    : annotation+
    ;

annotation
    : AT annotationName
    | AT annotationName LPAR annotationBody RPAR
    | AT annotationName LBRAK expressionList optTrailingComma RBRAK
    | AT annotationName LBRAK kvList optTrailingComma RBRAK
    ;

annotationBody
    : /* empty */
    | annotationBody LPAR annotationBody RPAR
    | annotationBody annotationToken
    ;

annotationToken
    : IDENTIFIER | INTEGER | STRING_LITERAL
    | ABSTRACT | ACTION | ACTIONS | APPLY | BOOL | BIT | BREAK | CONST
    | CONTINUE | CONTROL | DEFAULT | ELSE | ENTRIES | ENUM | ERROR | EXIT
    | EXTERN | FALSE | FOR | HEADER | HEADER_UNION | IF | IN | INOUT | INT
    | KEY | MATCH_KIND | TYPE | OUT | PARSER | PACKAGE | PRIORITY | RETURN
    | SELECT | STATE | STRING_KW | STRUCT | SWITCH | TABLE | THIS
    | TRANSITION | TRUE | TUPLE | TYPEDEF | VARBIT | VALUE_SET | LIST | VOID
    | DONTCARE
    | MASK | RANGE | SHL | LOG_AND | LOG_OR | EQ | NEQ | GEQ | LEQ | PP
    | PLUS | PLUS_SAT | MINUS | MINUS_SAT | MUL | DIV | MOD
    | BIT_OR | BIT_AND | BIT_XOR | BIT_NOT
    | LBRAK | RBRAK | LCURL | RCURL | LT | GT
    | LOG_NOT | COLON | COMMA | QUESTION | DOT | ASSIGN | SEMICOLON | AT
    ;

optTrailingComma
    : /* empty */
    | COMMA
    ;

//===----------------------------------------------------------------------===//
// Parameters
//===----------------------------------------------------------------------===//

parameterList
    : /* empty */
    | nonEmptyParameterList
    ;

nonEmptyParameterList
    : parameter (COMMA parameter)*
    ;

parameter
    : optAnnotations direction typeRef declarator (ASSIGN expression)?
    ;

direction
    : IN
    | OUT
    | INOUT
    | /* empty (None) */
    ;

//===----------------------------------------------------------------------===//
// Types
//===----------------------------------------------------------------------===//

typeRef
    : baseType                                                 # baseTypeRef
    | typeName                                                 # typeNameRef
    | specializedType                                          # specializedTypeRef
    | typeRef LBRAK expression RBRAK                           # headerStackTypeRef
    | p4listType                                               # p4listTypeRef
    | tupleType                                                # tupleTypeRef
    ;

namedType
    : typeName
    | specializedType
    ;

prefixedType
    : IDENTIFIER
    | DOT IDENTIFIER
    ;

typeName
    : prefixedType
    ;

p4listType
    : LIST LT typeArg GT
    ;

tupleType
    : TUPLE LT typeArgumentList GT
    ;

specializedType
    : typeName LT typeArgumentList GT
    ;

baseType
    : BOOL
    | MATCH_KIND
    | ERROR
    | BIT
    | STRING_KW
    | INT
    | BIT LT INTEGER GT
    | INT LT INTEGER GT
    | VARBIT LT INTEGER GT
    | BIT LT LPAR expression RPAR GT
    | INT LT LPAR expression RPAR GT
    | VARBIT LT LPAR expression RPAR GT
    ;

typeOrVoid
    : typeRef
    | VOID
    | IDENTIFIER  // template args may introduce return type
    ;

optTypeParameters
    : /* empty */
    | typeParameters
    ;

typeParameters
    : LT typeParameterList GT
    ;

typeParameterList
    : name (COMMA name)*
    ;

typeArg
    : typeRef
    | nonTypeName  // template args may introduce return type
    | VOID
    | DONTCARE
    ;

typeArgumentList
    : /* empty */
    | typeArg (COMMA typeArg)*
    ;

realTypeArg
    : typeRef
    | VOID
    | DONTCARE
    ;

realTypeArgumentList
    : realTypeArg (COMMA typeArg)*
    ;

typeDeclaration
    : derivedTypeDeclaration
    | typedefDeclaration SEMICOLON
    | parserTypeDeclaration SEMICOLON
    | controlTypeDeclaration SEMICOLON
    | packageTypeDeclaration SEMICOLON
    ;

derivedTypeDeclaration
    : headerTypeDeclaration
    | headerUnionDeclaration
    | structTypeDeclaration
    | enumDeclaration
    ;

//===----------------------------------------------------------------------===//
// Header / Struct / Union / Enum
//===----------------------------------------------------------------------===//

headerTypeDeclaration
    : optAnnotations HEADER name optTypeParameters LCURL structFieldList RCURL
    ;

structTypeDeclaration
    : optAnnotations STRUCT name optTypeParameters LCURL structFieldList RCURL
    ;

headerUnionDeclaration
    : optAnnotations HEADER_UNION name optTypeParameters LCURL structFieldList RCURL
    ;

structFieldList
    : structField*
    ;

structField
    : optAnnotations typeRef declarator SEMICOLON
    ;

enumDeclaration
    : optAnnotations ENUM name LCURL identifierList optTrailingComma RCURL
    | optAnnotations ENUM typeRef name LCURL specifiedIdentifierList optTrailingComma RCURL
    ;

specifiedIdentifierList
    : specifiedIdentifier (COMMA specifiedIdentifier)*
    ;

specifiedIdentifier
    : name ASSIGN initializer
    ;

errorDeclaration
    : ERROR LCURL identifierList RCURL
    ;

matchKindDeclaration
    : MATCH_KIND LCURL identifierList optTrailingComma RCURL
    ;

identifierList
    : name (COMMA name)*
    ;

typedefDeclaration
    : optAnnotations TYPEDEF typeRef declarator
    | optAnnotations TYPEDEF derivedTypeDeclaration declarator
    | optAnnotations TYPE typeRef declarator
    ;

//===----------------------------------------------------------------------===//
// Package
//===----------------------------------------------------------------------===//

packageTypeDeclaration
    : optAnnotations PACKAGE name optTypeParameters LPAR parameterList RPAR
    ;

//===----------------------------------------------------------------------===//
// Parser
//===----------------------------------------------------------------------===//

parserDeclaration
    : parserTypeDeclaration optConstructorParameters
      LCURL parserLocalElements parserStates RCURL
    ;

parserTypeDeclaration
    : optAnnotations PARSER name optTypeParameters LPAR parameterList RPAR
    ;

parserLocalElements
    : parserLocalElement*
    ;

parserLocalElement
    : constantDeclaration
    | instantiation
    | variableDeclaration
    | valueSetDeclaration
    ;

parserStates
    : parserState+
    ;

parserState
    : optAnnotations STATE name LCURL parserStatements transitionStatement RCURL
    ;

parserStatements
    : parserStatement*
    ;

parserStatement
    : assignmentOrMethodCallStatement
    | directApplication
    | emptyStatement
    | variableDeclaration
    | constantDeclaration
    | parserBlockStatement
    | conditionalStatement
    ;

parserBlockStatement
    : optAnnotations LCURL parserStatements RCURL
    ;

transitionStatement
    : /* empty */
    | TRANSITION stateExpression
    ;

stateExpression
    : name SEMICOLON
    | selectExpression
    ;

selectExpression
    : SELECT LPAR expressionList RPAR LCURL selectCaseList RCURL
    ;

selectCaseList
    : selectCase*
    ;

selectCase
    : keysetExpression COLON name SEMICOLON
    ;

keysetExpression
    : tupleKeysetExpression
    | simpleKeysetExpression
    ;

tupleKeysetExpression
    : LPAR simpleKeysetExpression COMMA simpleExpressionList RPAR
    | LPAR reducedSimpleKeysetExpression RPAR
    ;

simpleExpressionList
    : simpleKeysetExpression (COMMA simpleKeysetExpression)*
    ;

reducedSimpleKeysetExpression
    : expression MASK expression
    | expression RANGE expression
    | DEFAULT
    | DONTCARE
    ;

simpleKeysetExpression
    : expression
    | expression MASK expression
    | expression RANGE expression
    | DEFAULT
    | DONTCARE
    ;

valueSetDeclaration
    : optAnnotations VALUE_SET LT baseType GT LPAR expression RPAR name SEMICOLON
    | optAnnotations VALUE_SET LT tupleType GT LPAR expression RPAR name SEMICOLON
    | optAnnotations VALUE_SET LT typeName GT LPAR expression RPAR name SEMICOLON
    ;

//===----------------------------------------------------------------------===//
// Control
//===----------------------------------------------------------------------===//

controlDeclaration
    : controlTypeDeclaration optConstructorParameters
      LCURL controlLocalDeclarations APPLY controlBody RCURL
    ;

controlTypeDeclaration
    : optAnnotations CONTROL name optTypeParameters LPAR parameterList RPAR
    ;

controlLocalDeclarations
    : controlLocalDeclaration*
    ;

controlLocalDeclaration
    : constantDeclaration
    | actionDeclaration
    | tableDeclaration
    | instantiation
    | variableDeclaration
    ;

controlBody
    : blockStatement
    ;

//===----------------------------------------------------------------------===//
// Extern
//===----------------------------------------------------------------------===//

externDeclaration
    : optAnnotations EXTERN nonTypeName optTypeParameters
      LCURL methodPrototypes RCURL
    | optAnnotations EXTERN functionPrototype SEMICOLON
    | optAnnotations EXTERN name SEMICOLON  // forward declaration
    ;

methodPrototypes
    : methodPrototype*
    ;

functionPrototype
    : typeOrVoid name optTypeParameters LPAR parameterList RPAR
    ;

methodPrototype
    : optAnnotations functionPrototype SEMICOLON
    | optAnnotations ABSTRACT functionPrototype SEMICOLON
    | optAnnotations IDENTIFIER LPAR parameterList RPAR SEMICOLON  // constructor
    ;

//===----------------------------------------------------------------------===//
// Instantiation
//===----------------------------------------------------------------------===//

instantiation
    : annotations typeRef LPAR argumentList RPAR declarator optObjInitializer SEMICOLON
    | typeRef LPAR argumentList RPAR declarator optObjInitializer SEMICOLON
    ;

optObjInitializer
    : /* empty */
    | ASSIGN LCURL objDeclarations RCURL
    ;

objDeclarations
    : objDeclaration*
    ;

objDeclaration
    : functionDeclaration
    | instantiation
    ;

optConstructorParameters
    : /* empty */
    | LPAR parameterList RPAR
    ;

//===----------------------------------------------------------------------===//
// Table
//===----------------------------------------------------------------------===//

tableDeclaration
    : optAnnotations TABLE name LCURL tablePropertyList RCURL
    ;

tablePropertyList
    : tableProperty+
    ;

tableProperty
    : KEY ASSIGN LCURL keyElementList RCURL
    | ACTIONS ASSIGN LCURL actionList RCURL
    | optAnnotations optCONST ENTRIES ASSIGN LCURL entriesList RCURL
    | optAnnotations optCONST nonTableKwName ASSIGN initializer SEMICOLON
    ;

optCONST
    : /* empty */
    | CONST
    ;

keyElementList
    : keyElement*
    ;

keyElement
    : expression COLON name optAnnotations SEMICOLON
    ;

actionList
    : (optAnnotations actionRef SEMICOLON)*
    ;

actionRef
    : prefixedNonTypeName
    | prefixedNonTypeName LPAR argumentList RPAR
    ;

prefixedNonTypeName
    : nonTypeName
    | DOT nonTypeName
    ;

entry
    : optCONST entryPriority keysetExpression COLON actionRef optAnnotations SEMICOLON
    | optCONST keysetExpression COLON actionRef optAnnotations SEMICOLON
    ;

entryPriority
    : PRIORITY ASSIGN INTEGER COLON
    | PRIORITY ASSIGN LPAR expression RPAR COLON
    ;

entriesList
    : entry*
    ;

//===----------------------------------------------------------------------===//
// Action
//===----------------------------------------------------------------------===//

actionDeclaration
    : optAnnotations ACTION name LPAR parameterList RPAR blockStatement
    ;

//===----------------------------------------------------------------------===//
// Variables / Constants
//===----------------------------------------------------------------------===//

variableDeclaration
    : annotations typeRef declarator optInitializer SEMICOLON
    | typeRef declarator optInitializer SEMICOLON
    ;

variableDeclarationWithoutSemicolon
    : annotations typeRef declarator optInitializer
    | typeRef declarator optInitializer
    ;

constantDeclaration
    : optAnnotations CONST typeRef declarator ASSIGN initializer SEMICOLON
    ;

declarator
    : name
    | declarator LBRAK expression RBRAK
    ;

optInitializer
    : /* empty */
    | ASSIGN initializer
    ;

initializer
    : expression
    ;

//===----------------------------------------------------------------------===//
// Functions
//===----------------------------------------------------------------------===//

functionDeclaration
    : annotations functionPrototype blockStatement
    | functionPrototype blockStatement
    ;

//===----------------------------------------------------------------------===//
// Arguments
//===----------------------------------------------------------------------===//

argumentList
    : /* empty */
    | nonEmptyArgList
    ;

nonEmptyArgList
    : argument (COMMA argument)*
    ;

argument
    : expression
    | name ASSIGN expression
    | DONTCARE
    | name ASSIGN DONTCARE
    ;

expressionList
    : /* empty */
    | expression (COMMA expression)*
    ;

//===----------------------------------------------------------------------===//
// KV pairs (for structured annotations)
//===----------------------------------------------------------------------===//

kvList
    : kvPair (COMMA kvPair)*
    ;

kvPair
    : name ASSIGN expression
    ;

//===----------------------------------------------------------------------===//
// Statements
//===----------------------------------------------------------------------===//

statement
    : assignmentOrMethodCallStatement
    | directApplication
    | conditionalStatement
    | emptyStatement
    | blockStatement
    | returnStatement
    | breakStatement
    | continueStatement
    | exitStatement
    | switchStatement
    | forStatement
    ;

assignmentOrMethodCallStatement
    : lvalue LPAR argumentList RPAR SEMICOLON                                    # methodCallStmt
    | lvalue LT typeArgumentList GT LPAR argumentList RPAR SEMICOLON             # typeArgsMethodCallStmt
    | lvalue ASSIGN expression SEMICOLON                                          # assignmentStmt
    | lvalue ASSIGN_MUL expression SEMICOLON                                      # mulAssignStmt
    | lvalue ASSIGN_DIV expression SEMICOLON                                      # divAssignStmt
    | lvalue ASSIGN_MOD expression SEMICOLON                                      # modAssignStmt
    | lvalue ASSIGN_PLUS expression SEMICOLON                                     # addAssignStmt
    | lvalue ASSIGN_MINUS expression SEMICOLON                                    # subAssignStmt
    | lvalue ASSIGN_PLUS_SAT expression SEMICOLON                                 # addSatAssignStmt
    | lvalue ASSIGN_MINUS_SAT expression SEMICOLON                                # subSatAssignStmt
    | lvalue ASSIGN_SHL expression SEMICOLON                                      # shlAssignStmt
    | lvalue ASSIGN_SHR expression SEMICOLON                                      # shrAssignStmt
    | lvalue ASSIGN_BIT_AND expression SEMICOLON                                  # bandAssignStmt
    | lvalue ASSIGN_BIT_OR expression SEMICOLON                                   # borAssignStmt
    | lvalue ASSIGN_XOR expression SEMICOLON                                      # bxorAssignStmt
    ;

emptyStatement
    : SEMICOLON
    ;

exitStatement
    : EXIT SEMICOLON
    ;

returnStatement
    : RETURN SEMICOLON
    | RETURN expression SEMICOLON
    ;

conditionalStatement
    : IF LPAR expression RPAR statement (ELSE statement)?
    ;

breakStatement
    : BREAK SEMICOLON
    ;

continueStatement
    : CONTINUE SEMICOLON
    ;

directApplication
    : typeName DOT APPLY LPAR argumentList RPAR SEMICOLON
    | specializedType DOT APPLY LPAR argumentList RPAR SEMICOLON
    ;

blockStatement
    : optAnnotations LCURL statOrDeclList RCURL
    ;

statOrDeclList
    : statementOrDeclaration*
    ;

statementOrDeclaration
    : variableDeclaration
    | constantDeclaration
    | statement
    | instantiation
    ;

switchStatement
    : SWITCH LPAR expression RPAR LCURL switchCases RCURL
    ;

switchCases
    : switchCase*
    ;

switchCase
    : switchLabel COLON blockStatement
    | switchLabel COLON
    ;

switchLabel
    : DEFAULT
    | nonBraceExpression
    ;

forStatement
    : optAnnotations FOR LPAR forInitStatements SEMICOLON
      expression SEMICOLON
      forUpdateStatements RPAR
      statement
    | optAnnotations FOR LPAR typeRef name IN forCollectionExpr RPAR statement
    | optAnnotations FOR LPAR annotations typeRef name IN forCollectionExpr RPAR statement
    ;

forInitStatements
    : /* empty */
    | declOrAssignmentOrMethodCallStatement
        (COMMA declOrAssignmentOrMethodCallStatement)*
    ;

declOrAssignmentOrMethodCallStatement
    : variableDeclarationWithoutSemicolon
    | assignmentOrMethodCallStatementWithoutSemicolon
    ;

assignmentOrMethodCallStatementWithoutSemicolon
    : lvalue LPAR argumentList RPAR
    | lvalue LT typeArgumentList GT LPAR argumentList RPAR
    | lvalue ASSIGN expression
    | lvalue ASSIGN_MUL expression
    | lvalue ASSIGN_DIV expression
    | lvalue ASSIGN_MOD expression
    | lvalue ASSIGN_PLUS expression
    | lvalue ASSIGN_MINUS expression
    | lvalue ASSIGN_PLUS_SAT expression
    | lvalue ASSIGN_MINUS_SAT expression
    | lvalue ASSIGN_SHL expression
    | lvalue ASSIGN_SHR expression
    | lvalue ASSIGN_BIT_AND expression
    | lvalue ASSIGN_BIT_OR expression
    | lvalue ASSIGN_XOR expression
    ;

forUpdateStatements
    : /* empty */
    | assignmentOrMethodCallStatementWithoutSemicolon
        (COMMA assignmentOrMethodCallStatementWithoutSemicolon)*
    ;

forCollectionExpr
    : expression
    | expression RANGE expression
    | typeRef
    ;

//===----------------------------------------------------------------------===//
// L-values
//===----------------------------------------------------------------------===//

lvalue
    : prefixedNonTypeName                                        # pathLvalue
    | THIS                                                       # thisLvalue
    | lvalue DOT name                                            # memberLvalue
    | lvalue LBRAK expression RBRAK                              # indexLvalue
    | lvalue LBRAK expression COLON expression RBRAK             # sliceLvalue
    | lvalue LBRAK expression PLUS COLON expression RBRAK        # plusSliceLvalue
    | LPAR lvalue RPAR                                           # parenLvalue
    ;

//===----------------------------------------------------------------------===//
// Expressions
//
// ANTLR4 handles left-recursion and operator precedence via alternative
// ordering (top = lowest precedence, bottom = highest).
//===----------------------------------------------------------------------===//

// In ANTLR4, left-recursive alternatives are ordered from highest precedence
// (first) to lowest precedence (last). Non-recursive alternatives (base cases)
// are not affected by this ordering.
expression
    // Postfix operators (highest precedence)
    : expression LPAR argumentList RPAR                          # methodCallExpr
    | expression LT realTypeArgumentList GT
      LPAR argumentList RPAR                                     # typeCallExpr
    | expression DOT name                                        # memberExpr
    | expression LBRAK expression RBRAK                          # arrayIndexExpr
    | expression LBRAK expression COLON expression RBRAK         # sliceExpr
    | expression LBRAK expression PLUS COLON expression RBRAK    # plusSliceExpr
    // Prefix unary operators
    | LPAR typeRef RPAR expression                               # castExpr
    | LOG_NOT expression                                         # lnotExpr
    | BIT_NOT expression                                         # cmplExpr
    | MINUS expression                                           # negExpr
    | PLUS expression                                            # uplusExpr
    // Multiplicative
    | expression MUL expression                                  # mulExpr
    | expression DIV expression                                  # divExpr
    | expression MOD expression                                  # modExpr
    // Additive + saturation
    | expression PLUS expression                                 # addExpr
    | expression MINUS expression                                # subExpr
    | expression PLUS_SAT expression                             # addSatExpr
    | expression MINUS_SAT expression                            # subSatExpr
    // Concatenation
    | expression PP expression                                   # concatExpr
    // Shift (>> is two GT tokens, not SHR, to avoid template ambiguity)
    | expression SHL expression                                  # shlExpr
    | expression GT GT expression                                # shrExpr
    // Bitwise
    | expression BIT_AND expression                              # bandExpr
    | expression BIT_XOR expression                              # bxorExpr
    | expression BIT_OR expression                               # borExpr
    // Comparison
    | expression LT expression                                   # lssExpr
    | expression GT expression                                   # grtExpr
    | expression LEQ expression                                  # leqExpr
    | expression GEQ expression                                  # geqExpr
    // Equality
    | expression EQ expression                                   # eqExpr
    | expression NEQ expression                                  # neqExpr
    // Logical
    | expression LOG_AND expression                              # landExpr
    | expression LOG_OR expression                               # lorExpr
    // Ternary (lowest precedence)
    | expression QUESTION expression COLON expression            # ternaryExpr
    // Non-recursive base cases (precedence ordering does not apply)
    | namedType LPAR argumentList RPAR                           # constructorCallExpr
    | ERROR DOT name                                             # errorMemberExpr
    | INTEGER                                                    # integerExpr
    | DOTS                                                       # dotsExpr
    | STRING_LITERAL                                             # stringLiteralExpr
    | TRUE                                                       # trueExpr
    | FALSE                                                      # falseExpr
    | THIS                                                       # thisExpr
    | prefixedNonTypeName                                        # pathExpr
    | LCURL expressionList optTrailingComma RCURL                # listExpr
    | INVALID_TOK                                                # invalidExpr
    | LCURL kvList optTrailingComma RCURL                        # structExpr
    | LCURL kvList COMMA DOTS optTrailingComma RCURL             # structDotsExpr
    | LPAR expression RPAR                                       # parenExpr
    ;

// Expression that cannot start with '{' (used in switch labels)
nonBraceExpression
    : expression
    ;
