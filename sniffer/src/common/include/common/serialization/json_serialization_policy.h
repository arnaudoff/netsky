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

#ifndef SNIFFER_SRC_COMMON_INCLUDE_COMMON_SERIALIZATION_JSON_SERIALIZATION_POLICY_H_
#define SNIFFER_SRC_COMMON_INCLUDE_COMMON_SERIALIZATION_JSON_SERIALIZATION_POLICY_H_

#include <algorithm>
#include <memory>
#include <string>

#include "json.hpp"

#include "common/serialization/serialized_object.h"

namespace sniffer {

namespace common {

namespace serialization {

/**
 * @brief This class represents a policy for serialization via JSON.
 *
 * @tparam T Type of an object to use as serialized, ready to use, object
 * (normally uses SerializedObject).
 */
template <class T>
class JsonSerializationPolicy {
 public:
  /**
   * @brief Creates an empty serialized object.
   *
   * @return The empty serialized object.
   */
  T Create() const {
    nlohmann::json empty_obj = nlohmann::json::object();

    T obj{empty_obj.dump()};

    return obj;
  }

  /**
   * @brief Checks if object with the name name exists in the serialized object.
   *
   * @param serialized_obj The serialized object to look into.
   * @param name The name of the object to search for.
   *
   * @return True if it exists, false otherwise.
   */
  bool ObjectExists(const T& serialized_obj, const std::string& name) const {
    auto json_obj = nlohmann::json::parse(serialized_obj.data());

    if (json_obj.find(name) != json_obj.end()) {
      return true;
    }

    return false;
  }

  /**
   * @brief Checks if a serialized object is empty.
   *
   * @param serialized_obj The serialized object to check.
   *
   * @return True if empty, false otherwise.
   */
  bool IsEmpty(const T& serialized_obj) const {
    auto json_obj = nlohmann::json::parse(serialized_obj.data());
    return json_obj.empty();
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
  U ExtractValue(const T& serialized_obj, const std::string& object_name,
                 const std::string& key_name) const {
    auto json_obj = nlohmann::json::parse(serialized_obj.data());
    return json_obj[object_name][key_name].template get<U>();
  }

  /**
   * @brief Sets a value of type U to a serialized object.
   *
   * @tparam U The type of the value.
   * @param key_name The name of the key.
   * @param serialized_obj The serialized object to set the value to.
   */
  template <typename U>
  void SetValue(const std::string& key_name, U value, T* serialized_obj) const {
    auto json_obj = nlohmann::json::parse(serialized_obj->data());

    json_obj[key_name] = value;

    serialized_obj->set_data(json_obj.dump());
  }

  /**
   * @brief Sets a serialized object to a serialized object.
   *
   * @param key_name The name of the key to use for the child object.
   * @param serialized_obj The child serialized object to set.
   * @param serialized_parent_obj The parent serialized object to set to.
   */
  void SetObject(const std::string& key_name, const T& serialized_obj,
                 T* serialized_parent_obj) const {
    auto json_pobj = nlohmann::json::parse(serialized_parent_obj->data());
    auto json_obj = nlohmann::json::parse(serialized_obj.data());
    json_pobj[key_name] = json_obj;

    serialized_parent_obj->set_data(json_pobj.dump());
  }

  /**
   * @brief Appends a serialized object to another serialized object. The parent
   * object generally holds an array of child serialized object.
   *
   * @param key_name The name of the key.
   * @param serialized_obj The child object to append.
   * @param serialized_parent_obj The parent object to append to.
   */
  void AppendObject(const std::string& key_name, const T& serialized_obj,
                    T* serialized_parent_obj) const {
    auto json_pobj = nlohmann::json::parse(serialized_parent_obj->data());
    auto json_obj = nlohmann::json::parse(serialized_obj.data());

    if (!json_pobj.count(key_name)) {
      json_pobj[key_name] = nlohmann::json::array();
    }

    json_pobj[key_name].push_back(json_obj);

    serialized_parent_obj->set_data(json_pobj.dump());
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
                                 const T& serialized_obj,
                                 T* serialized_parent_obj) const {
    auto json_pobj = nlohmann::json::parse(serialized_parent_obj->data());
    auto json_obj = nlohmann::json::parse(serialized_obj.data());

    InsertObjectAtNthDepth(children_key_name, subtree_depth_delta, json_obj,
                           &(json_pobj[root_key_name]));

    serialized_parent_obj->set_data(json_pobj.dump());
  }

  /**
   * @brief Traverses a tree recursively while calculating its height
   * starting with the root object and appends an object at height -
   * subtree_depth_delta.
   *
   * @param children_key_name The name of the children property to append to.
   * @param subtree_depth_delta The distance from the leaf of the parent object
   * tree to the children property to append to.
   * @param obj_to_insert The object to insert.
   * @param root The root of the parent object tree.
   *
   * @return The height of the tree.
   */
  int InsertObjectAtNthDepth(const std::string& children_key_name,
                             int subtree_depth_delta,
                             nlohmann::json obj_to_insert,
                             nlohmann::json* root) const {
    if (root->empty()) {
      return 0;
    }

    int height = 0;

    for (auto& obj : (*root)[children_key_name]) {
      height = std::max(
          height, InsertObjectAtNthDepth(children_key_name, subtree_depth_delta,
                                         obj_to_insert, &obj));
    }

    if (height + 1 == subtree_depth_delta) {
      (*root)[children_key_name].push_back(obj_to_insert);
    }

    return height + 1;
  }
};

}  // namespace serialization

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_INCLUDE_COMMON_SERIALIZATION_JSON_SERIALIZATION_POLICY_H_
