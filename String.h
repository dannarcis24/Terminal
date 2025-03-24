#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    CMD_SUCCES = 0,
    CMD_INVALID_ARGS,
    CMD_NOT_FOUND,
    CMD_RUNTIME_ERROR
} CommandStatus;

CommandStatus status = CMD_SUCCES;

#define FREE_MEM(ptr)   free(ptr);  ptr = NULL;

#define CHECK_ARG(arg, cond) \
    if(cond) {\
        if(!(arg)) return CMD_INVALID_ARGS; }\
    else \
        if(arg) return CMD_INVALID_ARGS; 

#define CHECK_ALLOC(ptr) \
    if(!(ptr)) { \
        printf("!! variabilei '%s' NU i s-a putut aloca memorie!! (%s, linia %s)\n", #ptr, __FILE__, __LINE__); \
        status = CMD_RUNTIME_ERROR; \
    }   status = CMD_SUCCES;

// Remove spaces from the beginning and end of a string with memory reallocation.
CommandStatus stringTrim(char**);

// Read a string of characters and dynamically allocates exactly how much memory we need. The reading is done character by character.
char* stringRead();

// Only the FIRST word is extracted, and the initial string is modified so that it starts after the first space encountered. The modification is done with memory reallocation.
char* stringFirstWord(char**);

// Break the sentence into a vector of words.
char** stringSplit(char**, int*);

// Remove all spaces inside the sentence.
CommandStatus stringRemoveSpaces(char**);

// Free the word vector memory.
void stringsDelete(char***);