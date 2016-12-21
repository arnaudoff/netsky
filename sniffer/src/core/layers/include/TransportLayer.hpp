#ifndef TRANSPORT_LAYER_HPP_
#define TRANSPORT_LAYER_HPP_

#include "Layer.hpp"

namespace Sniffer {
    namespace Core {
        namespace Layers {
            class TransportLayer : public Layer {
                public:
                    TransportLayer(
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
