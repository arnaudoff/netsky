#include <iterator>

#include "include/Layer.hpp"

using namespace Sniffer::Core;
using namespace Sniffer::Core::Layers;
using namespace Sniffer::Protocols::Headers;
using namespace Sniffer::Protocols::Headers::Metadata;

using HeaderMetadataCollection = std::vector<std::unique_ptr<HeaderMetadata>>;

using SupportedHeadersIterator =
    boost::indirect_iterator<
        HeaderMetadataCollection::iterator,
        const HeaderMetadata>;

Layer::Layer(const SerializationMgr& serializer, const HeaderFactory& hfactory)
    : lower_layer_{NULL},
    upper_layer_{NULL},
    reception_handler_{this, serializer, hfactory}
{};

Layer* Layer::get_lower_layer() const {
    return lower_layer_;
}

void Layer::set_lower_layer(Layer* layer) {
    lower_layer_ = layer;
}

Layer* Layer::get_upper_layer() const {
    return upper_layer_;
}

void Layer::set_upper_layer(Layer* layer) {
    upper_layer_ = layer;
}

SupportedHeadersIterator Layer::begin() {
    return std::begin(supported_headers_);
}

SupportedHeadersIterator Layer::end() {
    return std::end(supported_headers_);
}

// wtf?
void Layer::set_supported_headers(
        std::vector<std::unique_ptr<HeaderMetadata>>&& headers) {
    supported_headers_ = std::move(headers);
}
