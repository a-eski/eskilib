/* Copyright (C) eskilib by Alex Eski 2024 */

#ifndef ESKILIB_EDA_H_
#define ESKILIB_EDA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

enum eda_Result
{
	FAILURE_MALLOC = -4,
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_ELEMENT = -2,
	FAILURE_NULL_LIST = -1,
	FAILURE = 0,
	SUCCESS = 1
};

struct eda
{
	size_t size;
	size_t position;
	void** elements;
};
typedef struct eda eda;

eda* eda_malloc(const size_t sizeOfList, const size_t sizeOfElements);

void eda_free(eda* list);

enum eda_Result eda_add(void* element, eda* list);

#ifdef __cplusplus
}
#endif

#endif /* !ESKILIB_EDA_H_ */
