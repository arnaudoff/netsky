#ifndef POLICY_BINDINGS_HPP_
#define POLICY_BINDINGS_HPP_

#include "../../utils/include/ConfigurationManager.hpp"
#include "../../utils/include/FileStoragePolicy.hpp"
#include "../../utils/include/JsonFormattingPolicy.hpp"

typedef Sniffer::Utils::ConfigurationManager<
    Sniffer::Utils::FileStoragePolicy,
    Sniffer::Utils::JsonFormattingPolicy> ConfigManager;

#endif
