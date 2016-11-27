#include "include/NetworkLayer.hpp"

using namespace Sniffer::Core::Layers;

NetworkLayer::NetworkLayer()
    : reception_handler_{this}
{}

void NetworkLayer::handle_reception(SniffedPacket* packet, int next_header) {
    reception_handler_.handle(packet);
}
