/*
 * Copyright (C) 2017  Ivaylo Arnaudov <ivaylo.arnaudov12@gmail.com>
 * Author: Ivaylo Arnaudov <ivaylo.arnaudov12@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "spdlog/spdlog.h"

#include "common/addressing/ip_address_factory.h"
#include "common/policy_bindings.h"

#include "core/server_command_invoker.h"
#include "core/server_commands/kill_command.h"
#include "core/server_commands/retrieve_interfaces_command.h"
#include "core/server_commands/start_sniffer_command.h"
#include "core/websocket_server.h"
#include "core/websocket_server_event_handler.h"

#include "core/layer_stack.h"
#include "core/layers/application_layer.h"
#include "core/layers/data_link_layer.h"
#include "core/layers/network_layer.h"
#include "core/layers/transport_layer.h"
#include "core/pcap_interface_retriever.h"

#include "protocols/headers/ethernet_header.h"
#include "protocols/headers/internet_header.h"
#include "protocols/headers/metadata/ethernet_header_metadata.h"
#include "protocols/headers/metadata/header_metadata.h"
#include "protocols/headers/metadata/internet_header_metadata.h"
#include "protocols/headers/metadata/transmission_control_header_metadata.h"
#include "protocols/headers/transmission_control_header.h"

// Common
using sniffer::common::serialization::SerializationMgr;
using sniffer::common::config::ConfigurationMgr;
using sniffer::common::addressing::IpAddressFactory;
using sniffer::core::PcapInterfaceRetriever;

// Layers
using sniffer::core::LayerStack;
using sniffer::core::layers::DataLinkLayer;
using sniffer::core::layers::NetworkLayer;
using sniffer::core::layers::TransportLayer;
using sniffer::core::layers::ApplicationLayer;

// Headers
using sniffer::protocols::headers::EthernetHeader;
using sniffer::protocols::headers::InternetHeader;
using sniffer::protocols::headers::TransmissionControlHeader;

// Headers metadata
using sniffer::protocols::headers::metadata::HeaderMetadata;
using sniffer::protocols::headers::metadata::EthernetHeaderMetadata;
using sniffer::protocols::headers::metadata::InternetHeaderMetadata;
using sniffer::protocols::headers::metadata::TransmissionControlHeaderMetadata;

// Server
using sniffer::core::WebSocketServerEventHandler;
using sniffer::core::WebSocketServer;

// Commands
using sniffer::core::ServerCommandInvoker;
using sniffer::core::server_commands::KillCommand;
using sniffer::core::server_commands::StartSnifferCommand;
using sniffer::core::server_commands::RetrieveInterfacesCommand;

int main() {
  auto console_logger = spdlog::stdout_logger_mt("console");
  console_logger->info("Initialized Netsky 0.1.0");

  // Initialize the serializer and configuration managers

  SerializationMgr serializer;
  ConfigurationMgr config_manager;

  // Initialize factories

  IpAddressFactory ip_addr_factory;

  // Data link layer specific initializations

  auto ethernet_metadata = std::make_unique<EthernetHeaderMetadata>(
      1, "EthernetHeader", 14, false, 0);

  std::vector<std::unique_ptr<HeaderMetadata>> dll_supported_headers{};
  dll_supported_headers.push_back(std::move(ethernet_metadata));

  DataLinkLayer dll{"datalink", serializer};
  dll.set_supported_headers(std::move(dll_supported_headers));

  // Network layer specific initializations

  auto internet_metadata = std::make_unique<InternetHeaderMetadata>(
      0x800, "InternetHeader", 0, true, 0);
  std::vector<std::unique_ptr<HeaderMetadata>> nl_supported_headers{};
  nl_supported_headers.push_back(std::move(internet_metadata));

  NetworkLayer nl{"network", serializer};
  nl.set_supported_headers(std::move(nl_supported_headers));

  // Transport layer specific initialization

  auto tcp_metadata = std::make_unique<TransmissionControlHeaderMetadata>(
      0x06, "TransmissionControlHeader", 0, true, 0);
  std::vector<std::unique_ptr<HeaderMetadata>> tl_supported_headers{};
  tl_supported_headers.push_back(std::move(tcp_metadata));

  TransportLayer tl{"transport", serializer};
  tl.set_supported_headers(std::move(tl_supported_headers));

  ApplicationLayer al{"application", serializer};

  // Build the protocol stack

  LayerStack ls;
  ls.AddLayer(&dll);
  ls.AddLayer(&nl);
  ls.AddLayer(&tl);
  ls.AddLayer(&al);

  auto invoker = std::make_unique<ServerCommandInvoker>();
  auto event_handler =
      std::make_unique<WebSocketServerEventHandler>(invoker.get());

  auto server = std::make_unique<WebSocketServer>(
      config_manager, std::move(event_handler),
      config_manager.ExtractValue<std::string>("server", "password"));

  auto pcap_retriever =
      std::make_unique<PcapInterfaceRetriever>(ip_addr_factory);

  // Commands for the server

  auto kill_cmd = std::make_unique<KillCommand>(server.get(), serializer);

  auto retrieve_if_cmd = std::make_unique<RetrieveInterfacesCommand>(
      server.get(), serializer, std::move(pcap_retriever));

  auto start_sniffer_cmd =
      std::make_unique<StartSnifferCommand>(server.get(), serializer, ls);

  invoker->AddCommand(kill_cmd.get());
  invoker->AddCommand(retrieve_if_cmd.get());
  invoker->AddCommand(start_sniffer_cmd.get());

  server->Start(config_manager.ExtractValue<int>("server", "port"));

  return 0;
}
