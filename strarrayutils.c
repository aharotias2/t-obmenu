#include "strarrayutils.h"

void sort_str_array(char **array) {
	int i, j;
	char *tmp;
	for (i = 0; array[i] != NULL; i++) {
		for (j = i; array[j] != NULL; j++) {
			if (strcmp(array[i], array[j]) > 0) {
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
}

int array_length(char **array) {
	int i = 0;
	while (array[i] != NULL) i++;
	return i;
}

void copy_array(char **dest, char **src) {
	int length = array_length(src);
	int i;
	for (i = 0; i < length; i++) {
		dest[i] = malloc(strlen(src[i]) + 1);
		strcpy(dest[i], src[i]);
	}
	dest[length] = NULL;
}

char **concat_array(char** array1, char **array2) {
	int i = array_length(array1);
	int j = array_length(array2);
	int length = i + j + 1;
	char **result = malloc(sizeof(char*) * (length + 1));
	copy_array(result, array1);
	copy_array(&result[i], array2);
	return result;
}

void free_array(char **array) {
	int i = 0;
	while (array[i] != NULL) {
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}
