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

#include "protocols/headers/metadata/transmission_control_header_metadata.h"

#include <map>
#include <string>

namespace sniffer {

namespace protocols {

namespace headers {

namespace metadata {

/**
 * @brief Constructs a TransmissionControlHeaderMetadata object.
 *
 * @param lower_layer_id_mappings Maps the ID of the TCP header based on the
 * lower layer header.
 * @param name The name of the header.
 * @param length The length of the header, normally 0 because it's var-length.
 * @param minimum_length The minimum length for the header in bytes. (e.g. 20)
 * @param has_variable_length Typically true, the length is fetched from Data
 * Offset field.
 * @param length_field_offset Determines how many bytes into the header to look
 * to fetch the length field if it's a variable-length header. (e.g. 0 for VIHL)
 */
TransmissionControlHeaderMetadata::TransmissionControlHeaderMetadata(
    std::map<std::string, int> lower_layer_id_mappings, std::string name,
    int length, int minimum_length, bool has_variable_length,
    int length_field_offset, bool accounts_for_payload_length)
    : HeaderMetadata(lower_layer_id_mappings, name, length, minimum_length,
                     has_variable_length, length_field_offset,
                     accounts_for_payload_length) {}

/**
 * @brief Calculates and sets the length of the TCP header. A byte that contains
 * 4 bits for the data offset and 4 into the Reserved field is fetched as
 * specified in RFC 793:
 *
 * https://tools.ietf.org/html/rfc793#section-3.1
 *
 * Note that after masked and shifted, it is multiplied by 4 because the Data
 * Offset field is in units of 4-byte words, so by multiplying times 4 we
 * convert it to units of "1-byte words".
 *
 * @param length_field Pointer to the byte containing the data offset.
 */
void TransmissionControlHeaderMetadata::set_length(const u_char* length_field) {
  u_char offset_x2 = *length_field;

  length_ = ((offset_x2 & 0xf0) >> 4) * 4;
}

}  // namespace metadata

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
