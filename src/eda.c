/* Copyright (C) eskilib by Alex Eski 2024 */

#include <stdlib.h>
#include <assert.h>

#include "eda.h"

#define EDA_DEFAULT_SIZE 8

eda* eda_malloc(const size_t sizeOfList, const size_t sizeOfElements)
{
	eda* list = NULL;
	size_t listSize = 0;

	assert(sizeOfElements != 0);
	if (sizeOfElements == 0)
		return NULL;

	list = (eda*)malloc(sizeof(eda));

	if (!list) {
		return NULL;
	}

	listSize = sizeOfList == 0 ? EDA_DEFAULT_SIZE : sizeOfList;

	list->elements = (void**)malloc(listSize * sizeOfElements);

	if (!list->elements) {
		return NULL;
	}

	list->size = listSize;
	list->position = 0;

	return list;
}

void eda_free(eda* list)
{
	assert(list != NULL);
	if (list == NULL)
		return;

	free(list->elements);
	list->elements = NULL;

	free(list);
	list = NULL;
}

enum eda_Result eda_add(void* element, eda* list)
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

		if (!list->elements)
		{
			return FAILURE_MALLOC;
		}
	}

	list->elements[list->position++] = element;

	return SUCCESS;
}
