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

#ifndef FRONTENDS_P4_ANTLR4_ANTLR4SOURCEINFO_H_
#define FRONTENDS_P4_ANTLR4_ANTLR4SOURCEINFO_H_

#include "lib/source_file.h"
#include "antlr4-runtime.h"

namespace P4ANTLR {

/// Converts ANTLR4 token/context positions to P4::Util::SourceInfo.
class SourceInfoFactory {
 public:
    explicit SourceInfoFactory(P4::Util::InputSources *sources) : sources(sources) {}

    /// Create SourceInfo from a single token.
    P4::Util::SourceInfo toSourceInfo(antlr4::Token *token) const;

    /// Create SourceInfo spanning a parser rule context.
    P4::Util::SourceInfo toSourceInfo(antlr4::ParserRuleContext *ctx) const;

    /// Create SourceInfo spanning two tokens (inclusive).
    P4::Util::SourceInfo toSourceInfo(antlr4::Token *start, antlr4::Token *stop) const;

    /// Create SourceInfo from explicit line/column values.
    P4::Util::SourceInfo toSourceInfo(size_t startLine, size_t startCol,
                                 size_t endLine, size_t endCol) const;

    P4::Util::InputSources *getSources() const { return sources; }

 private:
    P4::Util::InputSources *sources;
};

}  // namespace P4ANTLR

#endif /* FRONTENDS_P4_ANTLR4_ANTLR4SOURCEINFO_H_ */
