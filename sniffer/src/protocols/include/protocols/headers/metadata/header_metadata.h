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

#ifndef SNIFFER_SRC_PROTOCOLS_HEADERS_METADATA_HEADER_METADATA_H_
#define SNIFFER_SRC_PROTOCOLS_HEADERS_METADATA_HEADER_METADATA_H_

#include <sys/types.h>

#include <string>

namespace sniffer {

namespace protocols {

namespace headers {

namespace metadata {

class HeaderMetadata {
 public:
  HeaderMetadata(int id, std::string name, int length, bool has_variable_length,
                 int length_field_offset = 0);

  virtual ~HeaderMetadata() {}

  int id() const;

  std::string name() const;

  int length() const;

  bool has_variable_length() const;

  int length_field_offset() const;

  virtual int CalculateLength(const u_char* length_field) const;

 private:
  int id_;
  std::string name_;
  int length_;
  bool has_variable_length_;
  int length_field_offset_;
};

}  // namespace metadata

}  // namespace headers

}  // namespace protocols

}  // namespace sniffer

#endif  // SNIFFER_SRC_PROTOCOLS_HEADERS_METADATA_HEADER_METADATA_H_