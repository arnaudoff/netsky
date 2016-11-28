#ifndef HEADER_FACTORY_REGISTRATOR_HPP_
#define HEADER_FACTORY_REGISTRATOR_HPP_

#include <utility>
#include <string>

#include "HeaderFactory.hpp"

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            template<typename T>
            class HeaderFactoryRegistrator : public HeaderFactory {
                HeaderFactoryRegistrator(const std::string& type_name) {
                    get_map()->insert(std::make_pair(type_name, &create_header<T>));
                }
            };
        }
    }
}

#endif
