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

#include "antlr4ErrorListener.h"

#include "lib/compile_context.h"
#include "lib/error.h"

namespace P4ANTLR {

void P4ErrorListener::syntaxError(antlr4::Recognizer * /*recognizer*/,
                                  antlr4::Token * /*offendingSymbol*/, size_t line,
                                  size_t charPositionInLine, const std::string &msg,
                                  std::exception_ptr /*e*/) {
    P4::Util::SourcePosition start(line, charPositionInLine + 1);
    P4::Util::SourcePosition end(line, charPositionInLine + 2);
    P4::Util::SourceInfo srcInfo(sources, start, end);

    auto &context = P4::BaseCompileContext::get();
    context.errorReporter().parser_error(srcInfo, msg);
}

}  // namespace P4ANTLR
