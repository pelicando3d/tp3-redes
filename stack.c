/* Lib of stack from: https://gist.github.com/sjoness/6219073 */

#include <stdio.h>
#include "stack.h"

void initialise(Stack *s) {
    s->size = 0;
    s->top = NULL;
}

void push(Stack *s, int value) {
    Node *np;
    np = (Node *)malloc(sizeof(Node));
    if (np == NULL) {
        exit(1);
    }

    np->item = value;
    np->next = s->top;
    s->top = np;
    s->size++;
}

int pop(Stack *s) {
    int temp;
    Node *np;

    if (s->top == NULL) {
        return -1;
    }

    np = s->top;
    temp = s->top->item;
    s->top = np->next;
    s->size--;
    free(np);

    return temp;
}

/* int main() {
    int pv;
    Stack stk;

    initialise(&stk); 
    push(&stk, 7);
    push(&stk, 9);
    pv = pop(&stk);
    pv = pop(&stk);
	
    return 0;
} */