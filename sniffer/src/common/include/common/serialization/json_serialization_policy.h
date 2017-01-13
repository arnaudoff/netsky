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

template <class T>
class JsonSerializationPolicy {
 public:
  T Create() const {
    nlohmann::json empty_obj = nlohmann::json::object();

    T obj{empty_obj.dump()};

    return obj;
  }

  bool ObjectExists(const T& serialized_obj, const std::string& object) const {
    auto json_obj = nlohmann::json::parse(serialized_obj.data());

    if (json_obj.find(object) != json_obj.end()) {
      return true;
    }

    return false;
  }

  bool IsEmpty(const T& serialized_obj) const {
    auto json_obj = nlohmann::json::parse(serialized_obj.data());
    return json_obj.empty();
  }

  template <typename U>
  U ExtractValue(const T& serialized_obj, const std::string& object,
                 const std::string& key) const {
    auto json_obj = nlohmann::json::parse(serialized_obj.data());
    return json_obj[object][key].template get<U>();
  }

  template <typename U>
  void SetValue(const std::string& key, U value, T* serialized_obj) const {
    auto json_obj = nlohmann::json::parse(serialized_obj->data());

    json_obj[key] = value;

    serialized_obj->set_data(json_obj.dump());
  }

  void SetObject(const std::string& key, const T& serialized_obj,
                 T* serialized_parent_obj) const {
    auto json_pobj = nlohmann::json::parse(serialized_parent_obj->data());
    auto json_obj = nlohmann::json::parse(serialized_obj.data());
    json_pobj[key] = json_obj;

    serialized_parent_obj->set_data(json_pobj.dump());
  }

  void AppendObject(const std::string& key, const T& serialized_obj,
                    T* serialized_parent_obj) const {
    auto json_pobj = nlohmann::json::parse(serialized_parent_obj->data());
    auto json_obj = nlohmann::json::parse(serialized_obj.data());

    if (!json_pobj.count(key)) {
      json_pobj[key] = nlohmann::json::array();
    }

    json_pobj[key].push_back(json_obj);

    serialized_parent_obj->set_data(json_pobj.dump());
  }

  void AppendVariableDepthObject(const std::string& root_key,
                                 const std::string& children_key,
                                 int subtree_depth_delta,
                                 const T& serialized_obj,
                                 T* serialized_parent_obj) const {
    auto json_pobj = nlohmann::json::parse(serialized_parent_obj->data());
    auto json_obj = nlohmann::json::parse(serialized_obj.data());

    InsertObjectAtNthDepth(children_key, subtree_depth_delta, json_obj,
                           &(json_pobj[root_key]));

    serialized_parent_obj->set_data(json_pobj.dump());
  }

  int InsertObjectAtNthDepth(const std::string& children_key,
                             int subtree_depth_delta,
                             nlohmann::json obj_to_insert,
                             nlohmann::json* root) const {
    if (root->empty()) {
      return 0;
    }

    int height = 0;

    for (auto& obj : (*root)[children_key]) {
      height = std::max(
          height, InsertObjectAtNthDepth(children_key, subtree_depth_delta,
                                         obj_to_insert, &obj));
    }

    if (height + 1 == subtree_depth_delta) {
      (*root)[children_key].push_back(obj_to_insert);
    }

    return height + 1;
  }
};

}  // namespace serialization

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_INCLUDE_COMMON_SERIALIZATION_JSON_SERIALIZATION_POLICY_H_
