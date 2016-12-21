#include "include/InterfaceAddress.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Core::Addressing;
using namespace Sniffer::Communications::Serialization;

InterfaceAddress::InterfaceAddress(ip_addr_t addr, ip_addr_t bcast,
        ip_addr_t dst, ip_addr_t netmask)
    : address_{addr},
    broadcast_address_{bcast},
    destination_address_{dst},
    netmask_{netmask}
{}

void InterfaceAddress::set_address(ip_addr_t addr) {
    address_ = addr;
}

IpAddress* InterfaceAddress::get_address() const {
    return address_.get();
}

void InterfaceAddress::set_broadcast_address(ip_addr_t bcast) {
    broadcast_address_ = bcast;
}

IpAddress* InterfaceAddress::get_broadcast_address() const {
    return broadcast_address_.get();
}

void InterfaceAddress::set_destination_address(ip_addr_t dst) {
    destination_address_ = dst;
}

IpAddress* InterfaceAddress::get_destination_address() const {
    return destination_address_.get();
}

void InterfaceAddress::set_netmask(ip_addr_t netmask) {
    netmask_ = netmask;
}

IpAddress* InterfaceAddress::get_netmask() const {
    return netmask_.get();
}

SerializedObject InterfaceAddress::serialize(
        const SerializationMgr& serializer) const {
    auto obj = serializer.create_object();

    if (address_) {
        serializer.set_value<const char*>(obj, "addr", address_->data());
    }

    if (broadcast_address_) {
        serializer.set_value<const char*>(obj, "bcast_addr",
                broadcast_address_->data());
    }

    if (destination_address_) {
        serializer.set_value<const char*>(obj, "dst_addr",
                destination_address_->data());
    }

    if (netmask_) {
        serializer.set_value<const char*>(obj, "netmask", netmask_->data());
    }

    return obj;
}

std::string InterfaceAddress::get_entity_name() const {
    return address_ ? address_->data() : "none";
}

InterfaceAddress::~InterfaceAddress() {}

