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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_PACKET_SNIFFER_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_PACKET_SNIFFER_H_

#include <memory>
#include <string>
#include <vector>

#include "common/policy_bindings.h"
#include "core/layer_stack.h"

namespace sniffer {

namespace core {

class Server;

class PacketSniffer {
 public:
  PacketSniffer(const std::string& interface, const std::string& filter,
                const sniffer::common::config::ConfigurationMgr& config,
                const LayerStack& stack, Server* server);

  virtual ~PacketSniffer() {}

  void Start();

 protected:
  std::string interface_;

  std::string filter_;

  sniffer::common::config::ConfigurationMgr config_manager_;

  LayerStack stack_;

  Server* server_;

  virtual void PrepareInterfaces() = 0;

  virtual void ParseFilters() = 0;

  virtual void ApplyFilters() = 0;

  virtual void Sniff() = 0;
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_PACKET_SNIFFER_H_
