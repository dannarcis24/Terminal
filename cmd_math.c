#include "cmd_math.h"
#include <math.h>

ExprNode* exprNodeCreate(char *start, char *end)
{
    ExprNode *node = (ExprNode*)malloc(sizeof(ExprNode));
    CHECK_ALLOC(node);
    if(status)  return NULL;

    node->left = start;
    node->right = end;
    node->priority_operations = queueCreate();
    node->val = NAN;

    return node;
}

void exprNodeDelete(ExprNode **node) 
{
    if(!(*node))    return;

    queueExprNodeDelete(&(*node)->priority_operations);
    FREE_MEM(*node);
}

CommandStatus cmd_math(char* argv)
{
    CHECK_ARG(argv, 1);
    if(stringRemoveSpaces(&argv) != CMD_SUCCES) return CMD_INVALID_ARGS;
    
    mathFunctionValues(&argv);

    return CMD_SUCCES;
}

double ctg(double x) {
    double tg = tan(x);
    return (tg ? (1. / tg) : NAN);
}

double log2(double x) {
    return (x > 0 ? (log(x) / log(2)) : NAN);
}

void mathFunctionValues(char **str)
{
    FunctionPair functions[8] = {
        {"sin", 3, sin},
        {"cos", 3, cos},
        {"tg", 2, tan},     
        {"ctg", 3, ctg},   
        {"lg", 2, log10},   
        {"ln", 2, log},     
        {"exp", 3, exp},
        {"log", 3, log2}     
    };

    int length = strlen(*str);
    for(size_t i = 0; i < 7; i++)
    {
        char *p;
        while((p = strstr(*str, (functions[i]).name)))
        {
            char *p_end = strchr(p, ')'), num_str[50]; // cazul simplu, o functie contine DOAR un numar, NU o expresie
            strncpy(num_str, p + functions[i].length + 1, (p_end - 1) - (p + functions[i].length + 1));
            double num = functions[i].func(atoi(num_str));
            if(num == NAN) {
                FREE_MEM(*str);
                return;
            }
            
            p_end = strdup(p_end + 1);
            sprintf(num_str, "%.2f", num);
            strcpy(p, num_str);
            strcat(*str, p_end);

            FREE_MEM(p_end);
        }
    }

    if(length != strlen(*str))
    {
        *str = (char*)realloc(*str, sizeof(strlen(*str) + 1));
        CHECK_ALLOC(*str);
    }
}

Queue* mathQueueListAndValidation(char *str)
{
    if(!str) return NULL;

    int ok = 1;
    Queue *queue = queueCreate(); 
    Node *head = nodeCreate(exprNodeCreate(str, NULL)); 
    for(size_t i = 0; str[i]; i++) 
        if(!strchr("1234567890.+-*^/()", str[i])) {
            queueDelete(&queue);
            stackDelete(&head);

            return NULL;
        }
        else
        {
            if(str[i] == '(') { push(&head, exprNodeCreate(str + i, NULL)); continue;}

            if(strchr("+-*^/", str[i]))
                if(!ok) {
                    queueDelete(&queue);
                    stackDelete(&head);

                    return NULL;
                }
                else
                {
                    ok = 0;

                    if(str[i] == '^')
                        enQueueFront(top(head), exprNodeCreate(str + i, str + i)); 
                    if(str[i] == '*' || str[i] == '/')
                        enQueue(top(head), exprNodeCreate(str + i, str + i));

                    continue;
                }

            if(str[i] == ')') {
                if(!head) {
                    queueDelete(&queue);

                    return NULL;
                }

                ExprNode *aux = (ExprNode*)pop(&head);
                aux->right = str + i;
                enQueue(queue, aux); 
            }
        }

    if(head || !ok) {
        queueDelete(&queue);
        stackDelete(&head);

        return NULL;
    }

    return queue;
}

double getNumber(char *start, char *p, int where)
{
    if(where != -1 && where != 1)   return NAN;
    if(!p)                          return NAN;

    char num_str[50];
    if(where == 1)
    {
        char *p_end = p + 1;
        while(p_end)
            if(strchr("+-*^/()", *p_end))
                break;
            else
                p_end++;
        
        strncpy(num_str, p, p_end - p - 2);
    }
    else
    {
        char *p_end = --p;
        while(p >= start)
            if(strchr("+-*^/()", *p))
                break;
            else
                p--;

        strncpy(num_str, p, p_end - p - 1);
    }

    return atoi(num_str);
}

double mathResult(char *str)
{
    Queue *queue;
    if(!(queue == mathQueueListAndValidation(str))) return NAN;

    ExprNode *node;
    while((node = (ExprNode*)deQueue(queue)))
    {
        // in momentul de fata am extras secventa, care trebuie calculata
        // trebuie sa parcurg coada, pentru a putea calcula fiecare expresie (obtinere numar in dreapta si obtinere numar in stanga)
        // trebuie sa fiu atent la extinderea intervalului, va fi necesar sa eliberez nodul, care contine un altul
        // atentie la coliziuni si parcurgere in sine
    }
}