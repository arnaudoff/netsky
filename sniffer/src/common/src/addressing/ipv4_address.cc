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

#include "common/addressing/ipv4_address.h"

#include <cstring>

namespace sniffer {

namespace common {

namespace addressing {

Ipv4Address::Ipv4Address(struct sockaddr* sockaddr) {
  struct sockaddr_in* addr_in = (struct sockaddr_in*)sockaddr;
  buffer_ = new char[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(addr_in->sin_addr), buffer_, INET_ADDRSTRLEN);
}

Ipv4Address::Ipv4Address(const Ipv4Address& other) {
  buffer_ = new char[INET_ADDRSTRLEN];
  strcpy(buffer_, other.buffer_);
}

Ipv4Address& Ipv4Address::operator=(const Ipv4Address& other) {
  if (this != &other) {
    delete[] buffer_;

    buffer_ = new char[INET_ADDRSTRLEN];
    strcpy(buffer_, other.buffer_);
  }

  return *this;
}

Ipv4Address::~Ipv4Address() { delete[] buffer_; }

// TODO(arnaudoff): Refactor this crap
char* Ipv4Address::data() const { return buffer_; }

}  // namespace addressing

}  // namespace common

}  // namespace sniffer
