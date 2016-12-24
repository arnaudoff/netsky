#ifndef IP_ADDRESS_FACTORY_HPP_
#define IP_ADDRESS_FACTORY_HPP_

#include <sys/socket.h>
#include <memory>

#include "IpAddress.hpp"

namespace sniffer {

namespace core {

namespace addressing {

class IpAddressFactory {
   public:
    std::unique_ptr<IpAddress> parse(struct sockaddr* sockaddr);
};

}
}
}

#endif
