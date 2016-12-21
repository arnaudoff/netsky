#ifndef INTERNET_HEADER_FORMAT_HPP_
#define INTERNET_HEADER_FORMAT_HPP_

#include <sys/types.h>
#include <netinet/in.h> // in_addr

// https://tools.ietf.org/html/rfc791#section-3.1

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            namespace Formats {
                struct Internet {
                    u_char version_internet_header_length;
                    u_char type_of_service;
                    u_short total_length;
                    u_short identification;
                    u_short offset;
                    u_char time_to_live;
                    u_char protocol;
                    u_short checksum;
                    struct in_addr source_address, destination_address;
                };
            }
        }
    }
}
#endif
