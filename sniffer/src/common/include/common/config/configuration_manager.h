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
  template <typename U>
  U ExtractValue(const std::string& object, const std::string& key) {
    auto resource_path =
        config_path + FormattingPolicy<Configuration>::extension();

    auto configuration = StoragePolicy<Configuration>::Read(resource_path);

    return FormattingPolicy<Configuration>::template ExtractValue<U>(
        configuration, object, key);
  }

  template <typename U>
  void SetValue(const std::string& object, const std::string& key, U value) {
    auto resource_path =
        config_path + FormattingPolicy<Configuration>::extension();

    auto old_config = StoragePolicy<Configuration>::Read(resource_path);

    auto new_config = FormattingPolicy<Configuration>::template SetValue<U>(
        old_config, object, key, value);

    StoragePolicy<Configuration>::Write(new_config, resource_path);
  }

 private:
  static constexpr auto config_path = "../../config/config.";
};

}  // namespace config

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_INCLUDE_COMMON_CONFIG_CONFIGURATION_MANAGER_H_
