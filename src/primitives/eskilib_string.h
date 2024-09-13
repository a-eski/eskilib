#ifndef eskilib_string_h
#define eskilib_string_h

#include <stdint.h>

char* eskilib_string_copy(char* dest, char* source, const uint_fast32_t maxBufferSize);

int_fast32_t eskilib_string_compare(char* stringOne, char* stringTwo, const uint_fast32_t maxBufferSize);

#endif // !eskilib_string_h

