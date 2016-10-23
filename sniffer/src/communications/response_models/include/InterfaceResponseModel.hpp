#ifndef INTERFACE_RESPONSE_MODEL_HPP_
#define INTERFACE_RESPONSE_MODEL_HPP_

#include <string>
#include "ResponseModel.hpp"

namespace Sniffer {
    namespace Communications {
        namespace ResponseModels {
            class InterfaceResponseModel : public ResponseModel {
                private:
                    std::string name_;
                    std::string description_;

                public:
                    InterfaceResponseModel(std::string name, std::string desc);

                    std::string get_name() const;

                    std::string get_description() const;

                    virtual Serialization::SerializedObject serialize(
                            const SerializationMgr& serializer) const override;

                    virtual std::string get_model_name() const override;

                    ~InterfaceResponseModel() override;

            }
        }
    }
}

#endif
