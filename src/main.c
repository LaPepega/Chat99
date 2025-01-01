#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#include "server.h"
#include "client.h"

#define SERVER_PORT 9901
#define CLIENT_PORT 9902

int main(int argc, char const *argv[])
{
    if (argc > 1 && strcmp(argv[1], "-c") == 0)
    {
        struct sockaddr_in server_addr = {
            .sin_family = AF_INET,
            .sin_addr = htonl(INADDR_LOOPBACK),
            .sin_port = htons(SERVER_PORT)};

        int client_socket = client_init_socket(CLIENT_PORT);
        if (client_socket < 0)
        {
            perror("Failed to init client socket");
            exit(EXIT_FAILURE);
        }

        request_header hdr = {.payload_size = 5, .type = REQ_MSG};
        if (client_send_header_request(client_socket, server_addr, hdr) < 0)
        {
            perror("Failed to send request");
            exit(EXIT_FAILURE);
        }

        switch (client_receive_response(client_socket, server_addr))
        {
        case RES_ERR:
            printf("Header error!");
            exit(EXIT_FAILURE);
            break;

        case RES_SUC:
            printf("Header success!");
            break;

        default:
            printf("Invalid header response");
            exit(EXIT_FAILURE);
            break;
        }

        return 0;
    }

    int server_socket = server_init_socket(SERVER_PORT);
    if (server_socket < 0)
    {
        perror("Failed to init server socket");
        exit(EXIT_FAILURE);
    }

    char resp[9];

    struct sockaddr_in client_addr;
    request_header test_req;
    if (server_receive_header(server_socket, &test_req, &client_addr) < 0)
    {
        perror("Invalid header request received");
        server_respond(server_socket, client_addr, RES_ERR);

        exit(EXIT_FAILURE);
    }
    printf("Received a header request of type %d, payload size is %d\n", test_req.type, test_req.payload_size);
    server_respond(server_socket, client_addr, RES_SUC);
    /*
        char *pld = malloc(sizeof(char) * test_req.payload_size);
        free(pld);
    */
    return 0;
}
