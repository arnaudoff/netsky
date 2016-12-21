set(CORE_ADDRESSING_SOURCES addressing/Ipv4Address.cpp
    addressing/Ipv6Address.cpp addressing/IpAddressFactory.cpp)

set(CORE_SOURCES LayerStack.cpp Interface.cpp InterfaceAddress.cpp
    PacketSniffer.cpp PcapInterfaceRetriever.cpp PcapPacketSniffer.cpp
    ReceptionHandler.cpp SniffedPacket.cpp)

set(LAYER_SOURCES layers/Layer.cpp layers/DataLinkLayer.cpp
    layers/NetworkLayer.cpp layers/TransportLayer.cpp
    layers/ApplicationLayer.cpp)

add_library(sniffer-core ${CORE_SOURCES} ${LAYER_SOURCES} ${CORE_ADDRESSING_SOURCES})
target_link_libraries(sniffer-core pcap)

file(GLOB_RECURSE Core_HEADERS "*.hpp")

install(TARGETS sniffer-core DESTINATION bin)
install(FILES ${CORE_HEADERS} DESTINATION include)
