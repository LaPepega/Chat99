#pragma once
#include <stdint.h>

/**
 *
 * @brief Types of requests the server can receive
 *
 * - REQ_ADD - Request to add the server to active chats
 *
 * - REQ_MSG - Request carrying a message
 */
typedef enum request_type
{
    REQ_ADD,
    REQ_MSG,
} request_type;

/**
 * @brief Chat99 request data
 *
 */
typedef struct request_data
{
    int32_t payload_size;
    request_type type;
    char *payload;
} request_data;