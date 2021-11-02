#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <syslog.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include "defs.c"

static void daemonize()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE);

    if (pid > 0)
        exit(EXIT_SUCCESS);

    if (setsid() < 0)
        exit(EXIT_FAILURE);

    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE);

    if (pid > 0)
        exit(EXIT_SUCCESS);

    int x;
    for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
    {
        close(x);
    }
}

int authenticate(int socketax)
{
    char username[MAX];
    char password[MAX];
    char correctUsername[] = "bistinox";
    char correctPassword[] = "apapapapapapapapapapapapapapa";
    while (1)
    {
        recv(socketax, username, MAX, 0);
        recv(socketax, password, MAX, 0);

        if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0)
        {
            write(socketax, PASSED_AUTH, strlen(PASSED_AUTH));
            return 1;
        }
        else
        {
            write(socketax, FAILED_AUTH, strlen(FAILED_AUTH));
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    printf("DAEMONIZING\n");
    daemonize();

    int socketax, connfd, len;
    SAIN addresonax, cli;

    socketax = socket(AF_INET, SOCK_STREAM, 0);
    if (socketax == -1)
    {
        printf("ERROR CREATING SOCKET ❌\n");
        exit(1);
    }
    else
        printf("SOCKET CREATED ✅\n");
    bzero(&addresonax, sizeof(addresonax));

    // Assign IP, PORT
    addresonax.sin_family = AF_INET;
    addresonax.sin_addr.s_addr = htonl(INADDR_ANY);
    addresonax.sin_port = htons(PORT);

    if ((bind(socketax, (SA *)&addresonax, sizeof(addresonax))) != 0)
    {
        printf("ERROR BINDING SOCKETAX ❌\n");
        exit(1);
    }
    else
        printf("SOCKET BINDED ✅\n.\n");

    // Now server is ready to listen and verification
    if ((listen(socketax, 5)) != 0)
    {
        printf("[bruh moment]: LISTEN FAILED ❌\n");
        exit(1);
    }
    else
        printf("SERVER LISTENING 🙉");
    len = sizeof(SAIN);

    // Accept the data packet from client and verification
    connfd = accept(socketax, (SA *)&cli, (socklen_t *)&len);
    if (connfd < 0)
    {
        printf("[bruh moment]: SERVER REJECTED ❌\n");
        exit(1);
    }
    else
        printf("Server accepted the client...\n");

    int isAuthed = func(connfd);

    if (isAuthed)
    {
        printf("Authentication successful\n");
        printf("Server is ready to receive commands\n");
        while (1)
        {
            char command[MAX];
            char response[MAX];
            recv(connfd, command, MAX, 0);
            printf("Command received: %s\n", command);
            if (strcmp(command, "exit") == 0)
            {
                printf("Server is exiting\n");
                break;
            }
            else if (strcmp(command, "ls") == 0)
            {
                printf("Listing files\n");
                system("ls");
                strcpy(response, "ls");
            }
            else if (strcmp(command, "pwd") == 0)
            {
                printf("Printing working directory\n");
                system("pwd");
                strcpy(response, "pwd");
            }
            else if (strcmp(command, "cd") == 0)
            {
                printf("Changing directory\n");
                recv(connfd, command, MAX, 0);
                printf("Directory: %s\n", command);
                system("cd ");
                strcpy(response, "cd");
            }
            else if (strcmp(command, "cat") == 0)
            {
                printf("Printing file\n");
                recv(connfd, command, MAX, 0);
                printf("File: %s\n", command);
                system("cat ");
                strcpy(response, "cat");
            }
            else if (strcmp(command, "rm") == 0)
            {
                printf("Removing file\n");
                recv(connfd, command, MAX, 0);
                printf("File: %s\n", command);
                system("rm ");
                strcpy(response, "rm");
            }
            else if (strcmp(command, "mkdir") == 0)
            {
                printf("Creating directory\n");
                recv(connfd, command, MAX, 0);
                printf("Directory: %s\n", command);
            }
        }
    }

    close(socketax);

    return 0;
}
