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

#ifndef FRONTENDS_P4_ANTLR4_ANTLR4ERRORLISTENER_H_
#define FRONTENDS_P4_ANTLR4_ANTLR4ERRORLISTENER_H_

#include "lib/source_file.h"
#include "antlr4-runtime.h"

namespace P4ANTLR {

/// Routes ANTLR4 parse errors to the p4c error reporter.
class P4ErrorListener : public antlr4::BaseErrorListener {
 public:
    explicit P4ErrorListener(P4::Util::InputSources *sources) : sources(sources) {}

    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
                     size_t charPositionInLine, const std::string &msg,
                     std::exception_ptr e) override;

 private:
    P4::Util::InputSources *sources;
};

}  // namespace P4ANTLR

#endif /* FRONTENDS_P4_ANTLR4_ANTLR4ERRORLISTENER_H_ */
