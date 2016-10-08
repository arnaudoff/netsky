#include <netinet/in.h>
#include <sstream>
#include <memory>

#include "include/TCP.hpp"

using namespace Sniffer::Protocols;
using namespace Sniffer::Communications::Serialization;

TCP::TCP(Sniffer::Core::SniffedEntity* entity, int aggregated_offset)
    : header_{(tcp_header_t*)(entity->get_data() + aggregated_offset)},
    size_{get_offset() * 4} {
    if (size_ < 20) {
        std::ostringstream exception_message;
        exception_message << "Invalid TCP header length: " <<
            size_ << " bytes.";
        throw std::out_of_range { exception_message.str() };
    }
}

int TCP::get_size() const {
    return size_;
}

u_char TCP::get_offset() const {
    return (header_->th_offx2 & 0xf0) >> 4;
}

u_int16_t TCP::get_source_port() const {
    return ntohs(header_->th_sport);
}

u_int16_t TCP::get_destination_port() const {
    return ntohs(header_->th_dport);
}

std::string TCP::get_name() const {
    return "tcp";
}

SerializedObject TCP::serialize(const SerializationMgr& serializer) const {
    auto obj = serializer.create_object();

    serializer.set_value<u_int16_t>(obj, "src", get_source_port());
    serializer.set_value<u_int16_t>(obj, "dst", get_destination_port());
    serializer.set_value<int>(obj, "size", get_size());

    return obj;
}

