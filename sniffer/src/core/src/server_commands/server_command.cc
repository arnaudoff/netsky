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

#include "core/server_commands/server_command.h"

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"
#include "core/server.h"

namespace sniffer {

namespace core {

namespace server_commands {

/**
 * @brief Constructs a ServerCommand object with a name, e.g. "start-sniffer",
 * a pointer to a Server object (which is the object to invoke the command on)
 * and a SerializationMgr that is to be used when matching the command.
 *
 * @param name The name of the command
 * @param server The Server object for which the command is registered
 * @param serializer The SerializationMgr to use
 * @param secure If set to true, the command is executed if and only if the
 * client that requires its invocation is in the list of authenticated clients
 */
ServerCommand::ServerCommand(
    const std::string& name, Server* server,
    const sniffer::common::serialization::SerializationMgr& serializer,
    bool secure)
    : name_{name}, server_{server}, serializer_{serializer}, secure_{secure} {}

/**
 * @brief Retrieves the name with which the command was registered
 *
 * @return The name of the command
 */
std::string ServerCommand::name() const { return name_; }

/**
 * @brief If true, the command requires authentication prior to its execution.
 *
 * @return True if secure, false otherwise.
 */
bool ServerCommand::secure() const { return secure_; }

/**
 * @brief Checks whether a certain message is a "command" message, e.g.
 *
 * { 'start-sniffer': { 'interface': 'eth0' } }
 *
 * would match for a command registered with name 'start-sniffer'.
 *
 * @param data The raw data to match
 *
 * @return True if matches, false otherwise.
 */
bool ServerCommand::Matches(const std::string& data) const {
  sniffer::common::serialization::SerializedObject data_obj{data};
  return serializer_.ObjectExists(data_obj, name());
}

/**
 * @brief Default implementation for commands with no arguments.
 *
 * @return An empty map.
 */
std::map<std::string, std::string> ServerCommand::ParseArguments(
    const std::string& data) const {
  std::map<std::string, std::string> empty;
  return empty;
}

}  // namespace server_commands

}  // namespace core

}  // namespace sniffer
