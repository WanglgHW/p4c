// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "p4_control_lower.h"

#include <vector>

#include "../dslx_ir/build.h"
#include "binding_helpers.h"
#include "p4_action_lower.h"
#include "p4_stmt_lower.h"
#include "p4_table_lower.h"

namespace P4::DSLX::adapter {

namespace ir = ::dslx_ir;

void LowerControl(const IR::P4Control* control, const LowerContext& ctx,
                  const std::string& gress_name,
                  std::set<std::string>* emitted_actions,
                  ir::Module* module) {
    std::string cname = std::string(control->name.toString());
    module->AddDecl(std::make_unique<ir::CommentDecl>(
        "===== Control: " + gress_name + "_" + cname + " ====="));
    module->AddDecl(std::make_unique<ir::BlankLineDecl>());

    // 1) Actions (skip duplicates by name across gresses)
    for (auto decl : control->controlLocals) {
        if (auto act = decl->to<IR::P4Action>()) {
            std::string an = std::string(act->name.toString());
            if (emitted_actions != nullptr && emitted_actions->count(an) != 0) continue;
            module->AddDecl(LowerAction(act, ctx));
            if (emitted_actions != nullptr) emitted_actions->insert(an);
        }
    }

    // 2) Tables
    for (auto decl : control->controlLocals) {
        if (auto tbl = decl->to<IR::P4Table>()) {
            LowerTable(tbl, ctx, module);
        }
    }

    // 3) The control apply function: params include threaded + per-table
    // entries arrays; body uses LowerStmt with table_apply enabled.
    std::vector<ir::Param> params = BindingParams(*ctx.block_info);
    for (auto decl : control->controlLocals) {
        if (auto tbl = decl->to<IR::P4Table>()) {
            std::string tn = std::string(tbl->name.toString());
            params.emplace_back(
                tn + "_entries",
                ir::T_array(ir::T_ref(tn + "_entry_t"),
                             ir::E_name("MAX_TABLE_ENTRIES")));
        }
    }

    std::vector<ir::StmtPtr> body_stmts;
    if (control->body != nullptr) {
        for (auto s : control->body->components) {
            LowerStmt(s, ctx, &body_stmts, /*enable_table_apply=*/true);
        }
    }
    auto body = ir::B_make(std::move(body_stmts), BindingExpr(*ctx.block_info));

    module->AddDecl(std::make_unique<ir::Function>(
        gress_name + "_" + cname + "_apply", std::move(params),
        BindingReturnType(*ctx.block_info), std::move(body), /*is_pub=*/true));
}

}  // namespace P4::DSLX::adapter
