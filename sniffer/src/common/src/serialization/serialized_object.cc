/*
 * Copyright (C) 2017  Ivaylo Arnaudov <ivaylo.arnaudov12@gmail.com>
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

#include "common/serialization/serialized_object.h"

namespace sniffer {

namespace common {

namespace serialization {

/**
 * @brief Constructs a SerializedObject.
 *
 * @param data The raw data for the object.
 */
SerializedObject::SerializedObject(const std::string& data) : data_{data} {}

/**
 * @brief Retrieves the data.
 *
 * @return The raw data field of the object.
 */
std::string SerializedObject::data() const { return data_; }

/**
 * @brief Sets the raw data of the object.
 *
 * @param data The data for the object.
 */
void SerializedObject::set_data(const std::string& data) { data_ = data; }

}  // namespace config

}  // namespace common

}  // namespace sniffer
