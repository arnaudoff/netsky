#ifndef PCAP_INTERFACE_RETRIEVER_HPP_
#define PCAP_INTERFACE_RETRIEVER_HPP_

#include "InterfaceRetriever.hpp"

#include <vector>
#include <string>

namespace Sniffer {
    namespace Core {
        class PcapInterfaceRetriever : public InterfaceRetriever {
            public:
                virtual std::vector<std::string> retrieve() override;
        };
    }
}

#endif
