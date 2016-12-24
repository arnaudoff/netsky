#ifndef IPV4_ADDRESS_HPP_
#define IPV4_ADDRESS_HPP_

#include <arpa/inet.h>
#include <sys/socket.h>

#include "IpAddress.hpp"

namespace Sniffer {
    namespace Core {
        namespace Addressing {
            class Ipv4Address : public IpAddress {
                private:
                    char* buffer_;

                public:
                    Ipv4Address(struct sockaddr* sockaddr);

                    Ipv4Address(const Ipv4Address& other);

                    Ipv4Address& operator=(const Ipv4Address& other);

                    virtual char* data() const override;

                    ~Ipv4Address();
            };
        }
    }
}

#endif
