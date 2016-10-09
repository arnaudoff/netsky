#ifndef SERIALIZED_OBJECT_HPP_
#define SERIALIZED_OBJECT_HPP_

#include <string>

namespace Sniffer {
    namespace Communications {
        namespace Serialization {
            class SerializedObject {
                private:
                    std::string data_;

                public:
                    SerializedObject(const std::string& data)
                        : data_{data}
                    {}

                    std::string get_data() const {
                        return data_;
                    }

                    void set_data(const std::string& data) {
                        data_ = data;
                    }
            };

        }
    }
}

#endif
