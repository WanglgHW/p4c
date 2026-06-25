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

/* static */ std::pair<const P4::IR::P4Program *, const P4::Util::InputSources *>
Antlr4ParserDriver::parseProgramSources(std::istream &in, std::string_view sourceFile,
                                        unsigned sourceLine) {
    std::ostringstream oss;
    oss << in.rdbuf();
    return parseInternalWithSources(oss.str(), sourceFile, sourceLine);
}

/* static */ std::pair<const P4::IR::P4Program *, const P4::Util::InputSources *>
Antlr4ParserDriver::parseProgramSources(FILE *in, std::string_view sourceFile,
                                        unsigned sourceLine) {
    std::string input;
    char buffer[4096];
    while (size_t n = fread(buffer, 1, sizeof(buffer), in)) {
        input.append(buffer, n);
    }
    return parseInternalWithSources(input, sourceFile, sourceLine);
}

/* static */ const P4::IR::P4Program *Antlr4ParserDriver::parseInternal(
    const std::string &input, std::string_view sourceFile, unsigned sourceLine) {
    return parseInternalWithSources(input, sourceFile, sourceLine).first;
}

/* static */ std::pair<const P4::IR::P4Program *, const P4::Util::InputSources *>
Antlr4ParserDriver::parseInternalWithSources(const std::string &input, std::string_view sourceFile,
                                             unsigned sourceLine) {
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
        return {nullptr, sources};
    }

    // Create SourceInfo factory.
    SourceInfoFactory sourceInfoFactory(sources);

    // Visit parse tree to construct IR.
    P4IRConstructor visitor(sourceInfoFactory, sources);
    auto *program = visitor.visitProgram(tree);

    if (P4::errorCount() > 0) {
        return {nullptr, sources};
    }

    return {program, sources};
}

//===----------------------------------------------------------------------===//
// Annotation-body re-parsing
//
// Strategy: reconstruct the source text from the stored AnnotationToken
// stream (each token's `text` field is the exact source fragment it matched),
// feed it through the ANTLR4 P4Lexer, then invoke one of the `ann*` parser
// entry rules generated from P4Parser.g4. The resulting parse tree is walked
// with a fragment-specific visitor on P4IRConstructor.
//
// Per-token srcInfo is lost on the re-lex (tokens get offsets into the
// reconstructed string, not the original file); the caller's `srcInfo`
// argument — the annotation-body position in the original file — is used as
// the fallback. Errors inside annotation bodies are rare enough in practice
// that this trade-off matches the previous Bison-based behaviour.
//===----------------------------------------------------------------------===//

namespace {

std::string reconstructText(const P4::IR::Vector<P4::IR::AnnotationToken> &body) {
    std::string out;
    for (const auto *tok : body) {
        if (!out.empty()) out.push_back(' ');
        out.append(tok->text.c_str(), tok->text.size());
    }
    return out;
}

/// Common scaffolding for every fragment parser: builds an ANTLR4 input
/// stream + lexer + parser over the reconstructed text, installs an error
/// listener that reports against the annotation's original srcInfo, and
/// hands the parser to `startRule` which returns a parse-tree context. The
/// `visit` callable then turns that context into the desired IR value.
///
/// Returns nullptr if any lex/parse error was reported.
template <typename RuleCtx, typename StartRule, typename Visit>
auto runFragment(const P4::Util::SourceInfo &srcInfo,
                 const P4::IR::Vector<P4::IR::AnnotationToken> &body,
                 StartRule startRule, Visit visit) -> decltype(visit(nullptr, nullptr)) {
    // Every fragment rule requires at least one token; an empty annotation
    // body is a parse error for every shape we support.
    if (body.empty()) {
        ::P4::error(P4::ErrorType::ERR_EXPECTED, "%1%: empty annotation body", srcInfo);
        return nullptr;
    }

    const std::string input = reconstructText(body);

    // Route ANTLR4 errors back through the normal compiler error reporter,
    // anchored at the annotation's source position.
    struct FragmentErrorListener : public antlr4::BaseErrorListener {
        const P4::Util::SourceInfo &srcInfo;
        bool sawError = false;
        explicit FragmentErrorListener(const P4::Util::SourceInfo &si) : srcInfo(si) {}
        void syntaxError(antlr4::Recognizer *, antlr4::Token *, size_t, size_t,
                         const std::string &msg, std::exception_ptr) override {
            sawError = true;
            ::P4::error(P4::ErrorType::ERR_INVALID,
                        "%1%: annotation body: %2%", srcInfo, msg);
        }
    };

    antlr4::ANTLRInputStream inputStream(input);
    ::P4Lexer lexer(&inputStream);
    FragmentErrorListener errorListener(srcInfo);
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);

    antlr4::CommonTokenStream tokens(&lexer);
    ::P4Parser parser(&tokens);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    auto *ctx = static_cast<RuleCtx *>(startRule(parser));
    if (errorListener.sawError || ctx == nullptr) return nullptr;

    // The reconstructed text has no relationship to the original file
    // positions, so build a fresh, throwaway InputSources for the fragment.
    auto *fragmentSources = new P4::Util::InputSources();
    SourceInfoFactory factory(fragmentSources);
    P4IRConstructor visitor(factory, fragmentSources);
    // Anchor every node produced from the fragment at the annotation's original
    // source position. Beyond giving sensible diagnostics, this is required for
    // correctness: ResolveReferences enforces declaration-before-use ordering by
    // comparing source positions, so nodes left at the throwaway line 1 would
    // make in-scope declarations appear to come "after" their use and be
    // filtered out (e.g. the method names in `@synchronous(...)`).
    visitor.setSrcInfoOverride(srcInfo);
    return visit(&visitor, ctx);
}

}  // namespace

// ANTLR generates PascalCase Context classes (e.g. `AnnExpressionContext`) but
// camelCase parser methods (e.g. `annExpression()`). The macro takes both.
#define ANN_FRAGMENT(METHOD, RESULT, RULE, CTX, VISIT)                                           \
    const RESULT *Antlr4ParserDriver::METHOD(                                                    \
        const P4::Util::SourceInfo &srcInfo,                                                     \
        const P4::IR::Vector<P4::IR::AnnotationToken> &body) {                                   \
        return runFragment<::P4Parser::CTX##Context>(                                            \
            srcInfo, body, [](::P4Parser &p) { return p.RULE(); },                               \
            [](P4IRConstructor *v, ::P4Parser::CTX##Context *c) { return v->VISIT(c); });        \
    }

ANN_FRAGMENT(parseAnnExpressionList, P4::IR::Vector<P4::IR::Expression>,
             annExpressionList, AnnExpressionList, visitAnnExpressionList)
ANN_FRAGMENT(parseAnnKvList, P4::IR::IndexedVector<P4::IR::NamedExpression>,
             annKvList, AnnKvList, visitAnnKvList)
ANN_FRAGMENT(parseAnnIntegerList, P4::IR::Vector<P4::IR::Expression>,
             annIntegerList, AnnIntegerList, visitAnnIntegerList)
ANN_FRAGMENT(parseAnnIntOrStrList, P4::IR::Vector<P4::IR::Expression>,
             annIntOrStrList, AnnIntOrStrList, visitAnnIntOrStrList)
ANN_FRAGMENT(parseAnnStringList, P4::IR::Vector<P4::IR::Expression>,
             annStringList, AnnStringList, visitAnnStringList)

ANN_FRAGMENT(parseAnnExpression, P4::IR::Expression,
             annExpression, AnnExpression, visitAnnExpression)
ANN_FRAGMENT(parseAnnInteger, P4::IR::Constant,
             annInteger, AnnInteger, visitAnnInteger)
ANN_FRAGMENT(parseAnnIntOrStr, P4::IR::Expression,
             annIntOrStr, AnnIntOrStr, visitAnnIntOrStr)
ANN_FRAGMENT(parseAnnStringLiteral, P4::IR::StringLiteral,
             annStringLiteral, AnnStringLiteral, visitAnnStringLiteral)

ANN_FRAGMENT(parseAnnExpressionPair, P4::IR::Vector<P4::IR::Expression>,
             annExpressionPair, AnnExpressionPair, visitAnnExpressionPair)
ANN_FRAGMENT(parseAnnIntegerPair, P4::IR::Vector<P4::IR::Expression>,
             annIntegerPair, AnnIntegerPair, visitAnnIntegerPair)
ANN_FRAGMENT(parseAnnStringPair, P4::IR::Vector<P4::IR::Expression>,
             annStringPair, AnnStringPair, visitAnnStringPair)

ANN_FRAGMENT(parseAnnExpressionTriple, P4::IR::Vector<P4::IR::Expression>,
             annExpressionTriple, AnnExpressionTriple, visitAnnExpressionTriple)
ANN_FRAGMENT(parseAnnIntegerTriple, P4::IR::Vector<P4::IR::Expression>,
             annIntegerTriple, AnnIntegerTriple, visitAnnIntegerTriple)
ANN_FRAGMENT(parseAnnStringTriple, P4::IR::Vector<P4::IR::Expression>,
             annStringTriple, AnnStringTriple, visitAnnStringTriple)

ANN_FRAGMENT(parseAnnP4rtTranslation, P4::IR::Vector<P4::IR::Expression>,
             annP4rtTranslation, AnnP4rtTranslation, visitAnnP4rtTranslation)

#undef ANN_FRAGMENT

}  // namespace P4ANTLR
