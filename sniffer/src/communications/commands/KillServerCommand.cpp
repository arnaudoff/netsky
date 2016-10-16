#include "include/KillServerCommand.hpp"

using namespace Sniffer::Communications::Commands;

KillServerCommand::KillServerCommand(Server* server, const SerializationMgr& serializer)
    : ServerCommand{"kill", server, serializer}
{}

std::map<std::string, std::vector<std::string>> KillServerCommand::parse(
        const std::string& data) const {
    std::map<std::string, std::vector<std::string>> arguments;
    return arguments;
}

void KillServerCommand::execute(
        const ConnectionData& con_data,
        std::map<std::string, std::vector<std::string>> args) {
    server_->stop();
}
