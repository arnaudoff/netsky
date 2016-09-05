#include "include/SerializedObject.hpp"

using namespace Sniffer::Core::Communications::Serialization;

SerializedObject::SerializedObject(const std::string& data)
    : data_{data}
{}

std::string SerializedObject::get_data() const {
    return data_;
}

void SerializedObject::set_data(const std::string& data) {
    data_ = data;
}
