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

#include "./ipv6_address.h"

#include <cstring>

namespace sniffer {

namespace common {

namespace addressing {

Ipv6Address::Ipv6Address(struct sockaddr* sockaddr) {
  struct sockaddr_in6* addr_in6 = (struct sockaddr_in6*)sockaddr;
  buffer_ = new char[INET6_ADDRSTRLEN];
  inet_ntop(AF_INET6, &(addr_in6->sin6_addr), buffer_, INET6_ADDRSTRLEN);
}

Ipv6Address::Ipv6Address(const Ipv6Address& other) {
  buffer_ = new char[INET6_ADDRSTRLEN];
  strcpy(buffer_, other.buffer_);
}

Ipv6Address& Ipv6Address::operator=(const Ipv6Address& other) {
  if (this != &other) {
    delete[] buffer_;

    buffer_ = new char[INET6_ADDRSTRLEN];
    strcpy(buffer_, other.buffer_);
  }

  return *this;
}

Ipv6Address::~Ipv6Address() { delete[] buffer_; }

char* Ipv6Address::data() const { return buffer_; }

}  // namespace addressing

}  // namespace common

}  // namespace sniffer
