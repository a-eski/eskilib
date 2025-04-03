#ifndef ESKILIB_ELIST_H_
#define ESKILIB_ELIST_H_

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#define elist_DEFAULT_SIZE 8

enum elist_Result {
	FAILURE_OUT_OF_MEMORY = -4,
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_ELEMENT = -2,
	FAILURE_NULL_LIST = -1,
	FAILURE = 0,
	SUCCESS = 1
};

#endif /* !ESKILIB_ELIST_H_ */

#ifndef ELIST_TYPE
#error "Must define ELIST_TYPE"
#endif /* !ELIST_TYPE */

struct elist {
	size_t size;
	size_t position;
	ELIST_TYPE* elements;
};

static inline
struct elist* elist_malloc(const size_t sizeOfList) {
	struct elist* list = NULL;
	size_t listSize = 0;

	list = malloc(sizeof(struct elist));

	if (!list) {
		return NULL;
	}

	listSize = sizeOfList == 0 ? elist_DEFAULT_SIZE : sizeOfList;

	list->elements = malloc(listSize * sizeof(ELIST_TYPE));

	if (!list->elements) {
		return NULL;
	}

	list->size = listSize;
	list->position = 0;

	return list;
}

static inline
void elist_free(struct elist* list) {
	assert(list != NULL);
	if (list == NULL)
		return;

	free(list->elements);
	list->elements = NULL;

	free(list);
	list = NULL;
}

static inline
enum elist_Result elist_add(ELIST_TYPE element, struct elist* list) {
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

		if (!list->elements) {
			return FAILURE_OUT_OF_MEMORY;
		}
	}

	list->elements[list->position++] = element;

	return SUCCESS;
}

#undef ELIST_TYPE
