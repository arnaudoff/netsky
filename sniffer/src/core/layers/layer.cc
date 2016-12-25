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

#include "core/layers/layer.h"

#include <iterator>
#include <memory>
#include <utility>
#include <vector>

#include <boost/iterator/indirect_iterator.hpp>  // NOLINT

namespace sniffer {

namespace core {

namespace layers {

using HeaderMetadataCollection = std::vector<std::unique_ptr<HeaderMetadata>>;

using SupportedHeadersIterator =
    boost::indirect_iterator<HeaderMetadataCollection::iterator,
                             const HeaderMetadata>;

Layer::Layer(const SerializationMgr& serializer, const HeaderFactory& hfactory)
    : lower_layer_{NULL},
      upper_layer_{NULL},
      reception_handler_{this, serializer, hfactory} {};

Layer* Layer::lower_layer() const { return lower_layer_; }

void Layer::set_lower_layer(Layer* layer) { lower_layer_ = layer; }

Layer* Layer::upper_layer() const { return upper_layer_; }

void Layer::set_upper_layer(Layer* layer) { upper_layer_ = layer; }

SupportedHeadersIterator Layer::begin() const {
  return std::begin(supported_headers_);
}

SupportedHeadersIterator Layer::end() const {
  return std::end(supported_headers_);
}

// wtf?
void Layer::set_supported_headers(
    std::vector<std::unique_ptr<HeaderMetadata>>&& headers) {
  supported_headers_ = std::move(headers);
}

}  // namespace layers

}  // namespace core

}  // namespace sniffer
