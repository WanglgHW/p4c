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

#include "parserDriver.h"

#include <cstdio>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

#include "frontends/p4-antlr4/antlr4ParserDriver.h"
#include "lib/error.h"

namespace P4 {

/* static */ const IR::P4Program *P4ParserDriver::parse(std::istream &in,
                                                        std::string_view sourceFile,
                                                        unsigned sourceLine /* = 1 */) {
    return P4ANTLR::Antlr4ParserDriver::parse(in, sourceFile, sourceLine);
}

/* static */ const IR::P4Program *P4ParserDriver::parse(FILE *in, std::string_view sourceFile,
                                                        unsigned sourceLine /* = 1 */) {
    return P4ANTLR::Antlr4ParserDriver::parse(in, sourceFile, sourceLine);
}

/* static */ std::pair<const IR::P4Program *, const Util::InputSources *>
P4ParserDriver::parseProgramSources(std::istream &in, std::string_view sourceFile,
                                    unsigned sourceLine /* = 1 */) {
    return P4ANTLR::Antlr4ParserDriver::parseProgramSources(in, sourceFile, sourceLine);
}

/* static */ std::pair<const IR::P4Program *, const Util::InputSources *>
P4ParserDriver::parseProgramSources(FILE *in, std::string_view sourceFile,
                                    unsigned sourceLine /* = 1 */) {
    return P4ANTLR::Antlr4ParserDriver::parseProgramSources(in, sourceFile, sourceLine);
}

// Annotation-body re-parsing. Each method forwards to the matching
// `Antlr4ParserDriver::parseAnn*` entry point. The ANTLR4 driver handles the
// re-lex + fragment-rule parse + IR construction internally.

/* static */ const IR::Vector<IR::Expression> *P4ParserDriver::parseExpressionList(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnExpressionList(srcInfo, body);
}

/* static */ const IR::IndexedVector<IR::NamedExpression> *P4ParserDriver::parseKvList(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnKvList(srcInfo, body);
}

/* static */ const IR::Vector<IR::Expression> *P4ParserDriver::parseConstantList(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnIntegerList(srcInfo, body);
}

/* static */ const IR::Vector<IR::Expression> *P4ParserDriver::parseConstantOrStringLiteralList(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnIntOrStrList(srcInfo, body);
}

/* static */ const IR::Vector<IR::Expression> *P4ParserDriver::parseStringLiteralList(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnStringList(srcInfo, body);
}

/* static */ const IR::Expression *P4ParserDriver::parseExpression(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnExpression(srcInfo, body);
}

/* static */ const IR::Constant *P4ParserDriver::parseConstant(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnInteger(srcInfo, body);
}

/* static */ const IR::Expression *P4ParserDriver::parseConstantOrStringLiteral(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnIntOrStr(srcInfo, body);
}

/* static */ const IR::StringLiteral *P4ParserDriver::parseStringLiteral(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnStringLiteral(srcInfo, body);
}

/* static */ const IR::Vector<IR::Expression> *P4ParserDriver::parseExpressionPair(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnExpressionPair(srcInfo, body);
}

/* static */ const IR::Vector<IR::Expression> *P4ParserDriver::parseConstantPair(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnIntegerPair(srcInfo, body);
}

/* static */ const IR::Vector<IR::Expression> *P4ParserDriver::parseStringLiteralPair(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnStringPair(srcInfo, body);
}

/* static */ const IR::Vector<IR::Expression> *P4ParserDriver::parseExpressionTriple(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnExpressionTriple(srcInfo, body);
}

/* static */ const IR::Vector<IR::Expression> *P4ParserDriver::parseConstantTriple(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnIntegerTriple(srcInfo, body);
}

/* static */ const IR::Vector<IR::Expression> *P4ParserDriver::parseStringLiteralTriple(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnStringTriple(srcInfo, body);
}

/* static */ const IR::Vector<IR::Expression> *P4ParserDriver::parseP4rtTranslationAnnotation(
    const Util::SourceInfo &srcInfo, const IR::Vector<IR::AnnotationToken> &body) {
    return P4ANTLR::Antlr4ParserDriver::parseAnnP4rtTranslation(srcInfo, body);
}

}  // namespace P4

namespace P4::V1 {

/* static */ const IR::V1Program *V1ParserDriver::parse(std::istream & /*in*/,
                                                        std::string_view sourceFile,
                                                        unsigned /*sourceLine*/) {
    ::P4::error(ErrorType::ERR_UNSUPPORTED,
                "%1%: P4-14 (v1) programs are no longer supported; the flex/bison v1 "
                "parser has been removed. Please convert to P4-16.",
                std::string(sourceFile));
    return nullptr;
}

/* static */ const IR::V1Program *V1ParserDriver::parse(FILE * /*in*/, std::string_view sourceFile,
                                                        unsigned /*sourceLine*/) {
    ::P4::error(ErrorType::ERR_UNSUPPORTED,
                "%1%: P4-14 (v1) programs are no longer supported; the flex/bison v1 "
                "parser has been removed. Please convert to P4-16.",
                std::string(sourceFile));
    return nullptr;
}

}  // namespace P4::V1
