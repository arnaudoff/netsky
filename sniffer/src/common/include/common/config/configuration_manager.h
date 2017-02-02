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

#ifndef SNIFFER_SRC_COMMON_INCLUDE_COMMON_CONFIG_CONFIGURATION_MANAGER_H_
#define SNIFFER_SRC_COMMON_INCLUDE_COMMON_CONFIG_CONFIGURATION_MANAGER_H_

#include <memory>
#include <string>

#include "common/config/configuration.h"

namespace sniffer {

namespace common {

namespace config {

template <template <class> class StoragePolicy,
          template <class> class FormattingPolicy>
class ConfigurationManager : public StoragePolicy<Configuration>,
                             public FormattingPolicy<Configuration> {
 public:
   /**
    * @brief Extracts a value from an object.
    *
    * @tparam U The type of the value to extract.
    * @param object The object name to extract from.
    * @param key The key for the value to extract.
    *
    * @return The extracted value of type U.
    */
  template <typename U>
  U ExtractValue(const std::string& object, const std::string& key) const {
    auto resource_path = StoragePolicy<Configuration>::resource_path() +
                         FormattingPolicy<Configuration>::extension();

    auto configuration = StoragePolicy<Configuration>::Read(resource_path);

    return FormattingPolicy<Configuration>::template ExtractValue<U>(
        configuration, object, key);
  }

   /**
    * @brief Sets a value to an object.
    *
    * @tparam U The type of the value to set.
    * @param object The object name to set value to.
    * @param key The key for the value to set.
    */
  template <typename U>
  void SetValue(const std::string& object, const std::string& key,
                U value) const {
    auto resource_path = StoragePolicy<Configuration>::resource_path() +
                         FormattingPolicy<Configuration>::extension();

    auto old_config = StoragePolicy<Configuration>::Read(resource_path);

    auto new_config = FormattingPolicy<Configuration>::template SetValue<U>(
        old_config, object, key, value);

    StoragePolicy<Configuration>::Write(new_config, resource_path);
  }
};

}  // namespace config

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_INCLUDE_COMMON_CONFIG_CONFIGURATION_MANAGER_H_
