#include "list.h"

Queue* queueCreate()
{
    Queue *node = (Queue*)malloc(sizeof(Queue));
    CHECK_ALLOC(node);
    if(status)  return NULL;

    node->first = node->last = NULL;
    return NULL;
}

void enQueue(Queue *queue, void *name)
{
    if(!queue->first) queue->first = queue->last = nodeCreate(name);
    else {
        Node* aux = nodeCreate(name);
        queue->last->next = aux;
        queue->last = aux;
    }
}

void enQueueFront(Queue *queue, void *name) {
    if(!queue->first) queue->first = queue->last = nodeCreate(name);
    else {
        Node* aux = nodeCreate(name);
        aux->next = queue->first;
        queue->first = aux;
    }
}

void* deQueue(Queue *queue) 
{
    if(!queue->first)    return NULL;

    Node *aux = queue->first;
    if(queue->first == queue->last)     queue->first = queue->last = NULL;
    else    queue->first = aux->next;

    void *data = aux->option;
    FREE_MEM(aux);

    return data;
}

void* front(Queue *queue) {
    return queue->first;
}

void queueExprNodeDelete(Queue **queue)
{
    if(!(*queue))   return;
    
    void *aux;
    while((aux = deQueue(*queue)))
        exprNodeDelete(aux);
    
    FREE_MEM(*queue);
}