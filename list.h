#include "cmd.h"

typedef struct a {
    void *option;
    struct a* next;
} Node;

// Create a List element, a node of a simply linked list.
Node* nodeCreate(Command*);

////////////////* STACK *////////////////

////////////////* QUEUE *////////////////

typedef struct {
    Node *first, *last;
} Queue;