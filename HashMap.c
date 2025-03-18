#include "HashMap.h"

List* nodeCreate(Command *name)
{
    List *node = (List*)malloc(sizeof(List));
    CHECK_ALLOC(node);

    node->option = name;
    node->next = NULL;

    return node;
}

unsigned long hashFunction(const char *elem)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *elem++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return (hash % 97);
}

void hashInsert(Command *elem)
{
    exit_code = 1;
    unsigned long position = hashFunction(elem->name);

    List *new = nodeCreate(elem);

    if(!hashTable[position])
        hashTable[position] = new;
    else
    {
        new->next = hashTable[position];
        hashTable[position] = new;
    }
}

CommandStatus hashSearch(const char* name, Command **cmd)
{
    for(List *aux = hashTable[hashFunction(name)]; aux; aux = aux->next)
        if(strcmp(aux->option->name, name) == 0) {
            *cmd = aux->option;
            return CMD_SUCCES;
        }
    
    return CMD_NOT_FOUND;
}

void hashWriteFunctions()
{
    printf("Lista cu comenzi disponibile este:\n");
    for(size_t i = 0; i < 97; i++)
        if(hashTable[i])
        {
            printf("%d.\n", i);

            for(List *node = hashTable[i]; node; node = node->next)
                printf("%s -> detalii\n", node->option->name);
            printf("\n");
        }
}

void hashDelete()
{
    for(size_t i = 0; i < 97; i++)
    {
        List *node = hashTable[i];
        while(node)
        {
            List *aux = node;
            node = node->next;

            free(aux->option);
            free(aux);
        }

        hashTable[i] = NULL;
    }
}

void init()
{
    for(size_t i = 0; i < 97; i++)
        hashTable[i] = NULL;

    hashInsert(cmd_create("exit", "", cmd_exit));
    hashInsert(cmd_create("echo", "", cmd_echo));
    hashInsert(cmd_create("touch", "", cmd_touch));
    hashInsert(cmd_create("print", "", cmd_print));
    hashInsert(cmd_create("copy", "", cmd_copy));
    hashInsert(cmd_create("rm", "", cmd_rm));
}