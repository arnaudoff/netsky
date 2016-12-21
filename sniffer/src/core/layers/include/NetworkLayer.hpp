#ifndef NETWORK_LAYER_HPP_
#define NETWORK_LAYER_HPP_

#include "Layer.hpp"

namespace Sniffer {
    namespace Core {
        class SniffedPacket;

        namespace Layers {
            class NetworkLayer : public Layer {
                public:
                    NetworkLayer(
                          const SerializationMgr& serializer,
                          const Sniffer::Protocols::Headers::HeaderFactory& hf);

                    virtual void handle_reception(
                            SniffedPacket& packet,
                            Communications::Serialization::SerializedObject acc,
                            int next_header_id) override;
            };
        }
    }
}

#endif
