#ifndef SNIFFED_PACKET_HPP_
#define SNIFFED_PACKET_HPP_

#include <memory>
#include "PacketRegion.hpp"

namespace Sniffer {
    namespace Core {
        class SniffedPacket {
            private:
                PacketRegion header_;
                PacketRegion body_;
                PacketRegion trailer_;

                const u_char* data_;

            public:
                SniffedPacket(
                        const u_char* data,
                        PacketRegion body);

                const u_char* extract_header(int header_length);

                const u_char* extract_trailer(int trailer_length);

                const u_char* peek(int byte_offset);
        };
    }
}

#endif
