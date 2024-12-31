#pragma once
#include <stdint.h>

/*
So the communication model is something like this:

client --  request header   -> server
client <-      SUC/ERR      -- server
Assuming SUC:
client --  request payload  -> server
client <-      SUC/ERR      -- server

I have to send the header and the payload separately so
that i already have the payload size when i recvfrom()
*/

/** All UDP messages Chat99 sends start with
 * one of the following 6 byte signatures*/

/** Client->Server request header */
#define SIGNATURE_REQUEST "C99REQ"
/** TODO: Client->Server payload, sent with request */
#define SIGNATURE_PAYLOAD "C99PLD"
/** Server->Client response*/
#define SIGNATURE_RESPONSE "C99RES"

/**
 * @brief Types of requests the server can receive
 */
typedef enum request_type
{
    /** Request type to add another user to active chats */
    REQ_ADD,
    /** Request type to send a message */
    REQ_MSG,
} request_type;

/**
 * @brief Types of requests the server can receive
 */
typedef enum response_type
{
    /** Error response */
    RES_ERR,
    /** Success response */
    RES_SUC,
} response_type;

/**
 * @brief Chat99 request data. All request bytes
 * can be derived from this
 */
typedef struct request_header
{
    /** Number of bytes after the
     * header to consider payload */
    int32_t payload_size;
    /** Type of the request */
    request_type type;
} request_header;