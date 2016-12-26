add_executable(sniffer src/startup.cc)

target_link_libraries(sniffer common protocols core)
