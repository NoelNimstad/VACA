#ifndef VACA_utils_h
#define VACA_utils_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Integer types
typedef signed char            i8;
typedef unsigned char          u8;
typedef signed short int       i16;
typedef unsigned short int     u16;
typedef signed long int        i32;
typedef unsigned long int      u32;
typedef signed long long int   i64;
typedef unsigned long long int u64;

/**
 * @brief Reads the contents of the file at path `path`
 * 
 * @param path The path to the file
 * @return The contents of the file as a `char*` 
 */
char *ReadFile(const char *path);
/**
 * @brief Writes the contents of `contents` to a file at path `path`
 * 
 * @param contents The contents to write to the file
 * @param path The path of where to write
 */
void WriteFile(const char *contents, const char *path);

/**
 * @brief Reads a struct to memory adress `s` with size `struct_size` from the file at path `path`
 * 
 * @param s Pointer to a struct you want to read to
 * @param struct_size The size of said struct
 * @param path The path to the file
 * @return 0 for success, 1 for failiure (e.g file is empty)
 */
u8 ReadStructFromFile(void *s, const size_t struct_size, const char *path);
/**
 * @brief Writes a struct to file at path `path` with size `struct_size` from struct `s`
 * 
 * @param s Pointer to a struct you want to write from
 * @param struct_size The size of said struct
 * @param path The path to the file
 */
void WriteStructToFile(void *s, const size_t structSize, const char *path);

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
void DestroyStringList(char **stringList, int length);

/**
 * @brief Macro to seed the random function 
 */
#define seedRandom() srand(time(NULL))
/**
 * @brief Generates a random integer between `_l` and `_u`
 */
#define randomBetween(_l, _u) ((_l) + rand() % ((_u) - (_l) + 1))

#endif // VACA_utils_h