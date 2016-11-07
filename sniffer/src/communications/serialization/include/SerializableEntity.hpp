#ifndef SERIALIZABLE_ENTITY_HPP_
#define SERIALIZABLE_ENTITY_HPP_

#include <sys/types.h>
#include <string>

#include "SerializedObject.hpp"
#include "../../../core/include/PolicyBindings.hpp"

namespace Sniffer {
    namespace Communications {
        namespace Serialization {
            class SerializableEntity {
                public:
                    virtual SerializedObject serialize(
                            const SerializationMgr& serializer) const = 0;

                    virtual std::string get_entity_name() const = 0;

                    virtual ~SerializableEntity() {};
            };

        }
    }
}

#endif
