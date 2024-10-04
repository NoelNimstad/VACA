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

    char *contents = (char *)malloc((fileSize + 1) * sizeof(char));
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