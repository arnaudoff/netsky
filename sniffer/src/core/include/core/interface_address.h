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

#ifndef SNIFFER_SRC_CORE_INTERFACE_ADDRESS_H_
#define SNIFFER_SRC_CORE_INTERFACE_ADDRESS_H_

#include <memory>
#include <string>

#include "common/addressing/ipv4_address.h"
#include "common/serialization/serializable_entity.h"
#include "common/serialization/serialized_object.h"

namespace sniffer {

namespace core {

class InterfaceAddress
    : public sniffer::common::serialization::SerializableEntity {
 public:
  InterfaceAddress(ip_addr_t addr, ip_addr_t bcast, ip_addr_t dst,
                   ip_addr_t netmask);

  ~InterfaceAddress() override;

  sniffer::common::addressing::IpAddress* address() const;

  void set_address(ip_addr_t addr);

  sniffer::common::addressing::IpAddress* broadcast_address() const;

  void set_broadcast_address(ip_addr_t bcast);

  sniffer::common::addressing::IpAddress* destination_address() const;

  void set_destination_address(ip_addr_t dst);

  sniffer::common::addressing::IpAddress* netmask() const;

  void set_netmask(ip_addr_t netmask);

  sniffer::common::serialization::SerializedObject Serialize(
      const SerializationMgr& serializer) const override;

  std::string entity_name() const override;

 private:
  typedef std::shared_ptr<sniffer::common::addressing::IpAddress> ip_addr_t;

  ip_addr_t address_;
  ip_addr_t broadcast_address_;
  ip_addr_t destination_address_;
  ip_addr_t netmask_;
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INTERFACE_ADDRESS_H_
