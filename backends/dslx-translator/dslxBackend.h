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

#ifndef BACKENDS_XLS_DSLXBACKEND_H_
#define BACKENDS_XLS_DSLXBACKEND_H_

#include <string>

#include "frontends/common/resolveReferences/referenceMap.h"
#include "frontends/p4/typeMap.h"
#include "ir/ir.h"

namespace P4::DSLX {

/// Configuration for DSLX code generation.
struct DslxConfig {
    unsigned maxPacketBits = 12000;
    unsigned maxTableEntries = 1024;
    std::string outputDir;  ///< Base output directory for DSLX files
};

/// Backend entry point for Tofino integration.
/// Generates DSLX files from the P4 program after midend optimization.
/// Supports TNA/T2NA architectures.
void run_dslx_backend(const IR::P4Program *program, P4::ReferenceMap *refMap,
                      P4::TypeMap *typeMap, const IR::ToplevelBlock *toplevel,
                      const DslxConfig &config);

}  // namespace P4::DSLX

#endif  // BACKENDS_XLS_DSLXBACKEND_H_
