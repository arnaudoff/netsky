#ifndef PACKET_SNIFFER_HPP_
#define PACKET_SNIFFER_HPP_

#include <memory>
#include <vector>
#include <string>

#include "PolicyBindings.hpp"
#include "LayerStack.hpp"

namespace Sniffer {
    namespace Communications {
        class Server;
    }
}

namespace Sniffer {
    namespace Core {
        class PacketSniffer {
            protected:
                using Server = Sniffer::Communications::Server;

                Server* server_;

                std::vector<std::string> interfaces_;

                std::vector<std::string> filters_;

                std::vector<std::string> shared_;

                ConfigurationMgr config_manager_;

                LayerStack stack_;

                virtual void prepare_interface() = 0;

                virtual void parse_filters() = 0;

                virtual void apply_filters() = 0;

                virtual void sniff() = 0;

            public:
                PacketSniffer(
                        Server* server,
                        std::vector<std::string> interfaces,
                        std::vector<std::string> filters,
                        std::vector<std::string> shared,
                        const ConfigurationMgr& config,
                        const LayerStack& stack);

                void start();

                virtual ~PacketSniffer() {};
        };
    }
}

#endif
