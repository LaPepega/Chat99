#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#include "server.h"

int server_init_socket(uint16_t port)
{
    // 0 -> Internet Protocol
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("Failed to create socket");
        exit(-1);
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr = INADDR_ANY,
        .sin_port = htons(port)

    };

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Failed to bind socket");
        exit(-2);
    }

    if (listen(sock, 20) < 0)
    {
        perror("Failed to make socket passive");
        exit(-3);
    }

    return sock;
}