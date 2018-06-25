#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

int create_socket(int *socket_description)
{
    (*socket_description) = socket(AF_INET, SOCK_STREAM, 0);
    if ((*socket_description) == -1)
    {
        perror("[Error] Socket could not be created");
        return 1;
    }
    puts("Socked created successfully.");
    return 0;
}

int bind_socket(int socket_description, struct sockaddr_in *server, int port)
{
    /*Prepare the sockaddr_in structure*/
    server->sin_family = AF_INET;
    server->sin_addr.s_addr = INADDR_ANY;
    server->sin_port = htons(port);

    /*Bind*/
    if (bind(socket_description, server, sizeof(*server)) < 0)
    {
        perror("[Error] Socket bind failed.");
        return 1;
    }
    printf("Socket bind succeded at port %d.\n", port);
    return 0;
}

int receive_message_from_client(int client_sock)
{
    int read_size;
    char client_message[2000];
    /* //Receive a message from client */
    while ((read_size = read(client_sock, client_message, sizeof(client_message))) > 0)
    {
        /* //Send the message back to client */
        write(client_sock, client_message, strlen(client_message));
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
        perror("recv failed");
        return 1;
    }
    return 0;
}

int wait_connection(int socket_description, int (* on_message_receive_callback)(int))
{
    int client_sock, socket_address_length;
    struct sockaddr client;
    /* Accept and incoming connection */
    puts("Waiting for incoming connections...");
    socket_address_length = sizeof(struct sockaddr_in);
    pthread_t thread_id;

    /* while( (client_sock = accept(client_sock, (struct sockaddr *)&client, (socklen_t*)&socket_address_length)) )
    {
        puts("Connection accepted");
         
        if( pthread_create( &thread_id , NULL ,  on_message_receive_callback , (void*) &client_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        pthread_join( thread_id , NULL);
        puts("Handler assigned");
    } */

    /* Accept connection from an incoming client */
    client_sock = accept(socket_description, (struct sockaddr *)&client, (socklen_t *)&socket_address_length);
    if (client_sock < 0)
    {
        perror("[Error] Client connection failed to estabelish.");
        return 1;
    }
    puts("Connection with client estabelish accepted");
    pthread_create( &thread_id , NULL ,  on_message_receive_callback , (void*) &client_sock);
    /* return (*on_message_receive_callback)(client_sock); */
    return 1;
}

int socket_init(int port, int (* on_message_receive_callback)(int)) {
    printf("\n === Socket server ===\n");
    int socket_description;
    struct sockaddr_in server;

    /*Create socket*/
    if(create_socket(&socket_description))
    {
        return 1;
    }

    /*Prepare the sockaddr_in structure*/
    if (bind_socket(socket_description, &server, port))
    {
        printf("TEEEEEEEEESTE");
        return 1;
    }

    /* Listen */
    listen(socket_description, 3);
    while(1) wait_connection(socket_description, on_message_receive_callback);

}