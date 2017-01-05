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
 * @param next_header_id The header ID of the next header.
 * @param packet A pointer to the SniffedPacket object.
 * @param accumulator The object to use to accumulate the parsed properties.
 */
void LayerStack::HandleReception(
    int next_header_id, sniffer::protocols::SniffedPacket* packet,
    sniffer::common::serialization::SerializedObject* accumulator) {
  if (lowest_layer_) {
    lowest_layer_->HandleReception(next_header_id, packet, accumulator);
  }
  // else throw
}

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
