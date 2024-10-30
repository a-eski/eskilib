#include "eskilib_string.h"

char* eskilib_string_copy(char* dest, char* source, const uint_fast32_t maxBufferSize) {
	char* originalStringToSave = source;

	for (uint_fast32_t i = 0;
		i < maxBufferSize && (*dest = *source) != '\0';
		i++, ++dest, ++source);

	return (originalStringToSave);
}

[[nodiscard]]
bool eskilib_string_equals(char* stringOne, char* stringTwo, const uint_fast32_t maxStringSize) {
	const unsigned char *p1 = (const unsigned char*)stringOne;
	const unsigned char *p2 = (const unsigned char*)stringTwo;

	for (uint_fast32_t i = 0; i <= maxStringSize && *p1 && *p1 == *p2; i++) {
		if (i == maxStringSize)
			return -1;

		++p1, ++p2;
	}

	return (( *p1 > *p2 ) - ( *p2  > *p1 )) == 0;
}

[[nodiscard]]
int_fast32_t eskilib_string_compare(char* stringOne, char* stringTwo, const uint_fast32_t maxStringSize) {
	const unsigned char *p1 = (const unsigned char*)stringOne;
	const unsigned char *p2 = (const unsigned char*)stringTwo;

	for (uint_fast32_t i = 0; i <= maxStringSize && *p1 && *p1 == *p2; i++) {
		if (i == maxStringSize)
			return -1;

		++p1, ++p2;
	}

	return ( *p1 > *p2 ) - ( *p2  > *p1 );
}

bool eskilib_string_contains_unsafe(const char* string, const char* substring) {
	const char* a;
	const char* b;

	b = substring;

	if (*b == '\0')
		return true;

	for (; *string != '\0'; string += 1) {
		if (*string != *b)
			continue;

		a = string;
		while (1) {
			if (*b == 0) {
				return (char*)string;
			}
			if (*a++ != *b++) {
				break;
			}
		}
		b = substring;
	}

	return false;
}

bool eskilib_string_contains(const struct eskilib_String string, const struct eskilib_String substring) {
	if (string.length < substring.length)
		return false;

	char* stringValue = string.value;

	const char* a;
	const char* b;

	b = substring.value;

	if (*b == '\0')
		return true;

	for (uint_fast32_t i = 0; i < string.length && *stringValue != '\0'; i++, stringValue += 1) {
		if (*stringValue != *b)
			continue;

		a = stringValue;
		for (uint_fast32_t j = 0; j < substring.length; j++) {
			if (*b == '\0') {
				return true;
			}
			if (*a++ != *b++) {
				break;
			}
		}
		b = substring.value;
	}

	return false;
}

/*struct eskilib_String eskilib_string_concatenate(struct eskilib_String destination, struct eskilib_String source) {
	struct eskilib_String originalStringToSave = destination;

	while (*destination.value)
		++destination.value;
	while ((*destination.value++ = *source.value++));

	return originalStringToSave;
}*/

/*char* eskilib_string_concat(const char* stringOne, uint_fast32_t lengthOne,
			    const char* stringTwo, uint_fast32_t lengthTwo)
{
	char* result = malloc(sizeof(char) * (lengthOne + lengthTwo - 1));

	for (uint_fast32_t i = 0; i < lengthOne && stringOne[i] != '\0'; i++) {
		*result = stringOne[i];
		++result;
	}

	for (uint_fast32_t i = lengthOne; i < lengthOne + lengthTwo; i++) {
		*result = stringTwo[i];
		++result;
	}

	return result;
}

char* eskilib_string_replace(char* string, uint_fast32_t length, char value)
{
	for (uint_fast32_t i = 0; i < length; i++) {
		if (*string == value)
			string = value;
		++string;
	}

	return string;
}*/

