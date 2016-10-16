#ifndef RETRIEVE_INTERFACES_RESPONSE_MODEL_HPP_
#define RETRIEVE_INTERFACES_RESPONSE_MODEL_HPP_

#include <vector>
#include <string>

#include "ResponseModel.hpp"

namespace Sniffer {
    namespace Communications {
        namespace ResponseModels {
            class RetrieveInterfacesResponseModel : public ResponseModel {
                private:
                    std::vector<std::string> names_;

                public:
                    RetrieveInterfacesResponseModel(std::vector<std::string> names);

                    virtual Serialization::SerializedObject serialize(
                            const SerializationMgr& serializer) const override;

                    virtual std::string get_name() const override;

                    ~RetrieveInterfacesResponseModel() override;
            };
        }
    }
}

#endif
