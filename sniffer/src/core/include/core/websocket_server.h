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

#ifndef SNIFFER_SRC_CORE_WEBSOCKET_SERVER_H_
#define SNIFFER_SRC_CORE_WEBSOCKET_SERVER_H_

#include "core/server.h"

#include <map>     // NOLINT
#include <memory>  // NOLINT
#include <string>  // NOLINT

#include <websocketpp/common/thread.hpp>       // NOLINT
#include <websocketpp/config/asio_no_tls.hpp>  // NOLINT
#include <websocketpp/server.hpp>              // NOLINT

#include "core/websocket_server_action_handler.h"

namespace sniffer {

namespace core {

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
using websocketpp::lib::thread;

class WebSocketServer : public Server {
 public:
  WebSocketServer(const ConfigurationMgr& manager,
                  std::unique_ptr<WebSocketServerActionHandler> handler);

  ~WebSocketServer() {}

  void Start(uint16_t port) override;

  void Stop() override;

  void Unicast(const ConnectionData& con_data, const std::string& msg) override;

  void Broadcast(const std::string& message) override;

  void AddConnection(connection_hdl handle);

  void RemoveConnection(connection_hdl handle);

  ConnectionData GetConnectionDataFromHandle(connection_hdl hdl);

 private:
  typedef websocketpp::server<websocketpp::config::asio> server_t;
  typedef std::map<connection_hdl, ConnectionData,
                   std::owner_less<connection_hdl>>
      connection_list_t;

  std::unique_ptr<WebSocketServerActionHandler> action_handler_;
  server_t server_;
  connection_list_t connections_;

  void Run(uint16_t port);
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_WEBSOCKET_SERVER_H_
