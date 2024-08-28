#include <stdlib.h>
#include <assert.h>
#include "eskilib_error_handler.h"
#include "eskilib_arraylist.h"

#define ESKILIB_ARRAYLIST_DEFAULT_SIZE 4

eskilib_ArrayList* eskilib_arraylist_allocate(const size_t sizeOfArrayList, const size_t sizeOfElements)
{
	eskilib_ArrayList* arrayList = NULL;
	size_t arrayListSize = 0;

	assert(sizeOfElements != 0);
	if (sizeOfElements == 0)
		return NULL;
	
	arrayList = malloc(sizeof(eskilib_ArrayList));

	if (arrayList == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_ArrayList.\n");

	arrayListSize = sizeOfArrayList == 0 ? ESKILIB_ARRAYLIST_DEFAULT_SIZE : sizeOfArrayList;

	arrayList->Elements = malloc(arrayListSize * sizeOfElements);

	if (arrayList->Elements == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_ArrayList->Elements.\n");

	arrayList->Size = arrayListSize;
	arrayList->Position = 0;

	return arrayList;
}

void eskilib_arraylist_free(eskilib_ArrayList* arrayList)
{
	assert(arrayList != NULL);
	if (arrayList == NULL)
		return;

	free(arrayList->Elements);
	arrayList->Elements = NULL;

	free(arrayList);
	arrayList = NULL;
}

bool eskilib_arraylist_add(void* element, eskilib_ArrayList* arrayList)
{
	assert(arrayList != NULL);
	if (arrayList == NULL)
		return false;

	assert(element != NULL);
	if (element == NULL)
		return false;

	if (arrayList->Position > arrayList->Size || arrayList->Position == SIZE_MAX - 1)
		return false;

	if (arrayList->Position == arrayList->Size)
	{
		arrayList->Size *= 2;
		arrayList->Elements = realloc(arrayList->Elements, arrayList->Size * sizeof(element));

		if (arrayList->Elements == NULL)
		{
			eskilib_output_allocation_error_and_exit("Error reallocating arrayList->Elements.\n");
		}
	}

	arrayList->Elements[arrayList->Position++] = element;

	return true;
}
