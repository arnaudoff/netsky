#ifndef INTERFACE_RETRIEVER_HPP_
#define INTERFACE_RETRIEVER_HPP_

#include <vector>
#include "Interface.hpp"

namespace Sniffer {
    namespace Core {
        class InterfaceRetriever {
            public:
                virtual std::vector<Interface> retrieve() = 0;
        };
    }
}

#endif
