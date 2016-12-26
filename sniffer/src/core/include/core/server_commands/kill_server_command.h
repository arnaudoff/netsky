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

#ifndef SNIFFER_SRC_CORE_SERVER_COMMANDS_KILL_SERVER_COMMAND_H_
#define SNIFFER_SRC_CORE_SERVER_COMMANDS_KILL_SERVER_COMMAND_H_

#include <map>
#include <string>
#include <vector>

#include "core/commands/server_command.h"

namespace sniffer {

namespace core {

namespace server_commands {

class KillServerCommand : public ServerCommand {
 public:
  KillServerCommand(Server* server, const SerializationMgr& serializer);

  ~KillServerCommand() {}

  std::map<std::string, std::vector<std::string>> ParseArguments(
      const std::string& data) const override;

  void Execute(const ConnectionData& con_data,
               std::map<std::string, std::vector<std::string>> args) override;
};

}  // namespace server_commands

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_SERVER_COMMANDS_KILL_SERVER_COMMAND_H_
