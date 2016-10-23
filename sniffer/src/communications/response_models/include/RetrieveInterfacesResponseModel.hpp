#ifndef RETRIEVE_INTERFACES_RESPONSE_MODEL_HPP_
#define RETRIEVE_INTERFACES_RESPONSE_MODEL_HPP_

#include <vector>
#include <string>

#include "ResponseModel.hpp"
#include "InterfaceResponseModel.hpp"

namespace Sniffer {
    namespace Communications {
        namespace ResponseModels {
            class RetrieveInterfacesResponseModel : public ResponseModel {
                private:
                    std::vector<InterfaceResponseModel> interfaces_;

                public:
                    RetrieveInterfacesResponseModel(std::vector<InterfaceResponseModel> interfaces);

                    virtual Serialization::SerializedObject serialize(
                            const SerializationMgr& serializer) const override;

                    virtual std::string get_model_name() const override;

                    ~RetrieveInterfacesResponseModel() override;
            };
        }
    }
}

#endif
