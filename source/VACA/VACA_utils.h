#ifndef VACA_utils_h
#define VACA_utils_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Reads the contents of the file at path `path`
 * 
 * @param path The path to the file
 * @return The contents of the file as a `char*` 
 */
char *ReadFile(const char *path);

/**
 * @brief Counts the occurnces of `_c` in string `_s`
 * 
 * @param _s String to count from, of type `char*`
 * @param _c Char to count, of type `char`
 */
#define CountChars(_s, _c) ({ int CHAR_COUNTER = 0;                 \
                              for (int i = 0; (_s)[i] != '\0'; i++) \
                              {                                     \
                                  if ((_s)[i] == (_c))              \
                                  CHAR_COUNTER++;                   \
                              }                                     \
                              CHAR_COUNTER; })

/**
 * @brief Splits the string into substrings at delimiter `token`
 * 
 * @param string Target string
 * @param token Target delimiter
 * @return An array of substrings, of type `char**`
 */
char **SplitString(const char *string, char token);

#endif // VACA_utils_h