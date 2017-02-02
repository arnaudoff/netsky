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

#include "core/server_commands/retrieve_interfaces_command.h"

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "common/policy_bindings.h"
#include "core/interface_retriever.h"
#include "core/response_models/retrieve_interfaces_response_model.h"
#include "core/server.h"

namespace sniffer {

namespace core {

namespace server_commands {

/**
 * @brief Constructs a RetrieveInterfacesCommand object.
 *
 * @param server The server to use.
 * @param serializer The SerializationManager to use.
 * @param retriever The InterfaceRetriever to use.
 */
RetrieveInterfacesCommand::RetrieveInterfacesCommand(
    Server* server,
    const sniffer::common::serialization::SerializationMgr& serializer,
    std::unique_ptr<InterfaceRetriever> retriever)
    : ServerCommand{"retrieve-interfaces", server, serializer, true},
      interface_retriever_{std::move(retriever)} {}

/**
 * @brief Retrieves the interfaces from the underlying InterfaceRetriever,
 * instantiates a response model, serializes it and unicasts the interfaces to
 * the client that requested their retrieval.
 *
 * @param connection_id The connection ID of the client.
 * @param args
 */
void RetrieveInterfacesCommand::Execute(
    int connection_id, std::map<std::string, std::string> args) {
  auto interfaces = interface_retriever_->Retrieve();

  sniffer::core::response_models::RetrieveInterfacesResponseModel model{
      interfaces};
  auto model_obj = model.Serialize(serializer_);

  server_->Unicast(connection_id, model_obj.data());
}

}  // namespace server_commands

}  // namespace core

}  // namespace sniffer
