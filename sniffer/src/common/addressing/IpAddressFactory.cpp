#include <memory>
#include <spdlog/spdlog.h>

#include "include/IpAddressFactory.hpp"
#include "include/Ipv4Address.hpp"
#include "include/Ipv6Address.hpp"

using namespace Sniffer::Core::Addressing;

// Effective Modern C++, Meyers, p.119 & p.124
std::unique_ptr<IpAddress> IpAddressFactory::parse(struct sockaddr* sockaddr) {
    if (sockaddr) {
        switch (sockaddr->sa_family) {
            case AF_INET:
                return std::make_unique<Ipv4Address>(sockaddr);
            case AF_INET6:
                return std::make_unique<Ipv6Address>(sockaddr);
            default:
                break;
        }
    }

    return nullptr;
}
