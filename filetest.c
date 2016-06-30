#include <stdio.h>
#include "strlistutils.h"
#include "fileutils.h"

int test1() {

	str_list *list = get_file_list("/home/tk2/.pg");
	str_list *iter = list;

	if (list != NULL) {
		while (iter != NULL) {
			printf("%s\n", iter->str);
			iter = iter->next;
		}

		strlist_free(list);
	}
	return 0;
}

int test2() {
	int l, i;
	char *full_path = NULL;
	char *p[20];
	i = 0;
	p[i++] = "~/hoge/fuga/piyo.txt";
	p[i++] = "./test/test.txt";
	p[i++] = "/test/test/./../test.txt";
	p[i++] = "test/../test.txt";
	p[i++] = "../../../../../../test.txt";
	p[i++] = "./////test.txt";
	p[i++] = "~/test////test.txt";
	p[i++] = "~/hoge/../fuga/../piyo/../.././/test.txt";
	p[i++] = "./hoge/../fuga/../piyo/../.././/test.txt";
	p[i++] = "./hoge/~/fuga/.~/piyo/../.././/test.txt";
	l = i;

	for (i = 0; i < l; i++) {
		full_path = get_full_path(p[i]);
		printf("%s -> %s\n", p[i], full_path);
		free(full_path);
	}

	return 0;
}


int main(int argc, char **argv) {
	char test_no = '0';
	int result = 0;

	if (argc > 1) {
		test_no = argv[1][0];
		switch (test_no) {
			case '1': result = test1(); break;
			case '2': result = test2(); break;
		}
	} else {
		result = test1() || test2();
	}

	return result;
}

