#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"
#include "communications.h"

int server_init_socket(uint16_t port)
{
    // 0 -> Internet Protocol
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        // Failed to create socket
        return -1;
    }

    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_addr = htonl(INADDR_ANY),
        .sin_port = htons(port)

    };

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        // Failed to bind socket
        return -1;
    }

    return sock;
}

int server_receive_header(
    int sock,
    request_header *req_ret,
    struct sockaddr_in *client_addr_ret)
{
    char header[LEN_HEADER];
    uint32_t client_addr_size = sizeof(*client_addr_ret);

    if (recvfrom(sock, &header, LEN_HEADER, 0, (struct sockaddr *)client_addr_ret, &client_addr_size) < 0)
    {
        // receiving error
        return -1;
    }

    char signature[7];
    strncpy(signature, header, 6);
    signature[6] = '\0';

    if (strcmp(signature, SIGNATURE_REQUEST) != 0)
    {
        // Invalid signature;
        return -1;
    }

    // The easiest way to get a string slice here :/
    char req_type[4] = {header[6], header[7], header[8], '\0'};

    if (strcmp(req_type, REQ_ADD_S) == 0)
    {
        req_ret->type = REQ_ADD;
    }
    else if (strcmp(req_type, REQ_MSG_S) == 0)
    {
        req_ret->type = REQ_MSG;
    }
    else
    {
        // Invalid type
        return -1;
    }

    // Reading payload size stored in 4 bytes to int32_t
    // Oh boy, I sure hope this won't cause any endianness issues!
    char payload_size_b[4] = {header[12], header[11], header[10], header[9]};
    uint32_t payload_size = *(uint32_t *)payload_size_b;

    req_ret->payload_size = payload_size;

    return 0;
}

int server_receive_payload(
    int sock,
    struct sockaddr_in expected_addr,
    size_t payload_size,
    char *payload_ret)
{
    struct sockaddr_in received_addr;
    uint32_t addr_size = sizeof(received_addr);

    if (recvfrom(sock, payload_ret, payload_size, 0, (struct sockaddr *)&received_addr, &addr_size) < 0)
    {
        // receiving error
        return -1;
    }

    if (received_addr.sin_family != expected_addr.sin_family || received_addr.sin_addr.s_addr != expected_addr.sin_addr.s_addr)
    {
        return -1;
    }

    return 0;
}

int server_build_response(response_code t, char *res_ret)
{
    strcpy(res_ret, SIGNATURE_RESPONSE);

    switch (t)
    {
    case RES_ERR:
        res_ret[6] = 'E';
        res_ret[7] = 'R';
        res_ret[8] = 'R';
        break;

    case RES_SUC:
        res_ret[6] = 'S';
        res_ret[7] = 'U';
        res_ret[8] = 'C';
        break;

    default:
        // Invalid response code
        return -1;
        break;
    }
    return 0;
}

int server_respond(
    int sock,
    struct sockaddr_in client_addr,
    response_code res)
{
    uint32_t addr_size = sizeof(client_addr);
    char response[LEN_RESPONSE];

    if (server_build_response(res, response) < 0)
    {
        return -1;
        // failed to build response
    }

    if (sendto(sock, response, LEN_RESPONSE, 0, (struct sockaddr *)&client_addr, addr_size) < 0)
    {
        // sending error
        return -1;
    }

    return 0;
}
