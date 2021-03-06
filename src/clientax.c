#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "./definitions.c"

char *sendMessage(int sockfd, char *message)
{
    char *reply;
    int len;
    if (send(sockfd, message, strlen(message), 0) < 0)
    {
        puts("Send failed");
        exit(1);
    }
    len = recv(sockfd, reply, MAX, 0);
    if (len < 0)
    {
        puts("Recv failed");
        exit(1);
    }

    reply[len] = '\0';

    return reply;
}

int authenticate(int sockfd)
{
    char username[MAX];
    char password[MAX];
    char reply[MAX] = FAILED_AUTH;

    while (strcmp(reply, FAILED_AUTH) == 0)
    {
        printf("Introduzca username: ");
        scanf("%s", username);
        sendMessage(sockfd, username);

        printf("Introduzca password: ");
        scanf("%s", password);
        strcpy(reply, sendMessage(sockfd, password));

        if (strcmp(reply, FAILED_AUTH) == 0)
        {
            printf("Username o password incorrectos. Inténtalo de nuevo\n");
        }
        else
        {
            printf("Bienvenido\n");
        }
    }

    return strcmp(reply, PASSED_AUTH) == 0 ? 1 : 0;
}

int main(int argc, char *argv[])
{
    int sockfd, connfd;
    SAIN servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(1);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(INET_ADDR);
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Connection with the server failed...\n");
        exit(1);
    }
    else
        printf("Connected to the server..\n");

    int authenticated = authenticate(sockfd);

    if (authenticated)
    {
        char message[MAX];
        char *reply;
        while (1)
        {
            printf("WHATCHA WANNA DO? ");
            scanf("%s", message);
            reply = sendMessage(sockfd, message);
            printf("%s\n", reply);
        }
    }

    // close the socket
    close(sockfd);

    return 0;
}
