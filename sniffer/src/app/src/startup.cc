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

#include <unistd.h>

#include <map>

#include "spdlog/spdlog.h"

#include "common/addressing/ip_address_factory.h"
#include "common/policy_bindings.h"

#include "core/server_command_invoker.h"
#include "core/server_commands/authenticate_command.h"
#include "core/server_commands/has_host_command.h"
#include "core/server_commands/kill_command.h"
#include "core/server_commands/retrieve_interfaces_command.h"
#include "core/server_commands/start_sniffer_command.h"
#include "core/server_commands/stop_sniffer_command.h"

#include "core/websocket_server.h"
#include "core/websocket_server_event_handler.h"

#include "core/layer_stack.h"
#include "core/layers/application_layer.h"
#include "core/layers/data_link_layer.h"
#include "core/layers/network_layer.h"
#include "core/layers/transport_layer.h"

#include "core/hex_ascii_payload_interpreter.h"
#include "core/pcap_interface_retriever.h"

#include "protocols/headers/metadata/ethernet_header_metadata.h"
#include "protocols/headers/metadata/header_metadata.h"
#include "protocols/headers/metadata/internet_header_metadata.h"
#include "protocols/headers/metadata/transmission_control_header_metadata.h"
#include "protocols/headers/metadata/user_datagram_header_metadata.h"

int main() {
  namespace core = sniffer::core;
  namespace layers = sniffer::core::layers;
  namespace metadata = sniffer::protocols::headers::metadata;
  namespace serialization = sniffer::common::serialization;
  namespace config = sniffer::common::config;
  namespace addressing = sniffer::common::addressing;
  namespace commands = sniffer::core::server_commands;

  auto console_logger = spdlog::stdout_color_mt("console");

  if (getuid()) {
    console_logger->critical("You must be root in order to run the server.");
    return 1;
  }

  console_logger->info(
      "Initialized Netsky 0.1.0. You may use the client to connect.");

  // Initialize the serializer and configuration managers

  serialization::SerializationMgr serializer;
  config::ConfigurationMgr config_manager;

  // Initialize factories

  addressing::IpAddressFactory ip_addr_factory;

  // Data link layer specific initializations

  std::map<std::string, int> eth_lower_id_map = {{"physical", 1}};
  auto ethernet_metadata = std::make_unique<metadata::EthernetHeaderMetadata>(
      eth_lower_id_map, "EthernetHeader", 14, 14, false, 0, false);

  std::vector<std::unique_ptr<metadata::HeaderMetadata>>
      dll_supported_headers{};
  dll_supported_headers.push_back(std::move(ethernet_metadata));

  layers::DataLinkLayer dll{"datalink", serializer};
  dll.set_supported_headers(std::move(dll_supported_headers));

  // Network layer specific initializations

  std::map<std::string, int> ip_lower_id_map = {{"EthernetHeader", 0x800}};
  auto internet_metadata = std::make_unique<metadata::InternetHeaderMetadata>(
      ip_lower_id_map, "InternetHeader", 0, 20, true, 0, true);
  std::vector<std::unique_ptr<metadata::HeaderMetadata>> nl_supported_headers{};
  nl_supported_headers.push_back(std::move(internet_metadata));

  layers::NetworkLayer nl{"network", serializer};
  nl.set_supported_headers(std::move(nl_supported_headers));

  // Transport layer specific initialization

  std::map<std::string, int> tcp_lower_id_map = {{"InternetHeader", 0x06}};
  auto tcp_metadata =
      std::make_unique<metadata::TransmissionControlHeaderMetadata>(
          tcp_lower_id_map, "TransmissionControlHeader", 0, 20, true, 12, true);

  std::map<std::string, int> udp_lower_id_map = {{"InternetHeader", 0x11}};
  auto udp_metadata = std::make_unique<metadata::UserDatagramHeaderMetadata>(
      udp_lower_id_map, "UserDatagramHeader", 8, 8, false, 0, true);

  std::vector<std::unique_ptr<metadata::HeaderMetadata>> tl_supported_headers{};
  tl_supported_headers.push_back(std::move(tcp_metadata));
  tl_supported_headers.push_back(std::move(udp_metadata));

  layers::TransportLayer tl{"transport", serializer};
  tl.set_supported_headers(std::move(tl_supported_headers));

  auto hexascii_payload_interpreter =
      std::make_unique<core::HexAsciiPayloadInterpreter>();

  layers::ApplicationLayer al{"application", serializer,
                              std::move(hexascii_payload_interpreter)};

  // Build the protocol stack
  core::LayerStack ls;
  ls.AddLayer(&dll);
  ls.AddLayer(&nl);
  ls.AddLayer(&tl);
  ls.AddLayer(&al);

  auto invoker = std::make_unique<core::ServerCommandInvoker>();
  auto event_handler =
      std::make_unique<core::WebSocketServerEventHandler>(invoker.get());

  auto server = std::make_unique<core::WebSocketServer>(
      config_manager,
      config_manager.ExtractValue<std::string>("server", "password"),
      std::move(event_handler));

  auto pcap_retriever =
      std::make_unique<core::PcapInterfaceRetriever>(ip_addr_factory);

  // Commands for the server
  auto kill_cmd =
      std::make_unique<commands::KillCommand>(server.get(), serializer);
  auto retrieve_if_cmd = std::make_unique<commands::RetrieveInterfacesCommand>(
      server.get(), serializer, std::move(pcap_retriever));

  auto start_sniffer_cmd = std::make_unique<commands::StartSnifferCommand>(
      server.get(), serializer, ls);

  auto stop_sniffer_cmd = std::make_unique<commands::StopSnifferCommand>(
      server.get(), serializer);

  auto authenticate_cmd =
      std::make_unique<commands::AuthenticateCommand>(server.get(), serializer);

  auto hashost_cmd =
      std::make_unique<commands::HasHostCommand>(server.get(), serializer);

  invoker->AddCommand(kill_cmd.get());
  invoker->AddCommand(retrieve_if_cmd.get());
  invoker->AddCommand(start_sniffer_cmd.get());
  invoker->AddCommand(stop_sniffer_cmd.get());
  invoker->AddCommand(authenticate_cmd.get());
  invoker->AddCommand(hashost_cmd.get());

  server->Start(config_manager.ExtractValue<int>("server", "port"));

  return 0;
}
