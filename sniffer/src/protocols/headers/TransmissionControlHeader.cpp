#include <netinet/in.h>
#include <sstream>
#include <memory>

#include "include/TransmissionControlHeader.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Protocols;
using namespace Sniffer::Protocols::Headers;
using namespace Sniffer::Protocols::Headers::Formats;
using namespace Sniffer::Communications::Serialization;

HeaderFactoryRegistrator<TransmissionControlHeader>
    TransmissionControlHeader::registrator_ {};

/**
 * @brief Constructs a TCP header of length length from a SniffedPacket by re-
 * interpreting the internal byte array of the SniffedPacket.
 *
 * @param length The length of the header to extract in bytes.
 * @param packet A reference to a SniffedPacket object.
 */
TransmissionControlHeader::TransmissionControlHeader(
        int length,
        SniffedPacket& packet)
    : Header{length},
    data_{(const struct TransmissionControl*)(packet.extract_header(length))}
    /*
    if (size_ < 20) {
        std::ostringstream exception_message;
        exception_message << "Invalid TCP header length: " <<
            size_ << " bytes.";
        throw std::out_of_range { exception_message.str() };
    }
    */
{}

/**
 * @brief Registers the header class into the global HeaderFactory registry.
 *
 * @param name A name which to use for the TransmissionControlHeader class.
 */
void TransmissionControlHeader::register_class(const std::string& name) {
    registrator_.register_header(name);
}

/**
 * @brief Retrieves the offset
 *
 * @return The offset.
 */
u_char TransmissionControlHeader::get_offset() const {
    return (data_->offset_x2 & 0xf0) >> 4;
}

/**
 * @brief Retrieves the 16 bit source port from the TCP header.
 *
 * @return The source port
 */
u_int16_t TransmissionControlHeader::get_source_port() const {
    return ntohs(data_->source_port);
}

/**
 * @brief Retrieves the 16 bit destination port from the TCP header.
 *
 * @return The destination port
 */
u_int16_t TransmissionControlHeader::get_destination_port() const {
    return ntohs(data_->destination_port);
}

/**
 * @brief Retrieves the 32 bit sequence number from the TCP header.
 *
 * @return The sequence number.
 */
int TransmissionControlHeader::get_sequence_number() const {
    return data_->sequence_number;
}

/**
 * @brief Retrieves the 32 bit acknowledgment number from the TCP header.
 *
 * @return The acknowledgment number.
 */
int TransmissionControlHeader::get_acknowledgment_number() const {
    return data_->acknowledgment_number;
}

int TransmissionControlHeader::get_next_header_id() const {
    return 0;
}

/**
 * @brief Defines the entity name for the class that is used when serializing
 * it as an object.
 *
 * @return The name of the entity.
 */
std::string TransmissionControlHeader::get_entity_name() const {
    return "tcp";
}

/**
 * @brief Serializes a TransmissionControlHeader object into an object of
 * type defined by the policy used for SerializationMgr.
 *
 * @param serializer The serializer to use.
 *
 * @return A serialized version of the fields in the TCP header.
 */
SerializedObject TransmissionControlHeader::serialize(
        const SerializationMgr& serializer) const {
    auto obj = serializer.create_object();

    serializer.set_value<u_int16_t>(obj, "src", get_source_port());
    serializer.set_value<u_int16_t>(obj, "dst", get_destination_port());
    // TODO: Extract to base...
    serializer.set_value<int>(obj, "length", get_length());

    return obj;
}

