#ifndef eski_list_h
#define eski_list_h

#include <stdlib.h>
#include <stdint.h>

enum eski_List_Result
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
} eski_List;

eski_List* eski_list_malloc(const size_t sizeOfList, const size_t sizeOfElements);

void eski_list_free(eski_List* list);

enum eski_List_Result eski_list_add(void* element, eski_List* list);

#endif /* !eski_list_h */
