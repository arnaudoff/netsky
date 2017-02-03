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

#ifndef SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_INTERNET_HEADER_H_
#define SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_INTERNET_HEADER_H_

#include <sys/types.h>
#include <string>

#include "registry.h"

#include "protocols/headers/header.h"

namespace sniffer {

namespace protocols {

namespace headers {

namespace formats {

struct Internet;

}  // namespace formats

class InternetHeader : public Header {
 public:
  InternetHeader(int length, SniffedPacket* packet);

  ~InternetHeader() {}

  u_char version() const;

  u_char precedence() const;

  u_char delay_flag() const;

  u_char throughput_flag() const;

  u_char reliability_flag() const;

  u_short total_length() const;

  u_short identification() const;

  u_char dont_fragment_flag() const;

  u_char more_fragments_flag() const;

  u_short fragment_offset() const;

  u_char time_to_live() const;

  u_short header_checksum() const;

  const char* source_address() const;

  const char* destination_address() const;

  int next_header_id() const override;

  int length_field_length() const override;

  sniffer::common::serialization::SerializedObject Serialize(
      const sniffer::common::serialization::SerializationMgr& serializer)
      const override;

  sniffer::common::serialization::SerializedObject Summarise(
      const sniffer::common::serialization::SerializationMgr& serializer)
      const override;

  std::string entity_name() const override;

 private:
  const formats::Internet* data_;
};

REGISTER_SUBCLASS(Header, InternetHeader, int, SniffedPacket*)

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer

#endif  // SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_INTERNET_HEADER_H_
