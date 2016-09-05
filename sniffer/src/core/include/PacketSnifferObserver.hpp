#ifndef PACKET_SNIFFER_OBSERVER_HPP_
#define PACKET_SNIFFER_OBSERVER_HPP_

#include <memory>
#include <sys/types.h>

#include "SniffedEntity.hpp"

namespace Sniffer {
    namespace Core {
        class PacketSnifferObserver {
            public:
                virtual void update(SniffedEntity* sniffed_packet) = 0;
                virtual ~PacketSnifferObserver() {};
        };
    }
}

#endif
