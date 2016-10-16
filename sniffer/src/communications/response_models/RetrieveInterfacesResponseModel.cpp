#include "include/RetrieveInterfacesResponseModel.hpp"

using namespace Sniffer::Communications::ResponseModels;
using namespace Sniffer::Communications::Serialization;

RetrieveInterfacesResponseModel::RetrieveInterfacesResponseModel(
        std::vector<std::string> names)
    : names_{names}
{}

SerializedObject RetrieveInterfacesResponseModel::serialize(
        const SerializationMgr& serializer) const {
    auto obj = serializer.create_object();

    serializer.set_value<std::vector<std::string>>(obj, "names", names_);

    auto final_obj = serializer.create_object();
    serializer.set_object(final_obj, get_name(), obj);

    return final_obj;
}

std::string RetrieveInterfacesResponseModel::get_name() const {
    return "interfaces";
}

RetrieveInterfacesResponseModel::~RetrieveInterfacesResponseModel() {}

