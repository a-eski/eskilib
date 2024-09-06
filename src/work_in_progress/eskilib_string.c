#include <stdlib.h>
#include "eskilib_string.h"

struct eskilib_String* eskilib_string_malloc_unsafe(char* value, uint32_t maxLength)
{
	uint32_t length = 0;
	struct eskilib_String* string = NULL;

	while (value[length++] != '\0')
	{
		if (length >= maxLength)
			return NULL;
	}

	string = malloc(sizeof(struct eskilib_String));
	string->value = malloc(length + 1);

	string->length = length;
	string->value = value;

	return string;
}

struct eskilib_String* eskilib_string_malloc_safe(char* value, uint32_t length)
{
	struct eskilib_String* string = NULL;

	string = malloc(sizeof(struct eskilib_String));
	string->value = malloc(length + 1);

	string->length = length;
	string->value = value;

	return string;
}

enum eskilib_String_Result eskilib_string_create_unsafe(char* string, uint32_t maxLength, struct eskilib_String* destination)
{
	return FAILURE;
}

enum eskilib_String_Result eskilib_string_create_safe(char* string, uint32_t length, struct eskilib_String* destination)
{
	return FAILURE;
}

enum eskilib_String_Result eskilib_string_concat(struct eskilib_String valueOne, struct eskilib_String valueTwo, struct eskilib_String* destination)
{
	return FAILURE;
}

enum eskilib_String_Result eskilib_string_copy(struct eskilib_String value, struct eskilib_String* destination)
{
	return FAILURE;
}

