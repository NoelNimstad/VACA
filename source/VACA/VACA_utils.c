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

void WriteFile(const char *contents, const char *path)
{
    FILE *filePointer = fopen(path, "w");
    if(filePointer == NULL)
    {
        fprintf(stderr, "Failed to open file %s\n", path);
        return;
    }

    fprintf(filePointer, "%s", contents);
    fclose(filePointer);
}

u8 ReadStructFromFile(void *s, const size_t struct_size, const char *path) 
{
    FILE *filePointer = fopen(path, "rb");
    if(filePointer == NULL) 
    {
        printf("Failed to open file for reading.\n");
        return 1;
    }

    size_t read = fread(s, struct_size, 1, filePointer);
    if(read != 1) 
    {
        printf("Failed to read struct from file.\n");
        return 1;
    }

    fclose(filePointer);
    return 0;
}

void WriteStructToFile(void *s, size_t structSize, const char *path)
{
    FILE *filePointer = fopen(path, "wb");
    if(filePointer == NULL) 
    {
        printf("Failed to open file for writing.\n");
        return;
    }

    size_t written = fwrite(s, structSize, 1, filePointer);
    if(written != 1) 
    {
        printf("Failed to write struct to file.\n");
    }

    fclose(filePointer);
}

u32 CountChars(const char* s, char c) 
{
    int CHAR_COUNTER = 0;
    for(int i = 0; s[i] != '\0'; i++) 
    {
        if(s[i] == c) 
        {
            CHAR_COUNTER++;
        }
    }
    return CHAR_COUNTER;
}

char **SplitString(const char *string, char token, int *listLength)
{
    int parts = CountChars(string, token);
    char **stringList = (char**)malloc(sizeof(char*) * (parts + 1));
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
    *listLength = index + 1;

    return stringList;
}
void DestroyStringList(char **stringList, int length)
{
    for(int i = 0; i < length; i++)
    {
        free(stringList[i]);
    }
    free(stringList);
}
