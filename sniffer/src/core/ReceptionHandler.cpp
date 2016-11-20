#include "include/ReceptionHandler.hpp"

using namespace Sniffer::Core;

ReceptionHandler::ReceptionHandler() {};

void handle(SniffedPacket* packet) {
    // pass header length depending on the data link protocol header len
    char* header = packet->extract_header();

    Layer* upper_layer = layer_->get_upper_layer();
    if (upper_layer) {
        upper_layer->handle_reception(packet);
    }
}
