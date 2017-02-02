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

#include "core/pcap_interface_retriever.h"

#include <pcap/pcap.h>

#include <sstream>
#include <utility>
#include <vector>

#include "spdlog/spdlog.h"  // NOLINT

#include "common/addressing/ip_address.h"
#include "common/addressing/ip_address_factory.h"
#include "core/interface.h"
#include "core/interface_retriever_exception.h"

namespace sniffer {

namespace core {

/**
 * @brief Constructs a PcapInterfaceRetriever object.
 *
 * @param factory The IpAddressFactory to use for creating IP addresses for
 * the interfaces.
 */
PcapInterfaceRetriever::PcapInterfaceRetriever(
    const sniffer::common::addressing::IpAddressFactory& factory)
    : InterfaceRetriever{factory} {}

/**
 * @brief Retrieves a collection of Interface objects.
 *
 * @return Collection of interfaces.
 */
std::vector<Interface> PcapInterfaceRetriever::Retrieve() {
  pcap_if_t* interfaces;
  pcap_if_t* current_interface;
  char error_buffer[PCAP_ERRBUF_SIZE];

  if (pcap_findalldevs(&interfaces, error_buffer) == -1) {
    std::ostringstream exception_message;
    exception_message << "Couldn't retrieve interfaces: " << error_buffer;
    throw InterfaceRetrieverException{exception_message.str()};
  }

  std::vector<Interface> retrieved_interfaces;

  for (current_interface = interfaces; current_interface;
       current_interface = current_interface->next) {
    char* name = current_interface->name;
    char* description = current_interface->description;

    Interface interface{name, description};

    pcap_addr_t* current_if_addresses = current_interface->addresses;
    pcap_addr_t* current_if_address;

    for (current_if_address = current_if_addresses; current_if_address;
         current_if_address = current_if_address->next) {
      auto ip_addr = ip_addr_factory_.Parse(current_if_address->addr);
      auto broad_addr = ip_addr_factory_.Parse(current_if_address->broadaddr);
      auto dst_addr = ip_addr_factory_.Parse(current_if_address->dstaddr);
      auto netmask = ip_addr_factory_.Parse(current_if_address->netmask);

      InterfaceAddress if_addr{std::move(ip_addr), std::move(broad_addr),
                               std::move(dst_addr), std::move(netmask)};

      interface.AddAddress(std::move(if_addr));
    }

    retrieved_interfaces.push_back(interface);
  }

  return retrieved_interfaces;
}

}  // namespace core

}  // namespace sniffer
