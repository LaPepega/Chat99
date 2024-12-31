#pragma once
#include <stdint.h>

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
 * @brief Chat99 request data. All request bytes
 * can be derived from this
 */
typedef struct request_data
{
    /** Number of bytes after the
     * header to consider payload */
    int32_t payload_size;
    /// Type of the request
    request_type type;
    /// Pointer to the start of the payload
    char *payload;
} request_data;