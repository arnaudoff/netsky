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

#ifndef SNIFFER_SRC_CORE_INCLUDE_CORE_LAYERS_LAYER_H_
#define SNIFFER_SRC_CORE_INCLUDE_CORE_LAYERS_LAYER_H_

#include <memory>
#include <vector>

#include "common/policy_bindings.h"
#include "common/serialization/serialized_object.h"
#include "core/reception_handler.h"
#include "protocols/headers/metadata/header_metadata.h"

namespace sniffer {

namespace protocols {

class SniffedPacket;

namespace headers {

namespace metadata {

class HeaderMetadata;

}  // namespace metadata

}  // namespace headers

}  // namespace protocols

namespace core {

namespace layers {

class Layer {
 public:
  Layer(const sniffer::common::serialization::SerializationMgr& serializer);

  virtual ~Layer() {}

  virtual void HandleReception(
      sniffer::common::serialization::SerializedObject acc, int next_header_id,
      sniffer::protocols::SniffedPacket* packet) = 0;

  Layer* lower_layer() const;

  void set_lower_layer(Layer* layer);

  Layer* upper_layer() const;

  void set_upper_layer(Layer* layer);

  const std::vector<
      std::unique_ptr<sniffer::protocols::headers::metadata::HeaderMetadata>>&
  supported_headers() const;

  void set_supported_headers(
      std::vector<std::unique_ptr<
          sniffer::protocols::headers::metadata::HeaderMetadata>>&& headers);

 protected:
  ReceptionHandler reception_handler_;

 private:
  Layer* lower_layer_;

  Layer* upper_layer_;

  std::vector<
      std::unique_ptr<sniffer::protocols::headers::metadata::HeaderMetadata>>
      supported_headers_;
};

}  // namespace layers

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_INCLUDE_CORE_LAYERS_LAYER_H_
