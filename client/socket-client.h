/*======================= teste.h ===============*/
/*================== Cabeçalho ou header ========*/
#ifndef _H_SOCKET_CLIENT
#define _H_SOCKET_CLIENT
/* A nossa função */
int opened_socket;

void create_server_socket(struct sockaddr_in *server_address, char *server_name, int server_port);
int establish_connection(struct sockaddr_in *server_address);
int send_data(char *data);
int close_socket();
int open_socket(char * server_name, int server_port);
/* De um enter depois de endif*/
/*Para evitar warning*/
#endif