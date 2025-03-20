#include "list.h"

Node* nodeCreate(void *name)
{
    Node *node = (Node*)malloc(sizeof(Node));
    CHECK_ALLOC(node);

    node->option = name;
    node->next = NULL;

    return node;
}