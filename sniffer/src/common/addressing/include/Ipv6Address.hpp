#ifndef IPV6_ADDRESS_HPP_
#define IPV6_ADDRESS_HPP_

#include <arpa/inet.h>
#include <sys/socket.h>

#include "IpAddress.hpp"

namespace Sniffer {
    namespace Core {
        namespace Addressing {
            class Ipv6Address : public IpAddress {
                private:
                    char* buffer_;

                public:
                    Ipv6Address(struct sockaddr* sockaddr);

                    Ipv6Address(const Ipv6Address& other);

                    Ipv6Address& operator=(const Ipv6Address& other);

                    virtual char* data() const override;

                    ~Ipv6Address();
            };
        }
    }
}

#endif
