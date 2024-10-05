#include "VACA_utils.h"

char *ReadFile(const char *path)
{
    FILE *filePointer = fopen(path, "r");
    if(filePointer == NULL)
    {
        fprintf(stderr, "Failed to open file %s\n", path);
        return NULL;
    }

    fseek(filePointer, 0, SEEK_END);
    long fileSize = ftell(filePointer);
    rewind(filePointer);

    char *contents = (char*)malloc((fileSize + 1) * sizeof(char));
    if (contents == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(filePointer);
        return NULL;
    }

    fread(contents, sizeof(char), fileSize, filePointer);
    contents[fileSize] = '\0';

    fclose(filePointer);
    return contents;
}

char **SplitString(const char *string, char token)
{
    int parts = CountChars(string, token);
    char **stringList = (char**)malloc(sizeof(char*) * parts);
    if(stringList == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    const char *start = string;
    int index = 0;
    while(*string)
    {
        if(*string == token)
        {
            int length = string - start;
            stringList[index] = (char*)malloc(sizeof(char) * (length + 1));
            if(stringList[index] == NULL)
            {
                fprintf(stderr, "Memory allocation failed\n");
                for(int i = 0; i < index; i++)
                {
                    free(stringList[i]);
                }
                free(stringList);

                return NULL;
            }

            strncpy(stringList[index], start, length);
            stringList[index][length] = '\0';
            index++;
            start = string + 1;
        }
        string++;
    }

    stringList[index] = strdup(start);

    return stringList;
}