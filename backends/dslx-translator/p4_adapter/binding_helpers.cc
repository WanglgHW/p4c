// Copyright 2026 The Tofino DSLX Translator Authors
// SPDX-License-Identifier: Apache-2.0

#include "binding_helpers.h"

#include "../dslx_ir/build.h"

namespace P4::DSLX::adapter {

namespace ir = ::dslx_ir;

std::string BindingPattern(const PipelineBlockInfo& info) {
    if (info.all_threaded.size() == 1) return info.all_threaded[0].first;
    std::string s = "(";
    for (size_t i = 0; i < info.all_threaded.size(); ++i) {
        if (i != 0) s += ", ";
        s += info.all_threaded[i].first;
    }
    s += ")";
    return s;
}

ir::ExprPtr BindingExpr(const PipelineBlockInfo& info) {
    if (info.all_threaded.size() == 1) {
        return ir::E_name(info.all_threaded[0].first);
    }
    std::vector<ir::ExprPtr> v;
    for (const auto& [n, _t] : info.all_threaded) {
        v.push_back(ir::E_name(n));
    }
    return ir::E_tuple(std::move(v));
}

ir::TypePtr BindingReturnType(const PipelineBlockInfo& info) {
    if (info.all_threaded.size() == 1) {
        return ir::T_ref(info.all_threaded[0].second);
    }
    std::vector<ir::TypePtr> ts;
    for (const auto& [_n, t] : info.all_threaded) {
        ts.push_back(ir::T_ref(t));
    }
    return ir::T_tuple(std::move(ts));
}

std::vector<ir::Param> BindingParams(const PipelineBlockInfo& info) {
    std::vector<ir::Param> ps;
    for (const auto& [n, t] : info.all_threaded) {
        ps.emplace_back(n, ir::T_ref(t));
    }
    return ps;
}

}  // namespace P4::DSLX::adapter
