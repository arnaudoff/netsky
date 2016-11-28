#ifndef HEADER_FACTORY_HPP_
#define HEADER_FACTORY_HPP_

#include <map>
#include <memory>

#include "Header.hpp"

namespace Sniffer {
    namespace Core {
        class SniffedPacket;
    }
}

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            class HeaderFactory {
                private:
                    using SniffedPacket = Sniffer::Core::SniffedPacket;

                    using map_t = std::map<
                        std::string,
                        std::unique_ptr<Header> (*)(const SniffedPacket*)>;

                    map_t* map_;

                protected:
                    map_t get_map();

                public:
                    std::unique_ptr<Header> create_instance(
                            const std::string& type_name,
                            const SniffedPacket* packet);
            }
        }
    }
}

#endif
