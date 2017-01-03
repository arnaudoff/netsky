add_executable(sniffer src/startup.cc)

target_link_libraries(sniffer netsky-common netsky-protocols netsky-core)
