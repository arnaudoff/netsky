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

#include "core/websocket_server_event_handler.h"

#include <spdlog/spdlog.h>

#include "core/server_command_invoker.h"
#include "core/websocket_server.h"
#include "core/websocket_server_event.h"
#include "core/websocket_server_event_type.h"

namespace sniffer {

namespace core {

/**
 * @brief Constructs a WebSocketEventHandler object.
 *
 * @param invoker A pointer to the command invoker to use.
 */
WebSocketServerEventHandler::WebSocketServerEventHandler(
    ServerCommandInvoker* invoker)
    : command_invoker_{invoker} {}

/**
 * @brief Defines a callback that is invoked from websocketpp as soon as
 * a client connects. The addition of the WebSocketServerEvent to process to the
 * queue of events to be processed is thread and exception safe (lock_guard).
 *
 * Thread safety is required because the processing thread may be processing an
 * event already while a new event is to be handled.
 *
 * This function is normally executed on the main thread, since the
 * websocketpp run() method which internally calls io_service.run() of
 * Boost.Asio registers the handlers to the main thread.
 *
 * @param handle The handle for the recently connected client
 */
void WebSocketServerEventHandler::OnConnectionOpened(
    websocketpp::connection_hdl handle) {
  {
    std::lock_guard<std::mutex> guard(event_lock_);
    events_.push(
        WebSocketServerEvent(WebSocketServerEventType::kConnect, handle));
  }

  // Wake up the processing thread
  event_cond_.notify_one();
}

/**
 * @brief Defines a callback that is invoked from websocketpp as soon as
 * a client disconnects. The addition of the WebSocketServerEvent to process to
 * the queue of events to be processed is thread and exception safe
 * (lock_guard).
 *
 * Thread safety is required because the processing thread may be processing an
 * event already while a new event is to be handled.
 *
 * This function is normally executed on the main thread, since the
 * websocketpp run() method which internall calls io_service.run() of Boost.Asio
 * registers the handlers to the main thread.
 *
 * @param handle The handle for the recently disconnected client
 */
void WebSocketServerEventHandler::OnConnectionClosed(
    websocketpp::connection_hdl handle) {
  {
    std::lock_guard<std::mutex> guard(event_lock_);
    events_.push(
        WebSocketServerEvent(WebSocketServerEventType::kDisconnect, handle));
  }

  // Wake up the processing thread
  event_cond_.notify_one();
}

/**
 * @brief Defines a callback that is invoked from websocketpp as soon as
 * a client sends a message through the WebSocket channel. The addition of the
 * WebSocketServerEvent to process to the queue of events to be processed is
 * thread and exception safe (lock_guard).
 *
 * Thread safety is required because the processing thread may be processing an
 * event already while a new event is to be handled.
 *
 * This function is normally executed on the main thread, since the
 * websocketpp run() method which internall calls io_service.run() of Boost.Asio
 * registers the handlers to the main thread.
 *
 * @param handle The handle for the client that sent a message
 *
 * @param message A pointer to the message
 */
void WebSocketServerEventHandler::OnMessageReceived(
    websocketpp::connection_hdl handle,
    websocketpp::server<websocketpp::config::asio>::message_ptr message) {
  {
    std::lock_guard<std::mutex> guard(event_lock_);
    events_.push(WebSocketServerEvent(WebSocketServerEventType::kMessage,
                                      handle, message));
  }

  // Wake up the processing thread
  event_cond_.notify_one();
}

/**
 * @brief This function defines how received events are processed. Since it runs
 * in a separate processing thread, a condition variable (event_cond_) is used
 * to wait on until the main thread receives an event and notifies
 * the processing thread to handle it. In the producer-consumer terms, this is
 * the consumer thread.
 *
 * @param server A pointer to the current WebSocketServer instance
 */
void WebSocketServerEventHandler::Handle(WebSocketServer* server) {
  while (1) {
    std::unique_lock<std::mutex> lock(event_lock_);

    // The lambda prevents from spurious wake-ups
    event_cond_.wait(lock, [this] { return !events_.empty(); });

    WebSocketServerEvent current_event = events_.front();
    events_.pop();

    lock.unlock();

    if (current_event.type == WebSocketServerEventType::kConnect) {
      server->AddClient(current_event.handle);
    } else if (current_event.type == WebSocketServerEventType::kDisconnect) {
      server->RemoveClient(current_event.handle);
    } else if (current_event.type == WebSocketServerEventType::kMessage) {
      command_invoker_->Invoke(
          server->GetConnectionIdFromHandle(current_event.handle),
          current_event.message->get_payload());
    } else {
      spdlog::get("console")->info(
          "The WebSocket server received an event that cannot be handled.");
    }
  }
}

}  // namespace core

}  // namespace sniffer
