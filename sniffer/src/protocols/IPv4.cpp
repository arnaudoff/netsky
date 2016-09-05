#include <arpa/inet.h>
#include <sstream>

#include "include/IPv4.hpp"

using namespace Sniffer::Protocols;
using namespace Sniffer::Communications::Serialization;

IPv4::IPv4(SniffedEntity* entity, int aggregated_offset)
    : header_{(ipv4_header_t*)(entity->get_data() + aggregated_offset)},
    size_{get_header_length() * 4} {
    if (size_ < 20) {
        std::ostringstream exception_message;
        exception_message << "Invalid IP header length: " << size_ << " bytes.";
        throw std::out_of_range { exception_message.str() };
    }
}

u_char IPv4::get_header_length() const {
    return header_->ip_vhl & 0x0f;
}

u_char IPv4::get_version() const {
    return header_->ip_vhl >> 4;
}

u_char IPv4::get_upper_layer_protocol() const {
    return header_->ip_p;
}

char* IPv4::get_source_address() const {
    return inet_ntoa(header_->ip_src);
}

char* IPv4::get_destination_address() const {
    return inet_ntoa(header_->ip_dst);
}

int IPv4::get_size() const {
    return size_;
}

std::string IPv4::get_name() const {
    return "ipv4";
}

SerializedObject IPv4::serialize(const SerializationMgr& serializer) const {
    auto obj = serializer.create_object();

    serializer.set_value<u_char>(obj, "version", get_version());
    serializer.set_value<u_char>(obj, "upper_layer", get_upper_layer_protocol());
    serializer.set_value<char*>(obj, "src", get_source_address());
    serializer.set_value<char*>(obj, "dst", get_destination_address());
    serializer.set_value<int>(obj, "size", get_size());

    return obj;
}

