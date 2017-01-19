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
#include "core/websocket_server_tls_mode.h"

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
    websocketpp::config::asio::message_type::ptr message) {
  {
    std::lock_guard<std::mutex> guard(event_lock_);
    events_.push(WebSocketServerEvent(WebSocketServerEventType::kMessage,
                                      handle, message));
  }

  // Wake up the processing thread
  event_cond_.notify_one();
}

websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context>
WebSocketServerEventHandler::OnTlsInit(WebSocketServerTlsMode mode,
                                       WebSocketServer* ws_server,
                                       websocketpp::connection_hdl handle) {
  namespace asio = websocketpp::lib::asio;

  websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> ctx =
      websocketpp::lib::make_shared<asio::ssl::context>(
          asio::ssl::context::sslv23);

  try {
    if (mode == WebSocketServerTlsMode::kMozillaModern) {
      // Modern disables TLSv1
      ctx->set_options(
          asio::ssl::context::default_workarounds |
          asio::ssl::context::no_sslv2 | asio::ssl::context::no_sslv3 |
          asio::ssl::context::no_tlsv1 | asio::ssl::context::single_dh_use);
    } else {
      ctx->set_options(asio::ssl::context::default_workarounds |
                       asio::ssl::context::no_sslv2 |
                       asio::ssl::context::no_sslv3 |
                       asio::ssl::context::single_dh_use);
    }

    ctx->set_password_callback(std::bind(&WebSocketServer::password, ws_server));
    ctx->use_certificate_chain_file("../../config/server.pem");
    ctx->use_private_key_file("../../config/server.pem",
                              asio::ssl::context::pem);
    ctx->use_tmp_dh_file("../../config/dh.pem");

    std::string ciphers;

    if (mode == WebSocketServerTlsMode::kMozillaModern) {
      ciphers =
          "ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-"
          "AES256-GCM-SHA384:ECDHE-ECDSA-AES256-GCM-SHA384:DHE-RSA-AES128-GCM-"
          "SHA256:DHE-DSS-AES128-GCM-SHA256:kEDH+AESGCM:ECDHE-RSA-AES128-"
          "SHA256:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA:ECDHE-ECDSA-"
          "AES128-SHA:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES256-SHA384:ECDHE-"
          "RSA-AES256-SHA:ECDHE-ECDSA-AES256-SHA:DHE-RSA-AES128-SHA256:DHE-RSA-"
          "AES128-SHA:DHE-DSS-AES128-SHA256:DHE-RSA-AES256-SHA256:DHE-DSS-"
          "AES256-SHA:DHE-RSA-AES256-SHA:!aNULL:!eNULL:!EXPORT:!DES:!RC4:!3DES:"
          "!MD5:!PSK";
    } else {
      ciphers =
          "ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-"
          "AES256-GCM-SHA384:ECDHE-ECDSA-AES256-GCM-SHA384:DHE-RSA-AES128-GCM-"
          "SHA256:DHE-DSS-AES128-GCM-SHA256:kEDH+AESGCM:ECDHE-RSA-AES128-"
          "SHA256:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA:ECDHE-ECDSA-"
          "AES128-SHA:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES256-SHA384:ECDHE-"
          "RSA-AES256-SHA:ECDHE-ECDSA-AES256-SHA:DHE-RSA-AES128-SHA256:DHE-RSA-"
          "AES128-SHA:DHE-DSS-AES128-SHA256:DHE-RSA-AES256-SHA256:DHE-DSS-"
          "AES256-SHA:DHE-RSA-AES256-SHA:AES128-GCM-SHA256:AES256-GCM-SHA384:"
          "AES128-SHA256:AES256-SHA256:AES128-SHA:AES256-SHA:AES:CAMELLIA:DES-"
          "CBC3-SHA:!aNULL:!eNULL:!EXPORT:!DES:!RC4:!MD5:!PSK:!aECDH:!EDH-DSS-"
          "DES-CBC3-SHA:!EDH-RSA-DES-CBC3-SHA:!KRB5-DES-CBC3-SHA";
    }

    if (SSL_CTX_set_cipher_list(ctx->native_handle(), ciphers.c_str()) != 1) {
      std::cout << "Error setting cipher list" << std::endl;
    }
  } catch (std::exception& e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  return ctx;
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
