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

#include "core/layers/layer.h"

#include <iterator>
#include <memory>
#include <utility>
#include <vector>

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"
#include "protocols/headers/header.h"
#include "protocols/headers/metadata/header_metadata.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace core {

namespace layers {

/**
 * @brief Constructs a Layer object.
 *
 * @param name The name of the layer, e.g. "Application" or "Transport"
 * @param serializer The type of Serializer to use for the ReceptionHandler
 * that exists per-layer.
 */
Layer::Layer(const std::string& name,
             const sniffer::common::serialization::SerializationMgr& serializer)
    : name_{name},
      lower_layer_{NULL},
      upper_layer_{NULL},
      reception_handler_{serializer, this} {};

/**
 * @brief Retrieves the layer below.
 *
 * @return Returns a pointer to the layer below this layer.
 */
Layer* Layer::lower_layer() const { return lower_layer_; }

/**
 * @brief Sets the layer below.
 *
 * @param layer Pointer to the layer below this layer.
 */
void Layer::set_lower_layer(Layer* layer) { lower_layer_ = layer; }

/**
 * @brief Retrieves the layer above.
 *
 * @return Returns a pointer to the layer above this layer.
 */
Layer* Layer::upper_layer() const { return upper_layer_; }

/**
 * @brief Sets the layer above.
 *
 * @param layer Pointer to the layer above this layer.
 */
void Layer::set_upper_layer(Layer* layer) { upper_layer_ = layer; }

/**
 * @brief Retrieves the name of this layer.
 *
 * @return String represting the name of the layer.
 */
std::string Layer::name() const { return name_; }

/**
 * @brief Retrieves the supported headers for the layer.
 *
 * @return A collection of supported headers as HeaderMetadata objects.
 */
const std::vector<
    std::unique_ptr<sniffer::protocols::headers::metadata::HeaderMetadata>>&
Layer::supported_headers() const {
  return supported_headers_;
}

/**
 * @brief Sets the supported headers per layer.
 *
 * @param headers A collection of HeaderMetadata objects that represent the
 * supported headers.
 */
void Layer::set_supported_headers(
    std::vector<std::unique_ptr<
        sniffer::protocols::headers::metadata::HeaderMetadata>>&& headers) {
  supported_headers_ = std::move(headers);
}

/**
 * @brief Appends a summary depending on the current layer to the accumulating
 * object.
 *
 * @param header The header from which to fetch the summary fields.
 * @param acc The object where to write the summary (usually the accumulating
 * object).
 */
void Layer::AppendSummary(
    sniffer::protocols::headers::Header* header,
    sniffer::common::serialization::SerializedObject* acc) const {
  auto serializer = reception_handler_.serializer();
  auto header_summary = header->Summarise(serializer);
  serializer.SetObject(name(), header_summary, acc);
}

}  // namespace layers

}  // namespace core

}  // namespace sniffer
