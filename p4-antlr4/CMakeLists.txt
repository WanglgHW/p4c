# CMakeLists.txt for the ANTLR4-based P4-16 frontend parser.
#
# This builds:
#   1. The ANTLR4-generated C++ lexer/parser (from P4Lexer.g4 / P4Parser.g4)
#   2. The bridge code that converts the ANTLR4 parse tree into p4c IR

# ---------- ANTLR4-generated sources ----------
set(ANTLR4_GEN_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/P4Lexer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/P4Parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/P4ParserBaseListener.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/P4ParserBaseVisitor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/P4ParserListener.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/P4ParserVisitor.cpp
)

# ---------- Hand-written bridge / integration sources ----------
set(ANTLR4_BRIDGE_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/antlr4ErrorListener.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/antlr4ParserDriver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/antlr4Preprocessor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/antlr4SourceInfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/p4IRConstructor.cpp
)

# Mark generated sources so they skip unity-build inclusion (avoids ODR issues).
set_source_files_properties(${ANTLR4_GEN_SRCS} PROPERTIES
  SKIP_UNITY_BUILD_INCLUSION TRUE
  # Suppress warnings in generated code
  COMPILE_FLAGS "-w"
)

add_library(frontend-antlr4 STATIC ${ANTLR4_GEN_SRCS} ${ANTLR4_BRIDGE_SRCS})

target_include_directories(frontend-antlr4
  PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
  # ANTLR4 C++ runtime headers
  PUBLIC  ${PROJECT_SOURCE_DIR}/tools/antlr4/runtime/Cpp/runtime/src
)

target_link_libraries(frontend-antlr4
  PUBLIC  antlr4_static
  PUBLIC  ir
  PUBLIC  p4ctoolkit
)

add_dependencies(frontend-antlr4 ir-generated)
