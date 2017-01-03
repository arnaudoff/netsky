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

#define IP_RF 0x8000      /* reserved fragment flag */
#define IP_DF 0x4000      /* dont fragment flag */
#define IP_MF 0x2000      /* more fragments flag */
#define IP_OFFMASK 0x1fff /* mask for fragmenting bits */

#include "protocols/headers/header.h"
#include "protocols/headers/header_factory_registrator.h"

namespace sniffer {

namespace protocols {

namespace headers {

namespace formats {

struct Internet;
}

class InternetHeader : public Header {
 public:
  InternetHeader(int length, SniffedPacket* packet);

  ~InternetHeader() {}

  static void RegisterClass(const std::string& name);

  u_char version() const;

  u_char header_length() const;

  u_char type_of_service() const;

  u_short total_length() const;

  u_short identification() const;

  u_char flags() const;

  u_short fragment_offset() const;

  u_short time_to_live() const;

  u_char protocol() const;

  u_short header_checksum() const;

  char* source_address() const;

  char* destination_address() const;

  int next_header_id() const override;

  sniffer::common::serialization::SerializedObject Serialize(
      const sniffer::common::serialization::SerializationMgr& serializer)
      const override;

  std::string entity_name() const override;

 private:
  static HeaderFactoryRegistrator<InternetHeader> registrator_;

  const formats::Internet* data_;
};

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer

#endif  // SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_INTERNET_HEADER_H_
