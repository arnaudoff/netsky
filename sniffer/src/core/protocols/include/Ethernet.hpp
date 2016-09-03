#ifndef ETHERNET_HPP_
#define ETHERNET_HPP_

#include <sys/types.h>
#include <string>
#include <iomanip>
#include <sstream>
#include "../../sniffers/include/SniffedPacket.hpp"

namespace Sniffer {
    namespace Core {
        namespace Protocols {
            class Ethernet {
                private:
                    static const int ADDRESS_LENGTH = 6;

                    typedef struct {
                        u_char destination_address[ADDRESS_LENGTH];
                        u_char source_address[ADDRESS_LENGTH];
                        u_short ether_type;
                    } ether_header_t;

                    const ether_header_t* header_;
                public:
                    Ethernet(Sniffers::SniffedPacket* sniffed_packet)
                        : header_{(ether_header_t*)(sniffed_packet->get_data())}
                    {}

                    static const int FRAME_SIZE = 14;

                    // TODO: Extract to cpp file and remove redundancy

                    std::string get_destination_address() const {
                        std::ostringstream os;
                        for (int i = 0; i < ADDRESS_LENGTH; i++) {
                            os << std::setw(2) << std::setfill('0') << 
                                std::hex << (int)(header_->destination_address[i]);
                            if (i < ADDRESS_LENGTH - 1) {
                                os << ":";
                            }
                        }

                        return os.str();
                    }

                    std::string get_source_address() const {
                        std::ostringstream os;
                        for (int i = 0; i < ADDRESS_LENGTH; i++) {
                            os << std::setw(2) << std::setfill('0') <<
                                std::hex << (int)(header_->destination_address[i]);
                            if (i < ADDRESS_LENGTH - 1) {
                                os << ":";
                            }
                        }

                        return os.str();
                    }

                    u_short get_ether_type() const {
                        return header_->ether_type;
                    }

                    ~Ethernet() {};
            };
        }
    }
}

#endif
