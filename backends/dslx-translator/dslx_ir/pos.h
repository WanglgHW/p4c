// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Reusable DSLX-IR — derived from xls/dslx/frontend/pos.h but stripped down
// to plain C++ standard-library types so this directory can be reused
// outside p4c (and outside the XLS Bazel build) verbatim.
//
// The full XLS Pos/Span machinery is overkill for emit-only use; we only need
// optional debug-tagging of nodes back to their source-language origin.

#ifndef DSLX_IR_POS_H_
#define DSLX_IR_POS_H_

#include <cstdint>
#include <string>

namespace dslx_ir {

// 0-indexed (line, column) in the originating source. Default-constructed
// means "no position information" — the formatter ignores it.
struct Pos {
    std::string filename;
    int32_t line = -1;
    int32_t column = -1;
    bool valid() const { return line >= 0; }
};

struct Span {
    Pos start;
    Pos end;
    bool valid() const { return start.valid(); }
};

}  // namespace dslx_ir

#endif  // DSLX_IR_POS_H_
