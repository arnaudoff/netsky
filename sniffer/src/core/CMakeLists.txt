set(CORE_SOURCES PacketParser.cpp PacketSniffer.cpp PcapInterfaceRetriever PcapPacketSniffer.cpp)

add_library(sniffer-core ${CORE_SOURCES})
target_link_libraries(sniffer-core pcap)

file(GLOB_RECURSE Core_HEADERS "*.hpp")

install(TARGETS sniffer-core DESTINATION bin)
install(FILES ${CORE_HEADERS} DESTINATION include)
