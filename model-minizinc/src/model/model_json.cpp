/**
 * Copyright (C) 2026
 * SPDX-License-Identifier: Apache-2.0
 *
 * JSON serialization for the model seam PODs (model_json.h). Self contained:
 * a minimal JSON DOM + recursive-descent parser live here so the model core
 * keeps zero external/bf-p4c dependencies.
 */
#include "ralloc/model_json.h"

#include <cctype>
#include <cstdint>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace ralloc {
namespace {

// ===========================================================================
// Minimal JSON DOM
// ===========================================================================
struct JVal;
using JArr = std::vector<JVal>;
using JObj = std::map<std::string, JVal>;

struct JVal {
    enum class T { Null, Bool, Num, Str, Arr, Obj } t = T::Null;
    bool b = false;
    double num = 0;
    std::string str;
    std::shared_ptr<JArr> arr;
    std::shared_ptr<JObj> obj;

    static JVal mkArr() {
        JVal v;
        v.t = T::Arr;
        v.arr = std::make_shared<JArr>();
        return v;
    }
    static JVal mkObj() {
        JVal v;
        v.t = T::Obj;
        v.obj = std::make_shared<JObj>();
        return v;
    }
    static JVal mkNum(double d) {
        JVal v;
        v.t = T::Num;
        v.num = d;
        return v;
    }
    static JVal mkBool(bool x) {
        JVal v;
        v.t = T::Bool;
        v.b = x;
        return v;
    }

    // typed accessors (throw on type mismatch / missing key)
    const JVal &at(const std::string &k) const {
        if (t != T::Obj) throw std::runtime_error("ralloc json: expected object for key '" + k + "'");
        auto it = obj->find(k);
        if (it == obj->end()) throw std::runtime_error("ralloc json: missing key '" + k + "'");
        return it->second;
    }
    const JArr &asArr() const {
        if (t != T::Arr) throw std::runtime_error("ralloc json: expected array");
        return *arr;
    }
    long asInt() const {
        if (t != T::Num) throw std::runtime_error("ralloc json: expected number");
        return static_cast<long>(num);
    }
    bool asBool() const {
        if (t == T::Bool) return b;
        if (t == T::Num) return num != 0;
        throw std::runtime_error("ralloc json: expected bool");
    }
    double asDouble() const {
        if (t != T::Num) throw std::runtime_error("ralloc json: expected number");
        return num;
    }
};

// ---- emitter --------------------------------------------------------------
void emitStr(std::ostream &os, const std::string &s) {
    os << '"';
    for (char c : s) {
        switch (c) {
            case '"': os << "\\\""; break;
            case '\\': os << "\\\\"; break;
            case '\n': os << "\\n"; break;
            case '\r': os << "\\r"; break;
            case '\t': os << "\\t"; break;
            default:
                if (static_cast<unsigned char>(c) < 0x20) {
                    static const char *hex = "0123456789abcdef";
                    os << "\\u00" << hex[(c >> 4) & 0xf] << hex[c & 0xf];
                } else {
                    os << c;
                }
        }
    }
    os << '"';
}

// Pretty-printer. Objects (and arrays that contain objects/arrays) are expanded
// one entry per line with 2-space indentation; arrays of scalars stay inline
// (e.g. demand vectors / id lists) so the files are readable without becoming
// thousands of lines long. The parser ignores whitespace, so this round-trips.
inline void indent(std::ostream &os, int depth) {
    for (int i = 0; i < depth; ++i) os << "  ";
}

inline bool allScalar(const JArr &a) {
    for (const auto &e : a)
        if (e.t == JVal::T::Arr || e.t == JVal::T::Obj) return false;
    return true;
}

void emit(std::ostream &os, const JVal &v, int depth = 0) {
    switch (v.t) {
        case JVal::T::Null: os << "null"; break;
        case JVal::T::Bool: os << (v.b ? "true" : "false"); break;
        case JVal::T::Num: {
            // Integers print without a fractional part; doubles keep precision.
            double r = v.num;
            if (r == static_cast<double>(static_cast<long long>(r))) {
                os << static_cast<long long>(r);
            } else {
                std::ostringstream tmp;
                tmp.precision(17);
                tmp << r;
                os << tmp.str();
            }
            break;
        }
        case JVal::T::Str: emitStr(os, v.str); break;
        case JVal::T::Arr: {
            const JArr &a = *v.arr;
            if (a.empty()) {
                os << "[]";
            } else if (allScalar(a)) {
                os << '[';
                bool first = true;
                for (const auto &e : a) {
                    if (!first) os << ", ";
                    first = false;
                    emit(os, e, depth);
                }
                os << ']';
            } else {
                os << "[\n";
                bool first = true;
                for (const auto &e : a) {
                    if (!first) os << ",\n";
                    first = false;
                    indent(os, depth + 1);
                    emit(os, e, depth + 1);
                }
                os << '\n';
                indent(os, depth);
                os << ']';
            }
            break;
        }
        case JVal::T::Obj: {
            const JObj &o = *v.obj;
            if (o.empty()) {
                os << "{}";
            } else {
                os << "{\n";
                bool first = true;
                for (const auto &kv : o) {
                    if (!first) os << ",\n";
                    first = false;
                    indent(os, depth + 1);
                    emitStr(os, kv.first);
                    os << ": ";
                    emit(os, kv.second, depth + 1);
                }
                os << '\n';
                indent(os, depth);
                os << '}';
            }
            break;
        }
    }
}

// ---- parser ---------------------------------------------------------------
class Parser {
 public:
    explicit Parser(const std::string &s) : s_(s) {}

    JVal parse() {
        JVal v = parseValue();
        skipWs();
        if (i_ != s_.size()) fail("trailing content");
        return v;
    }

 private:
    const std::string &s_;
    size_t i_ = 0;

    [[noreturn]] void fail(const std::string &msg) const {
        throw std::runtime_error("ralloc json parse error at " + std::to_string(i_) + ": " + msg);
    }
    void skipWs() {
        while (i_ < s_.size() && std::isspace(static_cast<unsigned char>(s_[i_]))) ++i_;
    }
    char peek() {
        skipWs();
        if (i_ >= s_.size()) fail("unexpected end");
        return s_[i_];
    }

    JVal parseValue() {
        char c = peek();
        switch (c) {
            case '{': return parseObj();
            case '[': return parseArr();
            case '"': {
                JVal v;
                v.t = JVal::T::Str;
                v.str = parseStr();
                return v;
            }
            case 't': case 'f': return parseBool();
            case 'n': expect("null"); return JVal{};
            default: return parseNum();
        }
    }
    void expect(const char *lit) {
        skipWs();
        for (const char *p = lit; *p; ++p) {
            if (i_ >= s_.size() || s_[i_] != *p) fail(std::string("expected ") + lit);
            ++i_;
        }
    }
    JVal parseBool() {
        if (peek() == 't') {
            expect("true");
            return JVal::mkBool(true);
        }
        expect("false");
        return JVal::mkBool(false);
    }
    JVal parseNum() {
        skipWs();
        size_t start = i_;
        while (i_ < s_.size() &&
               (std::isdigit(static_cast<unsigned char>(s_[i_])) || s_[i_] == '-' || s_[i_] == '+' ||
                s_[i_] == '.' || s_[i_] == 'e' || s_[i_] == 'E'))
            ++i_;
        if (i_ == start) fail("expected number");
        return JVal::mkNum(std::stod(s_.substr(start, i_ - start)));
    }
    std::string parseStr() {
        skipWs();
        if (s_[i_] != '"') fail("expected string");
        ++i_;
        std::string out;
        while (i_ < s_.size()) {
            char c = s_[i_++];
            if (c == '"') return out;
            if (c == '\\') {
                if (i_ >= s_.size()) fail("bad escape");
                char e = s_[i_++];
                switch (e) {
                    case '"': out += '"'; break;
                    case '\\': out += '\\'; break;
                    case '/': out += '/'; break;
                    case 'n': out += '\n'; break;
                    case 'r': out += '\r'; break;
                    case 't': out += '\t'; break;
                    case 'b': out += '\b'; break;
                    case 'f': out += '\f'; break;
                    case 'u': {
                        if (i_ + 4 > s_.size()) fail("bad \\u");
                        int code = std::stoi(s_.substr(i_, 4), nullptr, 16);
                        i_ += 4;
                        if (code < 0x80) {
                            out += static_cast<char>(code);
                        } else if (code < 0x800) {
                            out += static_cast<char>(0xC0 | (code >> 6));
                            out += static_cast<char>(0x80 | (code & 0x3F));
                        } else {
                            out += static_cast<char>(0xE0 | (code >> 12));
                            out += static_cast<char>(0x80 | ((code >> 6) & 0x3F));
                            out += static_cast<char>(0x80 | (code & 0x3F));
                        }
                        break;
                    }
                    default: fail("bad escape char");
                }
            } else {
                out += c;
            }
        }
        fail("unterminated string");
    }
    JVal parseArr() {
        ++i_;  // [
        JVal v = JVal::mkArr();
        skipWs();
        if (peek() == ']') {
            ++i_;
            return v;
        }
        while (true) {
            v.arr->push_back(parseValue());
            char c = peek();
            if (c == ',') {
                ++i_;
                continue;
            }
            if (c == ']') {
                ++i_;
                break;
            }
            fail("expected , or ]");
        }
        return v;
    }
    JVal parseObj() {
        ++i_;  // {
        JVal v = JVal::mkObj();
        skipWs();
        if (peek() == '}') {
            ++i_;
            return v;
        }
        while (true) {
            std::string key = parseStr();
            if (peek() != ':') fail("expected :");
            ++i_;
            (*v.obj)[key] = parseValue();
            char c = peek();
            if (c == ',') {
                ++i_;
                continue;
            }
            if (c == '}') {
                ++i_;
                break;
            }
            fail("expected , or }");
        }
        return v;
    }
};

// ===========================================================================
// helpers for building / reading typed values
// ===========================================================================
JVal arrOf() { return JVal::mkArr(); }

template <typename T>
JVal jIntArr(const std::vector<T> &xs) {
    JVal a = JVal::mkArr();
    for (auto x : xs) a.arr->push_back(JVal::mkNum(static_cast<double>(x)));
    return a;
}

std::vector<Id> readIdArr(const JVal &a) {
    std::vector<Id> out;
    for (const auto &e : a.asArr()) out.push_back(static_cast<Id>(e.asInt()));
    return out;
}

JVal jPair(Id a, Id b) {
    JVal v = JVal::mkArr();
    v.arr->push_back(JVal::mkNum(a));
    v.arr->push_back(JVal::mkNum(b));
    return v;
}

JVal jResourceVec(const ResourceVec &d) {
    JVal a = JVal::mkArr();
    for (int x : d) a.arr->push_back(JVal::mkNum(x));
    return a;
}
ResourceVec readResourceVec(const JVal &a) {
    ResourceVec out{};
    const JArr &xs = a.asArr();
    for (size_t k = 0; k < out.size() && k < xs.size(); ++k) out[k] = static_cast<int>(xs[k].asInt());
    return out;
}

}  // namespace

// ===========================================================================
// ModelInputs <-> JSON
// ===========================================================================
void writeModelInputs(const ModelInputs &in, std::ostream &os) {
    JVal root = JVal::mkObj();
    JObj &o = *root.obj;

    // device: kind + the only runtime-overridden field (num_stages). The rest of
    // DeviceSpec is reconstructed deterministically from kind on read (matching
    // CompilerBridge::ingest which builds it from DeviceSpec::fromName()).
    {
        JVal d = JVal::mkObj();
        (*d.obj)["kind"] = JVal::mkNum(static_cast<int>(in.device.kind));
        (*d.obj)["num_stages"] = JVal::mkNum(in.device.num_stages);
        o["device"] = d;
    }

    // slices
    {
        JVal a = arrOf();
        for (const auto &s : in.slices) {
            JVal e = JVal::mkObj();
            JObj &so = *e.obj;
            so["id"] = JVal::mkNum(s.id);
            so["width_bits"] = JVal::mkNum(s.width_bits);
            so["live_lo"] = JVal::mkNum(s.live_lo);
            so["live_hi"] = JVal::mkNum(s.live_hi);
            so["required_offset"] = JVal::mkNum(s.required_offset);
            so["byte_aligned"] = JVal::mkBool(s.byte_aligned);
            so["needs_mau"] = JVal::mkBool(s.needs_mau);
            so["solitary"] = JVal::mkBool(s.solitary);
            so["no_pack"] = JVal::mkBool(s.no_pack);
            so["max_kind_size"] = JVal::mkNum(static_cast<int>(s.max_kind_size));
            so["field_id"] = JVal::mkNum(s.field_id);
            a.arr->push_back(e);
        }
        o["slices"] = a;
    }

    // containers
    {
        JVal a = arrOf();
        for (const auto &c : in.containers) {
            JVal e = JVal::mkObj();
            JObj &co = *e.obj;
            co["id"] = JVal::mkNum(c.id);
            co["size"] = JVal::mkNum(static_cast<int>(c.size));
            co["kind"] = JVal::mkNum(static_cast<int>(c.kind));
            co["mau_group"] = JVal::mkNum(c.mau_group);
            co["ingress_only"] = JVal::mkBool(c.ingress_only);
            co["egress_only"] = JVal::mkBool(c.egress_only);
            a.arr->push_back(e);
        }
        o["containers"] = a;
    }

    // slice_pairs
    {
        JVal sp = JVal::mkObj();
        JVal mx = arrOf();
        for (const auto &p : in.slice_pairs.mutex) mx.arr->push_back(jPair(p.first, p.second));
        JVal cf = arrOf();
        for (const auto &p : in.slice_pairs.conflict) cf.arr->push_back(jPair(p.first, p.second));
        (*sp.obj)["mutex"] = mx;
        (*sp.obj)["conflict"] = cf;
        o["slice_pairs"] = sp;
    }

    // legal_containers
    {
        JVal a = arrOf();
        for (const auto &lc : in.legal_containers) a.arr->push_back(jIntArr(lc));
        o["legal_containers"] = a;
    }

    // tables
    {
        JVal a = arrOf();
        for (const auto &t : in.tables) {
            JVal e = JVal::mkObj();
            JObj &to = *e.obj;
            to["id"] = JVal::mkNum(t.id);
            to["gress"] = JVal::mkNum(static_cast<int>(t.gress));
            to["splittable"] = JVal::mkBool(t.splittable);
            to["host_table"] = JVal::mkNum(t.host_table);
            to["action_ids"] = jIntArr(t.action_ids);
            JVal opts = arrOf();
            for (const auto &op : t.options) {
                JVal oe = JVal::mkObj();
                JObj &oo = *oe.obj;
                oo["option_id"] = JVal::mkNum(op.option_id);
                oo["demand"] = jResourceVec(op.demand);
                oo["parts"] = JVal::mkNum(op.parts);
                oo["power"] = JVal::mkNum(op.power);
                oo["key_byte_ids"] = jIntArr(op.key_byte_ids);
                opts.arr->push_back(oe);
            }
            to["options"] = opts;
            a.arr->push_back(e);
        }
        o["tables"] = a;
    }

    // deps
    {
        JVal a = arrOf();
        for (const auto &d : in.deps) {
            JVal e = JVal::mkObj();
            (*e.obj)["from"] = JVal::mkNum(d.from);
            (*e.obj)["to"] = JVal::mkNum(d.to);
            (*e.obj)["gap"] = JVal::mkNum(d.gap);
            (*e.obj)["kind"] = JVal::mkNum(static_cast<int>(d.kind));
            a.arr->push_back(e);
        }
        o["deps"] = a;
    }

    // table_mutex
    {
        JVal a = arrOf();
        for (const auto &p : in.table_mutex) a.arr->push_back(jPair(p.first, p.second));
        o["table_mutex"] = a;
    }

    // actions
    {
        JVal a = arrOf();
        for (const auto &ac : in.actions) {
            JVal e = JVal::mkObj();
            JObj &ao = *e.obj;
            ao["id"] = JVal::mkNum(ac.id);
            ao["table_id"] = JVal::mkNum(ac.table_id);
            ao["gress"] = JVal::mkNum(static_cast<int>(ac.gress));
            ao["stateful"] = JVal::mkBool(ac.stateful);
            ao["written_containers"] = jIntArr(ac.written_containers);
            ao["identical_actions"] = jIntArr(ac.identical_actions);
            a.arr->push_back(e);
        }
        o["actions"] = a;
    }

    // action_data
    {
        JVal a = arrOf();
        for (const auto &f : in.action_data) {
            JVal e = JVal::mkObj();
            (*e.obj)["id"] = JVal::mkNum(f.id);
            (*e.obj)["action_id"] = JVal::mkNum(f.action_id);
            (*e.obj)["slot_bytes"] = JVal::mkNum(f.slot_bytes);
            (*e.obj)["format_offset"] = JVal::mkNum(f.format_offset);
            a.arr->push_back(e);
        }
        o["action_data"] = a;
    }

    o["action_data_bus_bytes"] = JVal::mkNum(in.action_data_bus_bytes);

    emit(os, root);
    os << '\n';
}

ModelInputs readModelInputs(std::istream &is) {
    std::ostringstream ss;
    ss << is.rdbuf();
    JVal root = Parser(ss.str()).parse();
    ModelInputs in;

    // device
    {
        const JVal &d = root.at("device");
        auto k = static_cast<DeviceKind>(d.at("kind").asInt());
        switch (k) {
            case DeviceKind::Tofino2U: in.device = DeviceSpec::tofino2u(); break;
            case DeviceKind::Tofino2M: in.device = DeviceSpec::tofino2m(); break;
            default: in.device = DeviceSpec::tofino1(); break;
        }
        in.device.kind = k;
        in.device.num_stages = static_cast<int>(d.at("num_stages").asInt());
    }

    for (const auto &e : root.at("slices").asArr()) {
        SliceInput s;
        s.id = static_cast<Id>(e.at("id").asInt());
        s.width_bits = static_cast<int>(e.at("width_bits").asInt());
        s.live_lo = static_cast<int>(e.at("live_lo").asInt());
        s.live_hi = static_cast<int>(e.at("live_hi").asInt());
        s.required_offset = static_cast<int>(e.at("required_offset").asInt());
        s.byte_aligned = e.at("byte_aligned").asBool();
        s.needs_mau = e.at("needs_mau").asBool();
        s.solitary = e.at("solitary").asBool();
        s.no_pack = e.at("no_pack").asBool();
        s.max_kind_size = static_cast<PhvSize>(e.at("max_kind_size").asInt());
        s.field_id = static_cast<Id>(e.at("field_id").asInt());
        in.slices.push_back(s);
    }

    for (const auto &e : root.at("containers").asArr()) {
        ContainerInput c;
        c.id = static_cast<Id>(e.at("id").asInt());
        c.size = static_cast<PhvSize>(e.at("size").asInt());
        c.kind = static_cast<PhvKind>(e.at("kind").asInt());
        c.mau_group = static_cast<int>(e.at("mau_group").asInt());
        c.ingress_only = e.at("ingress_only").asBool();
        c.egress_only = e.at("egress_only").asBool();
        in.containers.push_back(c);
    }

    {
        const JVal &sp = root.at("slice_pairs");
        for (const auto &p : sp.at("mutex").asArr()) {
            const JArr &pr = p.asArr();
            in.slice_pairs.mutex.push_back({static_cast<Id>(pr[0].asInt()),
                                            static_cast<Id>(pr[1].asInt())});
        }
        for (const auto &p : sp.at("conflict").asArr()) {
            const JArr &pr = p.asArr();
            in.slice_pairs.conflict.push_back({static_cast<Id>(pr[0].asInt()),
                                               static_cast<Id>(pr[1].asInt())});
        }
    }

    for (const auto &e : root.at("legal_containers").asArr())
        in.legal_containers.push_back(readIdArr(e));

    for (const auto &e : root.at("tables").asArr()) {
        TableInput t;
        t.id = static_cast<Id>(e.at("id").asInt());
        t.gress = static_cast<Gress>(e.at("gress").asInt());
        t.splittable = e.at("splittable").asBool();
        t.host_table = static_cast<Id>(e.at("host_table").asInt());
        t.action_ids = readIdArr(e.at("action_ids"));
        for (const auto &oe : e.at("options").asArr()) {
            LayoutOptionInput op;
            op.option_id = static_cast<Id>(oe.at("option_id").asInt());
            op.demand = readResourceVec(oe.at("demand"));
            op.parts = static_cast<int>(oe.at("parts").asInt());
            op.power = oe.at("power").asDouble();
            op.key_byte_ids = readIdArr(oe.at("key_byte_ids"));
            t.options.push_back(op);
        }
        in.tables.push_back(t);
    }

    for (const auto &e : root.at("deps").asArr()) {
        DepEdge d;
        d.from = static_cast<Id>(e.at("from").asInt());
        d.to = static_cast<Id>(e.at("to").asInt());
        d.gap = static_cast<int>(e.at("gap").asInt());
        d.kind = static_cast<DepKind>(e.at("kind").asInt());
        in.deps.push_back(d);
    }

    for (const auto &p : root.at("table_mutex").asArr()) {
        const JArr &pr = p.asArr();
        in.table_mutex.push_back(
            {static_cast<Id>(pr[0].asInt()), static_cast<Id>(pr[1].asInt())});
    }

    for (const auto &e : root.at("actions").asArr()) {
        ActionInput ac;
        ac.id = static_cast<Id>(e.at("id").asInt());
        ac.table_id = static_cast<Id>(e.at("table_id").asInt());
        ac.gress = static_cast<Gress>(e.at("gress").asInt());
        ac.stateful = e.at("stateful").asBool();
        ac.written_containers = readIdArr(e.at("written_containers"));
        ac.identical_actions = readIdArr(e.at("identical_actions"));
        in.actions.push_back(ac);
    }

    for (const auto &e : root.at("action_data").asArr()) {
        ActionDataField f;
        f.id = static_cast<Id>(e.at("id").asInt());
        f.action_id = static_cast<Id>(e.at("action_id").asInt());
        f.slot_bytes = static_cast<int>(e.at("slot_bytes").asInt());
        f.format_offset = static_cast<int>(e.at("format_offset").asInt());
        in.action_data.push_back(f);
    }

    in.action_data_bus_bytes = static_cast<int>(root.at("action_data_bus_bytes").asInt());
    return in;
}

// ===========================================================================
// ModelResults <-> JSON
// ===========================================================================
void writeModelResults(const ModelResults &res, std::ostream &os) {
    JVal root = JVal::mkObj();
    JObj &o = *root.obj;

    // phv
    {
        JVal p = JVal::mkObj();
        (*p.obj)["containers_used"] = JVal::mkNum(res.phv.containers_used);
        JVal a = arrOf();
        for (const auto &as : res.phv.assignments) {
            JVal e = JVal::mkObj();
            (*e.obj)["slice_id"] = JVal::mkNum(as.slice_id);
            (*e.obj)["container_id"] = JVal::mkNum(as.container_id);
            (*e.obj)["bit_offset"] = JVal::mkNum(as.bit_offset);
            a.arr->push_back(e);
        }
        (*p.obj)["assignments"] = a;
        o["phv"] = p;
    }

    // mau
    {
        JVal m = JVal::mkObj();
        (*m.obj)["stages_used"] = JVal::mkNum(res.mau.stages_used);
        (*m.obj)["total_power"] = JVal::mkNum(res.mau.total_power);
        (*m.obj)["peak_utilization"] = jResourceVec(res.mau.peak_utilization);
        JVal a = arrOf();
        for (const auto &ta : res.mau.tables) {
            JVal e = JVal::mkObj();
            (*e.obj)["table_id"] = JVal::mkNum(ta.table_id);
            (*e.obj)["option_id"] = JVal::mkNum(ta.option_id);
            (*e.obj)["first_stage"] = JVal::mkNum(ta.first_stage);
            (*e.obj)["last_stage"] = JVal::mkNum(ta.last_stage);
            (*e.obj)["stage_tables"] = jIntArr(ta.stage_tables);
            a.arr->push_back(e);
        }
        (*m.obj)["tables"] = a;
        o["mau"] = m;
    }

    // vliw
    {
        JVal v = JVal::mkObj();
        JVal acts = arrOf();
        for (const auto &aa : res.vliw.actions) {
            JVal e = JVal::mkObj();
            (*e.obj)["action_id"] = JVal::mkNum(aa.action_id);
            (*e.obj)["imem_row"] = JVal::mkNum(aa.imem_row);
            (*e.obj)["imem_color"] = JVal::mkNum(aa.imem_color);
            acts.arr->push_back(e);
        }
        (*v.obj)["actions"] = acts;
        JVal ad = arrOf();
        for (const auto &da : res.vliw.adata) {
            JVal e = JVal::mkObj();
            (*e.obj)["field_id"] = JVal::mkNum(da.field_id);
            (*e.obj)["bus_byte"] = JVal::mkNum(da.bus_byte);
            ad.arr->push_back(e);
        }
        (*v.obj)["adata"] = ad;
        o["vliw"] = v;
    }

    emit(os, root);
    os << '\n';
}

ModelResults readModelResults(std::istream &is) {
    std::ostringstream ss;
    ss << is.rdbuf();
    JVal root = Parser(ss.str()).parse();
    ModelResults res;

    {
        const JVal &p = root.at("phv");
        res.phv.containers_used = static_cast<int>(p.at("containers_used").asInt());
        for (const auto &e : p.at("assignments").asArr()) {
            PhvAssignment a;
            a.slice_id = static_cast<Id>(e.at("slice_id").asInt());
            a.container_id = static_cast<Id>(e.at("container_id").asInt());
            a.bit_offset = static_cast<int>(e.at("bit_offset").asInt());
            res.phv.assignments.push_back(a);
        }
    }

    {
        const JVal &m = root.at("mau");
        res.mau.stages_used = static_cast<int>(m.at("stages_used").asInt());
        res.mau.total_power = m.at("total_power").asDouble();
        res.mau.peak_utilization = readResourceVec(m.at("peak_utilization"));
        for (const auto &e : m.at("tables").asArr()) {
            TableAssignment ta;
            ta.table_id = static_cast<Id>(e.at("table_id").asInt());
            ta.option_id = static_cast<Id>(e.at("option_id").asInt());
            ta.first_stage = static_cast<int>(e.at("first_stage").asInt());
            ta.last_stage = static_cast<int>(e.at("last_stage").asInt());
            for (const auto &s : e.at("stage_tables").asArr())
                ta.stage_tables.push_back(static_cast<int>(s.asInt()));
            res.mau.tables.push_back(ta);
        }
    }

    {
        const JVal &v = root.at("vliw");
        for (const auto &e : v.at("actions").asArr()) {
            ActionAssignment aa;
            aa.action_id = static_cast<Id>(e.at("action_id").asInt());
            aa.imem_row = static_cast<int>(e.at("imem_row").asInt());
            aa.imem_color = static_cast<int>(e.at("imem_color").asInt());
            res.vliw.actions.push_back(aa);
        }
        for (const auto &e : v.at("adata").asArr()) {
            AdataAssignment da;
            da.field_id = static_cast<Id>(e.at("field_id").asInt());
            da.bus_byte = static_cast<int>(e.at("bus_byte").asInt());
            res.vliw.adata.push_back(da);
        }
    }

    return res;
}

// ===========================================================================
// ResumeBundle <-> JSON
// ===========================================================================
void writeResumeBundle(const ResumeBundle &b, std::ostream &os) {
    JVal root = JVal::mkObj();
    JObj &o = *root.obj;

    JVal ts = arrOf();
    for (const auto &t : b.tables) {
        JVal e = JVal::mkObj();
        (*e.obj)["id"] = JVal::mkNum(t.id);
        JVal nm;
        nm.t = JVal::T::Str;
        nm.str = t.name;
        (*e.obj)["name"] = nm;
        (*e.obj)["option_ids"] = jIntArr(t.option_ids);
        ts.arr->push_back(e);
    }
    o["tables"] = ts;

    JVal as = arrOf();
    for (const auto &a : b.actions) {
        JVal e = JVal::mkObj();
        (*e.obj)["id"] = JVal::mkNum(a.id);
        (*e.obj)["table_id"] = JVal::mkNum(a.table_id);
        JVal tn;
        tn.t = JVal::T::Str;
        tn.str = a.table_name;
        (*e.obj)["table_name"] = tn;
        JVal an;
        an.t = JVal::T::Str;
        an.str = a.action_name;
        (*e.obj)["action_name"] = an;
        as.arr->push_back(e);
    }
    o["actions"] = as;

    emit(os, root);
    os << '\n';
}

ResumeBundle readResumeBundle(std::istream &is) {
    std::ostringstream ss;
    ss << is.rdbuf();
    JVal root = Parser(ss.str()).parse();
    ResumeBundle b;
    for (const auto &e : root.at("tables").asArr()) {
        ResumeTableRef t;
        t.id = static_cast<Id>(e.at("id").asInt());
        t.name = e.at("name").str;
        t.option_ids = readIdArr(e.at("option_ids"));
        b.tables.push_back(t);
    }
    for (const auto &e : root.at("actions").asArr()) {
        ResumeActionRef a;
        a.id = static_cast<Id>(e.at("id").asInt());
        a.table_id = static_cast<Id>(e.at("table_id").asInt());
        a.table_name = e.at("table_name").str;
        a.action_name = e.at("action_name").str;
        b.actions.push_back(a);
    }
    return b;
}

// ===========================================================================
// path wrappers
// ===========================================================================
void writeModelInputsFile(const ModelInputs &in, const std::string &path) {
    std::ofstream os(path);
    if (!os) throw std::runtime_error("ralloc: cannot open for write: " + path);
    writeModelInputs(in, os);
}
ModelInputs readModelInputsFile(const std::string &path) {
    std::ifstream is(path);
    if (!is) throw std::runtime_error("ralloc: cannot open for read: " + path);
    return readModelInputs(is);
}
void writeModelResultsFile(const ModelResults &res, const std::string &path) {
    std::ofstream os(path);
    if (!os) throw std::runtime_error("ralloc: cannot open for write: " + path);
    writeModelResults(res, os);
}
ModelResults readModelResultsFile(const std::string &path) {
    std::ifstream is(path);
    if (!is) throw std::runtime_error("ralloc: cannot open for read: " + path);
    return readModelResults(is);
}
void writeResumeBundleFile(const ResumeBundle &b, const std::string &path) {
    std::ofstream os(path);
    if (!os) throw std::runtime_error("ralloc: cannot open for write: " + path);
    writeResumeBundle(b, os);
}
ResumeBundle readResumeBundleFile(const std::string &path) {
    std::ifstream is(path);
    if (!is) throw std::runtime_error("ralloc: cannot open for read: " + path);
    return readResumeBundle(is);
}

}  // namespace ralloc
