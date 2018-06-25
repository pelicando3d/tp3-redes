#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket-server.h"
#include "../utils.h"

/* 
    Essa funcao define o comportamento da presente aplicacao ao receber uma mensagem de um client.
 */
int on_message_receive_callback(int client_socket);

int main(int argc, char *argv[])
{
    /* === Naval Battle Server === */
    int port = atoi(argv[1]);    
    socket_init(port, &on_message_receive_callback);
    return 0;
}

int on_message_receive_callback(int client_socket)
{
    int read_size;
    char client_message[3];
    char response[3] = "";

    while ((read_size = read(client_socket, client_message, sizeof(client_message))) > 0)
    {
        /* // process_command(client_message, response); */
        write(client_socket, response, strlen(response));
        memset(&client_message, 0, sizeof(client_message));
    }

    if (read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
        return 1;
    }
    else if (read_size == -1)
    {
        perror("Failed to received");
        return 1;
    }
    return 0;
}

void process_command (char command[3], char response[3])
{

}
