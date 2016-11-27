#include "include/PhysicalLayer.hpp"

using namespace Sniffer::Core::Layers;

PhysicalLayer::PhysicalLayer()
    : reception_handler_{this}
{}

void PhysicalLayer::handle_reception(SniffedPacket* packet, int next_header) {
    reception_handler_.handle(packet);
}
