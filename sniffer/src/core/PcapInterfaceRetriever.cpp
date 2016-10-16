#include <sstream>
#include <pcap/pcap.h>

#include "include/PcapInterfaceRetriever.hpp"
#include "include/InterfaceRetrieverException.hpp"

using namespace Sniffer::Core;

std::vector<std::string> PcapInterfaceRetriever::retrieve() {
    pcap_if_t* pcap_interfaces;
    pcap_if_t* current_pcap_interface;

    char error_buffer[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(&pcap_interfaces, error_buffer) == -1) {
        std::ostringstream exception_message;
        exception_message << "Couldn't retrieve interfaces: " << error_buffer;
        throw InterfaceRetrieverException { exception_message.str() };
    }

    std::vector<std::string> interfaces;

    for (current_pcap_interface = pcap_interfaces;
            current_pcap_interface;
            current_pcap_interface = current_pcap_interface->next) {
        interfaces.push_back(current_pcap_interface->name);
    }

    return interfaces;
}
