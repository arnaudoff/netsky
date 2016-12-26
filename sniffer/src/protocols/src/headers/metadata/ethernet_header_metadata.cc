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

#include "protocols/headers/metadata/ethernet_header_metadata.h"

namespace sniffer {

namespace protocols {

namespace headers {

namespace metadata {

EthernetHeaderMetadata::EthernetHeaderMetadata(int id, std::string name,
                                               int size, bool variable_length,
                                               int length_field_offset)
    : HeaderMetadata(id, name, size, variable_length, length_field_offset) {}

}  // namespace metadata

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer