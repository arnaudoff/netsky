#ifndef SERVER_PACKET_SNIFFER_OBSERVER_HPP_
#define SERVER_PACKET_SNIFFER_OBSERVER_HPP_

#include <sys/types.h>

#include "PacketSnifferObserver.hpp"
#include "../sniffers/include/SniffedPacket.hpp"
#include "../communications/include/Server.hpp"

namespace Sniffer {
    namespace Core {
        class ServerPacketSnifferObserver : public PacketSnifferObserver {
            using Server = Communications::Server;

            private:
                Server* server_;
                std::unique_ptr<SniffedPacketSerializer> serializer_;

            public:
                ServerPacketSnifferObserver(
                        Server* server,
                        std::unique_ptr<SniffedPacketSerializer> serializer)
                    : server_{server}, serializer_{std::move(serializer)}
                {}

                virtual void update(Sniffers::SniffedPacket* sniffed_packet) override;

                ~ServerPacketSnifferObserver() {};
        };
    }
}

#endif
