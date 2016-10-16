#ifndef TCP_HPP_
#define TCP_HPP_

#include <sys/types.h>

#include "../../core/include/PolicyBindings.hpp"
#include "../../communications/serialization/include/SerializableEntity.hpp"

#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
#define TH_ECE 0x40
#define TH_CWR 0x80
#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)

namespace Sniffer {
    namespace Protocols {
        class TCP : public Communications::Serialization::SerializableEntity {
            private:
                typedef struct {
                    u_short th_sport;
                    u_short th_dport;
                    u_int th_seq;
                    u_int th_ack;
                    u_char th_offx2;
                    u_char th_flags;
                    u_short th_win;
                    u_short th_sum;
                    u_short th_urp;
                } tcp_header_t;

                const tcp_header_t* header_;
                int size_;

            public:
                TCP(const u_char* packet, int aggregated_offset);

                int get_size() const;

                u_char get_offset() const;

                u_int16_t get_source_port() const;

                u_int16_t get_destination_port() const;

                virtual Communications::Serialization::SerializedObject
                    serialize(const SerializationMgr& serializer) const override;

                virtual std::string get_name() const override;

                ~TCP() {};
        };
    }
}

#endif
