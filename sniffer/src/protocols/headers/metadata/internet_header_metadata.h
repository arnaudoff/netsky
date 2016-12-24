#ifndef INTERNET_HEADER_METADATA_HPP_
#define INTERNET_HEADER_METADATA_HPP_

#include <sys/types.h>
#include <string>

#include "HeaderMetadata.hpp"

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            namespace Metadata {
                class InternetHeaderMetadata : public HeaderMetadata {
                    public:
                        InternetHeaderMetadata(
                                int id,
                                std::string name,
                                int size,
                                bool has_variable_length,
                                int length_field_offset = 0);

                        virtual int calculate_length(
                                const u_char* length_field) const override;
                };
            }
        }
    }
}

#endif
