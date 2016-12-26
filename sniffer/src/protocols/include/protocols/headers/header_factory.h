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

#ifndef SNIFFER_SRC_PROTOCOLS_HEADERS_HEADER_FACTORY_H_
#define SNIFFER_SRC_PROTOCOLS_HEADERS_HEADER_FACTORY_H_

#include <map>
#include <memory>
#include <string>

#include "core/sniffed_packet.h"
#include "protocols/headers/header.h"

namespace sniffer {

namespace protocols {

namespace headers {

class HeaderFactory {
 public:
  std::unique_ptr<Header> CreateInstance(const std::string& class_name,
                                         int length,
                                         sniffer::core::SniffedPacket* packet);

 protected:
  map_type* map();

 private:
  using map_type =
      std::map<std::string,
               std::unique_ptr<Header> (*)(int, sniffer::core::SniffedPacket*)>;

  map_type* map_;
};

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer

#endif  // SNIFFER_SRC_PROTOCOLS_HEADERS_HEADER_FACTORY_H_