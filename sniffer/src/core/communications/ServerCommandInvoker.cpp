#include "include/ServerCommandInvoker.hpp"
#include "include/CommandParser.hpp"

using namespace Sniffer::Core::Communications;
using namespace Sniffer::Core::Communications::Commands;

void ServerCommandInvoker::add_command(ServerCommand* command) {
    server_commands_.insert(command);
}

void ServerCommandInvoker::invoke(const std::string& message) {
    auto parsed_command = CommandParser::parse(message, ' ');

    for (auto command : server_commands_) {
        if (command->get_name() == parsed_command->get_name()) {
            command->execute(parsed_command->get_args());
        }
    }
}
