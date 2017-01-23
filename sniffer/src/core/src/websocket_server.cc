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

#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

#include <spdlog/spdlog.h>  // NOLINT

#include "common/policy_bindings.h"
#include "core/websocket_server_event_handler.h"
#include "core/websocket_server_tls_mode.h"

namespace sniffer {

namespace core {

/**
 * @brief Constructs a WebSocketServer object which in turn is a wrapper
 * around a websocketpp server. The constructor initializes Boost.Asio and
 * sets the async IO handlers for handling new connections, disconnects and
 * new messages that are defined in WebSocketEventHandler.
 *
 * @param manager The ConfigurationManager to use
 * @param handler Event handler object to use
 * @param password The server password used for authentication of clients
 */
WebSocketServer::WebSocketServer(
    const common::config::ConfigurationMgr& config_manager,
    std::unique_ptr<WebSocketServerEventHandler> handler,
    const std::string& password)
    : Server{config_manager, password},
      event_handler_{std::move(handler)},
      next_connection_id_{0} {
  server_.init_asio();

  server_.set_open_handler(
      std::bind(&WebSocketServerEventHandler::OnConnectionOpened,
                event_handler_.get(), websocketpp::lib::placeholders::_1));

  server_.set_close_handler(
      std::bind(&WebSocketServerEventHandler::OnConnectionClosed,
                event_handler_.get(), websocketpp::lib::placeholders::_1));

  server_.set_message_handler(std::bind(
      &WebSocketServerEventHandler::OnMessageReceived, event_handler_.get(),
      websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));

  server_.set_tls_init_handler(
      std::bind(&WebSocketServerEventHandler::OnTlsInit, event_handler_.get(),
                WebSocketServerTlsMode::kMozillaIntermediate, this,
                websocketpp::lib::placeholders::_1));
}

/**
 * @brief In a nutshell, this function sets the internals of Boost.Asio. Note
 * that it invokes the run() method of websocketpp, which in turn invokes the
 * boost::asio::io_service. Therefore, the WebSocketServerEventHandler handlers
 * are executed within the main thread.
 *
 * @param port The port to use for listening
 */
void WebSocketServer::Run(uint16_t port) {
  server_.listen(port);
  server_.start_accept();

  try {
    server_.run();
  } catch (const std::exception& e) {
    spdlog::get("console")->critical("The WS server failed: {0}", e.what());
  }
}

/**
 * @brief Starts a new WebSocket server by spawning a processing thread, passing
 * a pointer to the Handle member function of the WebSocketServerEventHandler
 * class. It is used as a processing function for the incoming events.
 * Additionally, the thread is passed the address of the event_handler_ resource
 * that is held by the WebSocketServer so that the processing function is
 * invoked on the new thread. Also, the processing function is passed a pointer
 * to the current instance of the WebSocketServer.
 *
 * WebSocket++ handlers block core networking functions. In general, to maintain
 * responsiveness at high message rates handlers SHOULD pass processing requests
 * off to a processing thread to actually perform the work. This way, for
 * example, new messages can be received while sending.
 *
 * @param port The port on which the WebSocketServer should listen on.
 */
void WebSocketServer::Start(uint16_t port) {
  try {
    std::thread processing_thread(std::bind(
        &WebSocketServerEventHandler::Handle, event_handler_.get(), this));

    // Run the Boost.Asio loop on the main thread
    Run(port);

    // Wait for the processing thread to finish (and not detach it); p.17
    // C++ Concurrency in action, p. 17
    processing_thread.join();
  } catch (const websocketpp::exception& e) {
    spdlog::get("console")->critical("The WS server failed: {0}", e.what());
  }
}

/**
 * @brief Stops the WebSocketServer by calling the internal stop_listening()
 * function on the websocketpp server.
 */
void WebSocketServer::Stop() { server_.stop_listening(); }

/**
 * @brief Sends a specific message to a specific client by calling send() on the
 * server with the corresponding websocketpp::connection_hdl.
 *
 * @param connection_id The connection ID of the receiver
 * @param msg The specific message to send
 */
void WebSocketServer::Unicast(int connection_id, const std::string& message) {
  std::lock_guard<std::mutex> map_guard(ws_connections_map_lock_);

  server_.send(ws_connections_map_[connection_id], message,
               websocketpp::frame::opcode::text);
}

/**
 * @brief Sends the specified message to all currently connected clients
 *
 * @param message The message to send
 */
void WebSocketServer::Broadcast(const std::string& message) {
  std::lock_guard<std::mutex> connections_guard(connections_lock_);

  Server::Broadcast(message);
}

/**
 * @brief Sends the specified message to all currently connected AND
 * authenticated clients
 *
 * @param message The message to send
 */
void WebSocketServer::AuthenticatedBroadcast(const std::string& message) {
  std::lock_guard<std::mutex> auth_con_guard(authenticated_connections_lock_);

  Server::AuthenticatedBroadcast(message);
}

/**
 * @brief Adds a connection to the abstract server connections list. The
 * addition of the connection ID is thread-safe, because the WebSocket
 * implementation of a Server calls this function on it's processing thread;
 * meanwhile the main thread could try to read the set of connections and
 * therefore introduce a data race.
 *
 * @param connection_id The ID of the connection which uniquely identifies it
 */
void WebSocketServer::AddConnection(int connection_id) {
  std::lock_guard<std::mutex> guard(connections_lock_);

  Server::AddConnection(connection_id);
}

/**
 * @brief Removes a connection from the abstract server connections list. The
 * removal of the connection ID is thread-safe, because the WebSocket
 * implementation of a Server calls this function on it's processing thread;
 * meanwhile the main thread could try to read the set of connections and
 * therefore introduce a data race.
 *
 * @param connection_id The ID of the connection which uniquely identifies it
 */
void WebSocketServer::RemoveConnection(int connection_id) {
  std::lock_guard<std::mutex> guard(connections_lock_);
  std::lock_guard<std::mutex> auth_con_guard(authenticated_connections_lock_);

  Server::RemoveConnection(connection_id);
}

/**
 * @brief Adds a client to the map of connection ID <-> handle. The function is
 * thread safe, because AddClient is normally called from the processing thread.
 * Hence, on the ocassion that the main thread requires to send data to some
 * connection_id through the Server interface, it must look into the
 * ws_connections_map_ to fetch the corresponding underlying handle.
 *
 * @param handle The handle for the client
 */
void WebSocketServer::AddClient(websocketpp::connection_hdl handle) {
  std::unique_lock<std::mutex> map_lock(ws_connections_map_lock_);
  ws_connections_map_[next_connection_id_] = handle;
  map_lock.unlock();

  AddConnection(next_connection_id_);

  std::lock_guard<std::mutex> ncid_guard(next_connection_id_lock_);
  next_connection_id_++;
}

/**
 * @brief Removes a client to the map of connection ID <-> handle. The function
 * is thread safe, because RemoveClient is normally called from the processing
 * thread. Hence, on the ocassion that the main thread requires to send
 * data to some connection_id through the Server interface, it must look into
 * the ws_connections_map_ to fetch the corresponding underlying handle.
 *
 * @param handle The handle of the client to remove
 */
void WebSocketServer::RemoveClient(websocketpp::connection_hdl handle) {
  std::lock_guard<std::mutex> guard(ws_connections_map_lock_);
  for (const auto& entry : ws_connections_map_) {
    if (CompareClients(entry.second, handle)) {
      // Remove the connection from the local map
      ws_connections_map_.erase(entry.first);

      // Remove from the "abstract" list of connections
      RemoveConnection(entry.first);

      break;
    }
  }
}

/**
 * @brief Authenticates a client to the server. Thread safe, because the main
 * thread could try to broadcast while a new client is being authenticated.
 *
 * @param connection_id The ID of the client to authenticate.
 */
void WebSocketServer::Authenticate(int connection_id) {
  std::lock_guard<std::mutex> guard(authenticated_connections_lock_);

  Server::Authenticate(connection_id);
}

/**
 * @brief Determines if a client is in the list of authenticated clients.
 *
 * @param connection_id The connection ID of the client to check.
 *
 * @return True if authenticated, false otherwise.
 */
bool WebSocketServer::IsClientAuthenticated(int connection_id) {
  std::lock_guard<std::mutex> auth_con_guard(authenticated_connections_lock_);

  return Server::IsClientAuthenticated(connection_id);
}

/**
 * @brief Gets the connection ID from the concrete websocketpp::connection_hdl.
 *
 * @param handle The handle for which the corresponding connection ID is to be
 * fetched.
 *
 * @return The corresponding connection ID.
 */
int WebSocketServer::GetConnectionIdFromHandle(
    websocketpp::connection_hdl handle) const {
  std::lock_guard<std::mutex> guard(ws_connections_map_lock_);
  for (const auto& entry : ws_connections_map_) {
    if (CompareClients(entry.second, handle)) {
      return entry.first;
    }
  }
}

/**
 * @brief Compares two connection handles (clients) that are actually
 * implemented as weak_ptrs.
 *
 * @param first_handle The first connection handle
 * @param second_handle The second connection handle
 *
 * @return True if they are equal (the address of the control block is the same)
 */
bool WebSocketServer::CompareClients(
    const websocketpp::connection_hdl& first_handle,
    const websocketpp::connection_hdl& second_handle) const {
  return !first_handle.owner_before(second_handle) &&
         !second_handle.owner_before(first_handle);
}

/**
 * @brief Retrieves the next connection ID to be used.
 *
 * @return The next connection ID.
 */
int WebSocketServer::next_connection_id() const {
  std::lock_guard<std::mutex> ncid_guard(next_connection_id_lock_);
  return next_connection_id_;
}

}  // namespace core

}  // namespace sniffer
