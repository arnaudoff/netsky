#ifndef RECEPTION_HANDLER_HPP_
#define RECEPTION_HANDLER_HPP_

namespace Sniffer {
    namespace Core {
        class ReceptionHandler {
            private:
                Layer* layer_;

            public:
                void handle(SniffedPacket* packet);
        };
    }
}

#endif
