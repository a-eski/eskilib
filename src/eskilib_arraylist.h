#ifndef eskilib_arraylist_h
#define eskilib_arraylist_h

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	size_t Size;
	size_t Position;
	void** Elements;
} eskilib_ArrayList;

eskilib_ArrayList* eskilib_arraylist_allocate(const size_t sizeOfArrayList, const size_t sizeOfElements);

void eskilib_arraylist_free(eskilib_ArrayList* arrayList);

bool eskilib_arraylist_add(void* element, eskilib_ArrayList* arrayList);

#endif /* !eskilib_arraylist_h */

