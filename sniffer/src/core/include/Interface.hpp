#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <sys/socket.h>
#include <vector>
#include <string>

namespace Sniffer {
    namespace Core {
        class Interface {
            std::string name_;
            std::string description_;
            std::vector<std::string> addresses_;
            std::vector<std::string> netmasks_;

            public:
                Interface(std::string name,
                        std::string desc,
                        std::vector<std::string> addr,
                        std::vector<std::string> netmasks)
                    : name_{name},
                    description_{desc},
                    addresses_{addr},
                    netmasks_{netmasks}

                std::string get_name() const {
                    return name_;
                }

                std::string get_description() const {
                    return description_;
                }

                std::vector<std::string> get_addresses() const {
                    return addresses_;
                }

                std::vector<std::string> get_netmasks() const {
                    return netmasks_;
                }

        }
    }
}

#endif
