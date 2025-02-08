// Copyright (c) eski by Alex Eski 2024

#ifndef eski_trie_h
#define eski_trie_h

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "eski_string.h"

#define ESKI_TRIE_LETTERS 96 // ascii printable characters 32-127

// prefix tree for storing autocomplete posibilities
struct eski_Trie;

struct eski_Trie {
	bool is_end_of_a_word;
	char letter;
	struct eski_Trie* nodes[ESKI_TRIE_LETTERS];
};

struct eski_Trie_Matches {
	uint_fast32_t count;
	struct eski_String* entries;
};

static inline int eski_trie_index_get(char character) {
	return (int)character - ' ';
}

static inline char eski_trie_char_get(int position) {
	return (char)position + ' ';
}

struct eski_Trie* eski_trie_malloc();

void eski_trie_free(struct eski_Trie* tree);

void eski_trie_add(char* string, size_t length, struct eski_Trie* tree);
void eski_trie_add_string(struct eski_String string, struct eski_Trie* tree);
void eski_trie_add_multiple(struct eski_String* strings, int count, struct eski_Trie* tree);

struct eski_Trie* eski_trie_search(char* string, size_t length, struct eski_Trie* tree);
struct eski_Trie* eski_trie_search_string(struct eski_String string, struct eski_Trie* tree);

// gets all matches based on a search into matches. returns matches_length;
size_t eski_trie_get(char* search,
				       size_t search_length,
				       char* matches[],
				       const uint_fast32_t max_match_length,
				       struct eski_Trie* tree);

int eski_trie_index_get(char character);
char eski_trie_char_get(int position);

#endif // !eski_trie_h
