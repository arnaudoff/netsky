#ifndef INTERFACE_RETRIEVER_HPP_
#define INTERFACE_RETRIEVER_HPP_

#include <vector>

#include "Interface.hpp"
#include "IpAddressFactory.hpp"

namespace Sniffer {
    namespace Core {
        class InterfaceRetriever {
            protected:
                IpAddressFactory ip_addr_factory_;

            public:
                InterfaceRetriever(const IpAddressFactory& factory)
                    : ip_addr_factory_{factory}
                {}

                virtual std::vector<Interface> retrieve() = 0;
        };
    }
}

#endif
