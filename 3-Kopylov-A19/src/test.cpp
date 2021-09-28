#define _CRTDBG_MAP_ALLOC
#include "pch.h"
#include "list.h"
#include <stdlib.h>
#include <assert.h>
#include <crtdbg.h>


TEST(createListTest, createList_returnRightValue) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	list* spisok = createList();	
	EXPECT_TRUE(spisok != NULL);
	EXPECT_EQ(spisok->length, 0);
	EXPECT_TRUE(spisok->next == NULL);
	EXPECT_TRUE(spisok->prev == NULL);
	EXPECT_TRUE(spisok->value == NULL);
	free(spisok);
}


TEST(addElementToListTest, addElementToList_addElementAtTheEmptyList) {
	list* spisok = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = NULL;
	spisok->prev = NULL;
	spisok->length = 0;
	spisok->value = NULL;
	addElementToList(spisok, "123456");
	EXPECT_TRUE(spisok != NULL);
	EXPECT_EQ(spisok->length, strlen("123456"));
	EXPECT_TRUE(spisok->next == NULL);
	EXPECT_TRUE(spisok->prev == NULL);
	EXPECT_TRUE(strcmp(spisok->value, "123456") == 0);
	free(spisok);
}

TEST(addElementToListTest, addElementToList_addElementAtTheSemiFullList) {
	list *spisok;
	spisok = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = NULL;
	spisok->prev = NULL;
	spisok->length = 6;
	spisok->value = "123456";
	addElementToList(spisok, "7654321");
	EXPECT_TRUE(spisok != NULL);
	EXPECT_TRUE(spisok->next != NULL);
	EXPECT_TRUE(spisok->prev != NULL);
	EXPECT_TRUE(strcmp(spisok->next->value, "7654321") == 0);
	EXPECT_EQ(spisok->next->length, strlen("7654321"));
	free(spisok->next);
	free(spisok);
}

TEST(addElementToListTest, addElementToList_addElementAtTheFullList) {
	list* spisok, *el;
	spisok = (list*)malloc(sizeof(list));
	el = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = el;
	spisok->prev = el;
	spisok->length = 6;
	spisok->value = "123456";
	el->next = spisok;
	el->prev = spisok;
	el->length = 7;
	el->value = "7654321";
	addElementToList(spisok, "12345678");
	EXPECT_TRUE(spisok != NULL);
	EXPECT_TRUE(spisok->next->next != NULL);
	EXPECT_TRUE(spisok->prev != NULL);
	EXPECT_TRUE(strcmp(spisok->prev->value, "12345678") == 0);
	EXPECT_EQ(spisok->prev->length, strlen("12345678"));
	free(spisok->next);
	free(spisok->prev);
	free(spisok);
}

TEST(destroyListTest, destroyList_destroyTheEmptyList) {
	list* spisok = NULL;
	destroyList(&spisok);
	EXPECT_TRUE(spisok == NULL);
}

TEST(destroyListTest, destroyList_destroyTheSemiFullList) {
	list* spisok;
	spisok = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = NULL;
	spisok->prev = NULL;
	spisok->length = 6;
	spisok->value = "123456";
	destroyList(&spisok);
	EXPECT_TRUE(spisok == NULL);
}

TEST(destroyListTest, destroyList_destroyTheFullList) {
	list* spisok, * el;
	spisok = (list*)malloc(sizeof(list));
	el = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = el;
	spisok->prev = el;
	spisok->length = 6;
	spisok->value = "123456";
	el->next = spisok;
	el->prev = spisok;
	el->length = 7;
	el->value = "7654321";
	destroyList(&spisok);
	EXPECT_TRUE(spisok == NULL);
}

TEST(swapValuesTest, swapValuesTest_correctValue) {
	list* spisok, * el;
	spisok = (list*)malloc(sizeof(list));
	el = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = el;
	spisok->prev = el;
	spisok->length = 6;
	spisok->value = "123456";
	el->next = spisok;
	el->prev = spisok;
	el->length = 7;
	el->value = "7654321";
	swapValues(spisok, el);
	EXPECT_TRUE(strcmp(spisok->value, "7654321") == 0);
	EXPECT_TRUE(strcmp(el->value, "123456") == 0);
	free(el);
	free(spisok);
}

TEST(sortListTest, sortList_sortTheEmptyList) {
	list* spisok = NULL;
	sortList(spisok);
	EXPECT_TRUE(spisok == NULL);
}

TEST(sortListTest, sortList_sortTheSemiFullList) {
	list* spisok;
	spisok = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = NULL;
	spisok->prev = NULL;
	spisok->length = 6;
	spisok->value = "123456";
	sortList(spisok);
	EXPECT_TRUE(strcmp(spisok->value, "123456") == 0);
	free(spisok);
}

TEST(sortListTest, sortList_sortTheListWithTheElementsOfTheSameLengthUnsorted) {
	list* spisok, * el, * el2;
	spisok = (list*)malloc(sizeof(list));
	el = (list*)malloc(sizeof(list));
	el2 = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el2 == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = el;
	spisok->prev = el2;
	spisok->length = 1;
	spisok->value = "5";
	el->next = el2;
	el->prev = spisok;
	el->length = 1;
	el->value = "1";
	el2->next = spisok;
	el2->prev = el;
	el2->length = 1;
	el2->value = "3";
	sortList(spisok);
	EXPECT_TRUE(strcmp(spisok->value, spisok->next->value) < 0);
	EXPECT_TRUE(strcmp(spisok->next->value, spisok->prev->value) < 0);
	EXPECT_TRUE(strcmp(spisok->value, spisok->prev->value) < 0);
	free(spisok);
	free(el);
	free(el2);
}

TEST(sortListTest, sortList_sortTheListWithTheElementsOfTheSameLengthSorted) {
	list* spisok, * el, * el2;
	spisok = (list*)malloc(sizeof(list));
	el = (list*)malloc(sizeof(list));
	el2 = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el2 == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = el;
	spisok->prev = el2;
	spisok->length = 1;
	spisok->value = "1";
	el->next = el2;
	el->prev = spisok;
	el->length = 1;
	el->value = "2";
	el2->next = spisok;
	el2->prev = el;
	el2->length = 1;
	el2->value = "3";
	sortList(spisok);
	EXPECT_TRUE(strcmp(spisok->value, spisok->next->value) < 0);
	EXPECT_TRUE(strcmp(spisok->next->value, spisok->prev->value) < 0);
	EXPECT_TRUE(strcmp(spisok->value, spisok->prev->value) < 0);
	free(spisok);
	free(el);
	free(el2);
}

TEST(sortListTest, sortList_sortTheListWithTheElementsOfTheSameLengthReverseSorted) {
	list* spisok, * el, * el2;
	spisok = (list*)malloc(sizeof(list));
	el = (list*)malloc(sizeof(list));
	el2 = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el2 == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = el;
	spisok->prev = el2;
	spisok->length = 1;
	spisok->value = "5";
	el->next = el2;
	el->prev = spisok;
	el->length = 1;
	el->value = "3";
	el2->next = spisok;
	el2->prev = el;
	el2->length = 1;
	el2->value = "1";
	sortList(spisok);
	EXPECT_TRUE(strcmp(spisok->value, spisok->next->value) < 0);
	EXPECT_TRUE(strcmp(spisok->next->value, spisok->prev->value) < 0);
	EXPECT_TRUE(strcmp(spisok->value, spisok->prev->value) < 0);
	free(spisok);
	free(el);
	free(el2);
}

TEST(sortListTest, sortList_sortTheListWithTheElementsOfTheDifferentLengthUnsorted) {
	list* spisok, * el, * el2;
	spisok = (list*)malloc(sizeof(list));
	el = (list*)malloc(sizeof(list));
	el2 = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el2 == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = el;
	spisok->prev = el2;
	spisok->length = 2;
	spisok->value = "50";
	el->next = el2;
	el->prev = spisok;
	el->length = 1;
	el->value = "5";
	el2->next = spisok;
	el2->prev = el;
	el2->length = 3;
	el2->value = "555";
	sortList(spisok);
	EXPECT_TRUE(strcmp(spisok->value, spisok->next->value) < 0);
	EXPECT_TRUE(strcmp(spisok->next->value, spisok->prev->value) < 0);
	EXPECT_TRUE(strcmp(spisok->value, spisok->prev->value) < 0);
	free(spisok);
	free(el);
	free(el2);
}

TEST(sortListTest, sortList_sortTheListWithTheSameElements) {
	list* spisok, * el, * el2;
	spisok = (list*)malloc(sizeof(list));
	el = (list*)malloc(sizeof(list));
	el2 = (list*)malloc(sizeof(list));
	if (spisok == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	if (el2 == NULL) {
		EXPECT_TRUE(1 == 0);
		return;
	}
	spisok->next = el;
	spisok->prev = el2;
	spisok->length = 1;
	spisok->value = "5";
	el->next = el2;
	el->prev = spisok;
	el->length = 1;
	el->value = "5";
	el2->next = spisok;
	el2->prev = el;
	el2->length = 1;
	el2->value = "5";
	sortList(spisok);
	EXPECT_TRUE(strcmp(spisok->value, spisok->next->value) <= 0);
	EXPECT_TRUE(strcmp(spisok->next->value, spisok->prev->value) <= 0);
	EXPECT_TRUE(strcmp(spisok->value, spisok->prev->value) <= 0);
	free(spisok);
	free(el);
	free(el2);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}