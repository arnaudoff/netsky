#ifndef PACKET_PARSER_HPP_
#define PACKET_PARSER_HPP_

#include "PolicyBindings.hpp"
#include "../../communications/serialization/include/SerializedObject.hpp"

namespace Sniffer {
    namespace Core {
        class PacketParser {
            private:
                SerializationMgr serializer_;

            public:
                PacketParser(const SerializationMgr& serializer);

                std::string parse(const u_char* packet);
        };
    }
}

#endif
