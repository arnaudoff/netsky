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

#include "protocols/headers/internet_header.h"

#include <arpa/inet.h>

#include <sstream>

#include "protocols/headers/formats/internet.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace protocols {

namespace headers {

/**
 * @brief Constructs an Internet header from a SniffedPacket, reinterpreting
 * the internal byte array of the SniffedPacket object.
 *
 * @param length The length of the header to extract in bytes.
 * @param packet A pointer to the SnifffedPacket object.
 */
InternetHeader::InternetHeader(int length, SniffedPacket* packet)
    : Header{length, packet},
      data_{(const formats::Internet*)(packet_->ExtractHeader(length_))} {
  packet->IncrementPayloadLength(ntohs(data_->total_length));
}

/**
 * @brief Returns the length of the length field.
 *
 * @return The number of bits in the IHL field.
 */
int InternetHeader::length_field_length() const { return 4; }

/**
 * @brief Parses the VIHL field.
 *
 * @return The version which is encoded into the VIHL field of the packet
 * header.
 */
u_char InternetHeader::version() const {
  return data_->version_internet_header_length >> 4;
}

/**
 * @brief Parses the precedence of the ToS field.
 *
 * @return 3 bits containing the QoS desired.
 */
u_char InternetHeader::precedence() const {
  return (data_->type_of_service & 0xe0) >> 5;
}

/**
 * @brief Determines whether normal delay or low delay is to be used for the
 * datagram.
 *
 * @return The value of the delay flag.
 */
u_char InternetHeader::delay_flag() const {
  return (data_->type_of_service & 0x10) >> 4;
}

/**
 * @brief Determines whether normal throughput or high throughput is to be
 * used for the datagram.
 *
 * @return The value of the throughput flag.
 */
u_char InternetHeader::throughput_flag() const {
  return (data_->type_of_service & 0x08) >> 3;
}

/**
 * @brief Determines whether normal reliability or high reliability is to be
 * used for the datagram.
 *
 * @return The value of the reliability flag.
 */
u_char InternetHeader::reliability_flag() const {
  return (data_->type_of_service & 0x04) >> 2;
}

/**
 * @brief Parses the Total Length field.
 *
 * @return The length of the datagram in octets, incl. internet header and data.
 */
u_short InternetHeader::total_length() const {
  return ntohs(data_->total_length);
}

/**
 * @brief Parses the Identification field.
 *
 * @return The identifying value assigned by the sender to aid in assembling the
 * fragments of a datagram.
 */
u_short InternetHeader::identification() const {
  return ntohs(data_->identification);
}

/**
 * @brief Returns the DF flag (may fragment / don't fragment)
 *
 * @return The value of the DF flag.
 */
u_char InternetHeader::dont_fragment_flag() const {
  return (data_->fragment_offset & 0x4000) >> 14;
}

/**
 * @brief Returns the DF flag (may fragment / don't fragment)
 *
 * @return The value of the DF flag.
 */
u_char InternetHeader::more_fragments_flag() const {
  return (data_->fragment_offset & 0x2000) >> 13;
}

/**
 * @brief Indicates where in the datagram this fragment belongs.
 *
 * @return The fragment offset measured in units of 8 octets.
 */
u_short InternetHeader::fragment_offset() const {
  return data_->fragment_offset & 0x1fff;
}

/**
 * @brief Indicates the maximum number of router hops for the datagram.
 *
 * @return The value of the TTL field.
 */
u_char InternetHeader::time_to_live() const { return data_->time_to_live; }

/**
 * @brief Checksum of the header only, e.g. since the TTL changes it's
 * recomputed.
 *
 * @return The checksum for the header.
 */
u_short InternetHeader::header_checksum() const {
  return ntohs(data_->header_checksum);
}

/**
 * @brief Retrieves the source IP address.
 *
 * @return A pointer to the beginning of the source IP address.
 */
const char* InternetHeader::source_address() const {
  return inet_ntoa(data_->source_address);
}

/**
 * @brief Retrieves the destination IP address.
 *
 * @return A pointer to the beginning of the destination IP address.
 */
const char* InternetHeader::destination_address() const {
  return inet_ntoa(data_->destination_address);
}

/**
 * @brief Defines the next_header_id for the upper layer protocol.
 *
 * @return The value of the Protocol field of the packet, i.e TCP or UDP.
 */
int InternetHeader::next_header_id() const { return data_->protocol; }

/**
 * @brief Defines the entity name for the class that is used when serializing
 * it as an object.
 *
 * @return The name of the entity.
 */
std::string InternetHeader::entity_name() const { return "internet"; }

/**
 * @brief Serializes an InternetHeader object into an object of type defined
 * by the policy used for SerializationMgr.
 *
 * @param serializer The serializer to use.
 *
 * @return A serialized version of the fields in the Interner Protocol header.
 */
sniffer::common::serialization::SerializedObject InternetHeader::Serialize(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto version_obj = Header::SerializeField(serializer, "version",
                                            std::to_string(version()), 4);

  auto precedence_obj = Header::SerializeField(serializer, "precedence",
                                               std::to_string(precedence()), 3);
  auto delay_flag_obj = Header::SerializeField(serializer, "delay",
                                               std::to_string(delay_flag()), 1);
  auto throughput_flag_obj = Header::SerializeField(
      serializer, "throughput", std::to_string(throughput_flag()), 1);

  auto reliability_flag_obj = Header::SerializeField(
      serializer, "reliability", std::to_string(reliability_flag()), 1);

  auto total_length_obj = Header::SerializeField(
      serializer, "total length", std::to_string(total_length()), 16);

  auto identification_obj = Header::SerializeField(
      serializer, "identification", std::to_string(identification()), 16);

  auto dont_fragment_flag_obj = Header::SerializeField(
      serializer, "fl_dont_fragment", std::to_string(dont_fragment_flag()), 1);

  auto more_fragments_flag_obj =
      Header::SerializeField(serializer, "fl_more_fragments",
                             std::to_string(more_fragments_flag()), 1);

  auto fragment_offset_obj = Header::SerializeField(
      serializer, "fragment_offset", std::to_string(fragment_offset()), 13);

  auto time_to_live_obj = Header::SerializeField(
      serializer, "ttl", std::to_string(time_to_live()), 8);

  auto protocol_obj = Header::SerializeField(
      serializer, "protocol", std::to_string(next_header_id()), 8);

  auto checksum_obj = Header::SerializeField(
      serializer, "checksum", std::to_string(header_checksum()), 16);

  auto source_addr_obj = Header::SerializeField(
      serializer, "src", std::string(source_address()), 32);

  auto destination_addr_obj = Header::SerializeField(
      serializer, "dst", std::string(destination_address()), 32);

  auto root_obj = Header::Serialize(serializer);
  serializer.AppendObject("children", version_obj, &root_obj);

  serializer.AppendObject("children", precedence_obj, &root_obj);
  serializer.AppendObject("children", delay_flag_obj, &root_obj);
  serializer.AppendObject("children", throughput_flag_obj, &root_obj);
  serializer.AppendObject("children", reliability_flag_obj, &root_obj);
  serializer.AppendObject("children", total_length_obj, &root_obj);
  serializer.AppendObject("children", identification_obj, &root_obj);
  serializer.AppendObject("children", dont_fragment_flag_obj, &root_obj);
  serializer.AppendObject("children", more_fragments_flag_obj, &root_obj);
  serializer.AppendObject("children", fragment_offset_obj, &root_obj);
  serializer.AppendObject("children", time_to_live_obj, &root_obj);
  serializer.AppendObject("children", protocol_obj, &root_obj);
  serializer.AppendObject("children", checksum_obj, &root_obj);
  serializer.AppendObject("children", source_addr_obj, &root_obj);
  serializer.AppendObject("children", destination_addr_obj, &root_obj);

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
sniffer::common::serialization::SerializedObject InternetHeader::Summarise(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto root_obj = serializer.CreateObject();

  serializer.SetValue<const char*>("dst", destination_address(), &root_obj);
  serializer.SetValue<const char*>("src", source_address(), &root_obj);

  return root_obj;
}

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
