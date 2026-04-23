lexer grammar P4Lexer;

// Keywords (matching p4parser.ypp token definitions)
ABSTRACT     : 'abstract';
ACTION       : 'action';
ACTIONS      : 'actions';
APPLY        : 'apply';
BOOL         : 'bool';
BIT          : 'bit';
BREAK        : 'break';
CONST        : 'const';
CONTINUE     : 'continue';
CONTROL      : 'control';
DEFAULT      : 'default';
ELSE         : 'else';
ENTRIES      : 'entries';
ENUM         : 'enum';
ERROR        : 'error';
EXIT         : 'exit';
EXTERN       : 'extern';
FALSE        : 'false';
FOR          : 'for';
HEADER       : 'header';
HEADER_UNION : 'header_union';
IF           : 'if';
IN           : 'in';
INOUT        : 'inout';
INT          : 'int';
KEY          : 'key';
LIST         : 'list';
MATCH_KIND   : 'match_kind';
TYPE         : 'type';
OUT          : 'out';
PACKAGE      : 'package';
PARSER       : 'parser';
// Note: @pragma is handled as AT + IDENTIFIER("pragma") in the parser.
// The lexer does not have a special PRAGMA token.
PRIORITY     : 'priority';
RETURN       : 'return';
SELECT       : 'select';
STATE        : 'state';
STRING_KW    : 'string';
STRUCT       : 'struct';
SWITCH       : 'switch';
TABLE        : 'table';
THIS         : 'this';
TRANSITION   : 'transition';
TRUE         : 'true';
TUPLE        : 'tuple';
TYPEDEF      : 'typedef';
VARBIT       : 'varbit';
VALUE_SET    : 'value_set';
VOID         : 'void';

// Multi-character operators (ordered longest first to avoid ambiguity)
ASSIGN_PLUS_SAT  : '|+|=';
ASSIGN_MINUS_SAT : '|-|=';
PLUS_SAT     : '|+|';
MINUS_SAT    : '|-|';
ASSIGN_SHL   : '<<=';
ASSIGN_SHR   : '>>=';
DOTS         : '...';
MASK         : '&&&';
LOG_AND      : '&&';
LOG_OR       : '||';
EQ           : '==';
NEQ          : '!=';
GEQ          : '>=';
LEQ          : '<=';
SHL          : '<<';
// Note: '>>' is NOT lexed as a single SHR token. Instead, it is lexed as two
// GT tokens. This avoids the classic '>>' template-closing ambiguity
// (e.g., bit<bit<8>>). The parser handles shift-right via 'GT GT'.
PP           : '++';
RANGE        : '..';
ASSIGN_PLUS  : '+=';
ASSIGN_MINUS : '-=';
ASSIGN_MUL   : '*=';
ASSIGN_DIV   : '/=';
ASSIGN_MOD   : '%=';
ASSIGN_BIT_AND : '&=';
ASSIGN_BIT_OR  : '|=';
ASSIGN_XOR   : '^=';
INVALID_TOK  : '{#}';

// Single-character operators
ASSIGN       : '=';
PLUS         : '+';
MINUS        : '-';
MUL          : '*';
DIV          : '/';
MOD          : '%';
GT           : '>';
LT           : '<';
BIT_AND      : '&';
BIT_OR       : '|';
BIT_XOR      : '^';
BIT_NOT      : '~';
LOG_NOT      : '!';
COLON        : ':';
SEMICOLON    : ';';
COMMA        : ',';
DOT          : '.';
QUESTION     : '?';
AT           : '@';
LBRAK        : '[';
RBRAK        : ']';
LPAR         : '(';
RPAR         : ')';
LCURL        : '{';
RCURL        : '}';
DONTCARE     : '_';

// Integer literals
// Width-prefixed: 8w255, 16s0xFF, 0b1010, etc.
// Plain: 0, 42, 0xDEAD, 0b1010, 0o77, 0d99
INTEGER
    : [0-9]+ [wWsS] '0' [xX] [0-9a-fA-F_]+
    | [0-9]+ [wWsS] '0' [bB] [01_]+
    | [0-9]+ [wWsS] '0' [oO] [0-7_]+
    | [0-9]+ [wWsS] '0' [dD] [0-9_]+
    | [0-9]+ [wWsS] [0-9] [0-9_]*
    | '0' [xX] [0-9a-fA-F_]+
    | '0' [bB] [01_]+
    | '0' [oO] [0-7_]+
    | '0' [dD] [0-9_]+
    | [0-9] [0-9_]*
    ;

// Identifiers
IDENTIFIER   : [a-zA-Z_][a-zA-Z0-9_]*;

// String literals with escape sequences
STRING_LITERAL
    : '"' ( '\\' [\\"] | ~["\\\r\n] )* '"'
    ;

// Preprocessor #line directives -> hidden channel
// Matches both "# NUM ..." (GCC format) and "#line NUM ..." forms.
LINE_DIRECTIVE
    : '#' ~[\r\n]* -> channel(HIDDEN)
    ;

// Note: END_PRAGMA is not needed since @pragma is parsed as a regular annotation.

// Whitespace
WS : [ \t\r\n]+ -> skip;

// Comments -> hidden channel (for InputSources::addComment)
BLOCK_COMMENT : '/*' .*? '*/' -> channel(HIDDEN);
LINE_COMMENT  : '//' ~[\r\n]* -> channel(HIDDEN);
