#ifndef PHYSICAL_LAYER_HPP_
#define PHYSICAL_LAYER_HPP_

#include "Layer.hpp"
#include "../../include/ReceptionHandler.hpp"

class SniffedPacket;

namespace Sniffer {
    namespace Core {
        class SniffedPacket;

        namespace Layers {
            class PhysicalLayer : public Layer {
                private:
                    ReceptionHandler reception_handler_;

                public:
                    PhysicalLayer();

                    virtual void handle_reception(
                            const SniffedPacket* packet,
                            Communications::Serialization::SerializedObject acc,
                            int next_header) override;

            };
        }
    }
}

#endif
