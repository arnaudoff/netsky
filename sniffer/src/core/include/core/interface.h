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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_INTERFACE_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_INTERFACE_H_

#include <string>
#include <vector>

#include "common/policy_bindings.h"
#include "common/serialization/serializable_entity.h"
#include "common/serialization/serialized_object.h"
#include "core/interface_address.h"

namespace sniffer {

namespace core {

class Interface : public sniffer::common::serialization::SerializableEntity {
 public:
  Interface(const char* name, const char* desc);

  ~Interface() override;

  std::string name() const;

  std::string description() const;

  void set_addresses(std::vector<InterfaceAddress> addresses);

  std::vector<InterfaceAddress> addresses() const;

  sniffer::common::serialization::SerializedObject Serialize(
      const sniffer::common::serialization::SerializationMgr& serializer)
      const override;

  std::string entity_name() const override;

 private:
  std::string name_;
  std::string description_;
  std::vector<InterfaceAddress> addresses_;
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_INTERFACE_H_
