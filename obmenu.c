#include "obmenu.h"

/* Global variables */
char *g_cmd_name = NULL;
char *g_filer_name = NULL;
char *g_browser_name = NULL;
char *g_dir_name = NULL;
char *g_icon_dir = NULL;

/* Program */
int main(int argc, char **argv) {
	int err = 0;
	int i;
	int len;

	/* Set default applications to open bookmarks */

	g_cmd_name = argv[0];
	g_dir_name = getenv("HOME");
	g_browser_name = "firefox";
	g_filer_name = "rox";
	g_icon_dir = "/usr/share/icons/hicolor/32x32/apps";

	/* If applications is specified. */
	for (i = 1; i < argc; i++) {
		len = strlen(argv[i]);
		if (len > 2 && argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'd': g_dir_name = get_full_path(argv[i] + 2); break;
				case 'b': g_browser_name = argv[i] + 2; break;
				case 'f': g_filer_name = argv[i] + 2; break;
				case 'i': g_icon_dir = get_full_path(argv[i] + 2); break;
				default:
				    exit(1);
			}
		}
	}

	printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	printf("<openbox_pipe_menu>\n");
	err = print_dir_entries(g_dir_name);
	if (err) {
		printf(ERR_MSG_DIR);
	}

	printf(
		"<separator label=\"編集\" />\n"
		"<item label=\"Open the location with %s\" icon=\"%s/%s.png\">\n"
		"  <action name=\"Execute\"><execute>%s &quot;%s&quot;</execute></action>\n"
		"</item>\n",
		g_filer_name, g_icon_dir, g_filer_name, g_filer_name, g_dir_name
	);

	printf("</openbox_pipe_menu>\n");

	if (g_dir_name != NULL) {
		free(g_dir_name);
	}

	if (g_icon_dir != NULL) {
		free(g_icon_dir);
	}
	return 0;
}

int print_dir_entries(char *dir_name) {
	int dir_name_length = strlen(dir_name), item_length = 0;
	char *path = NULL;
	char *escaped_path = NULL;
	str_list *list = get_file_list(dir_name);
	struct DESKTOP_ENTRY data = { APPLICATION, NULL, NULL, NULL, NULL, NULL, true };

	if (dir_name == NULL || list == NULL) return 1;

	str_list *item = list;
	while (item != NULL) {
		item_length = strlen(item->str);
		path = realloc(path, dir_name_length + 1 + item_length + 1);
		sprintf(path, "%s/%s", dir_name, item->str);
		switch (is_reg_file(path)) {
		case 1:
			if (get_data(&data, path)) { 
				if (data.type == LINK) {
					printf(
						"<item\n"
						"  label=\"%s\"\n"
						"  icon=\"" PAGE_ICON "\">\n"
						"  <action name=\"Execute\">\n"
						"    <execute>%s &quot;%s&quot;</execute>\n"
						"  </action>\n"
						"</item>\n",
						data.name,
						g_browser_name,
						data.url
					);
				} else if (data.type == APPLICATION) {
					printf(
						"<item\n"
					);
					if (data.comment != NULL) {
						printf(
						"  label=\"%s (%s)\"\n", data.name, data.comment
						);
					} else {
						printf(
						"  label=\"%s\"\n", data.name
						);
					}
					printf(
						"  icon=\"%s/%s.png\">\n"
						"  <action name=\"Execute\">\n",
						g_icon_dir,
						data.icon
					);
					if (data.has_gui) {
						printf(
						"    <execute>%s</execute>\n", data.command
						);
					} else {
						printf(
						"    <execute>urxvt -icon &quot;%s/%s.png&quot; -title &quot;%s&quot; -e &quot;%s&quot;</execute>\n",
						g_icon_dir,
						data.command,
					   	data.command,
						data.command
						);
					}
					printf(
						"  </action>\n"
						"</item>\n"
					);
				}
			}
			reset_data(&data);
			break;

		case 0: /* if the path represents a directory */
			escaped_path = escape_space(path);
			printf(
				"<menu\n"
				"  icon=\"" CATEGORY_ICON "\"\n"
				"  id=\"%s\"\n"
				"  label=\"%s\"\n"
				"  execute=\"%s -d%s -b%s -f%s -i%s\" />\n",
				item->str,
				item->str,
				g_cmd_name,
				escaped_path,
				g_browser_name,
				g_filer_name,
				g_icon_dir
			);
			free(escaped_path);
			break;
		}
		item = item->next;
	}
	strlist_free(list);
	free(path);
	return 0;
}

int get_data(struct DESKTOP_ENTRY *data, char *path) {
	FILE *fp;
	char s[3000];
	int len;
	bool is_link = false, is_app = false;
	int i;
	int result = 0;

	fp = fopen(path, "r");
	if (fp == NULL)
		return 0;

	while (fgets(s, 3000, fp) != NULL) {
		/* chomp */
		len = strlen(s);
		i = 2;
		while (i > 0) {
			if (s[len - i] == '\n' || s[len - i] == '\r') {
				s[len - i] = '\0';
				break;
			}
			i--;
		}
		len -= i;

		/* Check the file is actually a .desktop file */
		if (strstr(s, "[InternetShortcut]") != NULL) {
			is_link = true;
			is_app = false;
			data->type = LINK;
			result = 1;
		} 

		if (strstr(s, "[Desktop Entry]") != NULL && !is_link) {
			is_app = true;
			data->type = APPLICATION;
			result = 1;
		}

		if (is_link) {
			/* Copy the URL found in the file */
			if (strncmp(s, "URL=", 4) == 0) {
				data->url = html_encode(s + 4);
			}
		} else if (is_app) {
			if (strncmp(s, "Name=", 5) == 0 && data->name == NULL) {
				data->name = html_encode(s + 5);
			} else if (strncmp(s, "Exec=", 5) == 0 && data->command == NULL) {
				char *temp = html_encode(s + 5);
				data->command = delete_argument(temp);
				free(temp);
			} else if (strncmp(s, "Comment[ja]=", 12) == 0) {
				if (data->comment != NULL) free(data->comment);
				data->comment = html_encode(s + 12);
			} else if (strncmp(s, "Comment=", 8) == 0 && data->comment == NULL) {
				data->comment = html_encode(s + 8);
			} else if (strncmp(s, "Terminal=", 9) == 0) {
				for (i = 0; i < strlen(s); i++) {
					s[i] = tolower(s[i]);
				}
				if (strstr(s, "true") != NULL) {
					data->has_gui = false;
				} else if (strstr(s, "false") != NULL) {
					data->has_gui = true;
				}
			}
		}
	}
	fclose(fp);

	if (data->name == NULL) {
		char *a = strrchr(path, '/') + 1;
		char *b = strrchr(path, '.');
		data->name = malloc(b - a + 1);
		strncpy(data->name, a, b - a);
		data->name[b - a] = '\0';
	}

	if (result == 1 && data->type == APPLICATION) {
		char *fn = strrchr(path, '/') + 1;
		char *ex = strrchr(path, '.');
		len = ex - fn;
		data->icon = malloc(len + 5);

		char *a = data->icon, *b = fn;
		while (*b != '\0' && b < ex) {
			if (*b == ' ') {
				*a = '-';
			} else {
				*a = tolower(*b);
			}
			a++;
			b++;
		}
		*a = '\0';
	}
	return result;
}

void reset_data(struct DESKTOP_ENTRY *data) {
	if (data->name != NULL) {
		free(data->name);
		data->name = NULL;
	}
	if (data->command != NULL) {
		free(data->command);
		data->command = NULL;
	}
	if (data->comment != NULL) {
		free(data->comment);
		data->comment = NULL;
	}
	if (data->url != NULL) {
		free(data->url);
		data->url = NULL;
	}
	if (data->icon != NULL) {
		free(data->icon);
		data->icon = NULL;
	}
	data->has_gui = false;
}

char *delete_argument(char *command) {
	char *result = NULL;
	/*int i;*/
	bool stop = false;
	char *p, *q; 

	result = malloc(strlen(command) + 1);
	p = result;
	q = command;
	while (*q != '\0') {
		if (*q == '%') {
			stop = true;
		}
		if (stop) {
		   if (*q == ' ') {
			stop = false;
		   }
		} else {
			*p = *q;
			p++;
		}
		q++;
	}
	if (stop && *(p - 1) == ' ') {
		p--;
	}
	*p = '\0';
	return result;
}



