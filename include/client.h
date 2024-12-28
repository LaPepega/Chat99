#pragma once
#include <stdint.h>

/**
 * @brief Creates and binds a new active socket for making requests to servers
 *
 * @param port port to bind socket to
 * @return int socket descriptor
 */
int client_init_socket(uint16_t port);