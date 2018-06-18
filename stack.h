/*================== Cabeçalho ou header ========*/
#ifndef _H_STACK
#define _H_STACK

typedef struct node {
    int item;
    struct node *next;
} Node;

typedef struct {
    Node *top;
    int size;
} Stack;
void initialise(Stack *s);
void push(Stack *s, int value);
int pop(Stack *s);

/*Para evitar warning*/
#endif