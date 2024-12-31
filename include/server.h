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
 * @brief Listen to an incoming request and read it's data into `req_ret`.
 * @param sock socket descriptor to listen to,
 * @param req_ret pointer to a `request_data` object
 * to which the data will be stored.
 * @return int 0 for success -1 for errors
 */
int server_receive(int sock, request_data *req_ret);
