#include "include/Server.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Communications;

Server::Server(const ConfigurationMgr& manager)
    : config_manager_{manager}, session_id_{0}
{};

void Server::set_sniffer(std::unique_ptr<PacketSniffer> sniffer) {
    sniffer_ = std::move(sniffer);
}

PacketSniffer* Server::get_sniffer() const {
    return sniffer_.get();
}

ConfigurationMgr Server::get_config_manager() const {
    return config_manager_;
}

