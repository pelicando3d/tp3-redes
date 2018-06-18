#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket-server.h"
#include "../utils.h"
#include "../stack.h"

#define BOARD_DIMENSION 10

int board[BOARD_DIMENSION][BOARD_DIMENSION];
int last_attacked[2];
int adversary_board[BOARD_DIMENSION][BOARD_DIMENSION];
Stack stacked_attacks_x;
Stack stacked_attacks_y;

/* 
    Essa funcao define o comportamento da presente aplicacao ao receber uma mensagem de um client.
 */
int on_message_receive_callback(int client_socket);
void process_command (char command[3], char response[3]);
void attack_position(int attack[2]);
void has_hitted ();

int main(int argc, char *argv[])
{
    /* === Naval Battle Server === */
    puts("\n=========== Naval Battle Server ===========");
    int port = atoi(argv[1]);    
    generate_board(board);
    print_board(board);
    printf("\nPontos distribuidos %d\n", count_points(board));
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
        process_command(client_message, response);
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
    Stack stacked_attacks_y;
    return 0;
}

void process_command (char command[3], char response[3])
{
    int x, y, attack[2];
    printf("\n Command %s\n", command);
    switch(command[0])
    {
        case 'A':
        case 'a':
            x = command[1] - '0';
            y = command[2] - '0';
            attack[0] = x;
            attack[1] = y;
            if(process_attack(board, attack))
            {
                if(count_points(board) == 30){
                    response[0] = 'V';
                    generate_board(board);
                }
                else response[0] = 'H'; 
                
            }
            else
            {
                response[0] = 'M';
            }
            response[1] = command[1];
            response[2] = command[2];
            printf("\n Response %s\n", response);
            break;
        case 'H':
        case 'h':
            has_hitted();
            break;
        case 'M':
        case 'm':
            break;
        case 'W':
        case 'w':
            attack_position(attack);
            response[0] = 'A';
            response[1] = attack[0] + '0';
            response[2] = attack[1] + '0';
            break;
        case 'V':
        case 'v':
            generate_board(board);
            break;
    }
}

void attack_position(int attack[2])
{
    int x, y;
    int stacked_x = pop(&stacked_attacks_x);
    int stacked_y = pop(&stacked_attacks_y);
    if (stacked_x < 0)
    {
        do
        {
            srand((unsigned int)time(NULL));
            x = rand() % BOARD_DIMENSION;
            y = rand() % BOARD_DIMENSION;
        } while (adversary_board[x][y]);
    }

    last_attacked[0] = x;
    last_attacked[1] = y;
    attack[0] = x;
    attack[1] = y;
}

void has_hitted ()
{
    if (last_attacked[1] - 1 >= 0 && !adversary_board[last_attacked[0]][last_attacked[1]]) 
    {
        push(&stacked_attacks_x, last_attacked[0]);
        push(&stacked_attacks_y, last_attacked[1] - 1);
    }
    if (last_attacked[0] - 1 >= 0  && !adversary_board[last_attacked[0]][last_attacked[1]]) 
    {
        push(&stacked_attacks_x, last_attacked[0] - 1);
        push(&stacked_attacks_y, last_attacked[1]);
    }
    if (last_attacked[0] + 1 >= 0  && !adversary_board[last_attacked[0]][last_attacked[1]]) 
    {
        push(&stacked_attacks_x, last_attacked[0] + 1);
        push(&stacked_attacks_y, last_attacked[1]);
    }
    if (last_attacked[1] + 1 >= 0  && !adversary_board[last_attacked[0]][last_attacked[1]]) 
    {
        push(&stacked_attacks_x, last_attacked[0]);
        push(&stacked_attacks_y, last_attacked[1] + 1);
    }

    adversary_board[last_attacked[0]][last_attacked[1]] = 1;
}