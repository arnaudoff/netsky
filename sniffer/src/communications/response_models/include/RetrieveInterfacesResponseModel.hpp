#ifndef RETRIEVE_INTERFACES_RESPONSE_MODEL_HPP_
#define RETRIEVE_INTERFACES_RESPONSE_MODEL_HPP_

#include <vector>
#include <string>

#include "ResponseModel.hpp"
#include "../../../core/include/Interface.hpp"

namespace Sniffer {
    namespace Communications {
        namespace ResponseModels {
            class RetrieveInterfacesResponseModel : public ResponseModel {
                private:
                    std::vector<Core::Interface> interfaces_;

                public:
                    RetrieveInterfacesResponseModel(std::vector<Core::Interface> interfaces);

                    virtual Serialization::SerializedObject serialize(
                            const SerializationMgr& serializer) const override;

                    virtual std::string get_entity_name() const override;

                    ~RetrieveInterfacesResponseModel() override;
            };
        }
    }
}

#endif
