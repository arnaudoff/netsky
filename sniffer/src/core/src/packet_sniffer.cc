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
#include <thread>

#include "common/policy_bindings.h"
#include "core/layer_stack.h"
#include "core/packet_sniffer.h"
#include "core/server.h"

namespace sniffer {

namespace core {

/**
 * @brief Constructs a PacketSniffer object.
 *
 * @param interface The interface to sniff on.
 * @param filter The filter to apply.
 * @param config The ConfigurationMgr to use when fetching config values.
 * @param stack The LayerStack to use for parsing.
 * @param server The server for which the sniffer is created.
 */
PacketSniffer::PacketSniffer(
    const std::string& interface, const std::string& filter,
    const sniffer::common::config::ConfigurationMgr& config,
    const LayerStack& stack, Server* server)
    : interface_{interface},
      filter_{filter},
      config_manager_{config},
      stack_{stack},
      server_{server},
      sniffing_thread_{} {}

/**
 * @brief Starts the packet sniffer.
 */
void PacketSniffer::Start() {
  PrepareInterfaces();

  if (!filter_.empty()) {
    ParseFilters();
  }

  if (!filter_.empty()) {
    ApplyFilters();
  }

  Sniff();
}

/**
 * @brief Runs the Start method in a separate sniffing thread.
 */
void PacketSniffer::Run() {
  sniffing_thread_ = std::thread(&PacketSniffer::Start, this);
}

/**
 * @brief Destructs the sniffer by stopping the underlying thread.
 */
PacketSniffer::~PacketSniffer() {
  if (sniffing_thread_.joinable()) {
    sniffing_thread_.join();
  }
}

}  // namespace core

}  // namespace sniffer
