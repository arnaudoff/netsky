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

#include "core/connection_data.h"

namespace sniffer {

namespace core {

ConnectionData::ConnectionData() : ConnectionData{0} {}

ConnectionData::ConnectionData(int session_id) : session_id_{session_id} {}

int ConnectionData::session_id() const { return session_id_; }

bool ConnectionData::operator==(const ConnectionData& other) const {
  return session_id_ == other.session_id_;
}

bool ConnectionData::operator!=(const ConnectionData& other) const {
  return !(*this == other);
}

}  // namespace core

}  // namespace sniffer
