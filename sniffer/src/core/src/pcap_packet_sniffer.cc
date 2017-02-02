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

#include <pcap/pcap.h>

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include <spdlog/spdlog.h>  // NOLINT

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"
#include "core/server.h"
#include "core/sniffer_exception.h"
#include "protocols/packet_region.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace core {

/**
 * @brief Constructs a packet sniffer based on libpcap.
 *
 * @param interface The interface to sniff on.
 * @param filter Filter to apply.
 * @param config An instance of a configuration manager.
 * @param stack The LayerStack to use for the packet parsing process.
 * @param server A pointer to the server which to use for transmission.
 */
PcapPacketSniffer::PcapPacketSniffer(
    const std::string& interface, const std::string& filter,
    const sniffer::common::config::ConfigurationMgr& config,
    const LayerStack& stack, Server* server)
    : PacketSniffer(interface, filter, config, stack, server) {}

/**
 * @brief Prepares the physical interfaces to sniff on
 */
void PcapPacketSniffer::PrepareInterfaces() {
  char error_buffer[PCAP_ERRBUF_SIZE];

  const char* interface = interface_.c_str();

  if (pcap_lookupnet(interface, &network_, &subnet_mask_, error_buffer) == -1) {
    spdlog::get("console")->warn("Could not get netmask for device {0}: {1}",
                                 interface, error_buffer);
    network_ = 0;
    subnet_mask_ = 0;
  }

  int snap_len = config_manager_.ExtractValue<int>("sniffer", "snap_len");

  handle_ = pcap_open_live(interface, snap_len, 1, 1000, error_buffer);
  if (handle_ == NULL) {
    std::ostringstream exception_message;
    exception_message << "Couldn't open device " << interface << ": "
                      << error_buffer;
    throw SnifferException{exception_message.str()};
  }

  if (pcap_datalink(handle_) != DLT_EN10MB) {
    std::ostringstream exception_message;
    exception_message << "Not an Ethernet device: " << interface;
    throw SnifferException{exception_message.str()};
  }
}

/**
 * @brief Parses any filters by passing them to pcap_compile
 */
void PcapPacketSniffer::ParseFilters() {
  if (pcap_compile(handle_, &parsed_filters_, filter_.c_str(), 0, network_) ==
      -1) {
    std::ostringstream exception_message;
    exception_message << "Couldn't parse filter " << filter_ << ": "
                      << pcap_geterr(handle_);
    throw SnifferException{exception_message.str()};
  }
}

/**
 * @brief Applies the filters by pcap_setfilter
 */
void PcapPacketSniffer::ApplyFilters() {
  if (pcap_setfilter(handle_, &parsed_filters_) == -1) {
    std::ostringstream exception_message;
    exception_message << "Couldn't apply filter " << filter_ << ": "
                      << pcap_geterr(handle_);

    throw SnifferException{exception_message.str()};
  }
}

/**
 * @brief Encapsulates a call to pcap_loop
 */
void PcapPacketSniffer::Sniff() {
  pcap_loop(handle_,
            config_manager_.ExtractValue<int>("sniffer", "packets_count"),
            OnPacketReceived, reinterpret_cast<u_char*>(this));
}

/**
 * @brief This routine is passed to libpcap as a callback that it invokes once a
 * packet is received on the link.
 *
 * @param args
 * @param header
 * @param packet
 */
void PcapPacketSniffer::OnPacketReceived(u_char* args,
                                         const struct pcap_pkthdr* header,
                                         const u_char* packet) {
  (reinterpret_cast<PcapPacketSniffer*>(args))
      ->OnPacketReceivedInternal(header, packet);
}

/**
 * @brief An internal callback called by the static one expected by libpcap.
 * It forms a SniffedPacket and a composite serialized object, passing both of
 * them to the layer stack.
 *
 * @param header Pointer to a pcap_pkthdr which is some header metadata
 * @param packet Pointer to the beginning of a packet
 */
void PcapPacketSniffer::OnPacketReceivedInternal(
    const struct pcap_pkthdr* header, const u_char* packet) {
  namespace protocols = sniffer::protocols;

  protocols::PacketRegion body{0, static_cast<int>(header->caplen)};
  protocols::SniffedPacket sniffed_packet{packet, body};

  sniffer::common::serialization::SerializedObject composite{"{}"};

  // http://www.tcpdump.org/linktypes.html
  stack_.HandleReception("physical", 1, &sniffed_packet, &composite);

  server_->AuthenticatedBroadcast(composite.data());
}

/**
 * @brief Destructs the libpcap-specific packet sniffer by applying the
 * libpcap-native freeing functions.
 */
PcapPacketSniffer::~PcapPacketSniffer() {
  pcap_freecode(&parsed_filters_);
  pcap_close(handle_);
}

}  // namespace core

}  // namespace sniffer
