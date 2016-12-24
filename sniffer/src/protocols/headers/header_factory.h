#ifndef HEADER_FACTORY_HPP_
#define HEADER_FACTORY_HPP_

#include <map>
#include <memory>

#include "Header.hpp"
#include "../../../core/include/SniffedPacket.hpp"

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            class HeaderFactory {
                private:
                    using SniffedPacket = Sniffer::Core::SniffedPacket;

                    using map_type = std::map<
                        std::string,
                        std::unique_ptr<Header> (*)(int, SniffedPacket&)>;

                    map_type* map_;

                protected:
                    map_type* get_map();

                public:
                    std::unique_ptr<Header> create_instance(
                            const std::string& class_name,
                            int length,
                            SniffedPacket& packet);
            };
        }
    }
}

#endif
