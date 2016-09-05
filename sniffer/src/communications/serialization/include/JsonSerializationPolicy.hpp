#ifndef JSON_SERIALIZATION_POLICY_HPP_
#define JSON_SERIALIZATION_POLICY_HPP_

#include <memory>
#include <nlohmann/json.hpp>

namespace Sniffer {
    namespace Communications {
        namespace Serialization {
            template<class T>
            class JsonSerializationPolicy {
                public:
                    T create() const {
                        json empty_obj = json::object();

                        T obj { empty_obj.dump() };

                        return obj;
                    }

                    template<typename U>
                    void set_value(T& object, const std::string& key,
                            U value) const {
                        auto json_obj = json::parse(object.get_data());

                        json_obj[key] = value;

                        object.set_data(json_obj.dump());
                    }

                    void set_object(T& parent_obj, const std::string& key,
                            const T& obj) const {
                        auto json_parent_obj = json::parse(parent_obj.get_data());
                        auto json_obj = json::parse(obj.get_data());
                        json_parent_obj[key] = json_obj;

                        parent_obj.set_data(json_parent_obj.dump());
                    }
            };

        }
    }
}

#endif
