#include <stdio.h>
#include "server.h"
#include "client.h"

#define SERVER_PORT 9901
#define CLIENT_PORT 9902

int main(int argc, char const *argv[])
{
    printf("Initializing server...");
    int server_socket = server_init_socket(SERVER_PORT);
    printf("Initializing client...");
    int client_socket = client_init_socket(CLIENT_PORT);
    return 0;
}
