/*
 * Copyright (C) 2017  Ivaylo Arnaudov <ivaylo.arnaudov12@gmail.com>
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

#include "protocols/headers/ethernet_header.h"

#include <arpa/inet.h>

#include <iomanip>
#include <sstream>

#include "protocols/headers/formats/ethernet.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace protocols {

namespace headers {

/**
 * @brief Constructs an Ethernet header from a SniffedPacket, reinterpreting
 * the internal byte array of the SniffedPacket object.
 *
 * @param length The length of the header to extract in bytes.
 * @param packet A pointer to a SniffedPacket object.
 */
EthernetHeader::EthernetHeader(int length, SniffedPacket* packet)
    : Header{length, packet},
      data_{(const formats::Ethernet*)(packet_->ExtractHeader(length_))} {}

/**
 * @brief Retrieves the destination MAC address.
 *
 * @return The destination MAC address of the frame.
 */
std::string EthernetHeader::destination_address() const {
  std::ostringstream os;
  for (int byte_count = 0; byte_count < EthernetHeader::ADDRESS_LENGTH;
       byte_count++) {
    os << std::setw(2) << std::setfill('0') << std::hex
       << static_cast<int>(data_->destination_address[byte_count]);
    if (byte_count < EthernetHeader::ADDRESS_LENGTH - 1) {
      os << ":";
    }
  }

  return os.str();
}

/**
 * @brief Retrieves the source MAC address.
 *
 * @return The source MAC address of the frame.
 */
std::string EthernetHeader::source_address() const {
  std::ostringstream os;
  for (int byte_count = 0; byte_count < EthernetHeader::ADDRESS_LENGTH;
       byte_count++) {
    os << std::setw(2) << std::setfill('0') << std::hex
       << static_cast<int>(data_->source_address[byte_count]);
    if (byte_count < ADDRESS_LENGTH - 1) {
      os << ":";
    }
  }

  return os.str();
}

/**
 * @brief Retrieves the EtherType field of the frame.
 *
 * @return A two-byte value indicating the upper layer protocol that is carried.
 */
u_short EthernetHeader::ether_type() const { return ntohs(data_->ether_type); }

/**
 * @brief Defines the next_header_id for the upper layer protocol.
 *
 * @return The value of the EtherType field of the frame.
 */
int EthernetHeader::next_header_id() const { return ether_type(); }

/**
 * @brief Defines the entity name for the class that is used when serializing
 * it as an object.
 *
 * @return The name of the entity.
 */
std::string EthernetHeader::entity_name() const { return "ethernet"; }

/**
 * @brief Serializes an EthernetHeader object into an object of type defined
 * by the policy used for SerializationMgr.
 *
 * @param serializer The serializer to use.
 *
 * @return A serialized version of the fields in the Ethernet header.
 */
sniffer::common::serialization::SerializedObject EthernetHeader::Serialize(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto root_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", entity_name(), &root_obj);

  auto dst_addr_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", "destination_address",
                                   &dst_addr_obj);

  auto dst_addr_value_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", destination_address(),
                                   &dst_addr_value_obj);
  serializer.SetValue<int>("size", ADDRESS_LENGTH, &dst_addr_value_obj);
  serializer.AppendObject("children", dst_addr_value_obj, &dst_addr_obj);

  auto src_addr_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", "source_address", &src_addr_obj);

  auto src_addr_value_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", source_address(),
                                   &src_addr_value_obj);
  serializer.SetValue<int>("size", ADDRESS_LENGTH, &src_addr_value_obj);
  serializer.AppendObject("children", src_addr_value_obj, &src_addr_obj);

  auto ether_type_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", "ether_type", &ether_type_obj);

  auto ether_type_value_obj = serializer.CreateObject();
  serializer.SetValue<u_short>("name", ether_type(), &ether_type_value_obj);
  serializer.SetValue<u_short>("size", 2, &ether_type_value_obj);
  serializer.AppendObject("children", ether_type_value_obj, &ether_type_obj);

  serializer.AppendObject("children", dst_addr_obj, &root_obj);
  serializer.AppendObject("children", src_addr_obj, &root_obj);
  serializer.AppendObject("children", ether_type_obj, &root_obj);

  return root_obj;
}

/**
 * @brief Summarises two of the most important fields in the header.
 *
 * @param serializer The serialized to use for summarization.
 *
 * @return A SerializedObject containing the object with the summary fields
 * contained as properties.
 */
sniffer::common::serialization::SerializedObject EthernetHeader::Summarise(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto root_obj = serializer.CreateObject();

  serializer.SetValue<std::string>("dst", destination_address(), &root_obj);
  serializer.SetValue<std::string>("src", source_address(), &root_obj);

  return root_obj;
}

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
