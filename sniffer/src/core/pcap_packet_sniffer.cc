#include <iterator>
#include <algorithm>
#include <sstream>
#include <spdlog/spdlog.h>

#include "include/PacketRegion.hpp"
#include "include/PcapPacketSniffer.hpp"
#include "include/SnifferException.hpp"
#include "include/SniffedPacket.hpp"

#include "../communications/include/Server.hpp"
#include "../communications/serialization/include/SerializedObject.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Communications;
using namespace Sniffer::Communications::Serialization;

PcapPacketSniffer::PcapPacketSniffer(
        Server* server,
        std::vector<std::string> interfaces,
        std::vector<std::string> filters,
        std::vector<std::string> shared,
        const ConfigurationMgr& config,
        const LayerStack& stack)
    : PacketSniffer(server, interfaces, filters, shared, config, stack)
{}

void PcapPacketSniffer::prepare_interface() {
    char error_buffer[PCAP_ERRBUF_SIZE];

    // TODO: Fix when multiple interfaces are supported
    const char* interface_name = interfaces_[0].c_str();

    if (pcap_lookupnet(interface_name, &network_, &subnet_mask_, error_buffer) == -1) {
        spdlog::get("console")->warn("Could not get netmask for device {0}: {1}",
                interface_name, error_buffer);
        network_ = 0;
        subnet_mask_ = 0;
    }

    int snap_len = config_manager_.get_value<int>("sniffer", "snap_len");

    handle_ = pcap_open_live(interface_name, snap_len, 1, 1000, error_buffer);
    if (handle_ == NULL) {
        std::ostringstream exception_message;
        exception_message << "Couldn't open device " << interface_name << ": "
            << error_buffer;
        throw SnifferException { exception_message.str() };
    }

    if (pcap_datalink(handle_) != DLT_EN10MB) {
        std::ostringstream exception_message;
        exception_message << "Not an Ethernet device: " << interface_name;
        throw SnifferException { exception_message.str() };
    }
}

void PcapPacketSniffer::parse_filters() {
    std::ostringstream filters;
    std::copy(filters_.begin(), filters_.end() - 1,
            std::ostream_iterator<std::string>(filters, ";"));
    filters << filters_.back();

    if (pcap_compile(handle_, &parsed_filters_, filters.str().c_str(), 0, network_) == -1) {
        std::ostringstream exception_message;
        exception_message << "Couldn't parse filters " << filters.str() << ": " << pcap_geterr(handle_);
        throw SnifferException { exception_message.str() };
    }
}

void PcapPacketSniffer::apply_filters() {
    if (pcap_setfilter(handle_, &parsed_filters_) == -1) {
        std::ostringstream exception_message;
        exception_message << "Couldn't apply filters ";
        std::copy(filters_.begin(), filters_.end() - 1,
                std::ostream_iterator<std::string>(exception_message, ","));
        exception_message << filters_.back() << ": " << pcap_geterr(handle_);
        throw SnifferException { exception_message.str() };
    }
}

void PcapPacketSniffer::sniff() {
    pcap_loop(
            handle_,
            config_manager_.get_value<int>("sniffer", "packets_count"),
            on_packet_received,
            (u_char *)this);
}

void PcapPacketSniffer::on_packet_received(u_char* args,
        const struct pcap_pkthdr* header, const u_char* packet) {
    ((PcapPacketSniffer *)args)->on_packet_received_internal(header, packet);
}

void PcapPacketSniffer::on_packet_received_internal(
        const struct pcap_pkthdr* header,
        const u_char* packet) {
    PacketRegion body { 0, (int)header->caplen };

    SniffedPacket packet_obj { packet, body };
    SerializedObject accumulator_obj { "{}" };

    // http://www.tcpdump.org/linktypes.html
    stack_.handle_reception(packet_obj, accumulator_obj, 1);
    server_->broadcast(accumulator_obj.get_data());
}

PcapPacketSniffer::~PcapPacketSniffer() {
    pcap_freecode(&parsed_filters_);
    pcap_close(handle_);
}
