// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "p4_deparser_lower.h"

#include <utility>
#include <vector>

#include "../dslx_ir/build.h"
#include "p4_expr_lower.h"
#include "p4_type_lower.h"

namespace P4::DSLX::adapter {

namespace ir = ::dslx_ir;
using ir::ExprPtr;
using ir::StmtPtr;

namespace {

// Walk the deparser body looking for `pkt.emit(hdr)` and collect each
// header expression with its resolved Type_Header.
struct HeaderEmit {
    const IR::Type_Header* type;
    const IR::Expression* expr;
};

std::vector<HeaderEmit> CollectEmits(const IR::P4Control* deparser,
                                      const LowerContext& ctx) {
    std::vector<HeaderEmit> out;
    if (deparser == nullptr || deparser->body == nullptr) return out;
    for (auto stmt : deparser->body->components) {
        auto mcs = stmt->to<IR::MethodCallStatement>();
        if (mcs == nullptr) continue;
        auto mc = mcs->methodCall;
        auto mem = mc->method->to<IR::Member>();
        if (mem == nullptr) continue;
        if (mem->member != "emit") continue;
        if (mc->arguments->size() < 1) continue;
        auto arg = mc->arguments->at(0)->expression;
        auto t = ctx.typeMap->getType(arg, false);
        if (t == nullptr) continue;
        auto ht = t->to<IR::Type_Header>();
        if (ht == nullptr) continue;
        out.push_back({ht, arg});
    }
    return out;
}

}  // namespace

void LowerDeparser(const IR::P4Control* deparser, const LowerContext& ctx,
                   const std::string& gress_name, ir::Module* module) {
    module->AddDecl(std::make_unique<ir::CommentDecl>(
        "===== " + gress_name + " Deparser ====="));
    module->AddDecl(std::make_unique<ir::BlankLineDecl>());

    // Function signature: just the headers param.
    std::vector<ir::Param> params;
    if (!ctx.block_info->all_threaded.empty()) {
        const auto& [vn, tn] = ctx.block_info->all_threaded[0];
        params.emplace_back(vn, ir::T_ref(tn));
    } else {
        params.emplace_back("headers", ir::T_ref("Headers"));
    }
    auto ret_type = ir::T_bits(ir::E_name("MAX_PACKET_BITS"));

    std::vector<StmtPtr> body;
    body.push_back(ir::S_let_inferred(
        "output", ir::E_cast(ir::E_uN(32, "0"),
                              ir::T_bits(ir::E_name("MAX_PACKET_BITS")))));
    body.push_back(ir::S_let_inferred("offset", ir::E_uN(32, "0")));

    // For each header, emit the conditional update chain.
    auto emits = CollectEmits(deparser, ctx);
    for (const auto& he : emits) {
        // Build the field-update chain inline rather than calling EmitOneHeader,
        // because we need the header_path expression repeatedly across fields.
        std::vector<StmtPtr> then_stmts;
        for (auto field : he.type->fields) {
            auto ft = ctx.typeMap->getType(field, false);
            if (ft == nullptr) ft = ctx.typeMap->getType(field->type, false);
            int width = WidthOfType(ft, ctx.typeMap);
            std::string fname = std::string(field->name.toString());

            std::vector<ExprPtr> args;
            args.push_back(ir::E_name("output"));
            args.push_back(ir::E_name("offset"));
            args.push_back(ir::E_attr(LowerExpr(he.expr, ctx), fname));
            then_stmts.push_back(ir::S_let_inferred(
                "output",
                ir::E_call_named("bit_slice_update", std::move(args))));
            then_stmts.push_back(ir::S_let_inferred(
                "offset",
                ir::E_binop(ir::BinopKind::kAdd, ir::E_name("offset"),
                             ir::E_uN(32, std::to_string(width)))));
        }

        std::vector<ExprPtr> tail_v;
        tail_v.push_back(ir::E_name("output"));
        tail_v.push_back(ir::E_name("offset"));
        auto then_block = ir::B_make(std::move(then_stmts),
                                       ir::E_tuple(std::move(tail_v)));

        std::vector<ExprPtr> else_v;
        else_v.push_back(ir::E_name("output"));
        else_v.push_back(ir::E_name("offset"));
        auto else_block = ir::B_make({}, ir::E_tuple(std::move(else_v)));

        auto cond = ir::E_attr(LowerExpr(he.expr, ctx), "_valid");
        auto if_expr = ir::E_cond(std::move(cond), std::move(then_block),
                                    std::move(else_block));
        body.push_back(ir::S_comment("Emit if valid"));
        body.push_back(ir::S_let_inferred("(output, offset)", std::move(if_expr)));
    }

    auto body_block = ir::B_make(std::move(body), ir::E_name("output"));
    module->AddDecl(std::make_unique<ir::Function>(
        gress_name + "_deparser_apply", std::move(params), std::move(ret_type),
        std::move(body_block), /*is_pub=*/true));
}

}  // namespace P4::DSLX::adapter
