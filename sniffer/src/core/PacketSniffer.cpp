#include "include/PacketSniffer.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Communications;

PacketSniffer::PacketSniffer(
        Server* server,
        std::vector<std::string> interfaces,
        std::vector<std::string> filters,
        std::vector<std::string> shared,
        const ConfigurationMgr& config,
        const PacketParser& parser)
    : server_{server},
    interfaces_{interfaces},
    filters_{filters},
    shared_{shared},
    config_manager_{config},
    packet_parser_{parser}
{}

void PacketSniffer::start() {
    prepare_interface();
    parse_filters();
    apply_filters();
    sniff();
}
