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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_SERVER_COMMANDS_SERVER_COMMAND_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_SERVER_COMMANDS_SERVER_COMMAND_H_

#include <map>
#include <string>
#include <vector>

#include "common/policy_bindings.h"

namespace sniffer {

namespace core {

class Server;

namespace server_commands {

class ServerCommand {
 public:
  ServerCommand(
      const std::string& name, Server* server,
      const sniffer::common::serialization::SerializationMgr& serializer,
      bool secure);

  virtual ~ServerCommand() {}

  std::string name() const;

  bool secure() const;

  bool Matches(const std::string& data) const;

  virtual std::map<std::string, std::string> ParseArguments(
      const std::string& data) const;

  virtual void Execute(
      int connection_id,
      std::map<std::string, std::string> args) = 0;

 protected:
  std::string name_;

  bool secure_;

  Server* server_;

  sniffer::common::serialization::SerializationMgr serializer_;
};

}  // namespace server_commands

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_SERVER_COMMANDS_SERVER_COMMAND_H_
