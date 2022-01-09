#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "tokenizer.h"
#include "calculator.h"
#include "util.h"

int main()
{
    pthread_t threadID;
    int size_recv, total_size;
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket. Error");
        abort();
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(12345);

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        return 1;
    }
    listen(socket_desc, 1);
    c = sizeof(struct sockaddr_in);
    while (1)
    {
        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
        if (client_sock < 0)
        {
            printf("accept failed. Error");
        }
        pthread_create(&threadID, NULL, process, &client_sock);
    }
}