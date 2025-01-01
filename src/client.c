#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "client.h"
#include "communications.h"

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
    strcpy(req_ret, SIGNATURE_REQUEST);

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

    return 0;
}

int client_send_header_request(
    int sock,
    struct sockaddr_in server_addr,
    request_header hdr)
{
    uint32_t addr_size = sizeof(server_addr);
    char header_req[LEN_HEADER];

    if (client_build_header_request(hdr, header_req) < 0)
    {
        // Failed to build header request
        return -1;
    }

    if (sendto(sock, header_req, LEN_HEADER, 0, (struct sockaddr *)&server_addr, addr_size) < 0)
    {
        // Failed to send header request
        return -1;
    }
    return 0;
}

int client_receive_response(int sock, struct sockaddr_in expected_addr)
{
    char resp[LEN_RESPONSE];
    struct sockaddr_in received_addr;
    uint32_t addr_size = sizeof(received_addr);

    if (recvfrom(sock, resp, LEN_RESPONSE, 0, (struct sockaddr *)&received_addr, &addr_size) < 0)
    {
        // Receive error
        return -1;
    }

    char signature[6];
    strncat(signature, resp, 6);

    char rettype_s[3] = {resp[6], resp[7], resp[8]};
    if (strcmp(rettype_s, RES_ERR_S) == 0)
    {
        return RES_ERR;
    }
    else if (strcmp(rettype_s, RES_SUC_S))
    {
        return RES_SUC;
    }
    else
    {
        // Invalid response code
        return -1;
    }
}