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

#include "core/response_models/authenticate_response_model.h"

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"

namespace sniffer {

namespace core {

namespace response_models {

AuthenticateResponseModel::AuthenticateResponseModel(bool is_authenticated)
    : is_authenticated_{is_authenticated} {}

sniffer::common::serialization::SerializedObject
AuthenticateResponseModel::Serialize(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto obj = serializer.CreateObject();

  serializer.SetValue<bool>("isAuthenticated", is_authenticated_, &obj);

  return obj;
}

std::string AuthenticateResponseModel::entity_name() const {
  return "authenticate";
}

AuthenticateResponseModel::~AuthenticateResponseModel() {}

}  // namespace response_models

}  // namespace core

}  // namespace sniffer
