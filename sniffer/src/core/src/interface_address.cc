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

namespace sniffer {

namespace core {

InterfaceAddress::InterfaceAddress(ip_addr_t addr, ip_addr_t bcast,
                                   ip_addr_t dst, ip_addr_t netmask)
    : address_{addr},
      broadcast_address_{bcast},
      destination_address_{dst},
      netmask_{netmask} {}

InterfaceAddress::~InterfaceAddress() {}

void InterfaceAddress::set_address(ip_addr_t addr) { address_ = addr; }

IpAddress* InterfaceAddress::address() const { return address_.get(); }

void InterfaceAddress::set_broadcast_address(ip_addr_t bcast) {
  broadcast_address_ = bcast;
}

IpAddress* InterfaceAddress::broadcast_address() const {
  return broadcast_address_.get();
}

void InterfaceAddress::set_destination_address(ip_addr_t dst) {
  destination_address_ = dst;
}

IpAddress* InterfaceAddress::destination_address() const {
  return destination_address_.get();
}

void InterfaceAddress::set_netmask(ip_addr_t netmask) { netmask_ = netmask; }

IpAddress* InterfaceAddress::netmask() const { return netmask_.get(); }

SerializedObject InterfaceAddress::Serialize(
    const SerializationMgr& serializer) const {
  auto obj = serializer.create_object();

  if (address_) {
    serializer.SetValue<const char*>(obj, "addr", address_->data());
  }

  if (broadcast_address_) {
    serializer.SetValue<const char*>(obj, "bcast_addr",
                                     broadcast_address_->data());
  }

  if (destination_address_) {
    serializer.SetValue<const char*>(obj, "dst_addr",
                                     destination_address_->data());
  }

  if (netmask_) {
    serializer.SetValue<const char*>(obj, "netmask", netmask_->data());
  }

  return obj;
}

std::string InterfaceAddress::entity_name() const {
  return address_ ? address_->data() : "none";
}

}  // namespace core

}  // namespace sniffer
