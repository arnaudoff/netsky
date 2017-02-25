cmake_minimum_required(VERSION 3.6.1 FATAL_ERROR)

project(sniffer VERSION 0.1.0 LANGUAGES CXX)

find_package(Boost REQUIRED system)
find_package(OpenSSL)

add_library(boost INTERFACE IMPORTED)
set_property(
  TARGET boost
  PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})

add_library(boost-system SHARED IMPORTED)
set_property(
  TARGET boost-system
  PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
set_property(
  TARGET boost-system
  PROPERTY IMPORTED_LOCATION ${Boost_SYSTEM_LIBRARY})

find_package(Threads)

# External 3rd party libs that we include

include(vendor/install.cmake)

# Sniffer-related targets

enable_testing()
add_subdirectory(common)
add_subdirectory(protocols)
add_subdirectory(core)
add_subdirectory(app)
