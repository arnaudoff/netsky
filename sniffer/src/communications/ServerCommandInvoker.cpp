#include "include/ServerCommandInvoker.hpp"

using namespace Sniffer::Communications;
using namespace Sniffer::Communications::Commands;

void ServerCommandInvoker::add_command(ServerCommand* command) {
    server_commands_.insert(command);
}

void ServerCommandInvoker::invoke(const ConnectionData& con_data,
        const std::string& message) {
    for (auto command : server_commands_) {
        if (command->matches(message)) {
            command->execute(con_data, command->parse(message));
        }
    }
}
