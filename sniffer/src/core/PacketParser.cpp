#include "include/PacketParser.hpp"

#include "../protocols/include/Ethernet.hpp"
#include "../protocols/include/IPv4.hpp"
#include "../protocols/include/TCP.hpp"

#include "../communications/serialization/include/SerializableEntity.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Protocols;
using namespace Sniffer::Communications;
using namespace Sniffer::Communications::Serialization;

PacketParser::PacketParser(const SerializationMgr& serializer)
    : serializer_{serializer}
{}

std::string PacketParser::parse(const u_char* packet) {
    std::vector<SerializableEntity*> entities;

    Ethernet ethernet { packet };
    entities.push_back(&ethernet);

    IPv4 ip { packet, Ethernet::FRAME_SIZE };
    entities.push_back(&ip);

    if (ip.get_upper_layer_protocol() == IPPROTO_TCP) {
        TCP tcp { packet,  Ethernet::FRAME_SIZE + ip.get_size()};
        entities.push_back(&tcp);
    }

    auto final_obj = serializer_.create_object();

    for (auto entity : entities) {
        auto entity_obj = entity->serialize(serializer_);
        serializer_.set_object(final_obj, entity->get_entity_name(), entity_obj);
    }

    return final_obj.get_data();
}

