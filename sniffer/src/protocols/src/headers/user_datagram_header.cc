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

#include "protocols/headers/user_datagram_header.h"

#include <netinet/in.h>

#include <memory>
#include <sstream>

#include "protocols/headers/formats/user_datagram.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace protocols {

namespace headers {

/**
 * @brief Constructs a UDP header of length length from a SniffedPacket by re-
 * interpreting the internal byte array of the SniffedPacket.
 *
 * @param length The length of the header to extract in bytes.
 * @param packet A pointer to a SniffedPacket object.
 */
UserDatagramHeader::UserDatagramHeader(int length, SniffedPacket* packet)
    : Header{length, packet},
      data_{(const formats::UserDatagram*)(packet_->ExtractHeader(length_))} {}

/**
 * @brief Retrieves the 16 bit source port from the UDP header.
 *
 * @return The source port.
 */
u_short UserDatagramHeader::source_port() const {
  return ntohs(data_->source_port);
}

/**
 * @brief Retrieves the 16 bit destination port from the UDP header.
 *
 * @return The destination port.
 */
u_short UserDatagramHeader::destination_port() const {
  return ntohs(data_->destination_port);
}

/**
 * @brief Retrieves the length from the UDP header (header length + payload).
 *
 * @return The header length + payload length.
 */
u_short UserDatagramHeader::header_len_payload_len() const {
  return ntohs(data_->length);
}

/**
 * @brief Retrieves the checksum from the UDP header.
 *
 * @return The checksum.
 */
u_short UserDatagramHeader::checksum() const {
  return ntohs(data_->checksum);
}

/**
 * @brief The header ID of the upper layer protocol; basically unused.
 *
 * @return Default value.
 */
int UserDatagramHeader::next_header_id() const { return 0; }

/**
 * @brief Defines the entity name for the class that is used when serializing
 * it as an object.
 *
 * @return The name of the entity.
 */
std::string UserDatagramHeader::entity_name() const { return "udp"; }

/**
 * @brief Serializes a UserDatagramHeader object into an object of
 * type defined by the policy used for SerializationMgr.
 *
 * @param serializer The serializer to use.
 *
 * @return A serialized version of the fields in the TCP header.
 */
sniffer::common::serialization::SerializedObject
UserDatagramHeader::Serialize(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto source_port_obj = Header::SerializeField(
      serializer, "src", std::to_string(source_port()), 16);

  auto destination_port_obj = Header::SerializeField(
      serializer, "dst", std::to_string(destination_port()), 16);

  auto length_obj = Header::SerializeField(
      serializer, "length", std::to_string(header_len_payload_len()), 16);

  auto checksum_obj = Header::SerializeField(
      serializer, "checksum", std::to_string(checksum()), 16);

  auto root_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", entity_name(), &root_obj);

  serializer.AppendObject("children", source_port_obj, &root_obj);
  serializer.AppendObject("children", destination_port_obj, &root_obj);
  serializer.AppendObject("children", length_obj, &root_obj);
  serializer.AppendObject("children", checksum_obj, &root_obj);

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
sniffer::common::serialization::SerializedObject
UserDatagramHeader::Summarise(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto root_obj = serializer.CreateObject();

  serializer.SetValue<u_short>("dst", destination_port(), &root_obj);
  serializer.SetValue<u_short>("src", source_port(), &root_obj);

  return root_obj;
}

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
