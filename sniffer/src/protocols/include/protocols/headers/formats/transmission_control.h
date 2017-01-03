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

#ifndef SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_FORMATS_TRANSMISSION_CONTROL_H_
#define SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_FORMATS_TRANSMISSION_CONTROL_H_

#include <sys/types.h>

// https://www.ietf.org/rfc/rfc793.txt section 3.1

namespace sniffer {

namespace protocols {

namespace headers {

namespace formats {

struct TransmissionControl {
  u_short source_port;
  u_short destination_port;
  u_int sequence_number;
  u_int acknowledgment_number;
  u_char offset_x2;
  u_char flags;
  u_short window;
  u_short checksum;
  u_short urgent_pointer;
};

}  // namespace formats

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer

#endif  // SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_FORMATS_TRANSMISSION_CONTROL_H_
