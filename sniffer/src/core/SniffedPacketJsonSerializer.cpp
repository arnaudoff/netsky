#include <iostream>
#include <nlohmann/json.hpp>

#include "include/SniffedPacketJsonSerializer.hpp"

#include "protocols/include/Ethernet.hpp"
#include "protocols/include/IPv4.hpp"
#include "protocols/include/TCP.hpp"
#include "sniffers/include/SniffedPacket.hpp"

using namespace Sniffer::Core::Protocols;
using namespace Sniffer::Core;
using namespace Sniffer::Core::Sniffers;

std::string SniffedPacketJsonSerializer::serialize(SniffedPacket* sniffed_packet) {
    Ethernet ethernet {sniffed_packet};

    std::cout << "mac src: " << ethernet.get_source_address() << std::endl;
    std::cout << "mac dst: " << ethernet.get_destination_address() << std::endl;

    IPv4 ip {sniffed_packet, Ethernet::FRAME_SIZE};

    std::cout << "ip src: " << ip.get_source() << std::endl;
    std::cout << "ip dst: " << ip.get_destination() << std::endl;

    if (ip.get_upper_layer_protocol() == IPPROTO_TCP) {
        TCP tcp {sniffed_packet,  Ethernet::FRAME_SIZE + ip.get_size()};
        std::cout << "tcp src port: " << tcp.get_source_port() << std::endl;
        std::cout << "tcp dst port: " << tcp.get_destination_port() << std::endl;
    }

    return "";
}
