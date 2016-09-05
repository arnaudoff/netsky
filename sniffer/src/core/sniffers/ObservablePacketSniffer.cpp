#include <algorithm>

#include "include/ObservablePacketSniffer.hpp"

using namespace Sniffer::Core::Sniffers;

void ObservablePacketSniffer::attach(PacketSnifferObserver* observer) {
    observers_.push_back(observer);
}

void ObservablePacketSniffer::detach(PacketSnifferObserver* observer) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

void ObservablePacketSniffer::notify(SniffedEntity* entity) {
    for (const auto& observer : observers_) {
        observer->update(entity);
    }
}
