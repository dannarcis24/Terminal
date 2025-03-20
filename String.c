#include "string.h"

CommandStatus stringTrim(char **str)
{
    if(!(*str))    return CMD_NOT_FOUND;

    char *start = *str;
    while(*start == ' ')  start++; // cautam primul caracter diferit de spatiu
    if(*start == '\0')
    {
        FREE_MEM(*str);
        return CMD_NOT_FOUND; // sirul a continut doar spatii => comanda invalida
    }

    char *end = start + strlen(start) - 1;
    while(end > start && *end == ' ') end--; // cautam ulrimul caracter diferit de spatiu
 
    int length = end - start + 1;
    char *aux = (char*)malloc(length + 1);
    CHECK_ALLOC(aux);

    strncpy(aux, start, length);
    aux[length] = '\0';
    free(*str);

    *str = aux;
    return CMD_SUCCES;
}

char* stringRead()
{
    char c;
    size_t pos = 0, size = 10;

    char *str = (char*)malloc(size);
    CHECK_ALLOC(str);

    while((c = fgetc(stdin)) != '\n')
    {
        if(pos + 1 == size)
        {
            size *= 2;
            str = (char*)realloc(str, size);
            CHECK_ALLOC(str);
        }

        str[pos++] = c;
    }

    str[pos] = '\0';
    if(pos + 1 < size) // ocupam doar spatiu necesar, daca am alocat mai mult, vom elibera excesul
    {
        str = (char*)realloc(str, pos + 1);
        CHECK_ALLOC(str);
    }

    if(stringTrim(&str) != CMD_SUCCES)
        return NULL;
    return str;
}

char* stringFirstWord(char **str)
{
    if(!(*str))         return NULL;

    char* word;
    if(!strchr(*str, ' ')) {
        word = strdup(*str);
        FREE_MEM(*str);

        return word;
    }

    size_t i;
    for(i = 0; (*str)[i] && (*str)[i] != ' '; i++)
        ;

    word = (char*)malloc(i + 1);
    CHECK_ALLOC(word);
    strncpy(word, *str, i);
    word[i] = '\0';

    while((*str)[i] == ' ') i++; // sarim pana la inceputul celui de al doilea cuvant
    char *aux = strdup(*str + i);
    free(*str);
    *str = aux;

    return word;
}

char** stringSplit(char **str, int *length)
{
    if(!(*str))     return NULL;

    int size = 5;
    *length = 0;
    char **words = (char**)malloc(sizeof(char*) * size), *p= strtok(*str, " ");
    CHECK_ALLOC(words);

    while(p)
    {
        if(*length + 1 == size)
        {
            size *= 2;
            words = (char**)realloc(words, sizeof(char*) * size);
            CHECK_ALLOC(words);
        }

        words[(*length)++] = strdup(p);
        p = strtok(NULL, " ");
    }
    words[*length] = NULL;

    if(*length < size)
    {
        words = (char**)realloc(words, sizeof(char*) * ((*length) + 1));
        CHECK_ALLOC(words);
    }

    FREE_MEM(*str);
    return words;
}

CommandStatus stringRemoveSpaces(char **str) 
{
    if (!(*str)) return CMD_INVALID_ARGS;

    char *start = *str, *dest = *str;
    while (*start) {
        if (*start != ' ')  *dest++ = *start;  // Mutam doar caracterele non-spatiu
        start++;
    }
    if(dest == *str)    return CMD_INVALID_ARGS;
    *dest = '\0'; // Terminam sirul corect

    *str = (char*)realloc(*str, dest - *str + 1);
    CHECK_ALLOC(*str);

    return CMD_SUCCES;
}

void stringsDelete(char ***str)
{
    if(!(*str)) return;

    for(size_t i = 0; (*str)[i]; i++) {
        FREE_MEM((*str)[i]);
    }

    FREE_MEM(*str);
}