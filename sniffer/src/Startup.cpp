#include <memory>
#include <spdlog/spdlog.h>

#include "core/include/PolicyBindings.hpp"
#include "core/include/PcapInterfaceRetriever.hpp"
#include "core/addressing/include/IpAddressFactory.hpp"

#include "communications/include/ServerCommandInvoker.hpp"

#include "communications/commands/include/KillServerCommand.hpp"
#include "communications/commands/include/RetrieveInterfacesCommand.hpp"
#include "communications/commands/include/StartPacketSnifferCommand.hpp"

#include "communications/include/WebSocketServer.hpp"
#include "communications/include/WebSocketServerActionHandler.hpp"

#include "core/layers/include/DataLinkLayer.hpp"
#include "core/layers/include/NetworkLayer.hpp"
#include "core/layers/include/TransportLayer.hpp"
#include "core/layers/include/ApplicationLayer.hpp"
#include "core/include/LayerStack.hpp"

#include "protocols/headers/metadata/include/HeaderMetadata.hpp"
#include "protocols/headers/metadata/include/EthernetHeaderMetadata.hpp"
#include "protocols/headers/metadata/include/InternetHeaderMetadata.hpp"
#include "protocols/headers/metadata/include/TransmissionControlHeaderMetadata.hpp"

#include "protocols/headers/include/EthernetHeader.hpp"
#include "protocols/headers/include/InternetHeader.hpp"
#include "protocols/headers/include/TransmissionControlHeader.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Core::Layers;
using namespace Sniffer::Core::Addressing;

using namespace Sniffer::Communications;
using namespace Sniffer::Communications::Commands;

using namespace Sniffer::Protocols::Headers;
using namespace Sniffer::Protocols::Headers::Metadata;

using namespace Sniffer::Utils;

int main() {
    auto console_logger = spdlog::stdout_logger_mt("console", true);
    console_logger->info("Initialized Netsky 0.1.0");

    // Data link layer specific initializations
    EthernetHeader::register_class("EthernetHeader");
    auto ethernet_metadata =
        std::make_unique<EthernetHeaderMetadata>(1, "EthernetHeader", 14, false, 0);

    std::vector<std::unique_ptr<HeaderMetadata>> dll_supported_headers {};
    dll_supported_headers.push_back(std::move(ethernet_metadata));

    SerializationMgr serializer;
    HeaderFactory hfactory;

    DataLinkLayer dll { serializer, hfactory };
    dll.set_supported_headers(std::move(dll_supported_headers));

    // Network layer specific initializations
    InternetHeader::register_class("InternetHeader");
    auto internet_metadata =
        std::make_unique<InternetHeaderMetadata>(2, "InternetHeader", 0, true, 0);
    std::vector<std::unique_ptr<HeaderMetadata>> nl_supported_headers {};
    nl_supported_headers.push_back(std::move(internet_metadata));

    NetworkLayer nl { serializer, hfactory };
    nl.set_supported_headers(std::move(nl_supported_headers));

    // Transport layer specific initialization
    TransmissionControlHeader::register_class("TransmissionControlHeader");
    auto tcp_metadata = std::make_unique<TransmissionControlHeaderMetadata>(
            3, "TransmissionControlHeader", 0, true, 0);
    std::vector<std::unique_ptr<HeaderMetadata>> tl_supported_headers {};
    tl_supported_headers.push_back(std::move(tcp_metadata));

    TransportLayer tl { serializer, hfactory };
    tl.set_supported_headers(std::move(tl_supported_headers));

    ApplicationLayer al { serializer, hfactory };

    LayerStack ls;
    ls.add_layer(&dll);
    ls.add_layer(&nl);
    ls.add_layer(&tl);
    ls.add_layer(&al);

    auto invoker = std::make_unique<ServerCommandInvoker>();
    auto action_handler =
        std::make_unique<WebSocketServerActionHandler>(invoker.get());

    ConfigurationMgr config_manager;
    auto server =
        std::make_unique<WebSocketServer>(config_manager, std::move(action_handler));

    auto kill_cmd = std::make_unique<KillServerCommand>(server.get(), serializer);

    IpAddressFactory ip_addr_factory;
    auto pcap_retriever = std::make_unique<PcapInterfaceRetriever>(ip_addr_factory);
    auto retrieve_if_cmd = std::make_unique<RetrieveInterfacesCommand>(
            server.get(),
            serializer,
            std::move(pcap_retriever));
    auto start_sniffer_cmd =
        std::make_unique<StartPacketSnifferCommand>(server.get(), serializer, ls);

    invoker->add_command(kill_cmd.get());
    invoker->add_command(retrieve_if_cmd.get());
    invoker->add_command(start_sniffer_cmd.get());

    server->start(config_manager.get_value<int>("server", "port"));
    return 0;

}
