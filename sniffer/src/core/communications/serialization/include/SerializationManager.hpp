#ifndef SERIALIZATION_MANAGER_HPP_
#define SERIALIZATION_MANAGER_HPP_

#include <memory>
#include "SerializedObject.hpp"

namespace Sniffer {
    namespace Core {
        namespace Communications {
            namespace Serialization {
                template<template <class> class SerializationPolicy>
                class SerializationManager :
                    public SerializationPolicy<SerializedObject> {
                    public:
                        SerializedObject create_object() const {
                            return SerializationPolicy<SerializedObject>::create();
                        }

                        template<typename U>
                        void set_value(SerializedObject& object, const std::string& key,
                                U value) const {
                            return SerializationPolicy<SerializedObject>::template
                                set_value<U>(object, key, value);
                        }

                        void set_object(SerializedObject& p_obj, const std::string& key,
                                const SerializedObject& obj) const {
                            return SerializationPolicy<SerializedObject>::
                                set_object(p_obj, key, obj);
                        }

                };
            }
        }
    }
}

#endif
