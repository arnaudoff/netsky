set(PROTO_SOURCES Ethernet.cpp IPv4.cpp TCP.cpp)

add_library(sniffer-proto ${PROTO_SOURCES})

file(GLOB_RECURSE PROTO_HEADERS "*.hpp")

install(TARGETS sniffer-proto DESTINATION bin)
install(FILES ${PROTO_HEADERS} DESTINATION include)
