#ifndef LAYER_STACK_HPP_
#define LAYER_STACK_HPP_

class SniffedPacket;
class Layer;

namespace Sniffer {
    namespace Core {
        class LayerStack {
            private:
                Layer* highest_layer_;
                Layer* lowest_layer_;

            public:
                LayerStack();

                enum class Position {
                    TOP,
                    ABOVE,
                    BELOW
                };

                void add_layer(
                        Layer* layer,
                        Position pos = Position::TOP,
                        Layer* existing = nullptr);

                void remove_layer(Layer* layer);

                void handle_receive(SniffedPacket* packet);
        };
    }
}

#endif
