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

#include "core/websocket_server_action_handler.h"

#include <spdlog/spdlog.h>

namespace sniffer {

namespace core {

void WebSocketServerActionHandler::OnOpen(connection_hdl handle) {
  {
    lock_guard<mutex> guard(action_lock_);
    actions_.push(action(SUBSCRIBE, handle));
  }

  action_cond_.notify_one();
}

void WebSocketServerActionHandler::OnClose(connection_hdl handle) {
  {
    lock_guard<mutex> guard(action_lock_);
    actions_.push(action(UNSUBSCRIBE, handle));
  }

  action_cond_.notify_one();
}

void WebSocketServerActionHandler::OnMessage(connection_hdl handle,
                                             message_ptr_t message) {
  {
    lock_guard<mutex> guard(action_lock_);
    actions_.push(action(MESSAGE, handle, message));
  }

  action_cond_.notify_one();
}

void WebSocketServerActionHandler::handle(WebSocketServer* server) {
  while (1) {
    unique_lock<mutex> lock(action_lock_);

    while (actions_.empty()) {
      action_cond_.wait(lock);
    }

    action current_action = actions_.front();
    actions_.pop();

    lock.unlock();

    if (current_action.type == SUBSCRIBE) {
      lock_guard<mutex> guard(connection_lock_);
      server->add_connection(current_action.handle);
    } else if (current_action.type == UNSUBSCRIBE) {
      lock_guard<mutex> guard(connection_lock_);
      server->remove_connection(current_action.handle);
    } else if (current_action.type == MESSAGE) {
      lock_guard<mutex> guard(connection_lock_);
      spdlog::get("console")->info("Received message: {0}",
                                   current_action.message->get_payload());
      command_invoker_->Invoke(
          server->GetConnectionDataFromHandle(current_action.handle),
          current_action.message->get_payload());
    } else {
      spdlog::get("console")->info(
          "The WebSocket server received an action that cannot be handled.");
    }
  }
}

}  // namespace core

}  // namespace sniffer
