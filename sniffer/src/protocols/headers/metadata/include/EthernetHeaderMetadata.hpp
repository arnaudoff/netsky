#ifndef ETHERNET_HEADER_METADATA_HPP_
#define ETHERNET_HEADER_METADATA_HPP_

#include <sys/types.h>
#include <string>

#include "HeaderMetadata.hpp"

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            namespace Metadata {
                class EthernetHeaderMetadata : public HeaderMetadata {
                    public:
                        EthernetHeaderMetadata(
                                int id,
                                std::string name,
                                int size,
                                bool has_variable_length,
                                int length_field_offset = 0);
                };
            }
        }
    }
}

#endif
