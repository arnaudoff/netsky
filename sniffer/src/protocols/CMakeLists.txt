project(libnetsky-protocols VERSION 0.1 LANGUAGES CXX)

add_library(libnetsky-protocols
  src/headers/header.cc
  src/headers/header_factory.cc
  src/headers/ethernet_header.cc
  src/headers/internet_header.cc
  src/headers/transmission_control_header.cc
  )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.

target_include_directories(libnetsky-protocols PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)

# If we have compiler requirements for this library, list them
# here

target_compile_features(libnetsky-protocols
  PUBLIC cxx_auto_type
  PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file

target_link_libraries(libnetsky-protocols common boost)

# 'make install' to the correct location

install(TARGETS libnetsky-protocols EXPORT LibNetskyProtocolsConfig
  ARCHIVE  DESTINATION lib
  LIBRARY  DESTINATION lib
  RUNTIME  DESTINATION bin)  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into <prefix>/cmake.

install(EXPORT LibNetskyProtocolsConfig DESTINATION share/LibNetskyProtocols/cmake)

# This makes the project importable from the build directory

export(TARGETS libnetsky-protocols FILE LibNetskyProtocolsConfig.cmake)

# Add the unit tests

add_executable(testprotocols test/protocols_tests.cc)

target_link_libraries(testprotocols libnetsky-protocols)

add_test(testprotocols testprotocols)
