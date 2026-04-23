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

#include "antlr4ParserDriver.h"

#include <sstream>

#include "lib/error.h"
#include "lib/log.h"
#include "lib/source_file.h"

#include "antlr4-runtime.h"

#include "P4Lexer.h"
#include "P4Parser.h"
#include "antlr4ErrorListener.h"
#include "antlr4Preprocessor.h"
#include "antlr4SourceInfo.h"
#include "p4IRConstructor.h"

namespace P4ANTLR {

/* static */ const P4::IR::P4Program *Antlr4ParserDriver::parse(
    std::istream &in, std::string_view sourceFile, unsigned sourceLine) {
    // Read entire input into a string.
    std::ostringstream oss;
    oss << in.rdbuf();
    return parseInternal(oss.str(), sourceFile, sourceLine);
}

/* static */ const P4::IR::P4Program *Antlr4ParserDriver::parse(
    FILE *in, std::string_view sourceFile, unsigned sourceLine) {
    // Read entire FILE* into a string.
    std::string input;
    char buffer[4096];
    while (size_t n = fread(buffer, 1, sizeof(buffer), in)) {
        input.append(buffer, n);
    }
    return parseInternal(input, sourceFile, sourceLine);
}

/* static */ const P4::IR::P4Program *Antlr4ParserDriver::parseInternal(
    const std::string &input, std::string_view sourceFile, unsigned sourceLine) {
    LOG1("Parsing P4-16 program (ANTLR4) " << sourceFile);

    // Set up InputSources and preprocess #line directives.
    auto *sources = new P4::Util::InputSources();
    Preprocessor preprocessor(sources);
    preprocessor.processInput(input, sourceFile, sourceLine);

    // Create ANTLR4 input stream.
    antlr4::ANTLRInputStream inputStream(input);

    // Create lexer.
    ::P4Lexer lexer(&inputStream);
    P4ErrorListener errorListener(sources);
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);

    // Create token stream.
    antlr4::CommonTokenStream tokens(&lexer);

    // Create parser.
    ::P4Parser p4parser(&tokens);
    p4parser.removeErrorListeners();
    p4parser.addErrorListener(&errorListener);

    // Parse.
    auto *tree = p4parser.program();

    if (P4::errorCount() > 0) {
        return nullptr;
    }

    // Create SourceInfo factory.
    SourceInfoFactory sourceInfoFactory(sources);

    // Visit parse tree to construct IR.
    P4IRConstructor visitor(sourceInfoFactory, sources);
    auto *program = visitor.visitProgram(tree);

    if (P4::errorCount() > 0) {
        return nullptr;
    }

    return program;
}

}  // namespace P4ANTLR
