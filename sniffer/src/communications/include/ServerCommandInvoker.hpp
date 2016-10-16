#ifndef SERVER_COMMAND_INVOKER_HPP_
#define SERVER_COMMAND_INVOKER_HPP_

#include <string>
#include <unordered_set>

#include "../commands/include/ServerCommand.hpp"
#include "ConnectionData.hpp"

namespace Sniffer {
    namespace Communications {
        class ServerCommandInvoker {
            private:
                std::unordered_set<Commands::ServerCommand*> server_commands_;

            public:
                ServerCommandInvoker() {};

                void add_command(Commands::ServerCommand* command);

                void invoke(const ConnectionData& con_data,
                        const std::string& received_message);

                ~ServerCommandInvoker() {};
        };
    }
}

#endif
