cmake_minimum_required(VERSION 3.6.1)

project(sniffer VERSION 0.1.0)

set(Sniffer_VERSION_MAJOR 0)
set(Sniffer_VERSION_MINOR 1)

# Set C++14 compiler flags

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(SOURCE_CODE_DIR src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(INCLUDE_DESTINATION_PATH "include")

# Configure a header file to pass some of the CMake settings
# to the source code

configure_file("${PROJECT_SOURCE_DIR}/${SOURCE_CODE_DIR}/SnifferConfig.hpp.in"
               "${PROJECT_BINARY_DIR}/SnifferConfig.hpp")

# Add the binary tree to the search path for include files
# so that SnifferConfig.hpp is found

include_directories("${PROJECT_BINARY_DIR}")

# Load the installation script for the third party libraries

include(vendor/install.cmake)

# Deal with the core library of the sniffer

file(GLOB_RECURSE Source_HEADERS "${SOURCE_CODE_DIR}/*.hpp")

# Automatically adds all directories that have a header file in them as
# include directories

set (Source_INCLUDE_DIRS "")
foreach (_headerFile ${Source_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Source_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Source_INCLUDE_DIRS)

include_directories(${Source_INCLUDE_DIRS})

add_subdirectory("${SOURCE_CODE_DIR}/communications")
add_subdirectory("${SOURCE_CODE_DIR}/core")
add_subdirectory("${SOURCE_CODE_DIR}/protocols")
add_subdirectory("${SOURCE_CODE_DIR}/utils")

add_executable (sniffer ${SOURCE_CODE_DIR}/Startup.cpp)
target_link_libraries(sniffer PUBLIC websocketpp nlohmann_json spdlog
    sniffer-comms sniffer-core sniffer-proto
    sniffer-utils)
