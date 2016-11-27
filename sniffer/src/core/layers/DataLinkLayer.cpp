#include "include/DataLinkLayer.hpp"

using namespace Sniffer::Core::Layers;

DataLinkLayer::DataLinkLayer()
    : reception_handler_{this}
{}

void DataLinkLayer::handle_reception(SniffedPacket* packet, int next_header) {
    reception_handler_.handle(packet);
}
