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

#include "core/layers/application_layer.h"

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"
#include "core/payload_interpreter.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace core {

namespace layers {

/**
 * @brief Constructs an ApplicationLayer object.
 *
 * @param name Name of the layer.
 * @param mgr The serialization manager to use.
 * @param interpreter The payload interpreter to use, e.g.
 * HexAsciiPayloadInterpreter.
 */
ApplicationLayer::ApplicationLayer(
    const std::string& name,
    const sniffer::common::serialization::SerializationMgr& mgr,
    std::unique_ptr<PayloadInterpreter> interpreter)
    : Layer{name, mgr}, interpreter_{std::move(interpreter)} {}

/**
 * @brief Handles the reception of a SniffedPacket on the ApplicationLayer.
 * Since the rest of the packet is dissected, the only thing left is to
 * interpret the payload and add it to the composite object.
 *
 * @param prev_header_name The name of the lower-layer header.
 * @param current_header_id ID extracted from the lower layer.
 * @param packet A raw pointer to the packet to interpret.
 * @param composite A pointer to the SerializedObject that is used as a
 * composite object for storage of the interpreted fields while going up
 * the stack.
 */
void ApplicationLayer::HandleReception(
    std::string prev_header_name, int current_header_id,
    sniffer::protocols::SniffedPacket* packet,
    sniffer::common::serialization::SerializedObject* composite) {
  int payload_length = packet->payload_length();

  if (payload_length > 0) {
    auto serializer = reception_handler_.serializer();
    auto payload_obj = serializer.CreateObject();

    auto interpreted_payload =
        interpreter_->Interpret(packet->Body(), payload_length);

    serializer.SetValue<std::string>("contents", interpreted_payload, &payload_obj);
    serializer.SetValue<int>("length", payload_length, &payload_obj);
    serializer.SetObject("payload", payload_obj, composite);

  }
}

}  // namespace layers

}  // namespace core

}  // namespace sniffer
