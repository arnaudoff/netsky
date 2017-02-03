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

#include "protocols/headers/header.h"

namespace sniffer {

namespace protocols {

namespace headers {

/**
 * @brief Constructs a header object.
 *
 * @param length The length of the header
 * @param packet Pointer to a SniffedPacket object.
 */
Header::Header(int length, SniffedPacket* packet)
    : length_{length}, packet_{packet} {}

/**
 * @brief Destructs the header.
 */
Header::~Header() {}

/**
 * @brief Retrieves the length of the header.
 *
 * @return The length of the header.
 */
int Header::length() const { return length_; }

/**
 * @brief Retrieves the length of the length field in bits. It's used when
 * serializing headers whose length is determined from a field within them.
 *
 * Typically, only headers with length field should override this method.
 *
 * @return By default, returns zero (fixed-length headers have no length field).
 */
int Header::length_field_length() const { return 0; }

/**
 * @brief Gets the pointer to the SniffedPacket object for the header.
 *
 * @return The pointer to the SniffedPacket object for the header.
 */
const SniffedPacket* Header::packet() const { return packet_; }

/**
 * @brief Serializes a field given it's name, value and the size in bits.
 *
 * @param serializer The serializer to use.
 * @param field_name Field name.
 * @param field_value Field value.
 * @param field_size The size of the field value in bits.
 *
 * @return A SerializedObject containing the field serialized.
 */
sniffer::common::serialization::SerializedObject Header::SerializeField(
    const sniffer::common::serialization::SerializationMgr& serializer,
    const std::string& field_name, const std::string& field_value,
    int field_size) const {
  auto field_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", field_name, &field_obj);

  auto field_value_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", field_value, &field_value_obj);
  serializer.SetValue<int>("size", field_size, &field_value_obj);
  serializer.AppendObject("children", field_value_obj, &field_obj);

  return field_obj;
}

/**
 * @brief Serializes the common fields for a header (length). Typically
 * called from the child class to reuse.
 *
 * @param serializer The serializer to use.
 *
 * @return SerializedObject containing the common fields serialized.
 */
sniffer::common::serialization::SerializedObject Header::Serialize(
    const sniffer::common::serialization::SerializationMgr& serializer) const {
  auto root_obj = serializer.CreateObject();
  serializer.SetValue<std::string>("name", entity_name(), &root_obj);

  auto length_obj = SerializeField(
      serializer, "length", std::to_string(length()), length_field_length());

  serializer.AppendObject("children", length_obj, &root_obj);

  return root_obj;
}

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
