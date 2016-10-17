#ifndef RESPONSE_MODEL_HPP_
#define RESPONSE_MODEL_HPP_

#include "../../serialization/include/SerializedObject.hpp"
#include "../../serialization/include/SerializableEntity.hpp"

namespace Sniffer {
    namespace Communications {
        namespace ResponseModels {
            class ResponseModel : public Serialization::SerializableEntity {
                public:
                    virtual Serialization::SerializedObject serialize(
                            const SerializationMgr& serializer) const = 0;

                    virtual std::string get_name() const = 0;

                    virtual ~ResponseModel() {}
            };
        }
    }
}

#endif
