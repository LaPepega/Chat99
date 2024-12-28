![Does it work yet? Nope](https://img.shields.io/badge/Does_it_work_yet%3F-NO-red)
![Build Status](https://img.shields.io/github/actions/workflow/status/LaPepega/Chat99/build-linux.yml)

# Chat99

The simplest possible P2P cli chat made with TCP sockets in C99 with no external libraries.

> **Warning!**
>
> This is a practice project (at least for now), not intended for actual use.
>
> This shit is insecure and unstable *as fuck*, so be aware.

## Getting Started

`TODO` :)

## Building

### On linux

No external libraries, so no requirements. Just build with CMake `>=3.30` and C99 compiler of your choice like so:

```bash
$ cd /path/to/chat99
$ cmake -S . -B build
$ cmake --build build --config Release --target all
```

Then you can find build result in `/path/to/chat99/build/src` (Main Chat99 binary, `libclient.so`, `libserver.so`)

Tested with `clang-18.1.8` and `gcc-14.1.1`

### On windows

Good fucking luck bro :)

(I might look into it later but I fucking hate windows so I might as well not)

## Structure

Chat99 Consists of 2 parts:

- A Server which runs on a separate thread and processes all incoming connections.
- A client which sends outgoing requests and messages.

The client and server code is compiled into shared libraries, which are then used by the main binary. The final binary acts as *both* the client and the server, it's just easier to separate functions of the two in code.

## Requests

Well more like connections but I don't care. All data transferred over TCP connections is formatted to be as easy to parse as possible so any messages, usernames, etc. can only contain ASCII characters.

**Any non-ASCII messages are undefined behavior because I said so, fuck you.**

Anyway, every request contains these parts:

1. Request header which consists of:
    1. Chat99 signature [6 bytes] : `43 39 39 52 45 51` ( ASCII `C99REQ` )
    2. [Request type](#request-types) [3 bytes]
    3. Payload length [4 bytes]
2. Payload of specified length which is interpreted according to the request's [type](#request-types).

### Request types

What is being requested? 3 byte flag which can be thought of as it's ASCII representation, always one of the following:

- ADD (`41 44 44`) - Start a new chat with the user, *add* them to peer list. Have no payload. Any unwanted payload will be ignored.
- MSG (`4D 53 47`) - Send a message to the user. Payload is the ASCII message for the user.

## Contributing

Any contributions are highly appreciated, although this is meant to be my personal study on sockets.

When contributing please create your own branch (or a fork) named `dev/{username}` or `feature/{feature name}` (you get the idea) and pull request.
