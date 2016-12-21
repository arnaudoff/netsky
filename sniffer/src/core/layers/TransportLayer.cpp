#include "include/TransportLayer.hpp"

using namespace Sniffer::Core::Layers;
using namespace Sniffer::Communications::Serialization;
using namespace Sniffer::Protocols::Headers;

TransportLayer::TransportLayer(
        const SerializationMgr& mgr,
        const HeaderFactory& hfactory)
    : Layer{mgr, hfactory}
{}

void TransportLayer::handle_reception(
        SniffedPacket& packet,
        SerializedObject acc,
        int next_header_id) {
    reception_handler_.handle(packet, acc, next_header_id);
}
