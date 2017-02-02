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

#include "core/layers/data_link_layer.h"

#include <string>

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace core {

namespace layers {

/**
 * @brief Constructs a DataLinkLayer object.
 *
 * @param name Name of the layer.
 * @param mgr The serialization manager to use.
 */
DataLinkLayer::DataLinkLayer(
    const std::string& name,
    const sniffer::common::serialization::SerializationMgr& mgr)
    : Layer{name, mgr} {}

/**
 * @brief Handles the reception of a SniffedPacket on the DataLinkLayer.
 *
 * @param prev_header_name The name of the lower-layer header.
 * @param current_header_id ID extracted from the lower layer.
 * @param packet A raw pointer to the packet to interpret.
 * @param composite A pointer to the SerializedObject that is used as a
 * composite object for storage of the interpreted fields while going up
 * the stack.
 */
void DataLinkLayer::HandleReception(
    std::string prev_header_name, int current_header_id,
    sniffer::protocols::SniffedPacket* packet,
    sniffer::common::serialization::SerializedObject* composite) {
  reception_handler_.Handle(prev_header_name, current_header_id, packet,
                            composite);
}

}  // namespace layers

}  // namespace core

}  // namespace sniffer
