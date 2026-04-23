
// Generated from P4Lexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  P4Lexer : public antlr4::Lexer {
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

  explicit P4Lexer(antlr4::CharStream *input);

  ~P4Lexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

