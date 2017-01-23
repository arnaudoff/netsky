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

#include "core/server_commands/kill_command.h"

#include <map>
#include <string>
#include <vector>

#include "common/policy_bindings.h"
#include "core/server.h"

namespace sniffer {

namespace core {

namespace server_commands {

/**
 * @brief Constructs a KillServerCommand object.
 *
 * @param server A pointer to a Server object.
 *
 * @param serializer The SerializationManager to use for parsing the arguments.
 */
KillCommand::KillCommand(
    Server* server,
    const sniffer::common::serialization::SerializationMgr& serializer)
    : ServerCommand{"kill", server, serializer, true} {}

/**
 * @brief Parses the arguments for the kill command.
 *
 * @param data The raw data message.
 *
 * @return An empty map; so far kill requires no arguments.
 */
std::map<std::string, std::vector<std::string>> KillCommand::ParseArguments(
    const std::string& data) const {
  std::map<std::string, std::vector<std::string>> arguments{};
  return arguments;
}

/**
 * @brief Stops the underlying implementation of a Server.
 *
 * @param connection_id Unused, kept to keep up with the interface.
 *
 * @param args Also unused.
 */
void KillCommand::Execute(
    int connection_id, std::map<std::string, std::vector<std::string>> args) {
  server_->Stop();
}

}  // namespace server_commands

}  // namespace core

}  // namespace sniffer
