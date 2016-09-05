#ifndef SERVER_PACKET_SNIFFER_OBSERVER_HPP_
#define SERVER_PACKET_SNIFFER_OBSERVER_HPP_

#include <sys/types.h>

#include "PolicyBindings.hpp"
#include "PacketSnifferObserver.hpp"
#include "SniffedEntity.hpp"
#include "../../communications/include/Server.hpp"

namespace Sniffer {
    namespace Core {
        class ServerPacketSnifferObserver : public PacketSnifferObserver {
            using Server = Communications::Server;

            private:
                Server* server_;
                SerializationMgr serializer_;

            public:
                ServerPacketSnifferObserver(
                        Server* server,
                        const SerializationMgr& serializer);

                virtual void update(SniffedEntity* entity) override;

                ~ServerPacketSnifferObserver() {};
        };
    }
}

#endif
