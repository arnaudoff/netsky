#ifndef SNIFFED_PACKET_SERIALIZER_HPP_
#define SNIFFED_PACKET_SERIALIZER_HPP_

#include <sys/types.h>
#include <string>

#include "../sniffers/include/SniffedPacket.hpp"

namespace Sniffer {
    namespace Core {
        class SniffedPacketSerializer {
            public:
                virtual std::string serialize(Sniffers::SniffedPacket* sniffed_packet) = 0;
        };
    }
}

#endif
