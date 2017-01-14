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

#ifndef SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_ETHERNET_HEADER_H_
#define SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_ETHERNET_HEADER_H_

#include <sys/types.h>
#include <string>

#include "registry.h"

#include "protocols/headers/header.h"

namespace sniffer {

namespace protocols {

namespace headers {

namespace formats {

struct Ethernet;

}  // namespace formats

class EthernetHeader : public Header {
 public:
  EthernetHeader(int length, SniffedPacket* packet);

  ~EthernetHeader() {}

  std::string destination_address() const;

  std::string source_address() const;

  u_short ether_type() const;

  int next_header_id() const override;

  std::string entity_name() const override;

  sniffer::common::serialization::SerializedObject Serialize(
      const sniffer::common::serialization::SerializationMgr& serializer)
      const override;

  sniffer::common::serialization::SerializedObject Summarise(
      const sniffer::common::serialization::SerializationMgr& serializer)
      const override;

 private:
  static constexpr int ADDRESS_LENGTH = 6;

  const formats::Ethernet* data_;
};

REGISTER_SUBCLASS(Header, EthernetHeader, int, SniffedPacket*)

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer

#endif  // SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_ETHERNET_HEADER_H_
