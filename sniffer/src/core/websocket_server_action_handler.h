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

#ifndef SNIFFER_SRC_CORE_WEBSOCKET_SERVER_ACTION_HANDLER_H_
#define SNIFFER_SRC_CORE_WEBSOCKET_SERVER_ACTION_HANDLER_H_

#include <queue>

#include <websocketpp/common/thread.hpp>       // NOLINT
#include <websocketpp/config/asio_no_tls.hpp>  // NOLINT
#include <websocketpp/server.hpp>              // NOLINT

#include "core/server_command_invoker.h"
#include "core/websocket_server.h"

namespace sniffer {

namespace core {

using websocketpp::connection_hdl;
using websocketpp::lib::mutex;
using websocketpp::lib::lock_guard;
using websocketpp::lib::unique_lock;
using websocketpp::lib::condition_variable;

typedef websocketpp::server<websocketpp::config::asio>::message_ptr
    message_ptr_t;

enum action_type { SUBSCRIBE, UNSUBSCRIBE, MESSAGE };

struct action {
  action(action_type type, connection_hdl handle)
      : type{type}, handle{handle} {}

  action(action_type type, connection_hdl handle, message_ptr_t msg)
      : type{type}, handle{handle}, message{msg} {}

  action_type type;
  connection_hdl handle;
  message_ptr_t message;
};

class WebSocketServerActionHandler {
 public:
  explicit WebSocketServerActionHandler(ServerCommandInvoker* invoker)
      : command_invoker_{invoker} {}

  void OnOpen(connection_hdl handle);

  void OnClose(connection_hdl handle);

  void OnMessage(connection_hdl handle, message_ptr_t msg);

  void Handle(WebSocketServer* server);

 private:
  ServerCommandInvoker* command_invoker_;

  std::queue<action> actions_;

  mutex action_lock_;
  mutex connection_lock_;
  condition_variable action_cond_;
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_WEBSOCKET_SERVER_ACTION_HANDLER_H_
