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

#include "antlr4SourceInfo.h"

namespace P4ANTLR {

P4::Util::SourceInfo SourceInfoFactory::toSourceInfo(antlr4::Token *token) const {
    if (!token) return P4::Util::SourceInfo();
    if (token->getType() == antlr4::Token::EOF) return P4::Util::SourceInfo();
    // ANTLR4 lines are 1-based, columns are 0-based.
    // P4::Util::SourcePosition uses 1-based for both line and column.
    unsigned startLine = token->getLine();
    unsigned startCol = token->getCharPositionInLine() + 1;
    auto text = token->getText();
    unsigned len = static_cast<unsigned>(text.size());
    if (len == 0) len = 1;  // Ensure end is after start.
    unsigned endCol = startCol + len;
    P4::Util::SourcePosition start(startLine, startCol);
    P4::Util::SourcePosition end(startLine, endCol);
    return P4::Util::SourceInfo(sources, start, end);
}

P4::Util::SourceInfo SourceInfoFactory::toSourceInfo(antlr4::ParserRuleContext *ctx) const {
    if (!ctx) return P4::Util::SourceInfo();
    auto *startToken = ctx->getStart();
    auto *stopToken = ctx->getStop();
    if (!startToken) return P4::Util::SourceInfo();
    if (!stopToken) return toSourceInfo(startToken);
    return toSourceInfo(startToken, stopToken);
}

P4::Util::SourceInfo SourceInfoFactory::toSourceInfo(antlr4::Token *start,
                                                 antlr4::Token *stop) const {
    if (!start) return P4::Util::SourceInfo();
    if (!stop || stop->getType() == antlr4::Token::EOF) return toSourceInfo(start);

    unsigned startLine = start->getLine();
    unsigned startCol = start->getCharPositionInLine() + 1;
    unsigned endLine = stop->getLine();
    unsigned len = static_cast<unsigned>(stop->getText().size());
    if (len == 0) len = 1;
    unsigned endCol = stop->getCharPositionInLine() + 1 + len;

    P4::Util::SourcePosition startPos(startLine, startCol);
    P4::Util::SourcePosition endPos(endLine, endCol);
    // Ensure end is not before start.
    if (endPos < startPos) return P4::Util::SourceInfo(sources, startPos, startPos);
    return P4::Util::SourceInfo(sources, startPos, endPos);
}

P4::Util::SourceInfo SourceInfoFactory::toSourceInfo(size_t startLine, size_t startCol,
                                                 size_t endLine, size_t endCol) const {
    P4::Util::SourcePosition startPos(startLine, startCol);
    P4::Util::SourcePosition endPos(endLine, endCol);
    return P4::Util::SourceInfo(sources, startPos, endPos);
}

}  // namespace P4ANTLR
