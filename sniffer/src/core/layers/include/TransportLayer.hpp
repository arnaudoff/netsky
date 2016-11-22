#ifndef TRANSPORT_LAYER_HPP_
#define TRANSPORT_LAYER_HPP_

#include "Layer.hpp"
#include "../include/ReceptionHandler.hpp"

class SniffedPacket;

namespace Sniffer {
    namespace Core {
        namespace Layers {
            class TransportLayer : public Layer {
                private:
                    ReceptionHandler reception_handler_;

                public:
                    TransportLayer();

                    void handle_reception(SniffedPacket* packet);
            };
        }
    }
}

#endif
