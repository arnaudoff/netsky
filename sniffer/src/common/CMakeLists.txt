set(UTILS_SOURCES Configuration.cpp)

add_library(sniffer-utils ${UTILS_SOURCES})

file(GLOB_RECURSE Utils_HEADERS "*.hpp")

install(TARGETS sniffer-utils DESTINATION bin)
install(FILES ${Utils_HEADERS} DESTINATION include)
