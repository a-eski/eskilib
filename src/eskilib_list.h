#ifndef eskilib_list_h
#define eskilib_list_h

#include <stdint.h>

enum eskilib_List_Result
{
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_ELEMENT = -2,
	FAILURE_NULL_LIST = -1,
	FAILURE = 0,
	SUCCESS = 1
};

typedef struct
{
	size_t size;
	size_t position;
	void** elements;
} eskilib_List;

eskilib_List* eskilib_list_malloc(const size_t sizeOfList, const size_t sizeOfElements);

void eskilib_list_free(eskilib_List* list);

enum eskilib_List_Result eskilib_list_add(void* element, eskilib_List* list);

#endif /* !eskilib_list_h */

