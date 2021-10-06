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
	list spis = {NULL, 0, NULL, NULL};
	list* spisok = &spis;
	addElementToList(spisok, "123456");
	EXPECT_TRUE(spisok != NULL);
	EXPECT_EQ(spisok->length, strlen("123456"));
	EXPECT_TRUE(spisok->next == NULL);
	EXPECT_TRUE(spisok->prev == NULL);
	EXPECT_TRUE(strcmp(spisok->value, "123456") == 0);
}

TEST(addElementToListTest, addElementToList_addElementAtTheSemiFullList) {
	list spis = {"123456", 6, NULL, NULL};
	list* spisok = &spis;
	addElementToList(spisok, "7654321");
	EXPECT_TRUE(spisok != NULL);
	EXPECT_TRUE(spisok->next != NULL);
	EXPECT_TRUE(spisok->prev == NULL);
	EXPECT_TRUE(strcmp(spisok->next->value, "7654321") == 0);
	EXPECT_EQ(spisok->next->length, strlen("7654321"));
	free(spisok->next);
}

TEST(addElementToListTest, addElementToList_addElementAtTheFullList) {
	list spis = { "123456", 6, NULL, NULL }, elem = { "7654321", 7, NULL, NULL };
	list* spisok = &spis, * el = &elem;
	spisok->next = el;
	el->prev = spisok;
	addElementToList(spisok, "12345678");
	EXPECT_TRUE(spisok != NULL);
	EXPECT_TRUE(spisok->next->next != NULL);
	EXPECT_TRUE(spisok->prev == NULL);
	EXPECT_TRUE(strcmp(spisok->next->next->value, "12345678") == 0);
	EXPECT_EQ(spisok->next->next->length, strlen("12345678"));
	free(spisok->next->next);
}

TEST(destroyListTest, destroyList_destroyTheEmptyList) {
	list* spisok = NULL;
	destroyList(&spisok);
	assert(spisok == NULL);
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
	assert(spisok == NULL);
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
	spisok->prev = NULL;
	spisok->length = 6;
	spisok->value = "123456";
	el->next = NULL;
	el->prev = spisok;
	el->length = 7;
	el->value = "7654321";
	destroyList(&spisok);
	assert(spisok == NULL);
}

TEST(swapValuesTest, swapValuesTest_correctValue) {
	list spis = { "123456", 6, NULL, NULL }, elem = { "7654321", 7, NULL, NULL };
	list* spisok = &spis, * el = &elem;
	spisok->next = el;
	el->prev = spisok;
	swapValues(spisok, el);
	EXPECT_TRUE(strcmp(spisok->value, "7654321") == 0);
	EXPECT_TRUE(strcmp(el->value, "123456") == 0);
}

TEST(sortListTest, sortList_sortTheEmptyList) {
	list* spisok = NULL;
	sortList(spisok);
	EXPECT_TRUE(spisok == NULL);
}

TEST(sortListTest, sortList_sortTheSemiFullList) {
	list spis = { "123456", 6, NULL, NULL };
	list* spisok = &spis;
	sortList(spisok);
	EXPECT_TRUE(strcmp(spisok->value, "123456") == 0);
}

TEST(sortListTest, sortList_sortTheListWithTheElementsOfTheSameLengthUnsorted) {
	list elem1 = { "3", 1, NULL, NULL }, elem2 = { "2", 1, NULL, NULL }, elem3 = { "1", 1, NULL, NULL };
	list* el1 = &elem1, * el2 = &elem2, * el3 = &elem3;
	el1->next = el2;
	el2->next = el3;
	el3->prev = el2;
	el2->prev = el1;
	sortList(el1);
	EXPECT_TRUE(strcmp(el1->value, el1->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->next->value, el1->next->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->value, el1->next->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->value, "1") == 0);
	EXPECT_TRUE(strcmp(el1->next->value, "2") == 0);
	EXPECT_TRUE(strcmp(el1->next->next->value, "3") == 0);
}

TEST(sortListTest, sortList_sortTheListWithTheElementsOfTheSameLengthSorted) {
	list elem1 = { "1", 1, NULL, NULL }, elem2 = { "2", 1, NULL, NULL }, elem3 = { "3", 1, NULL, NULL };
	list* el1 = &elem1, * el2 = &elem2, * el3 = &elem3;
	el1->next = el2;
	el2->next = el3;
	el3->prev = el2;
	el2->prev = el1;
	sortList(el1);
	EXPECT_TRUE(strcmp(el1->value, el1->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->next->value, el1->next->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->value, el1->next->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->value, "1") == 0);
	EXPECT_TRUE(strcmp(el1->next->value, "2") == 0);
	EXPECT_TRUE(strcmp(el1->next->next->value, "3") == 0);
}

TEST(sortListTest, sortList_sortTheListWithTheElementsOfTheSameLengthReverseSorted) {
	list elem1 = { "5", 1, NULL, NULL }, elem2 = { "3", 1, NULL, NULL }, elem3 = { "1", 1, NULL, NULL };
	list* el1 = &elem1, * el2 = &elem2, * el3 = &elem3;
	el1->next = el2;
	el2->next = el3;
	el3->prev = el2;
	el2->prev = el1;
	sortList(el1);
	EXPECT_TRUE(strcmp(el1->value, el1->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->next->value, el1->next->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->value, el1->next->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->value, "1") == 0);
	EXPECT_TRUE(strcmp(el1->next->value, "3") == 0);
	EXPECT_TRUE(strcmp(el1->next->next->value, "5") == 0);
}

TEST(sortListTest, sortList_sortTheListWithTheElementsOfTheDifferentLengthUnsorted) {
	list elem1 = { "50", 2, NULL, NULL }, elem2 = { "5", 1, NULL, NULL }, elem3 = { "555", 3, NULL, NULL };
	list* el1 = &elem1, * el2 = &elem2, * el3 = &elem3;
	el1->next = el2;
	el2->next = el3;
	el3->prev = el2;
	el2->prev = el1;
	sortList(el1);
	EXPECT_TRUE(strcmp(el1->value, el1->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->next->value, el1->next->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->value, el1->next->next->value) < 0);
	EXPECT_TRUE(strcmp(el1->value, "5") == 0);
	EXPECT_TRUE(strcmp(el1->next->value, "50") == 0);
	EXPECT_TRUE(strcmp(el1->next->next->value, "555") == 0);
}

TEST(sortListTest, sortList_sortTheListWithTheSameElements) {
	list elem1 = { "1", 1, NULL, NULL }, elem2 = { "1", 1, NULL, NULL }, elem3 = { "1", 1, NULL, NULL };
	list* el1 = &elem1, * el2 = &elem2, * el3 = &elem3;
	el1->next = el2;
	el2->next = el3;
	el3->prev = el2;
	el2->prev = el1;
	sortList(el1);
	EXPECT_TRUE(strcmp(el1->value, el1->next->value) == 0);
	EXPECT_TRUE(strcmp(el1->next->value, el1->next->next->value) == 0);
	EXPECT_TRUE(strcmp(el1->value, el1->next->next->value) == 0);
	EXPECT_TRUE(strcmp(el1->value, "1") == 0);
	EXPECT_TRUE(strcmp(el1->next->value, "1") == 0);
	EXPECT_TRUE(strcmp(el1->next->next->value, "1") == 0);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}