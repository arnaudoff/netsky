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

#include "protocols/headers/metadata/internet_header_metadata.h"

#include <map>
#include <string>

namespace sniffer {

namespace protocols {

namespace headers {

namespace metadata {

/**
 * @brief Constructs an InternetHeaderMetadata object.
 *
 * @param lower_layer_id_mappings Maps the ID of the IP header based on the
 * lower layer header.
 * @param name The name of the header.
 * @param length The length of the header, normally 0 because it's var-length.
 * @param minimum_length The minimum length for the header in bytes. (e.g. 20)
 * @param has_variable_length Typically true, the length is fetched from VIHL.
 * @param length_field_offset Determines how many bytes into the header to look
 * to fetch the length field if it's a variable-length header. (e.g. 0 for VIHL)
 */
InternetHeaderMetadata::InternetHeaderMetadata(
    std::map<std::string, int> lower_layer_id_mappings, std::string name,
    int length, int minimum_length, bool has_variable_length,
    int length_field_offset, bool accounts_for_payload_length)
    : HeaderMetadata(lower_layer_id_mappings, name, length, minimum_length,
                     has_variable_length, length_field_offset,
                     accounts_for_payload_length) {}

/**
 * @brief Calculates and sets the length of the IP header as specified in
 * RFC791:
 *
 * https://tools.ietf.org/html/rfc791#section-3.1
 *
 * Note the IHL is in 32-bit words (4 byte words), so we multiply by 4 to
 * convert to "1-byte" words.
 *
 * @param length_field Pointer to the beginning of the VIHL byte.
 */
void InternetHeaderMetadata::set_length(const u_char* length_field) {
  u_char version_internet_header_length = *length_field;

  length_ = (version_internet_header_length & 0x0f) * 4;
}

}  // namespace metadata

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
