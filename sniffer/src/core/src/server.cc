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

#include "core/server.h"

#include <utility>

namespace sniffer {

namespace core {

Server::Server(const ConfigurationMgr& manager)
    : config_manager_{manager}, session_id_{0} {}

void Server::set_sniffer(std::unique_ptr<PacketSniffer> sniffer) {
  sniffer_ = std::move(sniffer);
}

PacketSniffer* Server::sniffer() const { return sniffer_.get(); }

ConfigurationMgr Server::config_manager() const { return config_manager_; }

}  // namespace core

}  // namespace sniffer
