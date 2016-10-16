#ifndef START_PACKET_SNIFFER_COMMAND_HPP_
#define START_PACKET_SNIFFER_COMMAND_HPP_

#include "ServerCommand.hpp"
#include "../../../core/include/PacketParser.hpp"

namespace Sniffer {
    namespace Communications {
        namespace Commands {
            class StartPacketSnifferCommand : public ServerCommand {
                private:
                    Sniffer::Core::PacketParser packet_parser_;

                public:
                    StartPacketSnifferCommand(
                            Server* server,
                            const SerializationMgr& serializer,
                            const Sniffer::Core::PacketParser& packet_parser);

                    virtual std::map<std::string, std::vector<std::string>>
                        parse(const std::string& data) const override;

                    virtual void execute(
                            const ConnectionData& con_data,
                            std::map<std::string, std::vector<std::string>> args) override;

                    ~StartPacketSnifferCommand() {};
            };
        }
    }
}

#endif
