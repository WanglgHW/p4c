/*
 * DPVS L4 Load Balancer Offload for Tofino1
 *
 * Implements core DPVS L4 LB functionality:
 *   - Full NAT: Client->VIP rewritten to Client->RS (forward)
 *                RS->Client rewritten to VIP->Client (reverse)
 *   - Bidirectional flow tables for session persistence (5-tuple exact match)
 *   - Dynamic load balancing: new connections scheduled to RS with lowest
 *     cumulative traffic (byte count)
 *   - TCP and UDP support
 *
 * Architecture: TNA (Tofino Native Architecture) for Tofino1
 */

#include <core.p4>
#include <tna.p4>

// ===== Constants =====

typedef bit<48> mac_addr_t;
typedef bit<32> ipv4_addr_t;
typedef bit<16> ether_type_t;

const ether_type_t ETHERTYPE_IPV4 = 16w0x0800;
const bit<8> IP_PROTO_TCP = 6;
const bit<8> IP_PROTO_UDP = 17;

// Maximum number of real servers in the pool
const bit<32> MAX_RS = 32w64;

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
    bit<1>  flow_hit;         // 1 if existing flow found
    bit<1>  is_vip;           // 1 if dst_addr is a VIP

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

    // Packet length for traffic accounting
    bit<16> pkt_len;

    // Drop flag
    bit<1>  drop_flag;
}

struct eg_metadata_t {
    bit<1> placeholder;
}

// ===== Ingress Parser =====

parser SwitchIngressParser(
        packet_in pkt,
        out headers_t hdr,
        out ig_metadata_t ig_md,
        out ingress_intrinsic_metadata_t ig_intr_md) {

    state start {
        pkt.extract(ig_intr_md);
        pkt.advance(PORT_METADATA_SIZE);
        ig_md.flow_hit = 0;
        ig_md.is_vip = 0;
        ig_md.is_tcp = 0;
        ig_md.is_udp = 0;
        ig_md.drop_flag = 0;
        ig_md.rs_index = 0;
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
        ig_md.ip_proto = hdr.ipv4.protocol;
        ig_md.pkt_len = hdr.ipv4.total_len;
        transition select(hdr.ipv4.protocol) {
            IP_PROTO_TCP: parse_tcp;
            IP_PROTO_UDP: parse_udp;
            default: accept;
        }
    }

    state parse_tcp {
        pkt.extract(hdr.tcp);
        ig_md.l4_src_port = hdr.tcp.src_port;
        ig_md.l4_dst_port = hdr.tcp.dst_port;
        ig_md.is_tcp = 1;
        transition accept;
    }

    state parse_udp {
        pkt.extract(hdr.udp);
        ig_md.l4_src_port = hdr.udp.src_port;
        ig_md.l4_dst_port = hdr.udp.dst_port;
        ig_md.is_udp = 1;
        transition accept;
    }
}

// ===== Ingress Control =====

control SwitchIngress(
        inout headers_t hdr,
        inout ig_metadata_t ig_md,
        in ingress_intrinsic_metadata_t ig_intr_md,
        in ingress_intrinsic_metadata_from_parser_t ig_prsr_md,
        inout ingress_intrinsic_metadata_for_deparser_t ig_dprsr_md,
        inout ingress_intrinsic_metadata_for_tm_t ig_tm_md) {

    // ----- Actions -----

    action drop() {
        ig_dprsr_md.drop_ctl = 1;
    }

    action nop() { }

    // VIP table: check if destination IP is a virtual IP
    action set_vip() {
        ig_md.is_vip = 1;
    }

    table vip_table {
        key = {
            hdr.ipv4.dst_addr : exact;
        }
        actions = {
            set_vip;
            nop;
        }
        size = 256;
        default_action = nop();
    }

    // ----- Forward flow table (Client -> VIP, rewrite to Client -> RS) -----
    // Key: original 5-tuple from client
    // Populated by control plane when a new connection is established

    action forward_flow_nat(ipv4_addr_t rs_ip, bit<16> rs_port,
                            mac_addr_t dst_mac, mac_addr_t src_mac,
                            ipv4_addr_t local_ip, bit<16> local_port,
                            bit<9> port) {
        // Full NAT: src=local_ip:local_port, dst=rs_ip:rs_port
        ig_md.nat_src_ip   = local_ip;
        ig_md.nat_dst_ip   = rs_ip;
        ig_md.nat_src_port = local_port;
        ig_md.nat_dst_port = rs_port;
        ig_md.nat_dst_mac  = dst_mac;
        ig_md.nat_src_mac  = src_mac;
        ig_md.egress_port  = port;
        ig_md.flow_hit     = 1;
    }

    action forward_flow_drop() {
        ig_dprsr_md.drop_ctl = 1;
    }

    table forward_flow {
        key = {
            hdr.ipv4.src_addr  : exact;
            hdr.ipv4.dst_addr  : exact;
            ig_md.ip_proto     : exact;
            ig_md.l4_src_port  : exact;
            ig_md.l4_dst_port  : exact;
        }
        actions = {
            forward_flow_nat;
            forward_flow_drop;
            nop;
        }
        size = 65536;
        default_action = nop();
    }

    // ----- Reverse flow table (RS -> LB, rewrite to VIP -> Client) -----
    // Key: 5-tuple from RS response (src=RS, dst=local_ip)
    // Populated alongside forward flow

    action reverse_flow_nat(ipv4_addr_t vip, bit<16> orig_dst_port,
                            ipv4_addr_t client_ip, bit<16> client_port,
                            mac_addr_t dst_mac, mac_addr_t src_mac,
                            bit<9> port) {
        // Full NAT reverse: src=VIP:orig_dst_port, dst=client_ip:client_port
        ig_md.nat_src_ip   = vip;
        ig_md.nat_dst_ip   = client_ip;
        ig_md.nat_src_port = orig_dst_port;
        ig_md.nat_dst_port = client_port;
        ig_md.nat_dst_mac  = dst_mac;
        ig_md.nat_src_mac  = src_mac;
        ig_md.egress_port  = port;
        ig_md.flow_hit     = 1;
    }

    action reverse_flow_drop() {
        ig_dprsr_md.drop_ctl = 1;
    }

    table reverse_flow {
        key = {
            hdr.ipv4.src_addr  : exact;
            hdr.ipv4.dst_addr  : exact;
            ig_md.ip_proto     : exact;
            ig_md.l4_src_port  : exact;
            ig_md.l4_dst_port  : exact;
        }
        actions = {
            reverse_flow_nat;
            reverse_flow_drop;
            nop;
        }
        size = 65536;
        default_action = nop();
    }

    // ----- Dynamic Load Balancing -----
    // RS pool table: for new connections (no flow hit), select an RS
    // Control plane populates with RS entries and dynamically updates
    // rs_index based on traffic statistics (lowest traffic RS first).

    action select_rs(ipv4_addr_t rs_ip, bit<16> rs_port,
                     mac_addr_t dst_mac, mac_addr_t src_mac,
                     ipv4_addr_t local_ip, bit<16> local_port,
                     bit<9> port, bit<8> idx) {
        ig_md.nat_src_ip   = local_ip;
        ig_md.nat_dst_ip   = rs_ip;
        ig_md.nat_src_port = local_port;
        ig_md.nat_dst_port = rs_port;
        ig_md.nat_dst_mac  = dst_mac;
        ig_md.nat_src_mac  = src_mac;
        ig_md.egress_port  = port;
        ig_md.rs_index     = idx;
        ig_md.flow_hit     = 1;
    }

    // RS selection table: keyed by VIP + protocol
    // Control plane sets the action to point to the RS with lowest traffic
    table rs_select {
        key = {
            hdr.ipv4.dst_addr : exact;
            ig_md.ip_proto    : exact;
        }
        actions = {
            select_rs;
            drop;
        }
        size = 256;
        default_action = drop();
    }

    // ----- Traffic Counters per RS -----
    // Direct counter on RS traffic table for dynamic LB decisions
    // Control plane reads these counters to determine which RS has lowest traffic

    DirectCounter<bit<64>>(CounterType_t.BYTES) rs_traffic_counter;

    action count_rs_traffic() {
        rs_traffic_counter.count();
    }

    action count_rs_traffic_drop() {
        rs_traffic_counter.count();
        ig_dprsr_md.drop_ctl = 1;
    }

    table rs_traffic {
        key = {
            ig_md.rs_index : exact;
        }
        actions = {
            count_rs_traffic;
            count_rs_traffic_drop;
        }
        counters = rs_traffic_counter;
        size = 64;
        default_action = count_rs_traffic_drop();
    }

    // ----- NAT Rewrite -----
    // Applied after flow lookup / RS selection to rewrite packet headers

    action apply_nat_rewrite() {
        hdr.ipv4.src_addr = ig_md.nat_src_ip;
        hdr.ipv4.dst_addr = ig_md.nat_dst_ip;
        hdr.ethernet.dst_addr = ig_md.nat_dst_mac;
        hdr.ethernet.src_addr = ig_md.nat_src_mac;
        ig_tm_md.ucast_egress_port = ig_md.egress_port;
    }

    action apply_tcp_nat_rewrite() {
        hdr.tcp.src_port = ig_md.nat_src_port;
        hdr.tcp.dst_port = ig_md.nat_dst_port;
    }

    action apply_udp_nat_rewrite() {
        hdr.udp.src_port = ig_md.nat_src_port;
        hdr.udp.dst_port = ig_md.nat_dst_port;
    }

    // ----- TTL Decrement -----
    action decrement_ttl() {
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }

    // ===== Apply Block =====

    apply {
        if (!hdr.ipv4.isValid()) {
            drop();
            return;
        }

        if (!(ig_md.is_tcp == 1 || ig_md.is_udp == 1)) {
            drop();
            return;
        }

        // Stage 1: Check if destination is a VIP
        vip_table.apply();

        // Stage 2: Look up existing flow tables
        if (ig_md.is_vip == 1) {
            // Client -> VIP direction: check forward flow table
            forward_flow.apply();
        } else {
            // Possible RS -> LB direction: check reverse flow table
            reverse_flow.apply();
        }

        // Stage 3: If no flow hit and this is a VIP packet, do dynamic LB
        if (ig_md.flow_hit == 0 && ig_md.is_vip == 1) {
            rs_select.apply();
        }

        // Stage 4: Count RS traffic for dynamic LB statistics
        if (ig_md.flow_hit == 1) {
            rs_traffic.apply();
        }

        // Stage 5: Apply NAT rewrite if flow was matched/created
        if (ig_md.flow_hit == 1) {
            apply_nat_rewrite();
            decrement_ttl();

            // Rewrite L4 ports
            if (ig_md.is_tcp == 1 && hdr.tcp.isValid()) {
                apply_tcp_nat_rewrite();
            } else if (ig_md.is_udp == 1 && hdr.udp.isValid()) {
                apply_udp_nat_rewrite();
            }
        }

        // Stage 6: TTL check
        if (hdr.ipv4.ttl == 0) {
            drop();
        }

        // If no flow was established at all, drop
        if (ig_md.flow_hit == 0) {
            drop();
        }
    }
}

// ===== Ingress Deparser =====

control SwitchIngressDeparser(
        packet_out pkt,
        inout headers_t hdr,
        in ig_metadata_t ig_md,
        in ingress_intrinsic_metadata_for_deparser_t ig_dprsr_md) {
    apply {
        pkt.emit(hdr.ethernet);
        pkt.emit(hdr.ipv4);
        pkt.emit(hdr.tcp);
        pkt.emit(hdr.udp);
    }
}

// ===== Egress Parser =====

parser SwitchEgressParser(
        packet_in pkt,
        out headers_t hdr,
        out eg_metadata_t eg_md,
        out egress_intrinsic_metadata_t eg_intr_md) {

    state start {
        pkt.extract(eg_intr_md);
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
        transition select(hdr.ipv4.protocol) {
            IP_PROTO_TCP: parse_tcp;
            IP_PROTO_UDP: parse_udp;
            default: accept;
        }
    }

    state parse_tcp {
        pkt.extract(hdr.tcp);
        transition accept;
    }

    state parse_udp {
        pkt.extract(hdr.udp);
        transition accept;
    }
}

// ===== Egress Control =====

control SwitchEgress(
        inout headers_t hdr,
        inout eg_metadata_t eg_md,
        in egress_intrinsic_metadata_t eg_intr_md,
        in egress_intrinsic_metadata_from_parser_t eg_intr_md_from_prsr,
        inout egress_intrinsic_metadata_for_deparser_t eg_dprsr_md,
        inout egress_intrinsic_metadata_for_output_port_t eg_oport_md) {

    // Egress port MAC rewrite (optional, for L2 correctness)
    action rewrite_mac(mac_addr_t src_mac) {
        hdr.ethernet.src_addr = src_mac;
    }

    action eg_drop() {
        eg_dprsr_md.drop_ctl = 1;
    }

    table egress_mac {
        key = {
            eg_intr_md.egress_port : exact;
        }
        actions = {
            rewrite_mac;
            eg_drop;
        }
        size = 256;
        default_action = eg_drop();
    }

    apply {
        egress_mac.apply();
    }
}

// ===== Egress Deparser =====

control SwitchEgressDeparser(
        packet_out pkt,
        inout headers_t hdr,
        in eg_metadata_t eg_md,
        in egress_intrinsic_metadata_for_deparser_t eg_dprsr_md) {
    apply {
        pkt.emit(hdr.ethernet);
        pkt.emit(hdr.ipv4);
        pkt.emit(hdr.tcp);
        pkt.emit(hdr.udp);
    }
}

// ===== Pipeline =====

Pipeline(SwitchIngressParser(),
         SwitchIngress(),
         SwitchIngressDeparser(),
         SwitchEgressParser(),
         SwitchEgress(),
         SwitchEgressDeparser()) pipe;

Switch(pipe) main;
