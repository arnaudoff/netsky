#ifndef PROTOCOL_HEADER_HPP_
#define PROTOCOL_HEADER_HPP_

#include "../../../communications/serialization/include/SerializableEntity.hpp"
#include "../../core/include/PolicyBindings.hpp"

namespace Sniffer {
    namespace Core {
        class SniffedPacket;
    }
}

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            class Header : public Communications::Serialization::SerializableEntity {
                private:
                    int length_;

                public:
                    Header(int length);

                    template<typename T>
                    static std::unique_ptr<Header> create_header(
                            int length,
                            Sniffer::Core::SniffedPacket& packet) {
                        return std::make_unique<T>(length, packet);
                    }

                    int get_length() const;

                    virtual int get_next_header_id() const = 0;

                    virtual Communications::Serialization::SerializedObject
                        serialize(const SerializationMgr& serializer) const = 0;

                    virtual std::string get_entity_name() const = 0;

                    virtual ~Header();
            };
        }
    }
}

#endif
