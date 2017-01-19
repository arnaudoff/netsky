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

#include "core/server_commands/authenticate_command.h"

#include <map>
#include <string>
#include <vector>

#include "common/policy_bindings.h"
#include "core/response_models/authenticate_response_model.h"
#include "core/server.h"

namespace sniffer {

namespace core {

namespace server_commands {

/**
 * @brief Constructs an AuthenticateCommand object.
 *
 * @param server A pointer to a Server object.
 * @param serializer The SerializationManager to use for parsing the arguments.
 */
AuthenticateCommand::AuthenticateCommand(
    Server* server,
    const sniffer::common::serialization::SerializationMgr& serializer)
    : ServerCommand{"authenticate", server, serializer} {}

/**
 * @brief Parses the arguments for the authenticate command.
 *
 * @param data The raw data message.
 *
 * @return
 */
std::map<std::string, std::vector<std::string>>
AuthenticateCommand::ParseArguments(const std::string& data) const {
  std::map<std::string, std::vector<std::string>> arguments{};

  sniffer::common::serialization::SerializedObject data_obj {data};
  arguments["password"] = serializer_.ExtractValue<std::vector<std::string>>(
      data_obj, ServerCommand::name(), "password");
  return arguments;
}

/**
 * @brief Checks whether the client is submitted the right password
 *
 * @param connection_id Unused, kept to keep up with the interface.
 * @param args Also unused.
 */
void AuthenticateCommand::Execute(
    int connection_id, std::map<std::string, std::vector<std::string>> args) {
  auto is_authenticated = (server_->password() == args["password"]);

  sniffer::core::response_models::AuthenticateResponseModel model{is_authenticated};
  auto model_obj = model.Serialize(serializer_);

  server_->Unicast(connection_id, model_obj.data());
}

}  // namespace server_commands

}  // namespace core

}  // namespace sniffer
