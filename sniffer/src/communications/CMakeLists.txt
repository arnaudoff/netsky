set(COMMS_SOURCES CommandParser.cpp ServerCommandInvoker.cpp WebSocketServer.cpp
    WebSocketServerActionHandler.cpp)

set(COMMANDS_SOURCES commands/KillServerCommand.cpp)
set(SERIALIZATION_SOURCES serialization/SerializedObject.cpp)

find_package(Threads)
find_package(Boost COMPONENTS system REQUIRED)

add_library(sniffer-comms ${COMMS_SOURCES} ${COMMANDS_SOURCES}
    ${SERIALIZATION_SOURCES})
target_link_libraries(sniffer-comms ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_SYSTEM_LIBRARY})

file(GLOB_RECURSE COMMS_HEADERS "*.hpp")

install(TARGETS sniffer-comms DESTINATION bin)
install(FILES ${COMMS_HEADERS} DESTINATION include)
