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

#ifndef FRONTENDS_P4_ANTLR4_ANTLR4PARSERDRIVER_H_
#define FRONTENDS_P4_ANTLR4_ANTLR4PARSERDRIVER_H_

#include <cstdio>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

#include "ir/ir.h"
#include "lib/source_file.h"

namespace P4 {
namespace IR {
class P4Program;
}  // namespace IR
namespace Util {
class InputSources;
}  // namespace Util
}  // namespace P4

namespace P4ANTLR {

/// ANTLR4-based parser driver for P4-16 programs.
/// Provides the same static interface as P4ParserDriver.
class Antlr4ParserDriver {
 public:
    /// Parse a P4-16 program from an istream.
    static const P4::IR::P4Program *parse(std::istream &in, std::string_view sourceFile,
                                          unsigned sourceLine = 1);

    /// Parse a P4-16 program from a FILE*.
    static const P4::IR::P4Program *parse(FILE *in, std::string_view sourceFile,
                                          unsigned sourceLine = 1);

    /// Parse and return both the program and the populated InputSources.
    static std::pair<const P4::IR::P4Program *, const P4::Util::InputSources *> parseProgramSources(
        std::istream &in, std::string_view sourceFile, unsigned sourceLine = 1);

    static std::pair<const P4::IR::P4Program *, const P4::Util::InputSources *> parseProgramSources(
        FILE *in, std::string_view sourceFile, unsigned sourceLine = 1);

    // Annotation-body re-parsing. Each entry point reconstructs the source
    // text from the stored AnnotationToken stream, lexes it with the ANTLR4
    // P4Lexer, and parses it with the matching `ann*` fragment rule in the
    // ANTLR4 P4Parser grammar. Returns nullptr on syntax errors.
    static const P4::IR::Vector<P4::IR::Expression> *parseAnnExpressionList(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);
    static const P4::IR::IndexedVector<P4::IR::NamedExpression> *parseAnnKvList(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);
    static const P4::IR::Vector<P4::IR::Expression> *parseAnnIntegerList(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);
    static const P4::IR::Vector<P4::IR::Expression> *parseAnnIntOrStrList(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);
    static const P4::IR::Vector<P4::IR::Expression> *parseAnnStringList(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);

    static const P4::IR::Expression *parseAnnExpression(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);
    static const P4::IR::Constant *parseAnnInteger(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);
    static const P4::IR::Expression *parseAnnIntOrStr(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);
    static const P4::IR::StringLiteral *parseAnnStringLiteral(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);

    static const P4::IR::Vector<P4::IR::Expression> *parseAnnExpressionPair(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);
    static const P4::IR::Vector<P4::IR::Expression> *parseAnnIntegerPair(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);
    static const P4::IR::Vector<P4::IR::Expression> *parseAnnStringPair(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);

    static const P4::IR::Vector<P4::IR::Expression> *parseAnnExpressionTriple(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);
    static const P4::IR::Vector<P4::IR::Expression> *parseAnnIntegerTriple(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);
    static const P4::IR::Vector<P4::IR::Expression> *parseAnnStringTriple(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);

    static const P4::IR::Vector<P4::IR::Expression> *parseAnnP4rtTranslation(
        const P4::Util::SourceInfo &srcInfo,
        const P4::IR::Vector<P4::IR::AnnotationToken> &body);

 private:
    /// Common implementation: parse from a string.
    static const P4::IR::P4Program *parseInternal(const std::string &input,
                                                  std::string_view sourceFile,
                                                  unsigned sourceLine);

    static std::pair<const P4::IR::P4Program *, const P4::Util::InputSources *>
    parseInternalWithSources(const std::string &input, std::string_view sourceFile,
                             unsigned sourceLine);
};

}  // namespace P4ANTLR

#endif /* FRONTENDS_P4_ANTLR4_ANTLR4PARSERDRIVER_H_ */
