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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_HEX_ASCII_PAYLOAD_INTERPRETER_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_HEX_ASCII_PAYLOAD_INTERPRETER_H_

#include <string>

#include "core/payload_interpreter.h"

namespace sniffer {

namespace core {

class HexAsciiPayloadInterpreter : public PayloadInterpreter {
 public:
  std::string Interpret(const u_char* payload, int length) override;

  ~HexAsciiPayloadInterpreter() override;

 private:
  const int kBytesPerLine = 16;

  std::string InterpretLine(const u_char* payload, int length, int offset);
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_HEX_ASCII_PAYLOAD_INTERPRETER_H_

