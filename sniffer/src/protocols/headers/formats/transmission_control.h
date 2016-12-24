#ifndef TRANSMISSION_CONTROL_HEADER_FORMAT_HPP_
#define TRANSMISSION_CONTROL_HEADER_FORMAT_HPP_

#include <sys/types.h>

// https://www.ietf.org/rfc/rfc793.txt section 3.1

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            namespace Formats {
                struct TransmissionControl {
                    u_short source_port;
                    u_short destination_port;
                    u_int sequence_number;
                    u_int acknowledgment_number;
                    u_char offset_x2;
                    u_char flags;
                    u_short window;
                    u_short checksum;
                    u_short urgent_pointer;
                };
            }
        }
    }
}

#endif
