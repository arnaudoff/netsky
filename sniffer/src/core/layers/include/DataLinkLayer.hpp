#ifndef DATA_LINK_LAYER_HPP_
#define DATA_LINK_LAYER_HPP_

#include "Layer.hpp"
#include "../../include/ReceptionHandler.hpp"

namespace Sniffer {
    namespace Core {
        class SniffedPacket;

        namespace Layers {
            class DataLinkLayer : public Layer {
                private:
                    ReceptionHandler reception_handler_;

                public:
                    DataLinkLayer();

                    virtual void handle_reception(
                            const SniffedPacket* packet,
                            Communications::Serialization::SerializedObject acc,
                            int next_header) override;
            };
        }
    }
}

#endif
