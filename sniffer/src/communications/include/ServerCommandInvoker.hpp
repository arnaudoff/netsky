#ifndef SERVER_COMMAND_INVOKER_HPP_
#define SERVER_COMMAND_INVOKER_HPP_

#include "../commands/include/ServerCommand.hpp"

#include <string>
#include <unordered_set>

namespace Sniffer {
    namespace Communications {
        class ServerCommandInvoker {
            private:
                std::unordered_set<Commands::ServerCommand*> server_commands_;

            public:
                ServerCommandInvoker() {};

                void add_command(Commands::ServerCommand* command);

                void invoke(const std::string& received_message);

                ~ServerCommandInvoker() {};
        };
    }
}

#endif
