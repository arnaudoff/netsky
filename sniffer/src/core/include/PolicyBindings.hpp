#ifndef POLICY_BINDINGS_HPP_
#define POLICY_BINDINGS_HPP_

#include "../../utils/include/ConfigurationManager.hpp"
#include "../../utils/include/FileStoragePolicy.hpp"
#include "../../utils/include/JsonFormattingPolicy.hpp"

#include "../../core/communications/serialization/include/SerializationManager.hpp"
#include "../../core/communications/serialization/include/JsonSerializationPolicy.hpp"

typedef Sniffer::Utils::ConfigurationManager<
    Sniffer::Utils::FileStoragePolicy,
    Sniffer::Utils::JsonFormattingPolicy> ConfigManager;

typedef Sniffer::Core::Communications::Serialization::SerializationManager<
    Sniffer::Core::Communications::Serialization::JsonSerializationPolicy>
    SerializationMgr;

#endif
