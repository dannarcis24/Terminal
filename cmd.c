#include "cmd.h"

Command* cmd_create(char* name, char* details, Command_Function cmd)
{
    Command *node = (Command*)malloc(sizeof(Command));
    CHECK_ALLOC(node);
    if(status)  return NULL;

    node->name = name;
    node->details = details;
    node->function = cmd;

    return node;
}

CommandStatus cmd_exit(char *argv)
{
    CHECK_ARG(argv, 0);

    printf("Iesire din termi... :(");
    exit_code = 0;
    return CMD_SUCCES;
}

CommandStatus cmd_pwd(char *argv)
{
    CHECK_ARG(argv, 0);

    printf("%s\n", pwd);
    return CMD_SUCCES;
}

CommandStatus cmd_cd(char *argv)
{
    CHECK_ARG(argv, 1);

    if(strcmp("..", argv) == 0)
    {
        if(strcmp("C:\\", pwd) == 0) {
            error = "!! NU puteti cobori mai mult de C:\\, acesta este directorul principal !!\n";
            return CMD_INVALID_ARGS;
        }

        char *last = strrchr(pwd, '\\');
        if(last == pwd + 2) 
            last[1] = '\0';
        else
            *last = '\0';
        
        if(_chdir(pwd)) {
            error = "!! NU s-a putut realiza mutarea in calea specificata, a avut loc o eroare, in timpul rularii !!\n";
            return CMD_RUNTIME_ERROR;
        }
    }
    else
        if(!_chdir(argv)) {
            CALC_PWD();
        }
        else {
            error = "!! NU s-a putut realiza mutaea in calea specificata, calea nu este corecta, incercati din nou cu o cale existenta !!\n";
            return CMD_INVALID_ARGS;
        }

    return CMD_SUCCES;
}