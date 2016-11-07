#include <iomanip>
#include <sstream>

#include "include/Ethernet.hpp"

using namespace Sniffer::Protocols;
using namespace Sniffer::Communications::Serialization;

Ethernet::Ethernet(const u_char* packet)
    : header_{(ether_header_t*)(packet)}
{}

std::string Ethernet::get_destination_address() const {
    std::ostringstream os;
    for (int i = 0; i < ADDRESS_LENGTH; i++) {
        os << std::setw(2) << std::setfill('0') << 
            std::hex << (int)(header_->destination_address[i]);
        if (i < ADDRESS_LENGTH - 1) {
            os << ":";
        }
    }

    return os.str();
}

std::string Ethernet::get_source_address() const {
    std::ostringstream os;
    for (int i = 0; i < ADDRESS_LENGTH; i++) {
        os << std::setw(2) << std::setfill('0') <<
            std::hex << (int)(header_->source_address[i]);
        if (i < ADDRESS_LENGTH - 1) {
            os << ":";
        }
    }

    return os.str();
}

u_short Ethernet::get_ether_type() const {
    return header_->ether_type;
}

std::string Ethernet::get_entity_name() const {
    return "ethernet";
}

SerializedObject Ethernet::serialize(const SerializationMgr& serializer) const {
    auto obj = serializer.create_object();

    serializer.set_value<std::string>(obj, "dest", get_destination_address());
    serializer.set_value<std::string>(obj, "src", get_source_address());
    serializer.set_value<u_short>(obj, "ether_type", get_ether_type());

    return obj;
}

