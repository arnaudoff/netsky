#ifndef DATA_LINK_LAYER_HPP_
#define DATA_LINK_LAYER_HPP_

#include "Layer.hpp"
#include "../include/ReceptionHandler.hpp"

class SniffedPacket;

namespace Sniffer {
    namespace Core {
        namespace Layers {
            class DataLinkLayer : public Layer {
                private:
                    ReceptionHandler reception_handler_;

                public:
                    DataLinkLayer();

                    void handle_reception(SniffedPacket* packet);
            };
        }
    }
}

#endif
