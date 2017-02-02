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

#include "core/interface.h"

#include <string>

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"
#include "core/interface_address.h"

namespace sniffer {

namespace core {

/**
 * @brief Constructs an Interface object.
 *
 * @param name The name of the interface, e.g. eth0
 * @param desc Description of the interface
 */
Interface::Interface(const char* name, const char* desc)
    : name_{name ? name : std::string()},
      description_{desc ? desc : std::string()} {}

/**
 * @brief Destructs an Interface object.
 */
Interface::~Interface() {}

/**
 * @brief Retrieves the name of this interface.
 *
 * @return String representation of the interface name.
 */
std::string Interface::name() const { return name_; }

/**
 * @brief Retrieves the description of this interface.
 *
 * @return String representing the description for this interface.
 */
std::string Interface::description() const { return description_; }

/**
 * @brief Adds an address to the collection of addresses for the interface.
 *
 * @param addresses
 */
void Interface::AddAddress(const InterfaceAddress& address) {
  addresses_.push_back(address);
}

/**
 * @brief Retrieves the collection of addresses for this interface.
 *
 * @return A collection of addresses for the interface if any.
 */
std::vector<InterfaceAddress> Interface::addresses() const {
  return addresses_;
}

/**
 * @brief Serializes an interface.
 *
 * @param serializer The serializer to use for serializing the object.
 *
 * @return SerializedObject containing serialized interface fields.
 */
sniffer::common::serialization::SerializedObject Interface::Serialize(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", name_, &obj);

  if (!description_.empty()) {
    serializer.SetValue<std::string>("description", description_, &obj);
  }

  for (const auto addr : addresses_) {
    auto addr_obj = addr.Serialize(serializer);

    if (!serializer.IsEmpty(addr_obj)) {
      serializer.AppendObject("addresses", addr_obj, &obj);
    }
  }

  return obj;
}

/**
 * @brief Retrieves the entity name of the Interface, i.e. the name of the
 * interface.
 *
 * @return The entity name of the Interface.
 */
std::string Interface::entity_name() const { return name(); }

}  // namespace core

}  // namespace sniffer
