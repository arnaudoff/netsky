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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_INTERFACE_ADDRESS_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_INTERFACE_ADDRESS_H_

#include <memory>
#include <string>

#include "common/policy_bindings.h"
#include "common/serialization/serializable_entity.h"
#include "common/serialization/serialized_object.h"

namespace sniffer {

namespace common {

namespace addressing {

class IpAddress;

}  // namespace addressing

}  // namespace common

namespace core {

class InterfaceAddress
    : public sniffer::common::serialization::SerializableEntity {
  using IpAddressType = std::shared_ptr<sniffer::common::addressing::IpAddress>;

 public:
  InterfaceAddress(IpAddressType addr, IpAddressType bcast, IpAddressType dst,
                   IpAddressType netmask);

  ~InterfaceAddress() override;

  sniffer::common::addressing::IpAddress* address() const;

  void set_address(IpAddressType addr);

  sniffer::common::addressing::IpAddress* broadcast_address() const;

  void set_broadcast_address(IpAddressType bcast);

  sniffer::common::addressing::IpAddress* destination_address() const;

  void set_destination_address(IpAddressType dst);

  sniffer::common::addressing::IpAddress* netmask() const;

  void set_netmask(IpAddressType netmask);

  sniffer::common::serialization::SerializedObject Serialize(
      const sniffer::common::serialization::SerializationMgr& serializer)
      const override;

  std::string entity_name() const override;

 private:
  IpAddressType address_;
  IpAddressType broadcast_address_;
  IpAddressType destination_address_;
  IpAddressType netmask_;
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_INTERFACE_ADDRESS_H_
