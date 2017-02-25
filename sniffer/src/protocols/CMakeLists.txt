project(netsky-protocols VERSION 0.1 LANGUAGES CXX)

add_library(netsky-protocols
  src/headers/header.cc
  src/headers/ethernet_header.cc
  src/headers/internet_header.cc
  src/headers/transmission_control_header.cc
  src/headers/user_datagram_header.cc
  src/headers/metadata/header_metadata.cc
  src/headers/metadata/ethernet_header_metadata.cc
  src/headers/metadata/internet_header_metadata.cc
  src/headers/metadata/transmission_control_header_metadata.cc
  src/headers/metadata/user_datagram_header_metadata.cc
  src/packet_region.cc
  src/sniffed_packet.cc
  )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.

target_include_directories(netsky-protocols PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CPPREGPATTERN_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)

# If we have compiler requirements for this library, list them
# here

target_compile_features(netsky-protocols
  PUBLIC cxx_auto_type
  PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file

target_link_libraries(netsky-protocols netsky-common boost)

# 'make install' to the correct location

install(TARGETS netsky-protocols EXPORT NetskyProtocolsConfig
  ARCHIVE  DESTINATION lib
  LIBRARY  DESTINATION lib
  RUNTIME  DESTINATION bin)  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into <prefix>/cmake.

install(EXPORT NetskyProtocolsConfig DESTINATION share/NetskyProtocols/cmake)

# This makes the project importable from the build directory

# export(TARGETS netsky-protocols FILE NetskyProtocolsConfig.cmake)
