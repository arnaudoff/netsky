#ifndef INTERFACE_RETRIEVER_HPP_
#define INTERFACE_RETRIEVER_HPP_

#include <vector>

#include "Interface.hpp"
#include "../addressing/include/IpAddressFactory.hpp"

namespace Sniffer {
    namespace Core {
        class InterfaceRetriever {
            protected:
                Addressing::IpAddressFactory ip_addr_factory_;

            public:
                InterfaceRetriever(const Addressing::IpAddressFactory& factory)
                    : ip_addr_factory_{factory}
                {}

                virtual std::vector<Interface> retrieve() = 0;
        };
    }
}

#endif
