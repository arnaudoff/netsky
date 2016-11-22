#ifndef APPLICATION_LAYER_HPP_
#define APPLICATION_LAYER_HPP_

#include "Layer.hpp"
#include "../include/ReceptionHandler.hpp"

class SniffedPacket;

namespace Sniffer {
    namespace Core {
        namespace Layers {
            class ApplicationLayer : public Layer {
                private:
                    ReceptionHandler reception_handler_;

                public:
                    ApplicationLayer();

                    void handle_reception(SniffedPacket* packet);
            };
        }
    }
}

#endif
