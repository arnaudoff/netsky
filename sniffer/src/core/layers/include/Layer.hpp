#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <map>

#include "../../../communications/serialization/include/SerializedObject.hpp"

class SniffedPacket;

namespace Sniffer {
    namespace Core {
        namespace Layers {
            class Layer {
                private:
                    using map_t = std::map<int, std::string>;

                    Layer* lower_layer_;
                    Layer* upper_layer_;
                    map_t supported_header_types_;

                public:
                    Layer();

                    virtual void handle_reception(
                            const SniffedPacket* packet,
                            Communications::Serialization::SerializedObject acc,
                            int next_header) = 0;

                    Layer* get_lower_layer() const;

                    void set_lower_layer(Layer* layer);

                    Layer* get_upper_layer() const;

                    void set_upper_layer(Layer* layer);

                    map_t get_supported_header_types() const;

                    void set_supported_header_types(
                            const map_t& types);

                    virtual ~Layer() {};
            };

        }
    }
}

#endif
