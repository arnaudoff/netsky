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

#include "core/interface_address.h"

#include "common/addressing/ip_address.h"
#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"

namespace sniffer {

namespace core {

InterfaceAddress::InterfaceAddress(IpAddressType addr, IpAddressType bcast,
                                   IpAddressType dst, IpAddressType netmask)
    : address_{addr},
      broadcast_address_{bcast},
      destination_address_{dst},
      netmask_{netmask} {}

InterfaceAddress::~InterfaceAddress() {}

void InterfaceAddress::set_address(IpAddressType addr) { address_ = addr; }

sniffer::common::addressing::IpAddress* InterfaceAddress::address() const {
  return address_.get();
}

void InterfaceAddress::set_broadcast_address(IpAddressType bcast) {
  broadcast_address_ = bcast;
}

sniffer::common::addressing::IpAddress* InterfaceAddress::broadcast_address()
    const {
  return broadcast_address_.get();
}

void InterfaceAddress::set_destination_address(IpAddressType dst) {
  destination_address_ = dst;
}

sniffer::common::addressing::IpAddress* InterfaceAddress::destination_address()
    const {
  return destination_address_.get();
}

void InterfaceAddress::set_netmask(IpAddressType netmask) {
  netmask_ = netmask;
}

sniffer::common::addressing::IpAddress* InterfaceAddress::netmask() const {
  return netmask_.get();
}

sniffer::common::serialization::SerializedObject InterfaceAddress::Serialize(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto obj = serializer.CreateObject();

  if (address_) {
    serializer.SetValue<const char*>("addr", address_->data(), &obj);
  }

  if (broadcast_address_) {
    serializer.SetValue<const char*>("bcast_addr", broadcast_address_->data(),
                                     &obj);
  }

  if (destination_address_) {
    serializer.SetValue<const char*>("dst_addr", destination_address_->data(),
                                     &obj);
  }

  if (netmask_) {
    serializer.SetValue<const char*>("netmask", netmask_->data(), &obj);
  }

  return obj;
}

std::string InterfaceAddress::entity_name() const {
  return address_ ? address_->data() : "none";
}

}  // namespace core

}  // namespace sniffer
