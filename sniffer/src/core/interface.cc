#include "include/Interface.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Utils;
using namespace Sniffer::Communications::Serialization;

Interface::Interface(const char* name, const char* desc)
    : name_{name ? name : std::string()},
    description_{desc ? desc : std::string()}
{}

std::string Interface::get_name() const {
    return name_;
}

std::string Interface::get_description() const {
    return description_;
}

void Interface::set_addresses(std::vector<InterfaceAddress> addresses) {
    addresses_ = addresses;
}

std::vector<InterfaceAddress> Interface::get_addresses() const {
    return addresses_;
}

SerializedObject Interface::serialize(
        const SerializationMgr& serializer) const {
    auto obj = serializer.create_object();
    serializer.set_value<std::string>(obj, "name", name_);

    if (!description_.empty()) {
        serializer.set_value<std::string>(obj, "description", description_);
    }

    for (const auto addr: addresses_) {
        auto addr_obj = addr.serialize(serializer);

        if (!serializer.is_empty(addr_obj)) {
            serializer.push_back_obj(obj, "addresses", addr_obj);
        }
    }

    return obj;
}

std::string Interface::get_entity_name() const {
    return get_name();
}

Interface::~Interface() {}
