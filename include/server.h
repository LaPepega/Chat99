#pragma once
#include "request_data.h"

/**
 * @brief Creates and binds a new passive socket for comunicating with clients
 *
 * @param port port number to bind the socket to
 * @return int socket descriptor or -1 for errors
 */
int server_init_socket(uint16_t port);

/**
 * @brief Listen to an incoming request
 *
 * @param sock socket descriptor to listen to,
 * `payload_size = -1` for errors
 *
 * @return request parsed request
 */
request_data server_receive(int sock);
