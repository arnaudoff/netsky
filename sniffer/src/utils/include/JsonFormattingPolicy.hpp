#ifndef JSON_FORMATTING_POLICY_HPP_
#define JSON_FORMATTING_POLICY_HPP_

#include <memory>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Sniffer {
    namespace Utils {
        template<class T>
        class JsonFormattingPolicy {
            public:
                template<typename U>
                U get_value(
                        const T& config,
                        const std::string& object,
                        const std::string& key) {
                    auto json_obj = json::parse(config.get_contents());
                    return json_obj[object][key].template get<U>();
                }

                template<typename U>
                T set_value(
                        const T& config,
                        const std::string& object,
                        const std::string& key,
                        U value) {
                    auto json_obj = json::parse(config.get_contents());
                    json_obj[object][key] = value;

                    T config_obj { json_obj.dump() };
                    return config_obj;
                }

                std::string get_format_extension() {
                    return "json";
                }
        };
    }
}

#endif
