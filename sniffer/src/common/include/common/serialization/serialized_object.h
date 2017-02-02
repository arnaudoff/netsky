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

#ifndef SNIFFER_SRC_COMMON_INCLUDE_COMMON_SERIALIZATION_SERIALIZED_OBJECT_H_
#define SNIFFER_SRC_COMMON_INCLUDE_COMMON_SERIALIZATION_SERIALIZED_OBJECT_H_

#include <string>

namespace sniffer {

namespace common {

namespace serialization {

class SerializedObject {
 public:
  explicit SerializedObject(const std::string& data);

  std::string data() const;

  void set_data(const std::string& data);

 private:
  std::string data_;
};

}  // namespace serialization

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_INCLUDE_COMMON_SERIALIZATION_SERIALIZED_OBJECT_H_
