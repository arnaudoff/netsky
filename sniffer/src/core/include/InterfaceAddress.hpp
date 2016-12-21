#ifndef INTERFACE_ADDRESS_HPP_
#define INTERFACE_ADDRESS_HPP_

#include <memory>

#include "../addressing/include/Ipv4Address.hpp"
#include "../../communications/serialization/include/SerializedObject.hpp"
#include "../../communications/serialization/include/SerializableEntity.hpp"

namespace Sniffer {
    namespace Core {
        class InterfaceAddress :
                public Communications::Serialization::SerializableEntity {
            private:
                typedef std::shared_ptr<Addressing::IpAddress> ip_addr_t;

                ip_addr_t address_;
                ip_addr_t broadcast_address_;
                ip_addr_t destination_address_;
                ip_addr_t netmask_;

            public:
                InterfaceAddress(ip_addr_t addr, ip_addr_t bcast,
                        ip_addr_t dst, ip_addr_t netmask);

                Addressing::IpAddress* get_address() const;

                void set_address(ip_addr_t addr);

                Addressing::IpAddress* get_broadcast_address() const;

                void set_broadcast_address(ip_addr_t bcast);

                Addressing::IpAddress* get_destination_address() const;

                void set_destination_address(ip_addr_t dst);

                Addressing::IpAddress* get_netmask() const;

                void set_netmask(ip_addr_t netmask);

                virtual Communications::Serialization::SerializedObject
                    serialize(const SerializationMgr& serializer) const override;

                virtual std::string get_entity_name() const override;

                ~InterfaceAddress() override;
        };
    }
}

#endif
