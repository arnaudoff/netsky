#include "include/InternetHeaderMetadata.hpp"

using namespace Sniffer::Protocols::Headers::Metadata;

InternetHeaderMetadata::InternetHeaderMetadata(
        int id,
        std::string name,
        int size,
        bool has_variable_length,
        int length_field_offset)
    : HeaderMetadata(id, name, size, has_variable_length, length_field_offset)
{}

int InternetHeaderMetadata::calculate_length(const u_char* length_field) const {
    int version_internet_header_length = *length_field;
    return version_internet_header_length & 0x0f;
}
