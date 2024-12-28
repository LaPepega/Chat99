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
 * @brief Creates and binds a new passive socket for comunicating with clients
 *
 * @param port port number to bind the socket to
 * @return int socket descriptor or -1 for errors
 */
int server_init_socket(uint16_t port);