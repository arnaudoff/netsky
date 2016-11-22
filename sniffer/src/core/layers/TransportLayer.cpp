#include "include/TransportLayer.hpp"

using namespace Sniffer::Core::Layers;

TransportLayer::TransportLayer()
    : reception_handler_{this}
{}

void TransportLayer::handle_reception(SniffedPacket* packet) {
    reception_handler_.handle(packet);
}
