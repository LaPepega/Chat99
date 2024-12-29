#pragma once
#include <stdint.h>

#include "request_data.h"

/**
 * @brief Creates and binds a new active socket for
 * making requests to servers
 *
 * @param port port to bind socket to
 * @return int socket descriptor
 */
int client_init_socket(uint16_t port);

/**
 * @brief Make a request with desired data
 *
 * @param req_data data to build a request from
 * @param req_ret the request will be written here.
 * Must be 14 bytes or longer (13 byte header + `\0`)
 * @return int 0 for Success, -1 for errors
 */
int client_build_request(request_data req_data, char *req_ret);
