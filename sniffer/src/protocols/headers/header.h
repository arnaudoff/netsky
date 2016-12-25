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

#ifndef SNIFFER_SRC_PROTOCOLS_HEADERS_HEADER_H_
#define SNIFFER_SRC_PROTOCOLS_HEADERS_HEADER_H_

#include <memory>
#include <string>

#include "common/policy_bindings.h"
#include "common/serialization/serializable_entity.h"

namespace sniffer {

namespace protocols {

namespace headers {

class Header : public sniffer::common::serialization::SerializableEntity {
 public:
  explicit Header(int length);

  virtual ~Header();

  template <typename T>
  static std::unique_ptr<Header> CreateHeader(
      int length, sniffer::core::SniffedPacket* packet) {
    return std::make_unique<T>(length, packet);
  }

  int length() const;

  virtual int next_header_id() const = 0;

  virtual sniffer::common::serialization::SerializedObject Serialize(
      const SerializationMgr& serializer) const = 0;

  virtual std::string entity_name() const = 0;

 private:
  int length_;
};

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer

#endif  // SNIFFER_SRC_PROTOCOLS_HEADERS_HEADER_H_
