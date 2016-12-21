#include "include/SniffedPacket.hpp"

using namespace Sniffer::Core;

/**
 * @brief Constructs a SniffedPacket object.
 *
 * @param data A pointer to the beginning of an array of bytes.
 * @param body Designates where the body of the packet begins.
 */
SniffedPacket::SniffedPacket(
        const u_char* data,
        PacketRegion body)
    : data_{data} {
    body_.offset = body.offset;
    body_.length = body.length;

    // Since we literally haven't formed any header or trailer yet.
    header_.length = 0;
    trailer_.length = 0;
}

/**
 * @brief Extracts a header from the internal byte array.
 *
 * @param header_length The length of the header to extract.
 *
 * @return An observing raw pointer to the beginning of the header.
 */
const u_char* SniffedPacket::extract_header(int header_length) {
    // Form a "frame" for the header
    header_.offset = body_.offset;
    header_.length = header_length;

    // Reduce the length of the body to account for the formed "frame"
    body_.offset += header_length;
    body_.length -= header_length;

    return &(data_[header_.offset]);
}

/**
 * @brief Extracts a trailer from the internal byte array.
 *
 * @param trailer_length The length of the trailer to extract.
 *
 * @return An observing raw pointer to the beginning of the trailer.
 */
const u_char* SniffedPacket::extract_trailer(int trailer_length) {
    // Reduce the length of the body to account for the trailer "frame"
    body_.length -= trailer_length;

    // Form a "frame" for the trailer
    trailer_.offset = body_.offset + body_.length;
    trailer_.length = trailer_length;

    return &(data_[trailer_.offset]);
}

/**
 * @brief Peeks byte_offset into the body, without extracting
 * a header of particular size. This function is primary used for
 * headers with variable length.
 *
 * @param byte_offset How many bytes into the current body to peek.
 *
 * @return A pointer to the bytes after the byte_offset.
 */
const u_char* SniffedPacket::peek(int byte_offset) {
    return &(data_[header_.offset + byte_offset]);
}
