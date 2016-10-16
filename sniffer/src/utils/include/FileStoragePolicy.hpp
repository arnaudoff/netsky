#ifndef FILE_STORAGE_POLICY_HPP_
#define FILE_STORAGE_POLICY_HPP_

#include <sstream>
#include <fstream>
#include <memory>
#include <string>

namespace Sniffer {
    namespace Utils {
        template<class T>
        class FileStoragePolicy {
            public:
                T read(const std::string& resource) {
                    std::ifstream t(resource);
                    std::stringstream buffer;

                    buffer << t.rdbuf();
                    T config { buffer.str() };
                    return config;
                }

                void write(const T& config, const std::string& resource) {
                    std::ofstream out(resource);
                    out << config.get_contents();
                    out.close();
                }
        };
    }
}

#endif
