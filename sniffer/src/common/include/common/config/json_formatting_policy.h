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
  template <typename U>
  U ExtractValue(const T& config, const std::string& object,
                 const std::string& key) {
    auto json_obj = nlohmann::json::parse(config.data());
    return json_obj[object][key].template get<U>();
  }

  template <typename U>
  T SetValue(const T& config, const std::string& object, const std::string& key,
             U value) {
    auto json_obj = nlohmann::json::parse(config.data());

    json_obj[object][key] = value;

    T config_obj{json_obj.dump()};
    return config_obj;
  }

  std::string extension() { return "json"; }
};

}  // namespace config

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_INCLUDE_COMMON_CONFIG_JSON_FORMATTING_POLICY_H_
