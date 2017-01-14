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
  /*
  if (size_ < 20) {
      std::ostringstream exception_message;
      exception_message << "Invalid IP header length: " << size_ << "
  bytes.";
      throw std::out_of_range { exception_message.str() };
  }
  */
}

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
  auto root_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", entity_name(), &root_obj);

  auto dst_addr_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", "destination_address",
                                   &dst_addr_obj);

  auto dst_addr_value_obj = serializer.CreateObject();
  serializer.SetValue<const char*>("name", destination_address(),
                                   &dst_addr_value_obj);
  serializer.SetValue<int>("size", 4, &dst_addr_value_obj);
  serializer.AppendObject("children", dst_addr_value_obj, &dst_addr_obj);

  auto src_addr_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", "source_address", &src_addr_obj);

  auto src_addr_value_obj = serializer.CreateObject();
  serializer.SetValue<const char*>("name", source_address(),
                                   &src_addr_value_obj);
  serializer.SetValue<int>("size", 4, &src_addr_value_obj);
  serializer.AppendObject("children", src_addr_value_obj, &src_addr_obj);

  auto version_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", "version", &version_obj);

  auto version_value_obj = serializer.CreateObject();
  serializer.SetValue<u_short>("name", version(), &version_value_obj);
  serializer.SetValue<u_short>("size", 1, &version_value_obj);
  serializer.AppendObject("children", version_value_obj, &version_obj);

  auto upper_layer_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", "upper_layer", &upper_layer_obj);

  auto upper_layer_value_obj = serializer.CreateObject();
  serializer.SetValue<u_short>("name", next_header_id(),
                               &upper_layer_value_obj);
  serializer.SetValue<u_short>("size", 1, &upper_layer_value_obj);
  serializer.AppendObject("children", upper_layer_value_obj, &upper_layer_obj);

  // TODO(arnaudoff): Extract the length (and upper_layer?) stuff into the
  // Header and call the base implementation from here.
  auto length_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", "length", &length_obj);

  auto length_value_obj = serializer.CreateObject();
  serializer.SetValue<u_short>("name", length(), &length_value_obj);
  serializer.SetValue<u_short>("size", 1, &length_value_obj);
  serializer.AppendObject("children", length_value_obj, &length_obj);

  serializer.AppendObject("children", dst_addr_obj, &root_obj);
  serializer.AppendObject("children", src_addr_obj, &root_obj);
  serializer.AppendObject("children", version_obj, &root_obj);
  serializer.AppendObject("children", upper_layer_obj, &root_obj);
  serializer.AppendObject("children", length_obj, &root_obj);

  return root_obj;
}

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
