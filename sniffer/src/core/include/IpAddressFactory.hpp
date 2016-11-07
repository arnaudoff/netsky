#ifndef IP_ADDRESS_FACTORY_HPP_
#define IP_ADDRESS_FACTORY_HPP_

#include <memory>
#include <sys/socket.h>

#include "IpAddress.hpp"

namespace Sniffer {
    namespace Core {
        class IpAddressFactory {
            public:
                std::shared_ptr<IpAddress> parse(struct sockaddr* sockaddr);
        };
    }
}

#endif
