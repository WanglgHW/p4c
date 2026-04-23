// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "p4_stmt_lower.h"

#include <string>
#include <utility>
#include <vector>

#include "../dslx_ir/build.h"
#include "../dslx_ir/formatter.h"
#include "binding_helpers.h"
#include "p4_expr_lower.h"
#include "p4_type_lower.h"

namespace P4::DSLX::adapter {

namespace ir = ::dslx_ir;
using ir::ExprPtr;
using ir::StmtPtr;

namespace {

// Replace '.' with '_' for use as a let-binding name.
std::string Sanitize(const std::string& s) {
    std::string out = s;
    for (auto& c : out) {
        if (c == '.') c = '_';
    }
    return out;
}

// Render an Expr to its textual form (used to derive names for let bindings).
std::string ExprText(const ir::Expr& e) {
    ir::Formatter f;
    e.Format(f);
    return f.result();
}

// Build:    let bind_path = TypeName { field: rhs, ..parent_path };
StmtPtr StructUpdateStmt(const std::string& parent_textual,
                          const std::string& type_name,
                          const std::string& field_name,
                          ExprPtr rhs) {
    std::vector<ir::SplatStructInstance::Field> fs;
    fs.emplace_back(field_name, std::move(rhs));
    auto splat = ir::E_verbatim(parent_textual);
    auto rhs_expr = ir::E_struct_splat(type_name, std::move(fs), std::move(splat));
    return ir::S_let_inferred(Sanitize(parent_textual), std::move(rhs_expr));
}

// Build plain struct instance (no splat) for single-field structs.
StmtPtr PlainStructStmt(const std::string& var_name,
                         const std::string& type_name,
                         const std::string& field_name,
                         ExprPtr rhs) {
    std::vector<ir::StructInstance::Field> fs;
    fs.emplace_back(field_name, std::move(rhs));
    auto rhs_expr = ir::E_struct(type_name, std::move(fs));
    return ir::S_let_inferred(Sanitize(var_name), std::move(rhs_expr));
}

// Determine whether a type is a struct with >1 fields (splat ok) or <=1 fields.
bool ShouldUseSplat(const IR::Type* type, P4::TypeMap* typeMap) {
    if (type == nullptr) return true;
    if (auto ts = type->to<IR::Type_Struct>()) {
        return ts->fields.size() > 1;
    }
    if (auto tn = type->to<IR::Type_Name>()) {
        auto decl = typeMap->getTypeType(tn, true);
        if (auto ts = decl->to<IR::Type_Struct>()) {
            return ts->fields.size() > 1;
        }
    }
    return true;
}

// Lower an assignment to one or two struct-update lets.
// LHS shapes handled:
//   container.header.field = rhs    →  two updates (innermost outward)
//   param.field           = rhs     →  one update
//   plain_var             = rhs     →  let plain_var = rhs;
void LowerAssignment(const IR::AssignmentStatement* as,
                     const LowerContext& ctx,
                     std::vector<StmtPtr>* out) {
    auto rhs = LowerExpr(as->right, ctx);

    if (auto mem = as->left->to<IR::Member>()) {
        std::string field = std::string(mem->member.toString());

        if (auto inner = mem->expr->to<IR::Member>()) {
            // container.header.field = rhs
            std::string base_text = ExprText(*LowerExpr(mem->expr, ctx));
            auto t = ctx.typeMap->getType(mem->expr, false);
            std::string tname = DslxNameForType(t);
            out->push_back(StructUpdateStmt(base_text, tname, field, std::move(rhs)));

            // Then update the container with the new bind name.
            std::string container_text = ExprText(*LowerExpr(inner->expr, ctx));
            std::string header_field = std::string(inner->member.toString());
            auto ct = ctx.typeMap->getType(inner->expr, false);
            std::string ctname = DslxNameForType(ct);
            bool use_splat = ShouldUseSplat(ct, ctx.typeMap);
            if (use_splat) {
                out->push_back(StructUpdateStmt(
                    container_text, ctname, header_field,
                    ir::E_name(Sanitize(base_text))));
            } else {
                out->push_back(PlainStructStmt(
                    container_text, ctname, header_field,
                    ir::E_name(Sanitize(base_text))));
            }
            return;
        }

        if (auto pe = mem->expr->to<IR::PathExpression>()) {
            std::string base = std::string(pe->path->name.toString());
            auto it = ctx.param_name_map.find(base);
            std::string dslx_var = (it != ctx.param_name_map.end()) ? it->second : base;
            // Find the type
            std::string tname;
            auto t = ctx.typeMap->getType(mem->expr, false);
            if (ctx.block_info != nullptr) {
                for (const auto& [vn, tn] : ctx.block_info->all_threaded) {
                    if (vn == dslx_var) {
                        tname = tn;
                        break;
                    }
                }
            }
            if (tname.empty()) {
                tname = DslxNameForType(t);
            }
            bool use_splat = ShouldUseSplat(t, ctx.typeMap);
            if (use_splat) {
                out->push_back(StructUpdateStmt(dslx_var, tname, field, std::move(rhs)));
            } else {
                out->push_back(PlainStructStmt(dslx_var, tname, field, std::move(rhs)));
            }
            return;
        }
    }

    // Fallback: simple `let lhs = rhs;`
    auto lhs_expr = LowerExpr(as->left, ctx);
    out->push_back(ir::S_let_inferred(ExprText(*lhs_expr), std::move(rhs)));
}

// Lower setValid/setInvalid as a struct update on _valid + container update.
void LowerSetValidity(const IR::Member* mem, bool make_valid,
                      const LowerContext& ctx, std::vector<StmtPtr>* out) {
    std::string base_text = ExprText(*LowerExpr(mem->expr, ctx));
    auto t = ctx.typeMap->getType(mem->expr, false);
    std::string tname = DslxNameForType(t);
    out->push_back(StructUpdateStmt(base_text, tname, "_valid",
                                     ir::E_bool(make_valid)));

    if (auto inner = mem->expr->to<IR::Member>()) {
        std::string container_text = ExprText(*LowerExpr(inner->expr, ctx));
        std::string header_field = std::string(inner->member.toString());
        auto ct = ctx.typeMap->getType(inner->expr, false);
        std::string ctname = DslxNameForType(ct);
        bool use_splat = ShouldUseSplat(ct, ctx.typeMap);
        if (use_splat) {
            out->push_back(StructUpdateStmt(
                container_text, ctname, header_field,
                ir::E_name(Sanitize(base_text))));
        } else {
            out->push_back(PlainStructStmt(
                container_text, ctname, header_field,
                ir::E_name(Sanitize(base_text))));
        }
    }
}

// Lower a method-call statement (action call, table.apply, setValid, ...).
void LowerMethodCall(const IR::MethodCallStatement* mcs,
                     const LowerContext& ctx,
                     std::vector<StmtPtr>* out,
                     bool enable_table_apply) {
    auto mi = mcs->methodCall;
    if (auto mem = mi->method->to<IR::Member>()) {
        if (mem->member == "apply" && enable_table_apply) {
            std::string tname = ExprText(*LowerExpr(mem->expr, ctx));
            // If the table reference resolves to a P4Table declaration,
            // use the declaration's unique (renamed) name to match the
            // table function emitted by LowerTable.
            if (auto pe = mem->expr->to<IR::PathExpression>()) {
                auto decl = ctx.refMap->getDeclaration(pe->path, true);
                if (decl != nullptr) {
                    tname = std::string(decl->getName().toString());
                }
            }
            std::vector<ExprPtr> args;
            for (const auto& [vn, _t] : ctx.block_info->all_threaded) {
                args.push_back(ir::E_name(vn));
            }
            args.push_back(ir::E_name(tname + "_entries"));
            std::string hit_pat;
            if (ctx.block_info->all_threaded.size() == 1) {
                hit_pat = "(_, " + ctx.block_info->all_threaded[0].first + ")";
            } else {
                hit_pat = "(_, " + BindingPattern(*ctx.block_info) + ")";
            }
            out->push_back(ir::S_let_inferred(
                hit_pat,
                ir::E_call_named("table_" + tname + "_apply", std::move(args))));
            return;
        }
        if (mem->member == "setValid") {
            LowerSetValidity(mem, /*make_valid=*/true, ctx, out);
            return;
        }
        if (mem->member == "setInvalid") {
            LowerSetValidity(mem, /*make_valid=*/false, ctx, out);
            return;
        }
        if (mem->member == "mark_to_drop") {
            out->push_back(ir::S_comment(
                "TODO: mark_to_drop -> set drop_ctl in deparser intrinsic md"));
            return;
        }
    }

    // Direct action call: action(args...)
    if (auto pe = mi->method->to<IR::PathExpression>()) {
        std::string action_name = std::string(pe->path->name.toString());
        // The midend may have renamed the action (e.g. gtpu_decap ->
        // spgw_ingress_gtpu_decap). Resolve via refMap to match the definition.
        auto decl = ctx.refMap->getDeclaration(pe->path, true);
        if (decl != nullptr) {
            action_name = std::string(decl->getName().toString());
        }

        // Handle mark_to_drop extern: update egress_spec to drop port.
        if (action_name == "mark_to_drop") {
            std::string sm_name = "std_meta";
            std::string sm_type_name = "Standard_metadata_t";
            if (!mi->arguments->empty()) {
                if (auto arg_pe = (*mi->arguments)[0]->expression->to<IR::PathExpression>()) {
                    sm_name = std::string(arg_pe->path->name.toString());
                }
                auto sm_type = ctx.typeMap->getType((*mi->arguments)[0]->expression, false);
                if (auto ts = sm_type->to<IR::Type_Struct>()) {
                    sm_type_name = DslxNameForStruct(ts);
                } else if (auto tn = sm_type->to<IR::Type_Name>()) {
                    sm_type_name = std::string(tn->path->name.toString());
                    if (!sm_type_name.empty()) {
                        sm_type_name[0] = static_cast<char>(std::toupper(
                            static_cast<unsigned char>(sm_type_name[0])));
                    }
                }
            }
            std::vector<ir::SplatStructInstance::Field> fields;
            fields.push_back({"egress_spec", ir::E_uN(9, "0x1FF")});
            out->push_back(ir::S_let_inferred(
                sm_name,
                ir::E_struct_splat(sm_type_name, std::move(fields),
                                   ir::E_name(sm_name))));
            return;
        }

        std::vector<ExprPtr> args;
        if (ctx.block_info != nullptr) {
            for (const auto& [vn, _t] : ctx.block_info->all_threaded) {
                args.push_back(ir::E_name(vn));
            }
        }
        for (auto a : *mi->arguments) {
            args.push_back(LowerExpr(a->expression, ctx));
        }
        out->push_back(ir::S_let_inferred(
            BindingPattern(*ctx.block_info),
            ir::E_call_named(action_name, std::move(args))));
        return;
    }

    // Anything else: emit as comment to keep emit valid.
    auto call = LowerExpr(mi, ctx);
    out->push_back(ir::S_comment("TODO: " + ExprText(*call)));
}

// Build a Block whose body is `lowered stmts; tail = bindingExpr`.
std::unique_ptr<ir::Block> LowerBlockStatements(
    const IR::Vector<IR::StatOrDecl>& comps,
    const LowerContext& ctx, bool enable_table_apply) {
    std::vector<StmtPtr> stmts;
    for (auto s : comps) {
        LowerStmt(s, ctx, &stmts, enable_table_apply);
    }
    return ir::B_make(std::move(stmts), BindingExpr(*ctx.block_info));
}

}  // namespace

void LowerStmt(const IR::StatOrDecl* stmt, const LowerContext& ctx,
               std::vector<StmtPtr>* out, bool enable_table_apply) {
    if (auto mcs = stmt->to<IR::MethodCallStatement>()) {
        LowerMethodCall(mcs, ctx, out, enable_table_apply);
        return;
    }
    if (auto as = stmt->to<IR::AssignmentStatement>()) {
        LowerAssignment(as, ctx, out);
        return;
    }
    if (auto ifs = stmt->to<IR::IfStatement>()) {
        // Detect table.apply().hit / .miss in the condition and hoist the
        // table call so bindings are updated before the branch bodies run.
        auto cond_expr_raw = ifs->condition;
        bool cond_negated = false;
        if (auto un = cond_expr_raw->to<IR::Operation_Unary>()) {
            if (un->is<IR::LNot>()) {
                cond_negated = true;
                cond_expr_raw = un->expr;
            }
        }
        const IR::Member* hit_member = nullptr;
        if (auto mem = cond_expr_raw->to<IR::Member>()) {
            if (mem->member == "hit" || mem->member == "miss") {
                hit_member = mem;
            }
        }
        if (hit_member != nullptr) {
            if (auto mc = hit_member->expr->to<IR::MethodCallExpression>()) {
                if (auto mem = mc->method->to<IR::Member>()) {
                    if (mem->member == "apply") {
                        std::string tname = ExprText(*LowerExpr(mem->expr, ctx));
                        if (auto pe = mem->expr->to<IR::PathExpression>()) {
                            auto decl = ctx.refMap->getDeclaration(pe->path, true);
                            if (decl != nullptr) {
                                tname = std::string(decl->getName().toString());
                            }
                        }
                        std::vector<ExprPtr> args;
                        for (const auto& [vn, _t] : ctx.block_info->all_threaded) {
                            args.push_back(ir::E_name(vn));
                        }
                        args.push_back(ir::E_name(tname + "_entries"));
                        std::string hit_pat;
                        if (ctx.block_info->all_threaded.size() == 1) {
                            hit_pat = "(__hit, " + ctx.block_info->all_threaded[0].first + ")";
                        } else {
                            hit_pat = "(__hit, " + BindingPattern(*ctx.block_info) + ")";
                        }
                        out->push_back(ir::S_let_inferred(
                            hit_pat,
                            ir::E_call_named("table_" + tname + "_apply",
                                             std::move(args))));

                        ExprPtr new_cond = ir::E_name("__hit");
                        if (cond_negated) {
                            new_cond = ir::E_unop(ir::UnopKind::kNot, std::move(new_cond));
                        }
                        if (hit_member->member == "miss") {
                            new_cond = ir::E_unop(ir::UnopKind::kNot, std::move(new_cond));
                        }

                        auto block_for = [&](const IR::Statement* body) {
                            if (body == nullptr) {
                                return ir::B_make({}, BindingExpr(*ctx.block_info));
                            }
                            if (auto bs = body->to<IR::BlockStatement>()) {
                                return LowerBlockStatements(bs->components, ctx,
                                                            enable_table_apply);
                            }
                            std::vector<StmtPtr> ss;
                            LowerStmt(body, ctx, &ss, enable_table_apply);
                            return ir::B_make(std::move(ss), BindingExpr(*ctx.block_info));
                        };
                        auto then_block = block_for(ifs->ifTrue);
                        auto else_block = block_for(ifs->ifFalse);
                        auto cond_expr = ir::E_cond(std::move(new_cond),
                                                     std::move(then_block),
                                                     std::move(else_block));
                        out->push_back(ir::S_let_inferred(
                            BindingPattern(*ctx.block_info), std::move(cond_expr)));
                        return;
                    }
                }
            }
        }

        // Normal if lowering (no table apply in condition).
        auto cond = LowerExpr(ifs->condition, ctx);
        std::unique_ptr<ir::Block> then_block;
        std::unique_ptr<ir::Block> else_block;

        auto block_for = [&](const IR::Statement* body) {
            if (body == nullptr) {
                return ir::B_make({}, BindingExpr(*ctx.block_info));
            }
            if (auto bs = body->to<IR::BlockStatement>()) {
                return LowerBlockStatements(bs->components, ctx, enable_table_apply);
            }
            std::vector<StmtPtr> ss;
            LowerStmt(body, ctx, &ss, enable_table_apply);
            return ir::B_make(std::move(ss), BindingExpr(*ctx.block_info));
        };
        then_block = block_for(ifs->ifTrue);
        else_block = block_for(ifs->ifFalse);

        // `let bind = if cond { ... } else { ... };`
        auto cond_expr = ir::E_cond(std::move(cond),
                                     std::move(then_block),
                                     std::move(else_block));
        out->push_back(ir::S_let_inferred(BindingPattern(*ctx.block_info),
                                            std::move(cond_expr)));
        return;
    }
    if (auto bs = stmt->to<IR::BlockStatement>()) {
        for (auto s : bs->components) {
            LowerStmt(s, ctx, out, enable_table_apply);
        }
        return;
    }
    if (auto dv = stmt->to<IR::Declaration_Variable>()) {
        auto vt = ctx.typeMap->getType(dv, false);
        ExprPtr init = dv->initializer ? LowerExpr(dv->initializer, ctx)
                                        : DefaultValueOf(vt, ctx.typeMap);
        out->push_back(ir::S_let(std::string(dv->name.toString()),
                                   LowerType(vt, ctx.typeMap), std::move(init)));
        return;
    }
    if (auto sw = stmt->to<IR::SwitchStatement>()) {
        // No DSLX match emitted yet — keep as comments to preserve intent.
        auto sel = LowerExpr(sw->expression, ctx);
        out->push_back(ir::S_comment("switch: " + ExprText(*sel)));
        for (auto sc : sw->cases) {
            if (sc->label->is<IR::DefaultExpression>()) {
                out->push_back(ir::S_comment("default case"));
            } else {
                out->push_back(ir::S_comment(
                    "case " + ExprText(*LowerExpr(sc->label, ctx)) + ":"));
            }
            if (sc->statement != nullptr) {
                LowerStmt(sc->statement, ctx, out, enable_table_apply);
            }
        }
        return;
    }
}

}  // namespace P4::DSLX::adapter
