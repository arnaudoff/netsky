#ifndef DATA_LINK_LAYER_HPP_
#define DATA_LINK_LAYER_HPP_

#include "Layer.hpp"

namespace Sniffer {
    namespace Core {
        class SniffedPacket;

        namespace Layers {
            class DataLinkLayer : public Layer {
                public:
                    DataLinkLayer(
                            const SerializationMgr& serializer,
                            const Sniffer::Protocols::Headers::HeaderFactory& hfactory);

                    virtual void handle_reception(
                            SniffedPacket& packet,
                            Communications::Serialization::SerializedObject acc,
                            int next_header_id) override;
            };
        }
    }
}

#endif
