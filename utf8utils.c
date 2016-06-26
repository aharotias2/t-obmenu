#include "utf8utils.h"

char HIRAGANA[400] = "あいうえおぁぃぅぇぉかきくけこがぎぐげごさしすせそざじずぜぞたちつてとだぢづでどなにぬねのはひふへほばびぶべぼぱぴぷぺぽまみむめもやゃゆゅよょらりるれろわをん";

char KATAKANA[400] = "アイウエオァィゥェォカキクケコガギグゲゴサシスセソザジズゼゾタチツテトダヂヅデドナニヌネノハヒフヘホバビブベボパピプペポマミムメモヤャユュヨョラリルレロワヲン";

int is_hiragana(char *s) {
	int i = 0;
	char *hiragana = HIRAGANA;
	while (*hiragana != '\0') {
		if (strncmp(s, hiragana, 3) == 0) {
			return i;
		}
		hiragana += 3;
		i++;
	}
	return -1;
}

int is_katakana(char *s) {
	int i = 0;
	char *katakana = HIRAGANA;
	while (*katakana != '\0') {
		if (strncmp(s, katakana, 3) == 0) {
			return i;
		}
		katakana += 3;
		i++;
	}
	return -1;
}

/*
 * UTF-8 bit pattern:
 * 1 : 0xxxxxxx
 *   mask 11000000 = C0
 * 2 : 110xxxxx 10xxxxxx
 *   mask 11100000 = E0 => C0
 * 3 : 1110xxxx 10xxxxxx
 *   mask 11110000 = F0 => E0
 * 4 : 11110xxx 10xxxxxx
 *   mask 11111000 = F8 => F0
 * other : 10xxxxxx
 *   mask 11000000 = C0 => 80
 */
int uchar_size(char s) {
	if ((s & 0x80) == 0x0) {
		return 1;
	} else if ((s & 0xE0) == 0xC0) {
		return 2;
	} else if ((s & 0xF0) == 0xE0) {
		return 3;
	} else if ((s & 0xF8) == 0xF0) {
		return 4;
	} else if ((s & 0xFC) == 0xF8) {
		return 5;
	} else if ((s & 0xFE) == 0xFC) {
		return 6;
	} else {
		return 0;
	}
}

void uchar_cpy(char *dest, char *src) {
	int size = uchar_size(*src);
	if (size > 0) {
		strncpy(dest, src, size);
	}
}

void to_hiragana(char *dest, char *src) {
	int i;
	if (dest == NULL || src == NULL) return;
	if ((i = is_katakana(src)) >= 0) {
		strncpy(dest, (char*) HIRAGANA + i * 3, 3);
	} else {
		uchar_cpy(dest, src);
	}
}

void to_katakana(char *dest, char *src) {
	int i;
	if (dest == NULL || src == NULL) return;
	if ((i = is_hiragana(src)) >= 0) {
		strncpy(dest, (char*) KATAKANA + i * 3, 3);
	} else {
		uchar_cpy(dest,src);
	}
}

int ustricmp(char *s1, char *s2) {
	return strcmp(s1, s2);
}

int ustrlen(char *ustr) {
	int csize = 0;
	int slength = 0;

	char uchar[4] = "";

	while (*ustr != '\0') {
		csize = uchar_size(*ustr);
		memset(uchar, 0, 4);
		uchar_cpy(uchar, ustr);
		if (csize <= 0) {
			return -1;
		} else {
			slength++;
			ustr += csize;
		}
	}
	return slength;
}



