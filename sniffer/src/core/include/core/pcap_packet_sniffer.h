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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_PCAP_PACKET_SNIFFER_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_PCAP_PACKET_SNIFFER_H_

#include <string>
#include <vector>

#include <pcap/pcap.h>

#include "common/policy_bindings.h"
#include "core/packet_sniffer.h"

namespace sniffer {

namespace core {

class PcapPacketSniffer : public PacketSniffer {
 public:
  PcapPacketSniffer(const std::string& interface,
                    const std::string& filter,
                    const sniffer::common::config::ConfigurationMgr& config,
                    const LayerStack& stack, Server* server);

  ~PcapPacketSniffer() override;

 private:
  pcap_t* handle_;

  bpf_u_int32 subnet_mask_;

  bpf_u_int32 network_;

  struct bpf_program parsed_filters_;

  void PrepareInterfaces() override;

  void ParseFilters() override;

  void ApplyFilters() override;

  void Sniff() override;

  static void OnPacketReceived(u_char* args, const struct pcap_pkthdr* header,
                               const u_char* packet);

  void OnPacketReceivedInternal(const struct pcap_pkthdr* header,
                                const u_char* packet);
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_PCAP_PACKET_SNIFFER_H_
