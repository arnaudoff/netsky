#ifndef NETWORK_LAYER_HPP_
#define NETWORK_LAYER_HPP_

#include "Layer.hpp"
#include "../../include/ReceptionHandler.hpp"

namespace Sniffer {
    namespace Core {
        class SniffedPacket;

        namespace Layers {
            class NetworkLayer : public Layer {
                private:
                    ReceptionHandler reception_handler_;

                public:
                    NetworkLayer();

                    virtual void handle_reception(
                            const SniffedPacket* packet,
                            Communications::Serialization::SerializedObject acc,
                            int next_header) override;
            };
        }
    }
}

#endif
