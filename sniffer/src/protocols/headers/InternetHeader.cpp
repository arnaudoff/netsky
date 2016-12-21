#include <arpa/inet.h>
#include <sstream>

#include "include/InternetHeader.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Communications::Serialization;
using namespace Sniffer::Protocols::Headers;
using namespace Sniffer::Protocols::Headers::Formats;

HeaderFactoryRegistrator<InternetHeader> InternetHeader::registrator_ {};

/**
 * @brief Constructs an Internet header from a SniffedPacket, reinterpreting
 * the internal byte array of the SniffedPacket object.
 *
 * @param length The length of the header to extract in bytes.
 * @param packet A reference to a SnifffedPacket object.
 */
InternetHeader::InternetHeader(int length, SniffedPacket& packet)
    : Header{length},
    data_{(const struct Internet*)(packet.extract_header(length))} {
    /*
    if (size_ < 20) {
        std::ostringstream exception_message;
        exception_message << "Invalid IP header length: " << size_ << " bytes.";
        throw std::out_of_range { exception_message.str() };
    }
    data_ = (const struct Internet*)(packet.extract_header());
    */
}

/**
 * @brief Registers the header class into the global HeaderFactory registry.
 *
 * @param name A name which to use for the InternetHeader class.
 */
void InternetHeader::register_class(const std::string& name) {
    registrator_.register_header(name);
}

/**
 * @brief Parses the VIHL field.
 *
 * @return The version which is encoded into the VIHL field of the packet
 * header.
 */
u_char InternetHeader::get_version() const {
    return data_->version_internet_header_length >> 4;
}

/**
 * @brief Retrieves the source IP address.
 *
 * @return A pointer to the beginning of the source IP address.
 */
char* InternetHeader::get_source_address() const {
    return inet_ntoa(data_->source_address);
}

/**
 * @brief Retrieves the destination IP address.
 *
 * @return A pointer to the beginning of the destination IP address.
 */
char* InternetHeader::get_destination_address() const {
    return inet_ntoa(data_->destination_address);
}

/**
 * @brief Defines the next_header_id for the upper layer protocol.
 *
 * @return The value of the Protocol field of the packet, i.e TCP or UDP.
 */
int InternetHeader::get_next_header_id() const {
    return data_->protocol;
}

/**
 * @brief Defines the entity name for the class that is used when serializing
 * it as an object.
 *
 * @return The name of the entity.
 */
std::string InternetHeader::get_entity_name() const {
    return "internet";
}

/**
 * @brief Serializes an InternetHeader object into an object of type defined
 * by the policy used for SerializationMgr.
 *
 * @param serializer The serializer to use.
 *
 * @return A serialized version of the fields in the Interner Protocol header.
 */
SerializedObject InternetHeader::serialize(const SerializationMgr& serializer) const {
    auto obj = serializer.create_object();

    // TODO: Extract the upper_layer stuff into the Header and call the base
    // implementation from here.
    serializer.set_value<u_char>(obj, "version", get_version());
    serializer.set_value<u_char>(obj, "upper_layer", get_next_header_id());
    serializer.set_value<char*>(obj, "src", get_source_address());
    serializer.set_value<char*>(obj, "dst", get_destination_address());
    serializer.set_value<int>(obj, "length", get_length());

    return obj;
}

