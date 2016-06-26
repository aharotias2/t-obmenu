#include "utf8utils.h"
#include <stdio.h>

int test_size() {
	char hiragana[] = "おはようございます。";
	char *iter = hiragana;
	int i = 0, size;
	char buff[4];
	memset(buff, 0, 4);

	while (*iter != '\0') {
		size = uchar_size(*iter);
		strncpy(buff, iter, size);
		printf("%s: %d\n", buff, size);
		iter += size;
	}

	return 0;
}

int test_length() {
	char katakana[] = "イッツ・ア・ワンダフル・ワールド！";
	int length = ustrlen(katakana);
	printf("length of \"%s\": %d\n", katakana, length);
	if (length == 17) {
		return 0;
	} else {
		return 1;
	}
}

int main() {
	if(test_size() == 0) {
		printf("test_size: OK\n");
	} else {
		printf("test_size: FAIL\n");
	}
	if (test_length() == 0) {
		printf("test_length: OK\n");
	} else {
		printf("test_length: FAIL\n");
	}
	/*
	for (i = 0; i < strlen(hiragana); i += 3) {
		to_katakana(buff, hiragana[i]);
		printf("%s: %d\n", buff, uchar_size(buff));
	}
	*/
	printf("\n");
	return 0;
}

