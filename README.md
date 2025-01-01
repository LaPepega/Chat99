![Does it work yet? Nope](https://img.shields.io/badge/Does_it_work_yet%3F-NO-red)
![Build Status](https://img.shields.io/github/actions/workflow/status/LaPepega/Chat99/build-linux.yml)
![Lines of code](https://tokei.rs/b1/github/LaPepega/Chat99)

# Chat99

The simplest possible P2P cli chat made with UDP sockets in C99 with no external libraries.

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

Then you can find build result in `/path/to/chat99/build/src` (Main Chat99 binary, `libclient.a`, `libserver.a`)

Tested with `clang-18.1.8` and `gcc-14.1.1`

### On windows

Good fucking luck bro :)

(I might look into it later but I fucking hate windows so I might as well not)

## Structure

Chat99 Consists of 2 parts:

- A Server which runs on a separate thread and processes all incoming connections.
- A client which sends outgoing requests and messages.

The client and server code is compiled into shared libraries, which are then used by the main binary. The final binary acts as *both* the client and the server, it's just easier to separate functions of the two in code.

## Communications

All data transferred over UDP is formatted to be as easy to parse as possible so any messages, usernames, etc. can only contain ASCII characters.

***There is no encryption whatsoever.*** All the exchanges between clients and servers are raw bytes which can be interpreted as ASCII for human readability.

So every communication happens in this order:

```plaintext
client -> header request
server -> response
Assuming SUC:
client -> payload request
server -> response
```

### Requests

First 6 bytes of any request are a signature. Requests can be either headers (signed `C99REQ`) or payloads (signed `C99PLD`)

All `REQ` requests specify a request type in the next 3 bytes after the signature. Currently implemented request types are:

- `ADD` - For adding the user to active chats
- `MSG` - For sending a message to a user

Every header request must be followed by a payload request. Next 4 bytes after the request type are a `uint32` payload length. `PLD` Requests carry said payload, which can be anything, these requests are interpreted differently depending on the preceding header request type.

#### Examples:

These are ASCII representations of raw bytes sent through UDP. Some of the bytes can't be adequately represented with ASCII. Here the symbol `\` followed by a number represents the hex equivalent of this number (`\18` would be `11` in hex)

- `C99REQADD\0\0\0\0` followed by `C99PLD` requests to add the receiving user to active chat.
- `C99REQMSG\0\0\0\11` followed by `C99PLDhello world` sends the message "hello world" to the receiving user.

### Responses

Responses are signed in a similar way to requests - `C99RES`. Response codes are stored the same way as request types and are 3 bytes long too. Currently implemented response codes are:

- `SUC` - Request received and processed successfully, the client may proceed to send the `PLD`.
- `ERR` - An error occurred while processing the request, the server will not be expecting to receive a `PLD`.

So with this knowledge here's an example of a full, successful interaction between the client and the server:

```plaintext
client -> C99REQMSG\0\0\0\11
server -> C99RESSUC
client -> C99REQPLDhello world
server -> C99RESSUC
```

After this exchange user acting as the server will receive a message "hello world".

## Contributing

Any contributions are highly appreciated.

When contributing please create your own branch (or a fork) named `dev/{username}` or `feature/{feature name}` (you get the idea) and pull request. <3