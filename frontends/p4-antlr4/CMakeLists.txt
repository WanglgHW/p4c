# CMakeLists.txt for the ANTLR4-based P4-16 frontend parser.
#
# This builds:
#   1. The ANTLR4-generated C++ lexer/parser (from P4Lexer.g4 / P4Parser.g4)
#   2. The bridge code that converts the ANTLR4 parse tree into p4c IR
#
# The generated .cpp/.h files are checked in under this directory — they are
# regenerated via the optional `regenerate-p4-antlr4-grammar` target, which
# shells out to tools/antlr-4.13.2-complete.jar. A Java runtime must be on
# PATH for regeneration; it is NOT required for normal builds.

message(STATUS "Configuring the P4 ANTLR4 frontend")

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

# Mark generated sources so they skip unity-build inclusion (avoids ODR issues)
# and silence their own warnings (they are machine-generated).
set_source_files_properties(${ANTLR4_GEN_SRCS} PROPERTIES
  SKIP_UNITY_BUILD_INCLUSION TRUE
  COMPILE_FLAGS "-w"
)

add_library(frontend-antlr4 STATIC ${ANTLR4_GEN_SRCS} ${ANTLR4_BRIDGE_SRCS})

target_include_directories(frontend-antlr4
  PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(frontend-antlr4
  PUBLIC  antlr4_static
  PUBLIC  ir
  PUBLIC  p4ctoolkit
)

add_dependencies(frontend-antlr4 ir-generated)

# ---------- Optional grammar regeneration ----------
# Regenerates the .cpp/.h lexer/parser from the .g4 grammar files using the
# vendored antlr jar. Not part of the default build; only run when a developer
# edits the grammar.
set(P4_ANTLR4_JAR "${PROJECT_SOURCE_DIR}/tools/antlr-4.13.2-complete.jar")
find_package(Java COMPONENTS Runtime QUIET)
if (Java_JAVA_EXECUTABLE AND EXISTS "${P4_ANTLR4_JAR}")
  add_custom_target(regenerate-p4-antlr4-grammar
    COMMAND ${Java_JAVA_EXECUTABLE} -jar "${P4_ANTLR4_JAR}"
            -Dlanguage=Cpp
            -visitor -listener
            -o "${CMAKE_CURRENT_SOURCE_DIR}"
            -lib "${CMAKE_CURRENT_SOURCE_DIR}"
            "${CMAKE_CURRENT_SOURCE_DIR}/P4Lexer.g4"
            "${CMAKE_CURRENT_SOURCE_DIR}/P4Parser.g4"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "Regenerating P4 ANTLR4 lexer/parser from .g4 files"
    VERBATIM
  )
endif()

message(STATUS "Done configuring the P4 ANTLR4 frontend")
