#include "string.h"
#include <direct.h>

#define CHECK_OPEN(file, name) \
    if(!(file)) { \
        printf("!! NU s-a putut deschide fisierul '%s' (%s, linia %d) !!\n", name, __FILE__, __LINE__); \
        return CMD_RUNTIME_ERROR; \
    }

char *pwd;
#define CALC_PWD()  CHECK_ALLOC((pwd = _getcwd(NULL, 0)));

typedef CommandStatus (*Command_Function)(char *argv);

typedef struct {
    char *name, *details;
    Command_Function function;
} Command;

int exit_code;
char *error;

// Create a command with name, details and function like CommandStatus name(char*).
Command* cmd_create(char*, char*, Command_Function);

////////////////* FUNCTIONS FOR TERMINAL PROCESSING COMMANDS *////////////////

// Close the program.
CommandStatus cmd_exit(char*);

// Print the current path.
CommandStatus cmd_pwd(char*);

// Change the current path with a specified one or ".." for the previous.
CommandStatus cmd_cd(char*);

////////////////* FUNCTIONS FOR FILE PROCESSING COMMANDS *////////////////

// Display text on the screen/file.
CommandStatus cmd_echo(char*);

// Create a file.
CommandStatus cmd_touch(char*);

// Print on console the file contents.
CommandStatus cmd_print(char*);

// Delete a file.
CommandStatus cmd_rm(char*);

// Copy the file contents in another file.
CommandStatus cmd_copy(char*);

// Rename an existent file.
CommandStatus cmd_rename(char*);