set(HEADERS_FOLDER headers)
set(PROTO_SOURCES ${HEADERS_FOLDER}/HeaderFactory.cpp
    ${HEADERS_FOLDER}/Header.cpp
    ${HEADERS_FOLDER}/EthernetHeader.cpp
    ${HEADERS_FOLDER}/InternetHeader.cpp
    ${HEADERS_FOLDER}/TransmissionControlHeader.cpp)

set(METADATA_FOLDER ${HEADERS_FOLDER}/metadata)
set(PROTO_METADATA_SOURCES ${METADATA_FOLDER}/HeaderMetadata.cpp
    ${METADATA_FOLDER}/EthernetHeaderMetadata.cpp
    ${METADATA_FOLDER}/InternetHeaderMetadata.cpp
    ${METADATA_FOLDER}/TransmissionControlHeaderMetadata.cpp)

add_library(sniffer-proto ${PROTO_SOURCES} ${PROTO_METADATA_SOURCES})

file(GLOB_RECURSE PROTO_HEADERS "*.hpp")

install(TARGETS sniffer-proto DESTINATION bin)
install(FILES ${PROTO_HEADERS} DESTINATION include)
