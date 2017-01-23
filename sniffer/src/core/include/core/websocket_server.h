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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_WEBSOCKET_SERVER_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_WEBSOCKET_SERVER_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "websocketpp/config/asio.hpp"
#include "websocketpp/server.hpp"

#include "common/policy_bindings.h"
#include "core/server.h"

namespace sniffer {

namespace core {

class WebSocketServerEventHandler;

class WebSocketServer : public Server {
 public:
  WebSocketServer(
      const sniffer::common::config::ConfigurationMgr& config_manager,
      std::unique_ptr<WebSocketServerEventHandler> handler,
      const std::string& password);

  ~WebSocketServer(){};

  void Start(uint16_t port) override;

  void Stop() override;

  void Unicast(int connection_id, const std::string& msg) override;

  void Broadcast(const std::string& message) override;

  void AuthenticatedBroadcast(const std::string& message) override;

  void AddConnection(int connection_id) override;

  void RemoveConnection(int connection_id) override;

  void Authenticate(int connection_id) override;

  bool IsClientAuthenticated(int connection_id) override;

  void AddClient(websocketpp::connection_hdl handle);

  void RemoveClient(websocketpp::connection_hdl handle);

  int GetConnectionIdFromHandle(websocketpp::connection_hdl handle) const;

  bool CompareClients(const websocketpp::connection_hdl& first_handle,
                      const websocketpp::connection_hdl& second_handle) const;

  int next_connection_id() const;

 private:
  websocketpp::server<websocketpp::config::asio_tls> server_;

  std::unique_ptr<WebSocketServerEventHandler> event_handler_;

  std::map<int, websocketpp::connection_hdl> ws_connections_map_;

  // https://channel9.msdn.com/posts/C-and-Beyond-2012-Herb-Sutter-You-dont-know-blank-and-blank

  mutable std::mutex ws_connections_map_lock_;

  int next_connection_id_;

  mutable std::mutex next_connection_id_lock_;

  mutable std::mutex connections_lock_;

  mutable std::mutex authenticated_connections_lock_;

  void Run(uint16_t port);
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_WEBSOCKET_SERVER_H_
