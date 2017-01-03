project(netsky-common VERSION 0.1 LANGUAGES CXX)

add_library(netsky-common
  src/addressing/ip_address_factory.cc
  src/addressing/ipv4_address.cc
  src/addressing/ipv6_address.cc
  src/config/configuration.cc
)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.

target_include_directories(netsky-common PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${NLOHMANN_JSON_INCLUDE_DIR}/src>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

# If we have compiler requirements for this library, list them
# here

target_compile_features(netsky-common
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates)

# Depend on a library that we defined in the top-level file

# target_link_libraries(netsky-common)

# 'make install' to the correct location

install(TARGETS netsky-common EXPORT NetskyCommonConfig
    ARCHIVE  DESTINATION lib
    LIBRARY  DESTINATION lib
    RUNTIME  DESTINATION bin)  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into <prefix>/cmake.

install(EXPORT NetskyCommonConfig DESTINATION share/NetskyCommon/cmake)

# This makes the project importable from the build directory

# export(TARGETS netsky-common FILE NetskyCommonConfig.cmake)

# Add the unit tests

add_executable(testcommon test/common_tests.cc)

target_link_libraries(testcommon netsky-common)

add_test(testcommon testcommon)
