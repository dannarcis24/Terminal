#include "cmd_math.h"
#include <math.h>

CommandStatus cmd_math(char* argv)
{
    CHECK_ARG(argv, 1);
    if(stringRemoveSpaces(&argv) != CMD_SUCCES) return CMD_INVALID_ARGS;
    
    mathFunctionValues(&argv);

    return CMD_SUCCES;
}

double ctg(double x) {
    double tg = tan(x);
    return (tg ? (1. / tg) : NAN);
}

double log2(double x) {
    return (x > 0 ? (log(x) / log(2)) : NAN);
}

void mathFunctionValues(char **str)
{
    FunctionPair functions[8] = {
        {"sin", 3, sin},
        {"cos", 3, cos},
        {"tg", 2, tan},     
        {"ctg", 3, ctg},   
        {"lg", 2, log10},   
        {"ln", 2, log},     
        {"exp", 3, exp},
        {"log", 3, log2}     
    };

    int length = strlen(*str);
    for(size_t i = 0; i < 7; i++)
    {
        char *p;
        while((p = strstr(*str, (functions[i]).name)))
        {
            char *p_end = strchr(p, ')'), num_str[50];
            double num = functions[i].func(atoi(num_str));
            if(num == NAN) {
                FREE_MEM(*str);
                return;
            }
            
            p_end = strdup(p_end + 1);
            sprintf(num_str, "%.2f", num);
            strcpy(p, num_str);
            strcat(*str, p_end);

            FREE_MEM(p_end);
        }
    }

    if(length != strlen(*str))
    {
        *str = (char*)realloc(*str, sizeof(strlen(*str)));
        CHECK_ALLOC(*str);
    }
}