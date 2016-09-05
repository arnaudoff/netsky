#include <vector>
#include <sstream>

#include "include/CommandParser.hpp"
#include "include/ParsedCommand.hpp"

using namespace Sniffer::Communications::Commands;

std::shared_ptr<ParsedCommand> CommandParser::parse(const std::string& message, char delimiter) {
    std::vector<std::string> command_tokens;
    std::stringstream message_stream(message);
    std::string token;

    while (std::getline(message_stream, token, delimiter)) {
        command_tokens.push_back(token);
    }

    std::vector<std::string> args { command_tokens.begin() + 1, command_tokens.end() };
    std::shared_ptr<ParsedCommand> parsed_command { new ParsedCommand { command_tokens.front(), args } };

    return parsed_command;
}
