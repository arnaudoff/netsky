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

#ifndef SNIFFER_SRC_COMMON_INCLUDE_COMMON_CONFIG_FILE_STORAGE_POLICY_H_
#define SNIFFER_SRC_COMMON_INCLUDE_COMMON_CONFIG_FILE_STORAGE_POLICY_H_

#include <fstream>
#include <memory>
#include <sstream>
#include <string>

namespace sniffer {

namespace common {

namespace config {

template <class T>
class FileStoragePolicy {
 public:
   /**
    * @brief Reads from a configuration file.
    *
    * @param resource Path to the file to read from.
    *
    * @return Object of type T encapsulating the contents of the file.
    */
  T Read(const std::string& resource) const {
    std::ifstream in(resource);
    std::stringstream buffer;

    buffer << in.rdbuf();

    T config{buffer.str()};
    return config;
  }

  /**
   * @brief Writes an object of type T to the resource specified by resource.
   *
   * @param config The object to save to the resource.
   * @param resource Path to the resource file.
   */
  void Write(const T& config, const std::string& resource) const {
    std::ofstream out(resource);
    out << config.data();
    out.close();
  }

  /**
   * @brief Defines where the configuration file resides on the disk.
   *
   * @return The path to the configuration file.
   */
  std::string resource_path() const {
    return "../../config/config.";
  }
};

}  // namespace config

}  // namespace common

}  // namespace sniffer

#endif  // SNIFFER_SRC_COMMON_INCLUDE_COMMON_CONFIG_FILE_STORAGE_POLICY_H_
