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
 * Must be `14 + payload_size` bytes long
 * @return int 0 for Success, -1 for errors
 */
int client_build_header_request(request_header req_data, char *req_ret);

/**
 * @brief Sends a header request to the server
 *
 * @param sock socket descriptor to send from
 * @param server_addr address of the server
 * @param header_req header request, see `client_build_header_request()`
 * @return int 0 for success -1 for errors
 */
int client_send_header_request(
    int sock,
    struct sockaddr_in server_addr,
    char *header_req);