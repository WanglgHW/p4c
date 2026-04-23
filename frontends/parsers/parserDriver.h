/*
Copyright 2013-present Barefoot Networks, Inc.

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

#ifndef FRONTENDS_PARSERS_PARSERDRIVER_H_
#define FRONTENDS_PARSERS_PARSERDRIVER_H_

#include <cstdio>
#include <iostream>
#include <string_view>
#include <utility>

#include "ir/ir.h"
#include "lib/cstring.h"
#include "lib/source_file.h"

namespace P4 {

// Historically, `parserDriver.h` transitively pulled in the bison-generated
// `p4parser.hpp`, which contained `using namespace literals;` inside
// `namespace P4`. Many downstream translation units (e.g. frontend pass
// implementations) rely on being able to write `"..."_cs` without qualifying
// the literal. Preserve that behaviour here so the migration from flex/bison
// to ANTLR4 does not force a cascade of edits across the codebase.
using namespace literals;  // NOLINT(build/namespaces)

/// A parser driver for P4-16 programs.
///
/// All parsing is delegated to the ANTLR4-based driver under
/// `frontends/p4-antlr4/`. This class exists solely to preserve the historical
/// `P4ParserDriver::parse*` entry points that the rest of the compiler calls
/// into. The flex/bison pipeline that previously backed these methods has been
/// removed.
class P4ParserDriver final {
 public:
    /// Parse a P4-16 program.
    static const IR::P4Program *parse(std::istream &in, std::string_view sourceFile,
                                      unsigned sourceLine = 1);
    static const IR::P4Program *parse(FILE *in, std::string_view sourceFile,
                                      unsigned sourceLine = 1);

    /// Parse and return both the P4Program and the populated InputSources.
    static std::pair<const IR::P4Program *, const Util::InputSources *> parseProgramSources(
        std::istream &in, std::string_view sourceFile, unsigned sourceLine = 1);

    static std::pair<const IR::P4Program *, const Util::InputSources *> parseProgramSources(
        FILE *in, std::string_view sourceFile, unsigned sourceLine = 1);

    // Annotation-body re-parsing. Each method takes the unparsed token stream
    // stored on the annotation and returns a typed IR node, or nullptr on
    // syntax error.

    // Lists /////////////////////////////////////////////////////////////////
    static const IR::Vector<IR::Expression> *parseExpressionList(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    static const IR::IndexedVector<IR::NamedExpression> *parseKvList(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    static const IR::Vector<IR::Expression> *parseConstantList(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    static const IR::Vector<IR::Expression> *parseConstantOrStringLiteralList(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    static const IR::Vector<IR::Expression> *parseStringLiteralList(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    // Singletons ////////////////////////////////////////////////////////////
    static const IR::Expression *parseExpression(const Util::SourceInfo &srcInfo,
                                                 const IR::Vector<IR::AnnotationToken> &body);

    static const IR::Constant *parseConstant(const Util::SourceInfo &srcInfo,
                                             const IR::Vector<IR::AnnotationToken> &body);

    static const IR::Expression *parseConstantOrStringLiteral(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    static const IR::StringLiteral *parseStringLiteral(const Util::SourceInfo &srcInfo,
                                                       const IR::Vector<IR::AnnotationToken> &body);

    // Pairs /////////////////////////////////////////////////////////////////
    static const IR::Vector<IR::Expression> *parseExpressionPair(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    static const IR::Vector<IR::Expression> *parseConstantPair(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    static const IR::Vector<IR::Expression> *parseStringLiteralPair(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    // Triples ///////////////////////////////////////////////////////////////
    static const IR::Vector<IR::Expression> *parseExpressionTriple(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    static const IR::Vector<IR::Expression> *parseConstantTriple(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    static const IR::Vector<IR::Expression> *parseStringLiteralTriple(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);

    // P4Runtime Annotations /////////////////////////////////////////////////
    static const IR::Vector<IR::Expression> *parseP4rtTranslationAnnotation(
        const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body);
};

}  // namespace P4

namespace P4::V1 {

/// P4-14 parsing is no longer supported. The flex/bison v1 parser has been
/// removed; these entry points remain only so that callers still compile and
/// report a clear error.
class V1ParserDriver final {
 public:
    static const IR::V1Program *parse(std::istream &in, std::string_view sourceFile,
                                      unsigned sourceLine = 1);
    static const IR::V1Program *parse(FILE *in, std::string_view sourceFile,
                                      unsigned sourceLine = 1);
};

}  // namespace P4::V1

#endif /* FRONTENDS_PARSERS_PARSERDRIVER_H_ */
