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

#include "core/layer_stack.h"

#include "common/serialization/serialized_object.h"
#include "core/layers/layer.h"
#include "protocols/sniffed_packet.h"

namespace sniffer {

namespace core {

/**
 * @brief Constructs a LayerStack object.
 */
LayerStack::LayerStack() : highest_layer_{nullptr}, lowest_layer_{nullptr} {}

/**
 * @brief Handles the reception of a SniffedPacket by defering it to the lowest
 * layer of the LayerStack.
 *
 * @param prev_header_name The name of the lower-layer header.
 * @param current_header_id ID extracted from the lower layer (physical).
 * @param packet A raw pointer to the packet to interpret.
 * @param composite A pointer to the SerializedObject that is used as a
 * composite object for storage of the interpreted fields while going up
 * the stack.
*/
void LayerStack::HandleReception(
    std::string prev_header_name, int current_header_id,
    sniffer::protocols::SniffedPacket* packet,
    sniffer::common::serialization::SerializedObject* composite) {
  if (lowest_layer_) {
    lowest_layer_->HandleReception(prev_header_name, current_header_id, packet,
                                   composite);
  }
}

/**
 * @brief Adds a layer on the Position relative to existing_layer.
 *
 * @param layer Pointer to the layer to add.
 * @param existing_layer Pointer to the existing layer.
 * @param position The position relative to which to apply the layer to existing
 * layer.
 */
void LayerStack::AddLayer(layers::Layer* layer, layers::Layer* existing_layer,
                          LayerStack::Position position) {
  layer->set_lower_layer(nullptr);
  layer->set_upper_layer(nullptr);

  if (highest_layer_) {
    switch (position) {
      case LayerStack::Position::TOP: {
        highest_layer_->set_upper_layer(layer);
        layer->set_lower_layer(highest_layer_);
        highest_layer_ = layer;

        break;
      }
      case LayerStack::Position::ABOVE: {
        layers::Layer* previous_upper_layer = existing_layer->upper_layer();
        layer->set_upper_layer(previous_upper_layer);
        layer->set_lower_layer(existing_layer);
        existing_layer->set_upper_layer(layer);

        if (existing_layer == highest_layer_) {
          highest_layer_ = layer;
        } else {
          previous_upper_layer->set_lower_layer(layer);
        }

        break;
      }
      case LayerStack::Position::BELOW: {
        layers::Layer* previous_lower_layer = existing_layer->lower_layer();
        layer->set_lower_layer(previous_lower_layer);
        layer->set_upper_layer(existing_layer);
        existing_layer->set_lower_layer(layer);

        if (existing_layer == lowest_layer_) {
          lowest_layer_ = layer;
        } else {
          previous_lower_layer->set_upper_layer(layer);
        }

        break;
      }
    }
  } else {
    highest_layer_ = layer;
    lowest_layer_ = layer;
  }
}

/**
 * @brief Removes a layer from the stack.
 *
 * @param layer Pointer to the layer to remove.
 */
void LayerStack::RemoveLayer(layers::Layer* layer) {
  if (layer == highest_layer_) {
    highest_layer_ = layer->lower_layer();

    if (highest_layer_) {
      highest_layer_->set_upper_layer(nullptr);
    }
  } else {
    (layer->upper_layer())->set_lower_layer(layer->lower_layer());
  }

  if (layer == lowest_layer_) {
    lowest_layer_ = layer->upper_layer();

    if (lowest_layer_) {
      lowest_layer_->set_lower_layer(nullptr);
    }
  } else {
    (layer->lower_layer())->set_upper_layer(layer->upper_layer());
  }

  layer->set_upper_layer(nullptr);
  layer->set_lower_layer(nullptr);
}

}  // namespace core

}  // namespace sniffer
