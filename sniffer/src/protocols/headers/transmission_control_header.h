#ifndef TRANSMISSION_CONTROL_HEADER_HPP_
#define TRANSMISSION_CONTROL_HEADER_HPP_

#include <sys/types.h>

#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
#define TH_ECE 0x40
#define TH_CWR 0x80
#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)

#include "Header.hpp"
#include "HeaderFactoryRegistrator.hpp"
#include "../../../core/include/SniffedPacket.hpp"
#include "../formats/TransmissionControl.hpp"

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            class TransmissionControlHeader : public Header {
                private:
                    static HeaderFactoryRegistrator<TransmissionControlHeader>
                        registrator_;

                    const Formats::TransmissionControl* data_;

                public:
                    TransmissionControlHeader(
                            int length,
                            Sniffer::Core::SniffedPacket& packet);

                    static void register_class(const std::string& name);

                    u_int16_t get_source_port() const;

                    u_int16_t get_destination_port() const;

                    int get_sequence_number() const;

                    int get_acknowledgment_number() const;

                    u_char get_offset() const;

                    virtual int get_next_header_id() const override;

                    virtual Communications::Serialization::SerializedObject
                        serialize(const SerializationMgr& serializer) const override;

                    virtual std::string get_entity_name() const override;

                    ~TransmissionControlHeader() {};
            };
        }
    }
}

#endif
