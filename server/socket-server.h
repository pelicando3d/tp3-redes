/*======================= teste.h ===============*/
/*================== Cabeçalho ou header ========*/
#ifndef _H_SOCKET_SERVER
#define _H_SOCKET_SERVER
/* A nossa função */
int create_socket(int * socket_description);
int bind_socket(int socket_description, struct sockaddr_in * server, int port);
int receive_message_from_client();
int wait_connection(int socket_description);
int socket_init(int port, int (* on_message_receive_callback)(int));
/* De um enter depois de endif*/
/*Para evitar warning*/
#endif