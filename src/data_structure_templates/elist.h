/* Copyright (C) eskilib by Alex Eski 2024 */
/* elist.h: a generic list implementation that doesn't rely on macros */
/* You must define ELIST_TYPE before including this header */
/* If you want null checks for your ELIST_TYPE, you can define ELIST_NULL_CHECKS */

#ifndef ESKILIB_ELIST_H_
#define ESKILIB_ELIST_H_

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>


#define ELIST_DEFAULT_SIZE 8

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
typedef struct elist elist;

static inline
elist* elist_malloc(const size_t sizeOfList) {
	elist* list = NULL;
	size_t listSize = 0;

	list = malloc(sizeof(elist));

	if (!list) {
		return NULL;
	}

	listSize = sizeOfList == 0 ? ELIST_DEFAULT_SIZE : sizeOfList;

	list->elements = malloc(listSize * sizeof(ELIST_TYPE));
	if (!list->elements) {
		return NULL;
	}

	list->size = listSize;
	list->position = 0;

	return list;
}

static inline
void elist_free(elist* list) {
	assert(list);
	if (!list) {
		return;
	}

	if (list->elements) {
		free(list->elements);
		list->elements = NULL;
	}

	free(list);
	list = NULL;
}

static inline
enum elist_Result elist_add(ELIST_TYPE element, elist* list) {
	assert(list);
	if (!list) {
		return FAILURE_NULL_LIST;
	}

#	ifdef ELIST_NULL_CHECKS
	assert(element);
	if (!element) {
		return FAILURE_NULL_ELEMENT;
	}
#	endif /* ELIST_NULL_CHECKS */

	if (list->position > list->size || list->position == SIZE_MAX - 1) {
		return FAILURE_OVERFLOW_PROTECTION;
	}

	if (list->position == list->size) {
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
#undef ELIST_NULL_CHECKS
