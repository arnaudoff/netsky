# This file fetches dependencies as git submodules and builds them as targets.

# spdlog

# find_path(SPDLOG_INCLUDE_DIR ...)

if((NOT SPDLOG_INCLUDE_DIR) OR (NOT EXISTS ${SPDLOG_INCLUDE_DIR}))
  # We couldn't find the header files for SPDLOG or they don't exist

  message("Unable to find spdlog, cloning...")

  # Clone the submodule under vendor/spdlog

  execute_process(COMMAND git submodule update --init -- vendor/spdlog
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

  set(SPDLOG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include/
    CACHE PATH "spdlog include directory")
endif()

install(DIRECTORY ${SPDLOG_INCLUDE_DIR}/spdlog DESTINATION include)

# Setup a target

add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE
  $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>)

# Export the target

install(TARGETS spdlog EXPORT spdlog DESTINATION include)

# websocketpp

# find_path(WEBSOCKETPP_INCLUDE_DIR ...)

if((NOT WEBSOCKETPP_INCLUDE_DIR) OR (NOT EXISTS ${WEBSOCKETPP_INCLUDE_DIR}))
  # We couldn't find the header files for WEBSOCKETPP or they don't exist

  message("Unable to find websocketpp, cloning...")

  # Clone the submodule under vendor/websocketpp

  execute_process(COMMAND git submodule update --init -- vendor/websocketpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

  set(WEBSOCKETPP_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/websocketpp/websocketpp/
    CACHE PATH "websocketpp include directory")
endif()

install(DIRECTORY ${WEBSOCKETPP_INCLUDE_DIR}/websocketpp DESTINATION include)

# Setup a target

add_library(websocketpp INTERFACE)
target_include_directories(websocketpp INTERFACE
  $<BUILD_INTERFACE:${WEBSOCKETPP_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>)

# Export the target

install(TARGETS websocketpp EXPORT websocketpp DESTINATION include)

# nlohmann/json

# find_path(NLOHMANN_JSON_INCLUDE_DIR ...)

if((NOT NLOHMANN_JSON_INCLUDE_DIR) OR (NOT EXISTS ${NLOHMANN_JSON_INCLUDE_DIR}))
  # We couldn't find the header file for nlohmann/json or it doesn't exist

  message("Unable to find nlohmann/json, cloning...")

  # Clone the submodule under vendor/nlohmann_json

  execute_process(COMMAND git submodule update --init -- vendor/nlohmann_json
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

  set(NLOHMANN_JSON_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/nlohmann_json/src/
    CACHE PATH "nlohmann/json include directory")
endif()

install(FILES ${NLOHMANN_JSON_INCLUDE_DIR}/json.hpp DESTINATION include)

# Setup a target

add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE
  $<BUILD_INTERFACE:${NLOHMANN_JSON_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>)

# Export the target

install(TARGETS nlohmann_json EXPORT nlohmann_json DESTINATION include)
