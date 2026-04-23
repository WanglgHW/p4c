// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0
//
// Module — top-level container of DSLX top-level declarations.
// Mirrors the role of xls/dslx/frontend/module.h::Module but without
// the parser/typechecker hooks.

#ifndef DSLX_IR_MODULE_H_
#define DSLX_IR_MODULE_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "ast.h"

namespace dslx_ir {

class Module {
 public:
    explicit Module(std::string name) : name_(std::move(name)) {}

    const std::string& name() const { return name_; }

    // Take ownership of a top-level declaration.
    void AddDecl(std::unique_ptr<Decl> decl) {
        decls_.push_back(std::move(decl));
    }

    const std::vector<std::unique_ptr<Decl>>& decls() const { return decls_; }

    // Render the module to a DSLX source string.
    std::string ToString() const;

 private:
    std::string name_;
    std::vector<std::unique_ptr<Decl>> decls_;
};

}  // namespace dslx_ir

#endif  // DSLX_IR_MODULE_H_
