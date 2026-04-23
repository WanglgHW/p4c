// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#ifndef DSLX_P4_ADAPTER_P4_CONTROL_LOWER_H_
#define DSLX_P4_ADAPTER_P4_CONTROL_LOWER_H_

#include <set>
#include <string>

#include "../dslx_ir/module.h"
#include "lower_context.h"

namespace P4::DSLX::adapter {

/// Append actions, table defs, and the control_apply function for `control`
/// to `module`. Updates `emitted_actions` to skip duplicate-named actions.
void LowerControl(const IR::P4Control* control, const LowerContext& ctx,
                  const std::string& gress_name,
                  std::set<std::string>* emitted_actions,
                  ::dslx_ir::Module* module);

}  // namespace P4::DSLX::adapter

#endif  // DSLX_P4_ADAPTER_P4_CONTROL_LOWER_H_
