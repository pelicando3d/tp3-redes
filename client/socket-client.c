#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int opened_socket;

void create_server_socket(struct sockaddr_in * server_address, char *server_name, int server_port)
{
    memset(server_address, 0, sizeof(server_address));
    server_address->sin_family = AF_INET;

    /* Cria uma representacao digital do socket do servidor */
    inet_pton(AF_INET, server_name, &server_address->sin_addr);

    /* // htons: port in network order format */
    server_address->sin_port = htons(server_port);
}

int establish_connection(struct sockaddr_in * server_address)
{
    /* Abre um socket local */
    if ((opened_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("[Error] Socket could not be created.");
        return 1;
    }
    /* Estabelece uma conexao TCP com o socket */
    if (connect(opened_socket, (struct sockaddr *)server_address, sizeof(*server_address)) < 0)
    {
        perror("[Error] Connection with server could not be established");
        return 1;
    }
    return 0;
}

int send_data(char *data)
{
    /* Envia dados para o servidor socket */
    send(opened_socket, data, strlen(data), 0);
}

int close_socket() {
    /* Fecha a conexao com o socket */
    close(opened_socket);
}

int open_socket(char * server_name, int server_port)
{
    struct sockaddr_in server_address;

    create_server_socket(&server_address, server_name, server_port);
    
    if (establish_connection(&server_address))
    {
        return 1;
    }  
    return 0;
}