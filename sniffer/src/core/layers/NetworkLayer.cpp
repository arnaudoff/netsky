#include "include/NetworkLayer.hpp"

using namespace Sniffer::Core::Layers;
using namespace Sniffer::Protocols::Headers;
using namespace Sniffer::Communications::Serialization;

NetworkLayer::NetworkLayer(
        const SerializationMgr& mgr,
        const HeaderFactory& hfactory)
    : Layer{mgr, hfactory}
{}

void NetworkLayer::handle_reception(
        SniffedPacket& packet,
        SerializedObject acc,
        int next_header_id) {
    reception_handler_.handle(packet, acc, next_header_id);
}
