#include "include/ConnectionData.hpp"

using namespace Sniffer::Communications;

ConnectionData::ConnectionData()
    : ConnectionData{0}
{}

ConnectionData::ConnectionData(int session_id)
    : session_id_{session_id}
{}

int ConnectionData::get_session_id() const {
    return session_id_;
}

bool ConnectionData::operator==(const ConnectionData& other) const {
    return session_id_ == other.session_id_;
}

bool ConnectionData::operator!=(const ConnectionData& other) const {
    return !(*this == other);
}

