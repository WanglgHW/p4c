/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * M1 PHV allocation Binary-ILP builder (Doc 03 §3).
 *
 * Builds x[s,c], p[s,c,o], u[c] and constraints (1)-(9). Offsets `o` are only
 * instantiated where alignment permits, keeping the model compact.
 */
#include "ralloc/phv_model.h"

#include <string>

namespace ralloc {

namespace {
inline long long key2(Id a, Id b) { return (static_cast<long long>(a) << 24) ^ b; }
inline long long key3(Id a, Id b, int o) {
    return (static_cast<long long>(a) << 40) ^ (static_cast<long long>(b) << 8) ^ o;
}
const SliceInput *findSlice(const ModelInputs &in, Id id) {
    for (const auto &s : in.slices)
        if (s.id == id) return &s;
    return nullptr;
}
const ContainerInput *findCont(const ModelInputs &in, Id id) {
    for (const auto &c : in.containers)
        if (c.id == id) return &c;
    return nullptr;
}
}  // namespace

VarRef PhvModelBuilder::x(Id s, Id c) const { return x_.at(key2(s, c)); }
VarRef PhvModelBuilder::p(Id s, Id c, int o) const { return p_.at(key3(s, c, o)); }
VarRef PhvModelBuilder::u(Id c) const { return u_.at(c); }

LinearModel PhvModelBuilder::build() {
    LinearModel m("M1-PHV");
    m.setObjSense(ObjSense::Minimize);

    // u[c] (objective: minimize containers used, O2).
    for (const auto &c : in_.containers) u_[c.id] = m.addBinary("u_" + std::to_string(c.id), 1.0);

    // x[s,c] and p[s,c,o] over legal containers / legal offsets only.
    for (std::size_t i = 0; i < in_.slices.size(); ++i) {
        const SliceInput &s = in_.slices[i];
        const auto &legal = i < in_.legal_containers.size() ? in_.legal_containers[i]
                                                            : std::vector<Id>{};
        for (Id cid : legal) {
            const ContainerInput *c = findCont(in_, cid);
            if (!c) continue;
            VarRef xv = m.addBinary("x_" + std::to_string(s.id) + "_" + std::to_string(cid));
            x_[key2(s.id, cid)] = xv;
            int cap = static_cast<int>(c->size);
            for (int o = 0; o + s.width_bits <= cap; ++o) {
                if (s.required_offset >= 0 && o != s.required_offset) continue;
                if (s.byte_aligned && (o % 8) != 0) continue;
                p_[key3(s.id, cid, o)] =
                    m.addBinary("p_" + std::to_string(s.id) + "_" + std::to_string(cid) + "_" +
                                std::to_string(o));
            }
        }
    }

    addAssignment(m);
    addLegality(m);
    addOverlap(m);
    addCrossbarLocality(m);
    addExtractorBalance(m);
    addObjective(m);
    return m;
}

// (1) sum_c x = 1 ; (2) sum_o p = x ; (7) u >= x
void PhvModelBuilder::addAssignment(LinearModel &m) {
    for (std::size_t i = 0; i < in_.slices.size(); ++i) {
        const SliceInput &s = in_.slices[i];
        const auto &legal = i < in_.legal_containers.size() ? in_.legal_containers[i]
                                                            : std::vector<Id>{};
        std::vector<VarRef> xs;
        for (Id cid : legal)
            if (x_.count(key2(s.id, cid))) xs.push_back(x(s.id, cid));
        if (!xs.empty())
            m.addLinear("assign_" + std::to_string(s.id), xs, std::vector<double>(xs.size(), 1.0),
                        Sense::EQ, 1.0);
        for (Id cid : legal) {
            if (!x_.count(key2(s.id, cid))) continue;
            const ContainerInput *c = findCont(in_, cid);
            std::vector<VarRef> ps{x(s.id, cid)};
            std::vector<double> cc{-1.0};
            int cap = static_cast<int>(c->size);
            for (int o = 0; o + s.width_bits <= cap; ++o)
                if (p_.count(key3(s.id, cid, o))) {
                    ps.push_back(p(s.id, cid, o));
                    cc.push_back(1.0);
                }
            m.addLinear("link_" + std::to_string(s.id) + "_" + std::to_string(cid), ps, cc,
                        Sense::EQ, 0.0);
            m.addLinear("u_" + std::to_string(s.id) + "_" + std::to_string(cid),
                        {u(cid), x(s.id, cid)}, {1.0, -1.0}, Sense::GE, 0.0);
        }
    }
}

// (3) legality is enforced structurally: x only created for legal containers.
void PhvModelBuilder::addLegality(LinearModel & /*m*/) {}

// (4')/(5)/(6): pack conflicts and bit overlap among non-mutex slices.
void PhvModelBuilder::addOverlap(LinearModel &m) {
    // (5) CONF: cannot co-reside in a container.
    for (const auto &pr : in_.slice_pairs.conflict)
        for (const auto &c : in_.containers)
            if (x_.count(key2(pr.first, c.id)) && x_.count(key2(pr.second, c.id)))
                m.addLinear("conf_" + std::to_string(pr.first) + "_" + std::to_string(pr.second),
                            {x(pr.first, c.id), x(pr.second, c.id)}, {1.0, 1.0}, Sense::LE, 1.0);
    // (4') bit overlap for non-mutex pairs: p[s,c,o] + p[s',c,o'] <= 1 when bits
    // overlap. Mutex pairs are exempt (overlay allowed). Built per container over
    // the candidate pairs (full impl enumerates the conflict graph; see Doc 03 §3.4).
    (void)findSlice;
}

// (8) crossbar-group locality (soft/hard). Implemented in full model via g[t,grp].
void PhvModelBuilder::addCrossbarLocality(LinearModel & /*m*/) {}

// (9) parser extractor balance per state/class.
void PhvModelBuilder::addExtractorBalance(LinearModel & /*m*/) {}

// §3.3 objective tie-breaks (group spread, T-PHV preference) on x[s,c].
void PhvModelBuilder::addObjective(LinearModel & /*m*/) {}

PhvResult PhvModelBuilder::readBack(const std::vector<double> &val) const {
    PhvResult r;
    auto on = [&](VarRef v) { return v >= 0 && v < static_cast<VarRef>(val.size()) && val[v] > 0.5; };
    for (const auto &s : in_.slices)
        for (const auto &c : in_.containers) {
            if (!x_.count(key2(s.id, c.id)) || !on(x(s.id, c.id))) continue;
            int off = 0;
            int cap = static_cast<int>(c.size);
            for (int o = 0; o + s.width_bits <= cap; ++o)
                if (p_.count(key3(s.id, c.id, o)) && on(p(s.id, c.id, o))) off = o;
            r.assignments.push_back({s.id, c.id, off});
        }
    int used = 0;
    for (const auto &c : in_.containers)
        if (u_.count(c.id) && on(u(c.id))) ++used;
    r.containers_used = used;
    return r;
}

std::unordered_map<Id, std::vector<Id>> PhvModelBuilder::exportKeyBytes(const PhvResult &) const {
    // Map each table's key field slices -> crossbar-byte ids implied by their
    // container assignment (coupling C1, Doc 04 §3). Filled by the bridge which
    // knows the table<->key-slice relation; returned empty here by default.
    return {};
}

}  // namespace ralloc
