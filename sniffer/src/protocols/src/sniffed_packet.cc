/*
 * Copyright (C) 2016  Ivaylo Arnaudov <ivaylo.arnaudov12@gmail.com>
 * Author: Ivaylo Arnaudov <ivaylo.arnaudov12@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "protocols/sniffed_packet.h"

#include <iostream>

#include "protocols/packet_region.h"

namespace sniffer {

namespace protocols {

/**
 * @brief Constructs a SniffedPacket object.
 *
 * @param data A pointer to the beginning of an array of bytes.
 * @param body Designates where the body of the packet begins.
 */
SniffedPacket::SniffedPacket(const u_char* data, PacketRegion body)
    : data_{data}, payload_length_{0}, valid_{true} {
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
const u_char* SniffedPacket::ExtractHeader(int header_length) {
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
const u_char* SniffedPacket::ExtractTrailer(int trailer_length) {
  // Reduce the length of the body to account for the trailer "frame"
  body_.length -= trailer_length;

  // Form a "frame" for the trailer
  trailer_.offset = body_.offset + body_.length;
  trailer_.length = trailer_length;

  return &(data_[trailer_.offset]);
}

/**
 * @brief Returns the beginning of the body region.
 *
 * @return Pointer to the beginning of the body region.
 */
const u_char* SniffedPacket::Body() {
  return &(data_[body_.offset]);
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
const u_char* SniffedPacket::Peek(int byte_offset) {
  return &(data_[body_.offset + byte_offset]);
}

PacketRegion SniffedPacket::header_region() const {
  return header_;
}

PacketRegion SniffedPacket::body_region() const {
  return body_;
}

PacketRegion SniffedPacket::trailer_region() const {
  return trailer_;
}

void SniffedPacket::IncrementPayloadLength(int length) {
  payload_length_ += length;
}

void SniffedPacket::DecrementPayloadLength(int length) {
  payload_length_ -= length;
}

int SniffedPacket::payload_length() const {
  return payload_length_;
}

bool SniffedPacket::valid() const {
  return valid_;
}

void SniffedPacket::set_valid(bool valid) {
  valid_ = valid;
}

}  // namespace protocols

}  // namespace sniffer
