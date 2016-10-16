#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "../../core/include/PolicyBindings.hpp"
#include "../../core/include/PacketSniffer.hpp"
#include "ConnectionData.hpp"

namespace Sniffer {
    namespace Communications {
        class Server {
            using PacketSniffer = Sniffer::Core::PacketSniffer;

            protected:
                std::unique_ptr<PacketSniffer> sniffer_;
                ConfigurationMgr config_manager_;
                int session_id_;

            public:
                Server(const ConfigurationMgr& manager);

                void set_sniffer(std::unique_ptr<PacketSniffer> sniffer);

                PacketSniffer* get_sniffer() const;

                ConfigurationMgr get_config_manager() const;

                virtual void start(uint16_t port) = 0;

                virtual void stop() = 0;

                virtual void unicast(
                        const ConnectionData& connection, const std::string& msg);

                virtual void broadcast(const std::string& message) = 0;

                virtual ~Server() {};
        };
    }
}

#endif
