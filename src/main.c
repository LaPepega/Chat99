#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "server.h"
#include "client.h"

#define SERVER_PORT 9901
#define CLIENT_PORT 9902

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        perror("No address specified");
        exit(1);
    }
    struct in_addr con_addr;

    if (inet_pton(AF_INET, argv[1], &con_addr) < 1)
    {
        perror("Invalid address");
        exit(1);
    }

    printf("Initializing server...\n");
    int server_socket = server_init_socket(SERVER_PORT);

    printf("Initializing client...\n");
    int client_socket = client_init_socket(CLIENT_PORT);

    return 0;
}
