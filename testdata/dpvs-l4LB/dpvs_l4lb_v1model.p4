/*
 * DPVS L4 Load Balancer - v1model version for BMv2/DSLX
 *
 * Implements core DPVS L4 LB functionality:
 *   - Full NAT: Client->VIP rewritten to Client->RS (forward)
 *                RS->Client rewritten to VIP->Client (reverse)
 *   - Bidirectional flow tables for session persistence (5-tuple exact match)
 *   - Dynamic load balancing: new connections scheduled to RS
 *   - TCP and UDP support
 *
 * Architecture: v1model.p4 (BMv2 simple_switch)
 */

#include <core.p4>
#include <v1model.p4>

// ===== Constants =====

typedef bit<48> mac_addr_t;
typedef bit<32> ipv4_addr_t;
typedef bit<16> ether_type_t;

const ether_type_t ETHERTYPE_IPV4 = 16w0x0800;
const bit<8> IP_PROTO_TCP = 6;
const bit<8> IP_PROTO_UDP = 17;

// ===== Headers =====

header ethernet_h {
    mac_addr_t dst_addr;
    mac_addr_t src_addr;
    ether_type_t ether_type;
}

header ipv4_h {
    bit<4>  version;
    bit<4>  ihl;
    bit<6>  dscp;
    bit<2>  ecn;
    bit<16> total_len;
    bit<16> identification;
    bit<3>  flags;
    bit<13> frag_offset;
    bit<8>  ttl;
    bit<8>  protocol;
    bit<16> hdr_checksum;
    ipv4_addr_t src_addr;
    ipv4_addr_t dst_addr;
}

header tcp_h {
    bit<16> src_port;
    bit<16> dst_port;
    bit<32> seq_no;
    bit<32> ack_no;
    bit<4>  data_offset;
    bit<4>  res;
    bit<8>  flags;
    bit<16> window;
    bit<16> checksum;
    bit<16> urgent_ptr;
}

header udp_h {
    bit<16> src_port;
    bit<16> dst_port;
    bit<16> length;
    bit<16> checksum;
}

struct headers_t {
    ethernet_h ethernet;
    ipv4_h     ipv4;
    tcp_h      tcp;
    udp_h      udp;
}

// ===== Metadata =====

struct ig_metadata_t {
    // Extracted L4 ports (unified across TCP/UDP)
    bit<16> l4_src_port;
    bit<16> l4_dst_port;
    bit<8>  ip_proto;

    // Flow direction flags
    bit<1>  is_tcp;
    bit<1>  is_udp;
    bit<1>  flow_hit;
    bit<1>  is_vip;

    // NAT rewrite values (populated by flow table or LB selection)
    ipv4_addr_t nat_src_ip;
    ipv4_addr_t nat_dst_ip;
    bit<16>     nat_src_port;
    bit<16>     nat_dst_port;
    mac_addr_t  nat_dst_mac;
    mac_addr_t  nat_src_mac;
    bit<9>      egress_port;

    // RS selection index for dynamic LB
    bit<8>  rs_index;

    // Drop flag
    bit<1>  drop_flag;
}

struct metadata {
    ig_metadata_t ig_md;
}

// ===== Parser =====

parser MyParser(packet_in pkt,
                out headers_t hdr,
                inout metadata meta,
                inout standard_metadata_t std_meta) {

    state start {
        meta.ig_md.flow_hit = 0;
        meta.ig_md.is_vip = 0;
        meta.ig_md.is_tcp = 0;
        meta.ig_md.is_udp = 0;
        meta.ig_md.drop_flag = 0;
        meta.ig_md.rs_index = 0;
        transition parse_ethernet;
    }

    state parse_ethernet {
        pkt.extract(hdr.ethernet);
        transition select(hdr.ethernet.ether_type) {
            ETHERTYPE_IPV4: parse_ipv4;
            default: accept;
        }
    }

    state parse_ipv4 {
        pkt.extract(hdr.ipv4);
        meta.ig_md.ip_proto = hdr.ipv4.protocol;
        transition select(hdr.ipv4.protocol) {
            IP_PROTO_TCP: parse_tcp;
            IP_PROTO_UDP: parse_udp;
            default: accept;
        }
    }

    state parse_tcp {
        pkt.extract(hdr.tcp);
        meta.ig_md.l4_src_port = hdr.tcp.src_port;
        meta.ig_md.l4_dst_port = hdr.tcp.dst_port;
        meta.ig_md.is_tcp = 1;
        transition accept;
    }

    state parse_udp {
        pkt.extract(hdr.udp);
        meta.ig_md.l4_src_port = hdr.udp.src_port;
        meta.ig_md.l4_dst_port = hdr.udp.dst_port;
        meta.ig_md.is_udp = 1;
        transition accept;
    }
}

// ===== Verify Checksum =====

control MyVerifyChecksum(inout headers_t hdr, inout metadata meta) {
    apply { }
}

// ===== Ingress Control =====

control MyIngress(inout headers_t hdr,
                  inout metadata meta,
                  inout standard_metadata_t std_meta) {

    action drop() {
        mark_to_drop(std_meta);
    }

    action nop() { }

    // VIP table: check if destination IP is a virtual IP
    action set_vip() {
        meta.ig_md.is_vip = 1;
    }

    table vip_table {
        key = {
            hdr.ipv4.dst_addr : exact;
        }
        actions = {
            set_vip;
            nop;
            NoAction;
        }
        size = 256;
        default_action = nop();
    }

    // Forward flow table (Client -> VIP, rewrite to Client -> RS)
    action forward_flow_nat(ipv4_addr_t rs_ip, bit<16> rs_port,
                            mac_addr_t dst_mac, mac_addr_t src_mac,
                            ipv4_addr_t local_ip, bit<16> local_port,
                            bit<9> port) {
        meta.ig_md.nat_src_ip   = local_ip;
        meta.ig_md.nat_dst_ip   = rs_ip;
        meta.ig_md.nat_src_port = local_port;
        meta.ig_md.nat_dst_port = rs_port;
        meta.ig_md.nat_dst_mac  = dst_mac;
        meta.ig_md.nat_src_mac  = src_mac;
        meta.ig_md.egress_port  = port;
        meta.ig_md.flow_hit     = 1;
    }

    action forward_flow_drop() {
        mark_to_drop(std_meta);
    }

    table forward_flow {
        key = {
            hdr.ipv4.src_addr  : exact;
            hdr.ipv4.dst_addr  : exact;
            meta.ig_md.ip_proto     : exact;
            meta.ig_md.l4_src_port  : exact;
            meta.ig_md.l4_dst_port  : exact;
        }
        actions = {
            forward_flow_nat;
            forward_flow_drop;
            nop;
            NoAction;
        }
        size = 1024;
        default_action = nop();
    }

    // Reverse flow table (RS -> LB, rewrite to VIP -> Client)
    action reverse_flow_nat(ipv4_addr_t vip, bit<16> orig_dst_port,
                            ipv4_addr_t client_ip, bit<16> client_port,
                            mac_addr_t dst_mac, mac_addr_t src_mac,
                            bit<9> port) {
        meta.ig_md.nat_src_ip   = vip;
        meta.ig_md.nat_dst_ip   = client_ip;
        meta.ig_md.nat_src_port = orig_dst_port;
        meta.ig_md.nat_dst_port = client_port;
        meta.ig_md.nat_dst_mac  = dst_mac;
        meta.ig_md.nat_src_mac  = src_mac;
        meta.ig_md.egress_port  = port;
        meta.ig_md.flow_hit     = 1;
    }

    action reverse_flow_drop() {
        mark_to_drop(std_meta);
    }

    table reverse_flow {
        key = {
            hdr.ipv4.src_addr  : exact;
            hdr.ipv4.dst_addr  : exact;
            meta.ig_md.ip_proto     : exact;
            meta.ig_md.l4_src_port  : exact;
            meta.ig_md.l4_dst_port  : exact;
        }
        actions = {
            reverse_flow_nat;
            reverse_flow_drop;
            nop;
            NoAction;
        }
        size = 1024;
        default_action = nop();
    }

    // Dynamic Load Balancing
    action select_rs(ipv4_addr_t rs_ip, bit<16> rs_port,
                     mac_addr_t dst_mac, mac_addr_t src_mac,
                     ipv4_addr_t local_ip, bit<16> local_port,
                     bit<9> port, bit<8> idx) {
        meta.ig_md.nat_src_ip   = local_ip;
        meta.ig_md.nat_dst_ip   = rs_ip;
        meta.ig_md.nat_src_port = local_port;
        meta.ig_md.nat_dst_port = rs_port;
        meta.ig_md.nat_dst_mac  = dst_mac;
        meta.ig_md.nat_src_mac  = src_mac;
        meta.ig_md.egress_port  = port;
        meta.ig_md.rs_index     = idx;
        meta.ig_md.flow_hit     = 1;
    }

    table rs_select {
        key = {
            hdr.ipv4.dst_addr : exact;
            meta.ig_md.ip_proto    : exact;
        }
        actions = {
            select_rs;
            drop;
            NoAction;
        }
        size = 256;
        default_action = drop();
    }

    // NAT Rewrite actions
    action apply_nat_rewrite() {
        hdr.ipv4.src_addr = meta.ig_md.nat_src_ip;
        hdr.ipv4.dst_addr = meta.ig_md.nat_dst_ip;
        hdr.ethernet.dst_addr = meta.ig_md.nat_dst_mac;
        hdr.ethernet.src_addr = meta.ig_md.nat_src_mac;
        std_meta.egress_spec = meta.ig_md.egress_port;
    }

    action apply_tcp_nat_rewrite() {
        hdr.tcp.src_port = meta.ig_md.nat_src_port;
        hdr.tcp.dst_port = meta.ig_md.nat_dst_port;
    }

    action apply_udp_nat_rewrite() {
        hdr.udp.src_port = meta.ig_md.nat_src_port;
        hdr.udp.dst_port = meta.ig_md.nat_dst_port;
    }

    action decrement_ttl() {
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }

    apply {
        if (!hdr.ipv4.isValid()) {
            drop();
            return;
        }

        if (!(meta.ig_md.is_tcp == 1 || meta.ig_md.is_udp == 1)) {
            drop();
            return;
        }

        // Stage 1: Check if destination is a VIP
        vip_table.apply();

        // Stage 2: Look up existing flow tables
        if (meta.ig_md.is_vip == 1) {
            forward_flow.apply();
        } else {
            reverse_flow.apply();
        }

        // Stage 3: If no flow hit and this is a VIP packet, do dynamic LB
        if (meta.ig_md.flow_hit == 0 && meta.ig_md.is_vip == 1) {
            rs_select.apply();
        }

        // Stage 4: Apply NAT rewrite if flow was matched/created
        if (meta.ig_md.flow_hit == 1) {
            apply_nat_rewrite();
            decrement_ttl();

            // Rewrite L4 ports
            if (meta.ig_md.is_tcp == 1 && hdr.tcp.isValid()) {
                apply_tcp_nat_rewrite();
            } else if (meta.ig_md.is_udp == 1 && hdr.udp.isValid()) {
                apply_udp_nat_rewrite();
            }
        }

        // Stage 5: TTL check
        if (hdr.ipv4.ttl == 0) {
            drop();
        }

        // If no flow was established at all, drop
        if (meta.ig_md.flow_hit == 0) {
            drop();
        }
    }
}

// ===== Egress Control =====

control MyEgress(inout headers_t hdr,
                 inout metadata meta,
                 inout standard_metadata_t std_meta) {
    apply { }
}

// ===== Compute Checksum =====

control MyComputeChecksum(inout headers_t hdr, inout metadata meta) {
    apply { }
}

// ===== Deparser =====

control MyDeparser(packet_out pkt, in headers_t hdr) {
    apply {
        pkt.emit(hdr.ethernet);
        pkt.emit(hdr.ipv4);
        pkt.emit(hdr.tcp);
        pkt.emit(hdr.udp);
    }
}

// ===== Pipeline =====

V1Switch(
    MyParser(),
    MyVerifyChecksum(),
    MyIngress(),
    MyEgress(),
    MyComputeChecksum(),
    MyDeparser()
) main;
