// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "p4_expr_lower.h"

#include <vector>

#include "../dslx_ir/build.h"
#include "../dslx_ir/formatter.h"
#include "lib/error.h"
#include "p4_type_lower.h"

namespace P4::DSLX::adapter {

using ::dslx_ir::ExprPtr;
namespace ir = ::dslx_ir;

namespace {

ir::BinopKind P4BinopKind(const IR::Operation_Binary* expr) {
    if (expr->is<IR::Add>())  return ir::BinopKind::kAdd;
    if (expr->is<IR::Sub>())  return ir::BinopKind::kSub;
    if (expr->is<IR::Mul>())  return ir::BinopKind::kMul;
    if (expr->is<IR::BAnd>()) return ir::BinopKind::kBAnd;
    if (expr->is<IR::BOr>())  return ir::BinopKind::kBOr;
    if (expr->is<IR::BXor>()) return ir::BinopKind::kBXor;
    if (expr->is<IR::Shl>())  return ir::BinopKind::kShl;
    if (expr->is<IR::Shr>())  return ir::BinopKind::kShr;
    if (expr->is<IR::Equ>())  return ir::BinopKind::kEq;
    if (expr->is<IR::Neq>())  return ir::BinopKind::kNe;
    if (expr->is<IR::Lss>())  return ir::BinopKind::kLt;
    if (expr->is<IR::Leq>())  return ir::BinopKind::kLe;
    if (expr->is<IR::Grt>())  return ir::BinopKind::kGt;
    if (expr->is<IR::Geq>())  return ir::BinopKind::kGe;
    if (expr->is<IR::LAnd>()) return ir::BinopKind::kLAnd;
    if (expr->is<IR::LOr>())  return ir::BinopKind::kLOr;
    if (expr->is<IR::Concat>()) return ir::BinopKind::kConcat;
    return ir::BinopKind::kAdd;  // unreachable; caller filters
}

}  // namespace

ExprPtr LowerExpr(const IR::Expression* expr, const LowerContext& ctx) {
    if (expr == nullptr) return ir::E_verbatim("/* null */");

    if (auto c = expr->to<IR::Constant>()) {
        auto type = ctx.typeMap->getType(expr, false);
        std::string prefix = "u32";
        if (auto tb = type ? type->to<IR::Type_Bits>() : nullptr) {
            prefix = (tb->isSigned ? "s" : "u") + std::to_string(tb->size);
        }
        return ir::E_num(prefix, c->value.str());
    }
    if (auto b = expr->to<IR::BoolLiteral>()) {
        return ir::E_bool(b->value);
    }
    if (auto pe = expr->to<IR::PathExpression>()) {
        std::string n = std::string(pe->path->name.toString());
        auto it = ctx.param_name_map.find(n);
        return ir::E_name(it != ctx.param_name_map.end() ? it->second : n);
    }
    if (auto m = expr->to<IR::Member>()) {
        return ir::E_attr(LowerExpr(m->expr, ctx),
                           std::string(m->member.toString()));
    }
    if (auto cast = expr->to<IR::Cast>()) {
        auto t = ctx.typeMap->getType(cast, false);
        return ir::E_cast(LowerExpr(cast->expr, ctx), LowerType(t, ctx.typeMap));
    }
    if (auto sl = expr->to<IR::Slice>()) {
        auto base = LowerExpr(sl->e0, ctx);
        auto hi = sl->e1->to<IR::Constant>();
        auto lo = sl->e2->to<IR::Constant>();
        if (hi != nullptr && lo != nullptr) {
            int hi_v = static_cast<int>(hi->value);
            int lo_v = static_cast<int>(lo->value);
            int width = hi_v - lo_v + 1;
            auto width_ty = (width > 64)
                ? ir::T_bits(ir::E_uN(32, std::to_string(width)))
                : ir::T_u(width);
            return ir::E_slice(std::move(base),
                                ir::E_num("", std::to_string(lo_v)),
                                std::move(width_ty));
        }
        return ir::E_verbatim("/* dynamic slice unsupported */");
    }
    if (auto mux = expr->to<IR::Mux>()) {
        return ir::E_cond(LowerExpr(mux->e0, ctx),
                           LowerExpr(mux->e1, ctx),
                           LowerExpr(mux->e2, ctx));
    }
    if (auto bin = expr->to<IR::Operation_Binary>()) {
        if (bin->is<IR::Mask>()) {
            // P4 ternary value &&& mask — model as (val, mask) tuple.
            std::vector<ExprPtr> v;
            v.push_back(LowerExpr(bin->left, ctx));
            v.push_back(LowerExpr(bin->right, ctx));
            return ir::E_tuple(std::move(v));
        }
        return ir::E_binop(P4BinopKind(bin),
                            LowerExpr(bin->left, ctx),
                            LowerExpr(bin->right, ctx));
    }
    if (auto un = expr->to<IR::Operation_Unary>()) {
        ir::UnopKind k = ir::UnopKind::kNeg;
        if (un->is<IR::Neg>()) k = ir::UnopKind::kNeg;
        else if (un->is<IR::Cmpl>()) k = ir::UnopKind::kInvert;
        else if (un->is<IR::LNot>()) k = ir::UnopKind::kNot;
        else {
            ::P4::error(ErrorType::ERR_UNSUPPORTED,
                        "Unsupported unary op %1% for DSLX", expr);
            return ir::E_verbatim("/* unsupported unary */");
        }
        return ir::E_unop(k, LowerExpr(un->expr, ctx));
    }
    if (auto mc = expr->to<IR::MethodCallExpression>()) {
        // Special-case isValid → `<base>._valid`.
        if (auto mem = mc->method->to<IR::Member>()) {
            if (mem->member == "isValid") {
                return ir::E_attr(LowerExpr(mem->expr, ctx), "_valid");
            }
            if (mem->member == "setValid" || mem->member == "setInvalid") {
                // These appear only as statements; defensive comment if seen here.
                return ir::E_verbatim(std::string("/* ") +
                                       std::string(mem->member.toString()) + " */");
            }
            if (mem->member == "lookahead") {
                // packet.lookahead<bit<N>>() → packet[offset +: uN]
                if (mc->typeArguments->size() == 1) {
                    auto ty = mc->typeArguments->at(0);
                    if (auto tb = ty->to<IR::Type_Bits>()) {
                        auto width_ty = tb->size > 64
                            ? ir::T_bits(ir::E_uN(32, std::to_string(tb->size)))
                            : ir::T_u(tb->size);
                        return ir::E_slice(ir::E_name("packet"), ir::E_name("offset"),
                                           std::move(width_ty));
                    }
                }
                return ir::E_verbatim("/* unsupported lookahead */");
            }
        }
        std::vector<ExprPtr> args;
        for (auto a : *mc->arguments) {
            args.push_back(LowerExpr(a->expression, ctx));
        }
        return ir::E_call(LowerExpr(mc->method, ctx), std::move(args));
    }
    if (auto ai = expr->to<IR::ArrayIndex>()) {
        return ir::E_index(LowerExpr(ai->left, ctx), LowerExpr(ai->right, ctx));
    }
    if (auto se = expr->to<IR::StructExpression>()) {
        auto t = ctx.typeMap->getType(expr, false);
        std::string tname = DslxNameForType(t);
        std::vector<ir::StructInstance::Field> fs;
        for (auto c : se->components) {
            fs.emplace_back(std::string(c->name.toString()),
                             LowerExpr(c->expression, ctx));
        }
        return ir::E_struct(std::move(tname), std::move(fs));
    }
    if (auto le = expr->to<IR::ListExpression>()) {
        std::vector<ExprPtr> v;
        for (auto c : le->components) v.push_back(LowerExpr(c, ctx));
        return ir::E_tuple(std::move(v));
    }

    return ir::E_verbatim("/* unsupported expression */");
}

std::string ExprToTextualName(const IR::Expression* expr, const LowerContext& ctx) {
    // Render the expression then sanitize: '.' -> '_'.
    auto e = LowerExpr(expr, ctx);
    ::dslx_ir::Formatter f;
    e->Format(f);
    std::string s = f.result();
    for (auto& c : s) {
        if (c == '.') c = '_';
    }
    return s;
}

}  // namespace P4::DSLX::adapter
