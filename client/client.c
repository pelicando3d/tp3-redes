#include <stdio.h>
#include <stdlib.h>
#include "socket-client.h"
#include "../utils.h"
#define BOARD_DIMENSION 10

int board[BOARD_DIMENSION][BOARD_DIMENSION];
int adversary_board[BOARD_DIMENSION][BOARD_DIMENSION];
int server_port;
char *server_name;

int on_message_receive_callback(int client_socket);
int process_command(char command[3], char response[3]);
void attack_position();
void has_hitted();
void menu();

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        puts("E necessario passar o ip/nome do servidor e a porta de conexao.");
        return 1;
    }
    server_name = argv[1];
    server_port = atoi(argv[2]);
    iniciatlize_adversary_board();
    generate_board(board);
    menu();
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
    send_command(response);
    if (wait_for_answer)
    {
        on_message_received();
    }
    else
    {
        close_socket();
        menu();
    }
}

int process_command(char command[3], char response[3])
{
    int x, y, attack[2];
    x = command[1] - '0';
    y = command[2] - '0';
    switch (command[0])
    {
    case 'A':
    case 'a':
        attack[0] = x;
        attack[1] = y;
        if (process_attack(board, attack))
        {
            puts("O inimigo acertou uma unidade sua.");
            if(count_points(board) == 30) {
                response[0] = 'V';
                puts("Voce perdeu!");
            }
            else response[0] = 'H';
        }
        else
        {
            puts("O inimigo te atacou, mas errou.");
            response[0] = 'M';
        }
        response[1] = command[1];
        response[2] = command[2];
        break;
    case 'H':
    case 'h':
        has_hitted(x, y);
        adversary_board[x][y];
        puts("Voce atingiu uma unidade inimiga!");
        response[0] = 'W';
        return 1;
    case 'M':
    case 'm':
        puts("Voce errou!");
        adversary_board[x][y] = 0;
        response[0] = 'W';
        response[1] = '1';
        response[2] = '1';
        return 1;
    case 'V':
    case 'v':
        puts('Parabéns! Voce venceu o jogo!');
        exit(0);
    }
    return 0;
}

void menu()
{
    char input;
    while (1)
    {
        puts("||===== Batalha naval menu =====||");
        puts("|| P - Visualizar boards        ||");
        puts("|| A - Atacar adversario        ||");
        puts("||==============================||");

        scanf("%s", &input);

        switch (input)
        {
        case 'P':
        case 'p':
            print_adversary_board(adversary_board);
            puts("\n=======================================\n");
            print_board(board);
            break;
        case 'A':
        case 'a':
            attack_position();
            on_message_received();
            return;
        default:
            puts("Opcao invalida.");
        }
        fflush(stdin);
    }
}

void attack_position()
{
    int x, y;
    char attack[3];
    char horizontal_position;
    char vertical_position;
    puts("Por favor, insira a posicao horizontal do ataque (de 0 a 9)");
    scanf("%s", &horizontal_position);
    puts("Agora insira a posicao vertical do ataque (de A a J)");
    scanf("%s", &vertical_position);
    attack[0] = 'A';
    attack[1] = horizontal_position;
    attack[2] = get_number_by_letter(vertical_position) + '0';
    send_command(attack);
}

void send_command(char command[3])
{
    switch (command[0])
    {
    case 'A':
    case 'a':
    case 'H':
    case 'h':
    case 'M':
    case 'm':
    case 'W':
    case 'w':
        break;
    default:
        return;
    }
    open_socket(server_name, server_port);
    send_data(command);
}

void has_hitted(int x, int y)
{
    adversary_board[x][y] = 1;
}

void iniciatlize_adversary_board()
{
    int x, y;
    for (x = 0; x < BOARD_DIMENSION; x++)
    {
        for (y = 0; y < BOARD_DIMENSION; y++)
        {
            adversary_board[x][y] = -1;
        }
    }
}