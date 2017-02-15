# Netsky

An open-source, remote-accessible packet sniffer, written in C++ and Angular 2.

## Supported protocols

- 802.3 Ethernet
- Internet Protocol (RFC 891)
- Transmission Control Protocol (RFC 793)
- User Datagram Protocol (RFC 768)
- Generic payload

## Core features

- Remote sniffing with authentication
- Shared sniffing (multiple clients are supported)
- SSL/TLS support
- Session-based filtering with pcap filters
- Display filtering through Jexl expressions
- Hierarchical frame structure visualisation
- Designed with extensibility in mind

## Prerequisites

- Compiler with C++11 support
- CMake >= 3.6.1
- git
- libssl-dev
- libboost-system-dev

## Building and running

```shell
# Clone the repository

$ git clone https://github.com/arnaudoff/netsky

# Build the sniffer

$ cd sniffer/
$ mkdir build
$ cd build && cmake -DCMAKE_BUILD_TYPE=Release ../src
$ make
```
