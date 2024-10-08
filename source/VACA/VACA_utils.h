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
 * @param listLength Pointer to where to store the length of the list
 * @return An array of substrings, of type `char**`
 */
char **SplitString(const char *string, char token, int *listLength);
/**
 * @brief Destroys string list allocated with `malloc`
 * 
 * @param stingList String list to destroy
 */
void DestroyStringList(char **stringList);

/**
 * @brief Macro to seed the random function 
 */
#define seedRandom() srand(time(NULL))
/**
 * @brief Generates a random integer between `_l` and `_u`
 */
#define randomBetween(_l, _u) ((_l) + rand() % ((_u) - (_l) + 1))

#endif // VACA_utils_h