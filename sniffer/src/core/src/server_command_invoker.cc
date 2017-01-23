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

#include "core/server_command_invoker.h"

#include "spdlog/spdlog.h"  // NOLINT

#include "core/server.h"
#include "core/server_commands/server_command.h"

namespace sniffer {

namespace core {

/**
 * @brief Adds a ServerCommand to the internal list of commands.
 *
 * @param command Pointer to a ServerCommand object that is the command to add
 */
void ServerCommandInvoker::AddCommand(server_commands::ServerCommand* command) {
  server_commands_.insert(command);
}

/**
 * @brief Iterates over the list of registered commands and if it matches,
 * executes it by passing it the client for which to execute it and the command
 * arguments. If a secure command, it is invoked if and only if the client is
 * in the authenticated list of the server.
 *
 * @param server A pointer to the server instance.
 * @param connection_id A connection ID representing the client session.
 * @param message The raw message from the client.
 */
void ServerCommandInvoker::Invoke(Server* server, int connection_id,
                                  const std::string& message) {
  for (auto command : server_commands_) {
    if (command->Matches(message)) {
      spdlog::get("console")->info("Invoking command {0} for client {1}",
                                   command->name(), connection_id);

      if (command->secure()) {
        if (server->IsClientAuthenticated(connection_id)) {
          command->Execute(connection_id, command->ParseArguments(message));
        }

        // TODO(arnaudoff): Log unauthorized attempt
      } else {
        command->Execute(connection_id, command->ParseArguments(message));
      }
    }
  }
}

}  // namespace core

}  // namespace sniffer
