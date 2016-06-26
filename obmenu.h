#ifndef OBMENU
#define OBMENU

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>

#include "htmlutils.h"
#include "fileutils.h"
#include "strlistutils.h"

#define CATEGORY_ICON "/usr/share/icons/gnome/16x16/mimetypes/gnome-mime-text-x-vcard.png"
#define PAGE_ICON "/usr/share/icons/gnome/16x16/mimetypes/gnome-mime-text-html.png"

#define ERR_MSG_OPTION "Unknown option has been passed."
#define ERR_MSG_DIR "<!-- The Directory was not found. -->\n"

#define NAME_SIZE 100

enum TYPE {
	APPLICATION,
	LINK,
	DIRECTORY
};

struct DESKTOP_ENTRY {
	enum TYPE type;
	char *name, *comment, *command, *url, *icon;
	bool has_gui;
};

int print_dir_entries(char *dir_name);
int search_dir(char *dir_name);
int get_data(struct DESKTOP_ENTRY *data, char *path); 
void reset_data(struct DESKTOP_ENTRY *data);

char *delete_argument(char *command);

#endif

