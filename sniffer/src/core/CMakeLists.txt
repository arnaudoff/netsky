project(libnetsky-core VERSION 0.1 LANGUAGES CXX)

add_library(libnetsky-core
  src/layers/layer.cc
  src/layers/data_link_layer.cc
  src/layers/network_layer.cc
  src/layers/transport_layer.cc
  src/layers/application_layer.cc
  src/response_models/retrieve_interfaces_response_model.cc
  src/server_commands/kill_server_command.cc
  src/server_commands/retrieve_interfaces_command.cc
  src/server_commands/server_command.cc
  src/server_commands/start_packet_sniffer_command.cc
  src/connection_data.cc
  src/interface.cc
  src/interface_address.cc
  src/layer_stack.cc
  src/packet_sniffer.cc
  src/pcap_interface_retriever.cc
  src/pcap_packet_sniffer.cc
  src/reception_handler.cc
  src/server.cc
  src/server_command_invoker.cc
  src/sniffed_packet.cc
  src/websocket_server.cc
  src/websocket_server_action_handler.cc
  )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.

target_include_directories(libnetsky-core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)

# If we have compiler requirements for this library, list them
# here

target_compile_features(libnetsky-core
  PUBLIC cxx_auto_type
  PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file

target_link_libraries(libnetsky-core libnetsky-common libnetsky-protocols
  boost websocketpp spdlog)

# 'make install' to the correct location

install(TARGETS libnetsky-core EXPORT LibNetskyCoreConfig
  ARCHIVE  DESTINATION lib
  LIBRARY  DESTINATION lib
  RUNTIME  DESTINATION bin)  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into <prefix>/cmake.

install(EXPORT LibNetskyCoreConfig DESTINATION share/LibNetskyCore/cmake)

# This makes the project importable from the build directory

export(TARGETS libnetsky-core FILE LibNetskyCoreConfig.cmake)

# Add the unit tests

add_executable(testcore test/core_tests.cc)

target_link_libraries(testcore libnetsky-core)

add_test(testcore testcore)
