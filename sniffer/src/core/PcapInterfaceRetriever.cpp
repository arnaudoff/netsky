#include <sstream>
#include <pcap/pcap.h>

#include "include/PcapInterfaceRetriever.hpp"
#include "include/InterfaceRetrieverException.hpp"
#include "include/Interface.hpp"

using namespace Sniffer::Core;

std::vector<Interface> PcapInterfaceRetriever::retrieve() {
    pcap_if_t* pcap_interfaces;
    pcap_if_t* current_pcap_interface;

    char error_buffer[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(&pcap_interfaces, error_buffer) == -1) {
        std::ostringstream exception_message;
        exception_message << "Couldn't retrieve interfaces: " << error_buffer;
        throw InterfaceRetrieverException { exception_message.str() };
    }

    std::vector<Interface> interfaces;

    for (current_pcap_interface = pcap_interfaces;
            current_pcap_interface;
            current_pcap_interface = current_pcap_interface->next) {
        char* name = current_pcap_interface->name;
        char* description = current_pcap_interface->description;
        pcap_addr_t* pcap_iface_addresses = current_pcap_interface->addresses;
        pcap_addr_t* current_pcap_iface_addr;

        for (curr_pcap_if_addr = pcap_iface_addresses;
                current_pcap_iface_addr;
                current_pcap_iface_addr= current_pcap_iface_addr->next) {
            struct sockaddr* addr = current_pcap_iface_addr->addr;
            struct sockaddr* netmask = current_pcap_iface_addr->netmask;
            // http://stackoverflow.com/questions/1276294/getting-ipv4-address-from-a-sockaddr-structure
        }

    }

    return interfaces;
}
