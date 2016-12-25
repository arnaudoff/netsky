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

#ifndef SNIFFER_SRC_CORE_RESPONSE_MODELS_RESPONSE_MODEL_H_
#define SNIFFER_SRC_CORE_RESPONSE_MODELS_RESPONSE_MODEL_H_

#include <string>

#include "common/serialization/serializable_entity.h"
#include "common/serialization/serialized_object.h"

namespace sniffer {

namespace core {

namespace response_models {

class ResponseModel : public Serialization::SerializableEntity {
 public:
  virtual Serialization::SerializedObject serialize(
      const SerializationMgr& serializer) const = 0;

  virtual ~ResponseModel() {}

  virtual std::string entity_name() const = 0;
};

}  // namespace response_models

}  // namespace core

}  // namespace sniffer

#endif  // SNIFFER_SRC_CORE_RESPONSE_MODELS_RESPONSE_MODEL_H_
