#include <memory>
#include <spdlog/spdlog.h>

#include "core/include/PolicyBindings.hpp"
#include "core/include/PcapInterfaceRetriever.hpp"
#include "core/include/IpAddressFactory.hpp"

#include "communications/include/ServerCommandInvoker.hpp"

#include "communications/commands/include/KillServerCommand.hpp"
#include "communications/commands/include/RetrieveInterfacesCommand.hpp"
#include "communications/commands/include/StartPacketSnifferCommand.hpp"

#include "communications/include/WebSocketServer.hpp"
#include "communications/include/WebSocketServerActionHandler.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Utils;
using namespace Sniffer::Communications;
using namespace Sniffer::Communications::Commands;

void initialize_logger();

int main() {
    initialize_logger();

    std::unique_ptr<ServerCommandInvoker> invoker {
        new ServerCommandInvoker {}
    };

    std::unique_ptr<WebSocketServerActionHandler> action_handler {
        new WebSocketServerActionHandler { invoker.get() }
    };

    ConfigurationMgr config_manager;
    SerializationMgr serializer;
    PacketParser parser { serializer };

    std::unique_ptr<Server> server {
        new WebSocketServer { config_manager, std::move(action_handler) }
    };

    std::unique_ptr<ServerCommand> kill_cmd {
        new KillServerCommand { server.get(), serializer }
    };

    IpAddressFactory ip_addr_factory;

    std::unique_ptr<InterfaceRetriever> pcap_retriever {
        new PcapInterfaceRetriever { ip_addr_factory }
    };

    std::unique_ptr<ServerCommand> retrieve_iface_cmd {
        new RetrieveInterfacesCommand { server.get(), serializer, std::move(pcap_retriever) }
    };

    std::unique_ptr<ServerCommand> start_sniffer_cmd {
        new StartPacketSnifferCommand { server.get(), serializer, parser }
    };

    invoker->add_command(kill_cmd.get());
    invoker->add_command(retrieve_iface_cmd.get());
    invoker->add_command(start_sniffer_cmd.get());

    server->start(config_manager.get_value<int>("server", "port"));

    return 0;

}

void initialize_logger() {
    auto console_logger = spdlog::stdout_logger_mt("console", true);
    console_logger->info("Initialized Netsky 0.1.0");
}
