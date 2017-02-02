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

#include "protocols/headers/metadata/header_metadata.h"

#include <map>
#include <string>

#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace protocols {

namespace headers {

namespace metadata {

/**
 * @brief Constructs a HeaderMetadata object.
 *
 * @param lower_layer_id_mappings Maps the ID of the current header based on the
 * lower layer header.
 * @param name The name of the header.
 * @param length The length of the header if it's a fixed-length header.
 * @param minimum_length The minimum length for the header in bytes.
 * @param has_variable_length Determines whether the header length is variable
 * such as TCP and IP (fetched from the header itself) or fixed (such as
 * Ethernet)
 * @param length_field_offset Determines how many bytes into the header to look
 * to fetch the length field if it's a variable-length header.
 */
HeaderMetadata::HeaderMetadata(
    std::map<std::string, int> lower_layer_id_mappings, std::string name,
    int length, int minimum_length, bool has_variable_length,
    int length_field_offset, bool accounts_for_payload_length)
    : lower_layer_id_mappings_{lower_layer_id_mappings},
      name_{name},
      length_{length},
      minimum_length_{minimum_length},
      has_variable_length_{has_variable_length},
      length_field_offset_{length_field_offset},
      accounts_for_payload_length_{accounts_for_payload_length} {}

/**
 * @brief Retrieves the lower layer to ID mappings for the header.
 *
 * @return The map of lower layer header name <-> ID.
 */
std::map<std::string, int> HeaderMetadata::lower_layer_id_mappings() const {
  return lower_layer_id_mappings_;
}

/**
 * @brief Retrieves the name of the header.
 *
 * @return The header name.
 */
std::string HeaderMetadata::name() const { return name_; }

/**
 * @brief Retrieves the length of the header.
 *
 * @return The header length.
 */
int HeaderMetadata::length() const { return length_; }

/**
 * @brief Retrieves the minimum length of the header.
 *
 * @return The minimum header length.
 */
int HeaderMetadata::minimum_length() const { return length_; }

/**
 * @brief Determines whether the header is variable-length of fixed-length.
 *
 * @return True if variable-length header, false otherwise.
 */
bool HeaderMetadata::has_variable_length() const {
  return has_variable_length_;
}

/**
 * @brief Determines whether this header should account for the payload length.
 *
 * @return True if it accounts, false otherwise.
 */
bool HeaderMetadata::accounts_for_payload_length() const {
  return accounts_for_payload_length_;
}

/**
 * @brief Retrieves how many bytes to look into the header to fetch its length.
 *
 * @return The number of bytes to look into the header.
 */
int HeaderMetadata::length_field_offset() const { return length_field_offset_; }

/**
 * @brief Typically, this method is overriden by the concrete variable-length
 * header, appropriate shifts are done to reach the length subfield and the
 * length is extracted and set accordingly. By default it's just set to the
 * beginning of the length field.
 *
 * @param length_field A pointer to the beginning of the length field.
 */
void HeaderMetadata::set_length(const u_char* length_field) {
  length_ = *length_field;
}

/**
 * @brief Takes into account the length of the header when calculating the
 * payload for a SniffedPacket.
 *
 * @param packet Pointer to a SniffedPacket object.
 */
void HeaderMetadata::AccountForPayloadLength(SniffedPacket* packet) const {
  packet->DecrementPayloadLength(length_);
}

}  // namespace metadata

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
