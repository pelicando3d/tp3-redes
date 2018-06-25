#include <stdio.h>
#include <stdlib.h>
#include "socket-client.h"
#include "../utils.h"
#define COMMAND_MAX_SIZE 100

int server_port;
char *server_name;

int on_message_receive_callback(int client_socket);
int process_command(char command[3], char response[3]);
void create_message();

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        puts("E necessario passar o ip/nome do servidor e a porta de conexao.");
        return 1;
    }
    server_name = argv[1];
    server_port = atoi(argv[2]);
    create_message();
    return 0;
}

int on_message_received()
{
    int n = 0;
    int len = 0;
    char server_message[3];
    char response[3];
    char *pbuffer = server_message;
    n = recv(opened_socket, pbuffer, 3, 0);
    pbuffer += n;
    len += n;
    server_message[len] = '\0';
    int wait_for_answer = process_command(server_message, response);
    close_socket();
    if (wait_for_answer)
    {
        on_message_received();
    }
    else
    {
        close_socket();
        create_message();
    }
}

int process_command(char command[3], char response[3])
{

    return 0;
}

void create_message()
{
    char* input_message = malloc(sizeof(char) * COMMAND_MAX_SIZE);
    while (1)
    {
        // N: Registro
        // S: Envio   
        // R: Recebimento      
        // L: Lista   

        scanf("%s", &input_message);
        char choice = input_message[0];

        switch (choice)
        {
        case 'N':
        case 'n':
            //funcao de registro
            register_new_user(&input_message);
            on_message_received();
            break;
        case 'S':
        case 's':
            //funcao de envio
            send_message(&input_message);
            on_message_received();
            return;
        case 'R':
        case 'r':
            //funcao de recebimento
            receive_message(&input_message);
            on_message_received();
            return;
        case 'L':
        case 'l':
            //funcao de mostrar lista
            list_message(&input_message);
            on_message_received();
            break;
        default:
            puts("Opcao invalida.");
        }
        fflush(stdin);
    }
}

void register_message(char *message)
{

}

void send_message(char *message)
{

}

void receive_message(char *message)
{

}

void list_message(char *message)
{

}

