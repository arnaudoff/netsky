#include "include/Header.hpp"

using namespace Sniffer::Protocols::Headers;

Header::Header(int length)
    : length_{length}
{}

int Header::get_length() const {
    return length_;
}

Header::~Header() {}
