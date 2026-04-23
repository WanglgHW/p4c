// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// TNA / T2NA intrinsic-metadata helpers. Knows the canonical struct names
// and provides a snake_case_t -> CamelCase converter used to derive DSLX
// type names. Only depends on <string> / <set>.

#ifndef DSLX_P4_ADAPTER_INTRINSIC_METADATA_H_
#define DSLX_P4_ADAPTER_INTRINSIC_METADATA_H_

#include <string>

namespace P4::DSLX::adapter {

// Returns true if `name` is a TNA/T2NA intrinsic-metadata struct/header type.
bool IsIntrinsicMetadataType(const std::string& name);

// "ingress_intrinsic_metadata_t" -> "IngressIntrinsicMetadata"
// (drops trailing _t, capitalizes after each underscore)
std::string ToCamelCase(const std::string& snake);

// "headers" -> "Headers"  (capitalize first letter only)
std::string CapitalizeFirst(const std::string& s);

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_INTRINSIC_METADATA_H_
