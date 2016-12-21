#ifndef APPLICATION_LAYER_HPP_
#define APPLICATION_LAYER_HPP_

#include "Layer.hpp"

namespace Sniffer {
    namespace Core {
        namespace Layers {
            class ApplicationLayer : public Layer {
                public:
                    ApplicationLayer(
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
