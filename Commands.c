#include "Commands.h"

Command* cmd_create(char* name, char* details, Command_Function cmd)
{
    Command *node = (Command*)malloc(sizeof(Command));
    CHECK_ALLOC(node);

    node->name = name;
    node->details = details;
    node->function = cmd;

    return node;
}

CommandStatus cmd_exit(char *argv)
{
    printf("Iesire din termi... :(");
    exit_code = 0;
    return CMD_SUCCES;
}