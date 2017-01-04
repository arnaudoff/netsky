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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_LAYER_STACK_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_LAYER_STACK_H_

#include "common/serialization/serialized_object.h"

namespace sniffer {

namespace protocols {

class SniffedPacket;

}  // namespace protocols

namespace core {

namespace layers {

class Layer;

}  // namespace layers

class LayerStack {
 public:
  enum class Position { TOP, ABOVE, BELOW };

  LayerStack();

  void AddLayer(layers::Layer* layer, layers::Layer* existing = nullptr,
                Position pos = Position::TOP);

  void RemoveLayer(layers::Layer* layer);

  void HandleReception(sniffer::common::serialization::SerializedObject acc,
                       int next_header_id,
                       sniffer::protocols::SniffedPacket* packet);

 private:
  layers::Layer* highest_layer_;
  layers::Layer* lowest_layer_;
};

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_LAYER_STACK_H_
