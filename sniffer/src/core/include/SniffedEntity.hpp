#ifndef SNIFFED_ENTITY_HPP_
#define SNIFFED_ENTITY_HPP_

#include <sys/types.h>

namespace Sniffer {
    namespace Core {
        class SniffedEntity {
            private:
                const u_char* data_;

            public:
                SniffedEntity(const u_char* data)
                    : data_{data} {}

                SniffedEntity() {};

                const u_char* get_data() const {
                    return data_;
                }
        };
    }
}

#endif
