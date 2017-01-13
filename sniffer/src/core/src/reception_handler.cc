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

#include "core/reception_handler.h"

#include <sys/types.h>

#include <algorithm>
#include <memory>
#include <string>

#include "registry.h"

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"
#include "core/layers/layer.h"
#include "protocols/headers/header.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace core {

/**
 * @brief Constructs a ReceptionHandler object
 *
 * @param serializer A const reference to the SerializationMgr to use while
 * serializing values into accumulated object.
 * @param layer A raw pointer to the current layer for which the handler is
 * is acting upon.
 */
ReceptionHandler::ReceptionHandler(
    const sniffer::common::serialization::SerializationMgr& serializer,
    layers::Layer* layer)
    : serializer_{serializer}, layer_{layer} {}

/**
 * @brief Handles the reception of a SniffedPacket.
 *
 * @param next_header_id An integer that is mapped to the header type.
 * @param packet A raw pointer to the packet to interpret.
 * @param accumulator_obj A pointer to the SerializedObject that is used as
 * accumulator for storage of the interpreted fields while going up the stack.
 */
void ReceptionHandler::Handle(
    int next_header_id, sniffer::protocols::SniffedPacket* packet,
    sniffer::common::serialization::SerializedObject* accumulator_obj) {
  auto& supported_headers = layer_->supported_headers();

  // Check if the current layer contains this header ID as supported
  auto header_metadata =
      std::find_if(supported_headers.begin(), supported_headers.end(),
                   [next_header_id](const auto& hm) {
                     return hm.get()->id() == next_header_id;
                   });

  // The layer has metadata for a header with such an ID
  if (header_metadata != supported_headers.end()) {
    std::string name = header_metadata->get()->name();

    // In order to initialize the header, we need to know its exact length.
    int length = 0;
    if (header_metadata->get()->has_variable_length()) {
      // In this case, we have to peek into the raw data before forming
      const u_char* len_field =
          packet->Peek(header_metadata->get()->length_field_offset());
      length = header_metadata->get()->CalculateLength(len_field);
    } else {
      // Otherwise this is a casual fixed-length header such as Ethernet
      length = header_metadata->get()->length();
    }

    // Now that we have the name and the size of the header, create an
    // object of its type and pass it the raw data.
    std::unique_ptr<sniffer::protocols::headers::Header> header_instance{
        registry::Registry<sniffer::protocols::headers::Header, int,
                           sniffer::protocols::SniffedPacket*>::Create(name,
                                                                       length,
                                                                       packet)};

    // Finally, serialize the parsed fields of the header and append
    // the generated object to the accumulating object.
    auto serialized_obj = header_instance->Serialize(serializer_);
    if (!serializer_.ObjectExists(*accumulator_obj, "data")) {
      serializer_.SetObject("data", serialized_obj, accumulator_obj);
    } else {
      serializer_.AppendVariableDepthObject("data", "children", 3,
                                            serialized_obj, accumulator_obj);
    }

    // Continue up the layer stack
    layers::Layer* upper_layer = layer_->upper_layer();
    if (upper_layer) {
      upper_layer->HandleReception(header_instance->next_header_id(), packet,
                                   accumulator_obj);
    } else {
      // We have reached the top of the layer stack, nothing more to interpret
      return;
    }
  } else {
    // The header is not supported yet.
    return;
  }
}

}  // namespace core

}  // namespace sniffer
