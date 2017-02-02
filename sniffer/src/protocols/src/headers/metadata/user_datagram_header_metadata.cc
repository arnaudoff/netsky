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

#include "protocols/headers/metadata/user_datagram_header_metadata.h"

#include <map>
#include <string>

namespace sniffer {

namespace protocols {

namespace headers {

namespace metadata {

UserDatagramHeaderMetadata::UserDatagramHeaderMetadata(
    std::map<std::string, int> lower_layer_id_mappings, std::string name,
    int length, int minimum_length, bool has_variable_length,
    int length_field_offset, bool accounts_for_payload_length)
    : HeaderMetadata(lower_layer_id_mappings, name, length, minimum_length,
                     has_variable_length, length_field_offset,
                     accounts_for_payload_length) {}

}  // namespace metadata

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
