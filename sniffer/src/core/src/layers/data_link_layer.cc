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

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"
#include "protocols/headers/header_factory.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace core {

namespace layers {

DataLinkLayer::DataLinkLayer(
    const sniffer::common::serialization::SerializationMgr& mgr,
    const sniffer::protocols::headers::HeaderFactory& hfactory)
    : Layer{mgr, hfactory} {}

void DataLinkLayer::HandleReception(
    sniffer::common::serialization::SerializedObject acc, int next_header_id,
    sniffer::protocols::SniffedPacket* packet) {
  reception_handler_.Handle(acc, next_header_id, packet);
}

}  // namespace layers

}  // namespace core

}  // namespace sniffer
