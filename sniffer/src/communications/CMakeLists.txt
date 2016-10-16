set(COMMS_SOURCES ConnectionData.cpp Server.cpp ServerCommandInvoker.cpp
    WebSocketServer.cpp WebSocketServerActionHandler.cpp)

set(COMMANDS_DIR commands)
set(COMMANDS_SOURCES ${COMMANDS_DIR}/StartPacketSnifferCommand.cpp
    ${COMMANDS_DIR}/RetrieveInterfacesCommand.cpp ${COMMANDS_DIR}/KillServerCommand.cpp)

set(RESPONSE_MODELS_DIR response_models)
set(RESPONSE_MODELS_SOURCES
    ${RESPONSE_MODELS_DIR}/RetrieveInterfacesResponseModel.cpp)

find_package(Threads)
find_package(Boost COMPONENTS system REQUIRED)

add_library(sniffer-comms ${COMMS_SOURCES} ${COMMANDS_SOURCES}
    ${RESPONSE_MODELS_SOURCES})
target_link_libraries(sniffer-comms ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_SYSTEM_LIBRARY})

file(GLOB_RECURSE COMMS_HEADERS "*.hpp")

install(TARGETS sniffer-comms DESTINATION bin)
install(FILES ${COMMS_HEADERS} DESTINATION include)
