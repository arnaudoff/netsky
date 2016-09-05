#ifndef PARSED_COMMAND_HPP_
#define PARSED_COMMAND_HPP_

#include <vector>
#include <string>

namespace Sniffer {
    namespace Communications {
        namespace Commands {
            class ParsedCommand {
                private:
                    std::string name_;
                    std::vector<std::string> arguments_;

                public:
                    ParsedCommand(std::string name, std::vector<std::string> arguments)
                        : name_{name}, arguments_{arguments}
                    {}

                    std::string get_name() const {
                        return name_;
                    }

                    std::vector<std::string> get_args() const {
                        return arguments_;
                    }

            };
        }
    }
}

#endif
