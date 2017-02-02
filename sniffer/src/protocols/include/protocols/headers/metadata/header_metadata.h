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

#ifndef SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_METADATA_HEADER_METADATA_H_
#define SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_METADATA_HEADER_METADATA_H_

#include <sys/types.h>

#include <map>
#include <string>

namespace sniffer {

namespace protocols {

class SniffedPacket;

namespace headers {

namespace metadata {

class HeaderMetadata {
 public:
  HeaderMetadata(std::map<std::string, int> lower_layer_id_mappings,
                 std::string name, int length, int minimum_length,
                 bool has_variable_length, int length_field_offset,
                 bool accounts_for_payload_length);

  virtual ~HeaderMetadata() {}

  std::map<std::string, int> lower_layer_id_mappings() const;

  std::string name() const;

  int length() const;

  int minimum_length() const;

  bool has_variable_length() const;

  int length_field_offset() const;

  bool accounts_for_payload_length() const;

  void AccountForPayloadLength(SniffedPacket* packet) const;

  virtual void set_length(const u_char* length_field);

 protected:
  int length_;

 private:
  std::map<std::string, int> lower_layer_id_mappings_;
  std::string name_;
  int minimum_length_;
  bool has_variable_length_;
  int length_field_offset_;
  bool accounts_for_payload_length_;
};

}  // namespace metadata

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer

#endif  // SNIFFER_SRC_PROTOCOLS_INCLUDE_PROTOCOLS_HEADERS_METADATA_HEADER_METADATA_H_
