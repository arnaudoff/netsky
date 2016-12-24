#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <string>

namespace Sniffer {
    namespace Utils {
        class Configuration {
            private:
                std::string raw_contents_;

            public:
                Configuration(const std::string& resource);

                std::string get_contents() const;
        };
    }
}

#endif
