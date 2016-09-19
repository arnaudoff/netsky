#include "include/KillServerCommand.hpp"

using namespace Sniffer::Communications::Commands;

KillServerCommand::KillServerCommand(Server* server)
    : ServerCommand{"kill", server}
{}


void KillServerCommand::execute(const std::vector<std::string>& arguments) {
    server_->stop();
}