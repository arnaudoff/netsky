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

#include <arpa/inet.h>

#include <sstream>

#include "protocols/headers/internet_header.h"

namespace sniffer {

namespace protocols {

namespace headers {

HeaderFactoryRegistrator<InternetHeader> InternetHeader::registrator_{};

/**
 * @brief Constructs an Internet header from a SniffedPacket, reinterpreting
 * the internal byte array of the SniffedPacket object.
 *
 * @param length The length of the header to extract in bytes.
 * @param packet A pointer to a SnifffedPacket object.
 */
InternetHeader::InternetHeader(int length, SniffedPacket* packet)
    : Header{length},
      data_{(const struct Internet*)(packet.ExtractHeader(length))} {
  /*
  if (size_ < 20) {
      std::ostringstream exception_message;
      exception_message << "Invalid IP header length: " << size_ << " bytes.";
      throw std::out_of_range { exception_message.str() };
  }
  data_ = (const struct Internet*)(packet.extract_header());
  */
}

/**
 * @brief Registers the header class into the global HeaderFactory registry.
 *
 * @param name A name which to use for the InternetHeader class.
 */
void InternetHeader::RegisterClass(const std::string& name) {
  registrator_.RegisterHeader(name);
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
char* InternetHeader::source_address() const {
  return inet_ntoa(data_->source_address);
}

/**
 * @brief Retrieves the destination IP address.
 *
 * @return A pointer to the beginning of the destination IP address.
 */
char* InternetHeader::destination_address() const {
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
SerializedObject InternetHeader::Serialize(
    const SerializationMgr& serializer) const {
  auto obj = serializer.create_object();

  // TODO(arnaudoff): Extract the upper_layer stuff into the Header and call the
  // base
  // implementation from here.
  serializer.SetValue<u_char>(obj, "version", version());
  serializer.SetValue<u_char>(obj, "upper_layer", next_header_id());
  serializer.SetValue<char*>(obj, "src", source_address());
  serializer.SetValue<char*>(obj, "dst", destination_address());
  serializer.SetValue<int>(obj, "length", length());

  return obj;
}

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
