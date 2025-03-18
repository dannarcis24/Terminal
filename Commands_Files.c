#include "Commands.h"

CommandStatus cmd_echo(char *argv)
{
    CHECK_ARG(argv);

    char *pos = strstr(argv, ">");
    if(!pos)
        printf("%s", argv);
    else
    {
        *(pos - 1) = '\0';

        int length = 0;
        char **words = stringSplit(&pos, &length);
        if(length != 2)
            return CMD_INVALID_ARGS;

        char *bin = strstr(words[1], ".bin");
        FILE *file = fopen(words[1], (bin ?
                ((strcmp(words[0], ">") == 0) ? "wb" : "ab") :
                ((strcmp(words[0], ">") == 0) ? "wt" : "at"))
        );
        CHECK_OPEN(file, words[1]);

        if(bin)
            fwrite(argv, strlen(argv), 1, file);
        else
            fprintf(file, "%s", argv);

        stringsDelete(&words);
        fclose(file);
    }

    return CMD_SUCCES;
}

CommandStatus cmd_touch(char* argv)
{
    CHECK_ARG(argv);
    if(stringRemoveSpaces(&argv) != CMD_SUCCES) return CMD_INVALID_ARGS;

    FILE *file = fopen(argv, "wt");
    CHECK_OPEN(file, argv);
    
    fclose(file);
    return CMD_SUCCES;
}

CommandStatus cmd_print(char* argv)
{
    CHECK_ARG(argv);

    char *bin = strstr(argv, ".bin");
    FILE *file = fopen(argv, (bin ? "rb" : "rt"));
    CHECK_OPEN(file, argv);

    char aux[100];
    if(bin)
        while(fread(aux, 1, 100, file) > 0)
            fwrite(aux, 1, 100, stdout);
    else
        while(fgets(aux, 100, file))
            printf("%s", aux);

    fclose(file);
    return CMD_SUCCES;
}

CommandStatus cmd_copy(char* argv)
{
    CHECK_ARG(argv);

    int length;
    char **words = stringSplit(&argv, &length);
    if(!words || length != 2)   return CMD_INVALID_ARGS;

    FILE *file1, *file2;
    char *type_file1 = strstr(words[0], ".bin"), *type_file2 = strstr(words[1], ".bin"); // acces files based on extensions
    file1 = fopen(words[0], (type_file1 ? "rb" : "rt"));
    CHECK_OPEN(file1, words[0]);
    file2 = fopen(words[1], (type_file2 ? "wb" : "wt"));
    CHECK_OPEN(file2, words[1]);

    char aux[100];
    while((type_file1 ? (void*)(fread(aux, 1, 100, file1) > 0) : (void*)fgets(aux, 100, file1)))
        (type_file2 ? fwrite(aux, 1, 100, file2) : fprintf(file2, "%s", aux));

    fclose(file1);
    fclose(file2);
    return CMD_SUCCES;
}

CommandStatus cmd_rm(char *argv)
{
    CHECK_ARG(argv);

    int length;
    char **words = stringSplit(&argv, &length);
    if(!words)  return CMD_INVALID_ARGS;

    for(size_t i = 0; i < length; i++)
        if(remove(words[i]))
            printf("Fisierul %s NU a putut fi sters.\n", words[i]);
    
    return CMD_SUCCES;
}