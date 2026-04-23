// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "p4_action_lower.h"

#include <vector>

#include "../dslx_ir/build.h"
#include "binding_helpers.h"
#include "p4_stmt_lower.h"
#include "p4_type_lower.h"

namespace P4::DSLX::adapter {

namespace ir = ::dslx_ir;

std::unique_ptr<ir::Function> LowerAction(const IR::P4Action* action,
                                            const LowerContext& ctx) {
    std::vector<ir::Param> params = BindingParams(*ctx.block_info);
    for (auto p : action->parameters->parameters) {
        auto t = ctx.typeMap->getType(p, false);
        params.emplace_back(std::string(p->name.toString()),
                             LowerType(t, ctx.typeMap));
    }

    std::vector<ir::StmtPtr> body_stmts;
    if (action->body != nullptr) {
        for (auto s : action->body->components) {
            LowerStmt(s, ctx, &body_stmts, /*enable_table_apply=*/false);
        }
    }
    auto body = ir::B_make(std::move(body_stmts), BindingExpr(*ctx.block_info));

    return std::make_unique<ir::Function>(
        std::string(action->name.toString()),
        std::move(params),
        BindingReturnType(*ctx.block_info),
        std::move(body),
        /*is_pub=*/true);
}

}  // namespace P4::DSLX::adapter
