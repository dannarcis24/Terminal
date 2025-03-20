#include "cmd.h"

typedef struct b {
    char *left, *right;
    struct b **priority_operations;
    double val;
} Node;

typedef double (*math_func)(double);

typedef struct {
    const char* name;
    int length;
    math_func func;
} FunctionPair;

CommandStatus cmd_math(char*);