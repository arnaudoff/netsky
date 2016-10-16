#ifndef KILL_SERVER_COMMAND_HPP_
#define KILL_SERVER_COMMAND_HPP_

#include "ServerCommand.hpp"

namespace Sniffer {
    namespace Communications {
        namespace Commands {
            class KillServerCommand : public ServerCommand {
                public:
                    KillServerCommand(Server* server, const SerializationMgr& serializer);

                    virtual std::map<std::string, std::vector<std::string>>
                        parse(const std::string& data) const override;

                    virtual void execute(
                            const ConnectionData& con_data,
                            std::map<std::string, std::vector<std::string>> args) override;

                    ~KillServerCommand() {};
            };
        }
    }
}

#endif
