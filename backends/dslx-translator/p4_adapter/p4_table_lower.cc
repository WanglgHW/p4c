// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "p4_table_lower.h"

#include <string>
#include <utility>
#include <vector>

#include "../dslx_ir/build.h"
#include "binding_helpers.h"
#include "p4_expr_lower.h"
#include "p4_type_lower.h"

namespace P4::DSLX::adapter {

namespace ir = ::dslx_ir;
using ir::ExprPtr;
using ir::StmtPtr;
using ir::TypePtr;

namespace {

const IR::ActionList* GetActionList(const IR::P4Table* t) {
    return t->getActionList();
}

// Build the per-table entry struct.
std::unique_ptr<ir::StructDef> BuildEntryStruct(
    const IR::P4Table* table, const LowerContext& ctx,
    const std::string& tname) {
    std::vector<ir::StructDef::Field> fields;

    auto key = table->getKey();
    if (key != nullptr) {
        for (auto ke : key->keyElements) {
            auto kt = ctx.typeMap->getType(ke->expression, false);
            std::string kname = ExprToTextualName(ke->expression, ctx);
            fields.emplace_back(kname, LowerType(kt, ctx.typeMap));
            std::string mt = std::string(ke->matchType->toString());
            if (mt == "ternary" || mt == "lpm") {
                fields.emplace_back(kname + "_mask", LowerType(kt, ctx.typeMap));
            }
            // selector fields are stored as exact (no mask)
        }
    }

    fields.emplace_back("action_id", ir::T_u(8));

    auto al = GetActionList(table);
    if (al != nullptr) {
        for (auto ale : al->actionList) {
            auto mc = ale->expression->to<IR::MethodCallExpression>();
            if (mc == nullptr) continue;
            auto pe = mc->method->to<IR::PathExpression>();
            if (pe == nullptr) continue;
            auto decl = ctx.refMap->getDeclaration(pe->path, true);
            auto act = decl->to<IR::P4Action>();
            if (act == nullptr) continue;

            for (auto p : act->parameters->parameters) {
                if (p->direction == IR::Direction::None) {
                    auto pt = ctx.typeMap->getType(p, false);
                    fields.emplace_back(
                        std::string(act->name.toString()) + "_" +
                            std::string(p->name.toString()),
                        LowerType(pt, ctx.typeMap));
                }
            }
        }
    }

    fields.emplace_back("_valid", ir::T_bool());
    return std::make_unique<ir::StructDef>(tname + "_entry_t", std::move(fields));
}

// Match condition for one key element: exact / lpm / ternary.
ExprPtr KeyMatchExpr(const IR::KeyElement* ke, const LowerContext& ctx) {
    std::string kname = ExprToTextualName(ke->expression, ctx);
    std::string mt = std::string(ke->matchType->toString());
    auto entry_field = ir::E_attr(ir::E_name("entry"), kname);
    auto lookup_var = ir::E_name("lookup_" + kname);
    if (mt == "exact" || mt == "selector") {
        return ir::E_binop(ir::BinopKind::kEq, std::move(entry_field),
                            std::move(lookup_var));
    }
    // ternary / lpm
    auto mask_field = ir::E_attr(ir::E_name("entry"), kname + "_mask");
    // (entry.k & entry.k_mask) == (lookup_k & entry.k_mask)
    auto entry_field2 = ir::E_attr(ir::E_name("entry"), kname);
    auto mask_field2 = ir::E_attr(ir::E_name("entry"), kname + "_mask");
    auto lookup_var2 = ir::E_name("lookup_" + kname);
    return ir::E_binop(
        ir::BinopKind::kEq,
        ir::E_binop(ir::BinopKind::kBAnd, std::move(entry_field), std::move(mask_field)),
        ir::E_binop(ir::BinopKind::kBAnd, std::move(lookup_var2), std::move(mask_field2)));
}

// Reduce a vector of bool exprs with `&&`. Returns BoolLiteral(true) if empty.
ExprPtr AndAll(std::vector<ExprPtr> conds) {
    if (conds.empty()) return ir::E_bool(true);
    auto acc = std::move(conds[0]);
    for (size_t i = 1; i < conds.size(); ++i) {
        acc = ir::E_binop(ir::BinopKind::kLAnd, std::move(acc), std::move(conds[i]));
    }
    return acc;
}

std::unique_ptr<ir::Function> BuildApplyFunction(
    const IR::P4Table* table, const LowerContext& ctx,
    const std::string& tname) {
    // Function params = threaded + entries[]
    std::vector<ir::Param> params = BindingParams(*ctx.block_info);
    params.emplace_back(
        "entries",
        ir::T_array(ir::T_ref(tname + "_entry_t"),
                     ir::E_name("MAX_TABLE_ENTRIES")));

    std::vector<StmtPtr> stmts;

    // 1) lookup vars
    auto key = table->getKey();
    std::vector<const IR::KeyElement*> key_elems;
    if (key != nullptr) {
        for (auto ke : key->keyElements) {
            key_elems.push_back(ke);
            std::string kname = ExprToTextualName(ke->expression, ctx);
            stmts.push_back(ir::S_let_inferred(
                "lookup_" + kname, LowerExpr(ke->expression, ctx)));
        }
    }
    stmts.push_back(ir::S_comment("Search entries with for-loop"));

    // 2) for-loop accumulator type/pattern: (bool, u32, <bindings...>)
    std::string acc_pat;
    {
        std::string s = "(matched, match_idx";
        for (const auto& [vn, _t] : ctx.block_info->all_threaded) {
            s += ", " + vn;
        }
        s += ")";
        acc_pat = s;
    }
    std::vector<ir::TypePtr> acc_types;
    acc_types.push_back(ir::T_bool());
    acc_types.push_back(ir::T_u(32));
    for (const auto& [_n, t] : ctx.block_info->all_threaded) {
        acc_types.push_back(ir::T_ref(t));
    }
    auto acc_type = ir::T_tuple(std::move(acc_types));

    // 3) For-loop body
    std::vector<StmtPtr> loop_stmts;
    loop_stmts.push_back(ir::S_let_inferred(
        "entry", ir::E_index(ir::E_name("entries"), ir::E_name("i"))));

    // outer if: !matched && entry._valid
    auto outer_cond = ir::E_binop(
        ir::BinopKind::kLAnd,
        ir::E_unop(ir::UnopKind::kNot, ir::E_name("matched")),
        ir::E_attr(ir::E_name("entry"), "_valid"));

    // Acc tuple pre-builders
    auto acc_match_found = [&]() -> ExprPtr {
        std::vector<ExprPtr> v;
        v.push_back(ir::E_bool(true));
        v.push_back(ir::E_name("i"));
        for (const auto& [vn, _t] : ctx.block_info->all_threaded) {
            v.push_back(ir::E_name(vn));
        }
        return ir::E_tuple(std::move(v));
    };
    auto acc_unchanged = [&]() -> ExprPtr {
        std::vector<ExprPtr> v;
        v.push_back(ir::E_name("matched"));
        v.push_back(ir::E_name("match_idx"));
        for (const auto& [vn, _t] : ctx.block_info->all_threaded) {
            v.push_back(ir::E_name(vn));
        }
        return ir::E_tuple(std::move(v));
    };

    // inner: if all key matches, return acc_match_found else acc_unchanged
    ExprPtr inner_then;
    if (!key_elems.empty()) {
        std::vector<ExprPtr> conds;
        for (auto ke : key_elems) conds.push_back(KeyMatchExpr(ke, ctx));
        auto match_cond = AndAll(std::move(conds));
        inner_then = ir::E_cond(
            std::move(match_cond),
            ir::B_make({}, acc_match_found()),
            ir::B_make({}, acc_unchanged()));
    } else {
        inner_then = acc_match_found();
    }

    auto outer_expr = ir::E_cond(
        std::move(outer_cond),
        ir::B_make({}, std::move(inner_then)),
        ir::B_make({}, acc_unchanged()));

    auto body_block = ir::B_make(std::move(loop_stmts), std::move(outer_expr));

    // Initial accumulator: (false, u32:0, <bindings...>)
    std::vector<ExprPtr> init_v;
    init_v.push_back(ir::E_bool(false));
    init_v.push_back(ir::E_uN(32, "0"));
    for (const auto& [vn, _t] : ctx.block_info->all_threaded) {
        init_v.push_back(ir::E_name(vn));
    }
    auto init_expr = ir::E_tuple(std::move(init_v));

    auto for_expr = std::make_unique<ir::For>(
        std::string("i"), acc_pat, ir::T_u(32), std::move(acc_type),
        ir::E_uN(32, "0"), ir::E_name("MAX_TABLE_ENTRIES"),
        std::move(body_block), std::move(init_expr));

    stmts.push_back(ir::S_let_inferred(acc_pat, std::move(for_expr)));

    // 4) Dispatch on action_id
    // Helper: wrap a binding expression in (true, bindings) for the hit+tuple
    // return type.
    auto wrap_hit = [&](bool hit, ExprPtr bindings) -> ExprPtr {
        std::vector<ExprPtr> v;
        v.push_back(ir::E_bool(hit));
        v.push_back(std::move(bindings));
        return ir::E_tuple(std::move(v));
    };

    ExprPtr dispatch_inner = wrap_hit(true, BindingExpr(*ctx.block_info));
    auto al = GetActionList(table);
    if (al != nullptr) {
        // Build chain from end backwards: else if id==N { call N(...) } else { binding }
        std::vector<std::pair<unsigned, const IR::P4Action*>> actions;
        unsigned aid = 0;
        for (auto ale : al->actionList) {
            auto mc = ale->expression->to<IR::MethodCallExpression>();
            if (mc == nullptr) continue;
            auto pe = mc->method->to<IR::PathExpression>();
            if (pe == nullptr) continue;
            auto decl = ctx.refMap->getDeclaration(pe->path, true);
            auto act = decl->to<IR::P4Action>();
            if (act == nullptr) continue;
            actions.emplace_back(aid++, act);
        }
        ExprPtr chain = wrap_hit(true, BindingExpr(*ctx.block_info));
        for (auto it = actions.rbegin(); it != actions.rend(); ++it) {
            unsigned id = it->first;
            auto act = it->second;
            auto cond = ir::E_binop(
                ir::BinopKind::kEq,
                ir::E_attr(ir::E_name("entry"), "action_id"),
                ir::E_uN(8, std::to_string(id)));
            std::vector<ExprPtr> args;
            for (const auto& [vn, _t] : ctx.block_info->all_threaded) {
                args.push_back(ir::E_name(vn));
            }
            for (auto p : act->parameters->parameters) {
                if (p->direction == IR::Direction::None) {
                    args.push_back(ir::E_attr(
                        ir::E_name("entry"),
                        std::string(act->name.toString()) + "_" +
                            std::string(p->name.toString())));
                }
            }
            auto call = ir::E_call_named(std::string(act->name.toString()),
                                          std::move(args));
            chain = ir::E_cond(std::move(cond),
                                ir::B_make({}, wrap_hit(true, std::move(call))),
                                ir::B_make({}, std::move(chain)));
        }
        dispatch_inner = std::move(chain);
    }

    // matched ? dispatch_inner : default-action(=binding)
    std::vector<StmtPtr> dispatch_pre;
    dispatch_pre.push_back(ir::S_let_inferred(
        "entry", ir::E_index(ir::E_name("entries"), ir::E_name("match_idx"))));

    auto matched_block = ir::B_make(std::move(dispatch_pre), std::move(dispatch_inner));
    auto unmatched_block = ir::B_make({}, wrap_hit(false, BindingExpr(*ctx.block_info)));
    auto final_cond = ir::E_cond(ir::E_name("matched"),
                                  std::move(matched_block),
                                  std::move(unmatched_block));
    std::string hit_pat;
    if (ctx.block_info->all_threaded.size() == 1) {
        hit_pat = "(__hit, " + ctx.block_info->all_threaded[0].first + ")";
    } else {
        hit_pat = "(__hit, " + BindingPattern(*ctx.block_info) + ")";
    }
    stmts.push_back(ir::S_let_inferred(hit_pat, std::move(final_cond)));

    std::vector<ExprPtr> tail_v;
    tail_v.push_back(ir::E_name("__hit"));
    tail_v.push_back(BindingExpr(*ctx.block_info));
    auto body = ir::B_make(std::move(stmts), ir::E_tuple(std::move(tail_v)));
    std::vector<TypePtr> ret_ts;
    ret_ts.push_back(ir::T_bool());
    ret_ts.push_back(BindingReturnType(*ctx.block_info));
    auto ret_type = ir::T_tuple(std::move(ret_ts));
    return std::make_unique<ir::Function>(
        "table_" + tname + "_apply", std::move(params),
        std::move(ret_type), std::move(body), /*is_pub=*/true);
}

}  // namespace

void LowerTable(const IR::P4Table* table, const LowerContext& ctx,
                ::dslx_ir::Module* module) {
    std::string tname = std::string(table->name.toString());
    module->AddDecl(std::make_unique<ir::CommentDecl>(
        "===== Table: " + tname + " ====="));
    module->AddDecl(std::make_unique<ir::BlankLineDecl>());
    module->AddDecl(BuildEntryStruct(table, ctx, tname));
    module->AddDecl(BuildApplyFunction(table, ctx, tname));
}

}  // namespace P4::DSLX::adapter
