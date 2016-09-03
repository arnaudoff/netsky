#include "include/ServerPacketSnifferObserver.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Core::Sniffers;

void ServerPacketSnifferObserver::update(SniffedPacket* sniffed_packet) {
    auto json = serializer_->serialize(sniffed_packet);
    server_->broadcast(json);
}
