#include "list.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

	list * createList() {
		list * spisok = (list*)malloc(sizeof(list));
		if (spisok == NULL) {
			return NULL;
		}
		spisok->length = 0;
		spisok->next = NULL;
		spisok->prev = NULL;
		spisok->value = NULL;
		return spisok;
	}

	int addElementToList(list* spisok, char* value) {
		list* temp;
		if (spisok->length == 0 && spisok->value == NULL) {
			spisok->value = value;
			spisok->length = strlen(value);
		}
		else {
			temp = (list*)malloc(sizeof(list));
			if (temp == NULL) {
				return 1;
			}
			temp->length = strlen(value);
			temp->value = value;
			if (spisok->next == NULL) {
				spisok->next = temp;
				temp->prev = spisok;
			}
			else {
				spisok->prev->next = temp;
				temp->prev = spisok->prev;
			}
			temp->next = spisok;
			spisok->prev = temp;
		}
		return 0;
	}

	int destroyList(list** spisok) {
		if (*spisok == NULL) {
			return 0;
		}
		if ((*spisok)->prev != NULL) {
			(*spisok)->prev->next = NULL;
			list* p = *spisok, * t = NULL;
			while (1) {
				t = p->next;
				free(p);
				p = t;
				if (p == NULL) {
					break;
				}
			}
			*spisok = NULL;
			return 0;
		}
		else {
			free(*spisok);
			*spisok = NULL;
			return 0;
		}
	}


	void swapValues(list* a, list* b) {
		int t = a->length;
		char* tValue = a->value;
		a->length = b->length;
		a->value = b->value;
		b->length = t;
		b->value = tValue;
	}

	void sortList(list* source) {
		if (source == NULL || source->next == NULL) {
			return;
		}
		list* p, * pNext;
		int cnt = 1;
		while (cnt) {
			cnt = 0;
			p = source;
			pNext = p->next;
			while (pNext != source) {
				if (strcmp(p->value, pNext->value) > 0) {
					swapValues(p, pNext);
					cnt++;
				}
				p = pNext;
				pNext = p->next;
			}
		}
	}

#ifdef __cplusplus
}
#endif