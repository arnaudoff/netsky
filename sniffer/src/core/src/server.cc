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

#include "core/server.h"

#include <memory>
#include <set>
#include <utility>

#include "spdlog/spdlog.h"

#include "common/policy_bindings.h"
#include "core/packet_sniffer.h"

namespace sniffer {

namespace core {

/**
 * @brief Constructs a Server object.
 *
 * @param manager The configuration manager to use for the server.
 * @param password The server password
 */
Server::Server(const sniffer::common::config::ConfigurationMgr& manager,
               const std::string& password)
    : config_manager_{manager},
      password_{password},
      has_host_connection_{false},
      host_connection_{0} {}

/**
 * @brief Destructs a Server object.
 */
Server::~Server() {}

/**
 * @brief Sets the sniffer for the current server instance by changing the
 * ownership of the sniffer to the server.
 *
 * @param sniffer A pointer with unique ownership semantics to a sniffer object.
 */
void Server::set_sniffer(std::unique_ptr<PacketSniffer> sniffer) {
  sniffer_ = std::move(sniffer);
}

PacketSniffer* Server::sniffer() const { return sniffer_.get(); }

/**
 * @brief Retrieves the configuration manager instance.
 *
 * @return The configuration manager.
 */
sniffer::common::config::ConfigurationMgr Server::config_manager() const {
  return config_manager_;
}

/**
 * @brief Gets the server password.
 *
 * @return The server password.
 */
std::string Server::password() const { return password_; }

/**
 * @brief Determines whether the server has a sniffer initialized, e.g. whether
 * there's just some connections or an actual sniffing session.
 *
 * @return True if there's a sniffing session, false otherwise.
 */
bool Server::has_host_connection() const { return has_host_connection_; }

/**
 * @brief Gets the ID of the client that started the sniffing session.
 *
 * @return The client ID
 */
int Server::host_connection() const { return host_connection_; }

/**
 * @brief Sets the host connection for a server, e.g. the one that initialized
 * the sniffing session. This is so because multiple clients are supported.
 *
 * @param connection_id The ID of the client that initiated the connection.
 */
void Server::set_host_connection(int connection_id) {
  host_connection_ = connection_id;
  has_host_connection_ = true;
}


/**
 * @brief Retrieves all stored connections on the server since it's started
 *
 * @return A set of integers representing the connection IDs
 */
std::set<int> Server::connections() const { return connections_; }

/**
 * @brief Sends the specified message to all currently connected clients
 *
 * @param message The message to send
 */
void Server::Broadcast(const std::string& message) {
  for (auto connection : connections_) {
    Unicast(connection, message);
  }
}

/**
 * @brief Sends the specified message to all currently connected AND
 * authenticated clients
 *
 * @param message The message to send
 */
void Server::AuthenticatedBroadcast(const std::string& message) {
  for (auto connection : authenticated_connections_) {
    Unicast(connection, message);
  }
}

/**
 * @brief Adds a connection to the set of connections.
 *
 * @param connection_id The ID of the connection that uniquely identifies it.
 */
void Server::AddConnection(int connection_id) {
  connections_.insert(connection_id);
}

/**
 * @brief Removes a connection from the set of connections AND authenticated
 * connections (if the disconnecting user was authenticated).
 *
 * If the disconnecting user was a host, denote that no hosts exists anymore and
 * stop the sniffing thread.
 *
 * @param connection_id The connection ID to remove.
 */
void Server::RemoveConnection(int connection_id) {
  connections_.erase(connection_id);

  if (authenticated_connections_.count(connection_id)) {
    authenticated_connections_.erase(connection_id);
  }

  if (host_connection_ == connection_id) {
    StopSniffer();
  }
}

/**
 * @brief Removes the host connection snd stops the sniffing thread.
 */
void Server::StopSniffer() {
  has_host_connection_ = false;
  sniffer_.reset();

  spdlog::get("console")->info("The sniffer was stopped.");
}

/**
 * @brief Authenticates a connection to the server.
 *
 * @param connection_id The connection ID of the client to authenticate.
 */
void Server::Authenticate(int connection_id) {
  authenticated_connections_.insert(connection_id);
}

/**
 * @brief Determines if a client is in the list of authenticated clients.
 *
 * @param connection_id The connection ID of the client to check.
 *
 * @return True if authenticated, false otherwise.
 */
bool Server::IsClientAuthenticated(int connection_id) {
  return authenticated_connections_.count(connection_id) > 0;
}

}  // namespace core

}  // namespace sniffer
