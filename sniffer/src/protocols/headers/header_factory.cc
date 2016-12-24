#include "include/Header.hpp"
#include "include/HeaderFactory.hpp"

using namespace Sniffer::Protocols::Headers;

using SniffedPacket = Sniffer::Core::SniffedPacket;
using map_type =
    std::map<std::string, std::unique_ptr<Header> (*)(int, SniffedPacket&)>;

/**
 * @brief Lazy loads the internal registry map.
 *
 * @return The internal registry map.
 */
map_type* HeaderFactory::get_map() {
    if (!map_) {
        map_ = new map_type;
    }

    return map_;
}

/**
 * @brief Creates a header with a runtime-determined type.
 *
 * @param class_name The name of the class that is registered.
 * @param length The length of the header to create an instance of.
 * @param packet The SniffedPacket object to pass to the header's constructor.
 *
 * @return A unique pointer to the Header object on the heap.
 */
std::unique_ptr<Header> HeaderFactory::create_instance(
        const std::string& class_name,
        int length,
        SniffedPacket& packet) {
    map_type::iterator it = get_map()->find(class_name);
    if (it == get_map()->end()) {
        return nullptr;
    }

    return it->second(length, packet);
}
