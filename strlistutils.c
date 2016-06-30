#include "strlistutils.h"

int strlist_length(str_list *list) {
	int length = 0;
	while (list != NULL) {
		length++;
		list = list->next;
	}
	return length;
}

str_list *strlist_last(str_list *list) {
	if (list == NULL) {
		return NULL;
	}
	while (list->next != NULL) {
		list = list->next;
	}
	return list;
}

str_list* strlist_add_sort(str_list *list, char *str) {
	if (str == NULL) {
		return NULL;
	}
	str_list *new_item = malloc(sizeof(str_list));
	new_item->next = NULL;
	new_item->str = malloc(strlen(str) + 1);
	strcpy(new_item->str, str);
	str_list root;
	root.next = list;
	str_list *iter = &root;
	while (iter->next != NULL) {
		if (ustricmp(iter->next->str, str) > 0) {
			str_list *temp = iter->next;
			iter->next = new_item;
			new_item->next = temp;
			return root.next;
		}
		iter = iter->next;
	}
	iter->next = new_item;
	return root.next;
}

void strlist_free(str_list *list) {
	str_list *temp;
	while (list->next != NULL) {
		temp = list->next->next;
		if (list->next->str != NULL) {
			free(list->next->str);
		}
		free(list->next);
		list->next = temp;
	}
	free(list->str);
	free(list);
	list = NULL;
}





