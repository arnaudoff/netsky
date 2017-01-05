add_executable(sniffer src/startup.cc)

if (APPLE)
  set(NETSKY_PROTOCOLS_LIB -Wl,-force_load netsky-protocols)
else()
  set(NETSKY_PROTOCOLS_LIB
      -Wl,--whole-archive netsky-protocols -Wl,--no-whole-archive)
endif()

target_link_libraries(sniffer netsky-core ${NETSKY_PROTOCOLS_LIB})
