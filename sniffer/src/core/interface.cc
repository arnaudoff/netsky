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

namespace sniffer {

namespace core {

Interface::Interface(const char* name, const char* desc)
    : name_{name ? name : std::string()},
      description_{desc ? desc : std::string()} {}

Interface::~Interface() {}

std::string Interface::name() const { return name_; }

std::string Interface::description() const { return description_; }

void Interface::set_addresses(std::vector<InterfaceAddress> addresses) {
  addresses_ = addresses;
}

// TODO(arnaudoff): Replace with iterator
std::vector<InterfaceAddress> Interface::addresses() const {
  return addresses_;
}

SerializedObject Interface::Serialize(
    const SerializationMgr& serializer) const {
  auto obj = serializer.create_object();
  serializer.SetValue<std::string>(obj, "name", name_);

  if (!description_.empty()) {
    serializer.SetValue<std::string>(obj, "description", description_);
  }

  for (const auto addr : addresses_) {
    auto addr_obj = addr.Serialize(serializer);

    if (!serializer.IsEmpty(addr_obj)) {
      serializer.AppendObject(obj, "addresses", addr_obj);
    }
  }

  return obj;
}

std::string Interface::entity_name() const { return name(); }

}  // namespace core

}  // namespace sniffer
