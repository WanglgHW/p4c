// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Public driver for the DSLX backend. Walks the toplevel IR, finds each
// Pipeline package, lowers it to a dslx_ir::Module via the p4_adapter
// layer, and writes the formatted result to <outputDir>/dslx/<pipe>.x.

#include "dslxBackend.h"

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "dslx_ir/module.h"
#include "lib/error.h"
#include "lib/log.h"
#include "p4_adapter/p4_to_dslx.h"

namespace P4::DSLX {

namespace {

struct PipelineEntry {
    std::string name;
    const IR::PackageBlock* block;
};

std::vector<PipelineEntry> CollectPipelines(const IR::PackageBlock* main) {
    std::vector<PipelineEntry> out;
    auto type = main->type;
    std::string main_type = type ? std::string(type->name.toString()) : "";
    if (main_type == "Pipeline" || main_type == "MultiParserPipeline" ||
        main_type == "V1Switch") {
        out.push_back({"pipe", main});
        return out;
    }
    int idx = 0;
    for (auto& cv : main->constantValue) {
        if (cv.second == nullptr) {
            ++idx;
            continue;
        }
        if (auto pipe = cv.second->to<IR::PackageBlock>()) {
            auto pt = pipe->type;
            std::string ptn = pt ? std::string(pt->name.toString()) : "";
            if (ptn == "Pipeline" || ptn == "MultiParserPipeline") {
                out.push_back({"pipe" + std::to_string(idx), pipe});
            }
        }
        ++idx;
    }
    return out;
}

}  // namespace

void run_dslx_backend(const IR::P4Program* program, P4::ReferenceMap* refMap,
                      P4::TypeMap* typeMap, const IR::ToplevelBlock* toplevel,
                      const DslxConfig& config) {
    if (program == nullptr || toplevel == nullptr) return;
    auto main = toplevel->getMain();
    if (main == nullptr) {
        LOG3("DSLX: No top-level block found, skipping DSLX generation");
        return;
    }

    auto pipelines = CollectPipelines(main);
    if (pipelines.empty()) {
        LOG3("DSLX: No Pipeline packages found, skipping DSLX generation");
        return;
    }

    std::string out_dir = config.outputDir.empty() ? "." : config.outputDir;
    std::string dslx_dir = out_dir + "/dslx";
    std::error_code ec;
    std::filesystem::create_directories(dslx_dir, ec);
    if (ec) {
        ::P4::warning(ErrorType::WARN_UNSUPPORTED,
                      "DSLX: Could not create output directory %1%: %2%",
                      dslx_dir, ec.message());
        return;
    }

    adapter::LowerOptions opts;
    opts.max_packet_bits = config.maxPacketBits;
    opts.max_table_entries = config.maxTableEntries;

    for (const auto& [name, block] : pipelines) {
        std::unique_ptr<::dslx_ir::Module> module;
        try {
            module = adapter::LowerPipelineToModule(program, refMap, typeMap,
                                                     block, opts);
        } catch (const std::exception& e) {
            ::P4::warning(ErrorType::WARN_UNSUPPORTED,
                          "DSLX: Exception lowering pipe %1%: %2%", name, e.what());
            continue;
        } catch (...) {
            ::P4::warning(ErrorType::WARN_UNSUPPORTED,
                          "DSLX: Unknown exception lowering pipe %1%", name);
            continue;
        }
        if (module == nullptr) {
            LOG3("DSLX: Failed to lower pipe " << name);
            continue;
        }

        std::string path = dslx_dir + "/" + name + ".x";
        std::ofstream f(path);
        if (!f.is_open()) {
            ::P4::warning(ErrorType::WARN_UNSUPPORTED,
                          "DSLX: Could not open output file %1%", path);
            continue;
        }
        f << module->ToString();
        f.flush();
        LOG1("DSLX: Generated " << path);
    }
}

}  // namespace P4::DSLX
