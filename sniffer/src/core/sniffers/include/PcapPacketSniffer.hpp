#ifndef PCAP_SNIFFER_HPP_
#define PCAP_SNIFFER_HPP_

#include <pcap/pcap.h>

#include "PacketSniffer.hpp"

namespace Sniffer {
    namespace Core {
        namespace Sniffers {
            class PcapPacketSniffer : public PacketSniffer {
                private:
                    pcap_t* handle_;
                    bpf_u_int32 subnet_mask_;
                    bpf_u_int32 network_;
                    struct bpf_program compiled_filter_expression_;

                    virtual void prepare_interface() override;

                    virtual void apply_filters() override;

                    virtual void sniff() override;

                    static void on_packet_received(u_char* args, const struct pcap_pkthdr* header, const u_char* packet);

                    void on_packet_received_internal(const struct pcap_pkthdr* header, const u_char* packet);

                public:
                    PcapPacketSniffer(std::shared_ptr<ConfigManager> manager);

                    ~PcapPacketSniffer() override;
            };
        }
    }
}

#endif
