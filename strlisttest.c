#include <stdio.h>
#include "strlistutils.h"

int main() {
	char array[5][100] = {
		"This is a pen.",
		"Hello, world!",
		"Bash is one of the best shell.",
		"Linux is the kernel.",
		"Totem pole is fantastic."
	};

	str_list root = { NULL, NULL }, *iter = &root;
	root.str = " ";

	int i;
	for (i = 0; i < 5; i++) {
		root.next = strlist_add_sort(root.next, array[i]);
	}

	printf("length: %d\n", strlist_length(root.next));
	iter = root.next;
	while (iter != NULL) {
		printf("%s\n", iter->str);
		iter = iter->next;
	}

	printf("last: %s\n", strlist_last(root.next)->str);
	strlist_free(root.next);

	return 0;
}

