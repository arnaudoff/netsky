#ifndef ETHERNET_HEADER_FORMAT_HPP_
#define ETHERNET_HEADER_FORMAT_HPP_

#include <sys/types.h>

// IEEE 802.3 Ethernet p.53 section 3.1.1

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            namespace Formats {
                struct Ethernet {
                    u_char destination_address[6];
                    u_char source_address[6];
                    u_short ether_type;
                };
            }
        }
    }
}

#endif
