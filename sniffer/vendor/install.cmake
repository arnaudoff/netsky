# This file fetches dependencies as git submodules and builds them as targets.

# Fetch and configure websocketpp

message("Cloning the websocketpp submodule...")

execute_process(COMMAND git submodule update --init -- vendor/websocketpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(WEBSOCKETPP_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/websocketpp/websocketpp
    CACHE PATH "websocketpp include directory")

## Create and configure the library target

add_library(websocketpp INTERFACE)
target_include_directories(websocketpp INTERFACE
    $<BUILD_INTERFACE:${WEBSOCKETPP_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${INCLUDE_DESTINATION_PATH}>)

install(DIRECTORY ${WEBSOCKETPP_INCLUDE_DIR}/websocketpp
    DESTINATION ${INCLUDE_DESTINATION_PATH})

## Export the target

install(TARGETS websocketpp
    EXPORT sniffer
    DESTINATION ${INCLUDE_DESTINATION_PATH})

# Fetch and configure nlohmann/json

message("Cloning the nlohmann/json submodule...")

execute_process(COMMAND git submodule update --init -- vendor/json
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json/src
    CACHE PATH "nlohmann/json include directory")

set(JSON_INCLUDE_DESTINATION "${INCLUDE_DESTINATION_PATH}/nlohmann")

## Create and configure the library target

add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE
    $<BUILD_INTERFACE:${JSON_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${JSON_INCLUDE_DESTINATION}>)

install(FILES ${JSON_INCLUDE_DIR}/json.hpp DESTINATION
    ${JSON_INCLUDE_DESTINATION})

## Export the target

install(TARGETS nlohmann_json
    EXPORT sniffer
    DESTINATION ${INCLUDE_DESTINATION_PATH})

# Fetch and configure spdlog

message("Cloning the spdlog submodule...")

execute_process(COMMAND git submodule update --init -- vendor/spdlog
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SPDLOG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    CACHE PATH "spdlog include directory")

## Create and configure the library larget

add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE
    $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${INCLUDE_DESTINATION_PATH}>)

install(DIRECTORY ${SPDLOG_INCLUDE_DIR}/spdlog
    DESTINATION ${INCLUDE_DESTINATION_PATH})

## Export the target

install(TARGETS spdlog EXPORT sniffer DESTINATION ${INCLUDE_DESTINATION_PATH})

