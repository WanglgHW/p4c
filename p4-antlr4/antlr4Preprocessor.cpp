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

#include "antlr4Preprocessor.h"

#include <cerrno>
#include <cstdlib>
#include <regex>
#include <sstream>

namespace P4ANTLR {

void Preprocessor::processInput(const std::string &input, std::string_view sourceFile,
                                unsigned sourceLine) {
    // Register initial source mapping.
    sources->mapLine(sourceFile, sourceLine);

    // Process input line by line: handle #line directives before appending
    // each line, so mapLine() is called before seal().
    std::istringstream stream(input);
    std::string line;
    bool firstLine = true;
    while (std::getline(stream, line)) {
        if (!firstLine) {
            sources->appendText("\n");
        }
        firstLine = false;
        if (!line.empty() && line[0] == '#') {
            processLineDirective(line);
        }
        sources->appendText(line.c_str());
    }
    // Handle trailing newline if present.
    if (!input.empty() && input.back() == '\n') {
        sources->appendText("\n");
    }
    sources->seal();
}

void Preprocessor::processLineDirective(const std::string &line) {
    // Match: # <linenum> "<filename>" or #line <linenum> "<filename>"
    static const std::regex lineDirectiveRegex(
        R"re(#\s*(?:line\s+)?(\d+)\s+"([^"]*)")re");
    std::smatch match;
    if (std::regex_search(line, match, lineDirectiveRegex)) {
        errno = 0;
        long lineNum = std::strtol(match[1].str().c_str(), nullptr, 10);
        if (errno == 0) {
            std::string filename = match[2].str();
            sources->mapLine(filename, static_cast<unsigned>(lineNum));
        }
    }
}

}  // namespace P4ANTLR
