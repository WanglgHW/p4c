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

#include "dslxOptions.h"

#include "midend.h"

namespace P4::DSLX {

DslxOptions::DslxOptions() {
    langVersion = CompilerOptions::FrontendVersion::P4_16;
    registerOption(
        "-o", "outfile",
        [this](const char *arg) {
            outputFile = arg;
            return true;
        },
        "Write DSLX output to outfile");
    registerOption(
        "--max-packet-bits", "bits",
        [this](const char *arg) {
            maxPacketBits = std::strtoul(arg, nullptr, 0);
            return true;
        },
        "Maximum packet size in bits (default 12000)");
    registerOption(
        "--max-table-entries", "entries",
        [this](const char *arg) {
            maxTableEntries = std::strtoul(arg, nullptr, 0);
            return true;
        },
        "Maximum number of entries per table (default 1024)");
    registerOption(
        "--listMidendPasses", nullptr,
        [this](const char *) {
            loadIRFromJson = false;
            listMidendPasses = true;
            DSLX::MidEnd midend;
            midend.run(*this, nullptr, outStream);
            exit(0);
            return false;
        },
        "[DSLX back-end] Lists exact name of all midend passes.\n");
    registerOption(
        "--fromJSON", "file",
        [this](const char *arg) {
            loadIRFromJson = true;
            file = arg;
            return true;
        },
        "Use IR representation from JsonFile dumped previously,"
        "the compilation starts with reduced midEnd.");
}

}  // namespace P4::DSLX
