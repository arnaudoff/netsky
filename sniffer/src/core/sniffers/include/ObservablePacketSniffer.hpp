#ifndef OBSERVABLE_PACKET_SNIFFER_HPP_
#define OBSERVABLE_PACKET_SNIFFER_HPP_

#include <vector>
#include <sys/types.h>

#include "../../include/PacketSnifferObserver.hpp"
#include "SniffedPacket.hpp"

namespace Sniffer {
    namespace Core {
        namespace Sniffers {
            class ObservablePacketSniffer {
                private:
                    std::vector<PacketSnifferObserver*> observers_;

                public:
                    void attach(PacketSnifferObserver* observer);
                    void detach(PacketSnifferObserver* observer);
                    void notify(SniffedPacket* sniffed_packet);
            };
        }
    }
}

#endif
