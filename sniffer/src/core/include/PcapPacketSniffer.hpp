#ifndef PCAP_SNIFFER_HPP_
#define PCAP_SNIFFER_HPP_

#include <pcap/pcap.h>

#include "PacketSniffer.hpp"

namespace Sniffer {
    namespace Core {
        class PcapPacketSniffer : public PacketSniffer {
            private:
                pcap_t* handle_;

                bpf_u_int32 subnet_mask_;

                bpf_u_int32 network_;

                struct bpf_program parsed_filters_;

                virtual void prepare_interface() override;

                virtual void parse_filters() override;

                virtual void apply_filters() override;

                virtual void sniff() override;

                static void on_packet_received(
                        u_char* args,
                        const struct pcap_pkthdr* header,
                        const u_char* packet);

                void on_packet_received_internal(
                        const struct pcap_pkthdr* header,
                        const u_char* packet);

            public:
                PcapPacketSniffer(
                        Server* server,
                        std::vector<std::string> interfaces,
                        std::vector<std::string> filters,
                        std::vector<std::string> shared,
                        const ConfigurationMgr& config,
                        const PacketParser& parser);

                ~PcapPacketSniffer() override;
        };
    }
}

#endif
