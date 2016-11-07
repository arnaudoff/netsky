#include <cstring>

#include "include/Ipv4Address.hpp"

using namespace Sniffer::Core;

Ipv4Address::Ipv4Address(struct sockaddr* sockaddr) {
    struct sockaddr_in* addr_in = (struct sockaddr_in*)sockaddr;
    buffer_ = new char[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr_in->sin_addr), buffer_, INET_ADDRSTRLEN);
}

Ipv4Address::Ipv4Address(const Ipv4Address& other) {
    buffer_ = new char[INET_ADDRSTRLEN];
    strcpy(buffer_, other.buffer_);
}

Ipv4Address& Ipv4Address::operator=(const Ipv4Address& other) {
    if (this != &other) {
        delete[] buffer_;

        buffer_ = new char[INET_ADDRSTRLEN];
        strcpy(buffer_, other.buffer_);
    }

    return *this;
}

char* Ipv4Address::data() const {
    return buffer_;
}

Ipv4Address::~Ipv4Address() {
    delete[] buffer_;
}
