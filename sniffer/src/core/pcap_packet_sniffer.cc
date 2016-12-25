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

#include "core/pcap_packet_sniffer.h"

#include <algorithm>
#include <iterator>
#include <sstream>

#include <spdlog/spdlog.h>  // NOLINT

#include "common/serialization/serialized_object.h"
#include "core/packet_region.h"
#include "core/server.h"
#include "core/sniffed_packet.h"
#include "core/sniffer_exception.h"

namespace sniffer {

namespace core {

PcapPacketSniffer::PcapPacketSniffer(std::vector<std::string> interfaces,
                                     std::vector<std::string> filters,
                                     std::vector<std::string> shared,
                                     const ConfigurationMgr& config,
                                     const LayerStack& stack, Server* server)
    : PacketSniffer(interfaces, filters, shared, config, stack, server) {}

void PcapPacketSniffer::PrepareInterfaces() {
  char error_buffer[PCAP_ERRBUF_SIZE];

  // TODO(arnaudoff): Fix when multiple interfaces are supported
  const char* interface_name = interfaces_[0].c_str();

  if (pcap_lookupnet(interface_name, &network_, &subnet_mask_, error_buffer) ==
      -1) {
    spdlog::get("console")->warn("Could not get netmask for device {0}: {1}",
                                 interface_name, error_buffer);
    network_ = 0;
    subnet_mask_ = 0;
  }

  int snap_len = config_manager_.ExtractValue<int>("sniffer", "snap_len");

  handle_ = pcap_open_live(interface_name, snap_len, 1, 1000, error_buffer);
  if (handle_ == NULL) {
    std::ostringstream exception_message;
    exception_message << "Couldn't open device " << interface_name << ": "
                      << error_buffer;
    throw SnifferException{exception_message.str()};
  }

  if (pcap_datalink(handle_) != DLT_EN10MB) {
    std::ostringstream exception_message;
    exception_message << "Not an Ethernet device: " << interface_name;
    throw SnifferException{exception_message.str()};
  }
}

void PcapPacketSniffer::ParseFilters() {
  std::ostringstream filters;
  std::copy(filters_.begin(), filters_.end() - 1,
            std::ostream_iterator<std::string>(filters, ";"));
  filters << filters_.back();

  if (pcap_compile(handle_, &parsed_filters_, filters.str().c_str(), 0,
                   network_) == -1) {
    std::ostringstream exception_message;
    exception_message << "Couldn't parse filters " << filters.str() << ": "
                      << pcap_geterr(handle_);
    throw SnifferException{exception_message.str()};
  }
}

void PcapPacketSniffer::ApplyFilters() {
  if (pcap_setfilter(handle_, &parsed_filters_) == -1) {
    std::ostringstream exception_message;
    exception_message << "Couldn't apply filters ";
    std::copy(filters_.begin(), filters_.end() - 1,
              std::ostream_iterator<std::string>(exception_message, ","));
    exception_message << filters_.back() << ": " << pcap_geterr(handle_);
    throw SnifferException{exception_message.str()};
  }
}

void PcapPacketSniffer::Sniff() {
  pcap_loop(handle_,
            config_manager_.ExtractValue<int>("sniffer", "packets_count"),
            OnPacketReceived, reinterpret_cast<u_char*>(this);
}

void PcapPacketSniffer::OnPacketReceived(u_char* args,
                                         const struct pcap_pkthdr* header,
                                         const u_char* packet) {
  (reinterpret_cast<PcapPacketSniffer*>(args))
      ->OnPacketReceivedInternal(header, packet);
}

void PcapPacketSniffer::OnPacketReceivedInternal(
    const struct pcap_pkthdr* header, const u_char* packet) {
  PacketRegion body{0, static_cast<int>(header->caplen)};

  SniffedPacket packet_obj{packet, body};
  SerializedObject accumulator_obj{"{}"};

  // http://www.tcpdump.org/linktypes.html
  stack_.HandleReception(accumulator_obj, 1, packet_obj);
  server_->broadcast(accumulator_obj.data());
}

PcapPacketSniffer::~PcapPacketSniffer() {
  pcap_freecode(&parsed_filters_);
  pcap_close(handle_);
}

}  // namespace core

}  // namespace sniffer
