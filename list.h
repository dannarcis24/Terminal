#include "cmd.h"

typedef struct a { 
    void *option;
    struct a* next;
} Node;

// Create a List element, a node of a simply linked list.
Node* nodeCreate(void*);

////////////////* STACK *////////////////

// Add an element to the stack.
void push(Node**, void*);

// Elbow and return the element at the top of the stack
void* pop(Node**);

// Return the element at the top of the stack.
void* top(Node*);

// Free the memory allocated by the stack.
void stackExprNodeDelete(Node**);

////////////////* QUEUE *////////////////

typedef struct {
    Node *first, *last;
} Queue;

Queue* queueCreate();

void enQueue(Queue*, void*);

void* deQueue(Queue*);

void* front(Queue*);

void queueExprNodeDelete(Queue**);