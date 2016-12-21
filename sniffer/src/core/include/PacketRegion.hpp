#ifndef PACKET_REGION_HPP_
#define PACKET_REGION_HPP_

namespace Sniffer {
    namespace Core {
        struct PacketRegion {
            int offset;
            int length;

            PacketRegion()
                : offset{0}, length{0}
            {}

            PacketRegion(int offset, int length)
                : offset{offset}, length{length}
            {}
        };
    }
}

#endif
