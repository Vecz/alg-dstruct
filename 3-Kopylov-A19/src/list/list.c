#include "list.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

	list* createList() {
		list* spisok = (list*)malloc(sizeof(list));
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
		list* temp, * t;
		if (spisok->length == 0 && spisok->value == NULL) {
			spisok->value = value;
			spisok->length = strlen(value);
		}
		else {
			temp = (list*)malloc(sizeof(list));
			if (temp == NULL) {
				return NULL;
			}
			temp->length = strlen(value);
			temp->value = value;
			t = spisok;
			while (t->next != NULL) {
				t = t->next;
			}
			t->next = temp;
			temp->prev = t;
			temp->next = NULL;
		}
		return OK;
	}

	int destroyList(list** spisok) {
		if (*spisok == NULL) {
			return OK;
		}
		if ((*spisok)->next != NULL) {
			list* p = *spisok, * t = NULL;
			while (p != NULL) {
				t = p->next;
				free(p);
				p = t;
			}
			*spisok = NULL;
			return OK;
		}
		else {
			free(*spisok);
			*spisok = NULL;
			return OK;
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
			return OK;
		}
		list* p, * pNext;
		int cnt = 1;
		while (cnt) {
			cnt = 0;
			p = source;
			pNext = p->next;
			while (pNext != NULL) {
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