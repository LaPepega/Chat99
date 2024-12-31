#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "server.h"
#include "client.h"

#define SERVER_PORT 9901
#define CLIENT_PORT 9902

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        perror("No address specified");
        exit(EXIT_FAILURE);
    }

    // Address to connect to, a temporary measure
    struct in_addr con_addr;
    if (inet_pton(AF_INET, argv[1], &con_addr) < 1)
    {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    printf("Initializing server...\n");
    int server_socket = server_init_socket(SERVER_PORT);

    char req_s[24];
    request_data req = {.payload_size = 10, .payload = "HAHAHAHAHA", .type = REQ_MSG};
    client_build_request(req, req_s);

    return 0;
}
