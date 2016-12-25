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

#include "core/websocket_server.h"
#include "core/websocket_server_action_handler.h"

#include <utility>

#include <spdlog/spdlog.h>  // NOLINT

namespace sniffer {

namespace core {

WebSocketServer::WebSocketServer(
    const ConfigurationMgr& manager,
    std::unique_ptr<WebSocketServerActionHandler> handler)
    : Server(manager), action_handler_{std::move(handler)} {
  server_.init_asio();
  server_.set_open_handler(
      bind(&WebSocketServerActionHandler::OnOpen, action_handler_.get(), ::_1));

  server_.set_close_handler(bind(&WebSocketServerActionHandler::OnClose,
                                 action_handler_.get(), ::_1));

  server_.set_message_handler(bind(&WebSocketServerActionHandler::OnMessage,
                                   action_handler_.get(), ::_1, ::_2));
}

void WebSocketServer::Run(uint16_t port) {
  server_.listen(port);
  server_.start_accept();

  try {
    server_.run();
  } catch (const std::exception& e) {
    spdlog::get("console")->critical("Running the WebSocket server failed: {0}",
                                     e.what());
  }
}

void WebSocketServer::Start(uint16_t port) {
  try {
    thread t(bind(&WebSocketServerActionHandler::Handle, action_handler_.get(),
                  this));
    Run(port);

    t.join();
  } catch (websocketpp::exception const& e) {
    spdlog::get("console")->critical("Running the WebSocket server failed: {0}",
                                     e.what());
  }
}

void WebSocketServer::Stop() { server_.stop_listening(); }

void WebSocketServer::Unicast(const ConnectionData& con_data,
                              const std::string& msg) {
  for (auto it = connections_.begin(); it != connections_.end(); ++it) {
    if (it->second == con_data) {
      server_.send(it->first, msg, websocketpp::frame::opcode::text);
      break;
    }
  }
}

void WebSocketServer::Broadcast(const std::string& message) {
  connection_list_t::iterator it;
  for (it = connections_.begin(); it != connections_.end(); ++it) {
    server_.send(it->first, message, websocketpp::frame::opcode::text);
  }
}

void WebSocketServer::AddConnection(connection_hdl handle) {
  ConnectionData data{session_id_++};
  connections_[handle] = data;

  // TODO(arnaudoff): use connection::get_remote_endpoint() here
  spdlog::get("console")->info("Session established: {0}",
                               data.get_session_id());
}

void WebSocketServer::RemoveConnection(connection_hdl handle) {
  auto data = GetConnectionDataFromHandle(handle);

  connections_.erase(handle);

  // TODO(arnaudoff): use connection::get_remote_endpoint() here
  spdlog::get("console")->info("Session killed: {0}", data.get_session_id());
}

ConnectionData WebSocketServer::GetConnectionDataFromHandle(
    connection_hdl hdl) {
  auto it = connections_.find(hdl);

  if (it == connections_.end()) {
    throw std::invalid_argument("No connection data avaliable for this handle");
  }

  return it->second;
}

}  // namespace core

}  // namespace sniffer
