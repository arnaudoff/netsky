#ifndef ETHERNET_HEADER_HPP_
#define ETHERNET_HEADER_HPP_

#include <sys/types.h>
#include <string>

#include "Header.hpp"
#include "HeaderFactoryRegistrator.hpp"
#include "../../../core/include/SniffedPacket.hpp"
#include "../formats/Ethernet.hpp"

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            class EthernetHeader : public Header {
                private:
                    static constexpr int ADDRESS_LENGTH = 6;
                    static HeaderFactoryRegistrator<EthernetHeader> registrator_;

                    const Formats::Ethernet* data_;

                public:
                    EthernetHeader(
                            int length,
                            Sniffer::Core::SniffedPacket& packet);

                    static void register_class(const std::string& name);

                    std::string get_destination_address() const;

                    std::string get_source_address() const;

                    u_short get_ether_type() const;

                    virtual int get_next_header_id() const override;

                    virtual std::string get_entity_name() const override;

                    virtual Communications::Serialization::SerializedObject
                        serialize(const SerializationMgr& serializer)
                        const override;

                    ~EthernetHeader() {};
            };
        }
    }
}

#endif
