#ifdef __cplusplus
extern "C" {
#endif

	typedef struct list_t {
		char* value;
		int length;
		struct list_t* next;
		struct list_t* prev;
	}list;

	typedef enum status {
		ERROR,
		OK
	};

	list * createList();

	int addElementToList(list* spisok, char* value);

	int destroyList(list** spisok);

	void swapValues(list* a, list* b);

	void sortList(list* source);

#ifdef __cplusplus
}
#endif