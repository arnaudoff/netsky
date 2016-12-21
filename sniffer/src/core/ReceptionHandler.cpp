#include <algorithm>
#include <sys/types.h>

#include "include/ReceptionHandler.hpp"
#include "layers/include/Layer.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Core::Layers;
using namespace Sniffer::Protocols::Headers;
using namespace Sniffer::Communications::Serialization;

/**
 * @brief Constructs a ReceptionHandler object
 *
 * @param layer A raw pointer to the current layer for which the handler is
 * is acting upon.
 * @param serializer A const reference to the SerializationMgr to use while
 * serializing values into accumulated object.
 * @param header_factory A const reference to a HeaderFactory to use in order to
 * construct the correct header objects.
 */
ReceptionHandler::ReceptionHandler(
        Layer* layer,
        const SerializationMgr& serializer,
        const HeaderFactory& header_factory)
    : layer_{layer},
    serializer_{serializer},
    header_factory_{header_factory}
{}

/**
 * @brief Handles the reception of a SniffedPacket.
 *
 * @param packet A reference to the packet to interpret.
 * @param accumulator_obj A reference to a SerializedObject that is used
 * as accumulator for storage of the interpreted fields while going up the stack
 * @param next_header_id An integer that is mapped to the header type.
 */
void ReceptionHandler::handle(
        SniffedPacket& packet,
        SerializedObject accumulator_obj,
        int next_header_id) {

    // Check if the current layer contains this header ID as supported
    auto header = std::find_if(
            layer_->begin(),
            layer_->end(),
            [next_header_id] (const auto& hm) {
                return hm.id() == next_header_id;
            });

    // The layer has metadata for a header with such an ID
    if (header != layer_->end()) {
        std::string name = header->name();

        // In order to initialize the header, we need to know its exact length.
        int length = 0;
        if (header->has_variable_length()) {
            // In this case, we have to peek into the raw data before forming
            const u_char* len_field =
                packet.peek(header->length_field_offset());
            length = header->calculate_length(len_field);
        } else {
            // Otherwise this is a casual fixed-length header such as Ethernet
            length = header->length();
        }

        // Now that we have the name and the size of the header, create an
        // object of its type and pass it the raw data.
        auto header_instance =
            header_factory_.create_instance(name, length, packet);

        // Finally, serialize the parsed fields of the header and append
        // the generated object to the accumulating object.
        auto serialized_obj = header_instance->serialize(serializer_);
        serializer_.set_object(accumulator_obj, name, serialized_obj);

        // Continue up the layer stack
        Layer* upper_layer = layer_->get_upper_layer();
        if (upper_layer) {
            upper_layer->handle_reception(
                    packet,
                    accumulator_obj,
                    header_instance->get_next_header_id());
        } else {
            // We have reached the top of the layer stack, nothing more to interpret
            return;
        }
    } else {
        // The header is not supported yet.
        return;
    }
}
