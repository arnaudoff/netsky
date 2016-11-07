#include <memory>
#include <spdlog/spdlog.h>

#include "include/IpAddressFactory.hpp"
#include "include/Ipv4Address.hpp"
#include "include/Ipv6Address.hpp"

using namespace Sniffer::Core;

std::shared_ptr<IpAddress> IpAddressFactory::parse(struct sockaddr* sockaddr) {
    if (sockaddr) {
        switch (sockaddr->sa_family) {
            case AF_INET:
                return std::make_shared<Ipv4Address>(sockaddr);
            case AF_INET6:
                return std::make_shared<Ipv6Address>(sockaddr);
            default:
                break;
        }
    }

    return nullptr;
}
