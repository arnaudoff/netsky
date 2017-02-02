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

#ifndef SNIFFER_SRC_COMMON_INCLUDE_COMMON_CONFIG_JSON_FORMATTING_POLICY_H_
#define SNIFFER_SRC_COMMON_INCLUDE_COMMON_CONFIG_JSON_FORMATTING_POLICY_H_

#include <memory>
#include <string>

#include "json.hpp"

namespace sniffer {

namespace common {

namespace config {

template <class T>
class JsonFormattingPolicy {
 public:
   /**
    * @brief Extracts a value from a config given an object and a key name.
    *
    * @tparam U The type of the value, e.g. std::string.
    * @param config The config object, normally Configuration.
    * @param object The name of the object which contains key.
    * @param key The name of the key.
    *
    * @return The value extracted.
    */
  template <typename U>
  U ExtractValue(const T& config, const std::string& object,
                 const std::string& key) const {
    auto json_obj = nlohmann::json::parse(config.data());
    return json_obj[object][key].template get<U>();
  }

  /**
   * @brief Sets a value to a config object given an object name and a key name.
   *
   * @tparam U The type of the value, e.g. std::string or int.
   * @param config The config object to use, normally Configuration.
   * @param object The object name which contains key.
   * @param key The name of the key.
   * @param value The value to set.
   *
   * @return A new instance of T (normally Configuration) containing the value
   * set.
   */
  template <typename U>
  T SetValue(const T& config, const std::string& object, const std::string& key,
             U value) const {
    auto json_obj = nlohmann::json::parse(config.data());

    json_obj[object][key] = value;

    T config_obj{json_obj.dump()};
    return config_obj;
  }

  /**
   * @brief Returns the extension for the JsonFormattingPolicy.
   *
   * @return The extension (.json).
   */
  std::string extension() const { return "json"; }
};

}  // namespace config

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_INCLUDE_COMMON_CONFIG_JSON_FORMATTING_POLICY_H_
