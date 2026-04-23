// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "intrinsic_metadata.h"

#include <cctype>
#include <set>

namespace P4::DSLX::adapter {

namespace {
const std::set<std::string>& KnownIntrinsicTypes() {
    static const std::set<std::string> kSet = {
        "ingress_intrinsic_metadata_t",
        "ingress_intrinsic_metadata_from_parser_t",
        "ingress_intrinsic_metadata_for_deparser_t",
        "ingress_intrinsic_metadata_for_tm_t",
        "egress_intrinsic_metadata_t",
        "egress_intrinsic_metadata_from_parser_t",
        "egress_intrinsic_metadata_for_deparser_t",
        "egress_intrinsic_metadata_for_output_port_t",
        "ghost_intrinsic_metadata_t",
    };
    return kSet;
}
}  // namespace

bool IsIntrinsicMetadataType(const std::string& name) {
    return KnownIntrinsicTypes().count(name) > 0;
}

std::string ToCamelCase(const std::string& snake) {
    std::string input = snake;
    if (input.size() > 2 && input.substr(input.size() - 2) == "_t") {
        input.resize(input.size() - 2);
    }
    std::string out;
    bool cap_next = true;
    for (char c : input) {
        if (c == '_') {
            cap_next = true;
        } else if (cap_next) {
            out += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
            cap_next = false;
        } else {
            out += c;
        }
    }
    return out;
}

std::string CapitalizeFirst(const std::string& s) {
    if (s.empty()) return s;
    std::string out = s;
    out[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(out[0])));
    return out;
}

}  // namespace P4::DSLX::adapter
