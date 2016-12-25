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

#include "core/server_commands/server_command.h"

namespace sniffer {

namespace core {

namespace server_commands {

ServerCommand::ServerCommand(const std::string& name, Server* server,
                             const SerializationMgr& serializer)
    : name_{name}, server_{server}, serializer_{serializer} {}

std::string ServerCommand::name() const { return name_; }

bool ServerCommand::Matches(const std::string& data) const {
  Serialization::SerializedObject data_obj{data};
  return serializer_.object_exists(data_obj, name());
}

}  // namespace server_commands

}  // namespace core

}  // namespace sniffer
