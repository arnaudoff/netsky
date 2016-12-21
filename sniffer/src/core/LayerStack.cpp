#include "include/LayerStack.hpp"
#include "layers/include/Layer.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Core::Layers;

/**
 * @brief Constructs a LayerStack object.
 */
LayerStack::LayerStack()
    : highest_layer_{nullptr}, lowest_layer_{nullptr}
{}

/**
 * @brief Handles the reception of a SniffedPacket by defering it to the lowest
 * layer of the LayerStack.
 *
 * @param packet A reference to a SniffedPacket object.
 * @param accumulator The object to use to accumulate the parsed properties.
 * @param next_header The header ID of the next header.
 */
void LayerStack::handle_reception(
        SniffedPacket& packet,
        Sniffer::Communications::Serialization::SerializedObject accumulator,
        int next_header) {
    if (lowest_layer_) {
        lowest_layer_->handle_reception(packet, accumulator, next_header);
    }
    // else throw
}

void LayerStack::add_layer(
        Layer* layer,
        LayerStack::Position position,
        Layer* existing_layer) {
    layer->set_lower_layer(nullptr);
    layer->set_upper_layer(nullptr);

    if (highest_layer_) {
        switch (position) {
            case LayerStack::Position::TOP:
                {
                    highest_layer_->set_upper_layer(layer);
                    layer->set_lower_layer(highest_layer_);
                    highest_layer_ = layer;

                    break;
                }
            case LayerStack::Position::ABOVE:
                {
                    Layer* previous_upper_layer = existing_layer->get_upper_layer();
                    layer->set_upper_layer(previous_upper_layer);
                    layer->set_lower_layer(existing_layer);
                    existing_layer->set_upper_layer(layer);

                    if (existing_layer == highest_layer_) {
                        highest_layer_ = layer;
                    } else {
                        previous_upper_layer->set_lower_layer(layer);
                    }

                    break;
                }
            case LayerStack::Position::BELOW:
                {
                    Layer* previous_lower_layer = existing_layer->get_lower_layer();
                    layer->set_lower_layer(previous_lower_layer);
                    layer->set_upper_layer(existing_layer);
                    existing_layer->set_lower_layer(layer);

                    if (existing_layer == lowest_layer_) {
                        lowest_layer_ = layer;
                    } else {
                        previous_lower_layer->set_upper_layer(layer);
                    }

                    break;
                }
        }
    } else {
        highest_layer_ = layer;
        lowest_layer_ = layer;
    }
}

void LayerStack::remove_layer(Layer* layer) {
    if (layer == highest_layer_) {
        /*
         * |..x..| <- layer to remove
         * |.....|
         */
        highest_layer_ = layer->get_lower_layer();

        // If this was not the only layer in the stack
        if (highest_layer_) {
            highest_layer_->set_upper_layer(nullptr);
        }
    } else {
        /*
         * |.....|
         * |..x..| <- layer to remove
         * |.....|
         */
        (layer->get_upper_layer())->set_lower_layer(layer->get_lower_layer());
    }

    if (layer == lowest_layer_) {
        /*
         * |.....|
         * |..x..| <- layer to remove
         */
        lowest_layer_ = layer->get_upper_layer();

        // If this was not the only layer in the stack
        if (lowest_layer_) {
            lowest_layer_->set_lower_layer(nullptr);
        }
    } else {
        /*
         * |.....|
         * |..x..| <- layer to remove
         * |.....|
         */
        (layer->get_lower_layer())->set_upper_layer(layer->get_upper_layer());
    }

    layer->set_upper_layer(nullptr);
    layer->set_lower_layer(nullptr);
}
