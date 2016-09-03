cmake_minimum_required(VERSION 3.6.1)

project(sniffer VERSION 0.1.0)

set(Sniffer_VERSION_MAJOR 0)
set(Sniffer_VERSION_MINOR 1)

# Set C++11 compiler flags

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(SOURCE_CODE_DIR src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Configure a header file to pass some of the CMake settings
# to the source code

configure_file("${PROJECT_SOURCE_DIR}/${SOURCE_CODE_DIR}/SnifferConfig.h.in"
               "${PROJECT_BINARY_DIR}/SnifferConfig.h")

# Add the binary tree to the search path for include files
# so that SnifferConfig.h is found

include_directories("${PROJECT_BINARY_DIR}")

# Add header-only libraries to the binary tree

include_directories(vendor/include)

# Deal with the core library of the sniffer

file(GLOB_RECURSE Core_HEADERS "${SOURCE_CODE_DIR}/core/*.hpp")

# Automatically adds all directories that have a header file in them as
# include directories

set (Core_INCLUDE_DIRS "")
foreach (_headerFile ${Core_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Core_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Core_INCLUDE_DIRS)

include_directories(${Core_INCLUDE_DIRS})

add_subdirectory("${SOURCE_CODE_DIR}/core")
add_subdirectory("${SOURCE_CODE_DIR}/utils")

add_executable (sniffer ${SOURCE_CODE_DIR}/Startup.cpp)
target_link_libraries(sniffer sniffer-core sniffer-utils)
