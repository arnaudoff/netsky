#ifndef RETRIEVE_INTERFACES_COMMAND_HPP_
#define RETRIEVE_INTERFACES_COMMAND_HPP_

#include "ServerCommand.hpp"
#include "../../../core/include/InterfaceRetriever.hpp"

namespace Sniffer {
    namespace Communications {
        namespace Commands {
            class RetrieveInterfacesCommand : public ServerCommand {
                private:
                    std::unique_ptr<Core::InterfaceRetriever> interface_retriever_;

                public:
                    RetrieveInterfacesCommand(
                            Server* server,
                            const SerializationMgr& serializer,
                            std::unique_ptr<Core::InterfaceRetriever> retriever);

                    virtual std::map<std::string, std::vector<std::string>>
                        parse(const std::string& data) const override;

                    virtual void execute(
                            const ConnectionData& con_data,
                            std::map<std::string,
                            std::vector<std::string>> args) override;

                    ~RetrieveInterfacesCommand() {};
            };
        }
    }
}

#endif
