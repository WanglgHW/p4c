// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "module.h"

#include "formatter.h"

namespace dslx_ir {

std::string Module::ToString() const {
    Formatter f;
    for (const auto& d : decls_) {
        d->Format(f);
    }
    return f.result();
}

}  // namespace dslx_ir
