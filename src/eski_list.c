#include <stdlib.h>
#include <assert.h>
#include "eski_error_handler.h"
#include "eski_list.h"

#define eski_LIST_DEFAULT_SIZE 8

eski_List* eski_list_malloc(const size_t sizeOfList, const size_t sizeOfElements)
{
	eski_List* list = NULL;
	size_t listSize = 0;

	assert(sizeOfElements != 0);
	if (sizeOfElements == 0)
		return NULL;

	list = (eski_List*)malloc(sizeof(eski_List));

	if (list == NULL)
		eski_output_allocation_error_and_exit("Failed to allocate eski_List.\n");

	listSize = sizeOfList == 0 ? eski_LIST_DEFAULT_SIZE : sizeOfList;

	list->elements = (void**)malloc(listSize * sizeOfElements);

	if (list->elements == NULL)
		eski_output_allocation_error_and_exit("Failed to allocate eski_List->elements.\n");

	list->size = listSize;
	list->position = 0;

	return list;
}

void eski_list_free(eski_List* list)
{
	assert(list != NULL);
	if (list == NULL)
		return;

	free(list->elements);
	list->elements = NULL;

	free(list);
	list = NULL;
}

enum eski_List_Result eski_list_add(void* element, eski_List* list)
{
	assert(list != NULL);
	if (list == NULL)
		return FAILURE_NULL_LIST;

	assert(element != NULL);
	if (element == NULL)
		return FAILURE_NULL_ELEMENT;

	if (list->position > list->size || list->position == SIZE_MAX - 1)
		return FAILURE_OVERFLOW_PROTECTION;

	if (list->position == list->size)
	{
		list->size *= 2;
		list->elements = (void**)realloc(list->elements, list->size * sizeof(element));

		if (list->elements == NULL)
		{
			eski_output_allocation_error_and_exit("Error reallocating eski_List->elements.\n");
		}
	}

	list->elements[list->position++] = element;

	return SUCCESS;
}
