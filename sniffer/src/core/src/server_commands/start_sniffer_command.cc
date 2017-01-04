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

#include "core/server_commands/start_sniffer_command.h"

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"
#include "core/layer_stack.h"
#include "core/pcap_packet_sniffer.h"
#include "core/server.h"

namespace sniffer {

namespace core {

namespace server_commands {

/**
 * @brief Creates an instance of the PacketSniffer class depending on the
 * parameter specified.
 *
 * @param server A pointer to a Server instance denoting the Server object to
 * execute the command on.
 *
 * @param serializer The serializer to use for parsing the arguments of
 * the StartSnifferCommand
 *
 * @param ls The layer stack object that is to be passed to the PacketSniffer
 * instance that is to be created.
 */
StartSnifferCommand::StartSnifferCommand(
    Server* server,
    const sniffer::common::serialization::SerializationMgr& serializer,
    const LayerStack& ls)
    : layer_stack_{ls}, ServerCommand{"start-sniffer", server, serializer} {}

/**
 * @brief Parses the arguments required for the sniffer to be started.
 *
 * @param data The raw data message
 *
 * @return Map with arguments
 */
std::map<std::string, std::vector<std::string>>
StartSnifferCommand::ParseArguments(const std::string& data) const {
  std::map<std::string, std::vector<std::string>> arguments;

  sniffer::common::serialization::SerializedObject data_obj{data};

  arguments["interfaces"] = serializer_.ExtractValue<std::vector<std::string>>(
      data_obj, ServerCommand::name(), "interfaces");

  arguments["filters"] = serializer_.ExtractValue<std::vector<std::string>>(
      data_obj, ServerCommand::name(), "filters");

  arguments["shared"] = serializer_.ExtractValue<std::vector<std::string>>(
      data_obj, ServerCommand::name(), "shared");

  return arguments;
}

/**
 * @brief Starts a packet sniffer
 *
 * @param connection_id
 *
 * @param args
 */
void StartSnifferCommand::Execute(
    int connection_id, std::map<std::string, std::vector<std::string>> args) {
  auto interfaces = args["interfaces"];
  auto filters = args["filters"];
  auto shared = args["shared"];

  std::unique_ptr<PacketSniffer> sniffer = std::make_unique<PcapPacketSniffer>(
      interfaces, filters, shared, server_->config_manager(), layer_stack_,
      server_);

  server_->set_sniffer(std::move(sniffer));

  server_->sniffer()->Start();
}

}  // namespace server_commands

}  // namespace core

}  // namespace sniffer
