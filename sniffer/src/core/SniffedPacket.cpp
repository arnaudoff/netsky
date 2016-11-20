#include "include/SniffedPacket.hpp"

using namespace Sniffer::Core;

SniffedPacket::SniffedPacket(chunk_t body) {
    header_.length = 0;
    trailer_.length = 0;
    body_ = body;
}

void SniffedPacket::extract_header(int header_length) {
    // Build the header
    header_.offset = body_.offset;
    header_.length = header_length;

    // Reduce the length of the body to account for the header
    body_.offset += header_length;
    body_.length -= header_length;
}

char* SniffedPacket::get_header() {
    return &buffer[header_.offset];
}

void SniffedPacket::extract_trailer(int trailer_length) {
    // Reduce the length of the body to account for the trailer
    body_.length -= trailer_length;

    // Build the trailer itself
    trailer_.offset = body_.offset + body_.length;
    trailer_.length = trailer_length;
}

char* SniffedPacket::get_trailer() {
    return &buffer[trailer_.offset];
}
