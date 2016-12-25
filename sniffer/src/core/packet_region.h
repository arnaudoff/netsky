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

#ifndef SNIFFER_SRC_CORE_PACKET_REGION_H_
#define SNIFFER_SRC_CORE_PACKET_REGION_H_

namespace sniffer {

namespace core {

struct PacketRegion {
  int offset;
  int length;

  PacketRegion() : offset{0}, length{0} {}

  PacketRegion(int offset, int length) : offset{offset}, length{length} {}
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_PACKET_REGION_H_
