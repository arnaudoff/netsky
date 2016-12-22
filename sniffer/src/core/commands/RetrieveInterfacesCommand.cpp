#include "include/RetrieveInterfacesCommand.hpp"

#include "../response_models/include/RetrieveInterfacesResponseModel.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Communications::ResponseModels;
using namespace Sniffer::Communications::Commands;

RetrieveInterfacesCommand::RetrieveInterfacesCommand(
        Server* server,
        const SerializationMgr& serializer,
        std::unique_ptr<InterfaceRetriever> retriever)
    : ServerCommand{"retrieve-interfaces", server, serializer},
    interface_retriever_{std::move(retriever)}
{}

std::map<std::string, std::vector<std::string>> RetrieveInterfacesCommand::parse(
        const std::string& data) const {
    std::map<std::string, std::vector<std::string>> arguments;
    return arguments;
}

void RetrieveInterfacesCommand::execute(
        const ConnectionData& con_data,
        std::map<std::string, std::vector<std::string>> args) {
    auto interfaces = interface_retriever_->retrieve();

    RetrieveInterfacesResponseModel model { interfaces };
    auto model_obj = model.serialize(serializer_);

    server_->unicast(con_data, model_obj.get_data());
}
