#ifndef IP_ADDRESS_FACTORY_HPP_
#define IP_ADDRESS_FACTORY_HPP_

#include <memory>
#include <sys/socket.h>

#include "IpAddress.hpp"

namespace Sniffer {
    namespace Core {
        namespace Addressing {
            class IpAddressFactory {
                public:
                    std::unique_ptr<IpAddress> parse(struct sockaddr* sockaddr);
            };
        }
    }
}

#endif
