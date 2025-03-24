#include "list.h"

Node* nodeCreate(void *name)
{
    Node *node = (Node*)malloc(sizeof(Node));
    CHECK_ALLOC(node);
    if(status)  return NULL;

    node->option = name;
    node->next = NULL;

    return node;
}

void push(Node **head, void *name)
{
    if(!(*head)) {
        *head = nodeCreate(name);
        return;
    }

    Node *aux = nodeCreate(name);
    aux->next = *head;
    *head = aux;
}

void* pop(Node **head)
{
    if(!(*head))    return NULL;

    Node* aux = *head;
    *head = aux->next;
    void *data = aux->option;
    FREE_MEM(aux);

    return data;
}

void* top(Node *head) {
    return (!head ? NULL : head->option);
}

void stackExprNodeDelete(Node **head)
{
    if(!(*head))    return;   

    void *aux;
    while((aux = pop(head)))
        exprNodeDelete(aux);

    *head = NULL;
}