#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <SDL2/SDL_net.h>

#define SERVER_HOST "127.0.0.1"
#define SERVER_PORT 2000
#define BUFFER_SIZE 512

int main(int argc, char **argv)
{
    IPaddress server_ip_address;
    const char *server_host = SERVER_HOST;
    Uint16 server_port = SERVER_PORT;
    SDLNet_SocketSet socket_set;
    TCPsocket client_socket;
    char buffer[BUFFER_SIZE];
    int message_length;

    if (SDLNet_Init() < 0)
    {
        fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
        return EXIT_FAILURE;
    }

    if (SDLNet_ResolveHost(&server_ip_address, server_host, server_port) != 0)
    {
        fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        return EXIT_FAILURE;
    }

    if (!(client_socket = SDLNet_TCP_Open(&server_ip_address)))
    {
        fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        return EXIT_FAILURE;
    }

    if (!(socket_set = SDLNet_AllocSocketSet(1)))
    {
        fprintf(stderr, "SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
        return EXIT_FAILURE;
    }

    SDLNet_TCP_AddSocket(socket_set, client_socket);

    printf("Welcome to the Multi-Client TCP Chat!\n\n");

    printf("Please enter your name: ");
    scanf("%[^\n]", buffer);
    message_length = strlen(buffer) + 1;
    // Consume \n character left in the input buffer by scanf()
    getchar();

    if (SDLNet_TCP_Send(client_socket, (void *)buffer, message_length) < message_length)
    {
        fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        return EXIT_FAILURE;
    }

    printf("\n\nYou're all set! To send a message, just type and press Enter. Press Ctrl+C to quit.\n\n");

    bool client_is_running = true;
    while (client_is_running)
    {
        // Non-blocking input check
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds); // Add standard input (keyboard) to the read set

        struct timeval timeout = {0, 100000}; // 100ms timeout
        int ready_count = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

        // Send user input to server
        if (ready_count > 0 && FD_ISSET(STDIN_FILENO, &readfds))
        {
            if (fgets(buffer, BUFFER_SIZE, stdin) != NULL)
            {
                buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
                message_length = strlen(buffer) + 1;

                if (SDLNet_TCP_Send(client_socket, buffer, message_length) < message_length)
                {
                    fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
                    return EXIT_FAILURE;
                }
                printf("\n");
            }
        }

        // Receive messages from the server
        int num_ready_sockets_server = SDLNet_CheckSockets(socket_set, 100); // 100ms timeout
        if (num_ready_sockets_server > 0)
        {
            if (SDLNet_SocketReady(client_socket))
            {
                int received = SDLNet_TCP_Recv(client_socket, buffer, BUFFER_SIZE);
                if (received > 0)
                {
                    buffer[received] = '\0';
                    printf("---- %s\n\n", buffer);
                }
            }
        }
    }

    SDLNet_FreeSocketSet(socket_set);
    SDLNet_TCP_Close(client_socket);
    SDLNet_Quit();

    return EXIT_SUCCESS;
}
