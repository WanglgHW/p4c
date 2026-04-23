// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "p4_to_dslx.h"

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "../dslx_ir/build.h"
#include "intrinsic_metadata.h"
#include "lib/cstring.h"
#include "p4_control_lower.h"
#include "p4_deparser_lower.h"
#include "p4_parser_lower.h"
#include "p4_type_lower.h"

namespace P4::DSLX::adapter {

namespace ir = ::dslx_ir;

namespace {

// ---------------------------------------------------------------------------
// Block analysis: derive PipelineBlockInfo from a parser/control IContainer.

PipelineBlockInfo AnalyzeBlock(const IR::IContainer* container,
                                P4::TypeMap* typeMap,
                                std::set<std::string>* intrinsic_seen) {
    PipelineBlockInfo info;
    if (container == nullptr) return info;
    info.block = container;
    info.name = std::string(container->getName().toString());

    const IR::ParameterList* params = nullptr;
    if (auto p = container->to<IR::P4Parser>()) params = p->getApplyParameters();
    else if (auto c = container->to<IR::P4Control>()) params = c->getApplyParameters();
    if (params == nullptr) return info;

    bool headers_found = false;
    bool meta_found = false;
    for (auto param : params->parameters) {
        auto type = typeMap->getType(param, false);
        if (type == nullptr) continue;
        if (type->is<IR::Type_Extern>()) continue;
        if (auto tn = type->to<IR::Type_Name>()) {
            std::string n = std::string(tn->path->name.toString());
            if (n == "packet_in" || n == "packet_out") continue;
        }

        std::string raw_type;
        std::string dslx_type;
        if (auto ts = type->to<IR::Type_Struct>()) {
            raw_type = std::string(ts->name.toString());
            dslx_type = DslxNameForStruct(ts);
        } else if (auto th = type->to<IR::Type_Header>()) {
            raw_type = std::string(th->name.toString());
            dslx_type = DslxNameForHeader(th);
        } else {
            dslx_type = "/* unknown */";
            raw_type = dslx_type;
        }

        std::string pname = std::string(param->name.toString());

        if (IsIntrinsicMetadataType(raw_type)) {
            info.intrinsic_params.emplace_back(pname, dslx_type);
            info.all_threaded.emplace_back(pname, dslx_type);
            if (intrinsic_seen != nullptr) intrinsic_seen->insert(raw_type);
        } else if (!headers_found &&
                   (param->direction == IR::Direction::Out ||
                    param->direction == IR::Direction::InOut)) {
            info.headers_type_name = dslx_type;
            info.all_threaded.emplace_back(pname, dslx_type);
            headers_found = true;
        } else if (!meta_found &&
                   (param->direction == IR::Direction::Out ||
                    param->direction == IR::Direction::InOut ||
                    param->direction == IR::Direction::In)) {
            info.meta_type_name = dslx_type;
            info.all_threaded.emplace_back(pname, dslx_type);
            meta_found = true;
        } else {
            info.all_threaded.emplace_back(pname, dslx_type);
        }
    }
    if (info.headers_type_name.empty()) info.headers_type_name = "Headers";
    if (info.meta_type_name.empty()) info.meta_type_name = "Metadata";
    return info;
}

// ---------------------------------------------------------------------------
// Type emission: structs and intrinsic metadata structs.

void EmitTypes(const IR::P4Program* program, P4::TypeMap* typeMap,
               const std::set<std::string>& intrinsic_seen,
               ir::Module* module) {
    module->AddDecl(std::make_unique<ir::CommentDecl>(
        "===== Type Definitions ====="));
    module->AddDecl(std::make_unique<ir::BlankLineDecl>());

    auto resolve_field_type = [&](const IR::StructField* f) -> const IR::Type* {
        auto t = typeMap->getType(f, false);
        if (t != nullptr) return t;
        return typeMap->getType(f->type, false);
    };

    auto emit_struct_like = [&](const std::string& dslx_name,
                                  const IR::IndexedVector<IR::StructField>& fields,
                                  bool include_valid) {
        std::vector<ir::StructDef::Field> ir_fields;
        for (auto field : fields) {
            auto ft = resolve_field_type(field);
            ir_fields.emplace_back(std::string(field->name.toString()),
                                    LowerType(ft, typeMap));
        }
        if (include_valid) {
            ir_fields.emplace_back("_valid", ir::T_bool());
        }
        module->AddDecl(std::make_unique<ir::StructDef>(dslx_name,
                                                         std::move(ir_fields)));
    };

    // Header types (skip intrinsic).
    for (auto decl : program->objects) {
        auto ht = decl->to<IR::Type_Header>();
        if (ht == nullptr) continue;
        std::string n = std::string(ht->name.toString());
        if (IsIntrinsicMetadataType(n)) continue;
        emit_struct_like(DslxNameForHeader(ht), ht->fields, /*include_valid=*/true);
    }

    // Struct types (skip intrinsic).
    for (auto decl : program->objects) {
        auto st = decl->to<IR::Type_Struct>();
        if (st == nullptr) continue;
        std::string n = std::string(st->name.toString());
        if (IsIntrinsicMetadataType(n)) continue;
        emit_struct_like(DslxNameForStruct(st), st->fields, /*include_valid=*/false);
    }

    if (intrinsic_seen.empty()) return;

    module->AddDecl(std::make_unique<ir::CommentDecl>(
        "===== TNA Intrinsic Metadata ====="));
    module->AddDecl(std::make_unique<ir::BlankLineDecl>());

    for (auto decl : program->objects) {
        const IR::Type_Struct* st = decl->to<IR::Type_Struct>();
        const IR::Type_Header* ht = decl->to<IR::Type_Header>();
        std::string raw;
        if (st != nullptr) raw = std::string(st->name.toString());
        else if (ht != nullptr) raw = std::string(ht->name.toString());
        else continue;
        if (intrinsic_seen.count(raw) == 0) continue;

        std::string dslx = ToCamelCase(raw);
        const auto& fields = (st != nullptr) ? st->fields : ht->fields;
        emit_struct_like(dslx, fields, /*include_valid=*/false);
    }
}

// ---------------------------------------------------------------------------
// Per-gress lowering: parser + control + deparser.

LowerContext MakeContext(const IR::P4Program* program, P4::ReferenceMap* refMap,
                         P4::TypeMap* typeMap, const PipelineBlockInfo* block,
                         const LowerOptions& opts) {
    LowerContext ctx;
    ctx.program = program;
    ctx.refMap = refMap;
    ctx.typeMap = typeMap;
    ctx.block_info = block;
    for (const auto& [n, _t] : block->all_threaded) {
        ctx.param_name_map[n] = n;
    }
    ctx.max_packet_bits = opts.max_packet_bits;
    ctx.max_table_entries = opts.max_table_entries;
    return ctx;
}

void LowerGress(const GressPipeline& gress, const std::string& gress_name,
                const IR::P4Program* program, P4::ReferenceMap* refMap,
                P4::TypeMap* typeMap, const LowerOptions& opts,
                std::set<std::string>* emitted_actions, ir::Module* module) {
    module->AddDecl(std::make_unique<ir::CommentDecl>(
        "===== " + gress_name + " Pipeline ====="));
    module->AddDecl(std::make_unique<ir::BlankLineDecl>());

    if (gress.parser.block != nullptr) {
        if (auto parser = gress.parser.block->to<IR::P4Parser>()) {
            auto ctx = MakeContext(program, refMap, typeMap, &gress.parser, opts);
            LowerParser(parser, ctx, gress_name, module);
        }
    }
    if (gress.control.block != nullptr) {
        if (auto control = gress.control.block->to<IR::P4Control>()) {
            auto ctx = MakeContext(program, refMap, typeMap, &gress.control, opts);
            LowerControl(control, ctx, gress_name, emitted_actions, module);
        }
    }
    if (gress.deparser.block != nullptr) {
        if (auto deparser = gress.deparser.block->to<IR::P4Control>()) {
            auto ctx = MakeContext(program, refMap, typeMap, &gress.deparser, opts);
            LowerDeparser(deparser, ctx, gress_name, module);
        }
    }
}

// ---------------------------------------------------------------------------
// Top-level pipeline function.

void EmitTopPipeline(const GressPipeline& ingress, const GressPipeline& egress,
                     ir::Module* module) {
    module->AddDecl(std::make_unique<ir::CommentDecl>(
        "===== Top-level Pipeline ====="));
    module->AddDecl(std::make_unique<ir::BlankLineDecl>());

    std::vector<ir::Param> params;
    params.emplace_back("packet", ir::T_bits(ir::E_name("MAX_PACKET_BITS")));
    for (const auto& [vn, tn] : ingress.parser.intrinsic_params) {
        params.emplace_back(vn, ir::T_ref(tn));
    }

    auto add_table_params = [&](const GressPipeline& g) {
        if (g.control.block == nullptr) return;
        auto ctrl = g.control.block->to<IR::P4Control>();
        if (ctrl == nullptr) return;
        for (auto decl : ctrl->controlLocals) {
            if (auto tbl = decl->to<IR::P4Table>()) {
                std::string tn = std::string(tbl->name.toString());
                params.emplace_back(
                    tn + "_entries",
                    ir::T_array(ir::T_ref(tn + "_entry_t"),
                                 ir::E_name("MAX_TABLE_ENTRIES")));
            }
        }
    };
    add_table_params(ingress);
    add_table_params(egress);

    std::vector<ir::TypePtr> ret_ts;
    ret_ts.push_back(ir::T_bits(ir::E_name("MAX_PACKET_BITS")));
    auto ret_type = ir::T_tuple(std::move(ret_ts));

    std::vector<ir::StmtPtr> body;

    // Step 1: Ingress parse — call returns (binding..., offset).
    if (ingress.parser.block != nullptr) {
        body.push_back(ir::S_comment("Step 1: Ingress parse"));
        std::vector<ir::ExprPtr> args;
        args.push_back(ir::E_name("packet"));
        for (const auto& [vn, _t] : ingress.parser.intrinsic_params) {
            args.push_back(ir::E_name(vn));
        }
        std::string pat;
        if (ingress.parser.all_threaded.size() == 1) {
            pat = "(" + ingress.parser.all_threaded[0].first +
                  ", _ig_parse_offset)";
        } else {
            pat = "(";
            for (size_t i = 0; i < ingress.parser.all_threaded.size(); ++i) {
                if (i != 0) pat += ", ";
                pat += ingress.parser.all_threaded[i].first;
            }
            pat += ", _ig_parse_offset)";
        }
        body.push_back(ir::S_let_inferred(
            pat,
            ir::E_call_named("ingress_parser_apply", std::move(args))));
    }

    // Step 2: Ingress control.
    if (ingress.control.block != nullptr) {
        auto ctrl = ingress.control.block->to<IR::P4Control>();
        body.push_back(ir::S_comment("Step 2: Ingress processing"));
        std::vector<ir::ExprPtr> args;
        for (const auto& [vn, _t] : ingress.control.all_threaded) {
            args.push_back(ir::E_name(vn));
        }
        if (ctrl != nullptr) {
            for (auto decl : ctrl->controlLocals) {
                if (auto tbl = decl->to<IR::P4Table>()) {
                    args.push_back(ir::E_name(
                        std::string(tbl->name.toString()) + "_entries"));
                }
            }
        }
        std::string pat;
        if (ingress.control.all_threaded.size() == 1) {
            pat = ingress.control.all_threaded[0].first;
        } else {
            pat = "(";
            for (size_t i = 0; i < ingress.control.all_threaded.size(); ++i) {
                if (i != 0) pat += ", ";
                pat += ingress.control.all_threaded[i].first;
            }
            pat += ")";
        }
        body.push_back(ir::S_let_inferred(
            pat,
            ir::E_call_named("ingress_" + ingress.control.name + "_apply",
                              std::move(args))));
    }

    // Step 3: Egress parse.
    if (egress.parser.block != nullptr) {
        body.push_back(ir::S_comment("Step 3: Egress parse"));
        std::vector<ir::ExprPtr> args;
        args.push_back(ir::E_name("packet"));
        for (const auto& [vn, _t] : egress.parser.intrinsic_params) {
            args.push_back(ir::E_name(vn));
        }
        std::string pat;
        if (egress.parser.all_threaded.size() == 1) {
            pat = "(" + egress.parser.all_threaded[0].first +
                  ", _eg_parse_offset)";
        } else {
            pat = "(";
            for (size_t i = 0; i < egress.parser.all_threaded.size(); ++i) {
                if (i != 0) pat += ", ";
                pat += egress.parser.all_threaded[i].first;
            }
            pat += ", _eg_parse_offset)";
        }
        body.push_back(ir::S_let_inferred(
            pat, ir::E_call_named("egress_parser_apply", std::move(args))));
    }

    // Step 4: Egress control.
    if (egress.control.block != nullptr) {
        auto ctrl = egress.control.block->to<IR::P4Control>();
        body.push_back(ir::S_comment("Step 4: Egress processing"));
        std::vector<ir::ExprPtr> args;
        for (const auto& [vn, _t] : egress.control.all_threaded) {
            args.push_back(ir::E_name(vn));
        }
        if (ctrl != nullptr) {
            for (auto decl : ctrl->controlLocals) {
                if (auto tbl = decl->to<IR::P4Table>()) {
                    args.push_back(ir::E_name(
                        std::string(tbl->name.toString()) + "_entries"));
                }
            }
        }
        std::string pat;
        if (egress.control.all_threaded.size() == 1) {
            pat = egress.control.all_threaded[0].first;
        } else {
            pat = "(";
            for (size_t i = 0; i < egress.control.all_threaded.size(); ++i) {
                if (i != 0) pat += ", ";
                pat += egress.control.all_threaded[i].first;
            }
            pat += ")";
        }
        body.push_back(ir::S_let_inferred(
            pat,
            ir::E_call_named("egress_" + egress.control.name + "_apply",
                              std::move(args))));
    }

    // Step 5: Ingress deparse.
    ir::ExprPtr tail = ir::E_name("output_packet");
    if (ingress.deparser.block != nullptr) {
        body.push_back(ir::S_comment("Step 5: Ingress deparse"));
        std::string headers_var = "headers";
        if (!ingress.control.all_threaded.empty()) {
            headers_var = ingress.control.all_threaded[0].first;
        } else if (!ingress.parser.all_threaded.empty()) {
            headers_var = ingress.parser.all_threaded[0].first;
        }
        std::vector<ir::ExprPtr> args;
        args.push_back(ir::E_name(headers_var));
        body.push_back(ir::S_let_inferred(
            "output_packet",
            ir::E_call_named("ingress_deparser_apply", std::move(args))));
    } else {
        // No deparser: pipeline output is unchanged input packet.
        body.push_back(ir::S_let_inferred("output_packet", ir::E_name("packet")));
    }

    // Wrap result as a single-element tuple to match the return type.
    std::vector<ir::ExprPtr> ret_v;
    ret_v.push_back(std::move(tail));
    auto ret_expr = ir::E_tuple(std::move(ret_v));
    auto body_block = ir::B_make(std::move(body), std::move(ret_expr));

    module->AddDecl(std::make_unique<ir::Function>(
        "pipeline", std::move(params), std::move(ret_type),
        std::move(body_block), /*is_pub=*/true));
}

// ---------------------------------------------------------------------------
// Pipeline package -> GressPipeline pair.

const IR::IContainer* GetBlock(const IR::PackageBlock* pkg, const char* name) {
    auto node = pkg->findParameterValue(cstring(name));
    if (node == nullptr) return nullptr;
    if (auto cb = node->to<IR::ControlBlock>()) return cb->container;
    if (auto pb = node->to<IR::ParserBlock>()) return pb->container;
    return nullptr;
}

}  // namespace

std::unique_ptr<ir::Module> LowerPipelineToModule(
    const IR::P4Program* program, P4::ReferenceMap* refMap,
    P4::TypeMap* typeMap, const IR::PackageBlock* pipeline_block,
    const LowerOptions& opts) {
    if (program == nullptr || pipeline_block == nullptr) return nullptr;

    std::set<std::string> intrinsic_seen;
    GressPipeline ingress;
    GressPipeline egress;

    // Try TNA parameter names first, then v1model names.
    auto try_blocks = [&](const char* tna_name, const char* v1_name) -> const IR::IContainer* {
        auto b = GetBlock(pipeline_block, tna_name);
        if (b != nullptr) return b;
        if (v1_name != nullptr) return GetBlock(pipeline_block, v1_name);
        return nullptr;
    };

    ingress.parser   = AnalyzeBlock(try_blocks("ingress_parser", "p"),
                                     typeMap, &intrinsic_seen);
    ingress.control  = AnalyzeBlock(try_blocks("ingress", "ig"),
                                     typeMap, &intrinsic_seen);
    ingress.deparser = AnalyzeBlock(try_blocks("ingress_deparser", "dep"),
                                     typeMap, &intrinsic_seen);
    egress.parser    = AnalyzeBlock(try_blocks("egress_parser", ""),
                                     typeMap, &intrinsic_seen);
    egress.control   = AnalyzeBlock(try_blocks("egress", "eg"),
                                     typeMap, &intrinsic_seen);
    egress.deparser  = AnalyzeBlock(try_blocks("egress_deparser", ""),
                                     typeMap, &intrinsic_seen);

    if (ingress.parser.block == nullptr && ingress.control.block == nullptr) {
        return nullptr;
    }

    auto module = std::make_unique<ir::Module>("pipe");

    // Preamble.
    module->AddDecl(std::make_unique<ir::CommentDecl>(
        "Auto-generated DSLX from P4 TNA program"));
    module->AddDecl(std::make_unique<ir::CommentDecl>(
        "Generated by p4c-barefoot DSLX translator"));
    module->AddDecl(std::make_unique<ir::BlankLineDecl>());
    module->AddDecl(std::make_unique<ir::ConstDecl>(
        "MAX_PACKET_BITS", ir::T_u(32),
        ir::E_uN(32, std::to_string(opts.max_packet_bits))));
    module->AddDecl(std::make_unique<ir::ConstDecl>(
        "MAX_TABLE_ENTRIES", ir::T_u(32),
        ir::E_uN(32, std::to_string(opts.max_table_entries))));
    module->AddDecl(std::make_unique<ir::BlankLineDecl>());

    // Type defs.
    EmitTypes(program, typeMap, intrinsic_seen, module.get());

    // Per-gress lowerings.
    std::set<std::string> emitted_actions;
    LowerGress(ingress, "ingress", program, refMap, typeMap, opts,
               &emitted_actions, module.get());
    LowerGress(egress, "egress", program, refMap, typeMap, opts,
               &emitted_actions, module.get());

    // Top-level orchestrator.
    EmitTopPipeline(ingress, egress, module.get());
    return module;
}

}  // namespace P4::DSLX::adapter
