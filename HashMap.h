#include "Commands.h"

typedef struct a {
    Command *option;
    struct a* next;
} List;

List* hashTable[97];

// Create a List element, a node of a simply linked list.
List* nodeCreate(Command*);

// The djb2 hash function. Returns the position of a command in the table.
unsigned long hashFunction(const char*);

// Add a new command to the hash table.
void hashInsert(Command*);

// Look for a command in the hash table, if it exists, then a pointer to that command will be returned, otherwise NULL.
CommandStatus hashSearch(const char*, Command**);

// Display all existing commands on the screen
void hashWriteFunctions();

// Free the memory allocated by the hash table.
void hashDelete();

// Initialise the hash table with commands.
void init();

// Write the documentation of a command.
CommandStatus cmd_help(char*);