#include "String.h"

#define CHECK_OPEN(file, name) \
    if(!(file)) { \
        printf("!! NU s-a putut deschide fisierul '%s' (%s, linia %d) !!\n", name, __FILE__, __LINE__); \
        return CMD_RUNTIME_ERROR; \
    }

typedef CommandStatus (*Command_Function)(char *argv);

typedef struct {
    char *name, *details;
    Command_Function function;
} Command;

int exit_code;

Command* cmd_create(char*, char*, Command_Function);

// Close the program.
CommandStatus cmd_exit(char*);

////////////////* FUNCTIONS FOR PROCESSING FILE COMMANDS *////////////////

// Display text on the screen/file.
CommandStatus cmd_echo(char*);

// Create a file.
CommandStatus cmd_touch(char*);

// Print on console the file contents.
CommandStatus cmd_print(char*);

CommandStatus cmd_rm(char*);
CommandStatus cmd_copy(char*);