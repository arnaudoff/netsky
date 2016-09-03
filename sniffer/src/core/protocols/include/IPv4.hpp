#ifndef IPV4_HPP_
#define IPV4_HPP_

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>

#include "../../sniffers/include/SniffedPacket.hpp"

#define IP_RF 0x8000            /* reserved fragment flag */
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */

namespace Sniffer {
    namespace Core {
        namespace Protocols {
            class IPv4 {
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
                    IPv4(Sniffers::SniffedPacket* sniffed_packet, int aggregated_offset)
                        : header_{(ipv4_header_t*)(sniffed_packet->get_data() + aggregated_offset)},
                        size_{get_header_length() * 4}
                    {
                        if (size_ < 20) {
                            std::ostringstream exception_message;
                            exception_message << "Invalid IP header length: " << size_ << " bytes.";
                            throw std::out_of_range { exception_message.str() };
                        }
                    }

                    u_char get_header_length() const {
                        return header_->ip_vhl & 0x0f;
                    }

                    u_char get_version() const {
                        return header_->ip_vhl >> 4;
                    }

                    u_char get_upper_layer_protocol() const {
                        return header_->ip_p;
                    }

                    char* get_source() const {
                        return inet_ntoa(header_->ip_src);
                    }

                    char* get_destination() const {
                        return inet_ntoa(header_->ip_dst);
                    }

                    int get_size() const {
                        return size_;
                    }

                    ~IPv4() {};
            };
        }
    }
}

#endif
