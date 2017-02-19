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

- git
- Compiler with C++11 support
- CMake >= 3.6.1
- libpcap-dev
- libssl-dev
- libboost-system-dev
- nodejs >= 6.5.0
- npm >= 3.10.3

Other dependencies will be fetched from git as submodules and from NPM.

## Building and running

```shell
# Clone the repository

$ git clone https://github.com/arnaudoff/netsky
```

### Building and running the sniffer/server

```shell
$ cd netsky/sniffer/
$ mkdir build
$ cd build && cmake -DCMAKE_BUILD_TYPE=Release ../src
$ make

# Run the sniffer
$ cd app
$ sudo ./sniffer
```

### Building and running the client

```shell
$ cd netsky/client/

# Fetch client dependencies to node_modules/
$ npm install

# Run the client in development env
$ npm start

# Copy a production-ready build to dist/prod
$ npm run build.prod
```

### Serving the client with a webserver (optional)
