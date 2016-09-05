#ifndef KILL_SERVER_COMMAND_HPP_
#define KILL_SERVER_COMMAND_HPP_

#include "ServerCommand.hpp"

namespace Sniffer {
    namespace Communications {
        namespace Commands {
            class KillServerCommand : public ServerCommand {
                public:
                    KillServerCommand(Server* server);

                    void execute(const std::vector<std::string>& arguments);

                    ~KillServerCommand() {};
            };
        }
    }
}

#endif
