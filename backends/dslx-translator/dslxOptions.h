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

#ifndef BACKENDS_XLS_DSLXOPTIONS_H_
#define BACKENDS_XLS_DSLXOPTIONS_H_

#include "frontends/common/options.h"

namespace P4::DSLX {

class DslxOptions : public CompilerOptions {
 public:
    /// Output file path (.x)
    std::filesystem::path outputFile;
    /// Maximum packet size in bits (default 1500 bytes = 12000 bits)
    unsigned maxPacketBits = 12000;
    /// Maximum number of table entries per table
    unsigned maxTableEntries = 1024;
    /// Read from JSON IR
    bool loadIRFromJson = false;

    DslxOptions();
};

using DslxContext = P4CContextWithOptions<DslxOptions>;

}  // namespace P4::DSLX

#endif  // BACKENDS_XLS_DSLXOPTIONS_H_
