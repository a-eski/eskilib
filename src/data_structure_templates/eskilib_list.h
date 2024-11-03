#ifndef eskilib_list_h
#define eskilib_list_h

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include "../eskilib_error_handler.h"

#define ESKILIB_LIST_DEFAULT_SIZE 8

enum eskilib_List_Result {
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_ELEMENT = -2,
	FAILURE_NULL_LIST = -1,
	FAILURE = 0,
	SUCCESS = 1
};

#endif /* !eskilib_list_h */

#ifndef ESKILIB_LIST_TYPE
#error "Must define ESKILIB_LIST_TYPE"
#endif /* !ESKILIB_LIST_TYPE */

struct eskilib_List {
	size_t size;
	size_t position;
	ESKILIB_LIST_TYPE* elements;
};

static inline
struct eskilib_List* eskilib_list_malloc(const size_t sizeOfList) {
	struct eskilib_List* list = NULL;
	size_t listSize = 0;

	list = malloc(sizeof(struct eskilib_List));

	if (list == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_List.\n");

	listSize = sizeOfList == 0 ? ESKILIB_LIST_DEFAULT_SIZE : sizeOfList;

	list->elements = malloc(listSize * sizeof(ESKILIB_LIST_TYPE));

	if (list->elements == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_List->elements.\n");

	list->size = listSize;
	list->position = 0;

	return list;
}

static inline
void eskilib_list_free(struct eskilib_List* list) {
	assert(list != NULL);
	if (list == NULL)
		return;

	free(list->elements);
	list->elements = NULL;

	free(list);
	list = NULL;
}

static inline
enum eskilib_List_Result eskilib_list_add(ESKILIB_LIST_TYPE element, struct eskilib_List* list) {
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
			eskilib_output_allocation_error_and_exit("Error reallocating eskilib_List->elements.\n");
		}
	}

	list->elements[list->position++] = element;

	return SUCCESS;
}

#undef ESKILIB_LIST_TYPE

