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
#include <string>

#include "core/layers/layer.h"

namespace sniffer {

namespace core {

/**
 * @brief Constructs a ReceptionHandler object
 *
 * @param serializer A const reference to the SerializationMgr to use while
 * serializing values into accumulated object.
 *
 * @param header_factory A const reference to a HeaderFactory to use in order to
 * construct the correct header objects.
 *
 * @param layer A raw pointer to the current layer for which the handler is
 * is acting upon.
 */
ReceptionHandler::ReceptionHandler(const SerializationMgr& serializer,
                                   const HeaderFactory& header_factory,
                                   Layer* layer)
    : serializer_{serializer}, header_factory_{header_factory}, layer_{layer} {}

/**
 * @brief Handles the reception of a SniffedPacket.
 *
 * @param accumulator_obj A reference to a SerializedObject that is used
 * as accumulator for storage of the interpreted fields while going up the stack
 *
 * @param next_header_id An integer that is mapped to the header type.
 *
 * @param packet A raw pointer to the packet to interpret.
 */
void ReceptionHandler::Handle(SerializedObject accumulator_obj,
                              int next_header_id, SniffedPacket* packet) {
  // Check if the current layer contains this header ID as supported
  auto header = std::find_if(
      layer_->begin(), layer_->end(),
      [next_header_id](const auto& hm) { return hm.id() == next_header_id; });

  // The layer has metadata for a header with such an ID
  if (header != layer_->end()) {
    std::string name = header->name();

    // In order to initialize the header, we need to know its exact length.
    int length = 0;
    if (header->HasVariableLength()) {
      // In this case, we have to peek into the raw data before forming
      const u_char* len_field = packet->Peek(header->length_field_offset());
      length = header->CalculateLength(len_field);
    } else {
      // Otherwise this is a casual fixed-length header such as Ethernet
      length = header->length();
    }

    // Now that we have the name and the size of the header, create an
    // object of its type and pass it the raw data.
    auto header_instance = header_factory_.CreateInstance(name, length, packet);

    // Finally, serialize the parsed fields of the header and append
    // the generated object to the accumulating object.
    auto serialized_obj = header_instance->Serialize(serializer_);
    serializer_.SetObject(accumulator_obj, name, serialized_obj);

    // Continue up the layer stack
    Layer* upper_layer = layer_->upper_layer();
    if (upper_layer) {
      upper_layer->HandleReception(accumulator_obj,
                                   header_instance->next_header_id(), packet);
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
