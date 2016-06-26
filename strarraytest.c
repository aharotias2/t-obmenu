#include <stdio.h>
#include "strarrayutils.h"

int main() {
	char **list = malloc(sizeof(char*) * 3);
	list[0] = "Hello, world";
	list[1] = "cat is very cute";
	list[2] = NULL;

	char **list2 = malloc(sizeof(char*) * 3);

	copy_array(list2, list);

	printf("%s\n%s\n%s\n", list[0], list[1], list[2]);
	printf("%s\n%s\n%s\n", list2[0], list2[1], list2[2]);

	char **list3 = concat_array(list, list2);
	char **iter = list3;
	while (*iter != NULL) {
		printf("%s\n", *iter);
		iter++;
	}

	printf("%d\n", array_length(list));
	printf("%d\n", array_length(list2));
	printf("%d\n", array_length(list3));

	/*
	free_array(list);
	free_array(list2);
	free_array(list3);
	*/
	
	return 0;
}
