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
 * @brief Listen to an incoming request header,
 * read it's data into `req_ret`and client's address
 * into `client_addr_ret`
 * @param sock socket descriptor to listen to,
 * @param req_ret pointer to a `request_header` object
 * to which the data will be stored.
 * @param client_addr_ret pointer to store client's address to
 * @return int 0 for success -1 for errors
 */
int server_receive_header(
    int sock,
    request_header *req_ret,
    struct sockaddr_in *client_addr_ret

);

/**
 * @brief Receives a request payload and stores it to `payload`
 *
 * @param sock socket descriptor to listen to
 * @param payload_size number of bytes to receive
 * @param payload_ret pointer to store the payload to
 * @param client_addr address to expect the payload from
 * @return int 0 for success -1 if addresses don't match
 */
int server_receive_payload(
    int sock,
    struct sockaddr_in expected_addr,
    size_t payload_size,
    char *payload_ret);
