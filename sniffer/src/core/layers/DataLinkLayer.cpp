#include "include/DataLinkLayer.hpp"

using namespace Sniffer::Core::Layers;

DataLinkLayer::DataLinkLayer()
    : reception_handler_{this}
{}

void DataLinkLayer::handle_reception(SniffedPacket* packet) {
    reception_handler_.handle(packet);
}
