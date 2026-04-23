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

#ifndef FRONTENDS_P4_ANTLR4_ANTLR4PREPROCESSOR_H_
#define FRONTENDS_P4_ANTLR4_ANTLR4PREPROCESSOR_H_

#include <string>
#include <vector>

#include "lib/source_file.h"

namespace P4ANTLR {

/// Pre-scans input for #line directives and maps them into InputSources.
/// Also processes comments on the HIDDEN channel for InputSources::addComment().
class Preprocessor {
 public:
    explicit Preprocessor(P4::Util::InputSources *sources) : sources(sources) {}

    /// Scan the input text for #line directives and register them.
    /// Also feeds the entire text into InputSources.
    void processInput(const std::string &input, std::string_view sourceFile,
                      unsigned sourceLine);

 private:
    /// Parse a single #line directive line and register it.
    void processLineDirective(const std::string &line);

    P4::Util::InputSources *sources;
};

}  // namespace P4ANTLR

#endif /* FRONTENDS_P4_ANTLR4_ANTLR4PREPROCESSOR_H_ */
