#include "include/ApplicationLayer.hpp"

using namespace Sniffer::Core::Layers;

ApplicationLayer::ApplicationLayer()
    : reception_handler_{this}
{}

void ApplicationLayer::handle_reception(SniffedPacket* packet, int next_header) {
    reception_handler_.handle(packet);
}
