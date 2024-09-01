#include <stdlib.h>
#include <assert.h>
#include "eskilib_error_handler.h"
#include "eskilib_list.h"

#define ESKILIB_LIST_DEFAULT_SIZE 8

eskilib_List* eskilib_list_malloc(const size_t sizeOfList, const size_t sizeOfElements)
{
	eskilib_List* list = NULL;
	size_t listSize = 0;

	assert(sizeOfElements != 0);
	if (sizeOfElements == 0)
		return NULL;
	
	list = malloc(sizeof(eskilib_List));

	if (list == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_List.\n");

	listSize = sizeOfList == 0 ? ESKILIB_LIST_DEFAULT_SIZE : sizeOfList;

	list->elements = malloc(listSize * sizeOfElements);

	if (list->elements == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_List->elements.\n");

	list->size = listSize;
	list->position = 0;

	return list;
}

void eskilib_list_free(eskilib_List* list)
{
	assert(list != NULL);
	if (list == NULL)
		return;

	free(list->elements);
	list->elements = NULL;

	free(list);
	list = NULL;
}

enum eskilib_List_Result eskilib_list_add(void* element, eskilib_List* list)
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
		list->elements = realloc(list->elements, list->size * sizeof(element));

		if (list->elements == NULL)
		{
			eskilib_output_allocation_error_and_exit("Error reallocating eskilib_List->elements.\n");
		}
	}

	list->elements[list->position++] = element;

	return SUCCESS;
}
