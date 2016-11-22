#ifndef NETWORK_LAYER_HPP_
#define NETWORK_LAYER_HPP_

#include "Layer.hpp"
#include "../include/ReceptionHandler.hpp"

class SniffedPacket;

namespace Sniffer {
    namespace Core {
        namespace Layers {
            class NetworkLayer : public Layer {
                private:
                    ReceptionHandler reception_handler_;

                public:
                    NetworkLayer();

                    void handle_reception(SniffedPacket* packet);
            };
        }
    }
}

#endif
