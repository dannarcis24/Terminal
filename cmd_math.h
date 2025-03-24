#include "list.h"

typedef struct b {
    char *left, *right;
    Queue *priority_operations;
    double val;
} ExprNode;

typedef double (*math_func)(double);

typedef struct {
    const char* name;
    int length;
    math_func func;
} FunctionPair;

ExprNode* exprNodeCreate(char*, char*);

void exprNodeDelete(ExprNode**);

// Calculate ctg(x) or return NAN, if the function is not defined at that point.
double ctg(double);

// Calculate log in base 2 of x => log2(x) or return NAN, if the function is not defined at that point.
double log2(double);

// Calculates and replaces functions in mathematical expressions
void mathFunctionValues(char**);

CommandStatus cmd_math(char*);