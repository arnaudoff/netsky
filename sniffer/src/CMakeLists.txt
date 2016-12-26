cmake_minimum_required(VERSION 3.6.1 FATAL_ERROR)

project(sniffer VERSION 0.1.0 LANGUAGES CXX)

# Include boost

find_package(Boost REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

# External 3rd party libs that we include

include(vendor/install.cmake)

# add_subdirectory(vendor/spdlog EXCLUDE_FROM_ALL)
# add_subdirectory(vendor/json EXCLUDE_FROM_ALL)
# add_subdirectory(vendor/websocketpp EXCLUDE_FROM_ALL)

# Sniffer-related targets

enable_testing()
add_subdirectory(common)
add_subdirectory(protocols)
add_subdirectory(core)

