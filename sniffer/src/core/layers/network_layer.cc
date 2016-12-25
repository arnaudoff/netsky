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

#include "core/layers/network_layer.h"

namespace sniffer {

namespace core {

namespace layers {

NetworkLayer::NetworkLayer(const SerializationMgr& mgr,
                           const HeaderFactory& hfactory)
    : Layer{mgr, hfactory} {}

void NetworkLayer::HandleReception(SerializedObject acc, int next_header_id,
                                   SniffedPacket* packet) {
  reception_handler_.Handle(acc, next_header_id, packet);
}

}  // namespace layers

}  // namespace core

}  // namespace sniffer
