#include "hash_map.h"

char** commandsList(char** str, int *length)
{
    CHECK_ALLOC(*str);

    int size = 5;
    char **words = (char**)malloc(sizeof(char*) * size), *start = *str, *p;
    CHECK_ALLOC(words);
    *length = 0;

    while ((p = strstr(start, " && ")))
    {
        size_t len = p - start; // lungimea comenzii curente

        words[*length] = (char*)malloc(len + 1);
        CHECK_ALLOC(words[*length]);

        strncpy(words[*length], start, len);
        words[(*length)++][len] = '\0'; // terminator de șir

        start = p + 4; // Avansăm după " && "

        if (*length >= size) {
            size *= 2;
            words = (char**)realloc(words, sizeof(char*) * size);
            CHECK_ALLOC(words);
        }
    }

    words[*length] = strdup(start); // Ultima comandă (după ultimul " && " sau dacă nu a existat niciunul)
    (*length)++;

    if(*length + 1 < size) {
        words = (char**)realloc(words, sizeof(char*) * (*length + 1));
        CHECK_ALLOC(words);
    }
    words[*length] = NULL; // Terminatorul listei

    FREE_MEM(*str);
    return words;
}

int main()
{
    init();

    while(exit_code)
    {
        printf(">");

        int length = 0;
        char *aux = stringRead();
        if(!aux)    continue;
        char **vec = commandsList(&aux, &length);
        if(!vec)    continue;

        for(size_t i = 0; i < length; i++)
        {
            Command *cmd = NULL;
            switch(hashSearch(stringFirstWord(&(vec[i])), &cmd)) {
                case(CMD_SUCCES):       {switch(cmd->function(vec[i])) {
                                            case(CMD_INVALID_ARGS): { printf("%s", error); break;}
                                            case(CMD_RUNTIME_ERROR):{ printf("%s", error); break;}
                                         }

                                         error = NULL;
                                         break;
                                        }
                case(CMD_NOT_FOUND):    printf("!! Comanda nu exista !!\n");
            }
        }

        stringsDelete(&vec);
    }

    hashDelete();
    printf("\n\n@");
    return 0;
}