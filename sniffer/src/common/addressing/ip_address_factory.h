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

#ifndef SNIFFER_SRC_COMMON_ADDRESSING_IP_ADDRESS_FACTORY_H_
#define SNIFFER_SRC_COMMON_ADDRESSING_IP_ADDRESS_FACTORY_H_

#include <sys/socket.h>
#include <memory>
#include "./ip_address.h"

namespace sniffer {

namespace common {

namespace addressing {

class IpAddressFactory {
 public:
  std::unique_ptr<IpAddress> Parse(struct sockaddr* sockaddr);
};

}  // namespace addressing

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_ADDRESSING_IP_ADDRESS_FACTORY_H_
