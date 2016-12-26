/*
 * Copyright (C) 2016  Ivaylo Arnaudov <ivaylo.arnaudov12@gmail.com>
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

#include "core/server_commands/start_packet_sniffer_command.h"

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "core/layer_stack.h"
#include "core/pcap_packet_sniffer.h"
#include "core/server.h"

namespace sniffer {

namespace core {

namespace server_commands {

StartPacketSnifferCommand::StartPacketSnifferCommand(
    Server* server, const SerializationMgr& serializer, const LayerStack& ls)
    : layer_stack_{ls},
      ServerCommand{"start-packet-sniffer", server, serializer} {}

std::map<std::string, std::vector<std::string>>
StartPacketSnifferCommand::ParseArguments(const std::string& data) const {
  std::map<std::string, std::vector<std::string>> arguments;

  SerializedObject data_obj{data};

  arguments["interfaces"] = serializer_.ExtractValue<std::vector<std::string>>(
      data_obj, ServerCommand::name(), "interfaces");

  arguments["filters"] = serializer_.ExtractValue<std::vector<std::string>>(
      data_obj, ServerCommand::name(), "filters");

  arguments["shared"] = serializer_.ExtractValue<std::vector<std::string>>(
      data_obj, ServerCommand::name(), "shared");

  return arguments;
}

void StartPacketSnifferCommand::Execute(
    const ConnectionData& con_data,
    std::map<std::string, std::vector<std::string>> args) {
  auto interfaces = args["interfaces"];
  auto filters = args["filters"];
  auto shared = args["shared"];

  std::unique_ptr<PacketSniffer> sniffer{
      new PcapPacketSniffer{server_, interfaces, filters, shared,
                            server_->get_config_manager(), layer_stack_}};

  server_->set_sniffer(std::move(sniffer));
}

}  // namespace server_commands

}  // namespace core

}  // namespace sniffer
