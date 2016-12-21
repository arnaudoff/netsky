#include <cstring>

#include "include/Ipv6Address.hpp"

using namespace Sniffer::Core::Addressing;

Ipv6Address::Ipv6Address(struct sockaddr* sockaddr) {
    struct sockaddr_in6* addr_in6 = (struct sockaddr_in6*)sockaddr;
    buffer_ = new char[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &(addr_in6->sin6_addr), buffer_, INET6_ADDRSTRLEN);
}

Ipv6Address::Ipv6Address(const Ipv6Address& other) {
    buffer_ = new char[INET6_ADDRSTRLEN];
    strcpy(buffer_, other.buffer_);
}

Ipv6Address& Ipv6Address::operator=(const Ipv6Address& other) {
    if (this != &other) {
        delete[] buffer_;

        buffer_ = new char[INET6_ADDRSTRLEN];
        strcpy(buffer_, other.buffer_);
    }

    return *this;
}

char* Ipv6Address::data() const {
    return buffer_;
}

Ipv6Address::~Ipv6Address() {
    delete[] buffer_;
}

