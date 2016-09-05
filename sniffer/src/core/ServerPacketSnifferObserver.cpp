#include "include/ServerPacketSnifferObserver.hpp"

#include "protocols/include/Ethernet.hpp"
#include "protocols/include/IPv4.hpp"
#include "protocols/include/TCP.hpp"

#include "communications/serialization/include/SerializableEntity.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Core::Protocols;
using namespace Sniffer::Core::Communications::Serialization;

ServerPacketSnifferObserver::ServerPacketSnifferObserver(
        Server* server,
        const SerializationMgr& serializer)
    : server_{server}, serializer_{serializer}
{}

void ServerPacketSnifferObserver::update(SniffedEntity* entity) {
    std::vector<SerializableEntity*> entities;

    Ethernet ethernet {entity};
    entities.push_back(&ethernet);

    IPv4 ip {entity, Ethernet::FRAME_SIZE};
    entities.push_back(&ip);

    if (ip.get_upper_layer_protocol() == IPPROTO_TCP) {
        TCP tcp {entity,  Ethernet::FRAME_SIZE + ip.get_size()};
        entities.push_back(&tcp);
    }

    auto final_obj = serializer_.create_object();

    for (auto entity : entities) {
        auto entity_obj = entity->serialize(serializer_);
        serializer_.set_object(final_obj, entity->get_name(), entity_obj);
    }

    server_->broadcast(final_obj.get_data());
}
