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

#include <spdlog/spdlog.h>  // NOLINT

#include "core/interface.h"
#include "core/interface_retriever_exception.h"

namespace sniffer {

namespace core {

std::vector<Interface> PcapInterfaceRetriever::Retrieve() {
  spdlog::get("console")->info("Retrieving pcap interfaces..");

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

    spdlog::get("console")->info("Retrieved {0} (desc: {1})", name,
                                 description ? description : "none");

    Interface interface{name, description};

    pcap_addr_t* current_if_addresses = current_interface->addresses;
    pcap_addr_t* current_if_address;

    std::vector<InterfaceAddress> interface_addresses;

    for (current_if_address = current_if_addresses; current_if_address;
         current_if_address = current_if_address->next) {
      auto ip_addr = ip_addr_factory_.Parse(current_if_address->addr);
      if (ip_addr) {
        spdlog::get("console")->info("Retrieved IP address for {0}: {1}", name,
                                     ip_addr->data());
      }

      auto broad_addr = ip_addr_factory_.Parse(current_if_address->broadaddr);
      if (broad_addr) {
        spdlog::get("console")->info("Retrieved BA for {0}: {1}", name,
                                     broad_addr->data());
      }

      auto dst_addr = ip_addr_factory_.Parse(current_if_address->dstaddr);
      if (dst_addr) {
        spdlog::get("console")->info("Retrieved DA for {0}: {1}", name,
                                     dst_addr->data());
      }

      auto netmask = ip_addr_factory_.Parse(current_if_address->netmask);
      if (netmask) {
        spdlog::get("console")->info("Retrieved SM for {0}: {1}", name,
                                     netmask->data());
      }

      InterfaceAddress if_addr{std::move(ip_addr), std::move(broad_addr),
                               std::move(dst_addr), std::move(netmask)};

      interface_addresses.push_back(std::move(if_addr));
    }

    interface.set_addresses(interface_addresses);

    retrieved_interfaces.push_back(interface);
  }

  return retrieved_interfaces;
}

}  // namespace core

}  // namespace sniffer