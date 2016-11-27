#ifndef TRANSPORT_LAYER_HPP_
#define TRANSPORT_LAYER_HPP_

#include "Layer.hpp"
#include "../../include/ReceptionHandler.hpp"

namespace Sniffer {
    namespace Core {
        class SniffedPacket;

        namespace Layers {
            class TransportLayer : public Layer {
                private:
                    ReceptionHandler reception_handler_;

                public:
                    TransportLayer();

                    virtual void handle_reception(
                            const SniffedPacket* packet,
                            Communications::Serialization::SerializedObject acc,
                            int next_header) override;

            };
        }
    }
}

#endif
