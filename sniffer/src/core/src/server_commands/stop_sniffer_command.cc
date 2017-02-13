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

#include "core/server_commands/stop_sniffer_command.h"

#include <map>
#include <string>
#include <vector>

#include "common/policy_bindings.h"
#include "core/server.h"

namespace sniffer {

namespace core {

namespace server_commands {

/**
 * @brief Constructs a StopSnifferCommand object.
 *
 * @param server A pointer to a Server object.
 * @param serializer The SerializationManager to use for parsing the arguments.
 */
StopSnifferCommand::StopSnifferCommand(
    Server* server,
    const sniffer::common::serialization::SerializationMgr& serializer)
    : ServerCommand{"stop-sniffer", server, serializer, true} {}

/**
 * @brief Stops the current sniffing session.
 *
 * @param connection_id Unused, kept to keep up with the interface.
 * @param args Also unused.
 */
void StopSnifferCommand::Execute(int connection_id,
                             std::map<std::string, std::string> args) {
  server_->StopSniffer();
}

}  // namespace server_commands

}  // namespace core

}  // namespace sniffer
