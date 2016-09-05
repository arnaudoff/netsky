#ifndef POLICY_BINDINGS_HPP_
#define POLICY_BINDINGS_HPP_

#include "../../utils/include/ConfigurationManager.hpp"
#include "../../utils/include/FileStoragePolicy.hpp"
#include "../../utils/include/JsonFormattingPolicy.hpp"

#include "../../communications/serialization/include/SerializationManager.hpp"
#include "../../communications/serialization/include/JsonSerializationPolicy.hpp"

typedef Sniffer::Utils::ConfigurationManager<
    Sniffer::Utils::FileStoragePolicy,
    Sniffer::Utils::JsonFormattingPolicy> ConfigManager;

typedef Sniffer::Communications::Serialization::SerializationManager<
    Sniffer::Communications::Serialization::JsonSerializationPolicy>
    SerializationMgr;

#endif
