#ifndef PACKET_SNIFFER_HPP_
#define PACKET_SNIFFER_HPP_

#include <memory>

#include "PolicyBindings.hpp"
#include "ObservablePacketSniffer.hpp"

namespace Sniffer {
    namespace Core {
        class PacketSniffer : public ObservablePacketSniffer {
            protected:
                std::shared_ptr<ConfigManager> config_manager_;

                virtual void prepare_interface() = 0;

                virtual void apply_filters() = 0;

                virtual void sniff() = 0;

            public:
                PacketSniffer(std::shared_ptr<ConfigManager> manager);

                void start();

                virtual ~PacketSniffer() {};
        };
    }
}

#endif
