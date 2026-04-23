// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Formatter — turns a `dslx_ir::Module` into DSLX source text.
// Conceptually plays the same role as xls/dslx/fmt/ast_fmt.cc::Format(Module),
// but is a single-pass append formatter (no doc-tree pretty-printer).
//
// All node `Format(Formatter&)` implementations live in ast.cc and call into
// the helper API below. Keeping the formatter the only writer-of-text means a
// new DSL frontend gets correct DSLX syntax for free.

#ifndef DSLX_IR_FORMATTER_H_
#define DSLX_IR_FORMATTER_H_

#include <cstring>
#include <stdexcept>
#include <string>

namespace dslx_ir {

class Formatter {
 public:
    explicit Formatter(int indent_amount = 4) : indent_amount_(indent_amount) {}

    // ---- raw text helpers -------------------------------------------------
    void Write(const std::string& s) {
        if (s.empty()) return;
        ends_in_space_ = std::isspace(static_cast<unsigned char>(s.back())) != 0;
        buffer_ += s;
    }
    void Write(const char* s) {
        if (s == nullptr) return;
        std::size_t n = std::strlen(s);
        if (n == 0) return;
        ends_in_space_ = std::isspace(static_cast<unsigned char>(s[n - 1])) != 0;
        buffer_.append(s, n);
    }
    void Newline() {
        buffer_ += '\n';
        line_started_ = false;
        ends_in_space_ = true;
    }
    void Space() {
        if (!ends_in_space_) {
            buffer_ += ' ';
            ends_in_space_ = true;
        }
    }

    // ---- indentation ------------------------------------------------------
    void Indent() { indent_level_ += indent_amount_; }
    void Dedent() {
        indent_level_ -= indent_amount_;
        if (indent_level_ < 0) {
            throw std::logic_error("dslx_ir::Formatter: negative indent");
        }
    }

    // Emit indentation if we're at column 0 (idempotent within a line).
    void EmitIndentIfNeeded() {
        if (!line_started_) {
            buffer_.append(indent_level_, ' ');
            line_started_ = true;
            ends_in_space_ = true;
        }
    }

    // Convenience: indent + write + newline.
    void Line(const std::string& s) {
        EmitIndentIfNeeded();
        Write(s);
        Newline();
    }

    // ---- result -----------------------------------------------------------
    const std::string& result() const { return buffer_; }

 private:
    std::string buffer_;
    int indent_amount_ = 4;
    int indent_level_ = 0;
    bool line_started_ = false;
    bool ends_in_space_ = true;
};

}  // namespace dslx_ir

#endif  // DSLX_IR_FORMATTER_H_
