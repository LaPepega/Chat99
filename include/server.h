#pragma once
#include <stdint.h>

/**
 * @brief Creates and binds a new passive socket for comunicating with clients
 *
 * @param port port number to bind the socket to
 * @return int socket descriptor or -1 for errors
 */
int server_init_socket(uint16_t port);
