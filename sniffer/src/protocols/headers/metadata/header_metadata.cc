#include "include/HeaderMetadata.hpp"

using namespace Sniffer::Protocols::Headers::Metadata;

HeaderMetadata::HeaderMetadata(
        int id,
        std::string name,
        int length,
        bool has_variable_length,
        int length_field_offset)
    : id_{id},
    name_{name},
    length_{length},
    has_variable_length_{has_variable_length},
    length_field_offset_{length_field_offset}
{}

int HeaderMetadata::id() const {
    return id_;
}

std::string HeaderMetadata::name() const {
    return name_;
}

int HeaderMetadata::length() const {
    return length_;
}

bool HeaderMetadata::has_variable_length() const {
    return has_variable_length_;
}

int HeaderMetadata::length_field_offset() const {
    return length_field_offset_;
}

int HeaderMetadata::calculate_length(const u_char* length_field) const {
    return length_;
}
