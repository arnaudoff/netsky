#ifndef SNIFFED_PACKET_JSON_SERIALIZER_HPP_
#define SNIFFED_PACKET_JSON_SERIALIZER_HPP_

#include <sys/types.h>
#include <string>

#include "../sniffers/include/SniffedPacket.hpp"
#include "SniffedPacketSerializer.hpp"

namespace Sniffer {
    namespace Core {
        class SniffedPacketJsonSerializer : public SniffedPacketSerializer {
            public:
                SniffedPacketJsonSerializer() {};

                virtual std::string serialize(Sniffers::SniffedPacket* sniffed_packet) override;

                ~SniffedPacketJsonSerializer() {};
        };
    }
}

#endif
