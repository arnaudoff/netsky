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

#ifndef SNIFFER_SRC_CORE_SERVER_H_
#define SNIFFER_SRC_CORE_SERVER_H_

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "common/policy_bindings.h"
#include "core/connection_data.h"
#include "core/packet_sniffer.h"

namespace sniffer {

namespace core {

class Server {
 public:
  explicit Server(const ConfigurationMgr& manager);

  virtual ~Server() {}

  void set_sniffer(std::unique_ptr<PacketSniffer> sniffer);

  PacketSniffer* sniffer() const;

  ConfigurationMgr config_manager() const;

  virtual void Start(uint16_t port) = 0;

  virtual void Stop() = 0;

  virtual void Unicast(const ConnectionData& connection,
                       const std::string& msg) = 0;

  virtual void Broadcast(const std::string& message) = 0;

 protected:
  std::unique_ptr<PacketSniffer> sniffer_;
  ConfigurationMgr config_manager_;
  int session_id_;
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_SERVER_H_
