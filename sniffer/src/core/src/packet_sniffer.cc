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

#include <string>
#include <vector>

#include "common/policy_bindings.h"
#include "core/layer_stack.h"
#include "core/packet_sniffer.h"
#include "core/server.h"

namespace sniffer {

namespace core {

PacketSniffer::PacketSniffer(
    std::vector<std::string> interfaces, std::vector<std::string> filters,
    const sniffer::common::config::ConfigurationMgr& config,
    const LayerStack& stack, Server* server)
    : interfaces_{interfaces},
      filters_{filters},
      config_manager_{config},
      stack_{stack},
      server_{server} {}

void PacketSniffer::Start() {
  PrepareInterfaces();

  if (!filters_.empty()) {
    ParseFilters();
    ApplyFilters();
  }

  Sniff();
}

}  // namespace core

}  // namespace sniffer
