#ifndef SNIFFED_PACKET_HPP_
#define SNIFFED_PACKET_HPP_

namespace Sniffer {
    namespace Core {
        class SniffedPacket {
            private:
                static constexpr int MAXIMUM_PACKET_LENGTH = 1500; // MTU

                typedef struct {
                    int offset;
                    int length;
                } chunk_t;

                chunk_t header_;
                chunk_t body_;
                chunk_t trailer_;

                char buffer[MAXIMUM_PACKET_LENGTH];

            public:
                SniffedPacket(chunk_t body);

                void extract_header(int header_length);

                char* get_header();

                void extract_trailer(int trailer_length);

                char* get_trailer();
        };
    }
}

#endif
