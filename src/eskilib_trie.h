/* Copyright (c) eskilib by Alex Eski 2024 */

#ifndef ESKILIB_TRIE_H_
#define ESKILIB_TRIE_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "eskilib_string.h"

#define ESKILIB_TRIE_LETTERS 96 // ascii printable characters 32-127

// prefix tree for storing autocomplete posibilities
struct eskilib_Trie;

struct eskilib_Trie {
	bool is_end_of_a_word;
	char letter;
	struct eskilib_Trie* nodes[ESKILIB_TRIE_LETTERS];
};

struct eskilib_Trie_Matches {
	uint_fast32_t count;
	struct eskilib_String* entries;
};

static inline int eskilib_trie_index_get(char character) {
	return (int)character - ' ';
}

static inline char eskilib_trie_char_get(int position) {
	return (char)position + ' ';
}

struct eskilib_Trie* eskilib_trie_malloc();

void eskilib_trie_free(struct eskilib_Trie* tree);

void eskilib_trie_add(char* string, size_t length, struct eskilib_Trie* tree);
void eskilib_trie_add_string(struct eskilib_String string, struct eskilib_Trie* tree);
void eskilib_trie_add_multiple(struct eskilib_String* strings, int count, struct eskilib_Trie* tree);

struct eskilib_Trie* eskilib_trie_search(char* string, size_t length, struct eskilib_Trie* tree);
struct eskilib_Trie* eskilib_trie_search_string(struct eskilib_String string, struct eskilib_Trie* tree);

// gets all matches based on a search into matches. returns matches_length;
size_t eskilib_trie_get(char* search,
				       size_t search_length,
				       char* matches[],
				       const uint_fast32_t max_match_length,
				       struct eskilib_Trie* tree);

int eskilib_trie_index_get(char character);
char eskilib_trie_char_get(int position);

#endif // !ESKILIB_TRIE_H_
