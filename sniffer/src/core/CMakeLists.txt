set(CORE_SOURCES ServerPacketSnifferObserver.cpp SniffedPacketJsonSerializer.cpp)

set(SNIFFERS_DIR sniffers)
set(SNIFFERS_SOURCES ${SNIFFERS_DIR}/PacketSniffer.cpp
    ${SNIFFERS_DIR}/PcapPacketSniffer.cpp ${SNIFFERS_DIR}/ObservablePacketSniffer.cpp)

set(COMMS_DIR communications)
set(COMMS_SOURCES ${COMMS_DIR}/CommandParser.cpp
    ${COMMS_DIR}/ServerCommandInvoker.cpp ${COMMS_DIR}/WebSocketServer.cpp
    ${COMMS_DIR}/WebSocketServerActionHandler.cpp)

set(COMMANDS_DIR communications/commands)
set(COMMANDS_SOURCES ${COMMANDS_DIR}/KillServerCommand.cpp)

find_package(Threads)
find_package(Boost COMPONENTS system REQUIRED)

add_library(sniffer-core ${CORE_SOURCES} ${SNIFFERS_SOURCES} ${COMMS_SOURCES}
    ${COMMANDS_SOURCES})
target_link_libraries(sniffer-core pcap ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_SYSTEM_LIBRARY})

file(GLOB_RECURSE Core_HEADERS "*.hpp")

install(TARGETS sniffer-core DESTINATION bin)
install(FILES ${CORE_HEADERS} DESTINATION include)
