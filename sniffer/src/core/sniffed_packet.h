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

#ifndef SNIFFER_SRC_CORE_SNIFFED_PACKET_H_
#define SNIFFER_SRC_CORE_SNIFFED_PACKET_H_

#include <memory>

#include "core/packet_region.h"

namespace sniffer {

namespace core {

class SniffedPacket {
 public:
  SniffedPacket(const u_char* data, PacketRegion body);

  const u_char* ExtractHeader(int header_length);

  const u_char* ExtractTrailer(int trailer_length);

  const u_char* Peek(int byte_offset);

 private:
  PacketRegion header_;
  PacketRegion body_;
  PacketRegion trailer_;

  const u_char* data_;
};

}  // namespace core
}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_SNIFFED_PACKET_H_
