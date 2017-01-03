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
#include "protocols/headers/header_factory_registrator.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace protocols {

namespace headers {

HeaderFactoryRegistrator<TransmissionControlHeader>
    TransmissionControlHeader::registrator_{};

/**
 * @brief Constructs a TCP header of length length from a SniffedPacket by re-
 * interpreting the internal byte array of the SniffedPacket.
 *
 * @param length The length of the header to extract in bytes.
 *
 * @param packet A pointer to a SniffedPacket object.
 */
TransmissionControlHeader::TransmissionControlHeader(int length,
                                                     SniffedPacket* packet)
    : Header{length},
      data_{
          (const formats::TransmissionControl*)(packet->ExtractHeader(length))}
/*
if (size_ < 20) {
    std::ostringstream exception_message;
    exception_message << "Invalid TCP header length: " <<
        size_ << " bytes.";
    throw std::out_of_range { exception_message.str() };
}
*/
{}

/**
 * @brief Registers the header class into the global HeaderFactory registry.
 *
 * @param name A name which to use for the TransmissionControlHeader class.
 */
void TransmissionControlHeader::RegisterClass(const std::string& name) {
  registrator_.RegisterHeader(name);
}

/**
 * @brief Retrieves the offset
 *
 * @return The offset.
 */
u_char TransmissionControlHeader::offset() const {
  return (data_->offset_x2 & 0xf0) >> 4;
}

/**
 * @brief Retrieves the 16 bit source port from the TCP header.
 *
 * @return The source port
 */
u_int16_t TransmissionControlHeader::source_port() const {
  return ntohs(data_->source_port);
}

/**
 * @brief Retrieves the 16 bit destination port from the TCP header.
 *
 * @return The destination port
 */
u_int16_t TransmissionControlHeader::destination_port() const {
  return ntohs(data_->destination_port);
}

/**
 * @brief Retrieves the 32 bit sequence number from the TCP header.
 *
 * @return The sequence number.
 */
int TransmissionControlHeader::sequence_number() const {
  return data_->sequence_number;
}

/**
 * @brief Retrieves the 32 bit acknowledgment number from the TCP header.
 *
 * @return The acknowledgment number.
 */
int TransmissionControlHeader::acknowledgment_number() const {
  return data_->acknowledgment_number;
}

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
  auto obj = serializer.CreateObject();

  serializer.SetValue<u_int16_t>("src", source_port(), &obj);
  serializer.SetValue<u_int16_t>("dst", destination_port(), &obj);
  // TODO(arnaudoff): Extract to base..
  serializer.SetValue<int>("length", length(), &obj);

  return obj;
}

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
