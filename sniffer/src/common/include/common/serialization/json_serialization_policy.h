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

#ifndef SNIFFER_SRC_COMMON_SERIALIZATION_JSON_SERIALIZATION_POLICY_H_
#define SNIFFER_SRC_COMMON_SERIALIZATION_JSON_SERIALIZATION_POLICY_H_

#include <memory>
#include <string>

#include <nlohmann/json.hpp>  // NOLINT

namespace sniffer {

namespace common {

namespace serialization {

template <class T>
class JsonSerializationPolicy {
 public:
  T Create() const {
    json empty_obj = json::object();

    T obj{empty_obj.dump()};

    return obj;
  }

  bool ObjectExists(const SerializedObject& data,
                    const std::string& object) const {
    auto json_obj = json::parse(data.data());

    if (json_obj.find(object) != json_obj.end()) {
      return true;
    }

    return false;
  }

  bool IsEmpty(const SerializedObject& obj) const {
    auto json_obj = json::parse(obj.data());
    return json_obj.empty();
  }

  template <typename U>
  U ExtractValue(const T& data, const std::string& object,
                 const std::string& key) const {
    auto json_obj = json::parse(data.data());
    return json_obj[object][key].template get<U>();
  }

  template <typename U>
  void SetValue(const std::string& key, U value, T* object) const {
    auto json_obj = json::parse(object->data());

    json_obj[key] = value;

    object->set_data(json_obj.dump());
  }

  void SetObject(const std::string& key, const T& obj, T* parent_obj) const {
    auto json_pobj = json::parse(parent_obj.data());
    auto json_obj = json::parse(obj.data());
    json_pobj[key] = json_obj;

    parent_obj.set_data(json_pobj.dump());
  }

  void AppendObject(const std::string& key, const T& obj, T* parent_obj) const {
    auto json_pobj = json::parse(parent_obj->data());
    auto json_obj = json::parse(obj.data());

    if (!json_pobj.count(key)) {
      json_pobj[key] = json::array();
    }

    json_pobj[key].push_back(json_obj);

    parent_obj->set_data(json_pobj.dump());
  }
};

}  // namespace serialization

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_SERIALIZATION_JSON_SERIALIZATION_POLICY_H_
