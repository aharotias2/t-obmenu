#ifndef FILEUTILS
#define FILEUTILS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include "strlistutils.h"

int is_reg_file(char *path);
str_list *get_file_list(char *dir_name);
char** get_file_names(char *dir_name);

char *get_full_path(char *ipath);
#endif

