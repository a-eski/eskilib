#ifndef eski_list_h
#define eski_list_h

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include "../eski_error_handler.h"

#define ESKI_LIST_DEFAULT_SIZE 8

enum eski_List_Result {
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_ELEMENT = -2,
	FAILURE_NULL_LIST = -1,
	FAILURE = 0,
	SUCCESS = 1
};

#endif /* !eski_list_h */

#ifndef ESKI_LIST_TYPE
#error "Must define ESKI_LIST_TYPE"
#endif /* !ESKI_LIST_TYPE */

struct eski_List {
	size_t size;
	size_t position;
	ESKI_LIST_TYPE* elements;
};

static inline
struct eski_List* eski_list_malloc(const size_t sizeOfList) {
	struct eski_List* list = NULL;
	size_t listSize = 0;

	list = malloc(sizeof(struct eski_List));

	if (list == NULL)
		eski_output_allocation_error_and_exit("Failed to allocate eski_List.\n");

	listSize = sizeOfList == 0 ? ESKI_LIST_DEFAULT_SIZE : sizeOfList;

	list->elements = malloc(listSize * sizeof(ESKI_LIST_TYPE));

	if (list->elements == NULL)
		eski_output_allocation_error_and_exit("Failed to allocate eski_List->elements.\n");

	list->size = listSize;
	list->position = 0;

	return list;
}

static inline
void eski_list_free(struct eski_List* list) {
	assert(list != NULL);
	if (list == NULL)
		return;

	free(list->elements);
	list->elements = NULL;

	free(list);
	list = NULL;
}

static inline
enum eski_List_Result eski_list_add(ESKI_LIST_TYPE element, struct eski_List* list) {
	assert(list != NULL);
	if (list == NULL)
		return FAILURE_NULL_LIST;

	// assert(element != NULL);
	// if (element == NULL)
	// 	return FAILURE_NULL_ELEMENT;

	if (list->position > list->size || list->position == SIZE_MAX - 1)
		return FAILURE_OVERFLOW_PROTECTION;

	if (list->position == list->size)
	{
		list->size *= 2;
		list->elements = realloc(list->elements, list->size * sizeof(element));

		if (list->elements == NULL)
		{
			eski_output_allocation_error_and_exit("Error reallocating eski_List->elements.\n");
		}
	}

	list->elements[list->position++] = element;

	return SUCCESS;
}

#undef ESKI_LIST_TYPE
