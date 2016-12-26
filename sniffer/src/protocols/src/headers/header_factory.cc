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

#include "protocols/headers/header_factory.h"
#include "protocols/headers/header.h"

namespace sniffer {

namespace protocols {

namespace headers {

using map_type = std::map<std::string, std::unique_ptr<Header> (*)(
                                           int, sniffer::core::SniffedPacket*)>;

/**
 * @brief Lazy loads the internal registry map.
 *
 * @return The internal registry map.
 */
map_type* HeaderFactory::map() {
  if (!map_) {
    map_ = new map_type;
  }

  return map_;
}

/**
 * @brief Creates a header with a runtime-determined type.
 *
 * @param class_name The name of the class that is registered.
 *
 * @param length The length of the header to create an instance of.
 *
 * @param packet Pointer to a SniffedPacket object to pass to the header's
 * constructor.
 *
 * @return A unique pointer to the Header object on the heap.
 */
std::unique_ptr<Header> HeaderFactory::CreateInstance(
    const std::string& class_name, int length, SniffedPacket* packet) {
  map_type::iterator it = map()->find(class_name);
  if (it == map()->end()) {
    return nullptr;
  }

  return it->second(length, packet);
}

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer
