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

#ifndef SNIFFER_SRC_PROTOCOLS_HEADERS_FORMATS_INTERNET_H_
#define SNIFFER_SRC_PROTOCOLS_HEADERS_FORMATS_INTERNET_H_

#include <netinet/in.h>  // in_addr
#include <sys/types.h>

namespace sniffer {

namespace protocols {

namespace headers {

namespace formats {

// https://tools.ietf.org/html/rfc791#section-3.1
struct Internet {
  u_char version_internet_header_length;
  u_char type_of_service;
  u_short total_length;
  u_short identification;
  u_short offset;
  u_char time_to_live;
  u_char protocol;
  u_short checksum;
  struct in_addr source_address, destination_address;
};

}  // namespace formats

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer

#endif  // SNIFFER_SRC_PROTOCOLS_HEADERS_FORMATS_INTERNET_H_
