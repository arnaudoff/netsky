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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_LAYERS_NETWORK_LAYER_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_LAYERS_NETWORK_LAYER_H_

#include "common/policy_bindings.h"
#include "core/layers/layer.h"

namespace sniffer {

namespace core {

namespace layers {

class NetworkLayer : public Layer {
 public:
  NetworkLayer(
      const std::string& name,
      const sniffer::common::serialization::SerializationMgr& serializer);

  void HandleReception(
      std::string prev_header_name, int current_header_id,
      sniffer::protocols::SniffedPacket* packet,
      sniffer::common::serialization::SerializedObject* composite) override;
};

}  // namespace layers

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_LAYERS_NETWORK_LAYER_H_
