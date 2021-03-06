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

#include "core/response_models/retrieve_interfaces_response_model.h"

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"
#include "core/interface.h"

namespace sniffer {

namespace core {

namespace response_models {

RetrieveInterfacesResponseModel::RetrieveInterfacesResponseModel(
    std::vector<Interface> interfaces)
    : interfaces_{interfaces} {}

sniffer::common::serialization::SerializedObject
RetrieveInterfacesResponseModel::Serialize(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto obj = serializer.CreateObject();

  for (const auto& iface : interfaces_) {
    auto iface_obj = iface.Serialize(serializer);
    serializer.AppendObject(entity_name(), iface_obj, &obj);
  }

  return obj;
}

std::string RetrieveInterfacesResponseModel::entity_name() const {
  return "interfaces";
}

RetrieveInterfacesResponseModel::~RetrieveInterfacesResponseModel() {}

}  // namespace response_models

}  // namespace core

}  // namespace sniffer
