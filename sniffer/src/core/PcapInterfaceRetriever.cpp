#include <sstream>
#include <pcap/pcap.h>

#include <spdlog/spdlog.h>

#include "include/PcapInterfaceRetriever.hpp"
#include "include/InterfaceRetrieverException.hpp"
#include "include/Interface.hpp"

using namespace Sniffer::Core;

std::vector<Interface> PcapInterfaceRetriever::retrieve() {
    spdlog::get("console")->info("Retrieving pcap interfaces..");

    pcap_if_t* interfaces;
    pcap_if_t* current_interface;
    char error_buffer[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(&interfaces, error_buffer) == -1) {
        std::ostringstream exception_message;
        exception_message << "Couldn't retrieve interfaces: " << error_buffer;
        throw InterfaceRetrieverException { exception_message.str() };
    }

    std::vector<Interface> retrieved_interfaces;

    for (current_interface = interfaces;
            current_interface;
            current_interface = current_interface->next) {
        char* name = current_interface->name;
        char* description = current_interface->description;

        spdlog::get("console")->info("Retrieved {0} (desc: {1})", name,
                description ? description : "none");

        Interface interface { name, description };

        pcap_addr_t* current_if_addresses = current_interface->addresses;
        pcap_addr_t* current_if_address;

        std::vector<InterfaceAddress> interface_addresses;

        for (current_if_address = current_if_addresses;
                current_if_address;
                current_if_address = current_if_address->next) {
            auto ip_addr = ip_addr_factory_.parse(current_if_address->addr);
            if (ip_addr) {
                spdlog::get("console")->info("Retrieved IP address for {0}: {1}",
                        name, ip_addr->data());
            }

            auto broad_addr = ip_addr_factory_.parse(current_if_address->broadaddr);
            if (broad_addr) {
                spdlog::get("console")->info("Retrieved BA for {0}: {1}",
                            name, broad_addr->data());
            }

            auto dst_addr = ip_addr_factory_.parse(current_if_address->dstaddr);
            if (dst_addr) {
                spdlog::get("console")->info("Retrieved DA for {0}: {1}",
                        name, dst_addr->data());
            }

            auto netmask = ip_addr_factory_ .parse(current_if_address->netmask);
            if (netmask) {
                spdlog::get("console")->info("Retrieved SM for {0}: {1}",
                        name, netmask->data());
            }

            InterfaceAddress if_addr { ip_addr, broad_addr, dst_addr, netmask };
            interface_addresses.push_back(if_addr);
        }

        interface.set_addresses(interface_addresses);

        retrieved_interfaces.push_back(interface);
    }

    return retrieved_interfaces;
}
