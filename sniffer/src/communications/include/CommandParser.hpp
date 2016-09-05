#ifndef COMMAND_PARSER_HPP_
#define COMMAND_PARSER_HPP_

#include <memory>
#include "ParsedCommand.hpp"

namespace Sniffer {
    namespace Communications {
        namespace Commands {
            class CommandParser {
                public:
                    static std::shared_ptr<ParsedCommand> parse(
                            const std::string& message,
                            char delimiter);
            };
        }
    }
}

#endif
