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
- Display filtering through JSQL (searchjs) expressions
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
- web server for serving the client (optional)

Other dependencies will be fetched from git as submodules and from NPM.

## Building and running

```shell

# Clone the repository

$ git clone https://github.com/arnaudoff/netsky
```

### Building and running the sniffer/server

**Note**: Before running and building anything, make sure to change the
path to the SSL certificates to use accordingly. This is done
in `netsky/sniffer/config/config.json`.

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


# Copy a production-ready build to dist/prod (optional)
$ npm run build.prod
```

### Other configuration

Other configuration such as the port that the sniffing server should listen on
is located in `sniffer/config/config.json`. Note that if you're using the
provided client, you should also change the address/port in the respective
environment configuration.

### Building the documentation (optional)

The sniffer project has a detailed documentation for most of the classes and
methods via Doxygen. It can be generated from the Doxyfile provided.

### Serving the client with a web server (optional)

Serving the client is no harder than serving any Angular application. Still,
`nginx.sample.conf` provides a simple configuration for nginx. Configuration for
other web servers is similar.

## A note on SSL/TLS

- Since the sniffer has built-in SSL/TLS support (and using SSL/TLS is practically a requirement),
you may need to allow development certificates (for localhost) in your browser to trust the
sample self-signed certificates that are provided when testing as well as if
you're trying out the application in production.
- Secure WebSocket may sometimes fail if it's not run under https or the
certificate is invalid.

