// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "p4_parser_lower.h"

#include <utility>
#include <vector>

#include "../dslx_ir/build.h"
#include "binding_helpers.h"
#include "p4_expr_lower.h"
#include "p4_stmt_lower.h"
#include "p4_type_lower.h"

namespace P4::DSLX::adapter {

namespace ir = ::dslx_ir;
using ir::ExprPtr;
using ir::StmtPtr;

namespace {

// Build the (h, m, ig, ..., offset) tuple expression / pattern.
ExprPtr ParserBindingExprWithOffset(const PipelineBlockInfo& info) {
    std::vector<ExprPtr> v;
    for (const auto& [vn, _t] : info.all_threaded) {
        v.push_back(ir::E_name(vn));
    }
    v.push_back(ir::E_name("offset"));
    return ir::E_tuple(std::move(v));
}

std::string ParserBindingPatWithOffset(const PipelineBlockInfo& info) {
    std::string s = "(";
    for (size_t i = 0; i < info.all_threaded.size(); ++i) {
        if (i != 0) s += ", ";
        s += info.all_threaded[i].first;
    }
    if (!info.all_threaded.empty()) s += ", ";
    s += "offset)";
    return s;
}

ir::TypePtr ParserBindingRetType(const PipelineBlockInfo& info) {
    std::vector<ir::TypePtr> ts;
    for (const auto& [_n, t] : info.all_threaded) {
        ts.push_back(ir::T_ref(t));
    }
    ts.push_back(ir::T_u(32));
    return ir::T_tuple(std::move(ts));
}

// Build:  let <field> = packet[offset +: <fieldType>];
//         let offset = offset + u32:<width>;
void EmitFieldExtract(const IR::StructField* f, const LowerContext& ctx,
                      std::vector<StmtPtr>* out) {
    auto ft = ctx.typeMap->getType(f, false);
    if (ft == nullptr) ft = ctx.typeMap->getType(f->type, false);
    if (ft == nullptr) ft = f->type;
    int width = WidthOfType(ft, ctx.typeMap);
    auto width_ty = LowerType(ft, ctx.typeMap);
    auto slice = ir::E_slice(ir::E_name("packet"), ir::E_name("offset"),
                              std::move(width_ty));
    out->push_back(ir::S_let_inferred(std::string(f->name.toString()),
                                        std::move(slice)));
    out->push_back(ir::S_let_inferred(
        "offset",
        ir::E_binop(ir::BinopKind::kAdd, ir::E_name("offset"),
                     ir::E_uN(32, std::to_string(width)))));
}

// Lower an extract(hdr.x) call: extract fields, build header struct, splat
// into headers container.
void EmitExtractCall(const IR::MethodCallStatement* mcs,
                     const LowerContext& ctx, std::vector<StmtPtr>* out) {
    auto mi = mcs->methodCall;
    if (mi->arguments->size() < 1) return;
    auto arg = mi->arguments->at(0)->expression;
    auto at = ctx.typeMap->getType(arg, false);
    auto ht = at ? at->to<IR::Type_Header>() : nullptr;
    if (ht == nullptr) return;

    std::string hvar = "header";
    if (auto mem = arg->to<IR::Member>()) {
        hvar = std::string(mem->member.toString());
    }
    out->push_back(ir::S_comment("Extract " + hvar));
    for (auto f : ht->fields) EmitFieldExtract(f, ctx, out);

    // Reconstruct header struct (with _valid: true)
    std::vector<ir::StructInstance::Field> fs;
    for (auto f : ht->fields) {
        std::string fn = std::string(f->name.toString());
        fs.emplace_back(fn, ir::E_name(fn));
    }
    fs.emplace_back("_valid", ir::E_bool(true));
    out->push_back(ir::S_let_inferred(
        hvar, ir::E_struct(DslxNameForHeader(ht), std::move(fs))));

    // Splat into headers container
    if (!ctx.block_info->all_threaded.empty()) {
        std::string hcontainer = ctx.block_info->all_threaded[0].first;
        std::vector<ir::SplatStructInstance::Field> upfs;
        upfs.emplace_back(hvar, ir::E_name(hvar));
        out->push_back(ir::S_let_inferred(
            hcontainer,
            ir::E_struct_splat(ctx.block_info->headers_type_name,
                                std::move(upfs), ir::E_name(hcontainer))));
    }
}

// Body for one parser state (excluding the transition).
void EmitStateBody(const IR::ParserState* state, const LowerContext& ctx,
                   std::vector<StmtPtr>* out) {
    for (auto stmt : state->components) {
        if (auto mcs = stmt->to<IR::MethodCallStatement>()) {
            auto mi = mcs->methodCall;
            if (auto mem = mi->method->to<IR::Member>()) {
                if (mem->member == "extract") {
                    EmitExtractCall(mcs, ctx, out);
                    continue;
                }
            }
            out->push_back(ir::S_comment("ignored method call in parser state"));
            continue;
        }
        if (auto as = stmt->to<IR::AssignmentStatement>()) {
            LowerStmt(as, ctx, out, /*enable_table_apply=*/false);
            continue;
        }
    }
}

ExprPtr CallNextState(const std::string& gress, const std::string& next_state,
                      const LowerContext& ctx) {
    std::vector<ExprPtr> args;
    args.push_back(ir::E_name("packet"));
    for (const auto& [vn, _t] : ctx.block_info->all_threaded) {
        args.push_back(ir::E_name(vn));
    }
    args.push_back(ir::E_name("offset"));
    return ir::E_call_named(gress + "_parser_state_" + next_state,
                             std::move(args));
}

// Body for select(...) transition: nested if/else-if chain with each branch
// evaluating to either the binding tuple (accept/reject) or a state call.
ExprPtr LowerSelectExpr(const IR::SelectExpression* sel,
                         const std::string& gress, const LowerContext& ctx) {
    // Build key expression
    ExprPtr key_expr;
    auto& comps = sel->select->components;
    if (comps.size() == 1) {
        key_expr = LowerExpr(comps.at(0), ctx);
    } else {
        std::vector<ExprPtr> v;
        for (auto k : comps) v.push_back(LowerExpr(k, ctx));
        key_expr = ir::E_tuple(std::move(v));
    }

    // Build chain back-to-front: start from a default tail (binding tuple
    // representing a reject), then wrap each non-default case as
    // `if key == case { branch_value } else { acc }`. Default case becomes
    // the new tail when seen.
    ExprPtr chain = ParserBindingExprWithOffset(*ctx.block_info);
    bool default_seen = false;
    auto branch_value = [&](const std::string& next) -> ExprPtr {
        if (next == "accept" || next == "reject") {
            return ParserBindingExprWithOffset(*ctx.block_info);
        }
        return CallNextState(gress, next, ctx);
    };

    for (auto it = sel->selectCases.rbegin(); it != sel->selectCases.rend(); ++it) {
        auto sc = *it;
        std::string next = std::string(sc->state->path->name.toString());
        auto bv = branch_value(next);
        if (sc->keyset->is<IR::DefaultExpression>()) {
            chain = std::move(bv);  // default replaces tail
            default_seen = true;
            continue;
        }
        // Midend may transform default into 0 &&& 0 mask.
        if (auto mask = sc->keyset->to<IR::Mask>()) {
            bool is_default_mask = false;
            if (auto left_lit = mask->left->to<IR::Constant>()) {
                if (auto right_lit = mask->right->to<IR::Constant>()) {
                    if (left_lit->value == 0 && right_lit->value == 0) {
                        is_default_mask = true;
                    }
                }
            }
            if (is_default_mask) {
                chain = std::move(bv);
                default_seen = true;
                continue;
            }
        }
        auto case_val = LowerExpr(sc->keyset, ctx);
        // Re-build key_expr each iteration since we move it; LowerExpr is cheap.
        ExprPtr key_copy;
        if (comps.size() == 1) {
            key_copy = LowerExpr(comps.at(0), ctx);
        } else {
            std::vector<ExprPtr> v;
            for (auto k : comps) v.push_back(LowerExpr(k, ctx));
            key_copy = ir::E_tuple(std::move(v));
        }
        auto cond = ir::E_binop(ir::BinopKind::kEq, std::move(key_copy),
                                 std::move(case_val));
        chain = ir::E_cond(std::move(cond),
                            ir::B_make({}, std::move(bv)),
                            ir::B_make({}, std::move(chain)));
    }
    (void)key_expr;        // unused outside the per-iteration rebuild
    (void)default_seen;
    return chain;
}

std::unique_ptr<ir::Function> LowerState(const IR::ParserState* state,
                                           const std::string& gress,
                                           const LowerContext& ctx) {
    std::string sname = gress + "_parser_state_" + std::string(state->name.toString());

    std::vector<ir::Param> params;
    params.emplace_back("packet",
                         ir::T_bits(ir::E_name("MAX_PACKET_BITS")));
    for (const auto& [vn, tn] : ctx.block_info->all_threaded) {
        params.emplace_back(vn, ir::T_ref(tn));
    }
    params.emplace_back("offset", ir::T_u(32));

    std::vector<StmtPtr> body_stmts;
    EmitStateBody(state, ctx, &body_stmts);

    ExprPtr tail;
    if (state->selectExpression == nullptr) {
        tail = ParserBindingExprWithOffset(*ctx.block_info);
    } else if (auto pe = state->selectExpression->to<IR::PathExpression>()) {
        std::string next = std::string(pe->path->name.toString());
        if (next == "accept" || next == "reject") {
            tail = ParserBindingExprWithOffset(*ctx.block_info);
        } else {
            tail = CallNextState(gress, next, ctx);
        }
    } else if (auto sel = state->selectExpression->to<IR::SelectExpression>()) {
        tail = LowerSelectExpr(sel, gress, ctx);
    } else {
        tail = ParserBindingExprWithOffset(*ctx.block_info);
    }

    auto body = ir::B_make(std::move(body_stmts), std::move(tail));
    return std::make_unique<ir::Function>(
        sname, std::move(params),
        ParserBindingRetType(*ctx.block_info),
        std::move(body), /*is_pub=*/true);
}

std::unique_ptr<ir::Function> LowerParserApply(
    const IR::P4Parser* /*parser*/, const std::string& gress,
    const LowerContext& ctx) {
    std::vector<ir::Param> params;
    params.emplace_back("packet",
                         ir::T_bits(ir::E_name("MAX_PACKET_BITS")));
    for (const auto& [vn, tn] : ctx.block_info->intrinsic_params) {
        params.emplace_back(vn, ir::T_ref(tn));
    }

    std::vector<StmtPtr> stmts;
    // Initialize threaded params except intrinsics (which come in as args).
    for (const auto& [vn, tn] : ctx.block_info->all_threaded) {
        bool is_intrinsic = false;
        for (const auto& [in, _it] : ctx.block_info->intrinsic_params) {
            if (in == vn) {
                is_intrinsic = true;
                break;
            }
        }
        if (!is_intrinsic) {
            stmts.push_back(ir::S_comment("Initialize " + vn));
            stmts.push_back(ir::S_let_inferred(vn, ir::E_zero(ir::T_ref(tn))));
        }
    }
    stmts.push_back(ir::S_let_inferred("offset", ir::E_uN(32, "0")));
    stmts.push_back(ir::S_comment("Call start state"));

    // bind = start_state(packet, threaded..., offset)
    std::vector<ExprPtr> args;
    args.push_back(ir::E_name("packet"));
    for (const auto& [vn, _t] : ctx.block_info->all_threaded) {
        args.push_back(ir::E_name(vn));
    }
    args.push_back(ir::E_name("offset"));
    auto call = ir::E_call_named(gress + "_parser_state_start", std::move(args));
    stmts.push_back(ir::S_let_inferred(ParserBindingPatWithOffset(*ctx.block_info),
                                         std::move(call)));

    auto body = ir::B_make(std::move(stmts),
                            ParserBindingExprWithOffset(*ctx.block_info));
    return std::make_unique<ir::Function>(
        gress + "_parser_apply", std::move(params),
        ParserBindingRetType(*ctx.block_info),
        std::move(body), /*is_pub=*/true);
}

}  // namespace

void LowerParser(const IR::P4Parser* parser, const LowerContext& ctx,
                 const std::string& gress, ::dslx_ir::Module* module) {
    module->AddDecl(std::make_unique<ir::CommentDecl>(
        "===== " + gress + " Parser: " + ctx.block_info->name + " ====="));
    module->AddDecl(std::make_unique<ir::BlankLineDecl>());

    // Collect all states.
    std::vector<const IR::ParserState*> states;
    const IR::ParserState* start_state = nullptr;
    for (auto state : parser->states) {
        if (state->name == "start") {
            start_state = state;
        } else if (state->name != "accept" && state->name != "reject") {
            states.push_back(state);
        }
    }

    // Build a map from state name to state pointer.
    std::map<std::string, const IR::ParserState*> state_map;
    for (auto s : states) {
        state_map[std::string(s->name.toString())] = s;
    }

    // Collect outgoing edges (transitions to named states).
    auto collect_targets = [&](const IR::ParserState* s) -> std::vector<std::string> {
        std::vector<std::string> targets;
        if (s->selectExpression == nullptr) return targets;
        if (auto pe = s->selectExpression->to<IR::PathExpression>()) {
            std::string n = std::string(pe->path->name.toString());
            if (n != "accept" && n != "reject") targets.push_back(n);
            return targets;
        }
        if (auto sel = s->selectExpression->to<IR::SelectExpression>()) {
            for (auto sc : sel->selectCases) {
                std::string n = std::string(sc->state->path->name.toString());
                if (n != "accept" && n != "reject") targets.push_back(n);
            }
            return targets;
        }
        return targets;
    };

    std::map<std::string, std::vector<std::string>> edges;
    for (auto s : states) {
        edges[std::string(s->name.toString())] = collect_targets(s);
    }

    // Topological sort (Kahn's algorithm) so callees are defined before callers.
    // in_degree[state] = number of other states it calls (prerequisites).
    std::map<std::string, int> in_degree;
    for (auto s : states) in_degree[std::string(s->name.toString())] = 0;
    for (const auto& [src, tgts] : edges) {
        for (const auto& tgt : tgts) {
            // Skip self-loops - they don't affect prereq count for ordering.
            if (tgt == src) continue;
            if (state_map.count(tgt) != 0) in_degree[src]++;
        }
    }

    std::vector<const IR::ParserState*> sorted;
    std::deque<std::string> queue;
    for (const auto& [name, deg] : in_degree) {
        if (deg == 0) queue.push_back(name);
    }
    while (!queue.empty()) {
        std::string n = queue.front();
        queue.pop_front();
        if (state_map.count(n) != 0) sorted.push_back(state_map[n]);
        // n was emitted; for every state that calls n, n is no longer a prereq.
        for (const auto& [src, tgts] : edges) {
            for (const auto& tgt : tgts) {
                if (tgt == n && state_map.count(src) != 0) {
                    in_degree[src]--;
                    if (in_degree[src] == 0) queue.push_back(src);
                }
            }
        }
    }
    // Append any remaining (cycle) in original order.
    for (auto s : states) {
        std::string n = std::string(s->name.toString());
        bool already = false;
        for (auto os : sorted) {
            if (os == s) { already = true; break; }
        }
        if (!already) sorted.push_back(s);
    }

    // Emit in dependency order (callees first).
    for (auto s : sorted) {
        module->AddDecl(LowerState(s, gress, ctx));
    }
    if (start_state != nullptr) module->AddDecl(LowerState(start_state, gress, ctx));

    module->AddDecl(LowerParserApply(parser, gress, ctx));
}

}  // namespace P4::DSLX::adapter
