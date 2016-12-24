#ifndef RECEPTION_HANDLER_HPP_
#define RECEPTION_HANDLER_HPP_

#include "PolicyBindings.hpp"

#include "../../communications/serialization/include/SerializedObject.hpp"
#include "../../protocols/headers/include/HeaderFactory.hpp"

namespace Sniffer {
    namespace Core {
        namespace Layers {
            class Layer;
        }

        class SniffedPacket;

        class ReceptionHandler {
            private:
                Layers::Layer* layer_;
                SerializationMgr serializer_;
                Sniffer::Protocols::Headers::HeaderFactory header_factory_;

            public:
                ReceptionHandler(
                        Layers::Layer* layer,
                        const SerializationMgr& manager,
                        const Sniffer::Protocols::Headers::HeaderFactory& header_factory);

                void handle(
                        SniffedPacket& packet,
                        Communications::Serialization::SerializedObject acc,
                        int next_header_id);
        };
    }
}

#endif
