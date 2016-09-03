#ifndef PACKET_SNIFFER_OBSERVER_HPP_
#define PACKET_SNIFFER_OBSERVER_HPP_

#include <memory>
#include <sys/types.h>

#include "SniffedPacketSerializer.hpp"
#include "../sniffers/include/SniffedPacket.hpp"

namespace Sniffer {
    namespace Core {
        class PacketSnifferObserver {
            public:
                virtual void update(Sniffers::SniffedPacket* sniffed_packet) = 0;
                virtual ~PacketSnifferObserver() {};
        };
    }
}

#endif
