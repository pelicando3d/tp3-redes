#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/queue.h>

/* const int BOARD_DIMENSION = 10;
const int AIRCRAFT_CARRIERS_SIZE = 5;
const int TANKER_SIZE = 4;
const int ANTI_TORPEDOS_SIZE = 3;
const int SUBMARINE_SIZE = 5;
const int AIRCRAFT_CARRIERS_AMOUNT = 1;
const int TANKER_AMOUNT = 2;
const int ANTI_TORPEDOS_AMOUNT = 3;
const int SUBMARINE_AMOUNT = 4; */

#define BOARD_DIMENSION 10
#define AIRCRAFT_CARRIERS_SIZE 5
#define TANKER_SIZE 4
#define ANTI_TORPEDOS_SIZE 3
#define SUBMARINE_SIZE 2
#define AIRCRAFT_CARRIERS_AMOUNT 1
#define TANKER_AMOUNT 2
#define ANTI_TORPEDOS_AMOUNT 3
#define SUBMARINE_AMOUNT 4


int get_number_by_letter(char c)
{
    switch (c)
    { 
    case 'A':
    case 'a':
        return 0;
    case 'B':
    case 'b':
        return 1;
    case 'C':
    case 'c':
        return 2;
    case 'D':
    case 'd':
        return 3;
    case 'E':
    case 'e':
        return 4;
    case 'F':
    case 'f':
        return 5;
    case 'G':
    case 'g':    
        return 6;
    case 'H':
    case 'h':
        return 7;
    case 'I':
    case 'i':
        return 8;
    case 'J':
    case 'j':
        return 9;
    }
    return -1; 
}

char get_letter_by_number(int i)
{
    switch (i)
    {
    case 0:
        return 'a';
    case 1:
        return 'b';
    case 2:
        return 'c';
    case 3:
        return 'd';
    case 4:
        return 'e';
    case 5:
        return 'f';
    case 6:
        return 'g';
    case 7:
        return 'h'; 
    case 8:
        return 'i';
    case 9:
        return 'j';
    }
    return '\0';
}

int count_points(int board[BOARD_DIMENSION][BOARD_DIMENSION])
{
    int x, y, points = 0;
    for (x = 0; x < BOARD_DIMENSION; x++)
    {
        for (y = 0; y < BOARD_DIMENSION; y++)
        {
            points += board[x][y];
        }
    }
    return points;
}

int process_attack(int board[BOARD_DIMENSION][BOARD_DIMENSION], int attack[2])
{
    int x = attack[0];
    int y = attack[1];
    int hitted = 0;

    if (board[x][y])
    {
        hitted = 1;
    }

    board[x][y] = 0;
    return hitted;
}

int print_board(int board[BOARD_DIMENSION][BOARD_DIMENSION])
{
    int x, y = 0;
    puts("-------- Your Board -------");

    printf("\n   | ");

    for (x = 0; x < BOARD_DIMENSION; x++)
    {
        printf(" %d ", x);
    }
    printf("\n");
    for (x = 0; x < BOARD_DIMENSION + 4; x++)
    {
        printf("___");
    }

    for (x = 0; x < BOARD_DIMENSION; x++)
    {
        printf("\n %c | ", get_letter_by_number(x));
        for (y = 0; y < BOARD_DIMENSION; y++)
        {
            if(board[x][y]) printf(" X ");
            else printf(" O ");
        }
    }
    puts("");
}

int print_adversary_board(int board[BOARD_DIMENSION][BOARD_DIMENSION])
{
    int x, y = 0;
    puts("-------- Adversary Board -------");

    printf("\n   | ");

    for (x = 0; x < BOARD_DIMENSION; x++)
    {
        printf(" %d ", x);
    }
    printf("\n");
    for (x = 0; x < BOARD_DIMENSION + 4; x++)
    {
        printf("___");
    }

    for (x = 0; x < BOARD_DIMENSION; x++)
    {
        printf("\n %c | ", get_letter_by_number(x));
        for (y = 0; y < BOARD_DIMENSION; y++)
        {
            if(board[x][y] == 1) printf(" X ");
            else if(board[x][y] == 0) printf(" O ");
            else printf(" ? ");

        }
    }
}

int **generate_board(int board[BOARD_DIMENSION][BOARD_DIMENSION])
{
    initialize_board(board);
    put_board_piece(board, AIRCRAFT_CARRIERS_SIZE, AIRCRAFT_CARRIERS_AMOUNT);
    put_board_piece(board, TANKER_SIZE, TANKER_AMOUNT);
    put_board_piece(board, ANTI_TORPEDOS_SIZE, ANTI_TORPEDOS_AMOUNT);
    put_board_piece(board, SUBMARINE_SIZE, SUBMARINE_AMOUNT);
    return board;
}

void initialize_board(int board[BOARD_DIMENSION][BOARD_DIMENSION])
{
    int x, y;
    for (x = 0; x < BOARD_DIMENSION; x++)
    {
        for (y = 0; y < BOARD_DIMENSION; y++)
        {
            board[x][y] = 0;
        }
    }
}

void put_board_piece(int board[BOARD_DIMENSION][BOARD_DIMENSION], int piece_size, int number)
{
    srand((unsigned int)time(NULL));
    int i, j, x, y, direction;
    for (i = 0; i < number;)
    {
        x = rand() % BOARD_DIMENSION;
        y = rand() % BOARD_DIMENSION;
        direction = check_vertical_size(board, x, y, piece_size);
        if (!direction)
        {
            direction = check_horizontal_size(board, x, y, piece_size);
            if (direction != 0)
            {
                for (j = 0; j < piece_size; j++)
                {
                    board[x + direction * j][y] = 1;
                }
                i++;
            }
        }
        else
        {
            for (j = 0; j < piece_size; j++)
            {
                board[x][y + direction * j] = 1;
            }
            i++;
        }
    }

}

int check_vertical_size(int board[BOARD_DIMENSION][BOARD_DIMENSION], int x, int y, int size)
{
    int i;
    int checked = 1;
    int start = y + (size - 1);
    int direction = 1;
    if (start >= BOARD_DIMENSION)
    {
        start = y - (size - 1);
        direction = -1;
    }

    for (i = 0; i < size; i++)
    {
        if (board[x][start - direction * i])
        {
            return 0;
        }
    }

    return direction;
}

int check_horizontal_size(int board[BOARD_DIMENSION][BOARD_DIMENSION], int x, int y, int size)
{
    int i;
    int checked = 1;
    int start = x + (size - 1);
    int direction = 1;
    if (start >= BOARD_DIMENSION)
    {
        start = x - (size - 1);
        direction = -1;
    }

    for (i = 0; i < size; i++)
    {
        if (board[start - direction * i][y] != 0)
        {
            return 0;
        }
    }

    return direction;
}