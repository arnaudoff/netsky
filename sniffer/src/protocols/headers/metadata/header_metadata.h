#ifndef HEADER_METADATA_HPP_
#define HEADER_METADATA_HPP_

#include <sys/types.h>
#include <string>

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            namespace Metadata {
                class HeaderMetadata {
                    private:
                        int id_;
                        std::string name_;
                        int length_;
                        bool has_variable_length_;
                        int length_field_offset_;

                    public:
                        HeaderMetadata(
                                int id,
                                std::string name,
                                int length,
                                bool has_variable_length,
                                int length_field_offset = 0);

                        int id() const;

                        std::string name() const;

                        int length() const;

                        bool has_variable_length() const;

                        int length_field_offset() const;

                        virtual int calculate_length(
                                const u_char* length_field) const;

                        virtual ~HeaderMetadata() {};
                };
            }
        }
    }
}

#endif
