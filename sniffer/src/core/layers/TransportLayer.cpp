#include "include/TransportLayer.hpp"

using namespace Sniffer::Core::Layers;

TransportLayer::TransportLayer()
    : reception_handler_{this}
{}

void TransportLayer::handle_reception(SniffedPacket* packet, int next_header) {
    reception_handler_.handle(packet);
}
