#ifndef IPV4_HPP_
#define IPV4_HPP_

#include <sys/types.h>
#include <memory>
#include <string>

#include <netinet/in.h> // in_addr

#include "../../include/PolicyBindings.hpp"
#include "../../communications/serialization/include/SerializableEntity.hpp"
#include "../../include/SniffedEntity.hpp"

#define IP_RF 0x8000            /* reserved fragment flag */
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */

namespace Sniffer {
    namespace Core {
        namespace Protocols {
            class IPv4 : public Core::Communications::Serialization::SerializableEntity {
                private:
                    typedef struct {
                        u_char ip_vhl;
                        u_char ip_tos;
                        u_short ip_len;
                        u_short ip_id;
                        u_short ip_off;
                        u_char ip_ttl;
                        u_char ip_p;
                        u_short ip_sum;
                        struct in_addr ip_src, ip_dst;
                    } ipv4_header_t;

                    const ipv4_header_t* header_;
                    int size_;

                public:
                    IPv4(SniffedEntity* entity, int aggregated_offset);

                    u_char get_header_length() const;

                    u_char get_version() const;

                    u_char get_upper_layer_protocol() const;

                    char* get_source_address() const;

                    char* get_destination_address() const;

                    int get_size() const;

                    virtual Core::Communications::Serialization::SerializedObject
                        serialize(const SerializationMgr& serializer) const override;

                    virtual std::string get_name() const override;

                    ~IPv4() {};
            };
        }
    }
}

#endif
