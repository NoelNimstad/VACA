#ifndef VACA_utils_h
#define VACA_utils_h

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Reads the contents of the file at path `path`
 * 
 * @param path The path to the file
 * @return The contents of the file as a `char *` 
 */
char *ReadFile(const char *path);

#endif // VACA_utils_h