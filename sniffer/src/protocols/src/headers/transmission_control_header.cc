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

#include "protocols/headers/transmission_control_header.h"

#include <netinet/in.h>

#include <memory>
#include <sstream>

#include "protocols/headers/formats/transmission_control.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace protocols {

namespace headers {

/**
 * @brief Constructs a TCP header of length length from a SniffedPacket by re-
 * interpreting the internal byte array of the SniffedPacket.
 *
 * @param length The length of the header to extract in bytes.
 * @param packet A pointer to a SniffedPacket object.
 */
TransmissionControlHeader::TransmissionControlHeader(int length,
                                                     SniffedPacket* packet)
    : Header{length, packet},
      data_{(const formats::TransmissionControl*)(packet_->ExtractHeader(
          length_))} {}

/**
 * @brief Returns the length of the length field.
 *
 * @return The number of bits in the Data Offset field.
 */
int TransmissionControlHeader::length_field_length() const { return 4; }

/**
 * @brief Retrieves the 16 bit source port from the TCP header.
 *
 * @return The source port.
 */
u_short TransmissionControlHeader::source_port() const {
  return ntohs(data_->source_port);
}

/**
 * @brief Retrieves the 16 bit destination port from the TCP header.
 *
 * @return The destination port.
 */
u_short TransmissionControlHeader::destination_port() const {
  return ntohs(data_->destination_port);
}

/**
 * @brief Retrieves the 32 bit sequence number from the TCP header.
 *
 * @return The sequence number.
 */
u_int TransmissionControlHeader::sequence_number() const {
  return ntohl(data_->sequence_number);
}

/**
 * @brief Retrieves the 32 bit acknowledgment number from the TCP header.
 *
 * @return The acknowledgment number.
 */
u_int TransmissionControlHeader::acknowledgment_number() const {
  return ntohl(data_->acknowledgment_number);
}

/**
 * @brief Retrieves the urgent flag.
 *
 * @return The value of the urgent flag.
 */
u_char TransmissionControlHeader::urg_flag() const {
  return (data_->flags & 0x20) >> 5;
}

/**
 * @brief Retrieves the acknowledgement flag.
 *
 * @return The value of the acknowledgment flag.
 */
u_char TransmissionControlHeader::ack_flag() const {
  return (data_->flags & 0x10) >> 4;
}

/**
 * @brief Retrieves the push flag.
 *
 * @return The value of the push flag.
 */
u_char TransmissionControlHeader::psh_flag() const {
  return (data_->flags & 0x08) >> 3;
}

/**
 * @brief Retrieves the reset flag.
 *
 * @return The value of the reset flag.
 */
u_char TransmissionControlHeader::rst_flag() const {
  return (data_->flags & 0x04) >> 2;
}

/**
 * @brief Retrieves the syn flag.
 *
 * @return The value of the syn flag.
 */
u_char TransmissionControlHeader::syn_flag() const {
  return (data_->flags & 0x02) >> 1;
}

/**
 * @brief Retrieves the fin flag.
 *
 * @return The value of the fin flag.
 */
u_char TransmissionControlHeader::fin_flag() const {
  return (data_->flags & 0x01);
}

/**
 * @brief Retrieves the window field.
 *
 * @return The value of the window (how many octets the sender is willing
 * to accept).
 */
u_short TransmissionControlHeader::window() const {
  return ntohs(data_->destination_port);
}

/**
 * @brief Retrieves the checksum.
 *
 * @return The value of the checksum.
 */
u_short TransmissionControlHeader::checksum() const {
  return ntohs(data_->destination_port);
}

/**
 * @brief Retrieves the urgent pointer.
 *
 * @return The urgent pointer value.
 */
u_short TransmissionControlHeader::urgent_pointer() const {
  return ntohs(data_->destination_port);
}

/**
 * @brief The header ID of the upper layer protocol; basically unused.
 *
 * @return Default value.
 */
int TransmissionControlHeader::next_header_id() const { return 0; }

/**
 * @brief Defines the entity name for the class that is used when serializing
 * it as an object.
 *
 * @return The name of the entity.
 */
std::string TransmissionControlHeader::entity_name() const { return "tcp"; }

/**
 * @brief Serializes a TransmissionControlHeader object into an object of
 * type defined by the policy used for SerializationMgr.
 *
 * @param serializer The serializer to use.
 *
 * @return A serialized version of the fields in the TCP header.
 */
sniffer::common::serialization::SerializedObject
TransmissionControlHeader::Serialize(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto src_port_obj = Header::SerializeField(serializer, "source_port",
                                             std::to_string(source_port()), 16);

  auto dst_port_obj = Header::SerializeField(
      serializer, "destination_port", std::to_string(destination_port()), 16);

  auto seq_number_obj = Header::SerializeField(
      serializer, "seq", std::to_string(sequence_number()), 32);

  auto ack_number_obj = Header::SerializeField(
      serializer, "ack", std::to_string(sequence_number()), 32);

  auto urg_flag_obj = Header::SerializeField(serializer, "urg_flag",
                                             std::to_string(urg_flag()), 1);

  auto ack_flag_obj = Header::SerializeField(serializer, "ack_flag",
                                             std::to_string(ack_flag()), 1);

  auto psh_flag_obj = Header::SerializeField(serializer, "psh_flag",
                                             std::to_string(psh_flag()), 1);

  auto rst_flag_obj = Header::SerializeField(serializer, "rst_flag",
                                             std::to_string(rst_flag()), 1);

  auto syn_flag_obj = Header::SerializeField(serializer, "syn_flag",
                                             std::to_string(syn_flag()), 1);

  auto fin_flag_obj = Header::SerializeField(serializer, "fin_flag",
                                             std::to_string(fin_flag()), 1);

  auto window_obj = Header::SerializeField(serializer, "window",
                                           std::to_string(window()), 16);

  auto checksum_obj = Header::SerializeField(serializer, "checksum",
                                             std::to_string(checksum()), 16);

  auto urgent_pointer_obj = Header::SerializeField(
      serializer, "urgent_pointer", std::to_string(urgent_pointer()), 16);

  auto root_obj = Header::Serialize(serializer);
  serializer.SetValue<std::string>("name", entity_name(), &root_obj);

  serializer.AppendObject("children", src_port_obj, &root_obj);
  serializer.AppendObject("children", dst_port_obj, &root_obj);
  serializer.AppendObject("children", seq_number_obj, &root_obj);
  serializer.AppendObject("children", ack_number_obj, &root_obj);

  serializer.AppendObject("children", urg_flag_obj, &root_obj);
  serializer.AppendObject("children", ack_flag_obj, &root_obj);
  serializer.AppendObject("children", psh_flag_obj, &root_obj);
  serializer.AppendObject("children", rst_flag_obj, &root_obj);
  serializer.AppendObject("children", syn_flag_obj, &root_obj);
  serializer.AppendObject("children", fin_flag_obj, &root_obj);

  serializer.AppendObject("children", window_obj, &root_obj);
  serializer.AppendObject("children", checksum_obj, &root_obj);
  serializer.AppendObject("children", urgent_pointer_obj, &root_obj);

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
TransmissionControlHeader::Summarise(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto root_obj = serializer.CreateObject();

  serializer.SetValue<u_int16_t>("dst", destination_port(), &root_obj);
  serializer.SetValue<u_int16_t>("src", source_port(), &root_obj);

  return root_obj;
}

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
