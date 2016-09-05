#include "include/PacketSniffer.hpp"

using namespace Sniffer::Core;

PacketSniffer::PacketSniffer(std::shared_ptr<ConfigManager> manager)
    : config_manager_{manager}
{}

void PacketSniffer::start() {
    prepare_interface();
    apply_filters();
    sniff();
}
