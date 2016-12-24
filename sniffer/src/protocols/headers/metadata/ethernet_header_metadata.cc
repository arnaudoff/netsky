#include "include/EthernetHeaderMetadata.hpp"

using namespace Sniffer::Protocols::Headers::Metadata;

EthernetHeaderMetadata::EthernetHeaderMetadata(
        int id,
        std::string name,
        int size,
        bool variable_length,
        int length_field_offset)
    : HeaderMetadata(id, name, size, variable_length, length_field_offset)
{}
