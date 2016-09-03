#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "../../../core/include/PolicyBindings.hpp"

namespace Sniffer {
    namespace Core {
        namespace Communications {
            class Server {
                private:
                    std::shared_ptr<ConfigManager> config_manager_;

                public:
                    Server(std::shared_ptr<ConfigManager> manager)
                        : config_manager_{manager}
                    {};

                    virtual void start(uint16_t port) = 0;

                    virtual void stop() = 0;

                    virtual void broadcast(const std::string& message) = 0;

                    virtual ~Server() {};
            };
        }
    }
}

#endif
