#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <assert.h>

#define RCVBUFSIZE 512

char *sett(char *chunk, char *copyChunk, int sizeChunk, int endOfCopyChunk, int sizeOfCopyChunk);

int SIZECHUNK = 512;

char *getSubString(unsigned int start, unsigned int end, const char *expression_string)
{
    char *line = malloc((end - start + 1) * sizeof(char));
    for (int i = 0; i < end - start; ++i)
    {
        line[i] = expression_string[start + i];
    }
    line[end - start] = '\0';
    return line;
}

char *readFile(char *input)
{
    char *source = NULL;
    FILE *file = fopen(input, "r");
    assert(file);
    size_t newLen;
    if (fseek(file, 0L, SEEK_END) == 0)
    {
        long sizeOfFile = ftell(file);
        source = malloc(sizeof(char) * (sizeOfFile + 1));
        fseek(file, 0L, SEEK_SET);
        newLen = fread(source, sizeof(char), sizeOfFile, file);
        if (ferror(file) != 0)
        {
            fputs("Error reading file", stderr);
        }
        else
        {
            source[newLen] = '\0';
        }
    }
    fclose(file);
    return source;
}

void *process(void *arg)
{
    int *client_sock = (int *)arg;
    char clientMessege[RCVBUFSIZE];
    int recvMsgSize;
    while (1)
    {
        if ((recvMsgSize = recv(*client_sock, clientMessege, RCVBUFSIZE, 0)) < 0)
        {
            printf("recv failed. Erorr");
            abort();
        }
        if (recvMsgSize <= 0)
        {
            break;
        }
        struct TokenArray tokenResult = tokenize(clientMessege);
        double result = calculateExpressionTokens(tokenResult);
        char *resultStr = (char *)malloc(sizeof(double));
        sprintf(resultStr, "%f", result);
        if (send(*client_sock, resultStr, sizeof(double), 0) < 0)
        {
            printf("Send failed. Error");
            abort();
        }
    }
    close(*client_sock);
    pthread_exit(NULL);
}
#endif