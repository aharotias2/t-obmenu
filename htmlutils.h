#ifndef HTMLUTILS
#define HTMLUTILS

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "utf8utils.h"

/* Utility function */
char *html_encode(char *s);
char *escape_space(char *s);

#endif
