#ifndef LAYER_HPP_
#define LAYER_HPP_

class SniffedPacket;

namespace Sniffer {
    namespace Core {
        namespace Layers {
            class Layer {
                private:
                    Layer* lower_layer_;
                    Layer* upper_layer_;

                public:
                    Layer();

                    virtual void handle_reception(SniffedPacket* packet) = 0;

                    Layer* get_lower_layer() const;

                    void set_lower_layer(Layer* layer);

                    Layer* get_upper_layer() const;

                    void set_upper_layer(Layer* layer);
            };

        }
    }
}

#endif
