#include "include/TransmissionControlHeaderMetadata.hpp"

using namespace Sniffer::Protocols::Headers::Metadata;

TransmissionControlHeaderMetadata::TransmissionControlHeaderMetadata(
        int id,
        std::string name,
        int length,
        bool has_variable_length,
        int length_field_offset)
    : HeaderMetadata(id, name, length, has_variable_length, length_field_offset)
{}

int TransmissionControlHeaderMetadata::calculate_length(
        const u_char* length_field) const {
    int offset = *length_field;
    return ((offset & 0xf0) >> 4) * 4;
}
