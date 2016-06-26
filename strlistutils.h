#ifndef STRLISTUTILS
#define STRLISTUTILS

#include <string.h>
#include <stdlib.h>
#include "utf8utils.h"

typedef struct STR_LIST {
	char *str;
	struct STR_LIST *next;
} str_list;

int strlist_length(str_list *list);

str_list *strlist_last(str_list *list);

str_list* strlist_add_sort(str_list *list, char *str);

void strlist_free(str_list *list);



#endif

