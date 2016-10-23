#include "include/RetrieveInterfacesResponseModel.hpp"

using namespace Sniffer::Communications::ResponseModels;
using namespace Sniffer::Communications::Serialization;

RetrieveInterfacesResponseModel::RetrieveInterfacesResponseModel(
        std::vector<InterfaceResponseModel> interfaces)
    : interfaces_{interfaces}
{}

SerializedObject RetrieveInterfacesResponseModel::serialize(
        const SerializationMgr& serializer) const {
    auto obj = serializer.create_object();

    for (const auto& iface: interfaces_) {
        auto iface_obj = iface.serialize(serializer);
        obj.set_object(obj, iface.get_model_name(), iface_obj);
    }

    auto final_obj = serializer.create_object();
    serializer.set_object(final_obj, get_name(), obj);

    return final_obj;
}

std::string RetrieveInterfacesResponseModel::get_model_name() const {
    return "interfaces";
}

RetrieveInterfacesResponseModel::~RetrieveInterfacesResponseModel() {}

