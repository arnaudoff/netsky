#include "include/StartPacketSnifferCommand.hpp"
#include "../../core/include/PcapPacketSniffer.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Communications::Serialization;
using namespace Sniffer::Communications::Commands;

StartPacketSnifferCommand::StartPacketSnifferCommand(
        Server* server,
        const SerializationMgr& serializer,
        const LayerStack& ls)
    : layer_stack_{ls}, ServerCommand{"start-packet-sniffer", server, serializer}
{}

std::map<std::string, std::vector<std::string>> StartPacketSnifferCommand::parse(
        const std::string& data) const {
    std::map<std::string, std::vector<std::string>> arguments;

    SerializedObject data_obj { data };

    arguments["interfaces"] = serializer_.get_value<std::vector<std::string>>(
            data_obj,
            ServerCommand::get_name(),
            "interfaces");

    arguments["filters"] = serializer_.get_value<std::vector<std::string>>(
            data_obj,
            ServerCommand::get_name(),
            "filters");

    arguments["shared"] = serializer_.get_value<std::vector<std::string>>(
            data_obj,
            ServerCommand::get_name(),
            "shared");

    return arguments;
}

void StartPacketSnifferCommand::execute(
        const ConnectionData& con_data,
        std::map<std::string, std::vector<std::string>> args) {
    auto interfaces = args["interfaces"];
    auto filters = args["filters"];
    auto shared = args["shared"];

    std::unique_ptr<PacketSniffer> sniffer {
        new PcapPacketSniffer {
            server_,
            interfaces,
            filters,
            shared,
            server_->get_config_manager(),
            layer_stack_
        }
    };

    server_->set_sniffer(std::move(sniffer));
}

