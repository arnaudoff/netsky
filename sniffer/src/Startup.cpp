#include <memory>
#include <spdlog/spdlog.h>

#include "core/include/PolicyBindings.hpp"
#include "core/include/ServerPacketSnifferObserver.hpp"
#include "core/communications/serialization/include/SerializationManager.hpp"

// Sniffers
#include "core/sniffers/include/PacketSniffer.hpp"
#include "core/sniffers/include/PcapPacketSniffer.hpp"

// Communications
#include "core/communications/commands/include/KillServerCommand.hpp"
#include "core/communications/include/ServerCommandInvoker.hpp"
#include "core/communications/include/WebSocketServer.hpp"
#include "core/communications/include/WebSocketServerActionHandler.hpp"

// Utils
#include "utils/include/ConfigurationManager.hpp"
#include "utils/include/FileStoragePolicy.hpp"
#include "utils/include/JsonFormattingPolicy.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Core::Sniffers;
using namespace Sniffer::Utils;
using namespace Sniffer::Core::Communications;
using namespace Sniffer::Core::Communications::Commands;

void initialize_logger();

int main() {
    initialize_logger();

    std::shared_ptr<ConfigManager> config_manager {
        new ConfigManager { "../config/config.json" }
    };

    std::unique_ptr<ServerCommandInvoker> invoker {
        new ServerCommandInvoker {}
    };

    std::unique_ptr<WebSocketServerActionHandler> action_handler {
        new WebSocketServerActionHandler { invoker.get() }
    };

    std::unique_ptr<Server> server {
        new WebSocketServer { config_manager, std::move(action_handler) }
    };

    std::unique_ptr<ServerCommand> kill_cmd {
        new KillServerCommand { server.get() }
    };

    invoker->add_command(kill_cmd.get());

    SerializationMgr serializer;

    std::unique_ptr<PacketSnifferObserver> server_observer {
        new ServerPacketSnifferObserver { server.get(), serializer }
    };

    std::unique_ptr<PacketSniffer> sniffer { new PcapPacketSniffer { config_manager } };
    sniffer->attach(server_observer.get());

    server->start(config_manager->get_value<int>("server", "port"));
    sniffer->start();

    return 0;

}

void initialize_logger() {
    auto console_logger = spdlog::stdout_logger_mt("console", true);
    console_logger->info("Initialized Netsky 0.1");
}
