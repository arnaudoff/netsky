#include "include/InterfaceResponseModel.hpp"

using namespace Sniffer::Communications::ResponseModels;

InterfaceResponseModel::InterfaceResponseModel(std::string name, std::string desc)
    : name_{name}, description_{desc}
{}

std::string InterfaceResponseModel::get_name() const {
    return name_;
}

std::string InterfaceResponseModel::get_description() const {
    return description_;
}

SerializedObject InterfaceResponseModel::serialize(
        const SerializationMgr& serializer) const {
    auto obj = serializer.create_object();
    obj.set_value<std::string>(obj, "name", get_name());
    obj.set_value<std::string>(obj, "description", get_description());

    return obj;
}

std::string InterfaceResponseModel::get_model_name() const {
    return get_name();
}

InterfaceResponseModel::~InterfaceResponseModel() {}


