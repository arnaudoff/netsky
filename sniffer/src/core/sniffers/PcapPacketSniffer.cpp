#include <sstream>
#include <spdlog/spdlog.h>

#include "include/PcapPacketSniffer.hpp"
#include "include/sniffer_exception.hpp"

using namespace Sniffer::Core::Sniffers;

PcapPacketSniffer::PcapPacketSniffer(std::shared_ptr<ConfigManager> manager)
    : PacketSniffer(manager)
{}

void PcapPacketSniffer::prepare_interface() {
    char error_buffer[PCAP_ERRBUF_SIZE];
    const char* interface_name = NULL;

    int conf_snap_len = config_manager_->get_value<int>("sniffer", "snap_len");
    std::string conf_interface_name =
        config_manager_->get_value<std::string>("sniffer", "interface_name");

    if (conf_interface_name.empty()) {
        interface_name = pcap_lookupdev(error_buffer);

        if (interface_name == NULL) {
            std::ostringstream exception_message;
            exception_message << "Could not find default device: " << error_buffer;
            throw sniffer_exception { exception_message.str() };
        }
    } else {
        interface_name = conf_interface_name.c_str();
    }

    if (pcap_lookupnet(interface_name, &network_, &subnet_mask_, error_buffer) == -1) {
        spdlog::get("console")->warn("Could not get netmask for device {0}: {1}",
                interface_name, error_buffer);
        network_ = 0;
        subnet_mask_ = 0;
    }

    handle_ = pcap_open_live(interface_name, conf_snap_len, 1, 1000,
            error_buffer);
    if (handle_ == NULL) {
        std::ostringstream exception_message;
        exception_message << "Couldn't open device " << interface_name << ": "
            << error_buffer;
        throw sniffer_exception { exception_message.str() };
    }

    if (pcap_datalink(handle_) != DLT_EN10MB) {
        std::ostringstream exception_message;
        exception_message << "Not an Ethernet device: " << interface_name;
        throw sniffer_exception { exception_message.str() };
    }
}

void PcapPacketSniffer::apply_filters() {
    char filter_expression[] = "ip";

    if (pcap_compile(handle_, &compiled_filter_expression_,
                filter_expression, 0, network_) == -1) {
        std::ostringstream exception_message;
        exception_message << "Couldn't parse filter " << filter_expression <<
            ": " << pcap_geterr(handle_);
        throw sniffer_exception { exception_message.str() };
    }

    if (pcap_setfilter(handle_, &compiled_filter_expression_) == -1) {
        std::ostringstream exception_message;
        exception_message << "Couldn't install filter " << filter_expression <<
            ": " << pcap_geterr(handle_);
        throw sniffer_exception { exception_message.str() };
    }
}

void PcapPacketSniffer::sniff() {
    pcap_loop(
            handle_,
            config_manager_->get_value<int>("sniffer", "packets_count"),
            on_packet_received,
            (u_char *)this);
}

void PcapPacketSniffer::on_packet_received(u_char* args,
        const struct pcap_pkthdr* header, const u_char* packet) {
    ((PcapPacketSniffer *)args)->on_packet_received_internal(header, packet);
}

void PcapPacketSniffer::on_packet_received_internal(const struct pcap_pkthdr* header,
        const u_char* packet) {
    std::unique_ptr<SniffedEntity> sniffed_entity { new SniffedEntity { packet } };
    notify(sniffed_entity.get());
}

PcapPacketSniffer::~PcapPacketSniffer() {
    pcap_freecode(&compiled_filter_expression_);
    pcap_close(handle_);
}
