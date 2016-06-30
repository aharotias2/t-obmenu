#include "htmlutils.h"

typedef enum {
	HTML,
	SPACE
} ENCODE_OPTION;

char *escape_string(char *s, ENCODE_OPTION option);


char *html_encode(char *s) {
	return escape_string(s, HTML);
}

char *escape_space(char *s) {
	return escape_string(s, SPACE);
}

char *escape_string(char *s, ENCODE_OPTION option) {
	char *result = NULL;
	char *a, *b;

	int c = 0;
	bool if_true_ascii = false;

	for (a = s; *a != '\0'; a++) {
		if (option == HTML) {
			if (*a == '&') {
				c += 4;
			} else if (*a == '<' || *a == '>') {
				c += 3;
			} else if (*a == '"' || *a == '\'') {
				c += 5;
			}
		} else if (option == SPACE) {
			if (*a == ' ') {
				c += 1;
			}
		}
	}

	result = malloc(strlen(s) + c + 1);
	a = s;
	b = result;
	*b = '\0';

	while (*a != '\0') {
		if_true_ascii = uchar_size(*a) == 1;
		
		if (option == HTML) {
			if (if_true_ascii && *a == '&') {
				strcat(b, "&amp;");
				b += 5;
			} else if (if_true_ascii && *a == '<') {
				strcat(b, "&lt;");
				b += 4;
			} else if (if_true_ascii && *a == '>') {
				strcat(b, "&gt;");
				b += 4;
			} else if (if_true_ascii && *a == '"') {
				strcat(b, "&quot;");
				b += 6;
			} else if (if_true_ascii && *a == '\'') {
				strcat(b, "&apos;");
				b += 6;
			} else {
				*b = *a;
				b += 1;
			}
		} else if (option == SPACE) {
			if (if_true_ascii && *a == ' ') {
				strcat(b, "\\ ");
				b += 2;
			} else {
				*b = *a;
				b += 1;
			}
		}
		*b = '\0';

		a++;
	}

	return result;
}

