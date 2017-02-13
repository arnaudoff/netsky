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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_SERVER_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_SERVER_H_

#include <memory>
#include <set>
#include <string>

#include "common/policy_bindings.h"

namespace sniffer {

namespace core {

class PacketSniffer;

class Server {
 public:
  Server(const sniffer::common::config::ConfigurationMgr& manager,
         const std::string& password);

  virtual ~Server();

  PacketSniffer* sniffer() const;

  void set_sniffer(std::unique_ptr<PacketSniffer> sniffer);

  std::set<int> connections() const;

  std::set<int> authenticated_connections() const;

  std::string password() const;

  sniffer::common::config::ConfigurationMgr config_manager() const;

  virtual bool has_host_connection() const;

  virtual int host_connection() const;

  virtual void set_host_connection(int connection_id);

  virtual void Start(uint16_t port) = 0;

  virtual void Stop() = 0;

  virtual void Unicast(int connection_id, const std::string& msg) = 0;

  virtual void Broadcast(const std::string& message);

  virtual void AuthenticatedBroadcast(const std::string& message);

  virtual void AddConnection(int connection_id);

  virtual void RemoveConnection(int connection_id);

  virtual void StopSniffer();

  virtual void Authenticate(int connection_id);

  virtual bool IsClientAuthenticated(int connection_id);

 protected:
  sniffer::common::config::ConfigurationMgr config_manager_;

  std::unique_ptr<PacketSniffer> sniffer_;

  std::set<int> connections_;

  std::set<int> authenticated_connections_;

  int host_connection_;

  bool has_host_connection_;

  std::string password_;
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_SERVER_H_
