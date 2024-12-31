#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "client.h"
#include "request_data.h"

int client_init_socket(uint16_t port)
{
    // 0 -> Internet Protocol
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        // Failed to create socket
        return -1;
    }

    struct sockaddr_in client_addr = {
        .sin_family = AF_INET,
        .sin_addr = htonl(INADDR_ANY),
        .sin_port = htons(port)

    };

    if (bind(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
    {
        // Failed to bind socket
        return -1;
    }

    return sock;
}

int client_build_header_request(request_header header, char *req_ret)
{
    // Signature
    strcpy(req_ret, "C99REQ");

    // I can't be bothered to do this better :/
    switch (header.type)
    {
    case REQ_ADD:
        req_ret[6] = 'A';
        req_ret[7] = 'D';
        req_ret[8] = 'D';
        break;

    case REQ_MSG:
        req_ret[6] = 'M';
        req_ret[7] = 'S';
        req_ret[8] = 'G';
        break;
    default:
        // Invalid request type
        return -1;
        break;
    }

    // Convert payload size to 4 separate bytes
    req_ret[9] = (header.payload_size >> 24) & 0xFF;
    req_ret[10] = (header.payload_size >> 16) & 0xFF;
    req_ret[11] = (header.payload_size >> 8) & 0xFF;
    req_ret[12] = header.payload_size & 0xFF;

    req_ret[13] = '\0';

    return 0;
}

int client_send_header_request(
    int sock,
    struct sockaddr_in server_addr,
    char *header_req)
{
    uint32_t addr_size = sizeof(server_addr);
    if (sendto(sock, header_req, 13, 0, (struct sockaddr *)&server_addr, addr_size) < 0)
    {
        return -1;
    }
    return 0;
}