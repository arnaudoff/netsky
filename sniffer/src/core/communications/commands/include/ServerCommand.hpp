#ifndef SERVER_COMMAND_HPP_
#define SERVER_COMMAND_HPP_

#include <string>
#include <vector>

#include "../../include/Server.hpp"

namespace Sniffer {
    namespace Core {
        namespace Communications {
            namespace Commands {
                class ServerCommand {
                    protected:
                        using Server = Sniffer::Core::Communications::Server;

                        std::string name_;
                        Server* server_;

                    public:
                        ServerCommand(const std::string& name, Server* server)
                            : name_{name}, server_{server}
                        {}

                        std::string get_name() const {
                            return name_;
                        }

                        virtual void execute(const std::vector<std::string>& arguments) = 0;

                        virtual ~ServerCommand() = 0;
                };
            }
        }
    }
}

#endif
