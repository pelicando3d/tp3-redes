/*======================= teste.h ===============*/
/*================== Cabeçalho ou header ========*/
#ifndef _H_UTILS
#define _H_UTILS

int get_number_by_letter(char c);
char get_letter_by_number(int i);
int print_board(int ** board);
int print_adversary_board(int ** board);
int count_points(int ** board);
int **generate_board();
void initialize_board(int **board);
void put_board_piece(int **board, int piece_size, int number);
int check_vertical_size(int **board, int x, int y, int size);
int check_horizontal_size(int **board, int x, int y, int size);
/* De um enter depois de endif*/
/*Para evitar warning*/
#endif