/*
 * Copyright (C) 2017  Ivaylo Arnaudov <ivaylo.arnaudov12@gmail.com>
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

#ifndef SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_USER_DATAGRAM_HEADER_H_
#define SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_USER_DATAGRAM_HEADER_H_

#include <sys/types.h>

#include <string>

#include "registry.h"
#include "protocols/headers/header.h"

namespace sniffer {

namespace protocols {

namespace headers {

namespace formats {

struct UserDatagram;

}  // namespace formats

class UserDatagramHeader : public Header {
 public:
  UserDatagramHeader(int length, SniffedPacket* packet);

  ~UserDatagramHeader() {}

  u_int16_t source_port() const;

  u_int16_t destination_port() const;

  // u_int16_t length() const;

  u_int16_t checksum() const;

  int next_header_id() const override;

  sniffer::common::serialization::SerializedObject Serialize(
      const sniffer::common::serialization::SerializationMgr& serializer)
      const override;

  sniffer::common::serialization::SerializedObject Summarise(
      const sniffer::common::serialization::SerializationMgr& serializer)
      const override;

  std::string entity_name() const override;

 private:
  const formats::UserDatagram* data_;
};

REGISTER_SUBCLASS(Header, UserDatagramHeader, int, SniffedPacket*)

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer

#endif  // SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_USER_DATAGRAM_HEADER_H_
