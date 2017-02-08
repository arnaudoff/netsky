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

#ifndef SNIFFER_SRC_COMMON_INCLUDE_COMMON_SERIALIZATION_SERIALIZATION_MANAGER_H_
#define SNIFFER_SRC_COMMON_INCLUDE_COMMON_SERIALIZATION_SERIALIZATION_MANAGER_H_

#include <memory>
#include <string>

#include "common/serialization/serialized_object.h"

namespace sniffer {

namespace common {

namespace serialization {

template <template <class> class SerializationPolicy>
class SerializationManager : public SerializationPolicy<SerializedObject> {
 public:
  /**
   * @brief Creates an empty serialized object.
   *
   * @return The empty serialized object.
   */
  SerializedObject CreateObject() const {
    return SerializationPolicy<SerializedObject>::Create();
  }

  /**
   * @brief Checks if object with the name name exists in the serialized object.
   *
   * @param serialized_obj The serialized object to look into.
   * @param name The name of the object to search for.
   *
   * @return True if it exists, false otherwise.
   */
  bool ObjectExists(const SerializedObject& serialized_obj,
                    const std::string& name) const {
    return SerializationPolicy<SerializedObject>::ObjectExists(serialized_obj,
                                                               name);
  }

  /**
   * @brief Checks if a serialized object is empty.
   *
   * @param serialized_obj The serialized object to check.
   *
   * @return True if empty, false otherwise.
   */
  bool IsEmpty(const SerializedObject& serialized_obj) const {
    return SerializationPolicy<SerializedObject>::IsEmpty(serialized_obj);
  }

  /**
   * @brief Extracts a value of type U from a serialized object.
   *
   * @tparam U The type of the value.
   * @param serialized_obj The serialized object to extract the value from.
   * @param object_name The name of the object to extract from.
   * @param key_name The name of the key.
   *
   * @return The extracted value.
   */
  template <typename U>
  U ExtractValue(const SerializedObject& serialized_obj,
                 const std::string& object_name,
                 const std::string& key_name) const {
    return SerializationPolicy<SerializedObject>::template ExtractValue<U>(
        serialized_obj, object_name, key_name);
  }

  /**
   * @brief Sets a value of type U to a serialized object.
   *
   * @tparam U The type of the value.
   * @param key_name The name of the key.
   * @param serialized_obj The serialized object to set the value to.
   */
  template <typename U>
  void SetValue(const std::string& key_name, U value,
                SerializedObject* serialized_obj) const {
    SerializationPolicy<SerializedObject>::template SetValue<U>(key_name, value,
                                                                serialized_obj);
  }

  /**
   * @brief Sets a serialized object to a serialized object.
   *
   * @param key_name The name of the key to use for the child object.
   * @param serialized_obj The child serialized object to set.
   * @param serialized_parent_obj The parent serialized object to set to.
   */
  void SetObject(const std::string& key_name,
                 const SerializedObject& serialized_obj,
                 SerializedObject* serialized_parent_obj) const {
    SerializationPolicy<SerializedObject>::SetObject(key_name, serialized_obj,
                                                     serialized_parent_obj);
  }

  /**
   * @brief Appends a serialized object to another serialized object. The parent
   * object generally holds an array of child serialized object.
   *
   * @param key_name The name of the key.
   * @param serialized_obj The child object to append.
   * @param serialized_parent_obj The parent object to append to.
   */
  void AppendObject(const std::string& key_name,
                    const SerializedObject& serialized_obj,
                    SerializedObject* serialized_parent_obj) const {
    SerializationPolicy<SerializedObject>::AppendObject(
        key_name, serialized_obj, serialized_parent_obj);
  }

  /**
   * @brief Appends a child object to the parent object at height = parent
   * object tree height - subtree_depth_delta.
   *
   * @param root_key_name The name of key of the root object.
   * @param children_key_name The name of the key for the children object.
   * @param subtree_depth_delta The distance from the leaf of the tree to the
   * specific position where to append the child.
   * @param serialized_obj The object to append.
   * @param serialized_parent_obj The object to append to.
   */
  void AppendVariableDepthObject(const std::string& root_key_name,
                                 const std::string& children_key_name,
                                 int subtree_depth_delta,
                                 const SerializedObject& obj,
                                 SerializedObject* p_obj) const {
    SerializationPolicy<SerializedObject>::AppendVariableDepthObject(
        root_key_name, children_key_name, subtree_depth_delta, obj, p_obj);
  }
};

}  // namespace serialization

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_INCLUDE_COMMON_SERIALIZATION_SERIALIZATION_MANAGER_H_
