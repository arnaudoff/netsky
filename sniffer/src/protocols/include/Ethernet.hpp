#ifndef ETHERNET_HPP_
#define ETHERNET_HPP_

#include <sys/types.h>
#include <string>

#include "../../core/include/PolicyBindings.hpp"
#include "../../core/include/SniffedEntity.hpp"
#include "../../communications/serialization/include/SerializableEntity.hpp"

namespace Sniffer {
    namespace Protocols {
        class Ethernet : public Communications::Serialization::SerializableEntity {
            private:
                static const int ADDRESS_LENGTH = 6;

                typedef struct {
                    u_char destination_address[ADDRESS_LENGTH];
                    u_char source_address[ADDRESS_LENGTH];
                    u_short ether_type;
                } ether_header_t;

                const ether_header_t* header_;

            public:
                static const int FRAME_SIZE = 14;

                Ethernet(Core::SniffedEntity* entity);

                std::string get_destination_address() const;

                std::string get_source_address() const;

                u_short get_ether_type() const;

                virtual Communications::Serialization::SerializedObject
                    serialize(const SerializationMgr& serializer) const override;

                virtual std::string get_name() const override;

                ~Ethernet() {};
        };
    }
}

#endif
