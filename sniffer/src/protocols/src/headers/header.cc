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
 * @brief Retrieves the length of the header.
 *
 * @return The length of the header.
 */
int Header::length() const { return length_; }

/**
 * @brief Gets the pointer to the SniffedPacket object for the header.
 *
 * @return The pointer to the SniffedPacket object for the header.
 */
const SniffedPacket* Header::packet() const { return packet_; }

/**
 * @brief Destructs the header.
 */
Header::~Header() {}

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
