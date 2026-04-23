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

namespace P4 {
namespace IR {
class P4Program;
}  // namespace IR
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

 private:
    /// Common implementation: parse from a string.
    static const P4::IR::P4Program *parseInternal(const std::string &input,
                                                  std::string_view sourceFile,
                                                  unsigned sourceLine);
};

}  // namespace P4ANTLR

#endif /* FRONTENDS_P4_ANTLR4_ANTLR4PARSERDRIVER_H_ */
