/*
 * Copyright (C) 2017  Ivaylo Arnaudov <ivaylo.arnaudov12@gmail.com>
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

#include "core/websocket_server_event.h"

#include "websocketpp/config/asio.hpp"
#include "websocketpp/server.hpp"

#include "core/websocket_server_event_type.h"

namespace sniffer {

namespace core {

/**
 * @brief Constructs a WebSocketServerEvent.
 *
 * @param type The type of the event.
 * @param handle The connection handle for the event.
 */
WebSocketServerEvent::WebSocketServerEvent(WebSocketServerEventType type,
                                           websocketpp::connection_hdl handle)
    : type{type}, handle{handle} {}

/**
 * @brief Constructs a WebSocketServerEvent (overload).
 *
 * @param type The type of the event.
 * @param handle The connection handle for the event.
 * @param message Pointer to a message for the event.
 */
WebSocketServerEvent::WebSocketServerEvent(
    WebSocketServerEventType type, websocketpp::connection_hdl handle,
    websocketpp::config::asio::message_type::ptr message)
    : type{type}, handle{handle}, message{message} {}

}  // namespace core

}  // namespace sniffer
