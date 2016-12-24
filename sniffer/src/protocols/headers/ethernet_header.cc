#include <iomanip>
#include <sstream>

#include "include/EthernetHeader.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Communications::Serialization;
using namespace Sniffer::Protocols::Headers;
using namespace Sniffer::Protocols::Headers::Formats;

HeaderFactoryRegistrator<EthernetHeader> EthernetHeader::registrator_ {};

/**
 * @brief Constructs an Ethernet header from a SniffedPacket, reinterpreting
 * the internal byte array of the SniffedPacket object.
 *
 * @param length The length of the header to extract in bytes.
 * @param packet A reference to a SniffedPacket object.
 */
EthernetHeader::EthernetHeader(int length, SniffedPacket& packet)
    : Header{length},
    data_{(const struct Ethernet*)(packet.extract_header(length))}
{}

/**
 * @brief Registers the header class into the global HeaderFactory registry.
 *
 * @param name A name which to use for the EthernetHeader class.
 */
void EthernetHeader::register_class(const std::string& name) {
    registrator_.register_header(name);
}

/**
 * @brief Retrieves the destination MAC address.
 *
 * @return The destination MAC address of the frame.
 */
std::string EthernetHeader::get_destination_address() const {
    std::ostringstream os;
    for (int byte_count = 0;
            byte_count < EthernetHeader::ADDRESS_LENGTH;
            byte_count++) {
        os << std::setw(2) << std::setfill('0') <<
            std::hex << (int)(data_->destination_address[byte_count]);
        if (byte_count < EthernetHeader::ADDRESS_LENGTH - 1) {
            os << ":";
        }
    }

    return os.str();
}

/**
 * @brief Retrieves the source MAC address.
 *
 * @return The source MAC address of the frame.
 */
std::string EthernetHeader::get_source_address() const {
    std::ostringstream os;
    for (int byte_count = 0;
            byte_count < EthernetHeader::ADDRESS_LENGTH;
            byte_count++) {
        os << std::setw(2) << std::setfill('0') <<
            std::hex << (int)(data_->source_address[byte_count]);
        if (byte_count < ADDRESS_LENGTH - 1) {
            os << ":";
        }
    }

    return os.str();
}

/**
 * @brief Retrieves the EtherType field of the frame.
 *
 * @return A two-byte value indicating the upper layer protocol that is carried.
 */
u_short EthernetHeader::get_ether_type() const {
    return data_->ether_type;
}

/**
 * @brief Defines the next_header_id for the upper layer protocol.
 *
 * @return The value of the EtherType field of the frame.
 */
int EthernetHeader::get_next_header_id() const {
    return get_ether_type();
}

/**
 * @brief Defines the entity name for the class that is used when serializing
 * it as an object.
 *
 * @return The name of the entity.
 */
std::string EthernetHeader::get_entity_name() const {
    return "ethernet";
}

/**
 * @brief Serializes an EthernetHeader object into an object of type defined
 * by the policy used for SerializationMgr.
 *
 * @param serializer The serializer to use.
 *
 * @return A serialized version of the fields in the Ethernet header.
 */
SerializedObject EthernetHeader::serialize(const SerializationMgr& serializer) const {
    auto obj = serializer.create_object();

    serializer.set_value<std::string>(obj, "dest", get_destination_address());
    serializer.set_value<std::string>(obj, "src", get_source_address());
    serializer.set_value<u_short>(obj, "ether_type", get_ether_type());

    return obj;
}
