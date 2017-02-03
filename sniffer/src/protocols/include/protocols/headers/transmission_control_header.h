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

#ifndef SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_TRANSMISSION_CONTROL_HEADER_H_
#define SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_TRANSMISSION_CONTROL_HEADER_H_

#include <sys/types.h>
#include <string>

#include "registry.h"
#include "protocols/headers/header.h"

namespace sniffer {

namespace protocols {

namespace headers {

namespace formats {

struct TransmissionControl;

}  // namespace formats

class TransmissionControlHeader : public Header {
 public:
  TransmissionControlHeader(int length, SniffedPacket* packet);

  ~TransmissionControlHeader() {}

  u_short source_port() const;

  u_short destination_port() const;

  u_int sequence_number() const;

  u_int acknowledgment_number() const;

  u_char urg_flag() const;

  u_char ack_flag() const;

  u_char psh_flag() const;

  u_char rst_flag() const;

  u_char syn_flag() const;

  u_char fin_flag() const;

  u_short window() const;

  u_short checksum() const;

  u_short urgent_pointer() const;

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
  const formats::TransmissionControl* data_;
};

REGISTER_SUBCLASS(Header, TransmissionControlHeader, int, SniffedPacket*)

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer

#endif  // SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_TRANSMISSION_CONTROL_HEADER_H_
