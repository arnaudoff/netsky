#ifndef HEADER_FACTORY_REGISTRATOR_HPP_
#define HEADER_FACTORY_REGISTRATOR_HPP_

#include <utility>
#include <string>

#include "HeaderFactory.hpp"
#include "Header.hpp"

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            template<typename T>
            class HeaderFactoryRegistrator : public HeaderFactory {
                public:
                    using func_ptr_type =
                        std::unique_ptr<Header> (*)(int, Sniffer::Core::SniffedPacket&);

                    void register_header(const std::string& type_name) {
                        get_map()->insert(
                                std::pair<std::string, func_ptr_type>(
                                    type_name,
                                    &Header::create_header<T>));
                    }
            };
        }
    }
}

#endif
