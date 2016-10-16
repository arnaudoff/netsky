#ifndef INTERFACE_RETRIEVER_HPP_
#define INTERFACE_RETRIEVER_HPP_

#include <vector>
#include <string>

namespace Sniffer {
    namespace Core {
        class InterfaceRetriever {
            public:
                virtual std::vector<std::string> retrieve() = 0;
        };
    }
}

#endif
