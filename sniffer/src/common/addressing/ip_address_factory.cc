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

#include "./ip_address_factory.h"

#include <memory>

#include <spdlog/spdlog.h>  // NOLINT

#include "./ip_address.h"
#include "./ipv4_address.h"
#include "./ipv6_address.h"

namespace sniffer {

namespace common {

namespace addressing {

// Effective Modern C++, Meyers, p.119 & p.124
std::unique_ptr<IpAddress> IpAddressFactory::Parse(struct sockaddr* sockaddr) {
  if (sockaddr) {
    switch (sockaddr->sa_family) {
      case AF_INET:
        return std::make_unique<Ipv4Address>(sockaddr);
      case AF_INET6:
        return std::make_unique<Ipv6Address>(sockaddr);
      default:
        break;
    }
  }

  return nullptr;
}

}  // namespace addressing

}  // namespace common

}  // namespace sniffer
