#ifndef eskilib_string_h
#define eskilib_string_h

#include <stdint.h>

enum eskilib_String_Result
{
	FAILURE = 0,
	SUCCESS = 1
};

struct eskilib_String
{
	uint32_t length;
	char* value;
};

struct eskilib_String* eskilib_string_malloc_unsafe(char* value, uint32_t maxLength);
struct eskilib_String* eskilib_string_malloc_safe(char* value, uint32_t length);

enum eskilib_String_Result eskilib_string_create_unsafe(char* string, uint32_t maxLength, struct eskilib_String* destination);
enum eskilib_String_Result eskilib_string_create_safe(char* string, uint32_t length, struct eskilib_String* destination);

enum eskilib_String_Result eskilib_string_concat(struct eskilib_String valueOne, struct eskilib_String valueTwo, struct eskilib_String* destination);

enum eskilib_String_Result eskilib_string_copy(struct eskilib_String value, struct eskilib_String* destination);


#endif /* !eskilib_string_h */
