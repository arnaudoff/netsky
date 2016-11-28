#include "include/Header.hpp"
#include "include/HeaderFactory.hpp"

using namespace Sniffer::Protocols::Headers;

map_t HeaderFactory::get_map() {
    if (!map_) {
        map_ = new map_t;
    }

    return map_;
}

std::unique_ptr<Header> HeaderFactory::create_instance(
        const std::string& type_name,
        const Sniffer::Core::SniffedPacket* packet) {
    map_t::iterator it = get_map()->find(type_name);
    if (it == get_map()->end()) {
        return std::make_unique<Header>(nullptr);
    }

    return it->second(packet);
}
