#ifndef SNIFFED_PACKET_HPP_
#define SNIFFED_PACKET_HPP_

#include <sys/types.h>

namespace Sniffer {
    namespace Core {
        namespace Sniffers {
            class SniffedPacket {
                private:
                    const u_char* data_;

                public:
                    SniffedPacket(const u_char* data)
                        : data_{data} {}

                    SniffedPacket() {};

                    const u_char* get_data() const {
                        return data_;
                    }
            };
        }
    }
}

#endif
