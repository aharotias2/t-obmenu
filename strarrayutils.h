#ifndef STRARRAYUTILS
#define STRARRAYUTILS

#include <string.h>
#include <stdlib.h>

void sort_str_array(char **array);

int array_length(char **array);

void copy_array(char **dest, char **src);

char **concat_array(char** array1, char **array2);

void free_array(char **array);

#endif

