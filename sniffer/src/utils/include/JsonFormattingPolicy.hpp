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
                            const std::shared_ptr<const T> config,
                            const std::string& object,
                            const std::string& key) {
                        auto json_obj = json::parse(config->get_contents());
                        return json_obj[object][key].template get<U>();
                    }

                template<typename U>
                    std::shared_ptr<T> set_value(
                            const std::shared_ptr<const T> config,
                            const std::string& object,
                            const std::string& key,
                            U value) {
                        auto json_obj = json::parse(config->get_contents());
                        json_obj[object][key] = value;

                        std::shared_ptr<T> ptr { new T { json_obj.dump() } };
                        return ptr;
                    }
        };
    }
}

#endif
