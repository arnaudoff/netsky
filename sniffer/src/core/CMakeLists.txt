project(netsky-core VERSION 0.1 LANGUAGES CXX)

add_library(netsky-core
  src/layers/layer.cc
  src/layers/data_link_layer.cc
  src/layers/network_layer.cc
  src/layers/transport_layer.cc
  src/layers/application_layer.cc
  src/response_models/retrieve_interfaces_response_model.cc
  src/response_models/has_host_response_model.cc
  src/response_models/authenticate_response_model.cc
  src/server_commands/kill_command.cc
  src/server_commands/has_host_command.cc
  src/server_commands/authenticate_command.cc
  src/server_commands/retrieve_interfaces_command.cc
  src/server_commands/server_command.cc
  src/server_commands/start_sniffer_command.cc
  src/interface.cc
  src/interface_address.cc
  src/layer_stack.cc
  src/packet_sniffer.cc
  src/pcap_interface_retriever.cc
  src/pcap_packet_sniffer.cc
  src/hex_ascii_payload_interpreter.cc
  src/reception_handler.cc
  src/server.cc
  src/server_command_invoker.cc
  src/websocket_server.cc
  src/websocket_server_event_handler.cc
  src/websocket_server_event.cc
  )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.

target_include_directories(netsky-core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>
  $<BUILD_INTERFACE:${CPPREGPATTERN_INCLUDE_DIR}>
  $<BUILD_INTERFACE:${WEBSOCKETPP_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)

# If we have compiler requirements for this library, list them
# here

target_compile_features(netsky-core
  PUBLIC cxx_auto_type
  PUBLIC cxx_decltype_auto
  PRIVATE cxx_variadic_templates)

# The header registry works when all of the headers to be constructed are linked
# directly to the executable. Since they are in an external library, the
# linker must be forced to load all of the symbols in that library.

if (APPLE)
  set(NETSKY_PROTOCOLS_LIB -Wl,-force_load netsky-protocols)
else()
  set(NETSKY_PROTOCOLS_LIB
      -Wl,--whole-archive netsky-protocols -Wl,--no-whole-archive)
endif()

# Depend on a library that we defined in the top-level file

target_link_libraries(netsky-core netsky-common ${NETSKY_PROTOCOLS_LIB}
  boost-system websocketpp spdlog pcap ${CMAKE_THREAD_LIBS_INIT}
  ${OPENSSL_LIBRARIES})

# 'make install' to the correct location

install(TARGETS netsky-core EXPORT NetskyCoreConfig
  ARCHIVE  DESTINATION lib
  LIBRARY  DESTINATION lib
  RUNTIME  DESTINATION bin)  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into <prefix>/cmake.

install(EXPORT NetskyCoreConfig DESTINATION share/NetskyCore/cmake)

# This makes the project importable from the build directory

#export(TARGETS netsky-core FILE NetskyCoreConfig.cmake)

# Add the unit tests

add_executable(testcore test/core_tests.cc)

target_link_libraries(testcore netsky-core)

add_test(testcore testcore)
