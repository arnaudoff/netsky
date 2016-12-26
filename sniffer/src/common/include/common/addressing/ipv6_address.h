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

#ifndef SNIFFER_SRC_COMMON_ADDRESSING_IPV6_ADDRESS_H_
#define SNIFFER_SRC_COMMON_ADDRESSING_IPV6_ADDRESS_H_

#include <arpa/inet.h>
#include <sys/socket.h>

#include "./ip_address.h"

namespace sniffer {

namespace common {

namespace addressing {

class Ipv6Address : public IpAddress {
 public:
  explicit Ipv6Address(struct sockaddr* sockaddr);

  Ipv6Address(const Ipv6Address& other);

  Ipv6Address& operator=(const Ipv6Address& other);

  ~Ipv6Address();

  char* data() const override;

 private:
  char* buffer_;
};

}  // namespace addressing

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_ADDRESSING_IPV6_ADDRESS_H_
