#include "include/Layer.hpp"

using namespace Sniffer::Core::Layers;

Layer::Layer()
    : lower_layer_{NULL}, upper_layer_{NULL}
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
