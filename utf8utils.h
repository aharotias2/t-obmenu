#ifndef UTF8UTILS
#define UTF8UTILS

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* UTF-8 functions */
int uchar_size(char s); 
bool is_head(char *c);
bool is_single(char *c);
int is_hiragana(char *s);
int is_katakana(char *s);
void to_hiragana(char *dest, char *src);
void to_katakana(char *dest, char *src);
int ustricmp(char *s1, char *s2);
int ustrlen(char *ustr);


#endif
