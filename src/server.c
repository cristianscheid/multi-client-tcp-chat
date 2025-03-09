#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_net.h>

#define SERVER_PORT 2000
#define BUFFER_SIZE 512
#define MAX_CLIENTS 10

int main(int argc, char **argv)
{
    IPaddress server_ip_address;
    const Uint16 server_port = SERVER_PORT;
    SDLNet_SocketSet socket_set;
    TCPsocket server_socket;
    TCPsocket client_sockets[MAX_CLIENTS] = {NULL};
    char *client_names[MAX_CLIENTS] = {NULL};
    char buffer[BUFFER_SIZE];

    if (SDLNet_Init() < 0)
    {
        fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
        return EXIT_FAILURE;
    }

    if (SDLNet_ResolveHost(&server_ip_address, NULL, server_port) != 0)
    {
        fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        return EXIT_FAILURE;
    }

    if (!(server_socket = SDLNet_TCP_Open(&server_ip_address)))
    {
        fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        return EXIT_FAILURE;
    }

    if (!(socket_set = SDLNet_AllocSocketSet(MAX_CLIENTS + 1))) // +1 for server socket
    {
        fprintf(stderr, "SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
        return EXIT_FAILURE;
    }

    SDLNet_TCP_AddSocket(socket_set, server_socket);

    printf("Server is up and running.\nPress Ctrl+C to shut down the server.\n\n");

    bool server_is_running = true;
    while (server_is_running)
    {
        int num_ready_sockets = SDLNet_CheckSockets(socket_set, 100); // 100ms timeout
        if (num_ready_sockets > 0)
        {
            // Accept new clients, assign a slot, and store their name
            if (SDLNet_SocketReady(server_socket))
            {
                TCPsocket new_client = SDLNet_TCP_Accept(server_socket);
                if (new_client)
                {
                    for (int i = 0; i < MAX_CLIENTS; i++)
                    {
                        if (!client_sockets[i])
                        {
                            client_sockets[i] = new_client;
                            SDLNet_TCP_AddSocket(socket_set, new_client);

                            int received_data = SDLNet_TCP_Recv(new_client, buffer, BUFFER_SIZE);
                            if (received_data > 0)
                            {
                                // Null-terminate the received data to treat it as a string
                                buffer[received_data] = '\0';
                                client_names[i] = malloc(strlen(buffer) + 1); // +1 for null terminator
                                if (client_names[i])
                                {
                                    strcpy(client_names[i], buffer);
                                    printf("New client connected: %s (slot %d).\n", client_names[i], i);
                                }
                            }
                            break;
                        }
                    }
                }
            }

            // Receive messages from clients and broadcast, handling disconnections
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                if (client_sockets[i] && SDLNet_SocketReady(client_sockets[i]))
                {
                    int received_data = SDLNet_TCP_Recv(client_sockets[i], buffer, BUFFER_SIZE);
                    if (received_data > 0)
                    {
                        // Null-terminate the received data to treat it as a string
                        buffer[received_data] = '\0';
                        char message_with_name[BUFFER_SIZE];
                        size_t name_length = strlen(client_names[i]);
                        size_t max_message_length = BUFFER_SIZE - name_length - 3; // 3 for ": " and null terminator

                        // Format the message as "Name: Message" (truncate if necessary)
                        snprintf(message_with_name, BUFFER_SIZE, "%s: %.*s",
                                 client_names[i], (int)max_message_length, buffer);

                        printf("%s\n", message_with_name);

                        for (int j = 0; j < MAX_CLIENTS; j++)
                        {
                            // Skip the sender
                            if (client_sockets[j] && j != i)
                            {
                                int message_length = strlen(message_with_name) + 1;
                                if (SDLNet_TCP_Send(client_sockets[j], message_with_name, message_length) < message_length)
                                {
                                    fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
                                }
                            }
                        }
                    }
                    else
                    {
                        printf("Client disconnected: %s (slot %d).\n", client_names[i], i);
                        SDLNet_TCP_DelSocket(socket_set, client_sockets[i]);
                        SDLNet_TCP_Close(client_sockets[i]);
                        free(client_names[i]);
                        client_names[i] = NULL;
                        client_sockets[i] = NULL;
                    }
                }
            }
        }
    }

    SDLNet_FreeSocketSet(socket_set);
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (client_sockets[i])
        {
            SDLNet_TCP_Close(client_sockets[i]);
            free(client_names[i]);
        }
    }
    SDLNet_TCP_Close(server_socket);
    SDLNet_Quit();

    return EXIT_SUCCESS;
}
