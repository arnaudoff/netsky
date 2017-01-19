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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_WEBSOCKET_SERVER_EVENT_HANDLER_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_WEBSOCKET_SERVER_EVENT_HANDLER_H_

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

#include "websocketpp/config/asio.hpp"  // NOLINT
#include "websocketpp/server.hpp"       // NOLINT

#include "core/websocket_server_event.h"
#include "core/websocket_server_tls_mode.h"

namespace sniffer {

namespace core {

class ServerCommandInvoker;

class WebSocketServer;

class WebSocketServerEventHandler {
 public:
  explicit WebSocketServerEventHandler(ServerCommandInvoker* invoker);

  void OnConnectionOpened(websocketpp::connection_hdl handle);

  void OnConnectionClosed(websocketpp::connection_hdl handle);

  void OnMessageReceived(websocketpp::connection_hdl handle,
                         websocketpp::config::asio::message_type::ptr msg);

  websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> OnTlsInit(
      WebSocketServerTlsMode mode, WebSocketServer* ws_server,
      websocketpp::connection_hdl handle);

  void Handle(WebSocketServer* ws_server);

 private:
  ServerCommandInvoker* command_invoker_;

  std::queue<WebSocketServerEvent> events_;

  std::mutex event_lock_;

  std::condition_variable event_cond_;
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_WEBSOCKET_SERVER_EVENT_HANDLER_H_
