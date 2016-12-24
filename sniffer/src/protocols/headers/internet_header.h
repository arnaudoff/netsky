#ifndef INTERNET_HEADER_HPP_
#define INTERNET_HEADER_HPP_

#include <sys/types.h>
#include <string>

#define IP_RF 0x8000            /* reserved fragment flag */
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */

#include "Header.hpp"
#include "HeaderFactoryRegistrator.hpp"
#include "../../../core/include/SniffedPacket.hpp"
#include "../formats/Internet.hpp"

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            class InternetHeader : public Header {
                private:
                    static HeaderFactoryRegistrator<InternetHeader> registrator_;

                    const Formats::Internet* data_;

                public:
                    InternetHeader(int length, Sniffer::Core::SniffedPacket& packet);

                    static void register_class(const std::string& name);

                    u_char get_version() const;

                    u_char get_header_length() const;

                    u_char get_type_of_service() const;

                    u_short get_total_length() const;

                    u_short get_identification() const;

                    u_char get_flags() const;

                    u_short get_fragment_offset() const;

                    u_short get_time_to_live() const;

                    u_char get_protocol() const;

                    u_short get_header_checksum() const;

                    char* get_source_address() const;

                    char* get_destination_address() const;

                    virtual int get_next_header_id() const override;

                    virtual Communications::Serialization::SerializedObject
                        serialize(const SerializationMgr& serializer) const override;

                    virtual std::string get_entity_name() const override;

                    ~InternetHeader() {};
            };
        }
    }
}

#endif
