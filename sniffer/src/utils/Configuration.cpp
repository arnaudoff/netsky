#include "include/Configuration.hpp"

using namespace Sniffer::Utils;

Configuration::Configuration(const std::string& raw_contents)
    : raw_contents_{raw_contents}
{}

std::string Configuration::get_contents() const {
    return raw_contents_;
}
