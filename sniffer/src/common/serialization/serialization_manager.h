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

#ifndef SNIFFER_SRC_COMMON_SERIALIZATION_SERIALIZATION_MANAGER_H_
#define SNIFFER_SRC_COMMON_SERIALIZATION_SERIALIZATION_MANAGER_H_

#include <memory>
#include <string>
#include "serialized_object.h"

namespace sniffer {

namespace common {

namespace serialization {

template <template <class> class SerializationPolicy>
class SerializationManager : public SerializationPolicy<SerializedObject> {
 public:
  SerializedObject CreateObject() const {
    return SerializationPolicy<SerializedObject>::Create();
  }

  bool ObjectExists(const SerializedObject& data,
                    const std::string& object) const {
    return SerializationPolicy<SerializedObject>::ObjectExists(data, object);
  }

  bool IsEmpty(const SerializedObject& obj) const {
    return SerializationPolicy<SerializedObject>::IsEmpty(obj);
  }

  template <typename U>
  U ExtractValue(const SerializedObject& data, const std::string& object,
                 const std::string& key) const {
    return SerializationPolicy<SerializedObject>::template ExtractValue<U>(
        data, object, key);
  }

  template <typename U>
  void SetValue(const std::string& key, U value, SerializedObject* obj) const {
    SerializationPolicy<SerializedObject>::template SetValue<U>(key, value,
                                                                obj);
  }

  void SetObject(const std::string& key, const SerializedObject& obj,
                 SerializedObject* p_obj) const {
    SerializationPolicy<SerializedObject>::SetObject(key, obj, p_obj);
  }

  void AppendObject(const std::string& key, const SerializedObject& obj,
                    SerializedObject* p_obj) const {
    SerializationPolicy<SerializedObject>::AppendObject(key, obj, p_obj);
  }
};

}  // namespace serialization

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_SERIALIZATION_SERIALIZATION_MANAGER_H_
