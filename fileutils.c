#include "fileutils.h"

int is_reg_file(char *path) {
	struct stat file_info;

	if (stat(path, &file_info) == 0) {
		if (S_ISREG(file_info.st_mode)) {
			return 1;
		} else if (S_ISDIR(file_info.st_mode)) {
			return 0;
		}
	}
	return -1;
}

str_list* get_file_list(char *dir_name) {
	str_list dir_list = {"  ", NULL}, file_list = {"  ", NULL};
	char *path;

	DIR *dir;
	struct dirent *dp;
	int dir_length = strlen(dir_name);

	if (dir_length <= 0) {
		return NULL;
	}

	dir = opendir(dir_name);
	if (dir == NULL) return NULL;

	for (dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
		if (dp->d_name[0] == '.') {
			continue;
		}
		path = malloc(dir_length + 1 + strlen(dp->d_name) + 1);
		sprintf(path, "%s/%s", dir_name, dp->d_name);
		int file_type = is_reg_file(path);
		if (file_type == 1) {
			strlist_add_sort(&file_list, dp->d_name);
		} else if (file_type == 0) {
			strlist_add_sort(&dir_list, dp->d_name);
		}
		free(path);
	}

	closedir(dir);

	if (strlist_length(dir_list.next) > 0) {
		strlist_last(dir_list.next)->next = file_list.next;
	} else {
		dir_list.next = file_list.next;
	}

	return dir_list.next;
}

char *get_full_path(char *ipath) {
	char *i, *j, *k;
	char *opath, *tmp;

	if (*ipath == '~' && *(ipath + 1) == '/') {
		tmp = getenv("HOME");
		opath = (char *) malloc(strlen(tmp) + strlen(ipath) + 1);
		sprintf(opath, "%s%s", tmp, ipath + 1);
	} else if (*ipath != '/') {
		tmp = getenv("PWD");
		opath = (char *) malloc(strlen(tmp) + strlen(ipath) + 2);
		sprintf(opath, "%s/%s", tmp, ipath);
	} else {
		opath = (char *) malloc(strlen(ipath) + 1);
		strcpy(opath, ipath);
	}

	i = opath;

	do {
		if (i > ipath && *(i + 1) == '.' && *(i - 1) == '/' && *i == '.' && *(i + 2) == '/') {
			j = i - 2;
			while (*j != '/' && j > opath) {
				j--;
			};
			if (j < opath) {
				j = opath;
			} else if (j == opath) {
				*j = '/';
			}
			i += 2;
		} else if (i > ipath && *i == '.' && *(i - 1) == '/' && *(i + 1) == '/') {
			j = i - 1;
			i += 1;
		} else if (i > ipath && *i == '/' && *(i - 1) == '/') {
			j = i - 1;
		} else if (*i == '/' && *(i + 1) == '/') {
			j = i;
			while (*(i + 1) == '/') {
				i += 1;
			}
		} else if (*i == '/' && *(i + 1) == '\0') {
			*i = '\0';
		} else {
			j = i;
		}

		if (i != j) {
			k = j;
			do {
				*j = *i;
				j++;
				i++;
			} while (*i != '\0');
			*j = '\0';
			i = k;
		}
		i++;
	} while (*i != '\0' && i >= opath);

	return opath;
}

