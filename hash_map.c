#include "hash_map.h"

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

    Node *new = nodeCreate(elem);

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
    for(Node *aux = hashTable[hashFunction(name)]; aux; aux = aux->next)
        if(strcmp(((Command*)(aux->option))->name, name) == 0) {
            *cmd = (Command*)(aux->option);
            return CMD_SUCCES;
        }
    
    return CMD_NOT_FOUND;
}

void hashWriteFunctions()
{
    printf("Nodea cu comenzi disponibile este:\n");
    for(size_t i = 0; i < 97; i++)
        if(hashTable[i])
        {
            printf("%d.\n", i);

            for(Node *node = hashTable[i]; node; node = node->next)
                printf("%s -> detalii\n", ((Command*)(node->option))->name);
            printf("\n");
        }
}

void hashDelete()
{
    for(size_t i = 0; i < 97; i++)
    {
        Node *node = hashTable[i];
        while(node)
        {
            Node *aux = node;
            node = node->next;

            FREE_MEM(aux->option);
            FREE_MEM(aux);
        }

        hashTable[i] = NULL;
    }
}

void init()
{
    for(size_t i = 0; i < 97; i++)
        hashTable[i] = NULL;
    
    exit_code = 1;
    CALC_PWD();

    hashInsert(cmd_create("exit", "", cmd_exit));
    hashInsert(cmd_create("pwd", "", cmd_pwd));
    hashInsert(cmd_create("cd", "", cmd_cd));
    hashInsert(cmd_create("echo", "", cmd_echo));
    hashInsert(cmd_create("touch", "", cmd_touch));
    hashInsert(cmd_create("print", "", cmd_print));
    hashInsert(cmd_create("copy", "", cmd_copy));
    hashInsert(cmd_create("rm", "", cmd_rm));
    hashInsert(cmd_create("help", "", cmd_help));
}

CommandStatus cmd_help(char* argv)
{
    if(!argv)
        hashWriteFunctions();
    else 
    {
        Command *cmd;
        if(hashSearch(argv, &cmd))
            printf("%s\n", cmd->details);
        else {
            error = "!! Comanda nu exista, consultati 'help', pentru a interoga Nodea cu toate comenzile existente !!\n";
            return CMD_INVALID_ARGS;
        }
    }

    return CMD_SUCCES;
}