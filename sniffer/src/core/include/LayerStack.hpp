#ifndef LAYER_STACK_HPP_
#define LAYER_STACK_HPP_

#include "../../communications/serialization/include/SerializedObject.hpp"

namespace Sniffer {
    namespace Core {
        namespace Layers {
            class Layer;
        }

        class SniffedPacket;
        class LayerStack {
            private:
                Layers::Layer* highest_layer_;
                Layers::Layer* lowest_layer_;

            public:
                LayerStack();

                enum class Position {
                    TOP,
                    ABOVE,
                    BELOW
                };

                void add_layer(
                        Layers::Layer* layer,
                        Position pos = Position::TOP,
                        Layers::Layer* existing = nullptr);

                void remove_layer(Layers::Layer* layer);

                void handle_reception(
                        SniffedPacket& packet,
                        Sniffer::Communications::Serialization::SerializedObject acc,
                        int next_header_id);
        };
    }
}

#endif
