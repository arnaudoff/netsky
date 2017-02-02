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
 * @param serializer A reference to the SerializationMgr to use while
 * serializing values into the composite object.
 * @param layer A pointer to the current layer for which the handler is
 * is acting upon.
 */
ReceptionHandler::ReceptionHandler(
    const sniffer::common::serialization::SerializationMgr& serializer,
    layers::Layer* layer)
    : serializer_{serializer}, layer_{layer} {}

/**
 * @brief Retrieves the serialization manager used for this instance.
 *
 * @return The serialization manager that is used.
 */
sniffer::common::serialization::SerializationMgr ReceptionHandler::serializer()
    const {
  return serializer_;
}

/**
 * @brief Handles the reception of a SniffedPacket.
 *
 * @param prev_header_name The name of the lower-layer header.
 * @param current_header_id ID extracted from the lower layer.
 * @param packet A raw pointer to the packet to interpret.
 * @param composite A pointer to the SerializedObject that is used as a
 * composite object for storage of the interpreted fields while going up
 * the stack.
 */
void ReceptionHandler::Handle(
    std::string prev_header_name, int current_header_id,
    sniffer::protocols::SniffedPacket* packet,
    sniffer::common::serialization::SerializedObject* composite) {
  sniffer::protocols::headers::metadata::HeaderMetadata* current_header_md =
      nullptr;

  // Check if the header metadata has support for the lower layer protocol and
  // if it does, check whether its ID matches with the one parsed and passed by
  // the lower layer.
  for (const auto& hm : layer_->supported_headers()) {
    if (hm.get()->lower_layer_id_mappings().count(prev_header_name) > 0 &&
        hm.get()->lower_layer_id_mappings()[prev_header_name] ==
            current_header_id) {
      current_header_md = hm.get();
    }
  }

  if (current_header_md) {
    std::string name = current_header_md->name();

    if (current_header_md->has_variable_length()) {
      const u_char* len_field =
          packet->Peek(current_header_md->length_field_offset());
      current_header_md->set_length(len_field);

      // We have malformed PDU, e.g. an IP header less than 20 bytes, a TCP
      // header less than 20 bytes etc.
      if (current_header_md->length() < current_header_md->minimum_length()) {
        return;
      }
    }

    int length = current_header_md->length();

    if (current_header_md->accounts_for_payload_length()) {
      current_header_md->AccountForPayloadLength(packet);
    }

    // Now that we have the name and the length of the header, create an
    // object of its type and pass it the raw data.
    std::unique_ptr<sniffer::protocols::headers::Header> header_instance{
        registry::Registry<sniffer::protocols::headers::Header, int,
                           sniffer::protocols::SniffedPacket*>::Create(name,
                                                                       length,
                                                                       packet)};

    auto serialized_header = header_instance->Serialize(serializer_);
    if (!serializer_.ObjectExists(*composite, "data")) {
      serializer_.SetObject("data", serialized_header, composite);
    } else {
      serializer_.AppendVariableDepthObject("data", "children", 3,
                                            serialized_header, composite);
    }

    layer_->AppendSummary(header_instance.get(), composite);

    // Continue up the layer stack
    layers::Layer* upper_layer = layer_->upper_layer();
    if (upper_layer) {
      upper_layer->HandleReception(name, header_instance->next_header_id(),
                                   packet, composite);
    } else {
      // We have reached the top of the layer stack, nothing more to interpret
      return;
    }
  }
}

}  // namespace core

}  // namespace sniffer
