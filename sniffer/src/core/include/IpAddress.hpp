#ifndef IP_ADDRESS_HPP_
#define IP_ADDRESS_HPP_

namespace Sniffer {
    namespace Core {
        class IpAddress {
            public:
                virtual char* data() const = 0;

                virtual ~IpAddress() {};
        };
    }
}

#endif
