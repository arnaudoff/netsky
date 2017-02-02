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

#include "core/hex_ascii_payload_interpreter.h"

#include <ctype.h>
#include <iomanip>
#include <sstream>
#include <string>

namespace sniffer {

namespace core {

HexAsciiPayloadInterpreter::~HexAsciiPayloadInterpreter() {}

/**
 * @brief Interprets an array of bytes which is normally the payload of a
 * SniffedPacket.
 *
 * @param payload A pointer to the beginning of a byte array with the payload.
 * @param length Length of the byte array.
 *
 * @return String containing interpreted lines.
 */
std::string HexAsciiPayloadInterpreter::Interpret(const u_char* payload,
                                                  int length) {
  if (length <= 0) {
    return "none";
  }

  const u_char* index_ptr = payload;
  int offset = 0;

  if (length <= kBytesPerLine) {
    auto res = InterpretLine(index_ptr, length, offset);
    return res;
  }

  int remaining_length = length;
  int current_line_length = 0;
  std::ostringstream out;

  while (true) {
    current_line_length = kBytesPerLine % remaining_length;

    out << InterpretLine(index_ptr, current_line_length, offset);

    remaining_length -= current_line_length;
    index_ptr += current_line_length;
    offset += kBytesPerLine;

    if (remaining_length <= kBytesPerLine) {
      out << InterpretLine(index_ptr, remaining_length, offset);
      break;
    }
  }

  return out.str();
}

/**
 * @brief Interprets an array of raw bytes to the format:
 *
 * OFFSET   HEX   ASCII
 *
 * Sample output:
 *
 * 00000   37 35 34 30 2f 2f 4f 54  54 5a 3f 31 2e 31 0d 0a   GET /index.htm ...
 *
 * @param payload Pointer to the beginning of the array.
 * @param length Length of the byte array.
 * @param offset Offset from the previous line.
 *
 * @return An interpreted line.
 */
std::string HexAsciiPayloadInterpreter::InterpretLine(const u_char* payload,
                                                      int length, int offset) {
  std::ostringstream out;
  const u_char* index_ptr = payload;

  // Offset
  out << std::setw(5) << std::setfill('0') << offset << "   ";

  for (int i = 0; i < length; i++) {
    out << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(*index_ptr) << " ";
    index_ptr++;

    // Print extra space after 8th byte
    if (i == 7) {
      out << " ";
    }
  }

  // Print space to handle lines less than 8 bytes
  if (length < 8) {
    out << " ";
  }

  // Fill hex gap with spaces
  int gap_length_to_fill;
  if (length < 16) {
    gap_length_to_fill = 16 - length;

    for (int i = 0; i < gap_length_to_fill; i++) {
      out << "   ";
    }
  }

  out << "   ";

  // Print ASCII if it's printable
  index_ptr = payload;
  for (int i = 0; i < length; i++) {
    if (isprint(*index_ptr)) {
      out << *index_ptr;
    } else {
      out << ".";
    }

    index_ptr++;
  }

  out << std::endl;

  return out.str();
}

}  // namespace core

}  // namespace sniffer
