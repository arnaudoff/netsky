#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <sys/socket.h>
#include <vector>
#include <string>
#include <memory>

#include "InterfaceAddress.hpp"

#include "../../communications/serialization/include/SerializedObject.hpp"
#include "../../communications/serialization/include/SerializableEntity.hpp"

namespace Sniffer {
    namespace Core {
        class Interface :
                public Communications::Serialization::SerializableEntity {
            private:
                std::string name_;
                std::string description_;
                std::vector<InterfaceAddress> addresses_;

            public:
                Interface(const char* name, const char* desc);

                std::string get_name() const;

                std::string get_description() const;

                void set_addresses(std::vector<InterfaceAddress> addresses);

                std::vector<InterfaceAddress> get_addresses() const;

                virtual Communications::Serialization::SerializedObject serialize(
                        const SerializationMgr& serializer) const override;

                virtual std::string get_entity_name() const override;

                ~Interface() override;

        };
    }
}

#endif
